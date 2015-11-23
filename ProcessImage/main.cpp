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
#include "shape/ShapeDiff.hpp"
#include "shape/ShapeLearning.hpp"
#include "BodyModel.hpp"
#include "ShadowDetect.hpp"

#include <iostream>
#include <stdio.h>

using namespace std;
using namespace cv;

Mat backgroundImg;
Mat currentImg;
Mat diffImg;
Mat src, src_gray, dst, detected_edges, contours;
Mat backgroundImg_blur, currentImg_blur;

int PreProcessing(int argc, char** argv);
void ShadowDetect(IplImage* currImg, IplImage* bkImg, Mat* shadowdeImg, double th1, double th2, double th3, double th4);
double getH(double R, double G, double B);

int main(int argc, char** argv)
{
    PreProcessing(argc, argv);
    //return 0;

    //waitKey(0);
    currentImg = imread("shadow.JPG");
    src = imread("shadow.jpg");
    learn(&src, &currentImg, &backgroundImg);
    return 0;
}

int PreProcessing(int argc, char** argv)
{
    /// Load the source image
    backgroundImg = imread("/Users/weiweich/Downloads/IMG_1541.JPG", 1);
    currentImg = imread("/Users/weiweich/Downloads/IMG_1551.JPG", 1);
    //backgroundImg = imread(
    //    "/Users/weiweich/Documents/M2M/ProcessImage/ProcessImage/build/Debug/"
    //    "IMG_1799.JPG",
    //    1);
    //currentImg = imread(
    //    "/Users/weiweich/Documents/M2M/ProcessImage/ProcessImage/build/Debug/"
    //    "IMG_1807.JPG",
    //    1);
    //    backgroundImg = imread(
    //        "/Users/weiweich/Documents/M2M/ProcessImage/ProcessImage/build/Debug/"
    //        "IMG_1462.JPG",
    //        1);
    //    currentImg = imread(
    //        "/Users/weiweich/Documents/M2M/ProcessImage/ProcessImage/build/Debug/"
    //        "IMG_1470.JPG",
    //        1);
    blur(backgroundImg, backgroundImg_blur, Size(2, 2));
    blur(currentImg, currentImg_blur, Size(2, 2));
    absdiff(backgroundImg_blur, currentImg_blur, diffImg);
    imwrite("diffImg.jpg", diffImg);
    IplImage curImg = IplImage(currentImg);
    IplImage bkgImg = IplImage(backgroundImg);

    //    double th1 = 1; works for IMG_1462/IMG_1470
    //    double th2 = 3;
    //    double th3 = 25.0;
    //    double th4 = 15.0;
    //    double th1 = 0.5; works for IMG_1551/IMG_1539
    //    double th2 = 1.0;
    //    double th3 = 10.0;
    //    double th4 = 5.0;
    double th1 = 0.5;
    double th2 = 3.0; //IMG_1551 between 0.5-1.0, 0.5-3.0
    double th3 = 10.0;
    double th4 = 5.0;
    ShadowDetect(&curImg, &bkgImg, &diffImg, th1, th2, th3, th4);
    //imshow("shadow", shadowedImg);
    imwrite("shadow.jpg", diffImg);

    return 0;
}

