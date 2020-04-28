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




class CameraCalibrator{
	//points in world coordinates
	std::vector<std::vector<cv::Point3f>> objectPoints;
	//points on image
	std::vector<std::vector<cv::Poin2f>> imagePoints;

	cv::Mat cameraMatrix;
	cv::Mat distCoeffs;

	int flag;

	//Open chessboard images and extract corner points
	int CameraCalibrator::addChessboardPoints(const std::vector<std::string> & filelist, cv::Size & boardSize){

		//points on chessboard
		std::vector<cv::Point2f> imageCorners;
		std::vector<cv::Point3f> objectCorners;

		//3D scene points of chessboard
		for(int i=0; i<boardSize.height; i++){
			for(int j=0; j<boardSize.width; j++){
				objectCorners.push_back(cv::Point3f(i, j, 0.0f));
			}
		}

		//2D image point of chessboard
		cv::Mat image;
		int successes = 0

		for(int i=0; i<filelist.size(); i++){
			
			image = cv::imread(filelist[i], 0);
			bool found = cv::findChessboardCorners(image, boardSize, imageCorners);

			//get subpixel accuracy on the corners
			if(found){
				cv::cornerSubPix(image, imageCorners, cv::Size(5,5), cv::Size(-1,-1), cv::TermCriteria(cv::TermCriteria::MAX_ITER + cv::TermCriteria::EPS, 30, 0.1));

				if(imageCorners.size() == boardSize.area()){
					//Add image and scene points from one view
					addPoints(imageCorners, objectCorners);
					successes++;
				}
			}
			if(imageCorners.size() == boardSize.area()){
				addPoints(imageCorners, objectCorners);
				successes++;
			}
		}

		return successes;

	}

	//Calibrate camera and return re-projection error
	double CameraCalibrator::calibrate(cv::Size &imageSize){

		//output rotations and translation
		std::vector<cv::Mat> rvecs, tvecs;

		return calibrateCamera(objectPoints, imagePoints, imageSize, cameraSize, cameraMatrix, distCoeffs, rvecs, tvecs, flag);
	}


}

int main(int argv, char** argc){


}
