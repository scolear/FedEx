#include "DataToMat.h"

DataToMat::DataToMat(int width): _width(width)
{
}

cv::Mat DataToMat::convert(std::vector<float> distances)
{
    cv::Mat blank(_width, _width, CV_8UC3, cv::Scalar(0, 0, 0));
    dottedShow(blank, distances);
    //linedShow(blank, distances);
    return blank;
}

cv::Point DataToMat::getCoordinates(int angle, int distance)
{
    cv::Point point((_width / 2) + (distance * cos(angle)), (_width / 2)+(distance * sin(angle)));
  
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
    cv::line(img,
        point,
        point,
        distancedScalar(distance),
        5,
        8);
    
}

void DataToMat::drawColoredLines(cv::Mat img, cv::Point point, cv::Point point2, int distance)
{
    cv::line(img,
        point,
        point2,
        distancedScalar(distance),
        2,
        8);

}

void DataToMat::dottedShow(cv::Mat img, std::vector<float> distances)
{
    for (size_t i = 0; i < 360; i++)
    {
        cv::Point point = getCoordinates(i, distances[i]);
        //drawWhitePoints(blank, point);
        drawColoredPoints(img, point, distances[i]);

    }
}

void DataToMat::linedShow(cv::Mat img, std::vector<float> distances)
{
    for (int i = 0; i < 360-1; i+=2)
    {
        cv::Point point = getCoordinates(i, distances[i]);
        cv::Point point2 = getCoordinates(i+1, distances[i+1]);
        drawColoredLines(img, point, point2, distances[i]);
    }
}

cv::Scalar DataToMat::distancedScalar(int distance)
{
    int tempsdist = distance;
    if (distance > (_width / 3)) {
        distance = 255;
    }
    int red = 255 - distance;
    int green = 255 - red;
    int blue = 0;
    if (green == 255) {
        green = (_width/2) - tempsdist+100;
        blue = (_width / 2) - green;
    }
    return cv::Scalar(blue, green, red);
}
