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


std::vector<std::vector<cv::Point3f>> objectPoints;
//points on image
std::vector<std::vector<cv::Point2f>> imagePoints;

cv::Mat cameraMatrix;
cv::Mat distCoeffs;
cv::Size imgSize;

std::vector<cv::Mat> rvecs, tvecs;



int flag;

int addChessboardPoints(const std::vector<std::string> & filelist, cv::Size & boardSize){

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
	int successes = 0;

	for(int i=0; i<filelist.size(); i++){
		
		image = cv::imread(filelist[i], 0);
		imgSize = image.size();
		bool found = cv::findChessboardCorners(image, boardSize, imageCorners);

		//get subpixel accuracy on the corners
		if(found){
			cv::cornerSubPix(image, imageCorners, cv::Size(5,5), cv::Size(-1,-1), cv::TermCriteria(cv::TermCriteria::MAX_ITER + cv::TermCriteria::EPS, 30, 0.1));

			if(imageCorners.size() == boardSize.area()){
				//Add image and scene points from one view
				// addPoints(imageCorners, objectCorners);
				imagePoints.push_back(imageCorners);
            	objectPoints.push_back(objectCorners);
				successes++;
			}
		}
		if(imageCorners.size() == boardSize.area()){
			// addPoints(imageCorners, objectCorners);
			imagePoints.push_back(imageCorners);
            objectPoints.push_back(objectCorners);
			successes++;
		}
	}

	return successes;

}


double calibrate(cv::Size &imageSize){

		return calibrateCamera(objectPoints, imagePoints, imageSize, cameraMatrix, distCoeffs, rvecs, tvecs, flag);
}


int main(){

	

	std::vector<std::string> v = { "chess1.jpg", "chess2.jpg" };


	int numCornersHor = 7;
	int numCornersVer = 7;

	int numSquares = numCornersHor * numCornersVer;
	Size board_size = Size(numCornersHor, numCornersVer); 

	addChessboardPoints(v, board_size);
	calibrate(imgSize);

	//vectors for keypoints and descriptors
	std::vector<cv::KeyPoint> keypoints1;
	std::vector<cv::KeyPoint> keypoints2;
	cv::Mat descriptors1, descriptors2;

	//Constructing SIFT detector
	cv::Ptr<cv::Feature2D> ptrFeature2D = cv::xfeatures2d::SIFT::create(500);

	cv::Mat image1 = cv::imread("m1.jpg");
	cv::Mat image2 = cv::imread("m2.jpg");

	//Detecting features and descriptors
	ptrFeature2D->detectAndCompute(image1, cv::noArray(), keypoints1, descriptors1);
	ptrFeature2D->detectAndCompute(image2, cv::noArray(), keypoints2, descriptors2);

	//Matching the descriptors
	cv::BFMatcher matcher(cv::NORM_L2, true);
	std::vector<cv::DMatch> matches;
	matcher.match(descriptors1, descriptors2, matches);

	//Convert keypoints to Point2f
	std::vector<cv::Point2f> points1, points2;
	for(std::vector<cv::DMatch>::const_iterator it = matches.begin(); it != matches.end(); ++it){

		//get left points
		float x = keypoints1[it->queryIdx].pt.x;
		float y = keypoints1[it->queryIdx].pt.y;
		points1.push_back(cv::Point2f(x,y));
		//get right points
		x = keypoints2[it->trainIdx].pt.x;
		y = keypoints2[it->trainIdx].pt.y;
		points2.push_back(cv::Point2f(x, y));
	}

	//Find Essential Matrix
	cv::Mat inliers;
	cv::Mat essential = cv::findEssentialMat(points1, points2, cameraMatrix, cv::RANSAC, 0.9, 1.0, inliers);

	cv::Mat matched_points;

	// drawMatches(image1, keypoints1, image2, keypoints2, matches, matched_points, Scalar::all(-1), Scalar::all(-1), inliers, 0);

	// cv::namedWindow("frame");
 //   	imshow("frame", matched_points);

 //   	cv::waitKey(0);

	//Recover Camera Pose from Essential Matrix
	cv::Mat rotation, translation;
	cv::recoverPose(essential, points1, points2, cameraMatrix, rotation, translation, inliers);

}