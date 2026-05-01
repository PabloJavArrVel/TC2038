#include "Workshop.h"

Workshop::Workshop(const std::string& name, double x, double y)
    : name(name), point(x, y) {}

const std::string& Workshop::getName() const { return name; }
const Point& Workshop::getPoint() const { return point; }