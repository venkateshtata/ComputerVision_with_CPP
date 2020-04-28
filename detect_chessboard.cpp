#include <opencv2/opencv.hpp>
#include <iostream>
#include <cstdlib>
#include <cstdlib>
#include <random>
#include <vector>
#include "opencv2/features2d/features2d.hpp"
#include <opencv2/xfeatures2d/nonfree.hpp>
#include <opencv2/xfeatures2d.hpp>

using namespace std;
using namespace cv;

int main(){
	cv::Mat image;

	image = cv::imread("chess.jpg");

	std::vector<cv::Point2f> imageCorners;
	cv::Size boardSize(7,7);

	bool found = cv::findChessboardCorners(image, boardSize, imageCorners);

	cv::drawChessboardCorners(image, boardSize, imageCorners, found);

	// cv::namedWindow("frame");
	// cv::imshow("frame", image);
	cv::imwrite("frame.jpg", image);
	// cv::waitKey(0);
}

