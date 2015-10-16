//
//  AngleAdjust.cpp
//  ProcessImage
//
//  Created by Weiwei Chen on 10/14/15.
//  Copyright © 2015 Weiwei Chen. All rights reserved.
//

#include "AngleAdjust.hpp"

const double PI = 3.1415926;

double AngleAdjust::getHeight(
                              double alpha_angle,
                              double height_pixel,
                              double upper_pixel,
                              double lower_pixel,
                              double eps_angle,
                              double iphone_length) {
    //double alpha_angle=59.34;//my experiment is 54.28%iphone 5s says HFOV is 59.34
    //double height_pixel=1280;//Overall pixel
    //double upper_pixel=116;//The pixel distance from top to head
    //double lower_pixel=1280-1178;//%The pixel distance from bottom to foot
    
    double beta_angle = alpha_angle / 2 - atan(tan(alpha_angle / 2 / 180 * PI) * (1 - 2 * lower_pixel / height_pixel)) / PI * 180;
    double delta_angle = alpha_angle / 2 - atan(tan(alpha_angle / 2 / 180 * PI) * (1 - 2 * upper_pixel / height_pixel)) / PI * 180;
    double gamma_angle = alpha_angle - beta_angle - delta_angle;
    //double eps_angle= 90 - 68.5;//68.5 is the angle with horizon
    double theta_angle = 90 - alpha_angle / 2;
    //double iphone_length = 11.8;
    double h = iphone_length * cos(eps_angle / 180 * PI);//11.8 in cm is the length of iphone 5s.
    double A1_angle = alpha_angle / 2  - eps_angle;
    double A2_angle = A1_angle - beta_angle;
    double d2 = h / tan(A2_angle / 180 * PI);
    double A3_angle = gamma_angle + eps_angle + theta_angle + beta_angle - 90;
    double h2 = d2 * tan (A3_angle / 180 * PI);
    return h2 + h;
}