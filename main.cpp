#include <iostream>
#include "DataToMat.h"

int main() {
    std::srand(time(NULL));
    int width = 600;
    DataToMat dataverter(width);
    std::vector<float> data;
    
    while (cv::waitKey(27))
    {
        cv::Mat img(width, width, CV_8UC3, cv::Scalar(0, 0, 0));
        for (float i = 0; i < 360; i++)
        {
            //data.push_back((rand() % (width / 2)));
            int random = (rand() % (width / 2));
            dataverter.drawColoredPoints(img, i,  random);
            //data.push_back(50);
            cv::imshow("test", img);
            cv::waitKey(1);

        }
        //dataverter.dottedShow(img, data);
        //data.clear();
        img.release();
        
    }
    
    return 0;
}
