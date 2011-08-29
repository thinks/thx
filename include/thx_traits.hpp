//------------------------------------------------------------------------------
//
// Contributors: 
//             1) Tommy Hinks
//
//------------------------------------------------------------------------------

#ifndef THX_TRAITS_HPP_INCLUDED
#define THX_TRAITS_HPP_INCLUDED

#include "thx_types.hpp"
#include <limits>
#include <cmath>
#include <cstdlib>
#include <cassert>

//------------------------------------------------------------------------------

namespace thx
{

// Generic, not implemented.
// Specializations below.

template <typename S>
class traits;

//------------------------------------------------------------------------------

// traits<float32>
//----------------
//! Traits for float32 scalar type.

template <>
class traits<float32> 
{
public:

	enum { is_floating = 1 };
	enum { is_integer  = 0 };
	enum { is_signed   = 1 };

	static float32 
	zero()		
	{ return  0.f; }

	static float32 
	one()		
	{ return  1.f; }

	static float32 
	m_one()	
	{ return -one(); }

	static float32 
	pi()		
	{ return  3.1415926535897f; }

	static float32
	big_value()	
	{ 
		return (traits<float32>::sqrt((std::numeric_limits<float32>::max)())/8);
	}

	static float32 
	epsilon() 
	{ return 0.000001f; }


	static float32 
	abs(const float32 x)  
	{ return ::fabsf(x); }

	static float32 
	exp(const float32 x)  
	{ return ::expf(x); }

	static float32 
	log(const float32 x)  
	{ return ::logf(x); }	

	static float32 
	sin(const float32 x)  
	{ return ::sinf(x); }

	static float32 
	cos(const float32 x)  
	{ return ::cosf(x); }

	static float32 
	tan(const float32 x)  
	{ return ::tanf(x); }

	static float32 
	asin(const float32 x) 
	{ return ::asinf(x); }

	static float32 
	acos(const float32 x) 
	{ return ::acosf(x); }

	static float32 
	atan(const float32 x) 
	{ return ::atanf(x); }

	static float32 
	atan2(const float32 y, const float32 x) 
	{ return ::atan2f(y, x); }

	static float32 
	sqrt(const float32 x) 
	{
		assert(traits<float32>::zero() < x);
		return ::sqrtf(x); 
	}

	static float32 
	flip(const float32 x) { return -x; }

	//static
	//int
	//log2int(float32 x)
	//{	// Logarithm base 2.
	//	//	
	//	assert(traits<float32>::zero < x);
	//	return ((*(reinterpret_cast<int*>(&x))) >> 23) - 127;
	//}

private:	// Non-constructible.

	traits();
	traits(const traits<float32>&);
	~traits();
	traits<float32>& operator=(const traits<float32>&);
};

//------------------------------------------------------------------------------

// traits<float64>
//----------------
//! Traits for float64 scalar type.

template <>
class traits<float64> 
{
public:

	enum { is_floating = 1 };
	enum { is_integer  = 0 };
	enum { is_signed   = 1 };

	static float64 
	zero()		
	{ return  0.0; }

	static float64 
	one()		
	{ return  1.0; }

	static float64 
	m_one()	
	{ return -one(); }

	static float64 
	pi()		
	{ return  3.1415926535897; }

	static float64 
	big_value()	
	{ 
		return (traits<float64>::sqrt((std::numeric_limits<float64>::max)())/8);
	}

	static float64 
	epsilon() 
	{ return 0.000001; }

	static float64 
	abs(const float64 x)  
	{ return ::fabs(x); }

	static float64 
	exp(const float64 x)  
	{ return ::exp(x); }

	static float64 
	log(const float64 x)  
	{ return ::log(x); }

	static float64 
	sin(const float64 x)  
	{ return ::sin(x); }

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
	{ 
		assert(traits<float64>::zero() < x);
		return ::sqrt(x); 
	}

	static float64 
	flip(const float64 x) 
	{ return -x; }

private:	// Non-constructible.

	traits();
	traits(const traits<float64>&);
	~traits();
	traits<float64>& operator=(const traits<float64>&);
};

//------------------------------------------------------------------------------

// traits<int8>
//-------------
//! Traits for int8 scalar type.

template <>
class traits<int8> 
{
public:

	enum { is_floating = 0 };
	enum { is_integer  = 1 };
	enum { is_signed   = 1 };

	static int8 
	zero()  
	{ return  0; }

	static int8 
	one()   
	{ return  1; }

	static int8 
	m_one() 
	{ return -one(); }

	static int8 
	epsilon() { return 0; }

	static int8 
	abs(const int8 x)	
	{ return static_cast<int8>(::abs(x)); }

	static int8 
	flip(const int8 x)	{ return -x; }

private:	// Non-constructible.

