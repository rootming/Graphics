#!/usr/bin/python

import cv2

clicked = False

def onMouse(event, x, y, flags, param):
    global clicked
    if event == cv2.EVENT_LBUTTONUP:
        clicked = True


def detect(source):
    face_cascade = cv2.CascadeClassifier("./haarcascades/haarcascade_frontalface_default.xml")
    image = source 
    gray = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)
    faces = face_cascade.detectMultiScale(gray, 1.3, 5)
    for(x, y, w, h) in faces:
        image = cv2.rectangle(image, (x, y), (x + w, y + h), (255, 0, 0), 2) 
    return image

VideoCapture = cv2.VideoCapture(0)
success, frame = VideoCapture.read()
size = 640, 480
fps = 25
videoWriter = cv2.VideoWriter("output.avi", cv2.VideoWriter_fourcc('X', 'V', 'I', 'D'), fps, size)

cv2.namedWindow("Camera")
cv2.setMouseCallback("Camera", onMouse)
success, frame = VideoCapture.read()
while success and cv2.waitKey(1) == -1 and not clicked:
    temp = detect(frame)
    # detect image
    videoWriter.write(temp)
    # save result
    cv2.imshow("Camera", temp)
    # show result
    success, frame = VideoCapture.read()

