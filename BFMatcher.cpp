#include <opencv2/opencv.hpp>
#include <iostream>
#include <cstdlib>
#include <cstdlib>
#include <random>
#include <vector>

#include "opencv2/features2d/features2d.hpp"

#include "opencv2/xfeatures2d.hpp"

#include <opencv2/xfeatures2d/nonfree.hpp>
#include <opencv2/xfeatures2d.hpp>



using namespace std;
using namespace cv;

int main(int argc, char** argv){

	cv::Mat img1;
	cv::Mat img2;
	

	img1 = cv::imread("t3.jpg");
	// img2 = cv::imread("t4.jpg");

	cv::namedWindow("img1");

	cv::VideoCapture cap;
	cap.open(0); 

	for(;;){

		cap >> img2;

		if(img2.empty()){
			break;
		}


	std::vector<cv::KeyPoint> keypoints1, keypoints2;

	cv::Ptr<cv::Feature2D> ptrFeature2D;
	ptrFeature2D = cv::xfeatures2d::SURF::create(10000);

	ptrFeature2D->detect(img1, keypoints1);
	ptrFeature2D->detect(img2, keypoints2);

	cv::Mat descriptor1;
	cv::Mat descriptor2;

	ptrFeature2D->compute(img1, keypoints1, descriptor1);
	ptrFeature2D->compute(img2, keypoints2, descriptor2);

	cv::BFMatcher matcher(cv::NORM_L2);

	std::vector<cv::DMatch> matches;
	matcher.match(descriptor1, descriptor2, matches);

	cv::Mat matchImage;

	cv::drawMatches(img1, keypoints1, img2, keypoints2, matches, matchImage, Scalar::all(-1), Scalar::all(-1), vector<char>(), DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS);

	matches.clear();
	keypoints1.clear();
	keypoints2.clear();


	// cv::namedWindow("img2");

	cv::imshow("img1",matchImage);
	// cv::imshow("img2",result2);

	cv::waitKey(1);





}
}

