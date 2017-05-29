#include <opencv2/core/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>

#include <math.h>
#include <vector>
#include <iostream>
#include <string>

/*******************************************************************************************/
using namespace cv;
using namespace std;
/*******************************************************************************************/
#define FILEEXTENSION 4 //number of chars after the filename

/*******************************************************************************************/
vector<uint> vectorMean (const vector<uint> a, const int size, const int rowSize);
vector<uint> whiteDotsVector(const Mat img);
double rootMeanSquareDeviation(const vector<uint> autoWhiteDots,const vector<uint> manualWhiteDots);
bool createOutput(vector<uint> source, uint numRows, uint numCols,const string fileName);
bool createSumOfInputs(vector<uint> source, uint numRows, uint numCols,const string fileName);
bool fileExists(const string filename);

/*******************************************************************************************/
auto main(int argc, char* argv[]) -> int{
	Mat firstImage, secondImage, manualRVE,autoRVE,additionalImage,additionalRVE;
	vector<uint> whiteDotsManualRVE,whiteDotsAutoRVE,whiteDotsAdditionalRVE, meanRVE, sumRVE;
	string nameFirstImage, nameSecondImage, nameGeneratedRVE, nameAdditionalImage,name;
	int totalImages=0;
	cout << "Enter the name of original image" <<std::endl;
	cin >> nameFirstImage;
	name=nameFirstImage.substr(0,nameFirstImage.size()-FILEEXTENSION);
	cout << "Enter the name of the manually marked image" <<std::endl;
	cin >> nameSecondImage;
	cout << "Enter the name of the RVE image" <<std::endl;
	cin >> nameGeneratedRVE;
	firstImage=imread(nameFirstImage.c_str(), IMREAD_GRAYSCALE);
	secondImage=imread(nameSecondImage.c_str(),IMREAD_GRAYSCALE);
	autoRVE=imread(nameGeneratedRVE.c_str(),IMREAD_GRAYSCALE);
	absdiff(firstImage, secondImage,manualRVE);
	namedWindow( "Manual RVE", CV_WINDOW_KEEPRATIO );
	imshow("Manual RVE", manualRVE);
	whiteDotsManualRVE=whiteDotsVector(manualRVE);
	whiteDotsAutoRVE=whiteDotsVector(autoRVE);
	if (argc>1){

				totalImages = atoi(argv[1]);
				sumRVE.resize(whiteDotsAutoRVE.size()); // sumRVE size is equal to WhitedotsRVE
				fill(sumRVE.begin(), sumRVE.end(), 0); //  Starting sumRVE with zeros
				transform(sumRVE.begin(),sumRVE.end(), whiteDotsManualRVE.begin(),
												               sumRVE.begin(), std::plus<uint>());

				cout << "An additional file containing the mean of "<<totalImages<<" images will  be created"<<endl;
				for (auto i=0;i<totalImages;i++){
					fill(whiteDotsAdditionalRVE.begin(), whiteDotsAdditionalRVE.end(), 0);
					cout << "Enter the name of the image number "<< i+1 <<endl;
					cin >> nameAdditionalImage;
					additionalImage=imread(nameAdditionalImage.c_str(),IMREAD_GRAYSCALE);
					absdiff(firstImage, additionalImage,additionalRVE);//additionalRVE= firstImage - additionalImage ;

					whiteDotsAdditionalRVE=whiteDotsVector(additionalRVE);
					createSumOfInputs(whiteDotsAdditionalRVE,firstImage.rows,firstImage.cols,name+"sum.png");
					transform(sumRVE.begin(),sumRVE.end(), whiteDotsAdditionalRVE.begin(),
								               sumRVE.begin(), std::plus<uint>());

				}
				meanRVE=vectorMean(sumRVE,totalImages+1,whiteDotsAutoRVE.size());
				createOutput(meanRVE,firstImage.rows,firstImage.cols,name+"meanRVE.png");
				Mat show=imread("meanRVE.png",IMREAD_GRAYSCALE);
				//namedWindow( "Mean white dots image", CV_WINDOW_KEEPRATIO );
				//imshow("Mean white dots image",show);

	}

	rootMeanSquareDeviation(whiteDotsManualRVE,whiteDotsAutoRVE);
	createOutput(whiteDotsManualRVE,firstImage.rows,firstImage.cols, name+"output.png");
	createSumOfInputs(whiteDotsManualRVE,firstImage.rows,firstImage.cols,name+"sum.png");
	waitKey(0);
}

