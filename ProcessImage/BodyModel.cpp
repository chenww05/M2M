//
//  BodyModel.cpp
//  ProcessImage
//
//  Created by Weiwei Chen on 7/28/15.
//  Copyright © 2015 Weiwei Chen. All rights reserved.
//

#include "BodyModel.hpp"

BodyModel::BodyModel()
{
}

BodyModel::BodyModel(
    int hip_width,
    int shoulder_width,
    int chest_heigh,
    int head_radius,
    int neck_heigh,
    int neck_width,
    int arm_length,
    int arm_width,
    int hand_width,
    int leg_length,
    int leg_width,
    int waist_width,
    int waist_heigh,
    int center_x,
    int center_y,
    int img_width,
    int img_heigh,
    double left_leg_angle,
    double right_leg_angle,
    double left_arm_angle,
    double right_arm_angle,
    int foot_width,
    int foot_heigh)
{
    _img_width = img_width;
    _img_heigh = img_heigh;

    _center_x = center_x;
    _center_x_min = _img_width / 4, _center_x_max = _img_width / 4 * 3;

    _center_y = center_y;
    _center_y_min = _img_heigh / 10, _center_y_max = _img_heigh / 2;

    _hip_width = hip_width;
    _hip_width_min = _img_width / 8, _hip_width_max = _img_width / 4;

    _shoulder_width = shoulder_width;
    _shoulder_width_min = _img_width / 10, _shoulder_width_max = _img_width / 2;

    _chest_heigh = chest_heigh;
    _chest_heigh_min = _img_heigh / 10, _chest_heigh_max = _img_heigh / 2;

    _head_radius = head_radius;
    _head_radius_min = _img_width / 20, _head_radius_max = _img_width / 4;

    _neck_heigh = neck_heigh;
    _neck_heigh_min = _img_heigh / 20, _neck_heigh_max = _img_heigh / 4;

    _neck_width = neck_width;
    _neck_width_min = _img_width / 30, _neck_width_max = _img_width / 8;

    _arm_length = arm_length;
    _arm_length_min = _img_heigh / 10, _arm_length_max = _img_heigh / 2;

    _arm_width = arm_width;
    _arm_width_min = _img_width / 40, _arm_width_max = _img_width / 8;

    _hand_width = hand_width;
    _hand_width_min = _img_width / 50, _hand_width_max = _img_width / 8;

    _leg_length = leg_length;
    _leg_length_min = _img_heigh / 10, _leg_length_max = _img_heigh / 2;

    _leg_width = leg_width;
    _leg_width_min = _img_width / 30, _leg_width_max = _img_width / 4;

    _waist_width = waist_width;
    _waist_width_min = _img_width / 10, _waist_width_max = _img_width / 2;

    _waist_heigh = waist_heigh;
    _waist_heigh_min = _img_heigh / 10, _waist_heigh_max = _img_heigh / 2;

    _left_leg_angle = left_leg_angle;
    _left_leg_angle_min = 60.0, _left_leg_angle_max = 89.0;

    _right_leg_angle = right_leg_angle;
    _right_leg_angle_min = 60.0, _right_leg_angle_max = 89.0;

    _left_arm_angle = left_arm_angle;
    _left_arm_angle_min = 45.0, _left_arm_angle_max = 70.0;

    _right_arm_angle = right_arm_angle;
    _right_arm_angle_min = 45.0, _right_arm_angle_max = 70.0;

    _foot_heigh = foot_heigh;
    _foot_heigh_min = _img_heigh / 30, _foot_heigh_max = _img_heigh / 8;

    _foot_width = foot_width;
    _foot_width_min = _img_width / 30, _foot_width_max = _img_width / 8;

    _heigh = _head_radius + _neck_heigh + _chest_heigh + _waist_heigh + _leg_length;
    _heigh_min = _img_heigh / 2, _heigh_max = _img_heigh;

    //derived
    _right_shoulder = Point(_center_x + _shoulder_width, _center_y);
    _left_shoulder = Point(_center_x - _shoulder_width, _center_y);

    _right_waist = Point(_center_x + _waist_width, _center_y + _chest_heigh);
    _left_waist = Point(_center_x - _waist_width, _center_y + _chest_heigh);

    _right_hip = Point(_center_x + _hip_width, _center_y + _chest_heigh + _waist_heigh);
    _left_hip = Point(_center_x - _hip_width, _center_y + _chest_heigh + _waist_heigh);
    _mid_hip = Point(_center_x, _center_y + _chest_heigh + _waist_heigh);

    double cos_left_arm_angle = cos(_left_arm_angle / 180 * PI);
    double sin_left_arm_angle = sin(_left_arm_angle / 180 * PI);
    double cos_right_arm_angle = cos(_right_arm_angle / 180 * PI);
    double sin_right_arm_angle = sin(_right_arm_angle / 180 * PI);

    double right_arm_center_x = _right_shoulder.x - _arm_width * sin_right_arm_angle / 2;
    double right_arm_center_y = _right_shoulder.y + _arm_width * cos_right_arm_angle / 2;
    _right_arm_center = Point(right_arm_center_x, right_arm_center_y);

    _right_arm_lower = Point(_right_shoulder.x - _arm_width * sin_right_arm_angle, _right_shoulder.y + _arm_width * cos_right_arm_angle);

    double right_hand_center_x = _right_arm_center.x + _arm_length * cos_right_arm_angle;
    double right_hand_center_y = _right_arm_center.y + _arm_length * sin_right_arm_angle;
    _right_hand_center = Point(right_hand_center_x, right_hand_center_y);

    _right_hand_upper = Point(_right_hand_center.x + _hand_width * sin_right_arm_angle / 2, _right_hand_center.y - _hand_width * cos_right_arm_angle / 2);

    _right_hand_lower = Point(_right_hand_center.x - _hand_width * sin_right_arm_angle / 2, _right_hand_center.y + _hand_width * cos_right_arm_angle / 2);

    double left_arm_center_x = _left_shoulder.x + _arm_width * sin_left_arm_angle / 2;
    double left_arm_center_y = _left_shoulder.y + _arm_width * cos_left_arm_angle / 2;
    _left_arm_center = Point(left_arm_center_x, left_arm_center_y);

    _left_arm_lower = Point(_left_shoulder.x + _arm_width * sin_left_arm_angle, _left_shoulder.y + _arm_width * cos_left_arm_angle);

    double left_hand_center_x = _left_arm_center.x - _arm_length * cos_left_arm_angle;
    double left_hand_center_y = _left_arm_center.y + _arm_length * sin_left_arm_angle;
    _left_hand_center = Point(left_hand_center_x, left_hand_center_y);

    _left_hand_upper = Point(_left_hand_center.x - _hand_width * sin_left_arm_angle / 2, _left_hand_center.y - _hand_width * cos_left_arm_angle / 2);

    _left_hand_lower = Point(_left_hand_center.x + _hand_width * sin_left_arm_angle / 2, _left_hand_center.y + _hand_width * cos_left_arm_angle / 2);

    //Derive Legs
    double cos_left_leg_angle = cos(_left_leg_angle / 180 * PI);
    double sin_left_leg_angle = sin(_left_leg_angle / 180 * PI);
    double cos_right_leg_angle = cos(_right_leg_angle / 180 * PI);
    double sin_right_leg_angle = sin(_right_leg_angle / 180 * PI);

    _right_footrope = Point(_right_hip.x + _leg_length * cos_right_leg_angle,
        _right_hip.y + _leg_length * sin_right_leg_angle);
    _right_heel = Point(_right_footrope.x - _leg_width, _right_footrope.y);

    _left_footrope = Point(_left_hip.x - _leg_length * cos_left_leg_angle,
        _left_hip.y + _leg_length * sin_left_leg_angle);
    _left_heel = Point(_left_footrope.x + _leg_width, _left_footrope.y);

    //Derive feet
    _right_toe = Point(_right_heel.x + _foot_width, _right_heel.y);
    _right_heel_upper = Point(_right_heel.x, _right_heel.y - _foot_heigh);

    _left_toe = Point(_left_heel.x - _foot_width, _left_heel.y);
    _left_heel_upper = Point(_left_heel.x, _left_heel.y - _foot_heigh);
    
    //Derive head
    _head_center = Point(_center_x, _center_y - _neck_heigh);
    _head_upper = Point(_center_x, _center_y - neck_heigh - _head_radius);
}

