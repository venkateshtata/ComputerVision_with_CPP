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

	cv::Mat img1, img2, matchImage, result1, result2;;

	img1 = cv::imread("t1.jpg",0);
	img2 = cv::imread("t2.jpg",0);

	std::vector<cv::KeyPoint> keypoints1, keypoints2;

	cv::Ptr<cv::FeatureDetector> ptrDetector;
	ptrDetector = cv::FastFeatureDetector::create(80);

	ptrDetector->detect(img1, keypoints1);
	ptrDetector->detect(img2, keypoints2);

	

	const int nsize(11);
	cv::Rect neighborhood(0,0, nsize, nsize);
	cv::Mat patch1;
	cv::Mat patch2;

	cv::Mat result;
	std::vector<cv::DMatch> matches;

	for(int i=0; i<keypoints1.size(); i++){
		neighborhood.x = keypoints1[i].pt.x-nsize/2;
		neighborhood.y = keypoints1[i].pt.y-nsize/2;

		if(neighborhood.x<0 || neighborhood.y<0 || neighborhood.x+nsize >= img1.cols || neighborhood.y+nsize >= img1.rows){
			continue;
		}

		patch1 = img1(neighborhood);

		cv::DMatch bestMatch;

		for(int j=0; j<keypoints2.size(); j++){
			neighborhood.x = keypoints2[j].pt.x-nsize/2;
			neighborhood.y = keypoints2[j].pt.y-nsize/2;

			if(neighborhood.x<0 || neighborhood.y<0 || neighborhood.x + nsize >= img2.cols || neighborhood.y + nsize >= img2.rows){
				continue;
			}

			patch2 = img2(neighborhood);

			cv::matchTemplate(patch1, patch2, result, cv::TM_SQDIFF);

			if(result.at<float>(0,0) < bestMatch.distance){
				bestMatch.distance = result.at<float>(0,0);
				bestMatch.queryIdx = i;
				bestMatch.trainIdx = j;
			}
		}

		matches.push_back(bestMatch);

		std::nth_element(matches.begin(), matches.begin()+25, matches.end());
		matches.erase(matches.begin() + 25, matches.end());

	}

	// cv::drawKeypoints(img1, keypoints1, result1);// drawing flag
	// cv::drawKeypoints(img2, keypoints2, result2);



	cv::drawMatches(img1, keypoints1, img2, keypoints2, matches, matchImage,cv::Scalar(255,255,255), cv::Scalar(255,255,255));

	// cv::namedWindow("img1");
	// cv::namedWindow("img2");

	// cv::imshow("img1",result1);
	// cv::imshow("img2",result2);

	cv::waitKey(0);



	// cv::drawMatches(img1, )

}

