#pragma once

#pragma warning(disable:4244)
#include "types.h"
#include <algorithm>
using namespace std;

#define RGB_BYTE
#define RGB_FLOAT


/*
class CColor24
{
public:
	unsigned char r, g, b;

public:
	CColor24() { r = 0; g = 0; b = 0; }
	CColor24(unsigned char _r, unsigned char _g, unsigned char _b)
	  { r = _r; g = _g; b = _b; }
	
};
*/

struct CColorHSV
{
	CColorHSV() 
	{ 
		h = 0.0f; s = 0.0f; v = 0.0f; 
	}
	CColorHSV(float _h, float _s, float _v) 
	{ 
		h = _h; s = _s; v = _v; 
	}

	float dist(CColorHSV c)
	{
		float h1 = h;
	    float s1 = s;
	    float v1 = v;
	    float h2 = c.h;
	    float s2 = c.s;
	    float v2 = c.v;

	    float cosh1 = Cos(h1);
	    float sinh1 = Sin(h1);
	    float cosh2 = Cos(h2);
	    float sinh2 = Sin(h2);
		return  sqrt( Sqr(s1*cosh1-s2*cosh2) + Sqr(s1*sinh1-s2*sinh2) );
	}

	float h, s, v;
};




class CColor{
public:
	float r, g, b;

public:
	CColor(void) {r=0.0; g=0.0;b=0.0;}
	~CColor(void){ }
	CColor(float a)                   { r = a; g = a; b = a; }
	CColor(float _r,float _g,float _b)   { r = _r; g = _g; b = _b; }
	void  Set(float a)								 { r = a; g = a; b = a; }
	void  Set(float _r,float _g,float _b) { r = _r; g = _g; b = _b; }

	CColor  operator*(float a)         { return CColor(r * a,g * a,b * a); }
	CColor  operator/(float a)         { a = 1.0f / a; return CColor(r * a,g * a,b * a); }
	
	CColor  operator+(CColor &a)       { return CColor(r + a.r,g + a.g,b + a.b); }
	CColor  operator-(CColor &a)       { return CColor(r - a.r,g - a.g,b - a.b); }
	CColor  operator*(CColor &a)        { return CColor(r * a.r,g * a.g,b * a.b); }
	
	void operator=(const CColor &a)         { r = a.r; g = a.g; b = a.b; }
	void  operator+=(float a)          { r += a; g += a; b += a; }
	void operator-=(float a)          { r -= a; g -= a; b -= a; }
	void  operator*=(float a)          { r *= a; g *= a; b *= a; }
	void  operator/=(float a)          { a = 1.0f / a; r *= a; g *= a; b *= a; }
	void  operator+=(CColor &a)        { r += a.r; g += a.g; b += a.b; }
	void  operator-=(CColor &a)        { r -= a.r; g -= a.g; b -=a.b; }

	inline int Convert2RGB();
	inline int Convert2BGR();

	unsigned char CharColor(float f)
	{
		int c = f*255;
		if (c < 0) 
			return 0; 
		else if (c > 255) 
			return 255;
		else 
			return (unsigned char)c; 
	}
	unsigned char GetRed() { return CharColor(r); }
	unsigned char GetGreen(){ return CharColor(g); }
	unsigned char GetBlue(){ return CharColor(b); }

	float Dist(CColor &c)
	{ return sqrt( (c.r-r)*(c.r-r) + (c.g-g)*(c.g-g) + (c.b-b)*(c.b-b) );}
	float SquareDist(CColor &c)
	{ return ((c.r-r)*(c.r-r) + (c.g-g)*(c.g-g) + (c.b-b)*(c.b-b));}
 
	float HSVDist(CColor &c);
	float HSDist(CColor &c);

	float operator!() { return sqrt(r*r+g*g+b*b); }
	int operator<(CColor &c)
	{
		return (!(*this) < !c);
	}
};


CColorHSV RGB2HSV(CColor c);
CColor HSV2RGB(CColorHSV c);

class CColor24{
public:
	typedef unsigned char T;
public:
	T r, g, b;

public:
	CColor24(void) {r=0.0; g=0.0;b=0.0;}
	~CColor24(void){ }
	CColor24(T a)                   { r = a; g = a; b = a; }
	CColor24(T _r,T _g,T _b)   { r = _r; g = _g; b = _b; }
	void  Set(T a)								 { r = a; g = a; b = a; }
	void  Set(T _r,T _g,T _b) { r = _r; g = _g; b = _b; }

	CColor24  operator*(float a)         { return CColor24(r * a,g * a,b * a); }
	CColor24  operator/(float a)         { a = 1.0f / a; return CColor24(r * a,g * a,b * a); }
	
	CColor24  operator+(CColor24 &a)       { return CColor24(r + a.r,g + a.g,b + a.b); }
	CColor24  operator-(CColor24 &a)       { return CColor24(r - a.r,g - a.g,b - a.b); }
	CColor24  operator*(CColor24 &a)        { return CColor24(r * a.r,g * a.g,b * a.b); }
	
	void operator=(const CColor24 &a)         { r = a.r; g = a.g; b = a.b; }
	void  operator+=(float a)          { r += a; g += a; b += a; }
	void operator-=(float a)          { r -= a; g -= a; b -= a; }
	void  operator*=(float a)          { r *= a; g *= a; b *= a; }
	void  operator/=(float a)          { a = 1.0f / a; r *= a; g *= a; b *= a; }
	void  operator+=(CColor24 &a)        { r += a.r; g += a.g; b += a.b; }
	void  operator-=(CColor24 &a)        { r -= a.r; g -= a.g; b -=a.b; }

	float Dist(CColor24 &c)
	{ 
		return sqrt( 1.0*(c.r-r)*(c.r-r) + (c.g-g)*(c.g-g) + (c.b-b)*(c.b-b) );
	}

	float SquareDist(CColor24 &c)
	{
		return (1.0*(c.r-r)*(c.r-r) + (c.g-g)*(c.g-g) + (c.b-b)*(c.b-b));
	}
	
 
	float operator!() { return sqrt(1.0*r*r+g*g+b*b); }	
};


