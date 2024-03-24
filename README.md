# CV-UNIPD
#labs & #lab_reports

g++ task1.cpp -o task -I/usr/local/include/opencv4 -lopencv_highgui -lopencv_core -lopencv_imgcodecs -lopencv_imgproc


g++ OpenImg.cpp -o OpenImg -I/usr/local/include/opencv4 -lopencv_highgui -lopencv_core -lopencv_imgcodecs


g++ -o task2 task2.cpp ImageFilters.cpp `pkg-config --cflags --libs opencv4`

Cv submissions 23-24 
