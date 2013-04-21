//#include "stdafx.h"
#include "plane.h"

CPlane::CPlane(CVector &p1, CVector &p2, CVector &p3)
{
	GetPlane(p1, p2, p3, m_Normal, m_D);
}



void CPlane::GetPlane(CVector &p1, CVector &p2, CVector &p3, 
		              CVector &n, float &d)
{
	CVector v1 = p2-p1;
	CVector v2 = p3-p1;
	n = v1^v2;
	d = n*p1;
}


void CPlane::GetPlane(CVector &p1, CVector &p2, CVector &p3, 
		                 float &a, float &b, float &c, float &d)
{
	// (p-p1)*n = 0
	CVector v1 = p2-p1;
	CVector v2 = p3-p1;
	CVector n = v1^v2;
	a = n.x;
	b = n.y;
	c = n.z;
	d = n*p1;
}

void CPlane::GetPlane(float x1, float y1, float z1, 
					  float x2, float y2, float z2,
					  float x3, float y3, float z3, 
					  float &a, float &b, float &c, float &d)
{
	a = y1 * (z2 - z3) + y2 * (z3 - z1) + y3 * (z1 - z2);
    b = z1 * (x2 - x3) + z2 * (x3 - x1) + z3 * (x1 - x2);
	c = x1 * (y2 - y3) + x2 * (y3 - y1) + x3 * (y1 - y2);
	d = - ( x1 * (y2 * z3 - y3 * z2) + x2 * (y3 * z1 - y1 * z3) + 
	        x3 * (y1 * z2 - y2 * z1) );
}

// line equation : p = p0 + t*dir;
bool CPlane::IntersectPlane(CPlane &plane, CVector &p0, CVector &dir)
{
	CVector &n1 = m_Normal;
	CVector &n2 = plane.m_Normal;
	float &d1 = m_D;
	float &d2 = plane.m_D;

	dir = (n1^n2).Normalized();
	if (dir.GetSquaredLength() < EPSILON) return false;

	float a1 = n1*n1;
	float a2 = n2*n2;
	float a3 = n1*n2;
	float determinant = a1*a2 - a3*a3;
	float c1 = (d1*a2 - d2*a3)/determinant;
	float c2 = (d2*a1 - d1*a3)/determinant;
	p0 = n1*c1 + n2*c2;
	return true;
}

bool CPlane::IntersectLineSegment(CVector &p0, CVector &p1, CVector &IntPoint)
{
	float a2 = m_Normal * (p0 - p1);
	if (fabs(a2)<EPSILON) return false;
	float a1 = m_Normal * p0 + m_D;
	float u = a1 / a2;
	if ( u>1.0f || u<0.0f ) return false;
	IntPoint = p0 + (p1-p0)*u;
	return true;
}


bool CPlane::IntersectLine(CVector &p0, CVector &p1, CVector &IntPoint)
{
	float a2 = m_Normal * (p0 - p1);
	if (fabs(a2)<EPSILON) return false;
	float a1 = m_Normal * p0 + m_D;
	float u = a1 / a2;
	IntPoint = p0 + (p1-p0)*u;
	return true;
}

bool CPlane::IntersectTriangle(CTriangle &tri, vector<CVector> &points)
{	
	CVector p;
	points.clear();
	if ( IntersectLineSegment(tri.p0, tri.p1, p) )
	{
		points.push_back(p);		
	}
	if ( IntersectLineSegment(tri.p1, tri.p2, p) )
	{
		points.push_back(p);				
	}
	if ( IntersectLineSegment(tri.p2, tri.p0, p) )
	{
		points.push_back(p);				
	}

	return (points.size() == 2);	
}
