#include <opencv2/core/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>

#include <math.h>

#include <vector>
#include <iostream>
#include <string>

using namespace cv;
using namespace std;
vector<uint> whiteDotsVector(const Mat img);
double rootMeanSquareDeviation(const vector<uint> autoWhiteDots,const vector<uint> manualWhiteDots);

auto main() -> int{
	Mat firstImage, secondImage, manualRVE,autoRVE;
	vector<uint> whiteDotsManualRVE,whiteDotsAutoRVE;
	string nameFirstImage, nameSecondImage;
	cout << "Enter the name of first image" <<std::endl;
	cin >> nameFirstImage;
	cout << "Enter the name of second image" <<std::endl;
	cin >> nameSecondImage;
	firstImage=imread(/*nameFirstImage.c_str()*/"a.png", IMREAD_COLOR);
	secondImage=imread(/*nameSecondImage.c_str()*/"c.png",IMREAD_COLOR);
	//absdiff(firstImage, secondImage,manualRVE);
	manualRVE = firstImage - secondImage;
	namedWindow( "Main window", CV_WINDOW_KEEPRATIO );
	imshow("Main window", manualRVE);
	whiteDotsManualRVE=whiteDotsVector(manualRVE);
	//whiteDotsAutoRVE=whiteDotsVector(autoRVE);

	for (auto i=0;i<firstImage.rows;i++)
		cout<< whiteDotsManualRVE.at(i) <<endl;

	rootMeanSquareDeviation(whiteDotsManualRVE,whiteDotsManualRVE);
	waitKey(0);
}

double rootMeanSquareDeviation(const vector<uint> autoWhiteDots,const vector<uint> manualWhiteDots){
	uint vectorSize = autoWhiteDots.size();
	cout<<"i"<<vectorSize<<endl;
	double sum=0;
	double result=0;
	/* RMSD COMPUTATION*/
	/*x= root square of 1/n sum 1 until n (pointA-pointB) */
	for (uint i = 0;i<vectorSize;i++){
		//sum = sum + static_cast<double>(autoWhiteDots.at(i));
		sum=sum+pow(static_cast<double>(autoWhiteDots.at(i))-static_cast<double>(manualWhiteDots.at(i)),2);
	}
	sum=sum*1/vectorSize;
	result=sqrt(sum);
	return result;
}

vector<uint> whiteDotsVector(const Mat img){
	Mat convertedImg;
	vector<uint> whiteDotsArray;
	cvtColor(img,convertedImg,CV_BGR2GRAY);
	namedWindow( "test window", CV_WINDOW_KEEPRATIO );
	imshow("test window",convertedImg);
	for (auto i=0;i<img.rows;i++)
		for (auto j=0;j<img.cols;j++){
			if (convertedImg.at<uchar>(i,j)!=0){
				whiteDotsArray.push_back(j);
				break;
			}
		}
	return whiteDotsArray;
}
