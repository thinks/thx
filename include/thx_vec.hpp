//------------------------------------------------------------------------------
//
// Contributors: 
//             1) Tommy Hinks
//
//------------------------------------------------------------------------------

#ifndef THX_VEC_HPP_INCLUDED
#define THX_VEC_HPP_INCLUDED

#include "thx_types.hpp"
#include <iostream>

//------------------------------------------------------------------------------

namespace thx
{

// vec<N,S> anatomy:
//
// define value_type
// define dimension
// 
// Default CTOR (set all zeros by default)
// Copy CTOR
// Array CTOR
// Value CTOR (specializations only)
// (All vec's have default DTOR)
//
// operator=
// operator+=
// operator-=
// operator*=(scalar)
//
// operator[]
// operator[] const

//------------------------------------------------------------------------------

// vec<N,S>
// --------
//! DOCS

template<int64 N, typename S>
class vec
{
public:

    typedef S value_type;
    static const int64 dim = N;

public:		// CTOR's.

    //! Default CTOR.
    explicit 
    vec(const S x = 0)
    { 
        for (int64 i = 0; i < N; ++i) { 
            _v[i] = x; 
        }
    }

    //! Copy CTOR.
    vec(const vec<N,S> &rhs)
    { std::memcpy(_v, rhs._v, N*sizeof(S)); }
    
    //! Array CTOR.
    explicit 
    vec(const S *v)
    { std::memcpy(_v, v, N*sizeof(S)); }

public:		// Operators.

    //! Assignment.
    vec<N,S>& 
    operator=(const vec<N,S> &rhs)
    {
        std::memcpy(_v, rhs._v, N*sizeof(S));
        return *this;
    }

    vec<N,S>& 
    operator+=(const vec<N,S> &u)
    {
        for (int64 i(0); i < N; ++i) { 
            _v[i] += u._v[i]; 
        }
        return *this;
    }

    vec<N,S>& 
    operator-=(const vec<N,S> &u)
    {
        for (int64 i(0); i < N; ++i) { 
            _v[i] -= u._v[i]; 
        }
        return *this;
    }

    //! Scalar multiplication.
    vec<N,S>& 
    operator*=(const S s)
    {
        for (int64 i(0); i < N; ++i) { 
            _v[i] *= s; 
        }
        return *this;
    }

public:     // Access operators.

    //! Return i'th component. No bounds checking!
    S& 
    operator[](const int64 i)
    { return _v[i];	}

    //! Return i'th component. No bounds checking!
    const S& 
    operator[](const int64 i) const
    { return _v[i];	}

private:	    // Member variables.

    S _v[N];    //!< Data.
};

//------------------------------------------------------------------------------

// vec2<S>
// -------
//! DOCS

template<typename S>
class vec<2,S>
{
public:

    typedef S value_type;
    static const int64 dim = 2;

public:		// CTOR/DTOR.

    //! Default CTOR.
    explicit
    vec(const S x = 0) 
    { _v[0] = x; _v[1] = x; }	

    //! Copy CTOR.
    vec(const vec<2,S> &rhs)
    { std::memcpy(_v, rhs._v, 2*sizeof(S)); }
    
    //! Array CTOR.
    explicit 
    vec(const S v[2])
    { std::memcpy(_v, v, 2*sizeof(S)); }

    //! Value CTOR.
    explicit 
    vec(const S v0, const S v1)
    { _v[0] = v0; _v[1] = v1; }

public:		// Operators.

    //! Assignment.
    vec<2,S>& 
    operator=(const vec<2,S> &rhs)
    {
        std::memcpy(_v, rhs._v, 2*sizeof(S));
        return *this;
    }

    vec<2,S>& 
    operator+=(const vec<2,S> &u)
    {
        _v[0] += u._v[0]; _v[1] += u._v[1];
        return *this;
    }

    vec<2,S>& 
    operator-=(const vec<2,S> &u)
    {
        _v[0] -= u._v[0]; _v[1] -= u._v[1];
        return *this;
    }

    //! Scalar multiplication.
    vec<2,S>& 
    operator*=(const S x)
    {
        _v[0] *= x; _v[1] *= x;
        return *this;
    }

public:         // Access operators.

    //! Return i'th component. No bounds checking!
    S& 
    operator[](const int64 i)
    { return _v[i];	}

    //! Return i'th component. No bounds checking!
    const S& 
    operator[](const int64 i) const
    { return _v[i];	}

private:	    // Member variables.

    S _v[2];    //!< Data.
};

//------------------------------------------------------------------------------

// vec3<S>
// -------
//! DOCS

template<typename S>
class vec<3,S>
{
public:

