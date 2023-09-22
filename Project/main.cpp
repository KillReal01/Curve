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


namespace {
    bool compareByRadius(const std::shared_ptr<Circle>& a, const std::shared_ptr<Circle>& b) {
        return a->getRadius() < b->getRadius();
    }
}


int main() {
    srand(time(NULL));
    int n = 10;

    // 2. init data
    std::vector<std::shared_ptr<Curve>> vec;
    for (int i = 0; i < n; ++i) {
        std::shared_ptr<Curve> ptr;
        switch (rand() % 3) {
        case 0:
            ptr = std::make_shared<Ellipse>(rand() % 10 + 1, rand() % 10 + 1);
            break;
        case 1:
            ptr = std::make_shared<Circle>(rand() % 10 + 1);
            break;
        case 2:
            ptr = std::make_shared<Helix>(rand() % 10 + 1, (rand() % 10 + 1) / 10.0);
            break;
        }
        vec.push_back(ptr);
    }

    // 3. 
    double t = M_PI_4;
    for (const auto& item : vec) {
        Point3d tmp;
        tmp = item->getPoint3d(t);
        std::cout << "Point: " << tmp << "\n";
        tmp = item->getDerivative(t);
        std::cout << "Derivative: " << tmp << "\n\n";
    }

    // 4.
    std::vector<std::shared_ptr<Circle>> circle_vec;
    for (auto& item : vec) {
        if (auto circle_ptr = std::dynamic_pointer_cast<Circle>(item)) {
            circle_vec.push_back(circle_ptr);
        }
    }

    // 5.
    std::sort(circle_vec.begin(), circle_vec.end(), compareByRadius);

    // 6.
    double totalRadiusSum = 0;
    for (const auto& circle : circle_vec) {
        totalRadiusSum += circle->getRadius();
    }

    // 8.

    return 0;
}

