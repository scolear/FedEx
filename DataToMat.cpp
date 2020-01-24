#include "DataToMat.h"

cv::Mat DataToMat::convert(std::vector<float> distances)
{
    _width = 600;
    cv::Mat blank(_width, _width, CV_8UC3, cv::Scalar(0, 0, 0));
    for (size_t i = 0; i < 360; i++)
    {
        cv::Point point = getCoordinates(i, distances[i]);
        drawWhitePoints(blank, point);
        
    }

    cv::Mat output;

    return blank;
}

cv::Point DataToMat::getCoordinates(int angle, int distance)
{
    cv::Point point((_width / 2) + (distance * cos(angle)), (_width/2)+(distance * sin(angle)));
  
    return point;
}

void DataToMat::drawWhitePoints(cv::Mat img, cv::Point point)
{
    cv::line(img,
        point,
        point,
        cv::Scalar(255, 255, 255),
        2,
        8);
}

void DataToMat::drawColoredPoints(cv::Mat img, cv::Point point, int distance)
{
    if (distance > 255) {

    }
    int red = 255 - distance;
    int green = distance;
    int blue = 0;
    if (green < 255) {
        green = 255 - distance;
        blue = dis
    }
    
}
