#!/usr/bin/python

import cv2

clicked = False

def onMouse(event, x, y, flags, param):
    global clicked
    if event == cv2.EVENT_LBUTTONUP:
        clicked = True


def detect(filename):
    face_cascade = cv2.CascadeClassifier("./haarcascades/haarcascade_frontalface_default.xml")
    image = cv2.imread(filename)
    gray = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)
    faces = face_cascade.detectMultiScale(gray, 1.3, 5)
    for(x, y, w, h) in faces:
        image = cv2.rectangle(image, (x, y), (x + w, y + h), (255, 0, 0), 2) 
    return image

temp = detect("lena.jpg")
cv2.imshow("Detect", temp)
cv2.imwrite("output.jpg",  temp)
cv2.waitKey()
cv2.destroyAllWindows()
