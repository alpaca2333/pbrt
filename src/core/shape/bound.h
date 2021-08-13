#pragma once

#include "spdlog/spdlog.h"

#include "camera/ray.h"
#include "math/vector.h"

using namespace spdlog;

class Bound
{
public:
    Bound(Point3f p_min, Point3f p_max);
    bool IsHit(const Ray& r) const;
protected:
    Point3f p_min, p_max;
};


// implementations

inline Bound::Bound(Point3f p_min, Point3f p_max)
{
    p_min = Point3f{
        std::min(p_min[0], p_max[0]),
        std::min(p_min[1], p_max[1]),
        std::min(p_min[2], p_max[2]),
    };
    p_max = Point3f{
        std::max(p_min[0], p_max[0]),
        std::max(p_min[1], p_max[1]),
        std::max(p_min[2], p_max[2]),
    };
}

inline bool Bound::IsHit(const Ray &r) const
{
    const auto &a = r.Origin();
    const auto &b = r.Direction();
    double tmin = 0, tmax = 1.0 / 0;
    for (int i = 0; i < 3; ++i)
    {
        float tmp = (p_min[i] - a[i]) / b[i];
        if (tmp > tmin) tmin = tmp;
        tmp = (p_max[i] - a[i]) / b[i];
        if (tmp < tmax) tmax = tmp;
        debug("tmin {} tmax {}", tmin, tmax);
    }
    return tmin < tmax;
}