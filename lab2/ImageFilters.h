#ifndef IMAGEFILTERS_H
#define IMAGEFILTERS_H

#include <opencv2/opencv.hpp>
#include <string>

// Declare the filtering functions
cv::Mat maxFilter(const cv::Mat& src, int kernelSize);
cv::Mat minFilter(const cv::Mat& src, int kernelSize);

// Declare the utility function for showing images in a resized window
void showResizedWindow(const std::string& winname, const cv::Mat& img, int width = 200, int height = 200);

#endif // IMAGEFILTERS_H
