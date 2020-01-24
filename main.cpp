#include <iostream>
#include "DataToMat.h"

int main() {
    std::srand(time(NULL));
    std::cout << "Hello, World!" << std::endl;
    DataToMat dataverter;
    std::vector<float> data;
    for (size_t i = 0; i < 360; i++)
    {
        data.push_back((rand() % 100)+100);
        //data.push_back(50);

    }
    cv::imshow("test", dataverter.convert(data));
    cv::waitKey(0);
    return 0;
}
