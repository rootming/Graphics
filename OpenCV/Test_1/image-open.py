#!/usr/bin/python

import cv2
#import numpy
#import time
#
#class CaptureManger(object):
#    def __init__(self, capture, previewWindowManger = None, shouldMirrorPreview = False):
#        self.previewWindowManger = previewWindowManger
#        self.shouldMirrorPreview = shouldMirrorPreview
#        self._capture = capture
#        self._channel = channel
#        self._enteredFrame = False
#


img = cv2.imread("test.png")
print img.shape
cv2.imshow("Test image", img)
cv2.waitKey()
cv2.destroyAllWindows()
