#include <opencv2/opencv.hpp>
#include <vector>

int main(){
    cv::Mat src_image = cv::imread("Parthenon.jpg");
    cv::Mat dst_image;
    std::vector<cv::Point2f> src_vertices{
        {1075, 1575},
        {2938, 1052},
        {2938, 2640},
        {1075, 2640},
    };
    std::vector<cv::Point2f> dst_vertices{
        {1075, 1052},
        {2938, 1052},
        {2938, 2640},
        {1075, 2640},
    };

    cv::Mat perspectiveMatrix = cv::getPerspectiveTransform(src_vertices, dst_vertices);
    cv::warpPerspective(src_image, dst_image, perspectiveMatrix, src_image.size());
    cv::imwrite("Parthenon_front.jpg", dst_image);

}
