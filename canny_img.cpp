#include <opencv2/opencv.hpp>
#include <cstdio>
#include <cstdlib>
#include <iostream>

using namespace std;

void detect_edge(cv::Mat);

int main(int argc, char** argv){

	cv::Mat img_orig = cv::imread("1.jpg", -1);

	cout << "Called function";

	detect_edge(img_orig);
}

void detect_edge(cv::Mat img_original){



	cv::Mat img_gray, img_canny;

	// img_original = cv::imread("1.jpg", -1);

	cv::cvtColor(img_original, img_gray, cv::COLOR_BGR2GRAY);
	cv::namedWindow("gray image", cv::WINDOW_AUTOSIZE);
	cv::imshow("gray image", img_gray);


	cv::Canny(img_gray, img_canny, 10, 100, 3, true);
	cv::namedWindow("canny image", cv::WINDOW_AUTOSIZE);
	cv::imshow("canny image", img_canny);


	cv::waitKey(0);

}