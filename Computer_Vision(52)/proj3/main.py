import cv2
from tqdm import tqdm
from CustomFunc import FilterPlate, preprocess
import cvlib as cv
import hyperlpr3 as lpr3
import glob

video_path = glob.glob(f"./Testing Video/*")


def open_video():
    print(f"Total video: {len(video_path)}")
    catcher = lpr3.LicensePlateCatcher(detect_level=lpr3.DETECT_LEVEL_HIGH)
    header, dic_header = "", ""

    for videoinx in range(len(video_path)):
        result = []
        cap = cv2.VideoCapture(video_path[videoinx]) # read video

        frame_count = 0
        while cap.isOpened():
            ret, frame = cap.read()
            if not ret:
                break
            
            if frame_count % 10 == 0:
                bbox, label, conf = cv.detect_common_objects(frame, model='yolov4', enable_gpu = True)

                # if there is a car in the frame, detect license plate in car region only
                if label.count('car') > 0:
                    for i in range(len(bbox)):
                        if label[i] == "car" or label[i] == "trunk":
                            bbox_valid = [x if x > 0 else 0 for x in bbox[i]]
                            bbox_image = frame[bbox_valid[1]: bbox_valid[3], bbox_valid[0]: bbox_valid[2], :]
                            results = catcher(bbox_image)

                            if len(results)!=0:
                                for code, confidence, type_idx, box in results:
                                    text = f"{code}"
                                    result.append(text)
                            else:
                                plate = preprocess(frame[bbox_valid[1]: bbox_valid[3], bbox_valid[0]: bbox_valid[2], :])
                                if len(plate) > 0:
                                    for p in plate:
                                        result.append(p)
                else:
                    bbox_image = frame
                    results = catcher(bbox_image)

                    if len(results)!=0:
                        for code, confidence, type_idx, box in results:
                            text = f"{code}"
                            result.append(text)
                    else:
                        plate = preprocess(bbox_image)
                        if len(plate) > 0:
                            for p in plate:
                                result.append(p)

            frame_count += 1

        result, dic = FilterPlate(result)
        header += video_path[videoinx].split("\\")[-1] + ' ' + result + " \n"
        dic_header += str(dic) + '\n'

        print(f"Result of {videoinx+1} video: {result}")
        print(f"Video {videoinx+1} done")
    

    text_file = open("../output.txt", "w")
    text_file.write(header)
    text_file.close()


open_video()



