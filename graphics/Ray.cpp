
#include ".\ray.h"


CRay::CRay(CVector _origin, CVector _dir)
{
	orig = _origin; dir = _dir;
}

CRay::~CRay(void)
{
}

CVector CRay::GetPos(float t)
{
	return (orig + dir * t);
}

float CRay::GetDist(CVector &p)
{
	// (o+t*d-p)*d=0
	// (o-p)*d+t*d*d=0;
	//t = (p-o)*d/(d*d)
	float t = (p - orig) * dir / (dir * dir);
	float dist = p.GetDist(orig+dir*t);
	return dist;
	
}

float CRay::GetNearest(CVector &p)
{
	// (o+t*d-p)*d=0
	// (o-p)*d+t*d*d=0;
	//t = (p-o)*d/(d*d)
	float t = (p - orig) * dir / (dir * dir);
	return t;
}

bool CRay::Intersect(CTriangle &tri, float &t)
{
	CVector n = tri.GetNormal();
	float s = dir * n;
	if ( fabs(s) < EPSILON ) return  false;
	t = (tri.p0 - orig) * n / s;
	CVector pt = GetPos(t); 
	if ( t < 0 || !(tri.IsInside(pt)) ) return false;
	return true;
}


bool CRay::GetInsPtWithTriangle(CTriangle &tri, CVector &pt)
{
	// p = o(rigin) + d(ir) * t
	// (p - p0) * n = 0 
	// ==> ( o - p0 + d * t ) * n = 0
	// ==> t = ( p0 - o ) * n / ( d * n) 
	// p0 could be any point on the triangle
	CVector n = tri.GetNormal();
	float s = dir * n;
	if ( fabs(s) < EPSILON ) return  false;
	float t = (tri.p0 - orig) * n / s;
	pt = GetPos(t); 
	if ( t < 0 || !(tri.IsInside(pt)) ) return false;
	return true;

}

bool CRay::GetInsPtWithPlane(CVector &pt0, CVector &pt1, CVector &pt2, CVector &ins_pt)
{
	CTriangle tri(pt0, pt1, pt2);
	CVector n = tri.GetNormal();
	float s = dir * n;
	if ( fabs(s) < EPSILON ) return false;
	float t = (pt0 - orig) * n / s;
	if (t < 0) return false;
	ins_pt = GetPos(t); 
	return true;
}


