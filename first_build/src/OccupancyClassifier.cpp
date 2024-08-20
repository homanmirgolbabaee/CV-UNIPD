#include "OccupancyClassifier.h"

OccupancyClassifier::OccupancyClassifier() {
    svm = cv::ml::SVM::create();
    svm->setType(cv::ml::SVM::C_SVC);
    svm->setKernel(cv::ml::SVM::RBF);
}

void OccupancyClassifier::train(const std::vector<cv::Mat>& occupiedSamples, const std::vector<cv::Mat>& emptySamples) {
    cv::Mat trainingData, labels;
    
    for (const auto& sample : occupiedSamples) {
        trainingData.push_back(extractFeatures(sample));
        labels.push_back(1);
    }
    
    for (const auto& sample : emptySamples) {
        trainingData.push_back(extractFeatures(sample));
        labels.push_back(0);
    }
    
    svm->train(trainingData, cv::ml::ROW_SAMPLE, labels);
}

bool OccupancyClassifier::isOccupied(const cv::Mat& parkingSpaceROI) {
    cv::Mat features = extractFeatures(parkingSpaceROI);
    float response = svm->predict(features);
    return response > 0.5;
}

cv::Mat OccupancyClassifier::extractFeatures(const cv::Mat& roi) {
    cv::Mat resized, features;
    cv::resize(roi, resized, cv::Size(64, 128));
    cv::HOGDescriptor hog;
    std::vector<float> descriptors;
    hog.compute(resized, descriptors);
    features = cv::Mat(descriptors).t();
    return features;
}