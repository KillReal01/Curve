﻿#include "curve.hpp"

#include <iostream>
#include <vector>
#include <memory>
#include <cmath>
#include <algorithm>

// Point3d
Point3d::Point3d() : x(0), y(0), z(0) {}

Point3d::Point3d(double x, double y, double z) : x(x), y(y), z(z) {}

std::ostream& operator<<(std::ostream& s, Point3d& p) {
    s << "( " << p.x << ", " << p.y << ", " << p.z << " )";
    return s;
}


// Ellipse
Ellipse::Ellipse(double radius_x, double radius_y) : radius_x(radius_x), radius_y(radius_y) {}

Point3d Ellipse::getPoint3d(double t) const {
    return Point3d(radius_x * cos(t), radius_y * sin(t), 0);
}

Point3d Ellipse::getDerivative(double t) const {
    return Point3d(-radius_x * sin(t), radius_y * cos(t), 0);
}


// Circle
Circle::Circle(double radius) : Ellipse(radius, radius) {}

double Circle::getRadius() const{
    return radius_x;
}

Point3d Circle::getPoint3d(double t) const {
    return Point3d(radius_x * cos(t), radius_x * sin(t), 0);
}


//Hellix
Helix::Helix(double radius, double step) : Circle(radius), step(step) {}

Point3d Helix::getPoint3d(double t) const {
    return Point3d(radius_x * cos(t), radius_x * sin(t), step * t);
}

Point3d Helix::getDerivative(double t) const {
    return Point3d(-radius_x * sin(t), radius_x * cos(t), step);
}


//Compare
namespace circle{
    bool compareByRadius(const std::shared_ptr<Circle>& a, const std::shared_ptr<Circle>& b) {
        return a->getRadius() < b->getRadius();
    }
}
