//------------------------------------------------------------------------------
//
// Contributors: 
//             1) Tommy Hinks
//
//------------------------------------------------------------------------------

#ifndef THX_VEC_HPP_INCLUDED
#define THX_VEC_HPP_INCLUDED

#include "thx_types.hpp"

//------------------------------------------------------------------------------

namespace thx
{

// vec<N,S> anatomy:
//
// define value_type
// define dimension
// 
// Empty CTOR (set all zeros by default)
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
// operator[] const
// operator[]

//------------------------------------------------------------------------------

// vec<N,S>

template<int64 N, typename S>
class vec
{
public:

    typedef S value_type;
    static const int64 dim = N;

public:		// CTOR/DTOR.

    //! Empty CTOR.
    explicit 
    vec(const S s = 0)
    { 
        for (int64 i(0); i < N; ++i) { 
            _v[i] = s; 
        }
    }

    //! Copy CTOR.
    //explicit
    vec(const vec<N,S> &rhs)
    {
        for (int64 i(0); i < N; ++i) { 
            _v[i] = rhs[i]; 
        }
    }
    
    //! Array CTOR.
    explicit 
    vec(const S *v)
    { 
        for (int64 i(0); i < N; ++i) { 
            _v[i] = v[i]; 
        }
    }

public:		// Operators.

    //! Assignment.
    vec<N,S>& 
    operator=(const vec<N,S> &u)
    {
        for (int64 i(0); i < N; ++i) { 
            _v[i] = u[i]; 
        }
        return *this;
    }

    vec<N,S>& 
    operator+=(const vec<N,S> &u)
    {
        for (int64 i(0); i < N; ++i) { 
            _v[i] += u[i]; 
        }
        return *this;
    }

    vec<N,S>& 
    operator-=(const vec<N,S> &u)
    {
        for (int64 i(0); i < N; ++i) { 
            _v[i] -= u[i]; 
        }
        return *this;
    }

    //! Scalar multiplication.
    vec<N,S>& 
    operator*=(const S s)
    {
        for (int64 i(0); i < N; ++i) { 
            v[i] *= s; 
        }
        return *this;
    }

public:     // Access operators.

    //! Return i'th component. No bounds checking!
    S 
    operator[](const int64 i) const
    { return _v[i];	}

    //! Return i'th component. No bounds checking!
    S& 
    operator[](const int64 i)
    { return _v[i];	}

private:	// Member variables.

    S _v[N];
};

//------------------------------------------------------------------------------

// vec2<S>

template<typename S>
class vec<2,S>
{
public:

    typedef S value_type;
    static const int64 dim = 2;

public:		// CTOR/DTOR.

    //! Empty CTOR.
    explicit
    vec(const S s = 0) 
    {
        _v[0] = s;
        _v[1] = s;
    }	

    //! Copy CTOR.
    //explicit
    vec(const vec<2,S> &rhs)
    {
        _v[0] = rhs[0];
        _v[1] = rhs[1];
    }
    
    //! Array CTOR.
    explicit 
    vec(const S v[2])
    { 
        _v[0] = v[0];
        _v[1] = v[1];
    }

    //! Value CTOR.
    explicit 
    vec(const S v0, const S v1)
    {
        _v[0] = v0;
        _v[1] = v1;
    }

public:		// Operators.

    //! Assignment.
    vec<2,S>& 
    operator=(const vec<2,S> &rhs)
    {
        _v[0] = u[0];
        _v[1] = u[1];
        return *this;
    }

    vec<2,S>& 
    operator+=(const vec<2,S> &u)
    {
        _v[0] += u[0];
        _v[1] += u[1];
        return *this;
    }

    vec<2,S>& 
    operator-=(const vec<2,S> &u)
    {
        _v[0] -= u[0];
        _v[1] -= u[1];
        return *this;
    }

    //! Scalar multiplication.
    vec<2,S>& 
    operator*=(const S s)
    {
        _v[0] *= s;
        _v[1] *= s;
        return *this;
    }

public:     // Access operators.

    //! Return i'th component.
    S 
    operator[](const int64 i) const
    { return _v[i];	}

    //! Return i'th component.
    S& 
    operator[](const int64 i)
    { return _v[i];	}

private:	// Member variables.

    S _v[2];
};

//------------------------------------------------------------------------------

// vec3<S>

template<typename S>
class vec<3,S>
{
public:

