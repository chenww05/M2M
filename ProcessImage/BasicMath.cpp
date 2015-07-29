//
//  BasicMath.cpp
//  ProcessImage
//
//  Created by Weiwei Chen on 7/28/15.
//  Copyright © 2015 Weiwei Chen. All rights reserved.
//

#include "BasicMath.hpp"

bool IsOnSegment(double xi, double yi, double xj, double yj,
                        double xk, double yk) {
    return (xi <= xk || xj <= xk) && (xk <= xi || xk <= xj) &&
    (yi <= yk || yj <= yk) && (yk <= yi || yk <= yj);
}

char ComputeDirection(double xi, double yi, double xj, double yj,
                             double xk, double yk) {
    double a = (xk - xi) * (yj - yi);
    double b = (xj - xi) * (yk - yi);
    return a < b ? -1 : a > b ? 1 : 0;
}

/** Do line segments (x1, y1)--(x2, y2) and (x3, y3)--(x4, y4) intersect? */
bool DoLineSegmentsIntersect(double x1, double y1, double x2, double y2,
                             double x3, double y3, double x4, double y4) {
    char d1 = ComputeDirection(x3, y3, x4, y4, x1, y1);
    char d2 = ComputeDirection(x3, y3, x4, y4, x2, y2);
    char d3 = ComputeDirection(x1, y1, x2, y2, x3, y3);
    char d4 = ComputeDirection(x1, y1, x2, y2, x4, y4);
    return (((d1 > 0 && d2 < 0) || (d1 < 0 && d2 > 0)) &&
            ((d3 > 0 && d4 < 0) || (d3 < 0 && d4 > 0))) ||
    (d1 == 0 && IsOnSegment(x3, y3, x4, y4, x1, y1)) ||
    (d2 == 0 && IsOnSegment(x3, y3, x4, y4, x2, y2)) ||
    (d3 == 0 && IsOnSegment(x1, y1, x2, y2, x3, y3)) ||
    (d4 == 0 && IsOnSegment(x1, y1, x2, y2, x4, y4));
}

bool DoLineSegmentsIntersect(Point a1, Point a2, Point b1, Point b2) {
    return DoLineSegmentsIntersect(a1.x, a1.y, a2.x, a2.y, b1.x, b1.y, b2.x, b2.y);
}
