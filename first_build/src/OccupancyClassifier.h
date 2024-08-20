#ifndef OCCUPANCY_CLASSIFIER_H
#define OCCUPANCY_CLASSIFIER_H

#include <opencv2/opencv.hpp>
#include <vector>

class OccupancyClassifier {
public:
    OccupancyClassifier();
    void train(const std::vector<cv::Mat>& occupiedSamples, const std::vector<cv::Mat>& emptySamples);
    bool isOccupied(const cv::Mat& parkingSpaceROI);

private:
    cv::Ptr<cv::ml::SVM> svm;
    cv::Mat extractFeatures(const cv::Mat& roi);
};

#endif // OCCUPANCY_CLASSIFIER_H