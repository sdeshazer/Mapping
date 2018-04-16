//opencv2:
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/features2d.hpp>
#include <opencv2/objdetect.hpp>

//opencv:
#include <opencv/highgui.h>
#include <opencv/cv.h>
//====================

#include "stdafx.h"
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>

// ==[namespace]==
using namespace std;
using namespace cv;

// ================
//       onMouse
// ================
int Id;
void onMouse(int evt, int x, int y, int flags, void* param) {
	if (evt == CV_EVENT_LBUTTONDOWN) {
		std::vector<cv::Point>* ptPtr = (std::vector<cv::Point>*)param;
		ptPtr->push_back(cv::Point(x, y));
	}
}
// ================
//     MouseEvent
// ================
void id(int i) {

	cout << "ID: ";
	cin >> i; 
	cout << " "; 

}

void mouseEvent(int event, int x, int y, int flags, void* param){
	IplImage* img = (IplImage*)param;

	if (event == CV_EVENT_LBUTTONDOWN){
	
		printf("%d %d\n",
			x, y);
		
	}//if
	ifstream f("C:\\Users\\Arg0s2\\Music\\newdata.txt");
	ofstream a_file;
	if (f.bad()) {
		a_file.open("C:\\Users\\Arg0s2\\Music\\newdata.txt");
	}
	a_file << x << " " << y << endl;
}//mousevent

// ================
//       MAIN
// ================

int main(){
	//int x, y;
	id(Id);
	
	IplImage *img = cvLoadImage("C:\\Users\\Arg0s2\\Pictures\\apptest\\hsbmapping.png", 1); //load in parkinglot you wish to map

	Mat howtoVector = imread("C:\\Users\\Arg0s2\\Music\\howtomap.png", 0); 

	cvNamedWindow("My Window", 1);
	cvNamedWindow("How To Map Vector Coordinates", 1);
	imshow("How To Map Vector Coordinates", howtoVector);
	
	cvSetMouseCallback("My Window", mouseEvent, &img);
	cvShowImage("My Window", img);

	cvWaitKey(0);
	
	cout << "writing txt file..." << endl;
	//ofstream outFile("", ios::out);
	cout << "text file complete." << endl;

	ifstream b_file("C:\\Users\\Arg0s2\\Music\\newdata.txt"); 

	return 0;

}