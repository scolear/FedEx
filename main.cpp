#include <iostream>
#include "DataToMat.h"

int main() {
    std::srand(time(NULL));
    int width = 600;
    DataToMat dataverter(width);
    cv::Mat img(width, width, CV_8UC3, cv::Scalar(0, 0, 0));
    while (1)
    {
        for (int i = 0; i < 360; i++)
        {
            int random = (rand() % (width / 2)+20);            
            cv::imshow("test", dataverter.convert(img, i, random));
            cv::waitKey(1);
        }
    }
    
    return 0;
}
