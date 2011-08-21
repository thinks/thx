//------------------------------------------------------------------------------
//
// Contributors: 
//             1) Tommy Hinks
//
//------------------------------------------------------------------------------

#ifndef THX_VEC_HPP_INCLUDED
#define THX_VEC_HPP_INCLUDED

#include "thx_traits.hpp"
#include "thx_types.hpp"
#include "thx_static_assert.hpp"
#include <cassert>

//------------------------------------------------------------------------------

namespace thx
{

template<int64 N, typename S, class T = traits<S> >
class vec
{
public:

	typedef S value_type;
	typedef T traits_type;

	static const int64 dim = N;

public:		// CTOR/DTOR.

	//! CTOR. NB: Uninitialized!
	explicit
	vec() 
	{}	

	explicit
	vec(const vec<N,S,T> &rhs)
	{
		for (int64 i(0); i < N; ++i) { 
			_v[i] = rhs[i]; 
		}
	}

	template<typename S2, class T2>
	explicit
	vec(const vec<N,S2,T2> &rhs)
	{
		for (int64 i(0); i < N; ++i) { 
			_v[i] = static_cast<S>(rhs[i]); 
		}
	}

    explicit 
	vec(const S v)
    { 
		for (int64 i(0); i < N; ++i) { 
			_v[i] = v; 
		}
	}

	template<typename S2>
	explicit
	vec(const S2 v)
	{
		const v2(static_cast<S>(v));
		for (int64 i(0); i < N; ++i) { 
			_v[i] = v2; 
		}
	}	
    
    explicit 
	vec(const S *v)
    { 
		for (int64 i(0); i < N; ++i) { 
			_v[i] = v[i]; 
		}
	}

	template<typename S2>
	vec(const S2 *v)
	{
		for (int64 i(0); i < N; ++i) { 
			_v[i] = static_cast<S>(v[i]); 
		}
	}

	//! DTOR.
	~vec()
	{}

public:

	vec<N,S,T>& 
	operator=(const vec<N,S,T> &rhs)
	{
		for (int64 i(0); i < N; ++i) { 
			_v[i] = rhs[i]; 
		}

		return *this;
	}

	template<typename S2, typename T2>
	vec<N,S,T>& 
	operator=(const vec<N,S2,T2> &rhs)
	{
		for (int64 i(0); i < N; ++i) { 
			_v[i] = static_cast<S>(rhs[i]); 
		}

		return *this;
	}


	vec<N,S,T>& 
	operator+=(const vec<N,S,T> &rhs)
	{
		for (int64 i(0); i < N; ++i) { 
			_v[i] += rhs[i]; 
		}

		return *this;
	}


	template<typename S2, typename T2>
	vec<N,S,T>& 
	operator+=(const vec<N,S2,T2> &rhs)
	{
		for (int64 i(0); i < N; ++i) { 
			_v[i] += static_cast<S>(rhs[i]); 
		}

		return *this;
	}


	vec<N,S,T>& 
	operator-=(const vec<N,S,T> &rhs)
	{
		for (int64 i(0); i < N; ++i) { 
			_v[i] -= rhs[i]; 
		}

		return *this;
	}

	template<typename S2, typename T2>
	vec<N,S,T>& 
	operator-=(const vec<N,S2,T2> &rhs)
	{
		for (int64 i(0); i < N; ++i) { 
			_v[i] -= static_cast<S>(rhs[i]); 
		}

		return *this;
	}


	vec<N,S,T>& 
	operator*=(const S rhs)
	{
		for (int64 i(0); i < N; ++i) { 
			v[i] *= rhs; 
		}

		return *this;
	}

	template<typename S2>
	vec<N,S,T>& 
	operator*=(const S2 rhs)
	{
		for (int64 i(0); i < N; ++i) { 
			v[i] *= static_cast<S>(rhs); 
		}

		return *this;
	}

	vec<N,S,T>& 
	operator/=(const S rhs)
	{
		assert(!is_zero(rhs));
		if (T::is_floating) {
			// Compile-time branching.
 
			const S inv_fact(T::one()/rhs);
			for(int64 i(0); i < N; ++i) { 
				v[i] *= inv_fact; 
			}		
		}
		else {
			for(int64 i = 0; i < N; ++i) { 
				v[i] /= rhs; 
			}		
		}

		return *this;
	}

