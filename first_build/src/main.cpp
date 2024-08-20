#include "ParkingSpaceDetector.h"
#include "OccupancyClassifier.h"
#include "CarSegmentation.h"
#include "TopViewVisualizer.h"
#include "PerformanceEvaluator.h"
#include "XMLParser.h"
#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>
#include <vector>
#include <filesystem>

namespace fs = std::filesystem;

std::vector<cv::RotatedRect> processSequence0(ParkingSpaceDetector& detector, OccupancyClassifier& classifier, const std::string& sequence0Path) {
    std::vector<cv::RotatedRect> parkingSpaces;
    std::vector<cv::Mat> occupiedSamples, emptySamples;

    for (const auto& entry : fs::directory_iterator(sequence0Path + "/frames")) {
        cv::Mat frame = cv::imread(entry.path().string());
        std::vector<cv::RotatedRect> spaces = detector.detectParkingSpaces(frame);
        parkingSpaces.insert(parkingSpaces.end(), spaces.begin(), spaces.end());

        std::string xmlPath = sequence0Path + "/bounding_boxes/" + entry.path().stem().string() + ".xml";
        std::vector<ParkingSpace> groundTruth = XMLParser::parseXML(xmlPath);

        for (const auto& space : groundTruth) {
            cv::Mat roi = frame(space.rect.boundingRect());
            if (space.occupied) {
                occupiedSamples.push_back(roi);
            } else {
                emptySamples.push_back(roi);
            }
        }
    }

    classifier.train(occupiedSamples, emptySamples);
    return parkingSpaces;
}

void processSequence(const std::string& sequencePath, 
                     const std::vector<cv::RotatedRect>& parkingSpaces,
                     OccupancyClassifier& classifier,
                     CarSegmentation& segmentation,
                     TopViewVisualizer& visualizer,
                     PerformanceEvaluator& evaluator) {
    for (const auto& entry : fs::directory_iterator(sequencePath + "/frames")) {
        cv::Mat frame = cv::imread(entry.path().string());
        
        // Classify occupancy
        std::vector<bool> occupancy;
        for (const auto& space : parkingSpaces) {
            cv::Mat roi = frame(space.boundingRect());
            occupancy.push_back(classifier.isOccupied(roi));
        }
        
        // Segment cars
        cv::Mat carSegmentation = segmentation.segmentCars(frame, parkingSpaces);
        
        // Update top view
        visualizer.updateTopView(parkingSpaces, occupancy);
        
        // Evaluate performance
        std::string xmlPath = sequencePath + "/bounding_boxes/" + entry.path().stem().string() + ".xml";
        float mAP = evaluator.calculateMAP(parkingSpaces, xmlPath);
        
        std::string maskPath = sequencePath + "/masks/" + entry.path().stem().string() + ".png";
        if (fs::exists(maskPath)) {
            cv::Mat groundTruthMask = cv::imread(maskPath, cv::IMREAD_GRAYSCALE);
            float mIoU = evaluator.calculateMIoU(carSegmentation, groundTruthMask);
            
            cv::imwrite("results/car_segmentation/" + entry.path().filename().string(), carSegmentation);
            std::cout << "Frame: " << entry.path().filename() << ", mAP: " << mAP << ", mIoU: " << mIoU << std::endl;
        } else {
            std::cout << "Frame: " << entry.path().filename() << ", mAP: " << mAP << " (No segmentation mask available)" << std::endl;
        }
        
        cv::imwrite("results/top_view/" + entry.path().filename().string(), visualizer.getTopView());
    }
}

int main() {
    ParkingSpaceDetector detector;
    OccupancyClassifier classifier;
    CarSegmentation segmentation;
    TopViewVisualizer visualizer(800, 600);
    PerformanceEvaluator evaluator;
    
    // Process sequence0 to detect parking spaces and train the classifier
    std::vector<cv::RotatedRect> parkingSpaces = processSequence0(detector, classifier, "data/sequence0");
    
    // Process other sequences
    for (int i = 1; i <= 5; ++i) {
        std::string sequencePath = "data/sequence" + std::to_string(i);
        processSequence(sequencePath, parkingSpaces, classifier, segmentation, visualizer, evaluator);
    }
    
    return 0;
}