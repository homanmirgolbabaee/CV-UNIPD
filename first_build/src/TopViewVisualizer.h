#ifndef TOP_VIEW_VISUALIZER_H
#define TOP_VIEW_VISUALIZER_H

#include <opencv2/opencv.hpp>
#include <vector>

class TopViewVisualizer {
public:
    TopViewVisualizer(int width, int height);
    void updateTopView(const std::vector<cv::RotatedRect>& spaces, const std::vector<bool>& occupancy);
    cv::Mat getTopView() const;

private:
    cv::Mat topView;
    cv::Point mapToTopView(const cv::Point2f& imagePoint);
};

#endif // TOP_VIEW_VISUALIZER_H