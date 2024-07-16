#include "VideoProcessor.h"
#include "BilliardAnalyzer.h"
#include "BilliardTableTopView.h"
#include "BilliardTable.h"
#include <opencv2/highgui.hpp>
#include <iostream>

int main(int argc, char** argv) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <video_path>" << std::endl;
        return -1;
    }

    std::string videoPath = argv[1];
    VideoProcessor vp(videoPath);

    if (!vp.isOpened()) {
        std::cerr << "Failed to open video file." << std::endl;
        return -1;
    }

    cv::Mat frame;
    int count = 0;
    std::vector<cv::Point2f> tablePoints;
    BilliardAnalyzer analyzer(cv::Mat());

    while (true) {
        frame = vp.getNextFrame();

        if (frame.empty()) {
            break; 
        }

        cv::Mat boundingBoxFrame = frame.clone();
        analyzer.setImage(boundingBoxFrame);
        
        if (count == 0) {
            analyzer.detectTableEdges();
            analyzer.initializeTracking(boundingBoxFrame);
        } else {
            std::vector<Ball> trackedBalls = analyzer.trackBalls(boundingBoxFrame);
            
            // Draw tracked balls
            for (const auto& ball : trackedBalls) {
                cv::Scalar color;
                switch (ball.type) {
                    case CUE: color = cv::Scalar(255, 255, 255); break;
                    case EIGHT: color = cv::Scalar(0, 0, 0); break;
                    case STRIPED: color = cv::Scalar(0, 0, 255); break;
                    case SOLID: color = cv::Scalar(255, 0, 0); break;
                }
                cv::circle(boundingBoxFrame, ball.center, cvRound(ball.radius), color, -1);
            }
        }

        analyzer.drawBoundingBox(tablePoints, boundingBoxFrame);

        cv::imshow("Frame", boundingBoxFrame);

        // Original ball detection and classification (for comparison)
        std::vector<cv::Point2f> ballCenters;
        std::vector<float> ballRadii;
        std::tie(ballCenters, ballRadii) = analyzer.locateBalls(boundingBoxFrame, tablePoints);

        cv::Point2f whitePt, blackPt;
        float whiteRadius, blackRadius;
        std::vector<cv::Point2f> stripedBalls, solidBalls;
        std::vector<float> stripedRadii, solidRadii;

        analyzer.classifyBalls(boundingBoxFrame, ballCenters, ballRadii,
                               whitePt, whiteRadius, blackPt, blackRadius,
                               stripedBalls, stripedRadii,
                               solidBalls, solidRadii);

        cv::Mat segmentationFrame = frame.clone();
        BilliardTable table(tablePoints, segmentationFrame);

        table.drawTable();

        std::vector<Ball> balls = {
            { whitePt, whiteRadius, CUE },
            { blackPt, blackRadius, EIGHT }
        };

        for (size_t i = 0; i < stripedBalls.size(); i++) {
            balls.push_back({ stripedBalls[i], stripedRadii[i], STRIPED });
        }

        for (size_t i = 0; i < solidBalls.size(); i++) {
            balls.push_back({ solidBalls[i], solidRadii[i], SOLID });
        }

        table.drawBalls(balls);

        cv::imshow("Pool Table", segmentationFrame);

        BilliardTableTopView topViewTransformer;
        topViewTransformer.setTableCorners(tablePoints);

        float width = cv::norm(tablePoints[0] - tablePoints[1]);  
        float height = cv::norm(tablePoints[0] - tablePoints[2]); 

        cv::Size outputSize(static_cast<int>(width), static_cast<int>(height));

        cv::Mat topViewImage = topViewTransformer.getTopView(outputSize);
        cv::imshow("Top View Image", topViewImage);
        cv::imshow("Tracked Balls", boundingBoxFrame);

        int key = cv::waitKey(30);
        if (key == 27) // ESC key
            break;

        count++;
    }

    return 0;
}
