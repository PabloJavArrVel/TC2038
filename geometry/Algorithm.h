#pragma once

#include "Point.h"
#include "Workshop.h"
#include <vector>
#include <tuple>

//main
std::vector<Workshop> parse_input();
std::tuple<const Workshop*, const Workshop*, double> solve(std::vector<Workshop>&  workshops);
void output_results(const std::tuple<const Workshop*, const Workshop*, double>&);

//Agnostic to the problem for reusability, they only know about points, not workshops. It does add overhead.
std::tuple<Point, Point, double> brute_force(std::vector<Point>& points);
std::tuple<const Point, const Point, double> divide_conquer (std::vector<Point>&  points);


double euclidean_dist(const Point& p, const Point& q);
