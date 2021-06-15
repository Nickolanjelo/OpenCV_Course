#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
//#include<opencv2/objdetect.hpp>
#include <iostream>

using namespace cv;
using namespace std;


Mat img;
vector<vector<int>>newPoints;

/////////////// Project 1 //////////////////////
vector<vector<int>> myColors{{0,0,0,179,234,255}};


void  getContours(Mat imgDil) {

	vector<vector<Point>> contours;
	vector<Vec4i>hierarchy;

	findContours(imgDil, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

	vector<vector<Point>> conPoly(contours.size());
	vector<Rect>boundRect(contours.size());

	Point myPoint(0, 0);
	
	for (int i = 0; i < contours.size(); i++)
	{
		int area = contourArea(contours[i]);
		cout << area << endl;

		string objectType;

		if (area > 1000)

		{
			float peri = arcLength(contours[i], true);
			approxPolyDP(contours[i], conPoly[i], 0.02 * peri, true);
			
			cout << conPoly[i].size() << endl;
			boundRect[i] = boundingRect(conPoly[i]);
			myPoint.x = boundRect[i].x + boundRect[i].width/2;
			myPoint.y = boundRect[i].y;


			drawContours(img, conPoly, i, Scalar(255, 0, 255), 2);
			rectangle(img, boundRect[i].tl(), boundRect[i].br(), Scalar(0, 255, 0), 5);

		}
	}



}



void findColour(Mat img)
{
	Mat imgHSV;
	cvtColor(img, imgHSV, COLOR_BGR2HSV);
	
	for (int i = 0; i < myColors.size(); i++)
	{

		Scalar lower(myColors[i][0], myColors[i][1], myColors[i][2]);
		Scalar upper(myColors[i][3], myColors[i][4], myColors[i][5]);
		Mat mask;
		inRange(imgHSV, lower, upper, mask);
		//imshow(to_string(i), mask);
		getContours(mask);
		Point myPoint = getContours(mask);
		if (myPoint.x != 0 && myPoint != 0) {
			newPoints.push_back({ myPoint.x,myPoint.y,i });

		}

	}
}

void drawOnCanvas()

void main() {

	VideoCapture cap(0);

	while (true) {
		cap.read(img);
		findColour(img);

		imshow("Image",img);
		waitKey(1);

	}

	
}