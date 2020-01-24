#include <iostream>
#include "DataToMat.h"

int main() {
    std::srand(time(NULL));
    std::cout << "Hello, World!" << std::endl;
    int width = 600;
    DataToMat dataverter(width);
    std::vector<float> data;
    for (size_t i = 0; i < 360; i++)
    {
        data.push_back((rand() % (width/2)) +5);
        //data.push_back(50);

    }
    cv::imshow("test", dataverter.convert(data));
    cv::waitKey(0);
    return 0;
}
