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
    int foot_width,
    int waist_width,
    int waist_heigh,
    int center_x,
    int center_y,
    int img_width,
    int img_heigh,
    double leg_angle,
    double arm_angle)
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

    _foot_width = foot_width;
    _foot_width_min = _img_width / 30, _foot_width_max = _img_width / 4;

    _waist_width = waist_width;
    _waist_width_min = _img_width / 10, _waist_width_max = _img_width / 2;

    _waist_heigh = waist_heigh;
    _waist_heigh_min = _img_heigh / 10, _waist_heigh_max = _img_heigh / 2;

    _leg_angle = leg_angle;
    _leg_angle_min = 60.0, _leg_angle_max = 89.0;

    _arm_angle = arm_angle;
    _arm_angle_min = 40.0, _arm_angle_max = 80.0;

    _heigh = _head_radius + _neck_heigh + _chest_heigh + _waist_heigh + _leg_length;
    _heigh_min = _img_heigh / 2, _heigh_max = _img_heigh;
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
    double cos_leg_angle = cos(_leg_angle / 180 * PI);
    double sin_leg_angle = sin(_leg_angle / 180 * PI);
    double cos_arm_angle = cos(_arm_angle / 180 * PI);
    double sin_arm_angle = sin(_arm_angle / 180 * PI);
    double right_arm_center_x = _center_x + _shoulder_width - _arm_width * sin_arm_angle / 2;
    double right_arm_center_y = _center_y + _arm_width * cos_arm_angle / 2;
    double right_hand_center_x = right_arm_center_x + _arm_length * cos_arm_angle;
    double right_hand_center_y = right_arm_center_y + _arm_length * sin_arm_angle;
    double left_arm_center_x = _center_x - _shoulder_width + _arm_width * sin_arm_angle / 2;
    double left_hand_center_x = left_arm_center_x - _arm_length * cos_arm_angle;

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
        && withinRange(_foot_width, _foot_width_min, _foot_width_max)
        && withinRange(_waist_width, _waist_width_min, _waist_width_max)
        && withinRange(_waist_heigh, _waist_heigh_min, _waist_heigh_max)
        && withinRange(_leg_angle, _leg_angle_min, _leg_angle_max)
        && withinRange(_arm_angle, _arm_angle_min, _arm_angle_max)
        && withinRange(_heigh, _heigh_min, _heigh_max)
        && withinImage(_center_x + _waist_width, true)
        && withinImage(_center_y + _chest_heigh, false)
        && withinImage(_center_x - _waist_width, true)
        && withinImage(_center_x + _hip_width, true)
        && withinImage(_center_x - _hip_width, true)
        && withinImage(_center_y + _chest_heigh + _waist_heigh, false)
        && withinImage(_center_x + _shoulder_width, true)
        && withinImage(_center_x - _shoulder_width, true)
        && withinImage(_center_y + _chest_heigh + _waist_heigh, false)
        && withinImage(_center_x + _hip_width + _leg_length * cos_leg_angle, true)
        && withinImage(_center_x + _hip_width + _leg_length * cos_leg_angle - _foot_width, true)
        && withinImage(_center_y + _chest_heigh + _waist_heigh + _leg_length * sin_leg_angle, false)
        && withinImage(_center_x - _hip_width - _leg_length * cos_leg_angle, true)
        && withinImage(_center_x - _hip_width - _leg_length * cos_leg_angle + _foot_width, true)
        && withinImage(_center_y - _neck_heigh - _head_radius, false)
        && withinImage(_center_x + _shoulder_width - _arm_width * sin_arm_angle, true)
        && withinImage(_center_y + _arm_width * cos_arm_angle, false)
        && withinImage(right_hand_center_x + _hand_width * sin_arm_angle / 2, true)
        && withinImage(right_hand_center_y - _hand_width * cos_arm_angle / 2, false)
        && withinImage(_center_x - _shoulder_width + _arm_width * sin_arm_angle, true)
        && withinImage(left_hand_center_x - _hand_width * sin_arm_angle / 2, true);
}

