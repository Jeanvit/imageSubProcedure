#include <iostream>
#include <string>
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;


auto main() -> int {
	Mat firstImage, secondImage, manualRVE;
	string nameFirstImage, nameSecondImage;
	cout << "Enter the name of first image" <<std::endl;
	cin >> nameFirstImage;
	cout << "Enter the name of second image" <<std::endl;
	cin >> nameSecondImage;
	imread(nameFirstImage, CV_LOAD_IMAGE_GRAYSCALE);
	imread(nameSecondImage,CV_LOAD_IMAGE_GRAYSCALE);
	manualRVE = firstImage - secondImage;
	namedWindow( "Main window", CV_WINDOW_KEEPRATIO );
	imshow("Main window", manualRVE);
}
