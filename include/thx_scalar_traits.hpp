//------------------------------------------------------------------------------
//
// Contributors: 
//             1) Tommy Hinks
//
//------------------------------------------------------------------------------

#ifndef THX_TRAITS_HPP_INCLUDED
#define THX_TRAITS_HPP_INCLUDED

#include "thx_namespace.hpp"
#include "thx_types.hpp"
#include <limits>
#include <cmath>
#include <cstdlib>
#include <cassert>

//------------------------------------------------------------------------------

BEGIN_THX_NAMESPACE

namespace detail {

class nonconstructible
{
private:
  nonconstructible();
  nonconstructible(const nonconstructible&);
  ~nonconstructible();
  nonconstructible& operator=(const nonconstructible&);
};

} // Namespace: detail.

struct real_scalar_tag {};
struct signed_integer_scalar_tag {};
struct unsigned_integer_scalar_tag {};

// !Generic, not implemented.
template <typename S>
class scalar_traits;

//------------------------------------------------------------------------------

//! Traits for float32 scalar type.
template <>
class scalar_traits<float32> : private detail::nonconstructible
{
public:

  typedef real_scalar_tag scalar_category;

  static /*constexpr*/ float32 
  pi()		
  { return 3.1415926535897f; }

  static float32
  big_value()	
  { 
    return scalar_traits<float32>::sqrt((std::numeric_limits<float32>::max)())/8;
  }

  static float32 
  abs(const float32 x)  
  { 
    return ::fabsf(x); 
  }

  static float32 
  exp(const float32 x)  
  { 
    return ::expf(x); 
  }

  static float32 
  log(const float32 x)  
  { 
    return ::logf(x); 
  }	

  static float32 
  sin(const float32 x)  
  { 
    return ::sinf(x); 
  }

  static float32 
  cos(const float32 x)  
  { 
    return ::cosf(x); 
  }

  static float32 
  tan(const float32 x)  
  { 
    return ::tanf(x); 
  }

  static float32 
  asin(const float32 x) 
  { 
    return ::asinf(x); 
  }

  static float32 
  acos(const float32 x) 
  { 
    return ::acosf(x); 
  }

  static float32 
  atan(const float32 x) 
  { 
    return ::atanf(x); 
  }

  static float32 
  atan2(const float32 y, const float32 x) 
  { 
    return ::atan2f(y, x); 
  }

  static float32 
  sqrt(const float32 x) 
  {
    return ::sqrtf(x); 
  }

  //static
  //int
  //log2int(float32 x)
  //{	// Logarithm base 2.
  //	//	
  //	assert(traits<float32>::zero < x);
  //	return ((*(reinterpret_cast<int*>(&x))) >> 23) - 127;
  //}
};

//------------------------------------------------------------------------------

//! Traits for float64 scalar type.
template <>
class scalar_traits<float64> : private detail::nonconstructible
{
public:

  static /*constexpr*/ float64 
  pi()		
  { return 3.1415926535897; }

  static float64 
  big_value()	
  { 
    return (scalar_traits<float64>::sqrt((std::numeric_limits<float64>::max)())/8);
  }

  static float64 
  abs(const float64 x)  
  { 
    return std::fabs(x); 
  }

  static float64 
  exp(const float64 x)  
  { 
    return std::exp(x); 
  }

  static float64 
  log(const float64 x)  
  {
    return std::log(x); 
  }

  static float64 
  sin(const float64 x)  
  { return std::sin(x); }

  static float64 
  cos(const float64 x)  
  { return ::cos(x); }

  static float64 
  tan(const float64 x)  
  { return ::tan(x); }

  static float64 
  asin(const float64 x) 
  { return ::asin(x); }

  static float64 
  acos(const float64 x) 
  { return ::acos(x); }

  static float64 
  atan(const float64 x) 
  { return ::atan(x); }

  static float64 
  atan2(const float64 y, const float64 x) 
  { return ::atan2(y, x); }

  static float64 
  sqrt(const float64 x) 
  { return ::sqrt(x); }
};

//------------------------------------------------------------------------------

//! Traits for int8 scalar type.
template <>
class scalar_traits<int8> : private detail::nonconstructible
{
public:

  static int8 
  abs(const int8 x)	
  { return static_cast<int8>(::abs(x)); }
};

//------------------------------------------------------------------------------

//! Traits for int16 scalar type.
template <>
class scalar_traits<int16> : private detail::nonconstructible
{
public:

  static int16 
  abs(const int16 x)  
  { 
    return static_cast<int16>(::abs(x)); 
  }
};

//------------------------------------------------------------------------------

//! Traits for int32 scalar type.
template <>
class scalar_traits<int32> : private detail::nonconstructible
{
public:

  static int32 
  abs(const int32 x)  
  { return ::abs(x); }

  //static bool is_pow2(const int val) { return ((val & (val - 1)) == 0); }

  //static
  //int
  //mod(int a, const int b)
  //{	// Modulus operator, leftover after integer division. 
  //	//
  //	assert(0 != b);
  //	const int n(static_cast<int>(a/b));
  //	a -= n*b;
  //	if( a < 0 ) { a += b; }
  //	return a;
  //}
};

//------------------------------------------------------------------------------

//! Traits for int64 scalar type.
template <>
class scalar_traits<int64> : private detail::nonconstructible
{
public:

  static int64 
  abs(const int64 x)  
  { return _abs64(x); }
};

//------------------------------------------------------------------------------

//! Traits for uint8 scalar type.
template <>
class scalar_traits<uint8> : private detail::nonconstructible
{};

//------------------------------------------------------------------------------

//! Traits for uint16 scalar type.
template <>
class scalar_traits<uint16> : private detail::nonconstructible
{};

//------------------------------------------------------------------------------

//! Traits for uint32 scalar type.
template <>
class scalar_traits<uint32>: private detail::nonconstructible 
{
public:

  // Round integer up to nearest power of 2.
  //	
  //static
  //unsigned int
  //round_up_pow2(unsigned int val)
  //{	// NB: Assumes 32-bit (sizeof(unsigned int) == 4)
  //	//
  //	assert(0 < val);
  //	val--;
  //	val |= val >> 1;
  //	val |= val >> 2;
  //	val |= val >> 4;
  //	val |= val >> 8;
  //	val |= val >> 16;
  //	return val+1;
  //}
};

//------------------------------------------------------------------------------

//! Traits for uint64 scalar type.
template <>
class scalar_traits<uint64> : private detail::nonconstructible
{};

END_THX_NAMESPACE

#endif	// THX_TRAITS_HPP_INCLUDED
