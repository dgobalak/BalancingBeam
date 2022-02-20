import cv2
import numpy as np
import time


# Set parameters
BEAM_LEN = 52.0
CAPTURE_WIDTH = 1280
CAPTURE_HEIGHT = 720

MAX_DIST = 45.0
MIN_DIST = 8.0

# Load hue, saturation, values for pink highlighter
hsv_value = np.load('hsv_value.npy')

# Setup webcam
cap = cv2.VideoCapture(0)
cap.set(3, CAPTURE_WIDTH)
cap.set(4, CAPTURE_HEIGHT)

kernel = np.ones((5,5), np.uint8)
x, y = 0, 0
noiseth = 800


def get_target_dist():
    _, frame = cap.read()
    frame = cv2.flip(frame, 1)
    
    hsv = cv2.cvtColor(frame, cv2.COLOR_BGR2HSV)
    
    lower_range = hsv_value[0]
    upper_range = hsv_value[1]

    mask = cv2.inRange(hsv, lower_range, upper_range)
    mask = cv2.erode(mask, kernel, iterations = 1)
    mask = cv2.dilate(mask, kernel, iterations = 2)
    
    # Get coordinate of highlighter
    contours, hierarchy = cv2.findContours(mask, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)
    if contours and cv2.contourArea(max(contours, key = cv2.contourArea)) > noiseth:
        c = max(contours, key = cv2.contourArea)    
        x, y, w, h = cv2.boundingRect(c)
    else:
        x, y = 0, 0
    
    # Scale x coordinate to within beam limits
    set_point = BEAM_LEN - (x / CAPTURE_WIDTH) * BEAM_LEN
    if set_point > MAX_DIST or set_point < MIN_DIST:
        set_point = BEAM_LEN // 2 
    
    return set_point
    

def main():
    while 1:
        set_point = get_target_dist()
        print(set_point)
        
    cv2.destroyAllWindows()
    cap.release()
        
        
if __name__ == '__main__':
    main()