//#include "stdafx.h"
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>

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

// ==[namespace]==
using namespace std;
using namespace cv;

// ================
//       onMouse
// ================
string ComputerUserName = "Maste";
vector<int> xValues;
vector<int> yValues;

void onMouse(int evt, int x, int y, int flags, void* param) {
	if (evt == CV_EVENT_LBUTTONDOWN) {
		std::vector<cv::Point>* ptPtr = (std::vector<cv::Point>*)param;
		ptPtr->push_back(cv::Point(x, y));
	}
}
// ================
//     MouseEvent
// ================
string ParkingLotName() {
	xValues.clear();
	yValues.clear();
	string i;
 cout << "*********************************" << endl;
 cout << "     Mapping New Parkinglot      " << endl; 
 cout << "*********************************" << endl;
cout << "[ Please note ]" << endl;
cout <<"You must have a monitor plugged into this raspberr pi" << endl;
cout <<"in order to use this program." << endl;
cout << "You must also have Vision Parking installed on this raspberry pi" << endl;
cout << "and have executed it at least once to obtain an image titled: latest.png " << endl;
cout << "This image is found in /home/pi/projects/VisualPark/images/latest.png" << endl;
cout << endl;
cout << endl; 
cout << "You may press Q to quit at any time. This will write the dataset." << endl;
cout << endl; 
cout <<"******************************************************************"<< endl;
cout << endl;  
	cout << "Please type the name of the lot: " << endl;
	cout << "Parkinglot Name: ";
	cin >> i;
	cout << endl;
	return i;
}

void mouseEvent(int event, int x, int y, int flags, void* param) {
	IplImage* img = (IplImage*)param;

	if (event == CV_EVENT_LBUTTONDOWN) {

		printf("%d %d\n",
			x, y);
		xValues.push_back(x);
		yValues.push_back(y);
	}//if
}//mousevent

 // ================
 //       MAIN
 // ================

int main() {
	//int x, y;
	string nameOfParkingLot = ParkingLotName();
	const char* ParkinglotToMapFile = string("/home/pi/projects/VisualPark/images/latest.png").c_str();
	IplImage *img = cvLoadImage(ParkinglotToMapFile, 1); //load in parkinglot you wish to map

	Mat howtoVector = imread("/home/pi/projects/MapLot/images/howtomap.png", 1);

	cvNamedWindow("My Window", 1);
	cvNamedWindow("How To Map Vector Coordinates", 1);
	imshow("How To Map Vector Coordinates", howtoVector);

	cvSetMouseCallback("My Window", mouseEvent, &img);
	cvShowImage("My Window", img);

	cvWaitKey(0);

	cout << "Writing text file..." << endl;
	ofstream a_file;
	int currentSpot = 1;
	a_file.open("/home/pi/projects/VisualPark/DataSets/" + nameOfParkingLot + ".txt");

	for (int i = 0; i < xValues.size(); i++) {
		if (i == 0) {
			a_file << currentSpot << " ";
			currentSpot++;
		}

		if (i % 4 == 0 && i != 0) {
			a_file << currentSpot << " ";
			currentSpot++;
		}
		a_file << xValues[i] << " " << yValues[i] << " ";
	}

	cout << "Text file complete." << endl;
	a_file.close();
	return 0;
}
