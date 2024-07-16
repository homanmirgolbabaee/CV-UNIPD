#ifndef BALLTRACKER_H
#define BALLTRACKER_H

#include <opencv2/opencv.hpp>
#include <vector>
#include "BilliardTable.h"

class BallTracker {
public:
    BallTracker();
    void initTrackers(const cv::Mat& frame, const std::vector<Ball>& balls);
    std::vector<Ball> updateTrackers(const cv::Mat& frame);

private:
    std::vector<cv::Ptr<cv::Tracker>> trackers;
    std::vector<Ball> trackedBalls;
};

#endif // BALLTRACKER_H
