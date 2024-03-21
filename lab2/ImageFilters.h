// ImageFilters.h
#ifndef IMAGEFILTERS_H
#define IMAGEFILTERS_H

#include <opencv2/opencv.hpp>

void applyMaxFilter(const cv::Mat& src, cv::Mat& dst, int kernelSize);
void applyMinFilter(const cv::Mat& src, cv::Mat& dst, int kernelSize);

#endif // IMAGEFILTERS_H
