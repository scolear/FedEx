#pragma once
#include <opencv2/opencv.hpp>
#include "UiMainWindow.h"

class DataToMat
{
public:
	DataToMat(int width);
	cv::Mat convert(std::vector<float>distances);
	cv::Point getCoordinates(int angle, int distance);
	void drawWhitePoints(cv::Mat img, cv::Point point);
	void drawColoredPoints(cv::Mat img, cv::Point point, int distance);
	void drawColoredLines(cv::Mat img, cv::Point point, cv::Point point2, int distance);
	void dottedShow(cv::Mat img, std::vector<float>distances);
	void linedShow(cv::Mat img, std::vector<float>distances);
	cv::Scalar distancedScalar(int distance);

private:
	std::vector<float> _distances;
	int _width;
    //id dataverter;
};