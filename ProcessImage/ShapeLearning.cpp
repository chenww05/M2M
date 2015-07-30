//
//  ShapeLearning.cpp
//  ProcessImage
//
//  Created by Weiwei Chen on 7/28/15.
//  Copyright © 2015 Weiwei Chen. All rights reserved.
//

#include "ShapeLearning.hpp"
#include "ShapeDiff.hpp"

pair<BodyModel*, BodyModel*> generateLeftRightModel(BodyModel* original,
    int index, int step)
{
    BodyModel* left_model = generateModel(original, index, -step);
    BodyModel* right_model = generateModel(original, index, step);
    return make_pair(left_model, right_model);
}

BodyModel* generateModel(BodyModel* original, int index, int step)
{
    int hip_width = original->_hip_width;
    int shoulder_width = original->_shoulder_width;
    int chest_heigh = original->_chest_heigh;
    int head_radius = original->_head_radius;
    int neck_heigh = original->_neck_heigh;
    int neck_width = original->_neck_width;
    int arm_length = original->_arm_length;
    int arm_width = original->_arm_width;
    int hand_width = original->_hand_width;
    int leg_length = original->_leg_length;
    int leg_width = original->_leg_width;
    int waist_width = original->_waist_width;
    int waist_heigh = original->_waist_heigh;
    int center_x = original->_center_x;
    int center_y = original->_center_y;
    int img_width = original->_img_width;
    int img_heigh = original->_img_heigh;
    double left_leg_angle = original->_left_leg_angle;
    double right_leg_angle = original->_right_leg_angle;
    double left_arm_angle = original->_left_arm_angle;
    double right_arm_angle = original->_right_arm_angle;
    int foot_width = original->_foot_width;
    int foot_heigh = original->_foot_heigh;
    CV_Assert(index < NUM_BODY_INPUT_POINTS && index >= 0);
    switch (index) {
    case 0:
        hip_width += step;
        break;
    case 1:
        shoulder_width += step;
        break;
    case 2:
        chest_heigh += step;
        break;
    case 3:
        head_radius += step;
        break;
    case 4:
        neck_heigh += step;
        break;
    case 5:
        neck_width += step;
        break;
    case 6:
        arm_length += step;
        break;
    case 7:
        arm_width += step;
        break;
    case 8:
        hand_width += step;
        break;
    case 9:
        leg_length += step;
        break;
    case 10:
        leg_width += step;
        break;
    case 11:
        waist_width += step;
        break;
    case 12:
        waist_heigh += step;
        break;
    case 13:
        center_x += step;
        break;
    case 14:
        center_y += step;
        break;
    case 15:
        left_leg_angle += step;
        break;
    case 16:
        right_leg_angle += step;
        break;
    case 17:
        left_arm_angle += step;
        break;
    case 18:
        right_arm_angle += step;
        break;
    case 19:
        foot_width += step;
        break;
    case 20:
        foot_heigh += step;
        break;
    default:
        break;
    }

    BodyModel* model = new BodyModel(hip_width, shoulder_width, chest_heigh, head_radius,
        neck_heigh, neck_width, arm_length, arm_width, hand_width,
        leg_length, leg_width, waist_width, waist_heigh, center_x,
        center_y, img_width, img_heigh, left_leg_angle, right_leg_angle, left_arm_angle, right_arm_angle, foot_width, foot_heigh);
    return model;
}