	S 
	operator[](const int64 i) const
	{
		assert(0 <= i && i < dim);
		return v[i];
	}

	S& 
	operator[](const int64 i)
	{
		assert(0 <= i && i < dim);
		return v[i];
	}

private:	// Member variables.

	S _v[N];
};

//------------------------------------------------------------------------------







template<int64 N, typename S, class T = traits<S> >
class vec
{
public:
	typedef S value_type;
	typedef T traits_type;
	static const int64 dim = N;

public:	// The data is the interface.
	S v[N];

public:
	vec() {}	// NB: Uninitialized!

	vec(const vec<N,S,T>& rhs)
	{
		for(int64 i = 0; i < N; ++i) { v[i] = rhs.v[i]; }
	}

    explicit 
	vec(S v_)
    { 
		for(int64 i = 0; i < N; ++i) { v[i] = v_; }
	}
    
    explicit 
	vec(const S *v_)
    { 
		for(int64 i = 0; i < N; ++i) { v[i] = v_[i]; }
	}

	vec<N,S,T>& 
	operator=(const vec<N,S,T>& rhs)
	{
		for(int64 i = 0; i < N; ++i) { v[i] = rhs.v[i]; }
		return *this;
	}

	vec<N,S,T>& 
	operator+=(const vec<N,S,T>& rhs)
	{
		for(int64 i = 0; i < N; ++i) { v[i] += rhs.v[i]; }
		return *this;
	}

	vec<N,S,T>& 
	operator-=(const vec<N,S,T>& rhs)
	{
		for(int64 i = 0; i < N; ++i) { v[i] -= rhs.v[i]; }		
		return *this;
	}

	vec<N,S,T>& 
	operator*=(const S rhs)
	{
		for(int64 i = 0; i < N; ++i) { v[i] *= rhs; }		
		return *this;
	}

	vec<N,S,T>& 
	operator/=(const S rhs)
	{
		assert(!is_zero(rhs));
		if( T::is_floating )
		{	// Compile-time branching.
			//
			const S inv_fact(T::one()/rhs);
			for(int64 i = 0; i < N; ++i) { v[i] *= inv_fact; }		
		}
		else
		{
			for(int64 i = 0; i < N; ++i) { v[i] /= rhs; }		
		}
		return *this;
	}

	S 
	operator[](const int64 i) const
	{
		assert(0 <= i && i < dim);
		return v[i];
	}

	S& 
	operator[](const int64 i)
	{
		assert(0 <= i && i < dim);
		return v[i];
	}
};

//==============================================================================

// vec2

template<typename S, class T>
class vec<2,S,T>
{
public:

	typedef S value_type;
	typedef T traits_type;
	static const int64 dim = 2;

	static const vec<2,S,T> x_axis;
	static const vec<2,S,T> y_axis;
	static const vec<2,S,T> origin;

public:	// The data is the interface.

	S x;
	S y;

public:

	vec() {}	// NB: Uninitialized!
	explicit vec(const S v)				  : x(v),     y(v)	   {}
	explicit vec(const S* v)			  : x(v[0]),  y(v[1])  {}
	explicit vec(const S x_, const S y_)  : x(x_),    y(y_)	   {}

	~vec() 
	{ 
		THX_STATIC_ASSERT(sizeof(vec<dim,S,T>) == dim*sizeof(S), invalid_size); 
	}

	// Default copy & assign.

	vec<2,S,T>& 
	operator+=(const vec<2,S,T>& rhs)
	{
		x += rhs.x;
		y += rhs.y;
		return *this;
	}

	vec<2,S,T>& 
	operator-=(const vec<2,S,T>& rhs)
	{
		x -= rhs.x;
		y -= rhs.y;
		return *this;
	}

	vec<2,S,T>& 
	operator*=(const S rhs)
	{
		x *= rhs;
		y *= rhs;
		return *this;
	}