/*******************************************************************************************/
/* This function creates a png image called output.png using a vector containing the col's white dots positions */
bool createOutput(vector<uint> source, uint numRows, uint numCols,const string fileName){
	Mat output=	Mat::zeros(numRows, numCols , CV_8U);
	cout<<"printing output..."<<endl;
	for (uint i=0;i<numRows;i++){
		if (source.at(i)!=0){
			output.at<uchar>(i,source.at(i))=255;
		}
	}
	vector<int> compression_params;
	compression_params.push_back(CV_IMWRITE_PNG_COMPRESSION);
	compression_params.push_back(9);
	cout<<"Creating output image...";
	try {
		imwrite(fileName, output, compression_params);
	}
	catch (cv::Exception& ex) {
	    cout<<"Error! Exception converting image to PNG format:"<< ex.what();
	    return false;
	}
	cout<<fileName<<" successfully created."<<endl;
	return true;
}

/*******************************************************************************************/
/* This function compute the Root Mean Square Deviation (RMSD) of a couple of vectors */
double rootMeanSquareDeviation(const vector<uint> autoWhiteDots,const vector<uint> manualWhiteDots){
	int vectorSize = autoWhiteDots.size();

	double sum=0;
	double result=0;
	/* RMSD*/
	/*x= root square of 1/n sum 1 until n (pointA-pointB) */
	for (auto i = 0;i<vectorSize;i++){
		sum=sum+pow(static_cast<double>(autoWhiteDots.at(i))-static_cast<double>(manualWhiteDots.at(i)),2);

	}
	sum=sum/vectorSize;
	result=sqrt(sum);
	cout<<endl<<endl;
	cout<<"The RMSD value is: "<<result<<endl;
	return result;
}

/*******************************************************************************************/
/* This function returns the mean of two vectors */
vector<uint> vectorMean (const vector<uint> a, const int size,const int rowSize){
	vector<uint> mean;

	for (auto i=0;i<rowSize;i++){

		double value=(a.at(i))/size;
		mean.push_back(static_cast<uint>(value));
	}
	return mean;
}

/*******************************************************************************************/
/* This function returns a vector containing non-zero pixels, one per line and column ,*/
vector<uint> whiteDotsVector(const Mat convertedImg){
	vector<uint> whiteDotsArray;
	namedWindow( "White dots image", CV_WINDOW_KEEPRATIO );
	imshow("White dots image",convertedImg);
	for (auto i=0;i<convertedImg.rows;i++){
		whiteDotsArray.push_back(0);
		for (auto j=0;j<convertedImg.cols;j++){				/* This guarantees that the whitedots vector will have the same size as the image */
			if (convertedImg.at<uchar>(i,j)>0){	            /* even if there's no enough lines with white dots */
				whiteDotsArray.at(whiteDotsArray.size()-1)=j;
				//break;
			}
		}
	}
	return whiteDotsArray;
}
/*******************************************************************************************/
/* This function creates an output containing the sum of all RVEs */
bool createSumOfInputs(vector<uint> source, uint numRows, uint numCols, const string fileName){
	Mat sum;
	cout<<"printing the RVE sum..."<<endl;
	if (!fileExists(fileName)){
		sum=Mat::zeros(numRows, numCols , CV_8U);
	} else{
		sum=imread(fileName, IMREAD_GRAYSCALE);
	}

	for (uint i=0;i<numRows;i++){
		if (source.at(i)!=0){
			sum.at<uchar>(i,source.at(i))=255;
		}
	}
	vector<int> compression_params;
	compression_params.push_back(CV_IMWRITE_PNG_COMPRESSION);
	//compression_params.push_back(9);	cout<<"Creating output image...";
	try {
		imwrite(fileName, sum, compression_params);
	}
	catch (cv::Exception& ex) {
	    cout<<"Error! Exception converting image to PNG format:"<< ex.what();
	    return false;
	}
	cout<<fileName<<" successfully created."<<endl;
	return true;
}
/*******************************************************************************************/
/* This functions verify whether the file exists or not*/
bool fileExists(const string filename) {
  std::ifstream ifile(filename.c_str());
  return (bool)ifile;
}
/*******************************************************************************************/
