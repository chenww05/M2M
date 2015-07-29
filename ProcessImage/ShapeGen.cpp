//
//  ShapeGen.cpp
//  ProcessImage
//
//  Created by Weiwei Chen on 7/28/15.
//  Copyright © 2015 Weiwei Chen. All rights reserved.
//

#include "ShapeGen.hpp"

Mat getBodyMask(Point points[][26], int numPoints) {
    // Create black empty images
    int width=1280;
    int heigh=960;
    Mat mask = Mat::zeros( width, heigh, CV_8UC3 );
    const Point* ppt[1] = { points[0] };
    int npt[] = { numPoints };
    fillPoly( mask, ppt, npt, 1, Scalar( 255, 255, 255 ), 8 );
    return mask;
}

Mat getInitialBodyMask()
{
    int width=1280;
    int heigh=960;
    // Create black empty images
    Mat mask = Mat::zeros( width, heigh, CV_8UC3 );
    
    /** Create body points */
    Point rook_points[1][26];
    rook_points[0][0] = Point( heigh/4.0, 7*width/8.0 );//左足
    rook_points[0][1] = Point( 3*heigh/8.0, 7*width/8.0 );
    rook_points[0][2] = Point( 3.75*heigh/8.0, 5*width/8.0 );//裆部
    rook_points[0][3] = Point( 4.25*heigh/8.0, 5*width/8.0 );
    rook_points[0][4] = Point( 5*heigh/8.0, 7*width/8.0 );//右足
    rook_points[0][5] = Point( 3*heigh/4.0, 7*width/8.0 );
    rook_points[0][6] = Point( 3*heigh/4.0, 13*width/16.0 );
    rook_points[0][7] = Point( 11*heigh/16.0, 13*width/16.0 );
    rook_points[0][8] = Point( 19*heigh/32.0, 4*width/8.0 );//右臀
    rook_points[0][9] = Point( 19*heigh/32.0, 3*width/8.0 );//右腋窝
    rook_points[0][10] = Point( 3*heigh/4.0, 3*width/8.0 );//右肘部
    rook_points[0][11] = Point( 3*heigh/4.0, width/8.0 );
    rook_points[0][12] = Point( 26*heigh/40.0, width/8.0 );
    rook_points[0][13] = Point( 26*heigh/40.0, width/4.0 );
    rook_points[0][14] = Point( 22*heigh/40.0, width/4.0 );
    rook_points[0][15] = Point( 22*heigh/40.0, width/8.0 );
    rook_points[0][16] = Point( 18*heigh/40.0, width/8.0 );
    rook_points[0][17] = Point( 18*heigh/40.0, width/4.0 );
    rook_points[0][18] = Point( 14*heigh/40.0, width/4.0 );
    rook_points[0][19] = Point( 14*heigh/40.0, width/8.0 );
    rook_points[0][20] = Point( heigh/4.0, width/8.0 );
    rook_points[0][21] = Point( heigh/4.0, 3*width/8.0 );//左肘部
    rook_points[0][22] = Point( 13*heigh/32.0, 3*width/8.0 );//左腋窝
    rook_points[0][23] = Point( 13*heigh/32.0, 4*width/8.0 );//左臀
    rook_points[0][24] = Point( 5*heigh/16.0, 13*width/16.0 );
    rook_points[0][25] = Point( heigh/4.0, 13*width/16.0) ;
    
    const Point* ppt[1] = { rook_points[0] };
    int npt[] = { 26 };
    
    fillPoly( mask, ppt, npt, 1, Scalar( 255, 255, 255 ), 8 );
//    for (int i = 0; i < 26; i ++) {
//        circle( mask, rook_points[0][i] , 5.0, Scalar( 255, 255, 255 ), 1, 8 );
//        
//        imshow("Input", mask);
//        waitKey(0);
//    }
//    waitKey(0);
    return mask;
}