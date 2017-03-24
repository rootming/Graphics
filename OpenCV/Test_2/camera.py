#!/usr/bin/python

import cv2
import time

filename = 'recode_' + time.strftime("%Y-%m-%d %H:%M:%S", time.localtime()) + ".avi"
clicked = False
path = ''

def onMouse(event, x, y, flags, param):
    global clicked
    if event == cv2.EVENT_LBUTTONUP:
        clicked = True


def detect(source):
    face_cascade = cv2.CascadeClassifier("./haarcascades/haarcascade_frontalface_default.xml")
    image = source 
    gray = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)
    faces = face_cascade.detectMultiScale(gray, 1.3, 5)
    # print len(faces)

    for(x, y, w, h) in faces:
        image = cv2.rectangle(image, (x, y), (x + w, y + h), (255, 0, 0), 2) 

    if len(faces) > 0:
        cv2.imwrite(path + 'image_' + time.strftime("%Y-%m-%d %H:%M:%S", time.localtime()) + ".jpg", image)
        print 'Save file.'
    return image

VideoCapture = cv2.VideoCapture(0)
success, frame = VideoCapture.read()
size = 640, 480
fps = 20
videoWriter = cv2.VideoWriter(path + filename, cv2.VideoWriter_fourcc('M', 'J', 'P', 'G'), fps, size)

# cv2.namedWindow("Camera")
# cv2.setMouseCallback("Camera", onMouse)
success, frame = VideoCapture.read()
while success:
    temp = detect(frame)
    # detect image
    videoWriter.write(temp)
    cv2.waitKey(30)
    # save result
    # cv2.imshow("Camera", frame)
    # show result
    success, frame = VideoCapture.read()

