//------------------------------------------------------------------------------
//
// Contributors: 
//             1) Tommy Hinks
//
//------------------------------------------------------------------------------

#ifndef THX_SCALAR_ALGO_HPP_INCLUDED
#define THX_SCALAR_ALGO_HPP_INCLUDED

#include "thx_namespace.hpp"
#include "thx_scalar_traits.hpp"
#include <type_traits>

BEGIN_THX_NAMESPACE

//------------------------------------------------------------------------------

namespace detail {

//! Floating point negate.
template<typename S> inline THX_CONST_EXPR
S
negate_dispatch(S const x, real_scalar_tag) {
  return -x;
}

//! Signed integer negate. NB: Not implemented for unsigned integer types.
template<typename S> inline THX_CONST_EXPR
S
negate_dispatch(const S x, signed_integer_scalar_tag) {
  return -x;
}

} // Namespace: detail.

//! Return negated value, if supported for the provided type.
template<typename S> inline THX_CONST_EXPR
S
negate(const S x) 
{
  typedef typename scalar_traits<S>::scalar_category category;
  return detail::scalar_negate_dispatch(x, category());
}

//------------------------------------------------------------------------------

namespace detail {

template<typename S> inline THX_CONST_EXPR
bool
equal_dispatch(const S x, const S y)
{
  return x == y;
}

} // Namespace: detail.

//! Returns true if arguments are equal.
template<typename S> inline THX_CONST_EXPR
bool
equal(const S x, const S y)
{
  return detail::equal_dispatch(x, y);
}

//------------------------------------------------------------------------------

namespace detail {

template<typename S> inline THX_CONST_EXPR
bool
not_equal_dispatch(const S x, const S y)
{
  return x != y;
}

} // Namespace: detail.

//! Returns true if arguments are not equal.
template<typename S> inline THX_CONST_EXPR
bool
not_equal(const S x, const S y)
{
  return detail::not_equal_dispatch(x, y);
}

//------------------------------------------------------------------------------

//! Value clamped to range [low..high]. Assumes low <= high.
template<typename S> inline THX_CONST_EXPR
S const&
clamp(S const& x, S const& low, S const& high)
{
    return (x <= low) ? low : ((x >= high) ? high : x);
}

//------------------------------------------------------------------------------

namespace detail {

//! Floating point lerp.
template<typename S> inline THX_CONST_EXPR
S
lerp_dispatch(const S x0, const S x1, const S t, real_scalar_tag)
{
  return (1 - t)*x0 + t*x1;
}

} // Namespace: detail.

//! Linear interpolation. [(1-t)*x0 + t*x1]
template<typename S> inline THX_CONST_EXPR
S
lerp(const S x0, const S x1, const S t)
{
  typedef typename scalar_traits<S>::scalar_category category;
  return detail::lerp_dispatch(x0, x1, t, category());
}

//------------------------------------------------------------------------------

namespace detail {

//! Floating point smooth step function.
template<typename S> inline THX_CONST_EXPR
S
smooth_step_dispatch(const S t, real_scalar_tag)
{
  return (t < 0) ? 0 : ((t > 1) ? 1 : t*t*t*(10 + t*(-15 + t*6)));
}

//! DOCS
template<typename S> inline THX_CONST_EXPR
S
smooth_step_dispatch(const S x0, 
                     const S x1, 
                     const S t, 
                     const S t0, 
                     const S t1,
                     real_scalar_tag)
{
  return 
    x0 + smooth_step_dispatch((t - t0)/(t1 - t0), real_scalar_tag())*(x1 - x0); 
}

} // Namespace: detail.

//! Floating point smooth step function.
template<typename S> inline THX_CONST_EXPR
S
smooth_step(const S t)
{
  typedef typename scalar_traits<S>::scalar_category category;
  return detail::smooth_step_dispatch(t, category());
}

//! DOCS
template<typename S> inline THX_CONST_EXPR
S
smooth_step(const S x0, const S x1, const S t, const S t0, const S t1)
{
  typedef typename scalar_traits<S>::scalar_category category;
  return detail::smooth_step_dispatch(x0, x1, t, t0, t1, category());
}

