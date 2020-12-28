#include "math/vector.h"

class Ray 
{
public:
    Ray() { }
    Ray(const Vector3f& origin, const Vector3f direction) 
        : origin(origin), direction(direction) { }
    Point3f Origin() const { return origin; }
    Vector3f Direction() const { return direction; }
    // y = o + t * dir
    Point3f At(double t) const { return origin + direction * t; }
    double DistanceTo(const Point3f& p) const;
protected:
    Point3f origin;
    Vector3f direction;
};

double DistanceOf(const Point3f& p, const Ray& r);
double DistanceOf(const Ray& r, const Point3f& p);