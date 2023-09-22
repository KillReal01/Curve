#include <iostream>
#include <vector>
#include <memory>
#include <cmath>
#include <algorithm>


struct Point3d {
    double x;
    double y;
    double z;

    Point3d();
    Point3d(double x, double y, double z);
    Point3d(const Point3d& other) = default;
    Point3d& operator=(const Point3d& other) = default;
    friend std::ostream& operator<<(std::ostream& s, Point3d& p);
};


class Curve {
public:
    virtual Point3d getPoint3d(double t) const = 0;
    virtual Point3d getDerivative(double t) const = 0;
    virtual ~Curve() {}
};


class Ellipse : public Curve {
public:
    Ellipse(double radius_x, double radius_y);
    Point3d getPoint3d(double t) const override;
    Point3d getDerivative(double t) const override;
    virtual ~Ellipse() {}

protected:
    double radius_x;

private:
    double radius_y;
};


class Circle : public Ellipse {
public:
    Circle(double radius);
    double getRadius() const;
    Point3d getPoint3d(double t)const override;
    virtual ~Circle() {}
};

class Helix : public Circle {
public:
    Helix(double radius, double step);
    Point3d getPoint3d(double t) const override;
    Point3d getDerivative(double t) const override;
    virtual ~Helix() {}

private:
    double step;
};


namespace circle{
    bool compareByRadius(const std::shared_ptr<Circle>& a, const std::shared_ptr<Circle>& b);
}

