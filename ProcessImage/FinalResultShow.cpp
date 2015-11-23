//
//  FinalResultShow.cpp
//  ProcessImage
//
//  Created by Weiwei Chen on 10/17/15.
//  Copyright © 2015 Weiwei Chen. All rights reserved.
//

#include "FinalResultShow.hpp"

void addText(Mat*dest, int height, int shoulde_width, int hip_width, int waist_width) {
    string text = "Estimated Height is: " + to_string(height) + " cm";
    int fontFace = FONT_HERSHEY_SIMPLEX;
    double fontScale = 1;
    int thickness = 2;
    Point textOrg(10, 130);
    cv::putText(*dest, text, textOrg, fontFace, fontScale, Scalar::all(255), thickness, 8);
    text = "Estimated Shoulder Width is: " + to_string(shoulde_width) + " cm";
    Point textOrg1(10, 260);
    cv::putText(*dest, text, textOrg1, fontFace, fontScale, Scalar::all(255), thickness, 8);
    text = "Estimated Waist Width is: " + to_string(waist_width) + " cm";
    Point textOrg2(10, 390);
    cv::putText(*dest, text, textOrg2, fontFace, fontScale, Scalar::all(255), thickness, 8);
    text = "Estimated Hip Width is: " + to_string(hip_width) + " cm";
    Point textOrg3(10, 520);
    cv::putText(*dest, text, textOrg3, fontFace, fontScale, Scalar::all(255), thickness, 8);
}

void showImg(BodyModel* model, Mat* src, int iteration)
{
    Mat edge, draw;
    Mat dest;
    src->copyTo(dest);
    Mat mask = model->generateMat();
    Canny(mask, edge, 50, 150, 3);
    edge.convertTo(draw, CV_8U);
    
    for (int i = 0; i < src->rows; ++i) {
        for (int j = 0; j < src->cols; ++j) {
            if (edge.at<uchar>(i, j) == 255) {
                //dest.at<uchar>(i, j * 3) = 255;
                circle(dest, Point(j, i), 5, CV_RGB(0, 0, 255));
            }
        }
    }
    
    string Result;
    ostringstream convert;
    convert << iteration;
    //imwrite("dest" +  convert.str() + ".jpg", dest);
    //displayStatusBar("Height: ", "100", 0);
    double alpha_angle = 59.34;
    double height_pixel = 1280;
    double lambda_angle = atan(tan(alpha_angle / 180 * PI) * 960 / 1280) / PI * 180;
    double upper_pixel = model->_head_upper.y;//116
    cout << "Estimated upper pixel " << upper_pixel << endl;
    double lower_pixel = 1280 - model->_left_footrope.y;//
    cout << "Estimated lower pixel " << lower_pixel << endl;
    double eps_angle = 90 - 68.5;
    double iphone_length = 11.8;
    AngleAdjust* angle_anjust = new AngleAdjust(alpha_angle, lambda_angle, height_pixel, eps_angle, iphone_length);

    int height = angle_anjust->getHeight(upper_pixel, lower_pixel);
    int shoulder_width = angle_anjust->getShoulderWidth(model->_right_shoulder.y, model->_right_shoulder.x - model->_center_x);
    int hip_width = angle_anjust->getHipWidth(model->_right_hip.y, model->_right_hip.x - model->_center_x);
    int waist_width = angle_anjust->getWaistWidth(model->_right_waist.y, model->_right_waist.x - model->_center_x);
    
    addText(&dest, height, shoulder_width, hip_width, waist_width);
    
    cv::circle(dest, model->_head_upper, 5, CV_RGB(255, 0, 0));
    cv::circle(dest, model->_head_center, 5, CV_RGB(255, 255, 0));
    cv::circle(dest, model->_right_shoulder, 5, CV_RGB(255, 255, 0));
    cv::circle(dest, model->_left_shoulder, 5, CV_RGB(255, 255, 0));
    cv::circle(dest, model->_right_waist, 5, CV_RGB(255, 255, 0));
    cv::circle(dest, model->_left_waist, 5, CV_RGB(255, 255, 0));
    cv::circle(dest, model->_right_toe, 5, CV_RGB(255, 255, 0));
    cv::circle(dest, model->_left_toe, 5, CV_RGB(255, 255, 0));
    cv::resize(dest, dest, Size(dest.cols/2, dest.rows/2));
    
    imshow("Estimation Result", dest);
    waitKey(0);
}