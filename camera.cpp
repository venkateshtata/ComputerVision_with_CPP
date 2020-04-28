#include <opencv2/opencv.hpp>
#include <iostream>

int main(int argc, char** argv){

	cv::namedWindow("stream", cv::WINDOW_AUTOSIZE);

	cv::VideoCapture cap;
	cap.open(0);

	cv::Mat frame;

	cv::Mat img_gray, img_canny;

	for(;;){

		cap >> frame;


		cv::cvtColor(frame, img_gray, cv::COLOR_BGR2GRAY);

		cv::Canny(img_gray, img_canny, 10, 100, 3, true);

		if(img_canny.empty()){
			break;
		}

		cv::imshow("stream", img_canny);
		if(cv::waitKey(33)<=0){
			break;
		}





	}
}