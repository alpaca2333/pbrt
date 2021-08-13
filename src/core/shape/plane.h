#include <cmath>

#include "shape/base.h"

/* Plane 表示满足方程 Ax + By + Cz + D = 0 的平面 */
class Plane: public IShape
{
public:
    Plane(double A, double B, double C, double D);
    virtual HitInfo TryHit(const Ray& r);
    virtual Bound GetBound();
protected:
    double a, b, c, d;
};

inline HitInfo Plane::TryHit(const Ray& r)
{
    auto a = r.Origin();
    auto b = r.Direction();
    double t = - (this->a * a[0] + this->b * a[1] + c * a[2] + d) / (this->a * b[0] + this->b * b[1] + c * b[2]);
    if (std::isnan(t))
    {
        return {false};
    }
    HitInfo h{true};
    h.HitPoint = r.At(t);
    
}