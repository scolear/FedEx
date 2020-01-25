#include "DataToMat.h"

#define PI 3.14159265

DataToMat::DataToMat(int width) : _width(width)
{
}

cv::Mat DataToMat::convert(cv::Mat* img, float angle, float distance)
{
    drawColoredPoints(*img, angle, distance);
    blackrefresher(*img, angle, _width);
    //refresherLine(*img, angle, _width);
    return *img;
}

cv::Point DataToMat::getCoordinates(float angle, float distance)
{
    int x = (distance * cos(angle * PI / 180.0)) + (_width / 2);
    int y = (distance * sin(angle * PI / 180.0)) + (_width / 2);
    cv::Point point(x, y);
    return point;
}

void DataToMat::drawColoredPoints(cv::Mat img, float angle, float distance)
{
    cv::Point pt = getCoordinates(angle, distance);
    cv::line(img,
        pt,
        pt,
        distancedScalar(distance),
        5,
        8);
}

void DataToMat::refresherLine(cv::Mat img, float angle, float distance)
{
    cv::Point pt = getCoordinates(angle+20, _width);
    cv::line(img,
        cv::Point(_width / 2, _width / 2),
        pt,
        cv::Scalar(0,163,49),
        7,
        4);
}

void DataToMat::blackrefresher(cv::Mat img, float angle, float distance)
{
    cv::Point pt = getCoordinates(angle + 3, _width);
    cv::line(img,
        cv::Point(_width / 2, _width / 2),
        pt,
        cv::Scalar(0, 0, 0),
        10,
        8);
}

cv::Scalar DataToMat::distancedScalar(int distance)
{
    int centerOffset = 20;
    int tempsdist = distance+centerOffset;
    if (distance > (_width / 3)) {
        distance = 255;
    }
    int red = 255 - distance;
    int green = 255 - red;
    int blue = 0;
    if (green > 254) {
        green = (_width/2) - tempsdist + 120+ centerOffset;
        blue = (_width / 2) - green;
    }
    return cv::Scalar(blue, green, red);
}
