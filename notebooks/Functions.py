import cv2 as cv
import imutils
import sys
import numpy as np
import matplotlib.pyplot as plt
def contrast_enh(img, p):
    chans = cv.split(img)

    hists = [cv.calcHist([img], [i], None, [256], [0, 256]) for i in range(3)]

    threshold = max([max(hist) for hist in  hists]) * p

    for i in range(3):
        channel = chans[i]
        hist = hists[i]
        
        for first in range(hist.size):
            if hist[first] > threshold:
                break;

        for last in range(255,-1,-1):
            if hist[last] > threshold:
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