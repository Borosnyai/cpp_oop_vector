#include "vector.hpp"
#include<cmath>

namespace geometry{
  Vector::Vector(){
    x = 0.0;
    y = 0.0;
    z = 0.0;
  }

  Vector::Vector(double x, double y, double z){
    this->x = x;
    this->y = y;
    this->z = z;
  }
 Vector Vector::plus(const Vector& o) const{
   
    return Vector(this->x + o.x,this->y + o.y,this->z + o.z);
  }
  Vector Vector::minus(const Vector& o) const{

    return Vector(this->x - o.x,this->y - o.y,this->z - o.z);
  }

  Vector Vector::times(double s) const{


    return Vector(this->x * s, this->y * s, this->z * s);
  }
  Vector Vector::cross(const Vector& o) const{

    return Vector(
      this->y * o.z - this->z * o.y,
     this->z * o.x - this->x * o.z,
     this->x * o.y - this->y * o.x
    );
  }

  // Scalar operations - return numbers
  double Vector::times(const Vector& o) const{
    double result = this->x * o.x + this->y * o.y + this->z * o.z;
    return result;
  }
  double Vector::dot (const Vector& o) const{
    double result = this->x * o.x + this->y * o.y + this->z * o.z;
    return result;

  }
  double Vector::length() const{


    return sqrt(x * x + y * y + z * z);
  }

  double Vector::magnitude () const{

    return length();
  }

  void Vector::print(std::ostream& o) const{
    o << "(" << x << ", " << y << ", " << z << ")";
  }

}