BodyModel* findBestModel(BodyModel* model, int index, Mat* src, bool& hasUpdate)
{
    int iteration = 0;
    const int max_iteration = 200;
    int last_similar = 0;
    int max_last_similar = 20;
    int max_step = 15;
    Mat mask = model->generateMat();
    double distance = getAvgDistance(&mask, src);
    const double eps = 0.001;
    cout << "Index : " << index << endl;
    while (iteration < max_iteration && last_similar < max_last_similar) {
        int step = rand() % max_step + 1;
        pair<BodyModel*, BodyModel*> pair = generateLeftRightModel(model, index, step);
        BodyModel* left_model = pair.first;
        BodyModel* right_model = pair.second;
        bool isRightLarger = false;
        double right_distance = 0;
        if (right_model->validate()) {
            mask = right_model->generateMat();
            right_distance = getAvgDistance(&mask, src);
            if (right_distance - distance > eps) {
                isRightLarger = true;
            }
        }

        bool isLeftLarger = false;
        double left_distance = 0;
        if (left_model->validate()) {
            mask = left_model->generateMat();
            left_distance = getAvgDistance(&mask, src);
            if (left_distance - distance > eps) {
                isLeftLarger = true;
            }
        }
        if (isLeftLarger && isRightLarger) {
            if (left_distance > right_distance) {
                distance = left_distance;
                delete model;
                model = left_model;
                if (right_model != NULL) {
                    delete right_model;
                }
            }
            else {
                distance = right_distance;
                delete model;
                model = right_model;
                if (left_model != NULL) {
                    delete left_model;
                }
            }
            last_similar = 0;
            hasUpdate = true;
        }
        else if (isLeftLarger) {
            distance = left_distance;
            delete model;
            model = left_model;
            if (right_model != NULL) {
                delete right_model;
            }
            last_similar = 0;
            hasUpdate = true;
        }
        else if (isRightLarger) {
            distance = right_distance;
            delete model;
            model = right_model;
            if (left_model != NULL) {
                delete left_model;
            }
            last_similar = 0;
            hasUpdate = true;
        }
        else {
            // good it is the larger one. no update.
            if (left_model != NULL) {
                delete left_model;
            }
            if (right_model != NULL) {
                delete right_model;
            }
            last_similar++;
        }
        iteration++;
    }
    cout << "Distance " << distance << " iteration " << iteration << endl;
    return model;
}

void execute(Mat* src)
{
    // First, picks up one dimension randomly. Goes one direction until reaches a
    // local optimal.

    double width = 960;
    double heigh = 1280;
    int hip_width = 150;
    int shoulder_width = 150;
    int chest_heigh = 250;
    int head_radius = 100;
    int neck_heigh = 100;
    int neck_width = 50;
    int arm_length = 400;
    int arm_width = 100;
    int hand_width = 50;
    int leg_length = 600;
    int leg_width = 40;
    int waist_width = 120;
    int waist_heigh = 150;
    double left_leg_angle = 85;
    double right_leg_angle = 85;
    double left_arm_angle = 60;
    double right_arm_angle = 60;
    int foot_width = 80;
    int foot_heigh = 120;
    int center_x = 515;
    int center_y = 280;
    BodyModel* model = new BodyModel(hip_width, shoulder_width, chest_heigh, head_radius,
        neck_heigh, neck_width, arm_length, arm_width, hand_width,
        leg_length, leg_width, waist_width, waist_heigh, center_x,
        center_y, width, heigh, left_leg_angle, right_leg_angle, left_arm_angle, right_arm_angle, foot_width, foot_heigh);

    CV_Assert(model->validate());
    srand((uchar)time(NULL));
    int index = 0;
    int iteration = 0;
    int max_iteration = 200;
    int last_update = 0;
    int max_update = 20;
    while (iteration < max_iteration && last_update < max_update) {
        int current_index = rand() % NUM_BODY_INPUT_POINTS;
        if (index == current_index) {
            continue;
        }
        index = current_index;
        bool hasUpdate = false;
        model = findBestModel(model, index, src, hasUpdate);
        if (hasUpdate) {
            last_update = 0;
        }
        else {
            last_update++;
        }
        if (iteration % 10 == 0) {
            //showImg(model, src);
        }
        iteration++;

    }
    showImg(model, src);
    //waitKey(0);

    //    Mat mask = model->generateMat();
    //    Mat edge, draw;
    //    Canny(mask, edge, 50, 150, 3);
    //    edge.convertTo(draw, CV_8U);
    //    for (int i = 0; i < src->rows; ++i) {
    //        for (int j = 0; j < src->cols; ++j) {
    //            if (edge.at<uchar>(i, j) == 255) {
    //                src->at<uchar>(i, j * 3) = 255;
    //            }
    //        }
    //    }

    //    imwrite("src.jpg", *src);
}

void showImg(BodyModel* model, Mat* src)
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
                dest.at<uchar>(i, j * 3) = 255;
            }
        }
    }

    imwrite("dest.jpg", dest);
    //imshow("Edge Map", dest);
    //waitKey(0);
    cout << "Updated " << endl;
}