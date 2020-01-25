#pragma once
#include <opencv2/opencv.hpp>
#include <math.h>       /* sin */
#include <vector>


class DataToMat
{
public:
	DataToMat(int width);
	cv::Mat convert(cv::Mat* img, float angle, float distance);
	cv::Point getCoordinates(float angle, float distance);
	void drawColoredPoints(cv::Mat img, float angle, float distance);
	void refresherLine(cv::Mat img, float angle, float distance);
	void blackrefresher(cv::Mat img, float angle, float distance);
    void pointDelete(cv::Mat img, float angle);
	cv::Scalar distancedScalar(int distance);
    void clearScreen(cv::Mat* img);

private:
	int _width;
    std::map<int, int> _previousDistance;
};