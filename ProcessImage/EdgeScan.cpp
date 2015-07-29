//
//  EdgeScan.cpp
//  ProcessImage
//
//  Created by Weiwei Chen on 7/27/15.
//  Copyright © 2015 Weiwei Chen. All rights reserved.
//

#include "EdgeScan.hpp"
#define PI 3.14159265

/*
Pixel getHeadPoint(Mat* img);
Pixel getHeadPointFromLine(Mat* img, int rowIndex, int leftmost, int rightmost);
Pixel getNextPoint(Mat* img, Pixel current, double last_angle, int step,
                   double& angle);
double calculateAngle(Pixel current_point, Pixel next_point);
void thresh_callback(int, void*);

Mat edge_scan(Mat* img) {
  Mat foregroundMask = Mat::zeros(img->rows, img->cols, CV_8UC1);
  Pixel head = getHeadPoint(img);

  int step = 10;
  double angle = 1.0;
  double current_angle = 0.0;
  int max_num_points = 100;
  int num_points = 1;
  Pixel current_point = head;
  bool increaseStep = false;
  unordered_map<Pixel, int> allPoints = {{current_point, 1}};
  while (num_points <= max_num_points) {
    if (!increaseStep) {
      step = 10;
    }
    Pixel next_point =
        getNextPoint(img, current_point, current_angle, step, angle);
      
      if (next_point.first == 0 && next_point.second == 0) {
          continue;
      }

    if (allPoints.find(next_point) != allPoints.end()) {
      // change step do it again.
      step += 10;
      increaseStep = true;
      continue;
    }
    allPoints.emplace(next_point, 1);
    increaseStep = false;
    num_points++;
    // update
    current_angle = calculateAngle(current_point, next_point);
    current_point = next_point;
    foregroundMask.at<uchar>(current_point.first, current_point.second) = 255;
  }
  namedWindow("", CV_WINDOW_AUTOSIZE);

  imshow("Processed Image", foregroundMask);
  imwrite("foregroundMask.jpg", foregroundMask);
  //    waitKey(0);

  return foregroundMask;
}

Pixel getNextPoint(Mat* img, Pixel current_point, double last_angle, int step,
                   double& angle) {
  double current_angle = last_angle;
    int max_search = 360.0 / abs(angle);
    int num_search = 0;
  while (num_search < max_search) {
    int new_row = current_point.first + step * sin(current_angle * PI / 180);
    int new_col = current_point.second + step * cos(current_angle * PI / 180);

    if (new_row < img->rows && new_col < img->cols && new_row >= 0 &&
        new_col >= 0 && img->at<uchar>(new_row, new_col) > 250) {
      cout << new_row << ", " << new_col << endl;
      return {new_row, new_col};
    }
    current_angle += angle;
      num_search ++;
  }
    angle = -angle;
    cout << "Angle changed: " << angle << endl;
  return {0, 0};
}
double calculateAngle(Pixel current_point, Pixel next_point) {
  if (next_point.second == current_point.second) {
    if (next_point.first > current_point.first) {
      return 90.0;
    } else {
      return 270.0;
    }
  }
  return atan((next_point.first - current_point.first) /
              (next_point.second - current_point.second)) *
         180 / PI;
}
Pixel getHeadPoint(Mat* img) {
  if (img == NULL) {
    cout << "Parameters Error. " << endl;
    return {0, 0};
  }
  double col = img->cols;
  for (int i = 0; i < img->rows / 2; i++) {
    Pixel pair =
        getHeadPointFromLine(img, i, (int)(col / 3), (int)(col * 2 / 3));
    if (pair.first != 0 || pair.second != 0) {
      cout << "Found the head point at " << pair.first << ", " << pair.second
           << endl;
      return pair;
    }
  }
  return {0, 0};
}
 

Pixel getHeadPointFromLine(Mat* img, int rowIndex, int leftmost,
                           int rightmost) {
  if (img == NULL || img->rows < rowIndex || img->cols < rightmost) {
    cout << "Parameters Error. " << endl;
    return {0, 0};
  }
  for (int j = leftmost; j <= rightmost; j++) {
    int val = img->at<uchar>(rowIndex, j);
    if (val > 250) {
      return {rowIndex, j};
    }
  }
  return {0, 0};
}
*/