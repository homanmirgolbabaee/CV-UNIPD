#include "PerformanceEvaluator.h"

float PerformanceEvaluator::calculateMAP(const std::vector<cv::RotatedRect>& detectedSpaces, const std::string& groundTruthXml) {
    std::vector<ParkingSpace> groundTruthSpaces = XMLParser::parseXML(groundTruthXml);
    std::vector<bool> truePositives = calculateTruePositives(detectedSpaces, groundTruthSpaces, 0.5f);
    
    int totalPositives = 0;
    float averagePrecision = 0.0f;
    
    for (size_t i = 0; i < truePositives.size(); ++i) {
        if (truePositives[i]) {
            totalPositives++;
            float precision = static_cast<float>(totalPositives) / (i + 1);
            averagePrecision += precision;
        }
    }
    
    return averagePrecision / groundTruthSpaces.size();
}

float PerformanceEvaluator::calculateMIoU(const cv::Mat& segmentationResult, const cv::Mat& groundTruthMask) {
    cv::Mat intersection, union_;
    cv::bitwise_and(segmentationResult, groundTruthMask, intersection);
    cv::bitwise_or(segmentationResult, groundTruthMask, union_);
    
    float iou = static_cast<float>(cv::countNonZero(intersection)) / cv::countNonZero(union_);
    return iou;
}

float PerformanceEvaluator::calculateIoU(const cv::RotatedRect& rect1, const cv::RotatedRect& rect2) {
    cv::Mat mask1 = cv::Mat::zeros(1000, 1000, CV_8UC1);
    cv::Mat mask2 = cv::Mat::zeros(1000, 1000, CV_8UC1);
    
    cv::Point2f vertices1[4], vertices2[4];
    rect1.points(vertices1);
    rect2.points(vertices2);
    
    std::vector<cv::Point> contour1(vertices1, vertices1 + 4);
    std::vector<cv::Point> contour2(vertices2, vertices2 + 4);
    
    cv::fillPoly(mask1, std::vector<std::vector<cv::Point>>{contour1}, 255);
    cv::fillPoly(mask2, std::vector<std::vector<cv::Point>>{contour2}, 255);
    
    cv::Mat intersection, union_;
    cv::bitwise_and(mask1, mask2, intersection);
    cv::bitwise_or(mask1, mask2, union_);
    
    return static_cast<float>(cv::countNonZero(intersection)) / cv::countNonZero(union_);
}

std::vector<bool> PerformanceEvaluator::calculateTruePositives(const std::vector<cv::RotatedRect>& detectedSpaces, const std::vector<ParkingSpace>& groundTruth, float iouThreshold) {
    std::vector<bool> truePositives(detectedSpaces.size(), false);
    std::vector<bool> matched(groundTruth.size(), false);
    
    for (size_t i = 0; i < detectedSpaces.size(); ++i) {
        float maxIoU = 0.0f;
        int bestMatch = -1;
        
        for (size_t j = 0; j < groundTruth.size(); ++j) {
            if (!matched[j]) {
                float iou = calculateIoU(detectedSpaces[i], groundTruth[j].rect);
                if (iou > maxIoU) {
                    maxIoU = iou;
                    bestMatch = j;
                }
            }
        }
        
        if (maxIoU >= iouThreshold) {
            truePositives[i] = true;
            if (bestMatch >= 0) {
                matched[bestMatch] = true;
            }
        }
    }
    
    return truePositives;
}