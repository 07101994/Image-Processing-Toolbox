//Name : Tushar Koshti
//Function : threshold(Mat object) which returns Mat as output
//Input argument: Mat
//Output : Mat
//For Example: Mat renderedImage = threshold(image);

#include <opencv2/opencv.hpp>
#include <iostream> //input output header file
#include "gui.hpp" //file which contains threshold function


using namespace cv;
int main() {
	VideoCapture cam(0); // Object to capture image from video camera
	Mat image, render; //image to store captured image and render to store threshold image
	ThreshOpts thresh; 

	//! [load]
	string imageName("sample.jpg"); // by default
	//! [mat]

	//! [imread]
	image = imread(imageName.c_str(), IMREAD_COLOR); // Read the file

	render = thresh.threshold(image); //threshold function to multithresh the image and store into render object
	imshow("Color", image); // show the original image
	imshow("Thresholded", render); // show the threshold image
	//! [wait]
	waitKey(0); // Wait for a keystroke in the window
	//! [wait]
	return 0;
}
