#include <opencv2/opencv.hpp>
#include <fmt/core.h>
constexpr bool debug = true;

const cv::Mat& image_fusion(cv::Mat& up, cv::Mat& down, cv::Mat& left, cv::Mat& right){
    static cv::Mat frame_result;    
    static float frame_width  = up.size().width;
    static float frame_height = up.size().height;
    static std::vector<cv::Point2f> src_vertices{  // 源图像的四个顶点
        {0, 0},
        {frame_width, 0},
        {frame_width, frame_height},
        {0, frame_height},
    };
    static std::vector<cv::Point2f> up_vertices{
        {0, 0},
        {frame_width, 0},
        {frame_width*0.666f, frame_height*0.333f},
        {frame_width*0.333f, frame_height*0.333f},
    };
    static std::vector<cv::Point2f> down_vertices{
        {frame_width, frame_height},
        {0, frame_height},
        {frame_width*0.333f, frame_height*0.666f},
        {frame_width*0.666f, frame_height*0.666f},
    };
    static std::vector<cv::Point2f> left_vertices{
        {0, frame_height},
        {0, 0},
        {frame_width*0.333f, frame_height*0.333f},
        {frame_width*0.333f, frame_height*0.666f},
    };
    static std::vector<cv::Point2f> right_vertices{
        {frame_width, 0},
        {frame_width, frame_height},
        {frame_width*0.666f, frame_height*0.666f},
        {frame_width*0.666f, frame_height*0.333f},
    };


    static cv::Mat up_perspective    = cv::getPerspectiveTransform(src_vertices, up_vertices);
    static cv::Mat down_perspective  = cv::getPerspectiveTransform(src_vertices, down_vertices);
    static cv::Mat left_perspective  = cv::getPerspectiveTransform(src_vertices, left_vertices);
    static cv::Mat right_perspective = cv::getPerspectiveTransform(src_vertices, right_vertices);

    cv::warpPerspective(up, up, up_perspective, up.size());
    cv::warpPerspective(down, down, down_perspective, up.size());
    cv::warpPerspective(left, left, left_perspective, up.size());
    cv::warpPerspective(right, right, right_perspective, up.size());
    if constexpr(debug){
        cv::imwrite("up.jpg",up);
        cv::imwrite("down.jpg",down);
        cv::imwrite("left.jpg",left);
        cv::imwrite("right.jpg",right);
    }
    frame_result = up + down + left + right;
    return frame_result;
}

int main(){
    // 打开视频文件
    cv::VideoCapture cap_up("up.mp4");
    cv::VideoCapture cap_down("down.mp4");
    cv::VideoCapture cap_left("left.mp4");
    cv::VideoCapture cap_right("right.mp4");
    cv::VideoWriter video_writer("output.mp4", cv::VideoWriter::fourcc('m', 'p', '4', 'v'), 30, cv::Size(1280, 720));

    // 检查视频是否成功打开
    if (!cap_up.isOpened() || !cap_down.isOpened() || !cap_left.isOpened() || !cap_right.isOpened()) {
        std::cerr << "Error: Unable to open video files." << std::endl;
        return -1;
    }

    while (true) {
        cv::Mat frame_up, frame_down, frame_left, frame_right;

        // 逐帧读取图像并处理
        if (!cap_up.read(frame_up) || !cap_down.read(frame_down) || !cap_left.read(frame_left) || !cap_right.read(frame_right)) {
            fmt::println("video end!");
            break;
        } else{
            video_writer << image_fusion(frame_up, frame_down, frame_left, frame_right);
        }

    }
    
    video_writer.release();
    cap_right.release();
    cap_left.release();
    cap_down.release();
    cap_up.release();

    return 0;
}
