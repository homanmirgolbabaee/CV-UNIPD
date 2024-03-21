// ImageFilters.cpp
#include "ImageFilters.h"

void applyMaxFilter(const cv::Mat& src, cv::Mat& dst, int kernelSize) {
    if (kernelSize % 2 == 0) {
        std::cout << "Kernel size must be odd!" << std::endl;
        return;
    }
    // Initialize the destination image
    dst = src.clone();
    int radius = kernelSize / 2;

    // Apply the max filter
    for (int y = radius; y < src.rows - radius; ++y) {
        for (int x = radius; x < src.cols - radius; ++x) {
            cv::Rect region(x - radius, y - radius, kernelSize, kernelSize);
            cv::Mat kernel = src(region);
            double minVal, maxVal;
            cv::minMaxLoc(kernel, &minVal, &maxVal);
            dst.at<uchar>(y, x) = static_cast<uchar>(maxVal);
        }
    }
}

void applyMinFilter(const cv::Mat& src, cv::Mat& dst, int kernelSize) {
    if (kernelSize % 2 == 0) {
        std::cout << "Kernel size must be odd!" << std::endl;
        return;
    }
    // Initialize the destination image
    dst = src.clone();
    int radius = kernelSize / 2;

    // Apply the min filter
    for (int y = radius; y < src.rows - radius; ++y) {
        for (int x = radius; x < src.cols - radius; ++x) {
            cv::Rect region(x - radius, y - radius, kernelSize, kernelSize);
            cv::Mat kernel = src(region);
            double minVal, maxVal;
            cv::minMaxLoc(kernel, &minVal, &maxVal);
            dst.at<uchar>(y, x) = static_cast<uchar>(minVal);
        }
    }
}
