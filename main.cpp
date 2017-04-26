#include <opencv2/core/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <iostream>
#include <string>

using namespace cv;
using namespace std;


auto main() -> int{
	Mat firstImage, secondImage, manualRVE;
	string nameFirstImage, nameSecondImage;
	cout << "Enter the name of first image" <<std::endl;
	cin >> nameFirstImage;
	cout << "Enter the name of second image" <<std::endl;
	cin >> nameSecondImage;
	firstImage=imread(nameFirstImage.c_str(), IMREAD_COLOR);
	secondImage=imread(nameSecondImage,IMREAD_COLOR);
	absdiff(firstImage, secondImage,manualRVE);

	namedWindow( "Main window", CV_WINDOW_KEEPRATIO );
	imshow("Main window", manualRVE);
	waitKey(0);
}
