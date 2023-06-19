#!/usr/bin/env python
# coding: utf-8

# In[12]:


import cv2, os
import numpy as np

def graystyle(image):
    output = np.zeros((image.shape[0], image.shape[1]))
    for x in range(image.shape[0]):
        for y in range(image.shape[1]):
            tmp = image[x][y]
            output[x][y] = 0.299 * tmp[0] + 0.587 * tmp[1] + 0.114 * tmp[2]
    return output
    

def conv2D(image, kernel, padding=0, strides=1):
    # Cross Correlation
    kernel = np.flipud(np.fliplr(kernel))

    # Gather Shapes of Kernel + Image + Padding
    xKernShape, yKernShape = kernel.shape[0], kernel.shape[1]
    xImgShape, yImgShape = image.shape[0], image.shape[1]

    # Shape of Output Convolution
    xOutput = (xImgShape - xKernShape + 2 * padding) // strides + 1
    yOutput = (yImgShape - yKernShape + 2 * padding) // strides + 1
    output = np.zeros((xOutput, yOutput))

    # Apply Equal Padding to All Sides
    if padding != 0:
        imagePadded = np.zeros((image.shape[0] + padding*2, image.shape[1] + padding*2))
        imagePadded[int(padding):int(-1 * padding), int(padding):int(-1 * padding)] = image
    else:
        imagePadded = image

    # Iterate through image
    for y in range(image.shape[1]):
        # Exit Convolution
        if y > image.shape[1] - yKernShape: break
        if y % strides == 0:
            for x in range(image.shape[0]):
                if x > image.shape[0] - xKernShape: break
                try:
                    if x % strides == 0:
                        output[x, y] = (kernel * imagePadded[x: x + xKernShape, y: y + yKernShape]).sum()
                except: break
    return output

kernal = np.array([[-1, 1, 1], [-1, -2, 1], [-1, 1, 1]])
filepath = os.environ['USERPROFILE'] + '/desktop/gray.jpg'
img = cv2.imread(filepath)

gray = graystyle(img)
output = conv2D(gray, kernal, padding = 2)
cv2.imwrite(os.environ['USERPROFILE'] + '/desktop/result.jpg', output)


# In[ ]:




