#ifndef PERFORMANCE_EVALUATOR_H
#define PERFORMANCE_EVALUATOR_H

#include <opencv2/opencv.hpp>
#include <vector>
#include <string>
#include "XMLParser.h"

class PerformanceEvaluator {
public:
    float calculateMAP(const std::vector<cv::RotatedRect>& detectedSpaces, const std::string& groundTruthXml);
    float calculateMIoU(const cv::Mat& segmentationResult, const cv::Mat& groundTruthMask);

private:
    float calculateIoU(const cv::RotatedRect& rect1, const cv::RotatedRect& rect2);
    std::vector<bool> calculateTruePositives(const std::vector<cv::RotatedRect>& detectedSpaces, const std::vector<ParkingSpace>& groundTruth, float iouThreshold);
};

#endif // PERFORMANCE_EVALUATOR_H