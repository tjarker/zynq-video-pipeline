import cv2 as cv
import sys
import numpy as np

def contrast_enh(img, p):
    chans = cv.split(img)
    for channel in chans:
        hist = cv.calcHist([channel], [0], None, [256], [0, 256])
        threshold = max(hist)*p
        
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

def image_sharp(image):
    kernel = np.array([[0, -1, 0], [-1, 5, -1], [0, -1, 0]])

    # Apply the filter matrix to the image
    sharpened = cv.filter2D(image, -1, kernel)
    
    return sharpened


if __name__ == "__main__":
    imm = cv.imread(sys.argv[1])
    out = image_sharp(contrast_enh(imm, 0.08))
    cv.imwrite(sys.argv[2], out)