BodyModel* BodyModel::generateNextValidBodyModel()
{
    int hip_width = _hip_width;
    int shoulder_width = _shoulder_width;
    int chest_heigh = _chest_heigh;
    int head_radius = _head_radius;
    int neck_heigh = _neck_heigh;
    int neck_width = _neck_width;
    int arm_length = _arm_length;
    int arm_width = _arm_width;
    int hand_width = _hand_width;
    int leg_length = _leg_length;
    int foot_width = _foot_width;
    int waist_width = _waist_width;
    int waist_heigh = _waist_heigh;
    int center_x = _center_x;
    int center_y = _center_y;
    int img_width = _img_width;
    int img_heigh = _img_heigh;
    double leg_angle = _leg_angle;
    double arm_angle = _arm_angle;
    srand((uchar)time(NULL));
    int index;
    int iteration = 0;
    int range;

    int max_iteration = 1000;
    int step = 5;
    while (iteration < max_iteration) {
        index = rand() % NUM_BODY_INPUT_POINTS;
        switch (index) {
        case 0:
            range = (_hip_width_max - _hip_width_min) / step; // 左range 右range
            hip_width += rand() % (range * 2) - range;
            break;
        case 1:
            range = (_shoulder_width_max - _shoulder_width_min) / step;
            shoulder_width += rand() % (range * 2) - range;
            break;
        case 2:
            range = (_chest_heigh_max - _chest_heigh_min) / step;
            chest_heigh += rand() % (range * 2) - range;
            break;
        case 3:
            range = (_head_radius_max - _head_radius_min) / step;
            head_radius += rand() % (range * 2) - range;
            break;
        case 4:
            range = (_neck_heigh_max - _neck_heigh_min) / step;
            neck_heigh += rand() % (range * 2) - range;
            break;
        case 5:
            range = (_neck_width_max - _neck_width_min) / step;
            neck_width += rand() % (range * 2) - range;
            break;
        case 6:
            range = (_arm_length_max - _arm_length_min) / step;
            arm_length += rand() % (range * 2) - range;
            break;
        case 7:
            range = (_arm_width_max - _arm_width_min) / step;
            arm_width += rand() % (range * 2) - range;
            break;
        case 8:
            range = (_hand_width_max - _hand_width_min) / step;
            hand_width += rand() % (range * 2) - range;
            break;
        case 9:
            range = (_leg_length_max - _leg_length_min) / step;
            leg_length += rand() % (range * 2) - range;
            break;
        case 10:
            range = (_foot_width_max - _foot_width_min) / step;
            foot_width += rand() % (range * 2) - range;
            break;
        case 11:
            range = (_waist_width_max - _waist_width_min) / step;
            waist_width += rand() % (range * 2) - range;
            break;
        case 12:
            range = (_waist_heigh_max - _waist_heigh_min) / step;
            waist_heigh += rand() % (range * 2) - range;
            break;
        case 13:
            range = (_center_x_max - _center_x_min) / step;
            center_x += rand() % (range * 2) - range;
            break;
        case 14:
            range = (_center_y_max - _center_y_min) / step;
            center_y += rand() % (range * 2) - range;
            break;
        case 15:
            range = (_leg_angle_max - _leg_angle_min) / step;
            leg_angle += rand() % (range * 2) - range;
            break;
        case 16:
            range = (_arm_angle_max - _arm_angle_min) / step;
            arm_angle += rand() % (range * 2) - range;
            break;
        default:
            break;
        }
        BodyModel* new_model = new BodyModel(hip_width,
            shoulder_width,
            chest_heigh,
            head_radius,
            neck_heigh,
            neck_width,
            arm_length,
            arm_width,
            hand_width,
            leg_length,
            foot_width,
            waist_width,
            waist_heigh,
            center_x,
            center_y,
            img_width,
            img_heigh,
            leg_angle,
            arm_angle);
        if (new_model->validate()) {
            //            cout << index << endl;
            //            cout << range << endl;
            return new_model;
        }
        else {
            delete new_model;
        }
        iteration++;
    }
    return NULL;
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
    generateWaist();
    generateChest();
    generateNeck();
    generateLeftArm();
    generateRightArm();
    generateHead();
    generateLeftLeg();
    generateRightLeg();
    return _mask;
}
//need a validate
void BodyModel::generateNeck()
{
    Point rook_points[1][4];
    rook_points[0][0] = Point(_center_x + _neck_width, _center_y - _neck_heigh);
    rook_points[0][3] = Point(_center_x - _neck_width, _center_y - _neck_heigh);
    rook_points[0][1] = Point(_center_x + _neck_width, _center_y);
    rook_points[0][2] = Point(_center_x - _neck_width, _center_y);
    const Point* ppt[1] = { rook_points[0] };
    int npt[] = { 4 };
    fillPoly(_mask, ppt, npt, 1, Scalar(255, 255, 255), 8);
}
void BodyModel::generateLeftArm()
{
    Point rook_points[1][4];
    rook_points[0][0] = Point(_center_x - _shoulder_width, _center_y); //done
    double cos_angle = cos(_arm_angle / 180 * PI);
    double sin_angle = sin(_arm_angle / 180 * PI);

    rook_points[0][3] = Point(_center_x - _shoulder_width + _arm_width * sin_angle, _center_y + _arm_width * cos_angle);

    double arm_center_x = _center_x - _shoulder_width + _arm_width * sin_angle / 2;
    double arm_center_y = _center_y + _arm_width * cos_angle / 2;
    double hand_center_x = arm_center_x - _arm_length * cos_angle;
    double hand_center_y = arm_center_y + _arm_length * sin_angle;
    rook_points[0][1] = Point(hand_center_x - _hand_width * sin_angle / 2, hand_center_y - _hand_width * cos_angle / 2);
    rook_points[0][2] = Point(hand_center_x + _hand_width * sin_angle / 2, hand_center_y + _hand_width * cos_angle / 2);
    const Point* ppt[1] = { rook_points[0] };
    int npt[] = { 4 };
    fillPoly(_mask, ppt, npt, 1, Scalar(255, 255, 255), 8);
}
void BodyModel::generateRightArm()
{
    Point rook_points[1][4];
    rook_points[0][0] = Point(_center_x + _shoulder_width, _center_y); //done
    double cos_angle = cos(_arm_angle / 180 * PI);
    double sin_angle = sin(_arm_angle / 180 * PI);

    rook_points[0][3] = Point(_center_x + _shoulder_width - _arm_width * sin_angle, _center_y + _arm_width * cos_angle);

    double arm_center_x = _center_x + _shoulder_width - _arm_width * sin_angle / 2;
    double arm_center_y = _center_y + _arm_width * cos_angle / 2;
    double hand_center_x = arm_center_x + _arm_length * cos_angle;
    double hand_center_y = arm_center_y + _arm_length * sin_angle;
    rook_points[0][1] = Point(hand_center_x + _hand_width * sin_angle / 2, hand_center_y - _hand_width * cos_angle / 2);
    rook_points[0][2] = Point(hand_center_x - _hand_width * sin_angle / 2, hand_center_y + _hand_width * cos_angle / 2);
    const Point* ppt[1] = { rook_points[0] };
    int npt[] = { 4 };
    fillPoly(_mask, ppt, npt, 1, Scalar(255, 255, 255), 8);
}
void BodyModel::generateHead()
{
    circle(_mask, Point(_center_x, _center_y - _neck_heigh), _head_radius, Scalar(255, 255, 255), -1);
}
void BodyModel::generateLeftLeg()
{
    Point rook_points[1][4];
    rook_points[0][0] = Point(_center_x - _hip_width, _center_y + _chest_heigh + _waist_heigh); //done
    rook_points[0][3] = Point(_center_x, _center_y + _chest_heigh + _waist_heigh); //done
    double cos_angle = cos(_leg_angle / 180 * PI);
    double sin_angle = sin(_leg_angle / 180 * PI);
    rook_points[0][1] = Point(_center_x - _hip_width - _leg_length * cos_angle,
        _center_y + _chest_heigh + _waist_heigh + _leg_length * sin_angle);
    rook_points[0][2] = Point(_center_x - _hip_width - _leg_length * cos_angle + _foot_width,
        _center_y + _chest_heigh + _waist_heigh + _leg_length * sin_angle);
    const Point* ppt[1] = { rook_points[0] };
    int npt[] = { 4 };
    fillPoly(_mask, ppt, npt, 1, Scalar(255, 255, 255), 8);
}
void BodyModel::generateRightLeg()
{
    Point rook_points[1][4];
    rook_points[0][0] = Point(_center_x + _hip_width, _center_y + _chest_heigh + _waist_heigh); //done
    rook_points[0][3] = Point(_center_x, _center_y + _chest_heigh + _waist_heigh); //done
    double cos_angle = cos(_leg_angle / 180 * PI);
    double sin_angle = sin(_leg_angle / 180 * PI);
    rook_points[0][1] = Point(_center_x + _hip_width + _leg_length * cos_angle,
        _center_y + _chest_heigh + _waist_heigh + _leg_length * sin_angle);
    rook_points[0][2] = Point(_center_x + _hip_width + _leg_length * cos_angle - _foot_width,
        _center_y + _chest_heigh + _waist_heigh + _leg_length * sin_angle);
    const Point* ppt[1] = { rook_points[0] };
    int npt[] = { 4 };
    fillPoly(_mask, ppt, npt, 1, Scalar(255, 255, 255), 8);
}

