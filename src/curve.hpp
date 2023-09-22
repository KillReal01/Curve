#define _USE_MATH_DEFINES

#include <iostream>
#include <vector>
#include <memory>
#include <cmath>
#include <algorithm>

struct Point3d {
    double x;
    double y;
    double z;

    Point3d() : x(0), y(0), z(0) {}
    Point3d(double x, double y, double z) : x(x), y(y), z(z) {}
    Point3d(const Point3d& other) = default;
    Point3d& operator=(const Point3d& other) = default;

    friend std::ostream& operator<<(std::ostream& s, Point3d& p) {
        s << "( " << p.x << ", " << p.y << ", " << p.z << " )";
        return s;
    }
};


class Curve {
public:
    virtual Point3d getPoint3d(double t) = 0;
    virtual Point3d getDerivative(double t) = 0;
    virtual ~Curve() {}
};


class Ellipse : public Curve {
public:
    Ellipse(double radius_x, double radius_y) : radius_x(radius_x), radius_y(radius_y) {}

    Point3d getPoint3d(double t) override {
        return Point3d(radius_x * cos(t), radius_y * sin(t), 0);
    }

    Point3d getDerivative(double t) override {
        return Point3d(-radius_x * sin(t), radius_y * cos(t), 0);
    }

    virtual ~Ellipse() {}

protected:
    double radius_x;

private:
    double radius_y;
};


class Circle : public Ellipse {
public:
    Circle(double radius) : Ellipse(radius, radius) {}

    double getRadius() {
        return radius_x;
    }

    Point3d getPoint3d(double t) override {

        return Point3d(radius_x * cos(t), radius_x * sin(t), 0);
    }

    virtual ~Circle() {}
};

class Helix : public Circle {
public:
    Helix(double radius, double step) : Circle(radius), step(step) {}

    Point3d getPoint3d(double t) override {
        return Point3d(radius_x * cos(t), radius_x * sin(t), step * t);
    }

    Point3d getDerivative(double t) override {
        return Point3d(-radius_x * sin(t), radius_x * cos(t), step);
    }

    virtual ~Helix() {}

private:
    double step;
};


namespace circle{
    bool compareByRadius(const std::shared_ptr<Circle>& a, const std::shared_ptr<Circle>& b) {
        return a->getRadius() < b->getRadius();
    }
}

