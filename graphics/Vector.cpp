
#include ".\vector.h"


CVector::~CVector(void)
{
}


float CVector::GetDist(CVector p)
{
	return !(p-(*this));
}

float CVector::GetAngleDist(CVector p)  // 0 - 180
{
	float b = (*this)*p/(!(*this))/(!p);
	if (b>1.0) return 0;
	else if (b<-1.0) 
		return 180.0;
	else return fabs(Rad2deg(acos(b)));		
}

float CVector::GetAngle()
{
	float angle = GetAngleDist(CVector(1.0,0.0,0.0));	
	if (y<0.0f)
		angle = 360-angle;
	return angle;	
}


CVector CVector::GetRotatedX(double angle) const
{
	if(angle==0.0)
		return (*this);

	float sinAngle=(float)sin(PI*angle/180);
	float cosAngle=(float)cos(PI*angle/180);

	return CVector(	x,
						y*cosAngle - z*sinAngle,
						y*sinAngle + z*cosAngle);
}

void CVector::RotateX(double angle)
{
	(*this)=GetRotatedX(angle);
}

CVector CVector::GetRotatedY(double angle) const
{
	if(angle==0.0)
		return (*this);

	float sinAngle=(float)sin(PI*angle/180);
	float cosAngle=(float)cos(PI*angle/180);

	return CVector(	x*cosAngle + z*sinAngle,
						y,
						-x*sinAngle + z*cosAngle);
}

void CVector::RotateY(double angle)
{
	(*this)=GetRotatedY(angle);
}

CVector CVector::GetRotatedZ(double angle) const
{
	if(angle==0.0)
		return (*this);

	float sinAngle=(float)sin(PI*angle/180);
	float cosAngle=(float)cos(PI*angle/180);
	
	return CVector(x*cosAngle - y*sinAngle,
					x*sinAngle + y*cosAngle,
					z);
}

void CVector::RotateZ(double angle)
{
	(*this)=GetRotatedZ(angle);
}

CVector CVector::GetRotatedAxis(double angle, CVector & axis) const
{
	if(angle==0.0)
		return (*this);

	CVector u=axis.Normalized();

	CVector rotMatrixRow0, rotMatrixRow1, rotMatrixRow2;

	float sinAngle=(float)sin(PI*angle/180);
	float cosAngle=(float)cos(PI*angle/180);
	float oneMinusCosAngle=1.0f-cosAngle;

	rotMatrixRow0.x=(u.x)*(u.x) + cosAngle*(1-(u.x)*(u.x));
	rotMatrixRow0.y=(u.x)*(u.y)*(oneMinusCosAngle) - sinAngle*u.z;
	rotMatrixRow0.z=(u.x)*(u.z)*(oneMinusCosAngle) + sinAngle*u.y;

	rotMatrixRow1.x=(u.x)*(u.y)*(oneMinusCosAngle) + sinAngle*u.z;
	rotMatrixRow1.y=(u.y)*(u.y) + cosAngle*(1-(u.y)*(u.y));
	rotMatrixRow1.z=(u.y)*(u.z)*(oneMinusCosAngle) - sinAngle*u.x;
	
	rotMatrixRow2.x=(u.x)*(u.z)*(oneMinusCosAngle) - sinAngle*u.y;
	rotMatrixRow2.y=(u.y)*(u.z)*(oneMinusCosAngle) + sinAngle*u.x;
	rotMatrixRow2.z=(u.z)*(u.z) + cosAngle*(1-(u.z)*(u.z));

	return CVector(	(*this) * rotMatrixRow0,
		            (*this) * rotMatrixRow1,
					(*this) * rotMatrixRow2);
}

void CVector::RotateAxis(double angle, CVector & axis)
{
	(*this)=GetRotatedAxis(angle, axis);
}