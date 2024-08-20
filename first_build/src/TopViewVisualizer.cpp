#include "TopViewVisualizer.h"

TopViewVisualizer::TopViewVisualizer(int width, int height) {
    topView = cv::Mat::zeros(height, width, CV_8UC3);
}

void TopViewVisualizer::updateTopView(const std::vector<cv::RotatedRect>& spaces, const std::vector<bool>& occupancy) {
    topView = cv::Mat::zeros(topView.size(), CV_8UC3);
    
    for (size_t i = 0; i < spaces.size(); ++i) {
        cv::Point2f vertices[4];
        spaces[i].points(vertices);
        
        std::vector<cv::Point> contour;
        for (int j = 0; j < 4; ++j) {
            contour.push_back(mapToTopView(vertices[j]));
        }
        
        cv::Scalar color = occupancy[i] ? cv::Scalar(0, 0, 255) : cv::Scalar(255, 0, 0);
        cv::fillConvexPoly(topView, contour, color);
    }
}

cv::Mat TopViewVisualizer::getTopView() const {
    return topView;
}

cv::Point TopViewVisualizer::mapToTopView(const cv::Point2f& imagePoint) {
    // This is a simplified mapping. You may need to adjust this based on your specific camera setup.
    float scale = 0.5f;
    return cv::Point(static_cast<int>(imagePoint.x * scale), static_cast<int>(imagePoint.y * scale));
}