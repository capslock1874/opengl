#pragma once

#include "Vector.h"
#include "Triangle.h"
class CRay
{
public:
	CVector orig, dir;
public:
	CRay() 
	{ orig = CVector(0.0f, 0.0f, 0.0f); dir = CVector(1.0f, 0.0f, 0.0f); }
	CRay(CVector _origin, CVector _dir);
	~CRay(void);
	float GetDist(CVector &p);  // the distance between point and ray
	
	CVector GetPos(float t);  // get the point by parameter t
	bool GetInsPtWithTriangle(CTriangle &tri, CVector &pt); // ray and triangle
	bool GetInsPtWithPlane(CVector &Pt0, CVector &pt1, CVector &pt2, CVector &ins_pt); // ray and plane defined by 3 points

	bool Intersect(CTriangle &tri, float &t);
	//´¹×ãµÄ²ÎÊý
	float GetNearest(CVector &p);
	
};

