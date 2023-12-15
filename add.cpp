#include <opencv2/opencv.hpp>

int main(){
    cv::Mat up = cv::imread("up.jpg");
    cv::Mat down = cv::imread("down.jpg");

    cv::Mat result;
    cv::addWeighted(up,1,down,1,0,result);
    cv::imwrite("result.jpg",result);
}
