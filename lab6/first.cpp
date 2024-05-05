#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
using namespace cv;
using namespace std;

// Declare functions before main
Ptr<Feature2D> createFeatureDetector(const string& type);
Ptr<DescriptorMatcher> createMatcher(const string& type);
vector<DMatch> filterMatchesByRatio(vector<vector<DMatch>>& knnMatches, float ratio_thresh = 0.75);
void analyzeMatches(const vector<DMatch>& good_matches, const vector<KeyPoint>& keypoints1, const vector<KeyPoint>& keypoints2);

int main(int argc, char** argv) {
    if (argc < 3) {
        cout << "Usage: ./feature_matching <image1_path> <image2_path> [feature_detector] [matcher_type]" << endl;
        return -1;
    }

    string feature_detector = (argc > 3) ? argv[3] : "ORB";
    string matcher_type = (argc > 4) ? argv[4] : "BRUTEFORCE_HAMMING";
    string descriptorType = getDescriptorType(feature_detector);    
    Mat image1 = imread(argv[1], IMREAD_GRAYSCALE);
    Mat image2 = imread(argv[2], IMREAD_GRAYSCALE);
    if (image1.empty() || image2.empty()) {
        cout << "Could not open or find the images!" << endl;
        return -1;
    }

    Ptr<Feature2D> detector = createFeatureDetector(feature_detector);
    vector<KeyPoint> keypoints1, keypoints2;
    Mat descriptors1, descriptors2;
    detector->detectAndCompute(image1, Mat(), keypoints1, descriptors1);
    detector->detectAndCompute(image2, Mat(), keypoints2, descriptors2);

    Ptr<DescriptorMatcher> matcher = createMatcher(matcher_type);
    vector<vector<DMatch>> knnMatches;
    matcher->knnMatch(descriptors1, descriptors2, knnMatches, 2);

    vector<DMatch> good_matches = filterMatchesByRatio(knnMatches);
    analyzeMatches(good_matches, keypoints1, keypoints2);

    Mat img_matches;
    drawMatches(image1, keypoints1, image2, keypoints2, good_matches, img_matches);

    double similarity = static_cast<double>(good_matches.size()) / knnMatches.size();
    if (similarity > 0.8) {
        cout << "The two images have similar content." << endl;
    } else if (similarity > 0.5) {
        cout << "The two images have similar content processed by some strong transformation." << endl;
    } else {
        cout << "The two images have different content." << endl;
    }

    namedWindow("Matches", WINDOW_NORMAL);
    imshow("Matches", img_matches);
    resizeWindow("Matches", 800, 600);
    waitKey(0);

    return 0;
}
string getDescriptorType(const string& detectorType) {
    if (detectorType == "SIFT" || detectorType == "SURF") return "float";
    // Other detectors like ORB, BRISK, AKAZE generate binary descriptors
    return "binary";
}
Ptr<Feature2D> createFeatureDetector(const string& type) {
    if (type == "SIFT") return SIFT::create();
    else if (type == "ORB") return ORB::create();
    else if (type == "AKAZE") return AKAZE::create();
    else if (type == "BRISK") return BRISK::create();
    // Add more detectors as needed
    else return ORB::create();  // Default
}

Ptr<DescriptorMatcher> createMatcher(const string& type, const string& descriptorType) {
    if (descriptorType == "binary") {
        if (type == "FLANN") return makePtr<FlannBasedMatcher>(new flann::LshIndexParams(20, 10, 2));
        else return DescriptorMatcher::create(DescriptorMatcher::BRUTEFORCE_HAMMING);
    }
    else {
        if (type == "FLANN") return DescriptorMatcher::create(DescriptorMatcher::FLANNBASED);
        else return DescriptorMatcher::create(DescriptorMatcher::BRUTEFORCE);
    }
}

vector<DMatch> filterMatchesByRatio(vector<vector<DMatch>>& knnMatches, float ratio_thresh) {
    vector<DMatch> good_matches;
    for (size_t i = 0; i < knnMatches.size(); i++) {
        if (knnMatches[i][0].distance < ratio_thresh * knnMatches[i][1].distance) {
            good_matches.push_back(knnMatches[i][0]);
        }
    }
    return good_matches;
}

void analyzeMatches(const vector<DMatch>& good_matches, const vector<KeyPoint>& keypoints1, const vector<KeyPoint>& keypoints2) {
    vector<Point2f> points1, points2;
    for (const DMatch& match : good_matches) {
        points1.push_back(keypoints1[match.queryIdx].pt);
        points2.push_back(keypoints2[match.trainIdx].pt);
    }

    Mat homography = findHomography(points1, points2, RANSAC);
    if (!homography.empty()) {
        cout << "Similar content with possible geometric transformation." << endl;
    } else {
        cout << "Content is different or transformation is too strong to detect." << endl;
    }
}
