//
//  ShadowDetect.hpp
//  ProcessImage
//
//  Created by Weiwei Chen on 10/16/15.
//  Copyright © 2015 Weiwei Chen. All rights reserved.
//

#ifndef ShadowDetect_hpp
#define ShadowDetect_hpp

#include "BasicMath.hpp"


#include <iostream>
#include <stdio.h>

using namespace cv;
using namespace std;

void ShadowDetect(IplImage* currImg, IplImage* bkImg, Mat* shadowdeImg, double th1, double th2, double th3, double th4);

#endif /* ShadowDetect_hpp */

