#include ".\triangle.h"


CTriangle::CTriangle(CVector _p0, CVector _p1, CVector _p2)
{
	p0 = _p0; p1 = _p1; p2 = _p2;
	n = GetNormal(p0, p1, p2).Normalized();
}

CTriangle::CTriangle(CTriangle &tri)
{
	p0 = tri.p0; p1 = tri.p1; p2 = tri.p2;
	n = tri.n;
}


CTriangle::CTriangle() : p0(0.0, 0.0, 0.0), p1(1.0, 0.0, 0.0), p2(0.0, 1.0, 0.0)
{
	n = GetNormal(p0, p1, p2).Normalized();
}

void CTriangle::operator=(CTriangle &tri)
{
	p0 = tri.p0; p1 = tri.p1; p2 = tri.p2;
	n = tri.n;
}

CTriangle::~CTriangle(void)
{
}

CVector CTriangle::GetNormal(CVector &_p0, CVector &_p1, CVector &_p2) 
{
	CVector t1 = (_p0^_p1);
	CVector t2 = (_p1^_p2);
	CVector t3 = (_p2^_p0);
	return (t1+t2+t3);

	//return (p0-p1)^(p2-p1);
}
;
CVector CTriangle::GetNormal() 
{
	return n;
}

bool CTriangle::IsInside(CVector &p) 
{
   CVector sign0 = GetNormal(p0, p1, p);  // not normalized for performance
   CVector sign1 = GetNormal(p1, p2, p);
   CVector sign2 = GetNormal(p2, p0, p);

   //opposite direction
   if ((!sign0) > EPSILON)  // should be far from the edge
   {
      if (n*sign0<0) return false;
   }

   if ((!sign1) > EPSILON)
   {
      if (n*sign1<0) return false;
   }

   if ((!sign2) > EPSILON)
   {
      if (n*sign2<0) return false;
   }

   return true;
};
