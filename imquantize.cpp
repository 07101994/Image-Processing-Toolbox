//Name : Tushar Koshti
/*function imquantize
* 'inputImage' is the input image.
* 'levels' is an array of threholds
* 'quantizedImage' is the returned image
*  with quantized levels.
*/


#include <opencv2/opencv.hpp>
#include <iostream> //input output header file
#include "gui.hpp" //file which contains threshold function


using namespace cv;


Mat imquantize(Mat inputImage, vector<vector<int> > levels)
{
	//initialise output label matrix
	Mat quantizedImage(inputImage.size(), inputImage.type(), Scalar::all(1));

	//Apply labels to the pixels according to the thresholds
	for (int i = 0; i < inputImage.cols; i++)
	{
		for (int j = 0; j < inputImage.rows; j++)
		{
			// Check if image is grayscale or BGR
			if (levels.size() == 1)
			{
				for (int k = 0; k < levels[0].size(); k++)
				{
					// if pixel < lowest threshold , then assign 0
					if (inputImage.at<uchar>(j, i) <= levels[0][0])
					{
						quantizedImage.at<uchar>(j, i) = 0;
					}

					// if pixel > highest threshold , then assign 255
					else if (inputImage.at<uchar>(j, i) >= levels[0][levels[0].size() - 1])
					{
						quantizedImage.at<uchar>(j, i) = 255;
					}

					// Check the level borders for pixel and assign the corresponding
					// upper bound quanta to the pixel
					else
					{
						if (levels[0][k] < inputImage.at<uchar>(j, i) && inputImage.at<uchar>(j, i) <= levels[0][k + 1])
						{
							quantizedImage.at<uchar>(j, i) = (k + 1) * 255 / (levels[0].size());
						}
					}
				}
			}

			else
			{
				Vec3b pair = inputImage.at<Vec3b>(j, i);

				// Processing the Blue Channel
				for (int k = 0; k < levels[0].size(); k++)
				{
					if (pair.val[0] <= levels[0][0])
					{
						quantizedImage.at<Vec3b>(j, i)[0] = 0;
					}
					else if (pair.val[0] >= levels[0][levels.size() - 1])
					{
						quantizedImage.at<Vec3b>(j, i)[0] = 255;
					}
					else
					{
						if (levels[0][k] < pair.val[0] && pair.val[0] <= levels[0][k + 1])
						{
							quantizedImage.at<Vec3b>(j, i)[0] = (k + 1) * 255 / (levels[0].size());
						}
					}
				}

				// Processing the Green Channel
				for (int k = 0; k < levels[1].size(); k++)
				{
					if (pair.val[1] <= levels[1][0])
					{
						quantizedImage.at<Vec3b>(j, i)[1] = 0;
					}
					else if (pair.val[1] >= levels[1][levels.size() - 1])
					{
						quantizedImage.at<Vec3b>(j, i)[1] = 255;
					}
					else
					{
						if (levels[1][k] < pair.val[1] && pair.val[1] <= levels[1][k + 1])
						{
							quantizedImage.at<Vec3b>(j, i)[1] = (k + 1) * 255 / (levels[1].size());
						}
					}
				}

				// Processing the Red Channel
				for (int k = 0; k < levels[2].size(); k++)
				{
					if (pair.val[2] <= levels[2][0])
					{
						quantizedImage.at<Vec3b>(j, i)[2] = 0;
					}
					else if (pair.val[2] >= levels[2][levels.size() - 1])
					{
						quantizedImage.at<Vec3b>(j, i)[2] = 255;
					}
					else
					{
						if (levels[2][k] < pair.val[2] && pair.val[2] <= levels[2][k + 1])
						{
							quantizedImage.at<Vec3b>(j, i)[2] = (k + 1) * 255 / (levels[2].size());
						}
					}
				}
			}
		}
	}


int main() {
	VideoCapture cam(0); // Object to capture image from video camera
	Mat image, render; //image to store captured image and render to store threshold image
	vector<vector<int> > levels; // 'levels' is an array of threholds
	levels[0][0] = 1;
	levels[0][1] = 1;
	levels[1][0] = 1;
	levels[1][1] = 1;
	//! [load]
	string imageName("sample.jpg"); // by default
	//! [mat]

	//! [imread]
	image = imread(imageName.c_str(), IMREAD_COLOR); // Read the file

	render = imquantize(image, levels) //threshold function to multithresh the image and store into render object
	imshow("Color", image); // show the original image
	imshow("IMQuantized Image", render); // show the threshold image
	//! [wait]
	waitKey(0); // Wait for a keystroke in the window
	//! [wait]
	return 0;
}
