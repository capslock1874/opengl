#pragma once

#include <math.h>
#include "Types.h"


class CVector
{
public:
	float x, y, z;

	CVector() {x=0.0; y=0.0;z=0.0;}
	CVector(float i,float j,float k)   { x = i; y = j; z = k; }
	~CVector(void);

	void  Set(float i,float j,float k) { x = i; y = j; z = k; }
	CVector  SetLength(float l){  return ((*this)*(l / !*this)); }
	CVector  Normalized() { return SetLength(1.0);}
	
	CVector  operator-() const								 { return CVector(-x,-y,-z); }
	float operator!() const                { return sqrt(x * x + y * y + z * z); } // Length
	float GetSquaredLength() { return (x * x + y * y + z * z); }
	
	
	CVector  operator*(float a)  const       { return CVector(x * a,y * a,z * a); }
	CVector  operator/(float a)  const       { a = 1.0f / a; return CVector(x * a,y * a,z * a); }
	CVector  operator+(CVector &a) const      { return CVector(x + a.x,y + a.y,z + a.z); }
	CVector  operator-(CVector &a) const      { return CVector(x - a.x,y - a.y,z - a.z); }

	float  operator*(CVector &a)   const     { return x * a.x + y * a.y + z * a.z; } // Dot product
	CVector  operator^(CVector &a) const      { return CVector(y * a.z - a.y * z, z * a.x - a.z * x, x * a.y - a.x * y); } // Cross product
	
	void operator=(const CVector &a)         { x = a.x; y = a.y; z = a.z; }
	void  operator+=(float a)          { x += a; y += a; z += a; }
	void operator-=(float a)          { x -= a; y -= a; z -= a; }
	void  operator*=(float a)          { x *= a; y *= a; z *= a; }
	void  operator/=(float a)          { a = 1.0f / a; x *= a; y *= a; z *= a; }
	void  operator+=(CVector &a)        { x += a.x; y += a.y; z += a.z; }
	void  operator-=(CVector &a)        { x -= a.x; y -= a.y; z -=a.z; }
	bool  operator==(CVector &a)        
	  { return ( fabs(x-a.x)<EPSILON && fabs(y-a.y)<EPSILON && fabs(z-a.z)<EPSILON ); }
	bool  operator!=(CVector &a)   { return ( !(*this==a) ); }

	//rotations
	void RotateX(double angle);
	CVector GetRotatedX(double angle) const;
	void RotateY(double angle);
	CVector GetRotatedY(double angle) const;
	void RotateZ(double angle);
	CVector GetRotatedZ(double angle) const;
	void RotateAxis(double angle, CVector & axis);
	CVector GetRotatedAxis(double angle, CVector & axis) const;


	float GetDist(CVector p);
	float GetAngleDist(CVector p);  // 0 - 180
	float GetAngle();


};





