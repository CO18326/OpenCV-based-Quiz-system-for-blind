// hello.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
/*#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
using namespace cv;
using namespace std;
void callback(int eve, int x, int y, int flags, void *user) {
	if (flags == (EVENT_FLAG_CTRLKEY+EVENT_FLAG_LBUTTON)) {
		cout << x << y;
	}
}
int main()
{
	VideoCapture video(0);
	namedWindow("jai shree ram");
	int bright;
	int angle;
	createTrackbar("bright", "jai shree ram", &bright,100);
	createTrackbar("rotation", "jai shree ram", &angle, 360);
	setMouseCallback("jai shree ram", callback, NULL);
	Mat im;
	//namedWindow("kala");
	while (true) {
		video.read(im);
		Mat il;
		im.convertTo(il, -1, 1, bright );
		int col = il.cols/ 2;
		int row = il.rows/ 2;
		Mat rotat = getRotationMatrix2D(Point(row, col), angle-180, 1);
		warpAffine(il, il, rotat, il.size());
		imshow("jai shree ram", il);
		if (waitKey(10) == 27) {
			break;
		}
	}
	destroyAllWindows();
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
*/