//! DOCS
template<typename S> inline THX_CONST_EXPR
S
ramp(const S t)
{
  typedef typename scalar_traits<S>::scalar_category category;
  return 
    detail::smooth_step_dispatch(S(0.5)*(t + S(1)), category())*S(2) - S(1); 
}

//! DOCS
template<typename S> inline THX_CONST_EXPR
S
smooth_heaviside(const S t, const S w)
{
  typedef typename scalar_traits<S>::scalar_category category;
  return detail::smooth_step_dispatch(t, -w, w, S(0), S(1), category()); 
}

//------------------------------------------------------------------------------

namespace detail {

//! Return fractional part of x.
template<typename S> inline THX_CONST_EXPR
 S
frac_dispatch(const S x, real_scalar_tag)
{
  return x - scalar_traits<S>::floor(x);
}

} // Namespace: detail.

//! DOCS
template<typename S> inline THX_CONST_EXPR
S
frac(const S x)
{
  typedef typename scalar_traits<S>::scalar_category category;
  return detail::frac_dispatch(x, category()); 
}

//------------------------------------------------------------------------------

//! Return true if x is nan.
template<typename S> inline THX_CONST_EXPR
bool
is_nan(const S x)
{ 
  return (x != x); 
}

//------------------------------------------------------------------------------

//! True if x is in the range [x0..x1]. Assumes low <= high.
template<typename S> inline THX_CONST_EXPR
bool   
is_range_incl(const S x, const S low, const S high)
{
  return (low <= x && x <= high);
}

//------------------------------------------------------------------------------

//! True if x is in the range (x0..x1). Assumes low < high.
template<typename S> inline THX_CONST_EXPR
bool   
is_range_excl(const S x, const S low, const S high)
{
  return (low < x && x < high);
}

//------------------------------------------------------------------------------

//! Return true if x0 is equivalent to x1.
template<typename S> inline THX_CONST_EXPR
bool 
equiv(const S x0, const S x1)
{
  return !(x0 < x1) && !(x0 > x1);
}

//------------------------------------------------------------------------------

namespace detail {

//! Convert degrees to radians. Floating point.
template<typename S> inline THX_CONST_EXPR
S 
deg_to_rad_dispatch(const S deg, real_scalar_tag)
{
  return (scalar_traits<S>::pi()/180)*deg; 
}

//! Convert radians to degrees. 
template<typename S> inline THX_CONST_EXPR
S 
rad_to_deg_dispatch(const S rad, real_scalar_tag)
{
  return (180/traits<S>::pi())*rad;
}

} // Namespace: detail.

//! Convert degrees to radians. 
template<typename S> inline THX_CONST_EXPR
S 
deg_to_rad(const S deg)
{
  typedef typename scalar_traits<S>::scalar_category category;
  return detail::deg_to_rad_dispatch(x, category()); 
}

//! Convert radians to degrees. 
template<typename S> inline THX_CONST_EXPR
S 
rad_to_deg(const S rad)
{
  typedef typename scalar_traits<S>::scalar_category category;
  return detail::rad_to_deg_dispatch(x, category()); 
}

//------------------------------------------------------------------------------

namespace detail {

//! DOCS
template<typename S>
S
compact_gaussian_dispatch(const S x, const S sigma, real_scalar_tag)
{
  const S y = scalar_traits<S>::abs(x/sigma);
  return y < S(2.5) ? S(1) + y*y*(S(-0.5) + y*(S(0.144) - y*S(0.0032))) : S(0);
}

} // Namespace: detail.

//! Decent and cheap approximation to a Gaussian: exp(-(x/sigma)^2/2),
//! which smoothly drops to zero at x = 2.5*sigma
template<typename S>
S
compact_gaussian(const S x, const S sigma)
{
  typedef typename scalar_traits<S>::scalar_category category;
  return detail::compact_gaussian_dispatch(x, sigma, category()); 
}

//------------------------------------------------------------------------------

namespace detail {

//! Unsigned types.
template <typename S> inline THX_CONST_EXPR
int 
signum_dispatch(const S x, std::false_type /*is_signed*/) {
  return S(0) < x;
}

//! Signed types.
template <typename S> inline THX_CONST_EXPR
int 
signum_dispatch(const S x, std::true_type /*is_signed*/) {
  return (S(0) < x) - (x < S(0));
}

} // Namespace: detail.

