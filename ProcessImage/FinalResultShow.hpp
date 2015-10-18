//
//  FinalResultShow.hpp
//  ProcessImage
//
//  Created by Weiwei Chen on 10/17/15.
//  Copyright © 2015 Weiwei Chen. All rights reserved.
//

#ifndef FinalResultShow_hpp
#define FinalResultShow_hpp
#include <stdio.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/imgproc/imgproc.hpp"
#include <opencv2/imgcodecs.hpp>

#include <iostream>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

#include "BodyModel.hpp"
#include "AngleAdjust.hpp"

using namespace cv;
using namespace std;
void showImg(BodyModel* , Mat* , int) ;


#endif /* FinalResultShow_hpp */
