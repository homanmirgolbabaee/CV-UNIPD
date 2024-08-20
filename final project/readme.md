deadline : 14/07/2024 - 14 july 2024

'''bash
dataset : https://drive.google.com/drive/folders/1dzNrhDpc2DXRqmQgbO5l2WMjzfhMdxVn
'''
D\mirghom49577@dei-cv-002:~/Desktop/parking-lot-management/build$ make
[ 12%] Building CXX object CMakeFiles/ParkingLotManagement.dir/src/main.cpp.o
[ 25%] Building CXX object CMakeFiles/ParkingLotManagement.dir/src/ParkingSpaceDetector.cpp.o
[ 37%] Building CXX object CMakeFiles/ParkingLotManagement.dir/src/OccupancyClassifier.cpp.o
[ 50%] Building CXX object CMakeFiles/ParkingLotManagement.dir/src/CarSegmentation.cpp.o
[ 62%] Building CXX object CMakeFiles/ParkingLotManagement.dir/src/TopViewVisualizer.cpp.o
/home/local/mirghom49577/Desktop/parking-lot-management/src/TopViewVisualizer.cpp: In member function ‘void TopViewVisualizer::updateTopView(const std::vector<cv::RotatedRect>&, const std::vector<bool>&)’:
/home/local/mirghom49577/Desktop/parking-lot-management/src/TopViewVisualizer.cpp:19:27: error: no matching function for call to ‘fillConvexPoly(cv::Mat&, cv::Point2f [4], int, cv::Scalar&)’
   19 |         cv::fillConvexPoly(topView, vertices, 4, color);
      |         ~~~~~~~~~~~~~~~~~~^~~~~~~~~~~~~~~~~~~~~~~~~~~~~
In file included from /usr/local/include/opencv4/opencv2/opencv.hpp:74,
                 from /home/local/mirghom49577/Desktop/parking-lot-management/src/TopViewVisualizer.h:4,
                 from /home/local/mirghom49577/Desktop/parking-lot-management/src/TopViewVisualizer.cpp:1:
/usr/local/include/opencv4/opencv2/imgproc.hpp:4514:17: note: candidate: ‘void cv::fillConvexPoly(cv::InputOutputArray, const Point*, int, const Scalar&, int, int)’
 4514 | CV_EXPORTS void fillConvexPoly(InputOutputArray img, const Point* pts, int npts,
      |                 ^~~~~~~~~~~~~~
/usr/local/include/opencv4/opencv2/imgproc.hpp:4514:67: note:   no known conversion for argument 2 from ‘cv::Point2f [4]’ {aka ‘cv::Point_<float> [4]’} to ‘const Point*’ {aka ‘const cv::Point_<int>*’}
 4514 | ORTS void fillConvexPoly(InputOutputArray img, const Point* pts, int npts,
      |                                                ~~~~~~~~~~~~~^~~

/usr/local/include/opencv4/opencv2/imgproc.hpp:4531:19: note: candidate: ‘void cv::fillConvexPoly(cv::InputOutputArray, cv::InputArray, const Scalar&, int, int)’
 4531 | CV_EXPORTS_W void fillConvexPoly(InputOutputArray img, InputArray points,
      |                   ^~~~~~~~~~~~~~
/usr/local/include/opencv4/opencv2/imgproc.hpp:4531:67: note:   no known conversion for argument 2 from ‘cv::Point2f [4]’ {aka ‘cv::Point_<float> [4]’} to ‘cv::InputArray’ {aka ‘const cv::_InputArray&’}
 4531 | _EXPORTS_W void fillConvexPoly(InputOutputArray img, InputArray points,
      |                                                      ~~~~~~~~~~~^~~~~~

make[2]: *** [CMakeFiles/ParkingLotManagement.dir/build.make:132: CMakeFiles/ParkingLotManagement.dir/src/TopViewVisualizer.cpp.o] Error 1
make[1]: *** [CMakeFiles/Makefile2:83: CMakeFiles/ParkingLotManagement.dir/all] Error 2
make: *** [Makefile:91: all] Error 2
AD\mirghom49577@dei-cv-002:~/Desktop/parking-lot-management/build$ 
