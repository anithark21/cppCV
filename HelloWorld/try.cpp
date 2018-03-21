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
	faceDetector.load("C:\\opencv\\build\\etc\\haarcascades\\haarcascade_frontalface_alt.xml");
	for(int i=1;i<8;i++){
	string j;
	stringstream convert; 
	convert << i;

	j = convert.str();

	Mat image = cv::imread("C:\\FaceDetection\\Inputs\\input"+j+".jpg");
	vector<Rect> faceDetections;
	Rect rect;
	std::vector<Rect> faces;
	Mat frame_gray;
	cvtColor(image, frame_gray, COLOR_BGR2GRAY);   // Convert to gray
	equalizeHist(frame_gray, frame_gray);
	try {
		faceDetector.detectMultiScale(frame_gray, faces,
			1.1, 3,
			0 | CASCADE_SCALE_IMAGE, Size(30, 30));
	}
	catch (Exception e) {
		cout << "Error: e";
	}
	for (size_t i = 0; i < faces.size(); i++)
	{
		rect = faces[i];

		cv::rectangle(image, rect, cv::Scalar(255, 0, 0), 3, 8, 0);
	}
	cv::imwrite("C:\\FaceDetection\\Outputs\\Output"+j+".jpg", image);
	}
}
