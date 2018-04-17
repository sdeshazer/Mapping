#include "stdafx.h"
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
	cout << "Examples: " << endl;
	cout << "This business has multiple parking lots so they labeled them as so: " << endl;
	cout << "<Insert Business Name Here> Parking Lot 1" << endl;
	cout << "<Insert Business Name Here> Parking Lot 2" << endl;
	cout << "This business only had one parking lot so they labeled it as so: " << endl;
	cout << "<Insert Business Name Here> Parking Lot" << endl;
	cout << "Please type the Id of the lot: " << endl;
	cout << "ParkingLotID: ";
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
	const char* ParkinglotToMapFile = string("C:\\Users\\" + ComputerUserName + "\\Pictures\\apptest\\hsbmapping.png").c_str();
	IplImage *img = cvLoadImage(ParkinglotToMapFile, 1); //load in parkinglot you wish to map

	Mat howtoVector = imread("C:\\Users\\" + ComputerUserName + "\\Music\\howtomap.png", 0);

	cvNamedWindow("My Window", 1);
	cvNamedWindow("How To Map Vector Coordinates", 1);
	imshow("How To Map Vector Coordinates", howtoVector);

	cvSetMouseCallback("My Window", mouseEvent, &img);
	cvShowImage("My Window", img);

	cvWaitKey(0);

	cout << "Writing text file..." << endl;
	ofstream a_file;
	int currentSpot = 1;
	a_file.open("C:\\Users\\" + ComputerUserName + "\\Music\\" + nameOfParkingLot + ".txt");

	for (int i = 0; i < xValues.size(); i++) {
		if (i == 0) {
			a_file << "Parking Spot" << currentSpot << endl;
			currentSpot++;
		}

		if (i % 4 == 0 && i != 0) {
			a_file << "Parking Spot" << currentSpot << endl;
			currentSpot++;
		}
		a_file << xValues[i] << " " << yValues[i] << endl;
	}

	cout << "Text file complete." << endl;
	a_file.close();
	return 0;
}