    typedef S value_type;
    static const int64 dim = 3;

public:		// CTOR's.

    //! Default CTOR.
    explicit
    vec(const S x = 0) 
    { _v[0] = x; _v[1] = x; _v[2] = x; }	

    //! Copy CTOR.
    vec(const vec<3,S> &rhs)
    { std::memcpy(_v, rhs._v, 3*sizeof(S)); }
    
    //! Array CTOR.
    explicit 
    vec(const S v[3])
    { std::memcpy(_v, v, 3*sizeof(S)); }

    //! Value CTOR.
    explicit 
    vec(const S v0, const S v1, const S v2)
    { _v[0] = v0; _v[1] = v1; _v[2] = v2; }

public:		// Operators.

    //! Assignment.
    vec<3,S>& 
    operator=(const vec<3,S> &rhs)
    {
        std::memcpy(_v, rhs._v, 3*sizeof(S));
        return *this;
    }

    vec<3,S>& 
    operator+=(const vec<3,S> &u)
    {
        _v[0] += u._v[0]; _v[1] += u._v[1]; _v[2] += u._v[2];
        return *this;
    }

    vec<3,S>& 
    operator-=(const vec<3,S> &u)
    {
        _v[0] -= u._v[0]; _v[1] -= u._v[1]; _v[2] -= u._v[2];
        return *this;
    }

    //! Scalar multiplication.
    vec<3,S>& 
    operator*=(const S x)
    {
        _v[0] *= x; _v[1] *= x; _v[2] *= x;
        return *this;
    }

public:     // Access operators.

    //! Return i'th component. No bounds checking!
    S& 
    operator[](const int64 i)
    { return _v[i];	}

    //! Return i'th component. No bounds checking!
    const S& 
    operator[](const int64 i) const
    { return _v[i];	}

private:	    // Member variables.

    S _v[3];    //!< Data.
};

//------------------------------------------------------------------------------

// vec4<S>
// -------
//! DOCS

template<typename S>
class vec<4,S>
{
public:

    typedef S value_type;
    static const int64 dim = 4;

public:		// CTOR's.

    //! Default CTOR.
    explicit
    vec(const S x = 0) 
    { _v[0] = x; _v[1] = x; _v[2] = x; _v[3] = x; }	

    //! Copy CTOR.
    vec(const vec<4,S> &rhs)
    { std::memcpy(_v, rhs._v, 4*sizeof(S)); }
    
    //! Array CTOR.
    explicit 
    vec(const S v[4])
    { std::memcpy(_v, v, 4*sizeof(S)); }

    //! Value CTOR.
    explicit 
    vec(const S v0, const S v1, const S v2, const S v3)
    { _v[0] = v0; _v[1] = v1; _v[2] = v2; _v[3] = v3; }

public:		// Operators.

    //! Assignment.
    vec<4,S>& 
    operator=(const vec<4,S> &rhs)
    {
        std::memcpy(_v, rhs._v, 4*sizeof(S));
        return *this;
    }

    vec<4,S>& 
    operator+=(const vec<4,S> &u)
    {
        _v[0] += u._v[0]; _v[1] += u._v[1]; _v[2] += u._v[2]; _v[3] += u._v[3];
        return *this;
    }

    vec<4,S>& 
    operator-=(const vec<4,S> &u)
    {
        _v[0] -= u._v[0]; _v[1] -= u._v[1]; _v[2] -= u._v[2]; _v[3] -= u._v[3];
        return *this;
    }

    //! Scalar multiplication.
    vec<4,S>& 
    operator*=(const S x)
    {
        _v[0] *= x; _v[1] *= x; _v[2] *= x; _v[3] *= x;
        return *this;
    }

public:     // Access operators.

    //! Return i'th component. No bounds checking!
    S& 
    operator[](const int64 i)
    { return _v[i];	}

    //! Return i'th component. No bounds checking!
    const S& 
    operator[](const int64 i) const
    { return _v[i];	}

private:	    // Member variables.

    S _v[4];    //!< Data.
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

//------------------------------------------------------------------------------

namespace std 
{

//! Binary operator: std::ostream << vec<N,S>
template<thx::int64 N, typename S>
ostream&
operator<<(ostream &os, const thx::vec<N,S> &rhs)
{
    os	<< "[";
    for (thx::int64 i = 0; i < N; ++i) {
        os << rhs[i] << (i != (N - 1) ? ", " : "");
    }
    os << "]";
    return os;
}

}	// Namespace: std.

//------------------------------------------------------------------------------

#endif	// THX_VEC_HPP_INCLUDED
