#include ".\color.h"



inline int  CColor::Convert2RGB()
{
	int ir = int(r*255); if (ir < 0) ir = 0; if (ir > 255) ir = 255;
	int ig = int(g*255); if (ig < 0) ig = 0; if (ig > 255) ig = 255;
	int ib = int(b*255); if (ib < 0) ib = 0; if (ib > 255) ib = 255;
	return (ir << 16) + (ig << 8) + ib;
}

inline int  CColor::Convert2BGR()
{
	int ir = int(r*255); if (ir < 0) ir = 0; if (ir > 255) ir = 255;
	int ig = int(g*255); if (ig < 0) ig = 0; if (ig > 255) ig = 255;
	int ib = int(b*255); if (ib < 0) ib = 0; if (ib > 255) ib = 255;
	return (ib << 16) + (ig << 8) + ir;
}



/* calculat the hsv distance between two rgb color,
   first transform color rgb into hsv color,
   then ...
 */

float CColor::HSVDist(CColor &c)
{
	CColorHSV c1 = RGB2HSV(c);
	CColorHSV c2 = RGB2HSV(*this);

	float h1 = c1.h;
	float s1 = c1.s;
	float v1 = c1.v;
	float h2 = c2.h;
	float s2 = c2.s;
	float v2 = c2.v;

	float cosh1 = Cos(h1);
	float sinh1 = Sin(h1);
	float cosh2 = Cos(h2);
	float sinh2 = Sin(h2);
	
	static float scale = 1.0/sqrt(5.0f); 	
	float dist = sqrt( Sqr(v1-v2) + Sqr(s1*cosh1-s2*cosh2) + Sqr(s1*sinh1-s2*sinh2) ) * scale;	
	return dist;
}

float CColor::HSDist(CColor &c)
{
	CColorHSV c1 = RGB2HSV(c);
	CColorHSV c2 = RGB2HSV(*this);

	float h1 = c1.h;
	float s1 = c1.s;
	float v1 = c1.v;
	float h2 = c2.h;
	float s2 = c2.s;
	float v2 = c2.v;

	float cosh1 = Cos(h1);
	float sinh1 = Sin(h1);
	float cosh2 = Cos(h2);
	float sinh2 = Sin(h2);
		
	float dist = sqrt( Sqr(s1*cosh1-s2*cosh2) + Sqr(s1*sinh1-s2*sinh2) );
	return dist;
}

/*
   Calculate HSV from RGB
   Hue is in degrees
   Lightness is betweeen 0 and 1
   Saturation is between 0 and 1
*/

CColorHSV RGB2HSV(CColor c)
{
   float themin,themax,delta;
   CColorHSV c2;
   
   themin = std::min(c.r,std::min(c.g,c.b));
   themax = std::max(c.r,std::max(c.g,c.b));
   delta = themax - themin;
   c2.v = themax;
   c2.s = 0;
   if (themax > 0)
      c2.s = delta / themax;
   c2.h = 0;
   if (delta > 0) {
      if (themax == c.r && themax != c.g)
         c2.h += (c.g - c.b) / delta;
      if (themax == c.g && themax != c.b)
         c2.h += (2 + (c.b - c.r) / delta);
      if (themax == c.b && themax != c.r)
         c2.h += (4 + (c.r - c.g) / delta);
      c2.h *= 60;
	  if (c2.h<0.0f) c2.h+=360.0;
   }
   return c2;
}


/*
   Calculate RGB from HSV, reverse of RGB2HSV()
   Hue is in degrees
   Lightness is between 0 and 1
   Saturation is between 0 and 1
*/

CColor HSV2RGB(CColorHSV c1)
{
   CColor c2,sat;

   while (c1.h < 0)
      c1.h += 360;
   while (c1.h > 360)
      c1.h -= 360;

   if (c1.h < 120) {
      sat.r = (120 - c1.h) / 60.0;
      sat.g = c1.h / 60.0;
      sat.b = 0;
   } else if (c1.h < 240) {
      sat.r = 0;
      sat.g = (240 - c1.h) / 60.0;
      sat.b = (c1.h - 120) / 60.0;
   } else {
      sat.r = (c1.h - 240) / 60.0;
      sat.g = 0;
      sat.b = (360 - c1.h) / 60.0;
   }
   
   sat.r = std::min(sat.r,1.0f);
   sat.g = std::min(sat.g,1.0f);
   sat.b = std::min(sat.b,1.0f);

   c2.r = (1 - c1.s + c1.s * sat.r) * c1.v;
   c2.g = (1 - c1.s + c1.s * sat.g) * c1.v;
   c2.b = (1 - c1.s + c1.s * sat.b) * c1.v;

   return(c2);
}





