
#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/calib3d.hpp>
using namespace std;
using namespace cv;
// global variables ///////////////////////////////////////////////////////////////////////////////
const cv::Scalar SCALAR_BLACK = cv::Scalar(0.0, 0.0, 0.0);
const cv::Scalar SCALAR_WHITE = cv::Scalar(255.0, 255.0, 255.0);
const cv::Scalar SCALAR_BLUE = cv::Scalar(255.0, 0.0, 0.0);
const cv::Scalar SCALAR_GREEN = cv::Scalar(0.0, 200.0, 0.0);
const cv::Scalar SCALAR_RED = cv::Scalar(0.0, 0.0, 255.0);
const Size chessboardDimension = Size(7 , 7);


void matrix_rotation();
void detectchessboard();
int find_move(cv::Point );
void motion_detect(VideoCapture );
bool Detect_moves(Mat imgFrame1,Mat imgFrame2,cv::Point &cent);
void chess_read();
void calibration();
void crop(int& xx,int& yy,int& width, int& height);