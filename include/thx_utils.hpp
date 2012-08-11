//------------------------------------------------------------------------------
//
// Contributors: 
//             1) Tommy Hinks
//
//------------------------------------------------------------------------------

#ifndef THX_UTILS_HPP_INCLUDED
#define THX_UTILS_HPP_INCLUDED

#include "thx_traits.hpp"
#include "thx_types.hpp"
#include <limits>
#include <cassert>

//------------------------------------------------------------------------------

namespace thx
{

// clamp
// -----
//! Value clamped to range [low..high].

template<typename S>
S
clamp(const S x, const S low, const S high)
{
    assert(high >= low);
    return (x <= low) ? low : ((x >= high) ? high : x);
}

//------------------------------------------------------------------------------

// lerp
// ----
//! Linear interpolation. Use floating point types. [(1-t)*x0 + t*x1]

template<typename S>
S
lerp(const S x0, const S x1, const S t)
{
    return (1 - t)*x0 + t*x1;
}

//------------------------------------------------------------------------------

// smooth_step
// -----------
//! Smooth step function.

template<typename S> 
S
smooth_step(const S t)
{
    return (t < 0) ? 0 : ((t > 1) ? 1 : t*t*t*(10 + t*(-15 + t*6)));
}

//------------------------------------------------------------------------------

// smooth_step
// -----------
//! DOCS

template<typename S> 
S
smooth_step(const S x0, const S x1, const S t, const S t0, const S t1)
{ 
    return x0 + smooth_step((t - t0)/(t1 - t0))*(x1 - x0); 
}

//------------------------------------------------------------------------------

// ramp
// ----
//! DOCS

template<typename S>
S
ramp(const S t)
{ 
    return smooth_step(0.5*(t + 1))*2 - 1; 
}

//------------------------------------------------------------------------------

// smooth_heaviside
// ----------------
//! DOCS

template<typename S>
S
smooth_heaviside(const S t, const S w)
{ 
    return smooth_step(t, -w, w, 0, 1); 
}

//------------------------------------------------------------------------------

// frac
// ----
//! Return fractional part of x.

template<typename S>
S
frac(const S x)
{	
    if (traits<S>::is_floating) { 
        // Compile-time branching.

        return (x - floor_int32(x)); 
    }

    return 0; 
}

//------------------------------------------------------------------------------

// log2
// ----
//! Logarithm base 2.

template<typename S>
S
log2(const S x)
{
    assert(0 < x);
    static const S inv_log2(1/traits<S>::log(2));
    return traits<S>::log(x)*inv_log2;
}

//------------------------------------------------------------------------------

// is_zero
// -------
//! Return true if x is zero.

template<typename S>
bool 
is_zero(const S x) 
{
    if (traits<S>::is_floating) { 
        // Compile-time branching.

        return (traits<S>::abs(x) < traits<S>::epsilon());
    }
    else {
        // Integer.

        return (0 == x); 
    }	
}

//------------------------------------------------------------------------------

// is_nan
// ------
//! Return true if x is nan.

template<typename S> 
bool
is_nan(const S x)
{ 
    return (x != x); 
}

//------------------------------------------------------------------------------

// is_range_incl
// -------------
//! True if x is in the range [x0..x1]

template<typename S> 
bool   
is_range_incl(const S x, const S low, const S high)
{
    assert(low <= high);
    return (low <= x && x <= high);
}

//------------------------------------------------------------------------------

// is_range_excl
// -------------
//! True if x is in the range (x0..x1)

template<typename S> 
bool   
is_range_excl(const S x, const S low, const S high)
{
    assert(low < high);
    return (low < x && x < high);
}

//------------------------------------------------------------------------------

// equal
// -----
//! Return true if x0 is equal to x1.

template<typename S>
bool 
equal(const S x0, const S x1) 
{
    if (traits<S>::is_floating) {	
        // Compile-time branching.

        return (traits<S>::abs(x0 - x1) < traits<S>::epsilon());
    }
    else {
        // Integer.

        return (x0 == x1); 
    }	
}

//------------------------------------------------------------------------------

// equiv
// -----
//! Return true if x0 is equivalent to x1.

template<typename S> 
bool 
equiv(const S x0, const S x1)
{
    return (!(x0 < x1) && !(x0 > x1));
}

//------------------------------------------------------------------------------

// sgn
// ---
//! Sign function.

template<typename S>
int64 
sgn(const S x)
{
    return (is_zero(x) ? 0 : (x < 0 ? -1 : 1));
}

//------------------------------------------------------------------------------

// deg2rad
// -------
//! Convert degrees to radians. 

template<typename S>
S 
deg2rad(const S deg)
{
    return (traits<S>::pi()/180)*deg; 
}

//------------------------------------------------------------------------------

// rad2deg
// -------
//! Convert radians to degrees. 

template<typename S> 
S 
rad2deg(const S rad)
{
    return (180/traits<S>::pi())*rad;
}

//------------------------------------------------------------------------------

//// round_int32
//// -----------
////! Round x to nearest integer.
//
//template<typename S>
//int32
//round_int32(S x) 
//{
//    assert(x > (std::numeric_limits<int32>::min)()/2 - traits<S>::one());
//    assert(x < (std::numeric_limits<int32>::max)()/2 + traits<S>::one());
//
//    const S round_to_nearest(static_cast<S>(0.5));
//    int32 i;
//    __asm
//    {
//        fld x
//        fadd st, st (0)
//        fadd round_to_nearest
//        fistp i
//        sar i, 1
//    }
//    return (i);
//}

//template<typename S>
//int64
//round_int64(S x) 
//{
//	assert(x > (std::numeric_limits<int64>::min)()/2 - traits<S>::one());
//	assert(x < (std::numeric_limits<int64>::max)()/2 + traits<S>::one());
//
//	const int64 i(floor_int64(x));
//	return (x - i) >= static_cast<S>(0.5) ? i + 1 : i;
//}

//------------------------------------------------------------------------------

// round_int32
// -----------
// Round towards positive infinity. Returns value "ceiled".
//
// ceil_int64(43.5f) = 44
// ceil_int64(-43.5f) = -43

//template<typename S>
//int32
//ceil_int32(S x)
//{
//    assert(x > (std::numeric_limits<int32>::min)()/2 - traits<S>::one());
//    assert(x < (std::numeric_limits<int32>::max)()/2 + traits<S>::one());
//
//    const S round_to_pos_inf(static_cast<S>(-0.5));
//    int32 i;
//    __asm
//    {
//        fld x
//        fadd st, st (0)
//        fsubr round_to_pos_inf
//        fistp i
//        sar i, 1
//    }
//
//    return (-i);
//}

//template<typename S>
//int64
//ceil_int64(S x) 
//{
//	assert(x > (std::numeric_limits<int64>::min)()/2 - traits<S>::one());
//	assert(x < (std::numeric_limits<int64>::max)()/2 + traits<S>::one());
//
//	const int64 i(floor_int64(x));
//	return (x - i) >= static_cast<S>(0.5) ? i + 1 : i;
//}

//------------------------------------------------------------------------------

// floor_int32
// -----------
//! Round towards minus infinity. Returns value "floored".
//!	
//! floor_int64(43.5f) = 43
//! floor_int64(-43.5f) = -44

//template<typename S>
//int32
//floor_int32(S x)
//{
//    assert(x > (std::numeric_limits<int32>::min)()/2 - traits<S>::one());
//    assert(x < (std::numeric_limits<int32>::max)()/2 + traits<S>::one());
//
//    const S round_to_neg_inf(static_cast<S>(-0.5));
//    int32 i;
//    __asm
//    {
//        fld x
//        fadd st, st (0)
//        fadd round_to_neg_inf
//        fistp i
//        sar i, 1
//    }
//    return (i);
//}

//template<typename S>
//int64
//floor_int64(S x) 
//{
//	//assert(x > (std::numeric_limits<int64>::min)()/2 - traits<S>::one());
//	//assert(x < (std::numeric_limits<int64>::max)()/2 + traits<S>::one());
//
//	//const int64 i(floor_int64(x));
//	//return (x - i) >= static_cast<S>(0.5) ? i + 1 : i;
//	return 0;
//}

//------------------------------------------------------------------------------

// trunc_int32
// -----------
//! Acts as floor for positive values, ceil for negative values,
//! i.e. rounds to integer closest to zero.

//template<typename S>
//int32
//trunc_int32(S x)
//{
//    assert(x > (std::numeric_limits<int32>::min)()/2 - traits<S>::one());
//    assert(x < (std::numeric_limits<int32>::max)()/2 + traits<S>::one());
//
//    const S round_towards_neg_inf(static_cast<S>(-0.5));
//    int32 i;
//    __asm
//    {
//        fld x
//        fadd st, st (0)
//        fabs
//        fadd round_towards_neg_inf
//        fistp i
//        sar i, 1
//    }
//
//    if( x < 0 ) { 
//        i = -i; 
//    }
//
//    return (i);
//}

//template<typename S>
//int64
//trunc_int64(S x) 
//{
//	assert(x > (std::numeric_limits<int64>::min)()/2 - traits<S>::one());
//	assert(x < (std::numeric_limits<int64>::max)()/2 + traits<S>::one());
//
//	const int64 i(floor_int64(x));
//	return (x - i) >= static_cast<S>(0.5) ? i + 1 : i;
//}

//------------------------------------------------------------------------------

// sqr
// ---
//! Return x squared.

template<typename S> 
S 
sqr(const S x) 
{ 
    return x*x; 
}

//------------------------------------------------------------------------------

// cube
// ----
//! Return x cubed.

template<typename S> 
S 
cube(const S x) 
{ 
    return x*x*x; 
}

//------------------------------------------------------------------------------

// min
// ---
//! Returns smallest value.

template<typename S>
S
min(const S x0, const S x1, const S x2)
{ 
    return std::min<S>(x0, std::min<S>(x1, x2)); 
}

//------------------------------------------------------------------------------

// min
// ---
//! Returns smallest value.

template<typename S>
S
min(const S x0, const S x1, const S x2, const S x3)
{ 
    return std::min<S>(std::min<S>(x0, x1), std::min<S>(x2, x3)); 
}

//------------------------------------------------------------------------------

// min
// ---
//! Returns smallest value.

template<typename S>
S
min(const S x0, const S x1, const S x2, const S x3, const S x4)
{ 
    return min(std::min<S>(x0, x1), std::min<S>(x2, x3), x4); 
}

//------------------------------------------------------------------------------

// min
// ---
//! Returns smallest value.

template<typename S>
S
min(const S x0, const S x1, const S x2, const S x3, const S x4, const S x5)
{ 
    return min(std::min<S>(x0, x1), std::min<S>(x2, x3), std::min<S>(x4, x5)); 
}

//------------------------------------------------------------------------------

// max
// ---
//! Returns largest value.

template<typename S>
S
max(const S x0, const S x1, const S x2)
{ 
    return std::max<S>(x0, std::max<S>(x1, x2)); 
}

//------------------------------------------------------------------------------

// max
// ---
//! Returns largest value.

template<typename S>
S
max(const S x0, const S x1, const S x2, const S x3)
{ 
    return std::max<S>(std::max<S>(x0, x1), std::max<S>(x2, x3)); 
}

//------------------------------------------------------------------------------

// max
// ---
//! Returns largest value.

template<typename S>
S
max(const S x0, const S x1, const S x2, const S x3, const S x4)
{ 
    return max(std::max<S>(x0, x1), std::max<S>(x2, x3), x4); 
}

//------------------------------------------------------------------------------

// max
// ---
//! Returns largest value.

template<typename S>
S
max(const S x0, const S x1, const S x2, const S x3, const S x4, const S x5)
{ 
    return max(std::max<S>(x0, x1), std::max<S>(x2, x3), std::max<S>(x4, x5)); 
}

//------------------------------------------------------------------------------

// sort
// ----
//! Simple sort.

template<typename S> 
void
sort(S* x0, S* x1, S* x2)
{
    assert(0 != x0 && 0 != x1 && 0 != x2);

    S tmp;
    if (*x0 < *x1) {
        if (*x0 < *x2) {
            if( *x2 < *x1 ) {	
                // x0 < x2 < x1

                tmp = *x2;
                *x2 = *x1;
                *x1 = tmp;
            } 
            // else: x0 < x1 < x2
        }
        else {	
            // x2 < x0 < x1

            tmp = *x2;
            *x2 = *x1;
            *x1 = *x0;
            *x0 = tmp;
        }
    }
    else {
        if( *x1 < *x2) {
            if( *x0 < *x2) {	
                // x1 < x0 < x2

                tmp = *x1;
                *x1 = *x0;
                *x0 = tmp;
            }
            else {	
                // x1 < x2 < x0

                tmp = *x1;
                *x1 = *x2;
                *x2 = *x0;
                *x0 = tmp;
            }
        }
        else {	
            // x2 < x1 < x0
            
            tmp = *x2;
            *x2 = *x0;
            *x0 = tmp;
        }
    }
}

//------------------------------------------------------------------------------

// sort
// ----
//! Simple sort.

template<typename S> 
void
sort(S* x0, S* x1, S* x2, S* x3)
{
    assert(0 != x0 && 0 != x1 && 0 != x2 && 0 != x3);

    sort(x0, x1, x2);

    S tmp;
    if( *x3 < *x1 ) {
        if( *x3 < *x0 ) {
            tmp = *x3; 
            *x3 = *x2; 
            *x2 = *x1; 
            *x1 = *x0; 
            *x0 = tmp;
        }
        else {
            tmp = *x3; 
            *x3 = *x2; 
            *x2 = *x1; 
            *x1 = tmp;
        }
    }
    else if( *x3 < *x2) {
        tmp = *x3; 
        *x3 = *x2; 
        *x2 = tmp;
    }
}

//------------------------------------------------------------------------------

// compact_gaussian
// ----------------
// Decent and cheap approximation to a Gaussian: exp(-(x/sigma)^2/2),
// which smoothly drops to zero at x = 2.5*sigma

template<typename S>
S
compact_gaussian(const S x, const S sigma)
{
    const S y(traits<S>::abs(x/sigma));
    if (y < 2.5) { 
        return 1 + y*y*(-0.5 + y*(0.144 - y*0.0032)); 
    }
    else { 
        return 0; 
    }
}

//------------------------------------------------------------------------------

// quadratic
// ---------
//! Solve quadratic equation. Use floating point types. True if 
//! quadratic has real (non-imaginary) roots.
//!
//! ax^2 + bx + c = 0

template<typename S>
bool 
quadratic(const S a, const S b, const S c, S* t0, S* t1)
{	
    // Find quadratic discriminant.
    
    const S discrim(b*b - 4*a*c);

    if (discrim < 0) { 
        return false; 
    }

    const S root_discrim(traits<S>::sqrt(discrim));

    // Compute quadratic t values.
    
    S q;
    if( b < 0 )	{ 
        q = -0.5*(b - root_discrim); 
    }
    else { 
        q = -0.5*(b + root_discrim);	
    }

    if (is_zero(a) || is_zero(q)) { 
        return false; 
    }

    if (0 != t0 && 0 != t1) {
        *t0 = q/a;
        *t1 = c/q;

        if (*t0 > *t1) {	
            // Swap.
            
            const S tmp0(*t0);
            *t0 = *t1;
            *t1 = tmp0;
        }
    }

    return true;	// Real roots.
}

}	// Namespace: thx.

#endif	// THX_UTILS_HPP_INCLUDED
