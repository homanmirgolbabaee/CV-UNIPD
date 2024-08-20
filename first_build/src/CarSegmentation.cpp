#include "CarSegmentation.h"

CarSegmentation::CarSegmentation() {}

cv::Mat CarSegmentation::segmentCars(const cv::Mat& image, const std::vector<cv::RotatedRect>& parkingSpaces) {
    cv::Mat colorMask = createColorMask(image);
    cv::Mat refinedMask = refineMask(colorMask);
    std::vector<std::vector<cv::Point>> carContours = findCarContours(refinedMask);
    
    cv::Mat result = cv::Mat::zeros(image.size(), CV_8UC3);
    classifyCars(carContours, parkingSpaces, result);
    
    return result;
}

cv::Mat CarSegmentation::createColorMask(const cv::Mat& image) {
    cv::Mat hsv, mask;
    cv::cvtColor(image, hsv, cv::COLOR_BGR2HSV);
    cv::inRange(hsv, cv::Scalar(0, 50, 50), cv::Scalar(180, 255, 255), mask);
    return mask;
}

cv::Mat CarSegmentation::refineMask(const cv::Mat& mask) {
    cv::Mat refined;
    cv::Mat kernel = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(5, 5));
    cv::morphologyEx(mask, refined, cv::MORPH_CLOSE, kernel);
    cv::morphologyEx(refined, refined, cv::MORPH_OPEN, kernel);
    return refined;
}

std::vector<std::vector<cv::Point>> CarSegmentation::findCarContours(const cv::Mat& mask) {
    std::vector<std::vector<cv::Point>> contours;
    cv::findContours(mask, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);
    return contours;
}

void CarSegmentation::classifyCars(std::vector<std::vector<cv::Point>>& carContours, const std::vector<cv::RotatedRect>& parkingSpaces, cv::Mat& result) {
    for (const auto& contour : carContours) {
        cv::RotatedRect carRect = cv::minAreaRect(contour);
        bool isInParkingSpace = false;
        
        for (const auto& space : parkingSpaces) {
            if (space.boundingRect().contains(carRect.center)) {
                isInParkingSpace = true;
                break;
            }
        }
        
        cv::Scalar color = isInParkingSpace ? cv::Scalar(0, 0, 255) : cv::Scalar(0, 255, 0);
        cv::drawContours(result, std::vector<std::vector<cv::Point>>{contour}, 0, color, -1);
    }
}