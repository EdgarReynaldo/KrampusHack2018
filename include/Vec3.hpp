



#ifndef Vec3_HPP
#define Vec3_HPP


#include <cmath>
#include <cassert>



class Vec3 {
public :
   union {
      double x;
      double lateral;
      double yaw;
   };
   union {
      double y;
      double progress;
      double pitch;
   };
   union {
      double z;
      double elevation;
      double roll;
   };
   
   Vec3() : x(0.0) , y(0.0) , z(0.0) {}
   Vec3(double xpos , double ypos , double zpos) : x(xpos) , y(ypos) , z(zpos) {}
   
   Vec3 operator+(const Vec3& v) const {
      return Vec3(x + v.x , y + v.y , z + v.z);
   }
   Vec3 operator-(const Vec3& v) const {
      return *this + -v;
   }
   inline Vec3 operator-() const {
      return Vec3(-x,-y,-z);
   }
   inline Vec3& operator+=(const Vec3& v) {
      *this = *this + v;
      return *this;
   }
   inline Vec3& operator-=(const Vec3& v) {
      *this = *this - v;
      return *this;
   }
   inline Vec3& operator*=(double factor) {
      *this = *this*factor;
      return *this;
   }
   
   inline double Magnitude() const {return sqrt(MagnitudeSquared());}
   inline double MagnitudeSquared() const {return x*x + y*y + z*z;}
   
   void Normalize() {
      double l = Magnitude();
      assert(l != 0.0);
      *this *= 1.0/l;
   }

   friend Vec3 Rotate3D(const Vec3& axis , const double theta_radians);
   
   friend Vec3 operator*(const Vec3& lhs , double factor);
   friend Vec3 CrossProduct(const Vec3& a , const Vec3& b);
   friend double DotProduct(const Vec3& a , const Vec3& b);
};

Vec3 Rotate3D(const Vec3& vec , const Vec3& axis , const double theta_radians);

inline Vec3 operator*(const Vec3& lhs , double factor) {
   return Vec3(factor*lhs.x , factor*lhs.y , factor*lhs.z);
}

inline Vec3 CrossProduct(const Vec3& a , const Vec3& b) {
   return Vec3(a.y*b.z - a.z*b.y , a.z*b.x - a.x*b.z , a.x*b.y - a.y*b.x);
}

inline double DotProduct(const Vec3& a , const Vec3& b) {
   return a.x*b.x + a.y*b.y + a.z*b.z;
}

inline Vec3 ORIGIN() {return Vec3(0,0,0);}


#endif // Vec3_HPP



