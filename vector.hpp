#ifndef VECTOR_HPP
#define VECTOR_HPP
#include<cmath>
#include<iostream>

namespace geometry {
class Vector {

public:
  // public data memebers
  double x;
  double y;
  double z;

  // Constructors
  Vector();
  // Constructors
  Vector(double x, double y, double z);

  // Vector operations - return new vectors
  Vector plus(const Vector& o) const;
  Vector minus(const Vector& o) const;
  Vector times(double s) const;
  Vector cross(const Vector& o) const;

  // Scalar operations - return numbers
  double times(const Vector& o) const;
  double dot (const Vector& o) const;
  double length() const;
  double magnitude() const;

  // Output
  void print(std::ostream& o) const;
};
}// end of the namespace

#endif  // VECTOR_HPP

