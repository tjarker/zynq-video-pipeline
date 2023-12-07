import cv2 as cv
import imutils
import sys
import numpy as np
import matplotlib.pyplot as plt
def contrast_enh(img, p):
    chans = cv.split(img)
    for channel in chans:
        hist = cv.calcHist([channel], [0], None, [256], [0, 256])
        high_threshold = max(hist)*p
        low_threshold = min(hist)*(1+p)
        
        for first in range(hist.size):
            if hist[first] > low_threshold:
                break;

        for last in range(255,-1,-1):
            if hist[last] > high_threshold:
                break;

        if last == first:
            den = 0.1
        else:
            den = last - first
            
        scale = 255 / den
        offset = first

        channel[channel < first] = 0
        channel[channel > last] = 255
        channel[(channel >= first) & (channel <= last)] = channel[(channel >= first) & (channel <= last)] * scale - offset
        
        final_image = cv.merge([chans[0], chans[1], chans[2]])
    
    return final_image