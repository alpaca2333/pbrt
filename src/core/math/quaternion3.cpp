//
// Created by black on 2020/8/30.
//

#include "quaternion3.h"
Quaternion3 &Quaternion3::operator+=(const Quaternion3 &q)
{
  w += q.w;
  v += q.v;
  return *this;
}
Quaternion3 Quaternion3::operator+(const Quaternion3 &q)
{

}
