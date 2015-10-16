//
//  ShapeDiff.hpp
//  ProcessImage
//
//  Created by Weiwei Chen on 7/28/15.
//  Copyright © 2015 Weiwei Chen. All rights reserved.
//

#ifndef ShapeDiff_hpp
#define ShapeDiff_hpp

#include <stdio.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/imgproc/imgproc.hpp"
#include <opencv2/imgcodecs.hpp>
#include <iostream>
using namespace cv;
using namespace std;

double getAvgDistance(Mat* mask, Mat* img) ;


#endif /* ShapeDiff_hpp */
