//
//  AngleAdjust.cpp
//  ProcessImage
//
//  Created by Weiwei Chen on 10/14/15.
//  Copyright © 2015 Weiwei Chen. All rights reserved.
//

#include "AngleAdjust.hpp"

const double PI = 3.1415926;

AngleAdjust::AngleAdjust(double alpha_angle,
                         double lambda_angle,
                         double height_pixel,
                         double eps_angle,
                         double iphone_length) {
    _alpha_angle = alpha_angle;
    _lambda_angle = lambda_angle;
    _height_pixel = height_pixel;
    _eps_angle = eps_angle;
    _iphone_length = iphone_length;
}

double AngleAdjust::getHeight(
                              double upper_pixel,
                              double lower_pixel) {
    //double alpha_angle=59.34;//my experiment is 54.28%iphone 5s says HFOV is 59.34
    //double height_pixel=1280;//Overall pixel
    //double upper_pixel=116;//The pixel distance from top to head
    //double lower_pixel=1280-1178;//%The pixel distance from bottom to foot
    _upper_pixel = upper_pixel;
    _lower_pixel = lower_pixel;
    
    _beta_angle = _alpha_angle / 2 - atan(tan(_alpha_angle / 2 / 180 * PI) * (1 - 2 * _lower_pixel / _height_pixel)) / PI * 180;
    _delta_angle = _alpha_angle / 2 - atan(tan(_alpha_angle / 2 / 180 * PI) * (1 - 2 * _upper_pixel / _height_pixel)) / PI * 180;
    _gamma_angle = _alpha_angle - _beta_angle - _delta_angle;
    //double eps_angle= 90 - 68.5;//68.5 is the angle with horizon
    _theta_angle = 90 - _alpha_angle / 2;
    //double iphone_length = 11.8;
    _h = _iphone_length * cos(_eps_angle / 180 * PI);//11.8 in cm is the length of iphone 5s.
    _A1_angle = _alpha_angle / 2  - _eps_angle;
    _A2_angle = _A1_angle - _beta_angle;
    _d2 = _h / tan(_A2_angle / 180 * PI);
    _A3_angle = _gamma_angle + _eps_angle + _theta_angle + _beta_angle - 90;
    _h2 = _d2 * tan (_A3_angle / 180 * PI);
    _h3 = _h2 + _h;
    return _h3;
}

double AngleAdjust::getShoulderWidth(
                                     double shoulder_y,
                                     double shoulder_x
                                    ) {
    double A4_angle = _lambda_angle / 2 - _A2_angle - _beta_angle;
    double d4 = _d2 /  cos(A4_angle / 180 * PI);
    double etha_1 = atan(tan(_alpha_angle / 2 / 180 * PI) * (640 - shoulder_y) / 640) / PI * 180;
    double etha_2 = atan(tan(_alpha_angle / 2 / 180 * PI) * (640 - _lower_pixel) / 640) / PI * 180;
    double etha = etha_1 + etha_2;
    double A5_angle = etha - _A2_angle - A4_angle;
    double A6_angle = 90 - A4_angle - A5_angle;
    double d5 = _d2 / sin(A6_angle / 180 * PI);
    double d6 = d5 / (1 / sin(A5_angle / 180 * PI) + sin(_eps_angle / 180 * PI) / sin(A6_angle / 180 * PI));
    double l1 = d4 / cos(_lambda_angle / 2 / 180 * PI);
    double l2 = sqrt(l1 * l1 + d6 * d6);
    double l3 = d4 * tan (_lambda_angle / 2 / 180 * PI);
    double l4 = sqrt(l2 * l2 - l3 * l3);
    double l5 = 2 * l3 * d5 / l4;
    double A7_angle = 2 * atan(tan(_lambda_angle / 2 / 180 * PI) * shoulder_x / 480) / PI * 180;//shoulder angle
    double l6 = tan(A7_angle / 2 / 180 * PI) * l5 / tan(_lambda_angle / 2 / 180 * PI);
    return l6;
}