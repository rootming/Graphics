#!/usr/bin/python
import cv2

clicked = False

def onMouse(event, x, y, flags, param):
    global clicked
    if event == cv2.EVENT_LBUTTONUP:
        clicked = True

cameraCapture = cv2.VideoCapture(0)
size = 640, 480
fps = 25
videoWriter = cv2.VideoWriter("output.avi", cv2.VideoWriter_fourcc('X', 'V', 'I', 'D'), 25, size)

cv2.namedWindow("Camera")
cv2.setMouseCallback("Camera", onMouse)
print "Press any to stop."
success, frame = cameraCapture.read()
while success and cv2.waitKey(1) == -1 and not clicked:
    cv2.imshow("Camera", frame)
    videoWriter.write(frame)
    success, frame = cameraCapture.read()

cv2.destroyAllWindows()
cameraCapture.release()