bool BodyModel::withinRange(Point point)
{
    return withinImage(point.x, true) && withinImage(point.y, false);
}

bool BodyModel::withinRange(int value, int value_min, int value_max)
{
    return value >= value_min && value <= value_max;
}

bool BodyModel::withinRange(double value, double value_min, double value_max)
{
    return value >= value_min && value <= value_max;
}
bool BodyModel::withinImage(int value, bool horizontal)
{
    if (horizontal) {
        return value >= 0 && value < _img_width;
    }
    else {
        return value >= 0 && value < _img_heigh;
    }
}
bool BodyModel::withinRange()
{
    double cos_left_arm_angle = cos(_left_arm_angle / 180 * PI);
    double sin_left_arm_angle = sin(_left_arm_angle / 180 * PI);
    double cos_right_leg_angle = cos(_right_leg_angle / 180 * PI);
    double sin_right_leg_angle = sin(_right_leg_angle / 180 * PI);
    double cos_right_arm_angle = cos(_right_arm_angle / 180 * PI);
    double sin_right_arm_angle = sin(_right_arm_angle / 180 * PI);
    double right_arm_center_x = _right_shoulder.x - _arm_width * sin_right_arm_angle / 2;
    double right_arm_center_y = _center_y + _arm_width * cos_right_arm_angle / 2;
    double right_hand_center_x = right_arm_center_x + _arm_length * cos_right_arm_angle;
    double right_hand_center_y = right_arm_center_y + _arm_length * sin_right_arm_angle;

    double left_arm_center_x = _left_shoulder.x + _arm_width * sin_left_arm_angle / 2;
    double left_hand_center_x = left_arm_center_x - _arm_length * cos_left_arm_angle;

    return withinRange(_center_x, _center_x_min, _center_x_max)
        && withinRange(_center_y, _center_y_min, _center_y_max)
        && withinRange(_hip_width, _hip_width_min, _hip_width_max)
        && withinRange(_shoulder_width, _shoulder_width_min, _shoulder_width_max)
        && withinRange(_chest_heigh, _chest_heigh_min, _chest_heigh_max)
        && withinRange(_head_radius, _head_radius_min, _head_radius_max)
        && withinRange(_neck_heigh, _neck_heigh_min, _neck_heigh_max)
        && withinRange(_neck_width, _neck_width_min, _neck_width_max)
        && withinRange(_arm_length, _arm_length_min, _arm_length_max)
        && withinRange(_arm_width, _arm_width_min, _arm_width_max)
        && withinRange(_hand_width, _hand_width_min, _hand_width_max)
        && withinRange(_leg_length, _leg_length_min, _leg_length_max)
        && withinRange(_leg_width, _leg_width_min, _leg_width_max)
        && withinRange(_waist_width, _waist_width_min, _waist_width_max)
        && withinRange(_waist_heigh, _waist_heigh_min, _waist_heigh_max)
        && withinRange(_left_leg_angle, _left_leg_angle_min, _left_leg_angle_max)
        && withinRange(_right_leg_angle, _right_leg_angle_min, _right_leg_angle_max)
        && withinRange(_left_arm_angle, _left_arm_angle_min, _left_arm_angle_max)
        && withinRange(_right_arm_angle, _right_arm_angle_min, _right_arm_angle_max)
        && withinRange(_heigh, _heigh_min, _heigh_max)
        && withinRange(_foot_width, _foot_width_min, _foot_width_max)
        && withinRange(_leg_width * 3 / 2, 0, _foot_width)
        && withinRange(_foot_heigh, _foot_heigh_min, _foot_heigh_max)
        && withinImage(_center_x + _waist_width, true)
        && withinImage(_center_y + _chest_heigh, false)
        && withinImage(_center_x - _waist_width, true)
        && withinImage(_center_x + _hip_width, true)
        && withinImage(_center_x - _hip_width, true)
        && withinImage(_center_y + _chest_heigh + _waist_heigh, false)
        && withinImage(_right_shoulder.x, true)
        && withinImage(_left_shoulder.x, true)
        && withinImage(_center_y + _chest_heigh + _waist_heigh, false)
        && withinImage(_center_x + _hip_width + _leg_length * cos_right_leg_angle, true)
        && withinImage(_center_x + _hip_width + _leg_length * cos_right_leg_angle - _leg_width, true)
        && withinImage(_center_y + _chest_heigh + _waist_heigh + _leg_length * sin_right_leg_angle, false)
        && withinImage(_center_x - _hip_width - _leg_length * cos_right_leg_angle, true)
        && withinImage(_center_x - _hip_width - _leg_length * cos_right_leg_angle + _leg_width, true)
        && withinImage(_center_y - _neck_heigh - _head_radius, false)
        && withinImage(_right_shoulder.x - _arm_width * sin_right_arm_angle, true)
        && withinImage(_center_y + _arm_width * cos_right_arm_angle, false)
        && withinImage(right_hand_center_x + _hand_width * sin_right_arm_angle / 2, true)
        && withinImage(right_hand_center_y - _hand_width * cos_right_arm_angle / 2, false)
        && withinImage(_left_shoulder.x + _arm_width * sin_right_arm_angle, true)
        && withinImage(left_hand_center_x - _hand_width * sin_right_arm_angle / 2, true)
        && withinImage(_center_x - _hip_width - _leg_length * cos_right_leg_angle + _leg_width - _foot_width, true)
        && withinImage(_center_x + _hip_width + _leg_length * cos_right_leg_angle - _leg_width + _foot_width, true);
}


