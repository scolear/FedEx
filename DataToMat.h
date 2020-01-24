#pragma once
#include <opencv2/opencv.hpp>

class DataToMat
{
public:
	cv::Mat convert(std::vector<float>);
	cv::Point getCoordinates(int angle, int distance);
	void drawWhitePoints(cv::Mat img, cv::Point point);
	void drawColoredPoints(cv::Mat img, cv::Point point, int distance);

private:
	std::vector<float> _distances;
	int _width;
};