	vec<2,S,T>& 
	operator/=(const S rhs)
	{
		assert(!is_zero(rhs));
		if( T::is_floating )
		{	// Compile-time branching.
			//
			const S inv_fact(T::one()/rhs);
			x *= inv_fact;
			y *= inv_fact;
		}
		else
		{
			x /= rhs;
			y /= rhs;
		}
		return *this;
	}

	S 
	operator[](const int64 i) const
	{
		assert(0 <= i && i < dim);
		return *(&x + i);
	}

	S& 
	operator[](const int64 i)
	{
		assert(0 <= i && i < dim);
		return *(&x + i);
	}
};

// Static constants.
//
template<typename S, class T> 
const vec<2,S,T> vec<2,S,T>::x_axis(T::one(), T::zero());

template<typename S, class T> 
const vec<2,S,T> vec<2,S,T>::y_axis(T::zero(), T::one());

template<typename S, class T> 
const vec<2,S,T> vec<2,S,T>::origin(T::zero(), T::zero());

//==============================================================================

// vec3 

template<typename S, class T>
class vec<3,S,T>
{
public:

	typedef S value_type;
	typedef T traits_type;
	static const int64 dim = 3;

	static const vec<3,S,T> x_axis;
	static const vec<3,S,T> y_axis;
	static const vec<3,S,T> z_axis;
	static const vec<3,S,T> origin;

public:	// The data is the interface.

	S x;
	S y;
	S z;

public:

	vec() {}	// NB: Uninitialized!
	explicit vec(const S v) : x(v), y(v), z(v) {}
	explicit vec(const S* v) : x(v[0]), y(v[1]), z(v[2]) {}
	explicit vec(const S x_, const S y_, const S z_) : x(x_), y(y_), z(z_) {}

	~vec() 
	{ 
		THX_STATIC_ASSERT(sizeof(vec<dim,S,T>) == dim*sizeof(S), invalid_size); 
	}

	// Default copy & assign.

	vec<3,S,T>& 
	operator+=(const vec<3,S,T>& rhs)
	{
		x += rhs.x;
		y += rhs.y;
		z += rhs.z;
		return *this;
	}

	vec<3,S,T>& 
	operator-=(const vec<3,S,T>& rhs)
	{
		x -= rhs.x;
		y -= rhs.y;
		z -= rhs.z;
		return *this;
	}

	vec<3,S,T>& 
	operator*=(const S rhs)
	{
		x *= rhs;
		y *= rhs;
		z *= rhs;
		return *this;
	}

	vec<3,S,T>& 
	operator/=(const S rhs)
	{
		assert(!is_zero(rhs));
		if( T::is_floating )
		{	// Compile-time branching.
			//
			const S inv_fact(T::one()/rhs);
			x *= inv_fact;
			y *= inv_fact;
			z *= inv_fact;
		}
		else
		{
			x /= rhs;
			y /= rhs;
			z /= rhs;
		}
		return *this;
	}

	S 
	operator[](const int64 i) const
	{
		assert(0 <= i && i < dim);
		return *(&x + i);
	}

	S& 
	operator[](const int64 i)
	{
		assert(0 <= i && i < dim);
		return *(&x + i);
	}
};

// Static constants.
//
template<typename S, class T> 
const vec<3,S,T> vec<3,S,T>::x_axis(T::one(),  T::zero(), T::zero());

template<typename S, class T> 
const vec<3,S,T> vec<3,S,T>::y_axis(T::zero(), T::one(),  T::zero());

template<typename S, class T> 
const vec<3,S,T> vec<3,S,T>::z_axis(T::zero(), T::zero(), T::one());

template<typename S, class T> 
const vec<3,S,T> vec<3,S,T>::origin(T::zero(), T::zero(), T::zero());

//==============================================================================

// vec4 

template<typename S, class T>
class vec<4,S,T>
{
public:

	typedef S value_type;
	typedef T traits_type;
	static const int64 dim = 4;

	static const vec<4,S,T> x_axis;
	static const vec<4,S,T> y_axis;
	static const vec<4,S,T> z_axis;
	static const vec<4,S,T> w_axis;
	static const vec<4,S,T> origin;

public:	// The data is the interface.

	S x;
	S y;
	S z;
	S w;

public:

