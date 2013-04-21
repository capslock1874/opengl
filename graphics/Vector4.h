#pragma once

#include "vector.h"
class CVector4
{
public:
	CVector4(void);
	CVector4(float _x, float _y, float _z, float _w);
	CVector4(float *v);
	~CVector4(void);


	void  Set(float _x, float _y, float _z, float _w);
	
	//rotations
	void RotateX(double angle);
	CVector4 GetRotatedX(double angle) const;
	void RotateY(double angle);
	CVector4 GetRotatedY(double angle) const;
	void RotateZ(double angle);
	CVector4 GetRotatedZ(double angle) const;
	void RotateAxis(double angle, CVector &axis);
	CVector4 GetRotatedAxis(double angle, CVector & axis) const;

	//operator
	CVector4  operator-() const								 { return CVector4(-x,-y,-z,-w); }
	CVector4  operator*(float a)  const       { return CVector4(x*a, y*a, z*a, w*a); }
	CVector4  operator/(float a)  const       { a = 1.0f/a; return CVector4(x*a, y*a, z*a, w*a); }
	CVector4  operator+(CVector4 &a) const      { return CVector4(x+a.x, y+a.y, z+a.z, w+a.w); }
	CVector4  operator-(CVector4 &a) const      { return CVector4(x-a.x, y-a.y, z-a.z, w-a.w); }

	float  operator*(CVector4 &a)   const  { return (x*a.x + y*a.y + z*a.z + w*a.w); }   // Dot product
	//CVector4  operator^(CVector4 &a) const    // Cross product
	
	void operator=(CVector4 &a)         { x = a.x; y = a.y; z = a.z; w = a.w; }
	void  operator*=(float a)          { x *= a; y *= a; z *= a; w *= a; }
	void  operator/=(float a)          { a = 1.0f / a; x *= a; y *= a; z *= a; w *= a; }
	void  operator+=(CVector4 &a)        { x += a.x; y += a.y; z += a.z; w += a.w; }
	void  operator-=(CVector4 &a)        { x -= a.x; y -= a.y; z -=a.z; w -= a.w; }
	bool  operator==(CVector4 &a)        
	{ return ( fabs(x-a.x)<EPSILON && fabs(y-a.y)<EPSILON 
	           && fabs(z-a.z)<EPSILON && fabs(w-a.w)<EPSILON ); }
	bool  operator!=(CVector4 &a) 	{ return ( !(*this==a) ); }
	


public:
	float x, y, z, w;
};
