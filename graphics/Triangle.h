#pragma once

#include "Vector.h"

class CTriangle
{
public:
	CTriangle(CVector _p0, CVector _p1, CVector _p2);
	CTriangle(CTriangle &tri);
	
	CTriangle(void);
	~CTriangle(void);
	
	CVector GetNormal(); // not normarlized
	bool IsInside(CVector &p);
	void operator=(CTriangle &tri);
	

protected:
	CVector GetNormal(CVector &_p0, CVector &_p1, CVector &_p2);

public:
	CVector p0, p1, p2;
	CVector n;
};
