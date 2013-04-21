#pragma once
#include <math.h>

#define PI       3.14159265358979323846
#define MAXREAL  3.402823466E+38f
#define EPSILON  1e-4

inline float Rad2deg(float x) { return float(x * 180 / PI); }
inline float Deg2rad(float x) { return float(x * PI / 180); }
inline int Sign(float x){return (x>0?1:-1);}
inline int Lower(float x) { return (int) x;}
inline int Upper(float x) { int y = (int)x; if (x>y) return y+1; else return y; }

inline float Cos(float deg) { return float(cos(Deg2rad(deg))); }
inline float Sin(float deg) { return float(sin(Deg2rad(deg))); }
inline float Sqr(float x) { return float(x*x); }
