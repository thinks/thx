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

//! Value clamped to range [low..high].
template<typename S>
constexpr S const&
clamp(S const& x, S const& low, S const& high)
{
    assert(high >= low);
    return (x <= low) ? low : ((x >= high) ? high : x);
}

//------------------------------------------------------------------------------

//! Linear interpolation. Use floating point types. [(1-t)*x0 + t*x1]
template<typename S>
constexpr S
lerp(const S x0, const S x1, const S t)
{
    static_assert(std::is_floating_point<S>::value, 
                 "Scalar type must be floating point" );
    return (1 - t)*x0 + t*x1;
}

//------------------------------------------------------------------------------

//! Smooth step function.
template<typename S> 
constexpr S
smooth_step(const S t)
{
    static_assert(std::is_floating_point<S>::value, 
                 "Scalar type must be floating point" );
    return (t < 0) ? 0 : ((t > 1) ? 1 : t*t*t*(10 + t*(-15 + t*6)));
}

//------------------------------------------------------------------------------

//! DOCS
template<typename S> 
constexpr S
smooth_step(const S x0, const S x1, const S t, const S t0, const S t1)
{
    static_assert(std::is_floating_point<S>::value, 
                 "Scalar type must be floating point" );
    return x0 + smooth_step((t - t0)/(t1 - t0))*(x1 - x0); 
}

//------------------------------------------------------------------------------

//! DOCS
template<typename S>
constexpr S
ramp(const S t)
{
    static_assert(std::is_floating_point<S>::value, 
                 "Scalar type must be floating point" );
    return smooth_step(0.5*(t + 1))*2 - 1; 
}

//------------------------------------------------------------------------------

//! DOCS
template<typename S>
constexpr S
smooth_heaviside(const S t, const S w)
{ 
    return smooth_step(t, -w, w, 0, 1); 
}

//------------------------------------------------------------------------------

//! Return fractional part of x.
template<typename S>
constexpr S
frac(const S x)
{
    return x - traits<S>::floor(x);
}

//------------------------------------------------------------------------------

////! Logarithm base 2.
//template<typename S>
//S
//log2(const S x)
//{
//    assert(0 < x);
//    static const S inv_log2 = 1/traits<S>::log(2);
//    return traits<S>::log(x)*inv_log2;
//}

//------------------------------------------------------------------------------

//! Return true if x is zero.
template<typename S>
constexpr bool 
is_zero(const S x, const S tolerance = 0) 
{
	return std::is_floating_point<S>::value ? 
		traits<S>::abs(x) < tolerance : 
		x == 0;
}

//------------------------------------------------------------------------------

//! Return true if x is nan.
template<typename S> 
constexpr bool
is_nan(const S x)
{ 
    return (x != x); 
}

//------------------------------------------------------------------------------

//! True if x is in the range [x0..x1]
template<typename S> 
constexpr bool   
is_range_incl(const S x, const S low, const S high)
{
    assert(low <= high);
    return (low <= x && x <= high);
}

//------------------------------------------------------------------------------

//! True if x is in the range (x0..x1)
template<typename S> 
constexpr bool   
is_range_excl(const S x, const S low, const S high)
{
    assert(low < high);
    return (low < x && x < high);
}

//------------------------------------------------------------------------------

//! Return true if x0 is equal to x1.
template<typename S>
constexpr bool 
equal(const S x0, const S x1, const S tolerance = 0) 
{
	return std::is_floating_point<S>::value ? 
		traits<S>::abs(x0 - x1) < tolerance :
		x0 == x1; // Integer.
}

//------------------------------------------------------------------------------

//! Return true if x0 is equivalent to x1.
template<typename S> 
constexpr bool 
equiv(const S x0, const S x1)
{
    return (!(x0 < x1) && !(x0 > x1));
}

//------------------------------------------------------------------------------

//! Sign function.
template<typename S>
int64 
sgn(const S x, const S tolerance = 0)
{
    return (is_zero(x, tolerance) ? 0 : (x < 0 ? -1 : 1));
}

//------------------------------------------------------------------------------

//! Convert degrees to radians. 
template<typename S>
constexpr S 
deg_to_rad(const S deg)
{
    static_assert(std::is_floating_point<S>::value, 
                 "Scalar type must be floating point" );
    return (traits<S>::pi()/180)*deg; 
}

//------------------------------------------------------------------------------

//! Convert radians to degrees. 
template<typename S> 
constexpr S 
rad_to_deg(const S rad)
{
    static_assert(std::is_floating_point<S>::value, 
                 "Scalar type must be floating point" );
    return (180/traits<S>::pi())*rad;
}

//------------------------------------------------------------------------------

//! Return x squared.
template<typename S> 
constexpr S 
sqr(const S x) 
{ 
    return x*x; 
}

//------------------------------------------------------------------------------

//! Return x cubed.
template<typename S> 
constexpr S 
cube(const S x) 
{ 
    return x*x*x; 
}

//------------------------------------------------------------------------------

//! Returns smallest value.
template<typename S> 
constexpr S const& 
min(S const& a, S const& b) 
{
	return (a < b) ? a : b;
}


//! Returns smallest value.
template<typename S>
constexpr S const&
min(S const& x0, S const& x1, S const& x2)
{ 
    return min<S>(x0, min<S>(x1, x2)); 
}


//! Returns smallest value.
template<typename S>
constexpr S
min(S const& x0, S const& x1, S const& x2, S const& x3)
{ 
    return min<S>(min<S>(x0, x1), min<S>(x2, x3)); 
}


