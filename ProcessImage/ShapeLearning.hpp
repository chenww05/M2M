//
//  ShapeLearning.hpp
//  ProcessImage
//
//  Created by Weiwei Chen on 7/28/15.
//  Copyright © 2015 Weiwei Chen. All rights reserved.
//

#ifndef ShapeLearning_hpp
#define ShapeLearning_hpp
#include <stdio.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/imgproc/imgproc.hpp"
#include <opencv2/imgcodecs.hpp>
#include "BodyModel.hpp"

#include <iostream>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
using namespace cv;
using namespace std;


#define NUM_POINTS 26

void execute(Mat* src) ;
pair<BodyModel*, BodyModel*> generateLeftRightModel(BodyModel* original, int index, int step);
BodyModel* generateModel(BodyModel* original, int index, int step) ;
BodyModel* findBestModel(BodyModel* model, int index, Mat* src);


#endif /* ShapeLearning_hpp */