    typedef S value_type;
    static const int64 dim = 3;

public:		// CTOR/DTOR.

    //! Empty CTOR. NB: Uninitialized!
    explicit
    vec(const S s = 0) 
    {
        _v[0] = s;
        _v[1] = s;
        _v[2] = s;
    }	

    //! Copy CTOR.
    //explicit
    vec(const vec<3,S> &rhs)
    {
        _v[0] = rhs[0];
        _v[1] = rhs[1];
        _v[2] = rhs[2];
    }
    
    //! Array CTOR.
    explicit 
    vec(const S v[3])
    { 
        _v[0] = v[0];
        _v[1] = v[1];
        _v[2] = v[2];
    }

    //! Value CTOR.
    explicit 
    vec(const S v0, const S v1, const S v2)
    {
        _v[0] = v0;
        _v[1] = v1;
        _v[2] = v2;
    }

public:		// Operators.

    //! Assignment.
    vec<3,S>& 
    operator=(const vec<3,S> &rhs)
    {
        _v[0] = rhs[0];
        _v[1] = rhs[1];
        _v[2] = rhs[2];
        return *this;
    }

    vec<3,S>& 
    operator+=(const vec<3,S> &u)
    {
        _v[0] += u[0];
        _v[1] += u[1];
        _v[2] += u[2];
        return *this;
    }

    vec<3,S>& 
    operator-=(const vec<3,S> &u)
    {
        _v[0] -= u[0];
        _v[1] -= u[1];
        _v[2] -= u[2];
        return *this;
    }

    //! Scalar multiplication.
    vec<3,S>& 
    operator*=(const S s)
    {
        _v[0] *= s;
        _v[1] *= s;
        _v[2] *= s;
        return *this;
    }

public:     // Access operators.

    //! Return i'th component.
    S 
    operator[](const int64 i) const
    { return _v[i];	}

    //! Return i'th component.
    S& 
    operator[](const int64 i)
    { return _v[i];	}

private:	// Member variables.

    S _v[3];
};

//------------------------------------------------------------------------------

// vec4<S>

template<typename S>
class vec<4,S>
{
public:

    typedef S value_type;
    static const int64 dim = 4;

public:		// CTOR/DTOR.

    //! Empty CTOR.
    explicit
    vec(const S s = 0) 
    {
        _v[0] = s;
        _v[1] = s;
        _v[2] = s;
        _v[3] = s;
    }	

    //! Copy CTOR.
    //explicit
    vec(const vec<4,S> &rhs)
    {
        _v[0] = rhs[0];
        _v[1] = rhs[1];
        _v[2] = rhs[2];
        _v[3] = rhs[3];
    }
    
    //! Array CTOR.
    explicit 
    vec(const S v[4])
    { 
        _v[0] = v[0];
        _v[1] = v[1];
        _v[2] = v[2];
        _v[3] = v[3];
    }

    //! Value CTOR.
    explicit 
    vec(const S v0, const S v1, const S v2, const S v3)
    {
        _v[0] = v0;
        _v[1] = v1;
        _v[2] = v2;
        _v[3] = v3;
    }

public:		// Operators.

    //! Assignment.
    vec<4,S>& 
    operator=(const vec<4,S> &rhs)
    {
        _v[0] = rhs[0];
        _v[1] = rhs[1];
        _v[2] = rhs[2];
        _v[3] = rhs[3];
        return *this;
    }

    vec<4,S>& 
    operator+=(const vec<4,S> &u)
    {
        _v[0] += u[0];
        _v[1] += u[1];
        _v[2] += u[2];
        _v[3] += u[3];
        return *this;
    }

    vec<4,S>& 
    operator-=(const vec<4,S> &u)
    {
        _v[0] -= u[0];
        _v[1] -= u[1];
        _v[2] -= u[2];
        _v[3] -= u[3];
        return *this;
    }

    //! Scalar multiplication.
    vec<4,S>& 
    operator*=(const S s)
    {
        _v[0] *= s;
        _v[1] *= s;
        _v[2] *= s;
        _v[3] *= s;
        return *this;
    }

public:     // Access operators.

    //! Return i'th component.
    S 
    operator[](const int64 i) const
    { return _v[i];	}

    //! Return i'th component.
    S& 
    operator[](const int64 i)
    { return _v[i];	}

private:	// Member variables.

    S _v[4];
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
