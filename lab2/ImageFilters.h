#ifndef IMAGEFILTERS_H
#define IMAGEFILTERS_H

#include <opencv2/opencv.hpp>
#include <string>

// Existing declarations
cv::Mat maxFilter(const cv::Mat& src, int kernelSize);
cv::Mat minFilter(const cv::Mat& src, int kernelSize);
void showResizedWindow(const std::string& winname, const cv::Mat& img, int width = 640, int height = 480);
// New declarations for Tasks 3, 4, 5, and 6
cv::Mat medianFilter(const cv::Mat& src, int kernelSize);
// In ImageFilters.h
cv::Mat gaussianSmoothing(const cv::Mat& src, int kernelSize, double sigmaX, double sigmaY = 0);

void plotHistogram(const cv::Mat& src);
cv::Mat histogramEqualization(const cv::Mat& src);

#endif // IMAGEFILTERS_H
