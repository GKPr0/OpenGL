#include <iostream>
#include <opencv2/opencv.hpp>
#include <numeric>
#include <chrono>

struct CameraData {
    cv::Point2f center;
    cv::Mat img;
};

void initializeCamera();
void releaseCamera();

void processCamera();
cv::Point2f findCenterRelativeHSV(cv::Mat& frame, cv::Scalar lowerBound, cv::Scalar upperBound);

void drawCrossRelative(cv::Mat& img, cv::Point2f center_relative, int size);

//HSV range (0..180) (0..255) (0..255)
cv::Scalar lowerBound(40, 100, 50);
cv::Scalar upperBound(80, 255, 255);

cv::VideoCapture videoCapture;
std::mutex cameraMutex;
std::unique_ptr<CameraData> sharedCameraData;

int main()
{
    initializeCamera();

    //Start camera processing thread
    std::thread cameraThread = std::thread(processCamera);

    cv::namedWindow("Camera");

    std::unique_ptr<CameraData> localCameraData;
    bool newCameraData = false;
    bool isRunning = true;
    while (videoCapture.isOpened() && isRunning)
    {
        //Receive data from camera processing thread
        cameraMutex.lock();
        if (sharedCameraData && !sharedCameraData->img.empty())
        {
            localCameraData = std::move(sharedCameraData);
            newCameraData = true;
        }
        cameraMutex.unlock();

       if (newCameraData)
        {
            std::cout << "\033[K\rDetected center: " << localCameraData->center; //clear line and print
            drawCrossRelative(localCameraData->img, localCameraData->center, 25);
            cv::imshow("Camera", localCameraData->img);
        }
	   
        newCameraData = false;
        char key = cv::waitKey(16); //poll OS events every 16ms (cca 60 fps)
        switch (key)
        {
            case 27: // Escape key
                isRunning = false;
                break;
        }
    }

    releaseCamera();
    cameraThread.join();

    return EXIT_SUCCESS;
}


void initializeCamera()
{
    videoCapture = cv::VideoCapture(cv::CAP_DSHOW);
    if (!videoCapture.isOpened())
    {
        std::cerr << "no camera" << std::endl;
        exit(EXIT_FAILURE);
    }

    std::cout << "Camera " <<
        ": width=" << videoCapture.get(cv::CAP_PROP_FRAME_WIDTH) <<
        ", height=" << videoCapture.get(cv::CAP_PROP_FRAME_HEIGHT) <<
        ", FPS=" << videoCapture.get(cv::CAP_PROP_FPS) << std::endl;
}

void releaseCamera()
{
    if (videoCapture.isOpened())
        videoCapture.release();
}


void processCamera()
{
    while (videoCapture.isOpened())
    {
        cv::Mat frame;
        videoCapture.read(frame);
        if (frame.empty())
        {
            std::cerr << "device disconected or video ended" << std::endl;
            releaseCamera();
            break;
        }

        auto tmpCameraData = std::make_unique<CameraData>();
        tmpCameraData->center = findCenterRelativeHSV(frame, lowerBound, upperBound);
        frame.copyTo(tmpCameraData->img);

        //Move data to shared variable
        cameraMutex.lock();
        sharedCameraData = std::move(tmpCameraData);
        cameraMutex.unlock();

        //std::this_thread::sleep_for(std::chrono::milliseconds(5));   //Sleep for 5ms
    }
}


cv::Point2f findCenterRelativeHSV(cv::Mat& frame, cv::Scalar lowerBound, cv::Scalar upperBound)
{
    cv::Mat frameHsv;
    cv::cvtColor(frame, frameHsv, cv::COLOR_BGR2HSV);

    // Tresholding
    cv::Mat frameTresholded;
    cv::inRange(frameHsv, lowerBound, upperBound, frameTresholded);

    // Remove noise by apliing morhp operation opening
    cv::Mat frameCleared;
    cv::Mat kernel = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(5, 5));
    cv::morphologyEx(frameTresholded, frameCleared, cv::MORPH_OPEN, kernel);

    // Calculating center of mass
    std::vector<cv::Point> whitePixels;
    cv::findNonZero(frameCleared, whitePixels);
    cv::Point whiteReduced = std::reduce(whitePixels.begin(), whitePixels.end()); //sum of all points per axis
    cv::Point2f center((float)whiteReduced.x / whitePixels.size() , (float)whiteReduced.y / whitePixels.size());
    cv::Point2f centerRelative(center.x / frame.cols, center.y / frame.rows);

    return centerRelative;
}


void drawCrossRelative(cv::Mat& img, cv::Point2f centerRelative, int size)
{
    centerRelative.x = std::clamp(centerRelative.x, 0.0f, 1.0f);
    centerRelative.y = std::clamp(centerRelative.y, 0.0f, 1.0f);
    size = std::clamp(size, 1, std::min(img.cols, img.rows));

    cv::Point2f centerAbsolute(centerRelative.x * img.cols, centerRelative.y * img.rows);

    cv::Point2f p1(centerAbsolute.x - size / 2, centerAbsolute.y);
    cv::Point2f p2(centerAbsolute.x + size / 2, centerAbsolute.y);
    cv::Point2f p3(centerAbsolute.x, centerAbsolute.y - size / 2);
    cv::Point2f p4(centerAbsolute.x, centerAbsolute.y + size / 2);

    cv::line(img, p1, p2, CV_RGB(255, 0, 0), 3);
    cv::line(img, p3, p4, CV_RGB(255, 0, 0), 3);
}
