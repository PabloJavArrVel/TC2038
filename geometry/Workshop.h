#pragma once
#include <string>
#include "Point.h"

class Workshop {
private:
    std::string name;
    Point point;

public:
    Workshop(const std::string& name, double x, double y);
    
    const std::string& getName() const;
    const Point& getPoint() const;
};