void BodyModel::generateChest()
{
    Point rook_points[1][4];
    rook_points[0][0] = Point(_center_x + _shoulder_width, _center_y);
    rook_points[0][3] = Point(_center_x - _shoulder_width, _center_y);
    rook_points[0][1] = Point(_center_x + _waist_width, _center_y + _chest_heigh);
    rook_points[0][2] = Point(_center_x - _waist_width, _center_y + _chest_heigh);
    const Point* ppt[1] = { rook_points[0] };
    int npt[] = { 4 };
    fillPoly(_mask, ppt, npt, 1, Scalar(255, 255, 255), 8);
}

void BodyModel::generateWaist()
{
    Point rook_points[1][4];
    rook_points[0][0] = Point(_center_x + _waist_width, _center_y + _chest_heigh);
    rook_points[0][3] = Point(_center_x - _waist_width, _center_y + _chest_heigh);
    rook_points[0][1] = Point(_center_x + _hip_width, _center_y + _chest_heigh + _waist_heigh);
    rook_points[0][2] = Point(_center_x - _hip_width, _center_y + _chest_heigh + _waist_heigh);
    const Point* ppt[1] = { rook_points[0] };
    int npt[] = { 4 };
    fillPoly(_mask, ppt, npt, 1, Scalar(255, 255, 255), 8);
}