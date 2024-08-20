#ifndef CAR_SEGMENTATION_H
#define CAR_SEGMENTATION_H

#include <opencv2/opencv.hpp>
#include <vector>

class CarSegmentation {
public:
    CarSegmentation();
    cv::Mat segmentCars(const cv::Mat& image, const std::vector<cv::RotatedRect>& parkingSpaces);

private:
    cv::Mat createColorMask(const cv::Mat& image);
    cv::Mat refineMask(const cv::Mat& mask);
    std::vector<std::vector<cv::Point>> findCarContours(const cv::Mat& mask);
    void classifyCars(std::vector<std::vector<cv::Point>>& carContours, const std::vector<cv::RotatedRect>& parkingSpaces, cv::Mat& result);
};

#endif // CAR_SEGMENTATION_H