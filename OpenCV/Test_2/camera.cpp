#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <vector>

using namespace cv;
using namespace std;

Mat back;
Mat gray;

Mat detect(Mat &frame)
{
    vector<Rect> post;
    back = frame;
    CascadeClassifier faceCascade("./haarcascades/haarcascade_frontalface_default.xml");
    cvtColor(frame, gray, COLOR_BGR2GRAY);
    faceCascade.detectMultiScale(gray, post, 1.3, 5);
    for(auto it: post) {
        rectangle(back, it, Scalar(255, 0, 0), 2);
    }
    return back;
}

int main(void)  
{  
    VideoCapture camera(0);
    Mat frame;
    namedWindow("Camera");
    if(!camera.isOpened()) {
        return -1;
    }
    while(1) {  
        camera.read(frame);
        imshow("Camera", frame);
         if(waitKey(20) >= 0)  
             break;
    }  
    return 0;
}   

