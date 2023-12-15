#include <iostream>
#include <opencv2/opencv.hpp>
#include <fmt/core.h>
using namespace std;
using namespace cv;

int main(int argc, char* argv[]){
    if(argc != 3){
        fmt::println(stderr,"<usage>{} image1_path image2_path",argv[0]);
        return 1;
    }
    vector<Mat> imgs;
    Mat img1 = imread(argv[1]);
    Mat img2 = imread(argv[2]);

    if (img1.empty() || img2.empty())
    {
        cout << "Can't read image" << endl;
        return -1;
    }
    imgs.push_back(img1);
    imgs.push_back(img2);


    Ptr<Stitcher> stitcher = Stitcher::create(Stitcher::PANORAMA);
    // 使用stitch函数进行拼接
    Mat pano;
    Stitcher::Status status = stitcher->stitch(imgs, pano);
    if (status != Stitcher::OK)
    {
        cout << "Can't stitch images, error code = " << int(status) << endl;
        return -1;
    }
    imwrite("result.jpg", pano);
    return 0;
}

