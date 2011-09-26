//------------------------------------------------------------------------------
//
// Contributors: 
//             1) Tommy Hinks
//
//------------------------------------------------------------------------------

#ifndef THX_VEC_HPP_INCLUDED
#define THX_VEC_HPP_INCLUDED

#include "thx_types.hpp"
#include <cassert>

//------------------------------------------------------------------------------

namespace thx
{

template<int64 N, typename S>
class vec
{
public:

	typedef S	  value_type;

	static const int64 dim = N;

public:		// CTOR/DTOR.

	//! CTOR. NB: Uninitialized!
	explicit
	vec() 
	{}	

	//! Copy CTOR.
	explicit
	vec(const vec<N,S> &rhs)
	{
		for (int64 i(0); i < N; ++i) { 
			_v[i] = rhs[i]; 
		}
	}

	template<typename S2>
	explicit
	vec(const vec<N,S2> &rhs)
	{
		for (int64 i(0); i < N; ++i) { 
			_v[i] = traits<S>::scalar_cast<S2>(rhs[i]); 
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
		const v2(traits<S>::scalar_cast<S2>(v));
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
	explicit
	vec(const S2 *v)
	{
		for (int64 i(0); i < N; ++i) { 
			_v[i] = traits<S>::scalar_cast<S2>(v[i]); 
		}
	}

	//! DTOR.
	~vec()
	{}

public:		// Operators.

	vec<N,S>& 
	operator=(const vec<N,S> &rhs)
	{
		for (int64 i(0); i < N; ++i) { 
			_v[i] = rhs[i]; 
		}
		return *this;
	}

	template<typename S2>
	vec<N,S>& 
	operator=(const vec<N,S2> &rhs)
	{
		for (int64 i(0); i < N; ++i) { 
			_v[i] = traits<S>::scalar_cast<S2>(rhs[i]); 
		}
		return *this;
	}


	vec<N,S>& 
	operator+=(const vec<N,S> &rhs)
	{
		for (int64 i(0); i < N; ++i) { 
			_v[i] += rhs[i]; 
		}
		return *this;
	}


	template<typename S2>
	vec<N,S>& 
	operator+=(const vec<N,S2> &rhs)
	{
		for (int64 i(0); i < N; ++i) { 
			_v[i] += traits<S>::scalar_cast<S2>(rhs[i]); 
		}
		return *this;
	}


	vec<N,S>& 
	operator-=(const vec<N,S> &rhs)
	{
		for (int64 i(0); i < N; ++i) { 
			_v[i] -= rhs[i]; 
		}
		return *this;
	}

	template<typename S2>
	vec<N,S>& 
	operator-=(const vec<N,S2> &rhs)
	{
		for (int64 i(0); i < N; ++i) { 
			_v[i] -= traits<S>::scalar_cast<S2>(rhs[i]); 
		}
		return *this;
	}


	vec<N,S>& 
	operator*=(const S rhs)
	{
		for (int64 i(0); i < N; ++i) { 
			v[i] *= rhs; 
		}
		return *this;
	}

	template<typename S2>
	vec<N,S>& 
	operator*=(const S2 rhs)
	{
		for (int64 i(0); i < N; ++i) { 
			v[i] *= traits<S>::scalar_cast<S2>(rhs); 
		}
		return *this;
	}

	// Access operators.

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

// Convenient types, add more if appropriate.

typedef vec<2,float32>	vec2f32;
typedef vec<2,float64>	vec2f64;
typedef vec<2,int8>		vec2i8;
typedef vec<2,int16>	vec2i16;
typedef vec<2,int32>	vec2i32;
typedef vec<2,int64>	vec2i64;
typedef vec<2,uint8>	vec2ui8;
typedef vec<2,uint16>	vec2ui16;
typedef vec<2,uint32>	vec2ui32;
typedef vec<2,uint64>	vec2ui64;

typedef vec<3,float32>	vec3f32;
typedef vec<3,float64>	vec3f64;
typedef vec<3,int8>		vec3i8;
typedef vec<3,int16>	vec3i16;
typedef vec<3,int32>	vec3i32;
typedef vec<3,int64>	vec3i64;
typedef vec<3,uint8>	vec3ui8;
typedef vec<3,uint16>	vec3ui16;
typedef vec<3,uint32>	vec3ui32;
typedef vec<3,uint64>	vec3ui64;

typedef vec<4,float32>	vec4f32;
typedef vec<4,float64>	vec4f64;
typedef vec<4,int8>		vec4i8;
typedef vec<4,int16>	vec4i16;
typedef vec<4,int32>	vec4i32;
typedef vec<4,int64>	vec4i64;
typedef vec<4,uint8>	vec4ui8;
typedef vec<4,uint16>	vec4ui16;
typedef vec<4,uint32>	vec4ui32;
typedef vec<4,uint64>	vec4ui64;

}	// Namespace: thx.

#endif	// THX_VEC_HPP_INCLUDED
