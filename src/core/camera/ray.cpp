#include "ray.h"

double Ray::DistanceTo(const Point3f& p) const
{
    if (p == origin) return 0;
    if (direction == Vector3f::Zero()) 
    {
        throw "The ray's direction vector must not be zero.";
    }
    Vector3f vOA = p - origin;
    double cosTheta = vOA.Dot(direction) / vOA.Length() / direction.Length();
    double sinTheta = sqrt(1 - cosTheta * cosTheta);
    return sinTheta * vOA.Length();
}

double DistanceOf(const Point3f& p, const Ray& r)
{
    return r.DistanceTo(p);
}

double DistanceOf(const Ray& r, const Point3f& p)
{
    return r.DistanceTo(p);
}