//
//  ShapeLearning.cpp
//  ProcessImage
//
//  Created by Weiwei Chen on 7/28/15.
//  Copyright © 2015 Weiwei Chen. All rights reserved.
//

#include "ShapeLearning.hpp"
#include "ShapeGen.hpp"
#include "ShapeDiff.hpp"
#include "BasicMath.hpp"
#include "BodyModel.hpp"

bool isValidPoint(Point rook_points[][NUM_POINTS], int index, bool vertical);

void execute(Mat* src) {


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
    int foot_width = 100;
    int waist_width = 120;
    int waist_heigh = 150;
    double leg_angle = 60;
    double arm_angle = 60;
    BodyModel* model = new BodyModel( hip_width,
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
                                     waist_heigh, width / 2,  heigh / 4 , width, heigh, leg_angle, arm_angle);
    Mat mask = model->generateMat();

    int iteration = 0;
    const int max_iteration = 200;
    double distance = getAvgDistance(&mask, src);
    double eps = 0.01;
    while (iteration < max_iteration) {
      BodyModel *next_model = model->generateNextValidBodyModel();
      if (next_model != NULL) {
        mask = next_model->generateMat();
        double current_distance = getAvgDistance(&mask, src);
        if (current_distance - distance > eps) {
          distance = current_distance;
            delete model;
          model = next_model;
            iteration ++;
        } else {
            delete next_model;
        }
      }
    }

    imwrite("mask.jpg", mask);
    cout << "Done" << endl;
}

bool isValidPoint(Point rook_points[1][NUM_POINTS], int index, bool vertical) {
  Point point = rook_points[0][index];
  int last_index = (index - 1) % NUM_POINTS;
  int next_index = (index + 1) % NUM_POINTS;
  Point last_point = rook_points[0][last_index];
  Point next_point = rook_points[0][next_index];
  for (int i = 0; i < NUM_POINTS; i++) {
    // if (i == index) { continue; }
    int next_i = (i + 1) % NUM_POINTS;
    int last_i = (i - 1) % NUM_POINTS;
    Point segment_start = rook_points[0][i];
    Point segment_next = rook_points[0][next_i];
    if (index != next_i && index != i && next_index != next_i &&
        next_index != i && DoLineSegmentsIntersect(segment_start, segment_next,
                                                   point, next_point)) {
      return false;
    }
    Point segment_last = rook_points[0][last_i];
    if (index != last_i && index != i && last_index != last_i &&
        last_index != i && DoLineSegmentsIntersect(segment_start, segment_last,
                                                   point, last_point)) {
      return false;
    }
  }
  return true;
}