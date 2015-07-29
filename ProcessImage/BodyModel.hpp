//
//  BodyModel.hpp
//  ProcessImage
//
//  Created by Weiwei Chen on 7/28/15.
//  Copyright © 2015 Weiwei Chen. All rights reserved.
//

#ifndef BodyModel_hpp
#define BodyModel_hpp

#include <stdio.h>

#include <stdio.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/imgproc/imgproc.hpp"
#include <opencv2/imgcodecs.hpp>
#include <iostream>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <math.h>
using namespace cv;
using namespace std;

#define PI 3.14159
#define NUM_BODY_INPUT_POINTS 17

class BodyModel {
    int _hip_width;
    int _hip_width_min, _hip_width_max;
    
    int _shoulder_width;
    int _shoulder_width_min, _shoulder_width_max;
    
    int _chest_heigh;
    int _chest_heigh_min,  _chest_heigh_max;
    
    int _head_radius;
    int _head_radius_min, _head_radius_max;
    
    int _neck_heigh;
    int _neck_heigh_min, _neck_heigh_max;
    
    int _neck_width;
    int _neck_width_min, _neck_width_max;
    
    int _arm_length;
    int _arm_length_min, _arm_length_max;
    
    int _arm_width;
    int _arm_width_min, _arm_width_max;
    
    int _hand_width;
    int _hand_width_min, _hand_width_max;
    
    int _leg_length;
    int _leg_length_min ,_leg_length_max;
    
    int _foot_width;
    int _foot_width_min, _foot_width_max;
    
    int _waist_width;
    int _waist_width_min, _waist_width_max;
    
    int _waist_heigh;
    int _waist_heigh_min, _waist_heigh_max;
    
    int _center_x;
    int _center_x_min, _center_x_max;
    int _center_y;
    int _center_y_min, _center_y_max;
    
    int _img_width;
    int _img_heigh;
    
    double _leg_angle;
    double _leg_angle_min, _leg_angle_max;
    
    double _arm_angle;
    double _arm_angle_min, _arm_angle_max;
    
    int _heigh;
    int _heigh_min, _heigh_max;
    
    Mat _mask;
public:
    BodyModel();
    BodyModel(int, int, int, int, int, int, int, int, int, int, int, int, int, int, int, int, int, double, double);
    Mat generateMat();
    bool validate();
    BodyModel* generateNextValidBodyModel();


private:
    void generateWaist();
    void generateChest();
    void generateNeck();
    void generateLeftArm();
    void generateRightArm();
    void generateHead();
    void generateLeftLeg();
    void generateRightLeg();
    bool withinRange();
    bool withinRange(double value, double value_min, double value_max);
    bool withinRange(int value, int value_min, int value_max);
    bool withinImage(int, bool) ;


};

#endif /* BodyModel_hpp */
