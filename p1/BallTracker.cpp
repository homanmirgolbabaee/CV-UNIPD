#include "BallTracker.h"

BallTracker::BallTracker() {}

void BallTracker::initTrackers(const cv::Mat& frame, const std::vector<Ball>& balls) {
    trackers.clear();
    trackedBalls = balls;

    for (const auto& ball : balls) {
        cv::Ptr<cv::Tracker> tracker = cv::TrackerKCF::create();
        cv::Rect2d roi(ball.center.x - ball.radius, ball.center.y - ball.radius, 
                       ball.radius * 2, ball.radius * 2);
        tracker->init(frame, roi);
        trackers.push_back(tracker);
    }
}

std::vector<Ball> BallTracker::updateTrackers(const cv::Mat& frame) {
    std::vector<Ball> updatedBalls;

    for (size_t i = 0; i < trackers.size(); ++i) {
        cv::Rect2d bbox;
        bool ok = trackers[i]->update(frame, bbox);

        if (ok) {
            Ball updatedBall = trackedBalls[i];
            updatedBall.center = cv::Point2f(bbox.x + bbox.width / 2, bbox.y + bbox.height / 2);
            updatedBall.radius = (bbox.width + bbox.height) / 4;
            updatedBalls.push_back(updatedBall);
        }
    }

    return updatedBalls;
}
