#include <opencv2/opencv.hpp>

int main() {
    // Create the first image (vertical gradient)
    cv::Mat image1(256, 256, CV_8UC1);
    for (int row = 0; row < image1.rows; row++) {
        for (int col = 0; col < image1.cols; col++) {
            image1.at<uchar>(row, col) = static_cast<uchar>(row);
        }
    }

    // Create the second image (horizontal gradient)
    cv::Mat image2(256, 256, CV_8UC1);
    for (int row = 0; row < image2.rows; row++) {
        for (int col = 0; col < image2.cols; col++) {
            image2.at<uchar>(row, col) = static_cast<uchar>(col);
        }
    }

    // Show the images on screen
    cv::imshow("Vertical Gradient", image1);
    cv::imshow("Horizontal Gradient", image2);
    cv::waitKey(0);

    // Create the third image (chessboard with squares of size 20 pixels)
    cv::Mat image3(300, 300, CV_8UC1);
    for (int row = 0; row < image3.rows; row++) {
        for (int col = 0; col < image3.cols; col++) {
            int squareSize = 20;
            int squareRow = row / squareSize;
            int squareCol = col / squareSize;
            if ((squareRow + squareCol) % 2 == 0) {
                image3.at<uchar>(row, col) = 255;
            } else {
                image3.at<uchar>(row, col) = 0;
            }
        }
    }

    // Create the fourth image (chessboard with squares of size 50 pixels)
    cv::Mat image4(300, 300, CV_8UC1);
    for (int row = 0; row < image4.rows; row++) {
        for (int col = 0; col < image4.cols; col++) {
            int squareSize = 50;
            int squareRow = row / squareSize;
            int squareCol = col / squareSize;
            if ((squareRow + squareCol) % 2 == 0) {
                image4.at<uchar>(row, col) = 255;
            } else {
                image4.at<uchar>(row, col) = 0;
            }
        }
    }

    // Show the images on screen
    cv::imshow("Chessboard (20 pixels)", image3);
    cv::imshow("Chessboard (50 pixels)", image4);
    cv::waitKey(0);

    return 0;
}