bool BodyModel::validate()
{
    if (!withinRange()) {
        return false;
    }
    //躯干为三个头高
    int main_body_heigh = _chest_heigh + _waist_heigh;
    int main_head_heigh = _head_radius + _neck_heigh;
    if (main_body_heigh > 4 * main_head_heigh || main_body_heigh < 2 * main_head_heigh) {
        return false;
    }
    //手臂长为3个头高
    if (_arm_length > 4 * main_head_heigh || _arm_length < 2 * main_head_heigh) {
        return false;
    }
    //大腿为2个头高，小腿和足为2个头高
    if (_leg_length > 5 * main_head_heigh || _leg_length < 3 * main_head_heigh) {
        return false;
    }
    return true;
}

Mat BodyModel::generateMat()
{
    _mask = Mat::zeros(_img_heigh, _img_width, CV_8UC3);
    drawPolygon(_right_waist, _left_waist, _right_hip, _left_hip);
    drawPolygon(_right_shoulder, _left_shoulder, _right_waist, _left_waist);
    drawPolygon(Point(_center_x + _neck_width, _center_y - _neck_heigh),
                 Point(_center_x - _neck_width, _center_y - _neck_heigh),
                 Point(_center_x + _neck_width, _center_y),
                 Point(_center_x - _neck_width, _center_y));
    drawPolygon(_left_shoulder, _left_arm_lower, _left_hand_upper, _left_hand_lower);
    drawPolygon(_right_shoulder, _right_arm_lower, _right_hand_upper, _right_hand_lower);
    drwaCircle(_head_center, _head_radius);
    drawPolygon(_left_hip, _mid_hip, _left_footrope, _left_heel);
    drawPolygon(_right_hip, _mid_hip, _right_footrope, _right_heel);
    drawTriangle(_left_heel, _left_toe, _left_heel_upper);
    drawTriangle(_right_heel, _right_toe, _right_heel_upper);
    return _mask;
}

void BodyModel::drawTriangle(Point p1, Point p2, Point p3) {
    Point rook_points[1][3];
    rook_points[0][0] = p1;
    rook_points[0][1] = p2;
    rook_points[0][2] = p3;
    const Point* ppt[1] = { rook_points[0] };
    int npt[] = { 3 };
    fillPoly(_mask, ppt, npt, 1, Scalar(255, 255, 255), 8);
}
void BodyModel::drawPolygon(Point upperRight, Point upperLeft, Point lowerRight, Point lowerLeft) {
    Point rook_points[1][4];
    rook_points[0][0] = upperRight;
    rook_points[0][3] = upperLeft;
    rook_points[0][1] = lowerRight;
    rook_points[0][2] = lowerLeft;
    const Point* ppt[1] = { rook_points[0] };
    int npt[] = { 4 };
    fillPoly(_mask, ppt, npt, 1, Scalar(255, 255, 255), 8);
}
void BodyModel::drwaCircle(Point center, int radius) {
    circle(_mask, center, radius, Scalar(255, 255, 255), -1);
}






