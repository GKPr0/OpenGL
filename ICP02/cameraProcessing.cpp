#include <numeric>

#include "cameraProcessing.h"
#include "globals.h"


void processCamera()
{
    //HSV range (0..180) (0..255) (0..255)
    cv::Scalar lowerBound(55, 50, 50);
    cv::Scalar upperBound(65, 255, 255);

    while (globals.capture.isOpened())
    {
        cv::Mat frame;
        globals.capture.read(frame);
        if (frame.empty())
        {
            std::cerr << "device disconected or video ended" << std::endl;
            if (globals.capture.isOpened())
                globals.capture.release();
            break;
        }

        auto tmpCameraData = std::make_unique<CameraData>();
        tmpCameraData->center = findCenterRelativeHSV(frame, lowerBound, upperBound);
        frame.copyTo(tmpCameraData->img);

        cameraMutex.lock();
        sharedCameraData = std::move(tmpCameraData);
        cameraMutex.unlock();
    }
}

cv::Point2f findCenterRelativeHSV(cv::Mat& frame, cv::Scalar lowerBound, cv::Scalar upperBound)
{
    cv::Mat frameHsv;
    cv::cvtColor(frame, frameHsv, cv::COLOR_BGR2HSV);

    cv::Mat frameTresholded;

    cv::inRange(frameHsv, lowerBound, upperBound, frameTresholded);

    /*
    cv::namedWindow("frameTrehsolded");
    cv::imshow("frameTrehsolded", frameTresholded);
    */

    std::vector<cv::Point> whitePixels;
    cv::findNonZero(frameTresholded, whitePixels);
    cv::Point whiteReduced = std::reduce(whitePixels.begin(), whitePixels.end());

    cv::Point2f centerRelative((float)whiteReduced.x / whitePixels.size() / frame.cols, (float)whiteReduced.y / whitePixels.size() / frame.rows);
    return centerRelative;
}

cv::Point2f findCenterRelative(cv::Mat& frame)
{
    cv::Mat gray_frame;
    frame.copyTo(gray_frame);

    int sx = 0, sy = 0, sw = 0;
    for (int i = 0; i < frame.cols; i++)
    {
        for (int j = 0; j < frame.rows; j++)
        {
            cv::Vec3b pixel = frame.at<cv::Vec3b>(j, i);
            unsigned char Y = 0.299 * pixel[2] + 0.587 * pixel[1] + 0.114 * pixel[0];

            if (Y < 230)
                Y = 0;
            else {
                Y = 255;
                sx += i;
                sy += j;
                sw++;
            }

            gray_frame.at<cv::Vec3b>(j, i) = cv::Vec3b(Y, Y, Y);
        }
    }

    cv::Point2i center(sx / sw, sy / sw);
    cv::Point2f centerRelative((float)center.x / frame.cols, (float)center.y / frame.rows);

    return centerRelative;
}

void draw_cross_relative(cv::Mat& img, cv::Point2f center_relative, int size)
{
    center_relative.x = std::clamp(center_relative.x, 0.0f, 1.0f);
    center_relative.y = std::clamp(center_relative.y, 0.0f, 1.0f);
    size = std::clamp(size, 1, std::min(img.cols, img.rows));

    cv::Point2f center_absolute(center_relative.x * img.cols, center_relative.y * img.rows);

    cv::Point2f p1(center_absolute.x - size / 2, center_absolute.y);
    cv::Point2f p2(center_absolute.x + size / 2, center_absolute.y);
    cv::Point2f p3(center_absolute.x, center_absolute.y - size / 2);
    cv::Point2f p4(center_absolute.x, center_absolute.y + size / 2);

    cv::line(img, p1, p2, CV_RGB(255, 0, 0), 3);
    cv::line(img, p3, p4, CV_RGB(255, 0, 0), 3);
}