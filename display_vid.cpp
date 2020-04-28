#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>

int main(int argc, char** argv){
	cv::namedWindow("example2", cv::WINDOW_AUTOSIZE);
	cv::VideoCapture cap;
	cap.open("1v.mkv");

	cv::Mat frame;
	for(;;){
		cap >> frame;
		if(frame.empty()){
			break;
		}

		cv::imshow("example2", frame);
		if(cv::waitKey(33) <=0 )break;
	}

	return 0;
}    