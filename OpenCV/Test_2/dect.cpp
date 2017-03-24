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
    vector<Rect> facePost;
    vector<Rect> eyePost;
    back = frame;
    CascadeClassifier faceCascade("./haarcascades/haarcascade_frontalface_default.xml");
    CascadeClassifier eyeCascade("./haarcascades/haarcascade_eye.xml");
    cvtColor(frame, gray, COLOR_BGR2GRAY);
    faceCascade.detectMultiScale(gray, facePost, 2.3, 5.0);
    if(facePost.size() > 0) {
        cout << "Found face!!! Count: " << facePost.size() << endl;
        eyeCascade.detectMultiScale(gray, eyePost, 1.3, 2.0);
        for(auto it: facePost) {
            rectangle(back, it, Scalar(255, 0, 0), 2);
        }

        for(auto it: eyePost) {
            rectangle(back, it, Scalar(255, 255, 0), 2);
        }
    }
    return back;
}

int main(void)  
{  
    VideoCapture camera(0);
    VideoWriter writer("video.avi", VideoWriter::fourcc('M','J','P','G'), 30, Size(640, 480));
    Mat frame;
    Mat result;
    namedWindow("Camera");
    if(!camera.isOpened()) {
        return -1;
    }
    while(1) {  
        camera.read(frame);
        result = detect(frame);
        imshow("Camera", result);
        writer << result;
        if(waitKey(20) >= 0)  
            break;
    }  
    return 0;
}   

