#pragma once

#include "matrix44.h"
#include "vector.h"

class CArcBall
{
public:
	CMatrix44 m_Mat;

	float m_fScaleWidth;
	float m_fScaleHeight;

public:
	CArcBall(void);
	CArcBall(float width, float height);
	~CArcBall(void);

	void Reset();
	void SetBound(float width, float height);
	float * GetMatrix();
	void ApplyRotation(CVector &start, CVector &end);
	

protected:
	CVector SphereCoord(CVector &v);
	CMatrix44 GetRotation(CVector &start, CVector &end);

};
