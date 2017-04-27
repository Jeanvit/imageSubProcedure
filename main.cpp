#include <opencv2/core/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>

#include <vector>
#include <iostream>
#include <string>

using namespace cv;
using namespace std;


vector<uchar> whiteDotsVector(const Mat img){
	Mat convertedImg;
	vector<uchar> whiteDotsArray;
	cvtColor(img,convertedImg,CV_BGR2GRAY);
	namedWindow( "test window", CV_WINDOW_KEEPRATIO );
	imshow("test window",convertedImg);
	for (int i=0;i<img.rows;i++)
		for (int j=0;j<img.cols;j++){
			if (convertedImg.at<uchar>(i,j)!=0){
				whiteDotsArray.push_back(j);
			}
		}
	return whiteDotsArray;
}

auto main() -> int{
	Mat firstImage, secondImage, manualRVE;
	string nameFirstImage, nameSecondImage;
	cout << "Enter the name of first image" <<std::endl;
	cin >> nameFirstImage;
	cout << "Enter the name of second image" <<std::endl;
	cin >> nameSecondImage;
	firstImage=imread(nameFirstImage.c_str(), IMREAD_COLOR);
	secondImage=imread(nameSecondImage,IMREAD_COLOR);
	//absdiff(firstImage, secondImage,manualRVE);
	manualRVE = firstImage - secondImage;
	namedWindow( "Main window", CV_WINDOW_KEEPRATIO );
	imshow("Main window", manualRVE);
	whiteDotsVector(manualRVE);
	waitKey(0);
}
