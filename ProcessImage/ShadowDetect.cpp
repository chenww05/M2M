//
//  ShadowDetect.cpp
//  ProcessImage
//
//  Created by Weiwei Chen on 10/16/15.
//  Copyright © 2015 Weiwei Chen. All rights reserved.
//

#include "ShadowDetect.hpp"

double getH(double R, double G, double B)
{
    if (R * R + G * G + B * B - R * G - R * B - G * B == 0) {
        return 0;
    }
    double degree = acos((R - G / 2 - B / 2) / sqrt(R * R + G * G + B * B - R * G - R * B - G * B)) * 180 / PI;
    if (G >= B) {
        return degree;
    }
    else {
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
            
            rt = getH(Rt, Gt, Bt); //acos((0.5 * ((Rt - Gt) + (Rt - Bt))) / (sqrt((Rt - Gt) * (Rt - Gt) + (Rt - Bt) * (Rt - Gt)))); //求色调(2pi-theta？)  H
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