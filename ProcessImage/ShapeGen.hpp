//
//  ShapeGen.hpp
//  ProcessImage
//
//  Created by Weiwei Chen on 7/28/15.
//  Copyright © 2015 Weiwei Chen. All rights reserved.
//

#ifndef ShapeGen_hpp
#define ShapeGen_hpp

#include <stdio.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/imgproc/imgproc.hpp"
#include <opencv2/imgcodecs.hpp>
using namespace cv;

Mat getInitialBodyMask();
Mat getBodyMask(Point[][26], int);

#endif /* ShapeGen_hpp */
