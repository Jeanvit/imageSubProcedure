#include <opencv2/core/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <math.h>

#include <math.h>

#include <vector>
#include <iostream>
#include <string>

using namespace cv;
using namespace std;

vector<uint> vectorMean (const vector<uint> a,const vector<uint>b);
vector<uint> whiteDotsVector(const Mat img);
double rootMeanSquareDeviation(const vector<uint> autoWhiteDots,const vector<uint> manualWhiteDots);
void createOutput(vector<uint> source, uint numRows, uint numCols);

auto main() -> int{
	Mat firstImage, secondImage, manualRVE,autoRVE;
	vector<uint> whiteDotsManualRVE,whiteDotsAutoRVE;
	string nameFirstImage, nameSecondImage, nameGeneratedRVE;
	cout << "Enter the name of original image" <<std::endl;
	//cin >> nameFirstImage;
	cout << "Enter the name of the manually marked image" <<std::endl;
	//cin >> nameSecondImage;
	cout << "Enter the name of the RVE image" <<std::endl;
	//cin >> nameGeneratedRVE;
	firstImage=imread(/*nameFirstImage.c_str()*/"f.png", IMREAD_COLOR);
	secondImage=imread(/*nameSecondImage.c_str()*/"e.png",IMREAD_COLOR);
	autoRVE=imread(/*nameSecondImage.c_str()*/"g.png",IMREAD_COLOR);
	//absdiff(firstImage, secondImage,manualRVE);
	manualRVE = firstImage - secondImage;
	namedWindow( "Main window", CV_WINDOW_KEEPRATIO );
	imshow("Main window", manualRVE);
	whiteDotsManualRVE=whiteDotsVector(manualRVE);
	whiteDotsAutoRVE=whiteDotsVector(autoRVE);

	/*for (auto i=0;i<firstImage.rows;i++)
		cout<< whiteDotsManualRVE.at(i) <<endl;

	for (auto i=0;i<firstImage.rows;i++)
			cout<< whiteDotsAutoRVE.at(i) <<endl;
// TO DO
	//CORRECT WHITE DOTS AUTO RVE DATA TO A CORRECT FILE*/
	rootMeanSquareDeviation(whiteDotsManualRVE,whiteDotsAutoRVE);
	createOutput(whiteDotsManualRVE,firstImage.rows,firstImage.cols);
	waitKey(0);
}
void createOutput(vector<uint> source, uint numRows, uint numCols){
	Mat output;
	Mat::zeros(numRows, numCols , CV_8U);
	for (auto i=0;i<numRows;i++){
		//output.at<uchar>(i,source.at(i))=255;
	}
	vector<int> compression_params;
	compression_params.push_back(CV_IMWRITE_PNG_COMPRESSION);
	compression_params.push_back(9);

	imwrite("output.png", output, compression_params);
}

double rootMeanSquareDeviation(const vector<uint> autoWhiteDots,const vector<uint> manualWhiteDots){
	int vectorSize = autoWhiteDots.size();
	int manualVectorSize = manualWhiteDots.size();
	cout<<"Auto vector size: "<<vectorSize<<endl;
	cout<<"manual vector size: "<<manualVectorSize<<endl;

	double sum=0;
	double result=0;
	/* RMSD*/
	/*x= root square of 1/n sum 1 until n (pointA-pointB) */
	for (auto i = 0;i<vectorSize;i++){
		sum=sum+pow(static_cast<double>(autoWhiteDots.at(i))-static_cast<double>(manualWhiteDots.at(i)),2);

	}
	sum=sum/vectorSize;
	result=sqrt(sum);
	cout<<"result "<<result<<endl;
	return result;
}

vector<uint> vectorMean (const vector<uint> a,const vector<uint>b){
	vector<uint> mean;
	for (auto i=a.begin();i<a.end();i++){
		double value=floor((a.at(*i)-b.at(*i)/2));
		mean.push_back(static_cast<uint>(value/2));
	}
	return mean;
}

vector<uint> whiteDotsVector(const Mat img){
	Mat convertedImg;
	vector<uint> whiteDotsArray;
	cvtColor(img,convertedImg,CV_BGR2GRAY);
	namedWindow( "test window", CV_WINDOW_KEEPRATIO );
	imshow("test window",convertedImg);
	for (auto i=0;i<img.rows;i++){
		whiteDotsArray.push_back(0);
		for (auto j=0;j<img.cols;j++){				/* This guarantees that the whitedots vector will have the same size as the image */
			if (convertedImg.at<uchar>(i,j)!=0){	/* even if there's no enough lines with white dots */
				whiteDotsArray.at(whiteDotsArray.size()-1)=j;
				break;
			}
		}
	}
	return whiteDotsArray;
}
