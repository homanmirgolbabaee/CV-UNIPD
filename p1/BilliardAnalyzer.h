#ifndef BILLIARDANALYZER_H
#define BILLIARDANALYZER_H

#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <string>
#include <vector>
#include "BallTracker.h"

class BilliardAnalyzer {
public:
    BilliardAnalyzer(const cv::Mat& inputImage);
    ~BilliardAnalyzer();

    std::vector<cv::Point2f> detectTableEdges();
    void drawBoundingBox(const std::vector<cv::Point2f>& tablePoints, cv::Mat& image);
    std::tuple<std::vector<cv::Point2f>, std::vector<float>> locateBalls(cv::Mat& image, const std::vector<cv::Point2f>& tablePoints);
    void classifyBalls(const cv::Mat& image, const std::vector<cv::Point2f>& ballCenters, const std::vector<float>& ballRadii,
                       cv::Point2f& whitePt, float& whiteRadius, cv::Point2f& blackPt, float& blackRadius,
                       std::vector<cv::Point2f>& stripedBalls, std::vector<float>& stripedRadii,
                       std::vector<cv::Point2f>& solidBalls, std::vector<float>& solidRadii);

    void setImage(const cv::Mat& inputImage) {
        image = inputImage.clone();
    }

    void setTablePoints(const std::vector<cv::Point2f>& points) { m_tablePoints = points; }
    const std::vector<cv::Point2f>& getTablePoints() const { return m_tablePoints; }
    void initializeTracking(const cv::Mat& frame);
    std::vector<Ball> trackBalls(const cv::Mat& frame);

private:
    cv::Mat image;
    cv::Mat tableMask;
    std::vector<cv::Vec4i> tableEdges;
    std::vector<cv::Rect> ballPositions;
    std::vector<cv::Point2f> m_tablePoints;  // Renamed to m_tablePoints

    cv::Mat preprocessImageTable(const cv::Mat& img, int erosionCount = 3, int dilationCount = 3);
    cv::Mat preprocessImageBalls(const cv::Mat& img, int erosionCount = 3, int dilationCount = 3);
    cv::Point2f getIntersection(cv::Vec2f line1, cv::Vec2f line2);

    BallTracker ballTracker;
    std::vector<Ball> currentBalls;
    Ball refineBallPosition(const cv::Mat& frame, const Ball& ball);

};

#endif // BILLIARDANALYZER_H
