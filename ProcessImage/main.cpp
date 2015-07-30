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
void ShadowDetect(IplImage* currImg, IplImage* bkImg, Mat* shadowdeImg, double th1, double th2, double th3, double th4);
double getH(double R, double G, double B) ;
int main(int argc, char** argv)
{
//        PreProcessing( argc, argv) ;
//            return 0;

    //waitKey(0);
        src = imread("shadow.jpg");
        execute(&src);
    return 0;
}

int PreProcessing(int argc, char** argv)
{
    /// Load the source image
        backgroundImg = imread(
            "/Users/weiweich/Documents/M2M/ProcessImage/ProcessImage/build/Debug/"
            "IMG_1551.JPG",
            1);
        currentImg = imread(
            "/Users/weiweich/Documents/M2M/ProcessImage/ProcessImage/build/Debug/"
            "IMG_1539.JPG",
            1);
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
    double th2 = 3.0;//IMG_1551 between 0.5-1.0, 0.5-3.0
    double th3 = 10.0;
    double th4 = 5.0;
    ShadowDetect(&curImg, &bkgImg, &diffImg, th1, th2, th3, th4);
    //imshow("shadow", shadowedImg);
    imwrite("shadow.jpg", diffImg);
    
    return 0;
}
double getH(double R, double G, double B) {
    if (R * R + G * G + B * B - R * G - R * B - G * B == 0) {return 0;}
    double degree = acos ((R - G / 2 - B / 2) / sqrt( R * R + G * G + B * B - R * G - R * B - G * B)) * 180 / PI;
    if (G >= B) {
        return degree;
    } else {
        return 360 - degree;
    }
}
void ShadowDetect(IplImage* currImg, IplImage* bkImg, Mat* shadowdeImg, double th1, double th2, double th3, double th4)
{
    unsigned char* currData;
    unsigned char* bkData;
    int i = 0, j = 0;
    int height = currImg->height;
    int width = currImg->width;
    double rb = 0, gb = 0, Ib = 0, Rb = 0, Gb = 0, Bb = 0, bf = 0;
    double rt = 0, gt = 0, It = 0, Rt = 0, Gt = 0, Bt = 0, tf = 0;
    //CvScalar cs=cvScalarAll(255);
    for (i = 0; i < height; i++) {
        currData = (unsigned char*)currImg->imageData + i * currImg->widthStep; //指针为第i+1行
        bkData = (unsigned char*)bkImg->imageData + i * bkImg->widthStep;
        for (j = 0; j < width; j++) {
            // current normalized
            //*******************
            //当前图像
            //*******************
            Bt = currData[j * 3]; //分别获取像素点的BGR值
            Gt = currData[j * 3 + 1];
            Rt = currData[j * 3 + 2];
            tf = (Rt > Gt ? Gt : Rt) > Bt ? Bt : (Rt > Gt ? Gt : Rt); //取R、G、B三值中的最小值存入tf

            rt = getH(Rt, Gt, Bt);//acos((0.5 * ((Rt - Gt) + (Rt - Bt))) / (sqrt((Rt - Gt) * (Rt - Gt) + (Rt - Bt) * (Rt - Gt)))); //求色调(2pi-theta？)  H
            gt = 1 - 3 * tf / (Rt + Gt + Bt); //求饱和度             S
            It = (Rt + Gt + Bt) / 3; //求亮度               I
            // Bk normalized
            //*********************
            //背景图像
            //*********************
            Bb = bkData[j * 3];
            Gb = bkData[j * 3 + 1];
            Rb = bkData[j * 3 + 2];
            bf = (Rb > Gb ? Gb : Rb) > Bb ? Bb : (Rb > Gb ? Gb : Rb);

            rb = getH(Rb, Gb, Bb); //acos((0.5 * ((Rb - Gb) + (Rb - Bb))) / (sqrt((Rb - Gb) * (Rb - Gb) + (Rb - Bb) * (Rb - Gb))));
            gb = 1 - 3 * bf / (Rb + Gb + Bb);
            Ib = (Rb + Gb + Bb) / 3;
            // judge whether is shadeimg
            //判断
            if (It / Ib >= th1 && It / Ib <= th2 && fabs(rt - rb) <= th3 && fabs(gt - gb) <= th4) {
                shadowdeImg->at<uchar>(i, j * 3) = 0;
                shadowdeImg->at<uchar>(i, j * 3 + 1) = 0;
                shadowdeImg->at<uchar>(i, j * 3 + 2) = 0;

            }
        }
    }
}
