# 107 電腦視覺期中考
1. What is the general procedure of computer vision recognition paradigm?
    - C(input from camera) -> G(grab image) -> P(preprocess) -> R(recognize)

2. List three Thresholding techniques
    - 3.2 Basic Global Thresholding
    - 3.3 Adaptive Thresholding
    - 3.4.1 Variance-Based Thresholding
    - 3.4.2 Entropy-Based Thresholding

3. Describe the main procedure of Canny Edge Detection Algorithm
    1. Apply Gaussian filter to smooth the image and remove the noise
    2. Find the intensity gradients of the image(Sobel)
    3. Apply non-maximum supression(NMS) involing subpixel intepolation of pixel intensities to thin the edge.
    4. Apply double threshold to determine potential edges
    5. Suppressing all the other edges that are weak and not connected to strong edges.

4. Compare the Canny Edge Detection Algorithm and general edge detection methods, what is the major improvement with Canny method?
    - It permits thin line structures to emerge and ensures that they are connected together as far as possible.
 
5. List three Corner and Interest Point Detection method
    - Template Matching (page 47/103)
    - Moravec Corner Detection (page 48/103)
    - Harris Detector (page 53/103)
    - Hessian Detector (page 67/103)

6. List three basic 1x3 masks of Laws' Texture Energy approach
    - 這東西好像這學期還沒上過
    -  [-1, 2, -1], [-1, 0, 1], [-1, -2, -1]
    
7. Manufactured good often check using digital image processing. Given the following picture taken from a product line. Design a computer vision inspection procedure to detect the abnormal bottles for this product line. You just need to draw the block diagram of yur idea.
    - use edge detection
    - 記錄長縱線的分佈，並記錄他們的 x coord
    - for loop x coord vector，若出現較小的 x[idx]-x[idx-1] 則為一個瓶子們的界限，各個瓶子的區間為 (x[idx-1]+x[idx-2]) ~ (x[idx]+x[idx+1])/2
    - 對於各區間，由上到下偵測第二條橫線
    - 觀察第二條橫線的 y-coord 去偵測產品好壞
    
8. Given a 5x5 image as the following matrix:
    30 32 100 102 100
    30 32 100 102 100
    70 32 100 102 100
    30 31 100 102 100
    31 31 100 102 100
    Compute the threshold value by:
    a. Adaptive Thresholding method, given the inital threshold 60
    b. Golval Valley approach
    c. Variance-based Thresholding
    d. Apply the Hysteresis Thresholding method to detect the edge. Set the initial upper threshold as 101 and low threshold level as 60
    e. Compare the results of question a and d, what is the difference? Can you tell the advantage of Hystersis thresholding method?
    - a 的計算方式會讓 70 這個 element 劃入邊的範圍內，但實際上這個可能會是 noise 而需要被過濾掉，Hystersis thresholding 的 double thresholds 機制可以迴避掉這個情形。
    
9. Apply the following Sobel edge detection masks s1 and s2 for image given in Problem 8
    a. Compute the edge magnitude s = abs(s_x) + abs(s_y)
    b. Compute the edge magnitude s = max(abs(s_x), abs(s_y))
10. Given a 5x5 image as the following matrix:
    20 20  20  20  20
    20 20  20  20  20
    20 20 200 200 200
    20 20 200 200 200
    20 20 200 200 200
    Detect the corner by the following methods:
    a. Template Matching using the following mask and show what you have detected.
        -4 -4 -4
        -4 5 5
        -4 5 5
    b. Given the following first-order derivation masks s1 and s2. Compute Hessian corner response of the center pixel in the above given image.
    s1: [[-1, -1, -1], [0, 0, 0], [1, 1, 1]]
    s2: [[-1, 0, 1], [-1, 0, 1], [-1, 0, 1]]
    c. Compute the Harris corner signal of the center pixel in the above given image using the first-order derivation masks s1 and s2.