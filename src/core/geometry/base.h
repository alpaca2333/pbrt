#pragma once

#include "camera/ray.h"
#include "math/vector.h"

class HitInfo
{
public:
    bool IsHit;
    Point3f HitPoint;
    Vector3f Normal;    // 交点处的表面法向量
    double T;           // 交点对应的光线的参数 t
    Vector3f OutDir;    // 出射方向
    operator bool() { return IsHit; }
};

interface GeometryBase 
{
public:   
    virtual HitInfo TryHit(const Ray& r) = 0;
};