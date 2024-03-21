#include "ImageFilters.h"
#include <algorithm>
#include <vector>

cv::Mat ImageFilters::applyMaxFilter(const cv::Mat &src, int kernelSize) {
    if (kernelSize % 2 == 0) {
        std::cerr << "Kernel size must be odd." << std::endl;
        return cv::Mat();
    }

    cv::Mat dst = src.clone();
    // Apply the max filter
    // This is a placeholder for the actual max filter implementation
    return dst;
}

cv::Mat ImageFilters::applyMinFilter(const cv::Mat &src, int kernelSize) {
    if (kernelSize % 2 == 0) {
        std::cerr << "Kernel size must be odd." << std::endl;
        return cv::Mat();
    }

    cv::Mat dst = src.clone();
    // Apply the min filter
    // This is a placeholder for the actual min filter implementation
    return dst;
}

cv::Mat ImageFilters::applyMedianFilter(const cv::Mat &src, int kernelSize) {
    if (kernelSize % 2 == 0) {
        std::cerr << "Kernel size must be odd." << std::endl;
        return cv::Mat();
    }

    cv::Mat dst = src.clone();
    // Apply the median filter
    // This is a placeholder for the actual median filter implementation
    return dst;
}
