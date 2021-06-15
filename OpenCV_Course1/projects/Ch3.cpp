#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;

/////////////// Basic Functions //////////////////////

void main() {

	string path = "Resources/test.jpg";
	Mat img = imread(path);
	Mat ImgResize, imgCrop;

	//resize
	resize(img, ImgResize, Size(), 0.5, 0.5);

	Rect roi(300, 100, 100, 200);
	imgCrop = img(roi);

	imshow("image", img);
	imshow("Image resize", img);
	imshow("Image Crop", imgCrop);
	waitKey(0);
}