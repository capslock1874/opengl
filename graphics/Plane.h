#pragma once

#include "Vector.h"
#include "Triangle.h"
#include <vector>
using namespace std;

class CPlane
{
public:
	CPlane(void){}
	CPlane(CVector &p1, CVector &p2, CVector &p3);
	~CPlane(void){}
	
	static void GetPlane(CVector &p1, CVector &p2, CVector &p3, 
		                 CVector &n, float &d);
	static void GetPlane(CVector &p1, CVector &p2, CVector &p3, 
		                 float &a, float &b, float &c, float &d);
	static void GetPlane(float x1, float y1, float z1, 
					     float x2, float y2, float z2,
					     float x3, float y3, float z3, 
					     float &a, float &b, float &c, float &d);

	// input a plane : plane, output an intersection line : p = p0 + t * dir
	bool IntersectPlane(CPlane &plane, CVector &p0, CVector &dir);
	// input a line segment : (p0,p1), output an intersection point : IntPoint	
	bool IntersectLineSegment(CVector &p0, CVector &p1, CVector &IntPoint);
	// input a line : (p0, p1), output an intersection point : IntPoint
	bool IntersectLine(CVector &p0, CVector &p1, CVector &IntPoint);
	// input a triangle : tri, output 2 intersection points  : points
	bool IntersectTriangle(CTriangle &tri, vector<CVector> &points);

public:
	CVector m_Normal;
	float m_D;	
	// a = m_Normal.x 
	// b = m_Normal.y
	// c = m_Normal.z
	// d = m_D
};
