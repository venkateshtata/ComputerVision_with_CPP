#include <opencv2/opencv.hpp>
#include <iostream>
#include <cstdlib>
#include <cstdlib>
#include <random>
#include <vector>
#include "opencv2/features2d/features2d.hpp"
#include <opencv2/xfeatures2d/nonfree.hpp>
#include <opencv2/xfeatures2d.hpp>

#define OPENCV_TRAITS_ENABLE_DEPRECATED

using namespace std;
using namespace cv;

int main(int argc, char** argv){
	cv::Mat image1, image2;

	image1 = cv::imread("m3.jpg",0);
	image2 = cv::imread("m4.jpg",0);

	std::vector<cv::KeyPoint> keypoints1;
	std::vector<cv::KeyPoint> keypoints2;
	cv::Mat descriptors1;
	cv::Mat descriptors2;

	cv::Ptr<cv::Feature2D> feature = cv::ORB::create(60);
	// cv::Ptr<cv::Feature2D> feature = cv::xfeatures2d::SIFT::create(500);

	feature->detectAndCompute(image1, cv::noArray(), keypoints1, descriptors1);
	feature->detectAndCompute(image2, cv::noArray(), keypoints2, descriptors2);

	std::vector<cv::Point2f> selPoints1, selPoints2;
	std::vector<int> pointIndexes1, pointIndexes2;
	cv::KeyPoint::convert(keypoints1, selPoints1, pointIndexes1);
	cv::KeyPoint::convert(keypoints2, selPoints2, pointIndexes2);

	cv::Mat fundamental = cv::findFundamentalMat(selPoints1, selPoints2, cv::FM_7POINT);

	cv::Mat h1;
	cv::Mat h2;

	cv::stereoRectifyUncalibrated(selPoints1, selPoints2, fundamental, image1.size(), h1, h2);

	cv::Mat rectified1(image1.size(), image1.type());
	cv::warpPerspective(image1, rectified1, h1, image1.size());

	cv::Mat rectified2(image2.size(), image2.type());
	cv::warpPerspective(image2, rectified2, h2, image1.size());


	cv::Mat disparity;
	cv::Ptr<cv::StereoMatcher> pStereo = cv::StereoSGBM::create(0, 32, 5);
	pStereo->compute(rectified1, rectified2, disparity);

String name = "ogl";
namedWindow(name, WINDOW_OPENGL);  
setOpenGlDrawCallback(name, disparity);
while (1)
{
     updateWindow(name); // this calls on_opengl
     int k = waitKey(20);
}
}