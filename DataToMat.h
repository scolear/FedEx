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
	void dottedShow(cv::Mat img, std::vector<float>distances);
	void pointDelete(cv::Mat img, float angle);
	cv::Scalar distancedScalar(int distance);

private:
	std::vector<float> _distances;
	std::map<float, float> _perviousDistance;
	int _width;
};