//! Returns smallest value.
template<typename S>
constexpr S const&
min(S const& x0, S const& x1, S const& x2, S const& x3, S const& x4)
{ 
    return min<S>(min<S>(x0, x1), min<S>(x2, x3), x4); 
}


//! Returns smallest value.
template<typename S>
constexpr S const&
min(S const& x0, 
	S const& x1, 
	S const& x2, 
	S const& x3, 
	S const& x4, 
	S const& x5)
{ 
    return min<S>(min<S>(x0, x1), min<S>(x2, x3), min<S>(x4, x5)); 
}

//------------------------------------------------------------------------------

//! Returns largest value.
template<typename S> 
constexpr S const& 
max(S const& a, S const& b) 
{
	return (a > b) ? a : b;
}


//! Returns largest value.
template<typename S>
constexpr S const&
max(S const& x0, S const& x1, S const& x2)
{ 
    return max<S>(x0, max<S>(x1, x2)); 
}


//! Returns largest value.
template<typename S>
constexpr S const&
max(S const& x0, S const& x1, S const& x2, S const& x3)
{ 
    return max<S>(max<S>(x0, x1), max<S>(x2, x3)); 
}


//! Returns largest value.
template<typename S>
constexpr S const&
max(S const& x0, S const& x1, S const& x2, S const& x3, S const& x4)
{ 
    return max(max<S>(x0, x1), max<S>(x2, x3), x4); 
}


//! Returns largest value.
template<typename S>
constexpr S const&
max(S const& x0, 
	S const& x1, 
	S const& x2, 
	S const& x3, 
	S const& x4, 
	S const& x5)
{ 
    return max(max<S>(x0, x1), max<S>(x2, x3), max<S>(x4, x5)); 
}

//------------------------------------------------------------------------------

//! Simple sort. 
//! Post-condition: x0 < x1 < x2.
template<typename S> 
void
simple_sort(S &x0, S &x1, S &x2)
{
    S tmp;
    if (x0 < x1) {
        if (x0 < x2) {
            if (x2 < x1 ) {	// x0 < x2 < x1, swap x1 and x2.
                tmp = x2;
                x2 = x1;
                x1 = tmp;
            } 
            // else: x0 < x1 < x2
        }
        else { // x2 < x0 < x1
            tmp = x2;
            x2 = x1;
            x1 = x0;
            x0 = tmp;
        }
    }
    else {
        if (x1 < x2) {
            if (x0 < x2) { // x1 < x0 < x2, swap x1 and x0	
                tmp = x1;
                x1 = x0;
                x0 = tmp;
            }
            else { // x1 < x2 < x0
                tmp = x1;
                x1 = x2;
                x2 = x0;
                x0 = tmp;
            }
        }
        else { // x2 < x1 < x0, swap x2 and x0.
            tmp = x2;
            x2 = x0;
            x0 = tmp;
        }
    }
	assert(x0 < x1 && x1 < x2); // Post-condition.
}


//! Simple sort.
//! Post-condition: x0 < x1 < x2 < x3.
//! TODO: Could be optimized!
template<typename S> 
void
simple_sort(S &x0, S &x1, S &x2, S &x3)
{
    simple_sort(x0, x1, x2);
    S tmp;
    if (x3 < x1 ) {
        if (x3 < x0) {
            tmp = x3; 
            x3 = x2; 
            x2 = x1; 
            x1 = x0; 
            x0 = tmp;
        }
        else {
            tmp = x3; 
            x3 = x2; 
            x2 = x1; 
            x1 = tmp;
        }
    }
    else if (x3 < x2) {
        tmp = x3; 
        x3 = x2; 
        x2 = tmp;
    }
	assert(x0 < x1 && x1 < x2 && x2 < x3); // Post-condition.
}

//------------------------------------------------------------------------------

//! Decent and cheap approximation to a Gaussian: exp(-(x/sigma)^2/2),
//! which smoothly drops to zero at x = 2.5*sigma
template<typename S>
S
compact_gaussian(const S x, const S sigma)
{
    static_assert(std::is_floating_point<S>::value, 
                 "Scalar type must be floating point" );
    const S y = traits<S>::abs(x/sigma);
    return (y < 2.5) ? (1 + y*y*(-0.5 + y*(0.144 - y*0.0032))) : 0;
}

//------------------------------------------------------------------------------

//! Solve quadratic equation. Use floating point types. True if 
//! quadratic has real (non-imaginary) roots.
//!
//! ax^2 + bx + c = 0
//template<typename S>
//bool 
//quadratic(const S a, const S b, const S c, S *t0, S *t1)
//{	
//    // Find quadratic discriminant.
//    
//    const S discrim = b*b - 4*a*c;
//
//    if (discrim < 0) { 
//        return false; 
//    }
//
//    const S root_discrim = traits<S>::sqrt(discrim);
//
//    // Compute quadratic t-values.
//    
//    S q = (b < 0) ? -0.5*(b - root_discrim) : -0.5*(b + root_discrim);
//
//    if (is_zero(a) || is_zero(q)) { 
//        return false; 
//    }
//
//    if (0 != t0 && 0 != t1) {
//        *t0 = q/a;
//        *t1 = c/q;
//
//        if (*t0 > *t1) {	
//            // Swap.
//            
//            const S tmp0(*t0);
//            *t0 = *t1;
//            *t1 = tmp0;
//        }
//    }
//
//    return true;	// Real roots.
//}

}	// Namespace: thx.

#endif	// THX_UTILS_HPP_INCLUDED
