#include <iostream>
#include "DataToMat.h"
#include "sdk/app/ultra_simple/main.cpp"

int main() {
    std::srand(time(NULL));
    std::cout << "Hello, World!" << std::endl;
    int width = 1000;
    DataToMat dataverter(width);
    std::vector<float> data;
    
    while (true)
    {
        cv::Mat img(width, width, CV_8UC3, cv::Scalar(0, 0, 0));
        for (size_t i = 0; i < 360; i++)
        {
            data.push_back((rand() % (width / 2)));
            //data.push_back(50);

        }
        dataverter.dottedShow(img, data);
        cv::imshow("test", img);
        data.clear();
        img.release();
        cv::waitKey(27);
    }
    
    return 0;
}
