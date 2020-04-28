#include <opencv2/opencv.hpp>
#include <iostream>
#include <cstdlib>
#include <cstdlib>
#include <random>
#include <vector>


#define OPENCV_FEATURES_2D_HPP

#include "opencv2/opencv_modules.hpp"

#include "opencv2/features2d.hpp"
#include "opencv2/xfeatures2d.hpp"

#include <opencv2/xfeatures2d/nonfree.hpp>
#include <opencv2/xfeatures2d.hpp>



int main(int argc, char** argv){

	cv::Mat img, result1, result2;

	img = cv::imread("images.jpeg");



	std::vector<cv::KeyPoint> keypoints, keypoints2;


	cv::Ptr<cv::xfeatures2d::SiftFeatureDetector> ptrSIFT = cv::xfeatures2d::SiftFeatureDetector::create();
	ptrSIFT->detect(img, keypoints2);

		// cv::Ptr<cv::FastFeatureDetector> ptrFAST = cv::FastFeatureDetector::create(40);
		// ptrFAST->detect(image,keypoints);

	cv::Ptr<cv::BRISK> ptrBRISK = cv::BRISK::create();
	ptrBRISK->detect(img, keypoints);

	cv::drawKeypoints(img, keypoints2, result1);// drawing flag
	cv::drawKeypoints(img, keypoints, result2);

	// cv::drawKeypoints(img, keypoints, result, cv::Scalar(255,255,255), cv::DrawMatchesFlags::DRAW_OVER_OUTIMG);// drawing flag

	// cv::drawKeypoints(img, keypoints, result, cv::Scalar(0,0,255),cv::DrawMatchesFlags::DRAW_RICH_KEYPOINTS);


	cv::namedWindow("Image");
	cv::imshow("Image",result1);
	// cv::waitKey(0);

	cv::namedWindow("Image2");
	cv::imshow("Image2",result2);
	cv::waitKey(0);
}
