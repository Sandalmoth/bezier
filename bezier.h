#ifndef __BEZIER_H__
#define __BEZIER_H__


#include <cstddef>
#include <array>
#include <vector>
#include <iostream>


// Utility for creating Bezier curves from a series of N dimensional control points.
template <size_t N>
class Bezier {
public:


  using Point = std::array<double, N>;


  static Point interpolate(const Point &a, const Point &b, double t) {
  // Linear interpolation between two points a and b. Position along line defined by t
    Point p = a;
    for (size_t i = 0; i < N; ++i) {
      p[i] += t * (b.at(i) - a.at(i));
    }
    return p;
  }


  // TODO check whether it's more reasonable to use one template iterator type
  template <typename It1, typename It2>
  static Point get_point(It1 first, It2 last, double t) {
    // Get a single point on a bezier curve (position defined by t = [0, 1])
    // length([first, last)) has to be at least 2. Bezier curves need at least 2 control points

    std::vector<Point> v_interpol;
    It1 second = first;
    ++second;
    while (second != last) {
      v_interpol.push_back(interpolate(*first, *second, t));
      first = second;
      ++second;
    }
    if (v_interpol.size() == 1) {
      return v_interpol.front();
    } else {
      return get_point(v_interpol.begin(), v_interpol.end(), t);
    }
  }


  // TODO check whether it's more reasonable to use two template iterator types (one input, one output)
  template <typename It1, typename It2, typename It3>
  static void get_curve(It1 first, It2 last, It3 out, size_t k) {
    // Get points on bezier curve defined by control points in [first, last)
    // Overwrites elements starting from *out to *(out+9).
    // Make sure you have space :)
    // Also, length([first, last)) has to be at least 2. Bezier curves need at least 2 control points

    double kk = k - 1;
    for (size_t i = 0; i < k; ++i) {
      *out = get_point(first, last, i / kk);
      ++out;
    }
  }


};


#endif
