//
//  AngleAdjust.hpp
//  ProcessImage
//
//  Created by Weiwei Chen on 10/14/15.
//  Copyright © 2015 Weiwei Chen. All rights reserved.
//

#ifndef AngleAdjust_hpp
#define AngleAdjust_hpp

#include <stdio.h>
#include <math.h>


class AngleAdjust {
public:
    AngleAdjust(double, double, double, double, double);
    double getHeight(double, double);
    double getShoulderWidth(double, double);
    double getHipWidth(double, double);
    double getWaistWidth(double, double);
    double getWidth(double, double);
private:
    double _alpha_angle;
    double _height_pixel;
    double _upper_pixel;
    double _lower_pixel;
    double _eps_angle;
    double _iphone_length;
    double _beta_angle;
    double _delta_angle;
    double _gamma_angle;
    double _theta_angle;
    double _h;
    double _A1_angle;
    double _A2_angle;
    double _d2;
    double _A3_angle;
    double _h2;
    double _h3;
    // width
    double _lambda_angle;
};

#endif /* AngleAdjust_hpp */