	vec() {}	// NB: Uninitialized!
	explicit vec(const S v) : x(v), y(v), z(v), w(v) {}
	explicit vec(const S* v) : x(v[0]), y(v[1]), z(v[2]), w(v[3]) {}
	explicit vec(const S x_, const S y_, const S z_, const S w_) 
		: x(x_), y(y_), z(z_), w(w_) {}
	
	~vec() 
	{ 
		THX_STATIC_ASSERT(sizeof(vec<dim,S,T>) == dim*sizeof(S), invalid_size); 
	}

	// Default copy & assign.

	vec<4,S,T>& 
	operator+=(const vec<4,S,T>& rhs)
	{
		x += rhs.x;
		y += rhs.y;
		z += rhs.z;
		w += rhs.w;
		return *this;
	}

	vec<4,S,T>& 
	operator-=(const vec<4,S,T>& rhs)
	{
		x -= rhs.x;
		y -= rhs.y;
		z -= rhs.z;
		w -= rhs.w;
		return *this;
	}

	vec<4,S,T>& 
	operator*=(const S rhs)
	{
		x *= rhs;
		y *= rhs;
		z *= rhs;
		w *= rhs;
		return *this;
	}

	vec<4,S,T>& 
	operator/=(const S rhs)
	{
		assert(!is_zero(rhs));
		if( T::is_floating )
		{	// Compile-time branching.
			//
			const S inv_fact(T::one()/rhs);
			x *= inv_fact;
			y *= inv_fact;
			z *= inv_fact;
			w *= inv_fact;
		}
		else
		{
			x /= rhs;
			y /= rhs;
			z /= rhs;
			w /= rhs;
		}
		return *this;
	}

	S 
	operator[](const int64 i) const
	{
		assert(0 <= i && i < dim);
		return *(&x + i);
	}

	S& 
	operator[](const int64 i)
	{
		assert(0 <= i && i < dim);
		return *(&x + i);
	}
};

// Static constants.
//
template<typename S, class T> 
const vec<4,S,T> vec<4,S,T>::x_axis(T::one(),  T::zero(), T::zero(), T::zero());

template<typename S, class T> 
const vec<4,S,T> vec<4,S,T>::y_axis(T::zero(), T::one(),  T::zero(), T::zero());

template<typename S, class T> 
const vec<4,S,T> vec<4,S,T>::z_axis(T::zero(), T::zero(), T::one(),  T::zero());

template<typename S, class T> 
const vec<4,S,T> vec<4,S,T>::w_axis(T::zero(), T::zero(), T::zero(), T::one());

template<typename S, class T> 
const vec<4,S,T> vec<4,S,T>::origin(T::zero(), T::zero(), T::zero(), T::zero());

//==============================================================================

// Convenient types, add more if appropriate.
//
typedef vec<2,float32>	vec2f32;
typedef vec<2,float64>	vec2f64;
typedef vec<2,int8>		vec2i8;
typedef vec<2,int16>	vec2i16;
typedef vec<2,int32>	vec2i32;
typedef vec<2,int64>	vec2i64;
typedef vec<2,uint8>	vec2u8;
typedef vec<2,uint16>	vec2u16;
typedef vec<2,uint32>	vec2u32;

typedef vec<3,float32>	vec3f32;
typedef vec<3,float64>	vec3f64;
typedef vec<3,int8>		vec3i8;
typedef vec<3,int16>	vec3i16;
typedef vec<3,int32>	vec3i32;
typedef vec<3,int64>	vec3i64;
typedef vec<3,uint8>	vec3u8;
typedef vec<3,uint16>	vec3u16;
typedef vec<3,uint32>	vec3u32;

typedef vec<4,float32>	vec4f32;
typedef vec<4,float64>	vec4f64;
typedef vec<4,int8>		vec4i8;
typedef vec<4,int16>	vec4i16;
typedef vec<4,int32>	vec4i32;
typedef vec<4,int64>	vec4i64;
typedef vec<4,uint8>	vec4u8;
typedef vec<4,uint16>	vec4u16;
typedef vec<4,uint32>	vec4u32;

//==============================================================================
}	// Namespace: thx.

#endif	// THX_VEC_HPP_INCLUDED
