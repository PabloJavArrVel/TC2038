#include "Point.h"

Point::Point(double x, double y) : x(x), y(y) {}
Point::Point() : x(0), y(0) {}
double Point::getX() const { return x; }
double Point::getY() const { return y; }
void Point::setX(double x) { this->x = x; }
void Point::setY(double y) { this->y = y; }
bool Point::operator==(const Point& other) const {
    return x == other.x && y == other.y;
}