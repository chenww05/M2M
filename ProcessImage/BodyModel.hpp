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
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/imgproc/imgproc.hpp"
#include <opencv2/imgcodecs.hpp>
#include <iostream>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <math.h>
#include "BasicMath.hpp"
using namespace cv;
using namespace std;

#define NUM_BODY_INPUT_POINTS 30

class BodyModel {
public:

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
    
    int _leg_width;
    int _leg_width_min, _leg_width_max;
    
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
    
    double _left_leg_angle;
    double _right_leg_angle;
    double _leg_angle_min, _leg_angle_max;
    
    double _left_arm_angle;
    double _right_arm_angle;
    double _arm_angle_min, _arm_angle_max;
    
    
    int _left_foot_width;
    int _right_foot_width;
    int _foot_width_min, _foot_width_max;
    
    int _left_foot_heigh;
    int _right_foot_heigh;
    int _foot_heigh_min, _foot_heigh_max;
    
    double _left_knee_angle;
    double _right_knee_angle;
    double _left_knee_angle_min, _left_knee_angle_max;
    double _right_knee_angle_min, _right_knee_angle_max;
    
    int _knee_width;
    int _knee_width_min, _knee_width_max;
    
    int _shoulder_heigh;
    int _shoulder_heigh_min, _shoulder_heigh_max;
    
    int _elbow_width;
    int _elbow_width_min, _elbow_width_max;
    
    double _left_elbow_angle;
    double _left_elbow_angle_min, _left_elbow_angle_max;

    double _right_elbow_angle;
    double _right_elbow_angle_min, _right_elbow_angle_max;
    
    //derived
    int _heigh;
    int _heigh_min, _heigh_max;
    
    Point _right_shoulder;
    Point _left_shoulder;
    
    Point _right_waist;
    Point _left_waist;
    
    Point _right_hip;
    Point _left_hip;
    Point _mid_hip;
    
    Point _right_knee;
    Point _left_knee;
    
    Point _right_knee_inner;
    Point _left_knee_inner;
    
    Point _right_heel;
    Point _left_heel;
    
    Point _right_footrope;
    Point _left_footrope;
    
    Point _right_toe;
    Point _left_toe;
    
    Point _right_heel_upper;
    Point _left_heel_upper;
    
    Point _right_arm_center;
    Point _left_arm_center;
    
    Point _right_arm_lower;
    Point _left_arm_lower;
    
    Point _right_hand_center;
    Point _left_hand_center;
    
    Point _right_hand_upper;
    Point _left_hand_upper;
    
    Point _right_hand_lower;
    Point _left_hand_lower;
    
    Point _head_upper;
    Point _head_center;
    
    Point _right_elbow_center;
    Point _right_elbow_upper;
    Point _right_elbow_lower;
    
    Point _left_elbow_center;
    Point _left_elbow_upper;
    Point _left_elbow_lower;
    
    Mat _mask;
    BodyModel();
    BodyModel(int, int, int, int, int, int, int, int, int, int, int, int, int, int, int, int, int, double, double, double, double, int, int, int, int, double, double, int, int, int ,double, double);
    Mat generateMat();
    bool validate();
    void printOut();


private:
    bool withinRange();
    bool withinImage(Point);
    bool withinRange(double value, double value_min, double value_max);
    bool withinRange(int value, int value_min, int value_max);
    bool withinImage(int, bool) ;
    void drawTriangle(Point, Point, Point);
    void drawPolygon(Point, Point, Point, Point);
    void drawBodyShape(Point, Point, Point, Point, int);
    void drwaCircle(Point, int);


};

#endif /* BodyModel_hpp */
