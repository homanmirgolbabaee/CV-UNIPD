#ifndef IMAGEFILTERS_H
#define IMAGEFILTERS_H

#include <opencv2/opencv.hpp>

class ImageFilters {
public:
    static cv::Mat applyMaxFilter(const cv::Mat &src, int kernelSize);
    static cv::Mat applyMinFilter(const cv::Mat &src, int kernelSize);
    static cv::Mat applyMedianFilter(const cv::Mat &src, int kernelSize);
};

#endif // IMAGEFILTERS_H
