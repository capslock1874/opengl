#include ".\arcball.h"
#include <assert.h>

CArcBall::CArcBall(void)
{
	SetBound(10, 10);
	Reset();
}

CArcBall::CArcBall(float width, float height)
{
	SetBound(width, height);
	Reset();
}

CArcBall::~CArcBall(void)
{
}

void CArcBall::Reset()
{
	m_Mat.LoadIdentity();
}

void CArcBall::SetBound(float width, float height)
{
	  assert((width > 1.0f) && (height > 1.0f));

      //Set adjustment factor for width/height
      m_fScaleWidth  = 1.0f / ((width  - 1.0f) * 0.5f);
      m_fScaleHeight = 1.0f / ((height - 1.0f) * 0.5f);
}

//Arcball sphere constants:
//Diameter is       2.0f
//Radius is         1.0f
//Radius squared is 1.0f


// input vector is the window pos without any transformation

CVector CArcBall::SphereCoord(CVector &v)
{
	CVector s;
	s.x = (v.x * m_fScaleWidth) - 1.0f;
	s.y = 1.0f - (v.y * m_fScaleHeight);
	

	float len = s.GetSquaredLength();

	if (len > 1.0f)
	{
		s = s.Normalized();
	}
	else
	{
		s.z = sqrt(1.0f - len);
	}

	return s;
}


float * CArcBall::GetMatrix()
{
	return m_Mat.m;
}

void CArcBall::ApplyRotation(CVector &start, CVector &end)
{
	if (start == end) return;
	m_Mat = GetRotation(start, end) * m_Mat;
}

CMatrix44 CArcBall::GetRotation(CVector &start, CVector &end)
{
	CVector s1 = SphereCoord(start);
	CVector s2 = SphereCoord(end);
	CVector dir = (s1^s2).Normalized();		
	float t = s1*s2;	
	float angle;
	if (fabs(t) <= 1.0f) 
		angle = Rad2deg(acos(t))*2;
	else 
		angle = 0;
	
	CMatrix44 mat;
	if ( dir.GetSquaredLength() > 1e-5 )
	{
	   mat.SetRotationAxis(angle, dir);
	}
	else
	{
		mat.LoadIdentity();
	}
	
	return mat;
}