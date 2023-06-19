import cv2
import glob as glob
import hyperlpr3 as lpr3
import re

# Set parameters going to be used
WIDTH_OFFSET = 7
HEIGHT_OFFSET = 7


def check(plate):
    if len(plate) != 6 and len(plate) != 7:
        return False
    if len(plate) == 7:
        first = plate[:3]
        last = plate[3:]
        first = first.replace('0','D').replace('2','Z').replace('1','J').replace('8','B').replace('5','S').replace('4', 'A')
        if first.isalpha() == False: return False
        last = last.replace('D','0').replace('O','0').replace('Z','2').replace('I','1').replace('J','1').replace('B','8').replace('S','5')
        if last.isnumeric() == False: return False
        
        plate = first + last
        if plate[0] not in ['A', 'B', 'E', 'T', 'R', 'W']:
            return False
        return True
    return True

def FilterPlate(plateList):
    new_plateList = {}
    for plate in plateList:
        plate = plate.upper()
        plate = "".join(re.findall("[A-Z|0-9]", plate)) 
        new_plateList[plate] = new_plateList.setdefault(plate, 0) + 1
    
    ans, cnt = '', 0
    for i in new_plateList.keys():
        if cnt < new_plateList[i]:
            cnt = new_plateList[i]
            ans = i
    return ans, new_plateList

###################################
# Function that serves as a first layer to detect the candidate region that might be a plate 
# a pre-trained MLP model
# Input: candidate frame
# Output: list of region that are plates
###################################
def preprocess(frame):

    # adjust image using image processing techniques
    gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
    blurred = cv2.GaussianBlur(gray, (3, 3), 2)
    contrast = 1.3; brightness = 0.5
    high_contrast = cv2.convertScaleAbs(blurred, alpha = contrast, beta = brightness)

    # thresholding
    thresh = cv2.adaptiveThreshold(high_contrast, 255, cv2.ADAPTIVE_THRESH_GAUSSIAN_C, cv2.THRESH_BINARY_INV, 201, 2)

    # masking
    mask = thresh * high_contrast

    # edge detection
    edges = cv2.Laplacian(thresh, ddepth = -1, ksize = 5)

    # find contours
    contours, hierarchy = cv2.findContours(edges, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_NONE)

    # filter contours by area    
    contour_filter = []
    for contour in contours:
        area = cv2.contourArea(contour)
        if area > 1000:
            contour_filter.append(contour)

    # filter contours by its shape. Plate should be a appoximated rectangle
    contour_reshape = []
    for contour in contour_filter:
        epsilon = 0.04 * cv2.arcLength(contour, True)
        approx = cv2.approxPolyDP(contour, epsilon, True)
        contour_reshape.append(approx)
        if len(approx) <= 6 and len(approx) >= 4 and cv2.isContourConvex(approx):
            contour_reshape.append(approx)

    # For the contours that are approximated to be a rectangle, crop the image and feed it to the model to
    # predict whether it is a plate or not
    catcher = lpr3.LicensePlateCatcher(detect_level=lpr3.DETECT_LEVEL_HIGH)
    plateDetected = []
    for contour in contour_reshape:
        try:
            x, y, w, h = cv2.boundingRect(contour)
            bbox = frame[y-HEIGHT_OFFSET: y+h+HEIGHT_OFFSET, x-WIDTH_OFFSET: x+w+WIDTH_OFFSET, :]
            bbox = cv2.resize(bbox, (500, 200))
            predict = catcher(bbox)
            if len(predict)!=0:
                for code, confidence, type_idx, box in predict:
                    text = f"{code}"
                    plateDetected.append(text)
        except cv2.error: pass

    return plateDetected











