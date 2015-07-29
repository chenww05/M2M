//
//  BasicMath.hpp
//  ProcessImage
//
//  Created by Weiwei Chen on 7/28/15.
//  Copyright © 2015 Weiwei Chen. All rights reserved.
//

#ifndef BasicMath_hpp
#define BasicMath_hpp

#include <stdio.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/imgproc/imgproc.hpp"
#include <opencv2/imgcodecs.hpp>
using namespace cv;

/** Do line segments (x1, y1)--(x2, y2) and (x3, y3)--(x4, y4) intersect? */
bool DoLineSegmentsIntersect(Point a1, Point a2, Point b1, Point b2) ;
#endif /* BasicMath_hpp */
