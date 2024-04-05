#include <opencv2/opencv.hpp>
#include <iostream>

void onMouse(int event, int x, int y, int flags, void* userdata) {
    if (event == cv::EVENT_LBUTTONDOWN) {
        cv::Mat* image = static_cast<cv::Mat*>(userdata);
        if (x >= 0 && x < image->cols && y >= 0 && y < image->rows) {
            int sumB = 0, sumG = 0, sumR = 0;
            int neighborhoodSize = 9;
            int startX = std::max(0, x - neighborhoodSize / 2);
            int endX = std::min(image->cols - 1, x + neighborhoodSize / 2);
            int startY = std::max(0, y - neighborhoodSize / 2);
            int endY = std::min(image->rows - 1, y + neighborhoodSize / 2);
            for (int j = startY; j <= endY; ++j) {
                for (int i = startX; i <= endX; ++i) {
                    cv::Vec3b color = image->at<cv::Vec3b>(j, i);
                    sumB += color[0];
                    sumG += color[1];
                    sumR += color[2];
                }
            }
            int numPixels = (endX - startX + 1) * (endY - startY + 1);
            int meanB = sumB / numPixels;
            int meanG = sumG / numPixels;
            int meanR = sumR / numPixels;
            std::cout << "Mean Color: B=" << meanB << ", G=" << meanG << ", R=" << meanR << std::endl;
        }
    }
}

int main() {
    cv::Mat image = cv::imread("robocup.jpg");
    if (image.empty()) {
        std::cerr << "Error: Unable to load image." << std::endl;
        return 1;
    }
    cv::imshow("Image", image);
    cv::setMouseCallback("Image", onMouse, &image);
    cv::waitKey(0);
    cv::destroyAllWindows();
    return 0;
}
