#include <iostream>
#include <opencv2/opencv.hpp>
#include <numeric>
#include <chrono>

void initCamera();
void draw_cross_relative(cv::Mat& img, cv::Point2f center_relative, int size);
cv::Point2f findCenterRelative(cv::Mat& frame);
cv::Point2f findCenterRelativeHSV(cv::Mat& frame, cv::Scalar lowerBound, cv::Scalar upperBound, bool vizualizeFoundPixels);

typedef struct s_globals {
    cv::VideoCapture capture;
} s_globals;

s_globals globals;

int main()
{
    cv::Mat frame, scene;

    initCamera();

    //HSV range (0..180) (0..255) (0..255)
    cv::Scalar lowerBound(40, 100, 50);
    cv::Scalar upperBound(80, 255, 255);

    while (true)
    {
        globals.capture.read(frame);
        if (frame.empty())
        {
            std::cerr << "device disconected or video ended" << std::endl;
            break;
        }
	    
        auto center = findCenterRelativeHSV(frame, lowerBound, upperBound, true);

	    draw_cross_relative(frame, center, 25);

        cv::namedWindow("frame");
        cv::imshow("frame", frame);

        cv::waitKey(1); //poll OS events
    }

    if (globals.capture.isOpened())
        globals.capture.release();
}

void initCamera()
{
    globals.capture = cv::VideoCapture(cv::CAP_DSHOW);

    if (!globals.capture.isOpened())
    {
        std::cerr << "no camera" << std::endl;
        exit(EXIT_FAILURE);
    }
    else
    {
        std::cout << "Camera " <<
            ": width=" << globals.capture.get(cv::CAP_PROP_FRAME_WIDTH) <<
            ", height=" << globals.capture.get(cv::CAP_PROP_FRAME_HEIGHT) <<
            ", FPS=" << globals.capture.get(cv::CAP_PROP_FPS) << std::endl;
    }
}

cv::Point2f findCenterRelativeHSV(cv::Mat& frame, cv::Scalar lowerBound, cv::Scalar upperBound, bool vizualizeFoundPixels = false)
{
    cv::Mat frameHsv;
    cv::cvtColor(frame, frameHsv, cv::COLOR_BGR2HSV);

    cv::Mat frameTresholded;
    cv::inRange(frameHsv, lowerBound, upperBound, frameTresholded);

    // Remove noise by apliing morhp operation opening
    cv::Mat frameCleared;
    cv::Mat kernel = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(5, 5));
    cv::morphologyEx(frameTresholded, frameCleared, cv::MORPH_OPEN, kernel);

    if(vizualizeFoundPixels)
        cv::namedWindow("frameTrehsolded");
        cv::imshow("frameTrehsolded", frameCleared);

    std::vector<cv::Point> whitePixels;
    cv::findNonZero(frameCleared, whitePixels);
    cv::Point whiteReduced = std::reduce(whitePixels.begin(), whitePixels.end());

    cv::Point2f centerRelative((float)whiteReduced.x / whitePixels.size() / frame.cols, (float) whiteReduced.y / whitePixels.size() / frame.rows);
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
