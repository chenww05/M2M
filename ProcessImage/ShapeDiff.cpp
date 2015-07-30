//
//  ShapeDiff.cpp
//  ProcessImage
//
//  Created by Weiwei Chen on 7/28/15.
//  Copyright © 2015 Weiwei Chen. All rights reserved.
//

#include "ShapeDiff.hpp"

double getAvgDistance(Mat* mask, Mat* img)
{
    int rows = img->rows;
    int cols = img->cols;
    CV_Assert(mask->rows == rows);
    CV_Assert(mask->cols == cols);
    double pixels_mask[3] = { 0, 0, 0 };
    int num_pixels_mask = 0;
    double pixels_unmask[3] = { 0, 0, 0 };
    int num_pixels_unmask = 0;
    //TODO cvSum(img) may work
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            Vec3b pixel = img->at<Vec3b>(i, j);
            Vec3b maskAt = mask->at<Vec3b>(i, j);
            if (maskAt[0] == 255 && maskAt[1] == 255 && maskAt[2] == 255) {
                num_pixels_mask++;
                pixels_mask[0] += pixel[0];
                pixels_mask[1] += pixel[1];
                pixels_mask[2] += pixel[2];
            }
            else {
                num_pixels_unmask++;
                pixels_unmask[0] += pixel[0];
                pixels_unmask[1] += pixel[1];
                pixels_unmask[2] += pixel[2];
            }
        }
    }
    //TODO the order may matter
    for (int i = 0; i < 3; i++) {
        pixels_mask[i] /= num_pixels_mask;
    }
    for (int i = 0; i < 3; i++) {
        pixels_unmask[i] /= num_pixels_unmask;
    }
    return sqrt(pow(pixels_mask[0] - pixels_unmask[0], 2)
        + pow(pixels_mask[0] - pixels_unmask[0], 2)
        + pow(pixels_mask[0] - pixels_unmask[0], 2));
}