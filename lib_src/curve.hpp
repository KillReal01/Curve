#pragma once

#include <iostream>
#include <memory>

struct Point3d {
    double x;
    double y;
    double z;

    Point3d();
    Point3d(double x, double y, double z);
    Point3d(const Point3d&) = default;
    Point3d& operator=(const Point3d&) = default;

    friend std::ostream& operator<<(std::ostream& s, const Point3d& p);
};


class Curve{
public:
    virtual Point3d getPoint3d(double t) const = 0;
    virtual Point3d getDerivative(double t) const = 0;

    virtual ~Curve() = default;
};


class Ellipse : public Curve {
public:
    Ellipse();
    Ellipse(double radius_x, double radius_y);
    Ellipse(const Ellipse&) = default;
    Ellipse& operator=(const Ellipse&) = default;

    Point3d getPoint3d(double t) const override;
    Point3d getDerivative(double t) const override;

    virtual ~Ellipse() = default;

protected:
    double radius_x;

private:
    double radius_y;
};


class Circle : public Ellipse {
public:
    Circle();
    Circle(double radius);
    Circle(const Circle&) = default;
    Circle& operator=(const Circle&) = default;

    double getRadius() const;
    Point3d getPoint3d(double t)const override;

    virtual ~Circle() = default;
};

class Helix : public Circle {
public:
    Helix();
    Helix(double radius, double step);
    Helix(const Helix&) = default;
    Helix& operator=(const Helix&) = default;

    Point3d getPoint3d(double t) const override;
    Point3d getDerivative(double t) const override;
    
    virtual ~Helix() = default;

private:
    double step;
};


namespace circle{
    bool compareByRadius(const std::shared_ptr<Circle>& a, const std::shared_ptr<Circle>& b);
}

