//
//  main.cpp
//  ProcessImage
//
//  Created by Weiwei Chen on 7/21/15.
//  Copyright © 2015 Weiwei Chen. All rights reserved.
//

#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <opencv2/imgcodecs.hpp>
#include <opencv2/videoio/videoio.hpp>
//#include "EdgeScan.hpp"
#include "ShapeGen.hpp"
#include "ShapeDiff.hpp"
#include "ShapeLearning.hpp"
#include "BodyModel.hpp"


#include <iostream>
#include <stdio.h>

using namespace std;
using namespace cv;

Mat backgroundImg;
Mat currentImg;
Mat diffImg;
Mat foregroundMask;
char window_name1[] = "Unprocessed Image";
char window_name2[] = "Processed Image";
char trackbar_type[] =
    "Type: \n 0: Binary \n 1: Binary Inverted \n 2: Truncate \n 3: To Zero \n "
    "4: To Zero Inverted";
char trackbar_value[] = "Value";
char window_name[] = "Threshold Demo";
Mat src, src_gray, dst, detected_edges, contours;
Mat backgroundImg_blur, currentImg_blur;

int threshold_value = 100;
int threshold_type = 3;
int const max_BINARY_value = 255;

/// Function headers
void Threshold_Demo(int, void*);

int PreProcessing(int argc, char** argv);

// Mat src, src_gray;
// Mat dst, detected_edges;

int edgeThresh = 1;
int lowThreshold = 25;
int const max_lowThreshold = 100;
double ratio = 3.0;
int kernel_size = 3;
/// char* window_name = "Edge Map";


int main(int argc, char** argv) {
//    PreProcessing( argc, argv) ;
//    return 0;
    src = imread("/Users/weiweich/Documents/M2M/ProcessImage/ProcessImage/build/Debug/diffImg.jpg");
    execute(&src);
    return 0;
}
int toss( int argc, char** argv )
{
    
    src = imread("/Users/weiweich/Documents/M2M/ProcessImage/ProcessImage/build/Debug/canny_output.jpg", 0);
    
    if (!src.data) {
        return -1;
    }
    
    /// Create a matrix of the same type and size as src (for dst)
    dst.create(src.size(), src.type());
    vector<Point> points = {Point(500, 500), Point(600, 600), Point(500, 710), Point(400, 600)};
    
    vector<Point> output;
    approxPolyDP(Mat(points), output, 1.0, true);
    
    for (vector<Point>::iterator it = output.begin() ; it != output.end(); ++it) {
        Point p = *it;
        cout  << p.x <<"," << p.y << endl;
    }
    
    /// Create Window
    namedWindow( "Source", CV_WINDOW_AUTOSIZE );
    imshow( "Source", dst );
    
    
    waitKey(0);
    return(0);
}

/**
 * @function CannyThreshold
 * @brief Trackbar callback - Canny thresholds input with a ratio 1:3
 */
void CannyThreshold(int, void*) {
  /// Reduce noise with a kernel 3x3
  blur(src_gray, detected_edges, Size(3, 3));

  /// Canny detector
  Canny(detected_edges, detected_edges, lowThreshold, lowThreshold * 3.0,
        kernel_size);

  /// Using Canny's output as a mask, we display our result
  dst = Scalar::all(0);

  src.copyTo(dst, detected_edges);
    imwrite("detected_edges.jpg", detected_edges);

  //imshow(window_name, dst);
}


int less(int argc, char** argv) {
    

  /// Load an image
    //argv[1]
  src = imread("/Users/weiweich/Documents/M2M/ProcessImage/ProcessImage/build/Debug/canny_output.jpg", 0);

  if (!src.data) {
    return -1;
  }
    
    //edge_scan(&src);
    return 0;

  /// Create a matrix of the same type and size as src (for dst)
  dst.create(src.size(), src.type());

  /// Convert the image to grayscale
  cvtColor(src, src_gray, CV_BGR2GRAY);

  /// Create a window
  namedWindow(window_name, CV_WINDOW_AUTOSIZE);

  /// Create a Trackbar for user to enter threshold
//  createTrackbar("Min Threshold:", window_name, &lowThreshold, max_lowThreshold,
//                 CannyThreshold);
    
//    //(const String& trackbarname, const String& winname,
//    int* value, int count,
//    TrackbarCallback onChange = 0,
//    void* userdata = 0);

  /// Show the image
  CannyThreshold(0, 0);

  /// Wait until user exit program by pressing a key
  waitKey(0);

  return 0;
}

int thresh = 20;
int max_thresh = 255;
RNG rng(12345);

/// Function header
void thresh_callback(int, void* );

/** @function main */
int more( int argc, char** argv )
{
    //PreProcessing(0, 0);
    //return 0;
    /// Load source image and convert it to gray
    src = imread("/Users/weiweich/Documents/M2M/ProcessImage/ProcessImage/build/Debug/diffImg.jpg");
    cvtColor(src, src_gray, CV_RGB2GRAY);
    blur( src_gray, src_gray, Size(3,3) );
    
    /// Create Window
    namedWindow( "Source", CV_WINDOW_AUTOSIZE );
    imshow( "Source", src_gray );
    
    createTrackbar( " Canny thresh:", "Source", &thresh, max_thresh, thresh_callback );
    thresh_callback( 0, 0 );
    
    waitKey(0);
    return(0);
}

/** @function thresh_callback */
void thresh_callback(int, void* )
{
    Mat canny_output;
    vector<vector<Point> > contours;
    vector<Vec4i> hierarchy;
    
    /// Detect edges using canny
    Canny( src_gray, canny_output, thresh, thresh*2, 3 );
    /// Find contours
    findContours( canny_output, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0) );
    
    /// Draw contours
    Mat drawing = Mat::zeros( canny_output.size(), CV_8UC3 );
    for( int i = 0; i< contours.size(); i++ )
    {
        Scalar color = Scalar( rng.uniform(255, 255), rng.uniform(255,255), rng.uniform(255,255) );
        drawContours( drawing, contours, i, color, 2, 8, hierarchy, 0, Point() );
    }
    
    /// Show in a window
    namedWindow( "Contours", CV_WINDOW_AUTOSIZE );
    
    imshow( "Contours", drawing );
    imwrite("drawing.jpg", drawing);

}

/**
 * @function Threshold_Demo
 */
void Threshold_Demo(int, void*) {
  /* 0: Binary
   1: Binary Inverted
   2: Threshold Truncated
   3: Threshold to Zero
   4: Threshold to Zero Inverted
   */

  threshold(src_gray, dst, threshold_value, max_BINARY_value, 0);
}

int PreProcessing(int argc, char** argv) {
  /// Load the source image
  backgroundImg = imread(
      "/Users/weiweich/Documents/M2M/ProcessImage/ProcessImage/build/Debug/"
      "IMG_1539.JPG",
      1);
  currentImg = imread(
      "/Users/weiweich/Documents/M2M/ProcessImage/ProcessImage/build/Debug/"
      "IMG_1551.JPG",
      1);
  blur(backgroundImg, backgroundImg_blur, Size(2, 2));
  blur(currentImg, currentImg_blur, Size(2, 2));
  absdiff(backgroundImg_blur, currentImg_blur, diffImg);
  imwrite("diffImg.jpg", diffImg);
   return 0;
}
