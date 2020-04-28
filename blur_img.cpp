#include<opencv2/opencv.hpp>

void blurr(cv::Mat);

int main(int argc, char** argv){
	cv::Mat img = cv::imread("1.jpg", -1);

	
	if(img.empty()){
		return -1;
	
	}

	cv::Mat b = img;

	blurr(b);
	return 0;
}



void blurr(cv::Mat image){

	cv::namedWindow("input image", cv::WINDOW_AUTOSIZE);
	cv::imshow("input image", image);

	cv::Mat out;

	cv::GaussianBlur(image, out, cv::Size(5,5), 3, 3);
	cv::GaussianBlur(out, out, cv::Size(5,5), 3, 3);
	

	cv::namedWindow("output image", cv::WINDOW_AUTOSIZE);
	cv::imshow("output image", out);

	cv::waitKey(0);
}

