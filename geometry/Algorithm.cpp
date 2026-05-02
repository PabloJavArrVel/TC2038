#include "Point.h"
#include "Workshop.h"
#include "Algorithm.h"
#include <cmath>
#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <limits>

/*
    Función: parse_input
    Propósito: leer los datos de entrada y construir el arreglo de talleres

    Retorna:
    - vector<Workshop> con los talleres leídos

    Complejidad: O(n)
*/
std::vector<Workshop> parse_input() {
    int n;
    std::cin >> n;

    std::vector<Workshop> workshops;
    workshops.reserve(n);
    

    for (int i = 0; i < n; i++) {
        std::string name;
        double x, y;
        std::cin >> name >> x >> y;
        workshops.emplace_back(name, x, y);
    }

    return workshops;
}

/*
    Función: solve
    Propósito: encontrar el par de talleres más cercano utilizando
    el algoritmo de divide y vencerás

    Parámetros:
    - workshops: lista de talleres

    Retorna:
    - tupla con:
        * puntero al primer taller
        * puntero al segundo taller
        * distancia mínima entre ellos

    Complejidad: O(n log n)
*/
std::tuple<const Workshop*, const Workshop*, double> solve(std::vector<Workshop>& workshops) {

    //Agnostic overhead (unmapping workshops to points O(N))
    std::vector<Point> points;
    points.reserve(workshops.size());
    for (const auto& w : workshops)
        points.push_back(w.getPoint());

    std::vector<Point> original = points; // ← snapshot before dividing mutates it

    //auto [p1, p2, dist] = brute_force(points);
    auto [p1, p2, dist] = divide_conquer(points);

    auto it1 = std::find(original.begin(), original.end(), p1);
    auto it2 = std::find(original.begin(), original.end(), p2);

    size_t i = std::distance(original.begin(), it1);
    size_t j = std::distance(original.begin(), it2);


    return std::tuple(&workshops[i], &workshops[j], dist);
}


/*
    Función: output_results
    Propósito: imprimir el resultado en el formato requerido

    Parámetros:
    - result: tupla con los talleres más cercanos y su distancia

    Complejidad: O(1)
*/
void output_results(const std::tuple<const Workshop*, const Workshop*, double>& result) {
    const Workshop* a = std::get<0>(result);
    const Workshop* b = std::get<1>(result);
    double dist       = std::get<2>(result);

    if (a->getName() > b->getName())
    std::swap(a, b);

    std::cout << std::fixed << std::setprecision(2);
    std::cout << "Los dos talleres que mas riesgo representan en Tultepec son "
              << a->getName() << " y " << b->getName()
              << " (distancia " << dist << ")\n";
}


/*
    Función: euclidean_dist
    Propósito: calcular la distancia euclidiana entre dos puntos

    Parámetros:
    - p: primer punto
    - q: segundo punto

    Retorna:
    - distancia euclidiana entre p y q

    Complejidad: O(1)
*/
double euclidean_dist(Point &p, Point &q){
    double diffx = q.getX() - p.getX();
    double diffy = q.getY() - p.getY();
    return std::sqrt(diffx*diffx + diffy*diffy);
}

/*
    Función: brute_force
    Propósito: encontrar el par de puntos más cercano evaluando
    todas las combinaciones posibles

    Parámetros:
    - points: lista de puntos

    Retorna:
    - tupla con los dos puntos más cercanos y su distancia

    Complejidad: O(n^2)
*/
std::tuple<Point, Point, double> brute_force(std::vector<Point>& points) {
    size_t n = points.size();
    size_t best_i = 0, best_j = 1;
    double min = std::numeric_limits<double>::infinity();
    double dist = 0.0;

    for (size_t i = 0; i < n; i++) {
        for (size_t j = i + 1; j < n; j++) {
            dist = euclidean_dist(points[i],points[j]);
            if (dist < min) {
                min = dist;
                best_i = i;
                best_j = j;
            }
        }
    }
    return std::tuple(points[best_i], points[best_j], min);
}

/*
    Función: divide_conquer
    Propósito: encontrar el par de puntos más cercano utilizando
    la estrategia de divide y vencerás

    Parámetros:
    - points: lista de puntos

    Retorna:
    - tupla con los dos puntos más cercanos y su distancia mínima

    Complejidad: O(n log n)
*/
std::tuple<const Point, const Point, double> divide_conquer(std::vector<Point>& points) {
    size_t n = points.size();

    if (n <= 3)
        return brute_force(points);

     // Sort by X (nlog(n))
    std::sort(points.begin(), points.end(), [](const Point& a, const Point& b) {
        return a.getX() < b.getX();
    });

    // Midpoint
    size_t mid = n / 2;
    double mid_x = points[mid].getX();

    // Split regions
    std::vector<Point> left(points.begin(), points.begin() + mid);
    std::vector<Point> right(points.begin() + mid, points.end());

    // Recurse
    auto [p1, p2, delta_left]  = divide_conquer(left);
    auto [p3, p4, delta_right] = divide_conquer(right);


    // Best so far
    double delta;
    Point best_a;
    Point best_b;

    if (delta_left < delta_right) {
        delta  = delta_left;
        best_a = p1;
        best_b = p2;
    } else {
        delta  = delta_right;
        best_a = p3;
        best_b = p4;
    }

    // Build strip — points within +/-delta of the dividing line
    std::vector<Point> strip;
    for (const Point& p : points)
        // "how far is this point from the dividing line in X?" 
        // If that distance is less than delta, the point is inside the area
        // if it's more we don't care since it can't beat the best right now
        if (std::abs(p.getX() - mid_x) < delta)
            strip.push_back(p);

    // Sort area by Y because we only care about pairs whose Y-distance is also < delta
    // if two points are farther apart in Y alone, their actual distance is already ≥ delta
    // thus they can't improve our answer
    std::sort(strip.begin(), strip.end(), [](const Point& a, const Point& b) {
        return a.getY() < b.getY();
    });

    // Check strip — at most 7 neighbors. 
    for (size_t i = 0; i < strip.size(); i++) {
        for (size_t j = i + 1; j < strip.size() && (strip[j].getY() - strip[i].getY()) < delta; j++) {
            double d = euclidean_dist(strip[i], strip[j]);
            if (d < delta) {
                delta  = d;
                best_a = strip[i];
                best_b = strip[j];
            }
        }
    }

    return std::tuple(best_a, best_b, delta);

}