//! Returns -1 of x < 0, 0 if x == 0, 1 if x > 0.
template <typename S> inline THX_CONST_EXPR
int 
signum(const S x) {
  return detail::signum_dispatch(x, std::is_signed<S>());
}

//------------------------------------------------------------------------------

//! Return x squared.
template<typename S> inline THX_CONST_EXPR
S 
sqr(const S x) { 
  return x*x; 
}

//------------------------------------------------------------------------------

//! Return x cubed.
template<typename S> inline THX_CONST_EXPR
S 
cube(const S x) { 
  return x*x*x; 
}

//------------------------------------------------------------------------------


//! Returns smallest value.
template <typename S> inline THX_CONST_EXPR
S const&
min(S const& a, S const& b) { 
  return (a < b) ? a : b; 
}

#if 0 // C++11
//! Returns smallest value using variadic templates.
template <typename S, typename ...P> inline THX_CONST_EXPR
S const&
min(const S &a, P const &... b) { 
  return min(a, min(b...)); 
}
#else
//! Returns smallest value.
template<typename S> inline THX_CONST_EXPR
S const&
min(S const& x0, S const& x1, S const& x2) { 
  return min<S>(x0, min<S>(x1, x2)); 
}

//! Returns smallest value.
template<typename S> inline THX_CONST_EXPR
S
min(S const& x0, S const& x1, S const& x2, S const& x3) { 
  return min<S>(min<S>(x0, x1), min<S>(x2, x3)); 
}

//! Returns smallest value.
template<typename S> inline THX_CONST_EXPR
S const&
min(S const& x0, S const& x1, S const& x2, S const& x3, S const& x4) { 
  return min<S>(min<S>(x0, x1), min<S>(x2, x3), x4); 
}

//! Returns smallest value.
template<typename S> inline THX_CONST_EXPR
S const&
min(S const& x0, 
    S const& x1, 
    S const& x2, 
    S const& x3, 
    S const& x4, 
    S const& x5) { 
  return min<S>(min<S>(x0, x1), min<S>(x2, x3), min<S>(x4, x5)); 
}
#endif

//------------------------------------------------------------------------------

//! Returns largest value.
template<typename S> inline THX_CONST_EXPR 
S const& 
max(S const& a, S const& b) {
	return (a > b) ? a : b;
}


#if 0 // C++11
//! Returns largest value using variadic templates.
template <typename S, typename ...P> inline THX_CONST_EXPR
S const&
max(const S &a, P const &... b) { 
	return max(a, max(b...)); 
}
#else
//! Returns largest value.
template<typename S> inline THX_CONST_EXPR
S const&
max(S const& x0, S const& x1, S const& x2) { 
  return max<S>(x0, max<S>(x1, x2)); 
}

//! Returns largest value.
template<typename S> inline THX_CONST_EXPR
S const&
max(S const& x0, S const& x1, S const& x2, S const& x3) { 
  return max<S>(max<S>(x0, x1), max<S>(x2, x3)); 
}

//! Returns largest value.
template<typename S> inline THX_CONST_EXPR
S const&
max(S const& x0, S const& x1, S const& x2, S const& x3, S const& x4) { 
  return max(max<S>(x0, x1), max<S>(x2, x3), x4); 
}

//! Returns largest value.
template<typename S> inline THX_CONST_EXPR
S const&
max(S const& x0, 
	  S const& x1, 
	  S const& x2, 
	  S const& x3, 
	  S const& x4, 
	  S const& x5) { 
  return max(max<S>(x0, x1), max<S>(x2, x3), max<S>(x4, x5)); 
}
#endif

//------------------------------------------------------------------------------

//! Simple sort. 
//! Post-condition: x0 < x1 < x2.
template<typename S> inline /* TODO: THX_CONST_EXPR ?? */
void
simple_sort(S& x0, S& x1, S& x2) {
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
}

END_THX_NAMESPACE

#endif // THX_SCALAR_ALGO_HPP_INCLUDED
