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
Mat src, src_gray, dst, detected_edges, contours;
Mat backgroundImg_blur, currentImg_blur;

int PreProcessing(int argc, char** argv);

int main(int argc, char** argv)
{
    //    PreProcessing( argc, argv) ;
    //    return 0;
    src = imread("diffImg.jpg");
    execute(&src);
    return 0;
}

int PreProcessing(int argc, char** argv)
{
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
