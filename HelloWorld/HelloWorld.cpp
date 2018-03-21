/*
// Include header files
#include"stdafx.h"
#include<opencv\highgui.h>
#include<opencv\cv.h>
#include<opencv\cv.hpp>
#include<opencv2\highgui.hpp>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#include <float.h>
#include <limits.h>
#include <time.h>
#include <ctype.h>
#include<opencv2\objdetect.hpp>
#include<opencv2\imgcodecs\imgcodecs.hpp>
#include <iostream>
#include <stdio.h>
#include<opencv2\imgproc\imgproc.hpp>
#include<opencv2\core\core.hpp>

using namespace std;
using namespace cv;

// Function for Face Detection
void detectAndDraw(Mat& img, CascadeClassifier& cascade,
	CascadeClassifier& nestedCascade, double scale);
string cascadeName, nestedCascadeName;

int main(int argc, const char** argv)
{
	// VideoCapture class for playing video for which faces to be detected
	VideoCapture capture;
	Mat frame, image;

	// PreDefined trained XML classifiers with facial features
	CascadeClassifier cascade, nestedCascade;
	double scale = 1;

	// Load classifiers from "opencv/data/haarcascades" directory 
	nestedCascade.load("../../haarcascade_eye_tree_eyeglasses.xml");

	// Change path before execution 
	cascade.load("../../haarcascade_frontalcatface.xml");

	// Start Video..1) 0 for WebCam 2) "Path to Video" for a Local Video
	capture.open(0);
	if (capture.isOpened())
	{
		// Capture frames from video and detect faces
		cout << "Face Detection Started...." << endl;
		while (1)
		{
			capture >> frame;
			if (frame.empty())
				break;
			Mat frame1 = frame.clone();
			detectAndDraw(frame1, cascade, nestedCascade, scale);
			char c = (char)waitKey(10);

			// Press q to exit from window
			if (c == 27 || c == 'q' || c == 'Q')
				break;
		}
	}
	else
		cout << "Could not Open Camera";
	return 0;
}

void detectAndDraw(Mat& img, CascadeClassifier& cascade,
	CascadeClassifier& nestedCascade,
	double scale)
{
	vector<Rect> faces, faces2;
	Mat gray, smallImg;

	cvtColor(img, gray, COLOR_BGR2GRAY); // Convert to Gray Scale
	double fx = 1 / scale;

	// Resize the Grayscale Image 
	resize(gray, smallImg, Size(), fx, fx, INTER_LINEAR);
	equalizeHist(smallImg, smallImg);

	// Draw circles around the faces
	for (size_t i = 0; i < faces.size(); i++)
	{
		Rect r = faces[i];
		Mat smallImgROI;
		vector<Rect> nestedObjects;
		Point center;
		Scalar color = Scalar(255, 0, 0); // Color for Drawing tool
		int radius;

		double aspect_ratio = (double)r.width / r.height;
		if (0.75 < aspect_ratio && aspect_ratio < 1.3)
		{
			center.x = cvRound((r.x + r.width*0.5)*scale);
			center.y = cvRound((r.y + r.height*0.5)*scale);
			radius = cvRound((r.width + r.height)*0.25*scale);
			circle(img, center, radius, color, 3, 8, 0);
		}
		else
			rectangle(img, cvPoint(cvRound(r.x*scale), cvRound(r.y*scale)),
				cvPoint(cvRound((r.x + r.width - 1)*scale),
					cvRound((r.y + r.height - 1)*scale)), color, 3, 8, 0);
		if (nestedCascade.empty())
			continue;
		smallImgROI = smallImg(r);

		// Detection of eyes int the input image
		nestedCascade.detectMultiScale(smallImgROI, nestedObjects, 1.1, 2,
			0 | CASCADE_SCALE_IMAGE, Size(30, 30));

		// Draw circles around eyes
		for (size_t j = 0; j < nestedObjects.size(); j++)
		{
			Rect nr = nestedObjects[j];
			center.x = cvRound((r.x + nr.x + nr.width*0.5)*scale);
			center.y = cvRound((r.y + nr.y + nr.height*0.5)*scale);
			radius = cvRound((nr.width + nr.height)*0.25*scale);
			circle(img, center, radius, color, 3, 8, 0);
		}
	}

	// Show Processed Image with detected faces
	imshow("Face Detection", img);
}*/
// Include header files
#include"stdafx.h"
#include<opencv\highgui.h>
#include<opencv\cv.h>
#include<opencv\cv.hpp>
#include<opencv2\highgui.hpp>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#include <float.h>
#include <limits.h>
#include <time.h>
#include <ctype.h>
#include<opencv2\objdetect.hpp>
#include<opencv2\imgcodecs\imgcodecs.hpp>
#include <iostream>
#include <stdio.h>
#include<opencv2\imgproc\imgproc.hpp>
#include<opencv2\core\core.hpp>
using namespace std;
using namespace cv;
int main(int argc, const char** argv)
{
	CascadeClassifier faceDetector;
	faceDetector.load("D:\\Users\\H282584\\Downloads\\opencv\\build\\etc\\haarcascades\\haarcascade_frontalface_alt.xml");
	Mat image = imread("C:\\FaceDetection\\Inputs\\input1.jpg");
	vector<Rect> faceDetections;
	faceDetector.detectMultiScale(image, faceDetections);
	Rect arr[15];
	std::copy(faceDetections.begin(), faceDetections.end(), arr);
	Rect rect;
	for (int i = 0; i <3; i++)
	{
		rect = arr[i];
		Point a = (Point)(rect.x, rect.y);
		Point b = (Point)(rect.x + rect.width, rect.y + rect.height);
		Scalar s = (255, 0, 0);
		rectangle(image, a, b, s, 3);
	}
	imwrite("C:\\FaceDetection\\Outputs\\Output1.jpg", image);
}