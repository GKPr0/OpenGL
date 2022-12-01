#pragma once
#include <opencv2/opencv.hpp>

struct CameraData {
    cv::Point2f center;
    cv::Mat img;
};

void processCamera();
void draw_cross_relative(cv::Mat& img, cv::Point2f center_relative, int size);
cv::Point2f findCenterRelative(cv::Mat& frame);
cv::Point2f findCenterRelativeHSV(cv::Mat& frame, cv::Scalar lowerBound, cv::Scalar upperBound);


inline static std::mutex cameraMutex;
inline static std::unique_ptr<CameraData> sharedCameraData;