#include ".\vector4.h"

CVector4::CVector4(void)
{
	x = 0.0; y = 0.0; z = 0.0; w = 0.0; 
}

CVector4::CVector4(float _x, float _y, float _z, float _w)
{
   x = _x; y = _y; z = _z; w = _w; 
}

CVector4::CVector4(float *v)
{ 
	x = v[0]; y = v[1]; z = v[2]; w = v[3]; 
}

CVector4::~CVector4(void)
{
}


void CVector4::RotateX(double angle)
{
	(*this)=GetRotatedX(angle);
}

CVector4 CVector4::GetRotatedX(double angle) const
{
	CVector v3d(x, y, z);

	v3d.RotateX(angle);

	return CVector4(v3d.x, v3d.y, v3d.z, w);
}

void CVector4::RotateY(double angle)
{
	(*this)=GetRotatedY(angle);
}

CVector4 CVector4::GetRotatedY(double angle) const
{
	CVector v3d(x, y, z);

	v3d.RotateY(angle);

	return CVector4(v3d.x, v3d.y, v3d.z, w);
}

void CVector4::RotateZ(double angle)
{
	(*this)=GetRotatedZ(angle);
}

CVector4 CVector4::GetRotatedZ(double angle) const
{
	CVector v3d(x, y, z);

	v3d.RotateZ(angle);

	return CVector4(v3d.x, v3d.y, v3d.z, w);
}

void CVector4::RotateAxis(double angle, CVector & axis)
{
	(*this)=GetRotatedAxis(angle, axis);
}

CVector4 CVector4::GetRotatedAxis(double angle, CVector & axis) const
{
	CVector v3d(x, y, z);

	v3d.RotateAxis(angle, axis);

	return CVector4(v3d.x, v3d.y, v3d.z, w);
}





