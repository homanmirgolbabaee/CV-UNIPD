#ifndef PARKING_SPACE_DETECTOR_H
#define PARKING_SPACE_DETECTOR_H

#include <opencv2/opencv.hpp>
#include <vector>

class ParkingSpaceDetector {
public:
    ParkingSpaceDetector();
    std::vector<cv::RotatedRect> detectParkingSpaces(const cv::Mat& image);

private:
    cv::Mat preprocessImage(const cv::Mat& image);
    std::vector<cv::Vec4i> detectLines(const cv::Mat& edges);
    std::vector<cv::Point2f> findIntersections(const std::vector<cv::Vec4i>& lines);
    std::vector<cv::RotatedRect> formParkingSpaces(const std::vector<cv::Point2f>& intersections);
    bool lineIntersection(cv::Vec4i line1, cv::Vec4i line2, cv::Point2f& intersection);
};

#endif // PARKING_SPACE_DETECTOR_H