	traits();
	traits(const traits<int8>&);
	~traits();
	traits<int8>& operator=(const traits<int8>&);
};

//------------------------------------------------------------------------------

// traits<int16>
//--------------
//! Traits for int16 scalar type.

template <>
class traits<int16> 
{
public:

	enum { is_floating = 0 };
	enum { is_integer  = 1 };
	enum { is_signed   = 1 };

	static int16 
	zero()  
	{ return  0; }

	static int16 
	one()   
	{ return  1; }

	static int16 
	m_one() 
	{ return -one(); }

	static int16 
	epsilon() 
	{ return 0; }

	static int16 
	abs(const int16 x)  
	{ return static_cast<int16>(::abs(x)); }

	static int16 
	flip(const int16 x) 
	{ return -x; }

private:	// Non-constructible.

	traits();
	traits(const traits<int16>&);
	~traits();
	traits<int16>& operator=(const traits<int16>&);
};

//------------------------------------------------------------------------------

// traits<int32>
//--------------
//! Traits for int32 scalar type.

template <>
class traits<int32> 
{
public:

	enum { is_floating = 0 };
	enum { is_integer  = 1 };
	enum { is_signed   = 1 };

	static int32 
	zero()  
	{ return  0; }

	static int32 
	one()   
	{ return  1; }

	static int32 
	m_one() 
	{ return flip(one()); }

	static int32 
	epsilon() 
	{ return 0; }

	static int32 
	abs(const int32 x)  
	{ return ::abs(x); }

	static int32 
	flip(const int32 x) 
	{ return -x; }

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

private:	// Non-constructible.

	traits();
	traits(const traits<int32>&);
	~traits();
	traits<int32>& operator=(const traits<int32>&);
};

//------------------------------------------------------------------------------

// traits<int64>
//--------------
//! Traits for int64 scalar type.

template <>
class traits<int64> 
{
public:

	enum { is_floating = 0 };
	enum { is_integer  = 1 };
	enum { is_signed   = 1 };

	static int64 
	zero()  
	{ return  0; }

	static int64 
	one()   
	{ return  1; }

	static int64 
	m_one() 
	{ return -1; }

	static int64 
	epsilon() 
	{ return 0; }

	static int64 
	abs(const int64 x)  
	{ return _abs64(x); }

	static int64 
	flip(const int64 x) 
	{ return -x; }

private:	// Non-constructible.

	traits();
	traits(const traits<int64>&);
	~traits();
	traits<int64>& operator=(const traits<int64>&);
};

//------------------------------------------------------------------------------

// traits<uint8>
//--------------
//! Traits for uint8 scalar type.


template <>
class traits<uint8> 
{
public:

	enum { is_floating = 0 };
	enum { is_integer  = 1 };
	enum { is_signed   = 0 };

	static uint8 
	zero() 
	{ return 0; }

	static uint8 
	one()  
	{ return 1; }

	static uint8 
	epsilon() 
	{ return 0; }

private:	// Non-constructible.

	traits();
	traits(const traits<uint8>&);
	~traits();
	traits<uint8>& operator=(const traits<uint8>&);
};

//------------------------------------------------------------------------------

// traits<uint16>
//---------------
//! Traits for uint16 scalar type.

template <>
class traits<uint16> 
{
public:

	enum { is_floating = 0 };
	enum { is_integer  = 1 };
	enum { is_signed   = 0 };

	static uint16 
	zero() 
	{ return 0; }

	static uint16 
	one()  
	{ return 1; }

	static uint16 
	epsilon() 
	{ return 0; }

private:	// Non-constructible.

	traits();
	traits(const traits<uint16>&);
	~traits();
	traits<uint16>& operator=(const traits<uint16>&);
};

//------------------------------------------------------------------------------

// traits<uint32>
//---------------
//! Traits for uint32 scalar type.

template <>
class traits<uint32> 
{
public:

	enum { is_floating = 0 };
	enum { is_integer  = 1 };
	enum { is_signed   = 0 };

	static uint32 
	zero() 
	{ return 0; }

	static uint32 
	one()  
	{ return 1; }

	static uint32 
	epsilon() 
	{ return 0; }

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

private:	// Non-constructible.

	traits();
	traits(const traits<uint32>&);
	~traits();
	traits<uint32>& operator=(const traits<uint32>&);
};


//------------------------------------------------------------------------------

// traits<uint64>
//---------------
//! Traits for uint64 scalar type.

template <>
class traits<uint64> 
{
public:

	enum { is_floating = 0 };
	enum { is_integer  = 1 };
	enum { is_signed   = 0 };

	static uint64 
	zero() 
	{ return 0; }

	static uint64 
	one()  
	{ return 1; }

	static uint64 
	epsilon() 
	{ return 0; }

private:	// Non-constructible.

	traits();
	traits(const traits<uint64>&);
	~traits();
	traits<uint64>& operator=(const traits<uint64>&);
};

}	// Namespace: thx.

#endif	// THX_TRAITS_HPP_INCLUDED
