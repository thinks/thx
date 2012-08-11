//------------------------------------------------------------------------------
//
// Contributors: 
//             1) Tommy Hinks
//
//------------------------------------------------------------------------------

#ifndef THX_COLOR_SPACE_HPP_INCLUDED
#define THX_COLOR_SPACE_HPP_INCLUDED

#include "thx_vec.hpp"
#include "thx_traits.hpp"
#include "thx_utils.hpp"
//#include <cmath>
#include <algorithm>	// std::min & std::max
#include <cassert>

//------------------------------------------------------------------------------

namespace thx
{

// xyYToXYZ
// --------
//! Convert xyY to XYZ.

template<typename S>
vec<3,S>
xyYToXYZ(const vec<3,S> &xyY)
{
	assert(traits<S>::zero <= xyY[0]);
	assert(traits<S>::zero <  xyY[1]);
	assert(traits<S>::zero <= xyY[2]);
	const S y_ratio(xyY[2]/xyY[1]);

	return vec<3,S>(xyY[0]*y_ratio, 
				    xyY[2], 
					(traits<S>::one - xyY[0] - xyY[1])*y_ratio);
}

//template <typename S>
//void 
//	XYZ2xyY(const S X_XYZ, const S Y_XYZ, const S Z_XYZ, S* x, S* y, S* Y)
//{
//	assert(0 != x);
//	assert(0 != y);
//	assert(0 != Y);
//	const S w(X_XYZ + Y_XYZ + Z_XYZ);
//	assert(!is_zero(w));
//	*x = X_XYZ/w;
//	*y = Y_XYZ/w;
//	*Y = Y_XYZ;
//}

//------------------------------------------------------------------------------

//--------------
// XYZ <-> RGB
//--------------

//template <typename S>
//void 
//	RGB2XYZ(const S R, const S G, const S B, S* X, S* Y, S* Z)
//{
//	assert(0 != X);					// Valid pointers.
//	assert(0 != Y);
//	assert(0 != Z);
//
//	// Valid input values.
//	//
//	assert(scalar_traits<S>::zero <= R && R <= scalar_traits<S>::one);	
//	assert(scalar_traits<S>::zero <= G && G <= scalar_traits<S>::one);
//	assert(scalar_traits<S>::zero <= B && B <= scalar_traits<S>::one);
//
//	// Matrix multiplication, R709 coefficients.
//	//
//	*X = R*static_cast<S>(0.4125) + 
//		G*static_cast<S>(0.3576) + 
//		B*static_cast<S>(0.1804);
//	*Y = R*static_cast<S>(0.2127) + 
//		G*static_cast<S>(0.7152) + 
//		B*static_cast<S>(0.0722);
//	*Z = R*static_cast<S>(0.0193) + 
//		G*static_cast<S>(0.1192) + 
//		B*static_cast<S>(0.9503);
//	
//	// Valid output values.
//	//
//	//assert(scalar_traits<S>::zero <= *X && *X <= scalar_traits<S>::one);	
//	//assert(scalar_traits<S>::zero <= *Y && *Y <= scalar_traits<S>::one);
//	//assert(scalar_traits<S>::zero <= *Z && *Z <= scalar_traits<S>::one);
//}

//------------------------------------------------------------------------------

// XYZToRGB
// --------
//! Convert XYZ to RGB.

template<typename S>
void 
XYZToRGB(const S X, const S Y, const S Z,	// Input
		S* R, S* G, S* B)					// Output
{
	assert(0 != R);
	assert(0 != G);
	assert(0 != B);

	// Matrix multiplication, R709 coefficients.
	//
	*R = clamp(
			static_cast<S>(0.01)*( X*static_cast<S>(3.2405) - 
			Y*static_cast<S>(1.5371) - Z*static_cast<S>(0.4985)), 
			traits<S>::zero, traits<S>::one);
	*G = clamp(
			static_cast<S>(0.01)*(-X*static_cast<S>(0.9693) + 
			Y*static_cast<S>(1.8760) + Z*static_cast<S>(0.0416)), 
			traits<S>::zero, traits<S>::one);
	*B = clamp(
			static_cast<S>(0.01)*( X*static_cast<S>(0.0556) - 
			Y*static_cast<S>(0.2040) + Z*static_cast<S>(1.0572)), 
			traits<S>::zero, traits<S>::one);
}

//------------------------------------------------------------------------------

//--------------
// RGB <-> sRGB
//--------------

template <typename S>
void
RGB2sRGB(const S R, const S G, const S B,		// Input
		 S* sR, S* sG, S* sB,					// Output
		 const S gamma		= static_cast<S>(2.2),	// Parameters.
		 const S offset		= static_cast<S>(0.055),
		 const S slope		= static_cast<S>(12.92),
		 const S transition = static_cast<S>(0.003))
{
	assert(0 != sR);
	assert(0 != sG);
	assert(0 != sB);
	assert(traits<S>::zero <= R && R <= traits<S>::one); // Valid input range.
	assert(traits<S>::zero <= G && G <= traits<S>::one);
	assert(traits<S>::zero <= B && B <= traits<S>::one);
	assert(traits<S>::zero < gamma);

	const S inv_gamma(traits<S>::one/gamma);
	const S offset_p1(traits<S>::one + offset);

	*sR = (R < transition) ? 
			(clamp(slope*R, traits<S>::zero, traits<S>::one)) : 
			(clamp(offset_p1*pow(R, inv_gamma) - offset, 
			 traits<S>::zero, traits<S>::one));
	*sG = (G < transition) ? 
			(clamp(slope*G, traits<S>::zero, traits<S>::one)) : 
			(clamp(offset_p1*pow(G, inv_gamma) - offset, 
			 traits<S>::zero, traits<S>::one));
	*sB = (B < transition) ? 
			(clamp(slope*B, traits<S>::zero, traits<S>::one)) : 
			(clamp(offset_p1*pow(B, inv_gamma) - offset, 
			 traits<S>::zero, traits<S>::one));
}

//template <typename S>
//void
//	sRGB2RGB(const S sR, const S sG, const S sB, S* R, S* G, S* B)
//{
//	assert(0 != R);
//	assert(0 != G);
//	assert(0 != B);
//
//	// Valid input values.
//	//
//	assert(scalar_traits<S>::zero <= sR && sR <= scalar_traits<S>::one);
//	assert(scalar_traits<S>::zero <= sG && sG <= scalar_traits<S>::one);
//	assert(scalar_traits<S>::zero <= sB && sB <= scalar_traits<S>::one);
//
//	static const S offset(static_cast<S>(0.055));
//	static const S slope(static_cast<S>(12.92));
//	static const S gamma(scalar_traits<S>::one/static_cast<S>(0.42));
//	static const S transition(static_cast<S>(0.04045));
//
//	static const S inv_offset_factor(
//		scalar_traits<S>::one/(scalar_traits<S>::one + offset));
//	static const S inv_slope(scalar_traits<S>::one/slope);
//
//	*R = (sR <= transition) ? (sR*inv_slope) : 
//		(pow((sR + offset)*inv_offset_factor, gamma));
//	*G = (sG <= transition) ? (sG*inv_slope) : 
//		(pow((sG + offset)*inv_offset_factor, gamma));
//	*B = (sB <= transition) ? (sB*inv_slope) : 
//		(pow((sB + offset)*inv_offset_factor, gamma));
//
//	// Valid output values.
//	//
//	assert(scalar_traits<S>::zero <= *R && *R <= scalar_traits<S>::one);
//	assert(scalar_traits<S>::zero <= *G && *G <= scalar_traits<S>::one);
//	assert(scalar_traits<S>::zero <= *B && *B <= scalar_traits<S>::one);
//}

//=============================================================================

//--------------
// RGB <-> HSV
//--------------

template<typename S>
void 
rgb2hsv(const S r, const S g, const S b,	// Input
		S* h, S* s, S* v)					// Output
{
	assert(0 != h);
	assert(0 != s);
	assert(0 != v);

	const S minc = std::min<S>(r, std::min<S>(g, b));
	const S maxc = std::max<S>(r, std::max<S>(g, b));

	*v = maxc;
	if( equal(maxc, minc) ) 
	{
		*h = traits<S>::zero;
		*s = traits<S>::zero;
	}
	else
	{
		const S diff(maxc - minc);
		const S inv_diff(static_cast<S>(1)/diff);
		*s = diff/maxc;
		const S rc((maxc - r)*inv_diff);
		const S gc((maxc - g)*inv_diff);
		const S bc((maxc - b)*inv_diff);

		if( equal(r, maxc) )		{ *h = bc - gc; }
		else if( equal(g, maxc) )	{ *h = static_cast<S>(2) + rc - bc; }
		else						{ *h = static_cast<S>(4) + gc - rc; }

		*h = frac((static_cast<S>(1)/6)*(*h));
	}
}

//=============================================================================

template<typename S>
void 
hsv2rgb(const S h, const S s, const S v,	// Input
		S* r, S* g, S* b)					// Output
{
	assert(0 != r);
	assert(0 != g);
	assert(0 != b);

	if( is_zero(s) )
	{
		*r = v;
		*g = v;
		*b = v;
	}
	else
	{
		const S tmp(static_cast<S>(6)*h);
		const int32 i(floor_int32(tmp));
		const S f((tmp) - i);
		const S p(v*(traits<S>::one() - s));
		const S q(v*(traits<S>::one() - s*f));
		const S t(v*(traits<S>::one() - s*(traits<S>::one() - f)));

		switch( i%6 )
		{
		case 0:
			*r = v; 
			*g = t; 
			*b = p;
			break;
		case 1:
			*r = q; 
			*g = v; 
			*b = p;
			break;
		case 2:
			*r = p; 
			*g = v; 
			*b = t;
			break;
		case 3:
			*r = p; 
			*g = q; 
			*b = v; 
			break;
		case 4:
			*r = t; 
			*g = p; 
			*b = v;
			break;
		case 5:
			*r = v; 
			*g = p; 
			*b = q;
			break;
		}
	}
}

//=============================================================================
}	// Namespace: thx.

#endif	// THX_COLOR_SPACE_HPP_INCLUDED
