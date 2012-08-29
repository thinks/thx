//------------------------------------------------------------------------------
//
// Contributors: 
//             1) Tommy Hinks
//
//------------------------------------------------------------------------------

#ifndef THX_MAT_HPP_INCLUDED
#define THX_MAT_HPP_INCLUDED

#include "thx_types.hpp"
#include <cassert>

//------------------------------------------------------------------------------

namespace thx
{

// mat<N,S> anatomy:
//
// Define value_type
// Define dimension
// Define linear size
//
// constexpr mat<N,S> identity() (specializations only)
//
// Default constexpr CTOR (set to identity by default)
// Array constexpr CTOR (specializations only)
// Value constexpr CTOR (specializations only)
// (All mat's have default DTOR)
// (All mat's have compiler-generated copy CTOR)
// (All mat's have compiler-generated operator=)
//
// operator+=
// operator-=
// operator*=(scalar)
// operator*=(matrix)
//
// S  operator()(row, col) const
// S& operator()(row, col)
// S  operator[](i) const
// S& operator[](i)
//
// const S* const_data() const
// S* data()
// 
// Matrix values are stored in column-major order. 

//------------------------------------------------------------------------------

// mat<N,S>
// --------
//! DOCS

template<int64 N, typename S>
class mat
{
public:

    typedef S value_type;
    static const int64 dim = N;
    static const int64 linear_size = dim*dim;
    static const mat<N,S> identity;

public:

    //! Default CTOR.
    explicit
    mat(const S v = 1)
    {
        for (int64 i = 0; i < N; ++i) {
            for (int64 j = 0; j < N; ++j) {
                _v[i + N*j] = ((i == j) ? v : 0); // Set diagonal to value.
            }
        }
    }

public:		// Operators.

    mat<N,S>& 
    operator+=(const mat<N,S> &b)
    {
        for (int64 i = 0; i < size; ++i) {
            _v[i] += b._v[i];
        }
        return *this;
    }

    mat<N,S>& 
    operator-=(const mat<N,S> &b)
    {
        for (int64 i = 0; i < size; ++i) {
            _v[i] -= b._v[i];
        }
        return *this;
    }

    mat<N,S>& 
    operator*=(const S s)
    {
        for (int64 i = 0; i < size; ++i) {
            _v[i] *= s;
        }
        return *this;
    }

    //! Matrix multiplication.
    mat<N,S>& 
    operator*=(const mat<N,S> &b)
    {	
        const mat<N,S> a(*this);  // Copy.
        for (int64 i = 0; i < N; ++i) {
            for (int64 j = 0; j < N; ++j) {
                _v[i + N*j] = 0;
                for (int64 k = 0; k < N; ++k) {
                    _v[i + N*j] += a._v[i + N*k]*b._v[k + N*j];
                }
            }
        }
        return *this;
    }

public:     // Access operators.

    //! Return element at row 'i' and column 'j'. No bounds checking!
    S&
    operator()(const int64 i, const int64 j)
    { return _v[i + dim*j]; }

    //! Return element at row 'i' and column 'j'. No bounds checking!
    S
    operator()(const int64 i, const int64 j) const
    { return _v[i + dim*j]; }

    //! Return i'th element. No bounds checking!
    S&
    operator[](const int64 i)
    { return _v[i]; }

    //! Return i'th element. No bounds checking!
    S
    operator[](const int64 i) const
    { return _v[i]; }

public:		// Data.

    //! Const data.
    const S* 
    const_data() const
    { return &_v[0]; }

    //! Mutable data.
    S* 
    data()
    { return &_v[0]; }

private:		// Member variables

    S _v[linear_size];  //!< Data.
};

// Static constants.

template<int64 N, typename S>
const mat<N,S> mat<N,S>::identity(1);

//------------------------------------------------------------------------------

// mat<2,S>
// --------
//! DOCS

template<typename S>
class mat<2,S>
{
public:

    typedef S value_type;
    static const int64 dim = 2;
    static const int64 linear_size = dim*dim;

	constexpr mat<2,S>
	identity()
	{ return mat<2,S>(1); }

public:

    //! Default CTOR.
    constexpr explicit
    mat(const S v = 1)
		: _v{v, 0, // Col 0.
			 0, v} // Col 1.
    {}

    //! Array CTOR - column-major.
    constexpr explicit
    mat(const S v[4])
		: _v{v[0], v[1], // Col 0.
			 v[2], v[3]} // Col 1.
    {}		

    //! Value CTOR - column-major.
    constexpr explicit
    mat(const S v0, const S v2,
        const S v1, const S v3)
		: _v{v0, v1, // Col 0.
			 v2, v3} // Col 1.
    {}

public:		// Operators.

    mat<2,S>& 
    operator+=(const mat<2,S> &b)
    {
        _v[0] += b._v[0]; _v[2] += b._v[2];
        _v[1] += b._v[1]; _v[3] += b._v[3];
        return *this;
    }

    mat<2,S>& 
    operator-=(const mat<2,S> &b)
    {
        _v[0] -= b._v[0]; _v[2] -= b._v[2];
        _v[1] -= b._v[1]; _v[3] -= b._v[3];
        return *this;
    }

    mat<2,S>& 
    operator*=(const S s)
    {
        _v[0] *= s; _v[2] *= s;
        _v[1] *= s; _v[3] *= s;
        return *this;
    }

    //! Matrix multiplication.
    mat<2,S>& 
    operator*=(const mat<2,S> &b)
    {	
        const mat<2,S> a(*this);
        _v[0] = a._v[0]*b._v[0] + a._v[2]*b._v[1];
		_v[1] = a._v[1]*b._v[0] + a._v[3]*b._v[1];
        _v[2] = a._v[0]*b._v[2] + a._v[2]*b._v[3];
        _v[3] = a._v[1]*b._v[2] + a._v[3]*b._v[3];
		return *this;
    }

public:     // Access operators.

    //! Return element at row 'i' and column 'j'. No bounds checking!
    S&
    operator()(const int64 i, const int64 j)
    { return _v[i + dim*j]; }

    //! Return element at row 'i' and column 'j'. No bounds checking!
    S
    operator()(const int64 i, const int64 j) const
    { return _v[i + dim*j]; }

    //! Return i'th element. No bounds checking!
    S&
    operator[](const int64 i)
    { return _v[i]; }

    //! Return i'th element. No bounds checking!
    S
    operator[](const int64 i) const
    { return _v[i]; }

public:		// Data.

    //! Const data.
    const S* 
    const_data() const
    { return &_v[0]; }

    //! Mutable data.
    S* 
    data()
    { return &_v[0]; }

private:		// Member variables

    S _v[linear_size];    //!< Data.
};

//------------------------------------------------------------------------------

// mat<3,S>
// --------
//! DOCS

template<typename S>
class mat<3,S>
{
public:

    typedef S value_type;
    static const int64 dim = 3;
    static const int64 linear_size = dim*dim;

    constexpr mat<3,S>
    identity()
    { return mat<3,S>(1); }

public:

    //! Default CTOR.
    constexpr explicit
    mat(const S v = 1)
        : _v{v, 0, 0, // Col 0.
             0, v, 0, // Col 1.
             0, 0, v} // Col 2.
    {}

    //! Array CTOR - column-major.
    constexpr explicit
    mat(const S v[9])
        : _v{v[0], v[1], v[2], // Col 0.
             v[3], v[4], v[5], // Col 1.
             v[6], v[7], v[8]} // Col 2.
    {}

    //! Value CTOR - column-major.
    constexpr explicit
    mat(const S v0, const S v3, const S v6,
        const S v1, const S v4, const S v7,
        const S v2, const S v5, const S v8)
        : _v{v0, v1, v2, // Col 0.
             v3, v4, v5, // Col 1.
             v6, v7, v8} // Col 2.
    {}

public:		// Operators.

    mat<3,S>& 
    operator+=(const mat<3,S> &b)
    {
        _v[0] += b._v[0]; _v[3] += b._v[3]; _v[6] += b._v[6];
        _v[1] += b._v[1]; _v[4] += b._v[4]; _v[7] += b._v[7];
        _v[2] += b._v[2]; _v[5] += b._v[5]; _v[8] += b._v[8];
        return *this;
    }

    mat<3,S>& 
    operator-=(const mat<3,S> &b)
    {
        _v[0] -= b._v[0]; _v[3] -= b._v[3]; _v[6] -= b._v[6];
        _v[1] -= b._v[1]; _v[4] -= b._v[4]; _v[7] -= b._v[7];
        _v[2] -= b._v[2]; _v[5] -= b._v[5]; _v[8] -= b._v[8];
        return *this;
    }

    mat<3,S>& 
    operator*=(const S s)
    {
        _v[0] *= s; _v[3] *= s; _v[6] *= s;
        _v[1] *= s; _v[4] *= s; _v[7] *= s;
        _v[2] *= s; _v[5] *= s; _v[8] *= s;
        return *this;
    }

    //! Matrix multiplication.
    mat<3,S>& 
    operator*=(const mat<3,S> &b)
    {	
        const mat<3,S> a(*this);    // Copy.
        _v[0] = a._v[0]*b._v[0] + a._v[3]*b._v[1] + a._v[6]*b._v[2];
        _v[1] = a._v[1]*b._v[0] + a._v[4]*b._v[1] + a._v[7]*b._v[2];
        _v[2] = a._v[2]*b._v[0] + a._v[5]*b._v[1] + a._v[8]*b._v[2];
        _v[3] = a._v[0]*b._v[3] + a._v[3]*b._v[4] + a._v[6]*b._v[5];
        _v[4] = a._v[1]*b._v[3] + a._v[4]*b._v[4] + a._v[7]*b._v[5];
        _v[5] = a._v[2]*b._v[3] + a._v[5]*b._v[4] + a._v[8]*b._v[5];
        _v[6] = a._v[0]*b._v[6] + a._v[3]*b._v[7] + a._v[6]*b._v[8];
        _v[7] = a._v[1]*b._v[6] + a._v[4]*b._v[7] + a._v[7]*b._v[8];
        _v[8] = a._v[2]*b._v[6] + a._v[5]*b._v[7] + a._v[8]*b._v[8];
        return *this;
	}

public:     // Access operators.

    //! Return element at row 'i' and column 'j'. No bounds checking!
    S&
    operator()(const int64 i, const int64 j)
    { return _v[i + dim*j]; }

    //! Return element at row 'i' and column 'j'. No bounds checking!
    S
    operator()(const int64 i, const int64 j) const
    { return _v[i + dim*j]; }

    //! Return i'th element. No bounds checking!
    S&	
    operator[](const int64 i)
    { return _v[i]; }

    //! Return i'th element. No bounds checking!
    S
    operator[](const int64 i) const
    { return _v[i]; }

public:		// Data.

    //! Const data.
    const S* 
    const_data() const
    { return &_v[0]; }

    //! Mutable data.
    S* 
    data()
    { return &_v[0]; }

private:		// Member variables.

    S _v[linear_size];    //!< Data.
};

//------------------------------------------------------------------------------

// mat<4,S>

template<typename S>
class mat<4,S>
{
public:

    typedef S value_type;
    static const int64 dim = 4;
    static const int64 linear_size = dim*dim;

    constexpr mat<4,S>
    identity()
    { return mat<4,S>(1); }

public:

    //! Default CTOR.
    constexpr explicit
    mat(const S v = 1)
        : _v{v, 0, 0, 0, // Col 0.
             0, v, 0, 0, // Col 1.
             0, 0, v, 0, // Col 2.
             0, 0, 0, v} // Col 3.
    {}

    //! Array CTOR - column major.
    constexpr explicit
    mat(const S v[16])
        : _v{v[0],  v[1],  v[2],  v[3],  // Col 0.
             v[4],  v[5],  v[6],  v[7],  // Col 1.
             v[8],  v[9],  v[10], v[11], // Col 2.
             v[12], v[13], v[14], v[15]} // Col 3.
    {}

    //! Value CTOR - column major.
    constexpr explicit
    mat(const S v0, const S v4, const S v8,  const S v12,
        const S v1, const S v5, const S v9,  const S v13,
        const S v2, const S v6, const S v10, const S v14,
        const S v3, const S v7, const S v11, const S v15)
        : _v{v0,  v1,  v2,  v3,  // Col 0.
             v4,  v5,  v6,  v7,  // Col 1.
             v8,  v9,  v10, v11, // Col 2.
             v12, v13, v14, v15} // Col 3.
    {}

public:		// Operators.

    mat<4,S>& 
    operator+=(const mat<4,S> &b)
    {
        _v[0]+=b._v[0]; _v[4]+=b._v[4]; _v[8] +=b._v[8];  _v[12]+=b._v[12];
        _v[1]+=b._v[1]; _v[5]+=b._v[5]; _v[9] +=b._v[9];  _v[13]+=b._v[13];
        _v[2]+=b._v[2]; _v[6]+=b._v[6]; _v[10]+=b._v[10]; _v[14]+=b._v[14];
        _v[3]+=b._v[3]; _v[7]+=b._v[7]; _v[11]+=b._v[11]; _v[15]+=b._v[15];
        return *this;
    }

    mat<4,S>& 
    operator-=(const mat<4,S> &b)
    {
        _v[0]-=b._v[0]; _v[4]-=b._v[4]; _v[8] -=b._v[8];  _v[12]-=b._v[12];
        _v[1]-=b._v[1]; _v[5]-=b._v[5]; _v[9] -=b._v[9];  _v[13]-=b._v[13];
        _v[2]-=b._v[2]; _v[6]-=b._v[6]; _v[10]-=b._v[10]; _v[14]-=b._v[14];
        _v[3]-=b._v[3]; _v[7]-=b._v[7]; _v[11]-=b._v[11]; _v[15]-=b._v[15];
        return *this;
    }

    mat<4,S>& 
    operator*=(const S s)
    {
        _v[0] *= s; _v[4] *= s; _v[8]  *= s; _v[12] *= s;
        _v[1] *= s; _v[5] *= s; _v[9]  *= s; _v[13] *= s;
        _v[2] *= s; _v[6] *= s; _v[10] *= s; _v[14] *= s;
        _v[3] *= s; _v[7] *= s; _v[11] *= s; _v[15] *= s;
        return *this;
    }

    //! Matrix multiplication.
    mat<4,S>&
    operator*=(const mat<4,S> &b)
    {	
        const mat<4,S> a(*this);    // Copy.
        _v[0] =a._v[0]*b._v[0] +a._v[4]*b._v[1] +a._v[8] *b._v[2] +a._v[12]*b._v[3];
        _v[1] =a._v[1]*b._v[0] +a._v[5]*b._v[1] +a._v[9] *b._v[2] +a._v[13]*b._v[3];
        _v[2] =a._v[2]*b._v[0] +a._v[6]*b._v[1] +a._v[10]*b._v[2] +a._v[14]*b._v[3];
        _v[3] =a._v[3]*b._v[0] +a._v[7]*b._v[1] +a._v[11]*b._v[2] +a._v[15]*b._v[3];
        _v[4] =a._v[0]*b._v[4] +a._v[4]*b._v[5] +a._v[8] *b._v[6] +a._v[12]*b._v[7];
        _v[5] =a._v[1]*b._v[4] +a._v[5]*b._v[5] +a._v[9] *b._v[6] +a._v[13]*b._v[7];
        _v[6] =a._v[2]*b._v[4] +a._v[6]*b._v[5] +a._v[10]*b._v[6] +a._v[14]*b._v[7];
        _v[7] =a._v[3]*b._v[4] +a._v[7]*b._v[5] +a._v[11]*b._v[6] +a._v[15]*b._v[7];
        _v[8] =a._v[0]*b._v[8] +a._v[4]*b._v[9] +a._v[8] *b._v[10]+a._v[12]*b._v[11];
        _v[9] =a._v[1]*b._v[8] +a._v[5]*b._v[9] +a._v[9] *b._v[10]+a._v[13]*b._v[11];
        _v[10]=a._v[2]*b._v[8] +a._v[6]*b._v[9] +a._v[10]*b._v[10]+a._v[14]*b._v[11];
        _v[11]=a._v[3]*b._v[8] +a._v[7]*b._v[9] +a._v[11]*b._v[10]+a._v[15]*b._v[11];
        _v[12]=a._v[0]*b._v[12]+a._v[4]*b._v[13]+a._v[8] *b._v[14]+a._v[12]*b._v[15];
        _v[13]=a._v[1]*b._v[12]+a._v[5]*b._v[13]+a._v[9] *b._v[14]+a._v[13]*b._v[15];
        _v[14]=a._v[2]*b._v[12]+a._v[6]*b._v[13]+a._v[10]*b._v[14]+a._v[14]*b._v[15];
        _v[15]=a._v[3]*b._v[12]+a._v[7]*b._v[13]+a._v[11]*b._v[14]+a._v[15]*b._v[15];
        return *this;
    }

public:     // Access operators.

    //! Return element at row 'i' and column 'j'. No bounds checking!
    S&
    operator()(const int64 i, const int64 j)
    { return _v[i + dim*j]; }

    //! Return element at row 'i' and column 'j'. No bounds checking!
    S
    operator()(const int64 i, const int64 j) const
    { return _v[i + dim*j]; }

    //! Return i'th element. No bounds checking!
    S&	
    operator[](const int64 i)
    { return _v[i]; }

    //! Return i'th element. No bounds checking!
    S
    operator[](const int64 i) const
    { return _v[i]; }

public:		// Data.

    //! Const data.
    const S* 
    const_data() const
    { return &_v[0]; }

    //! Mutable data.
    S* 
    data()
    { return &_v[0]; }

private:		// Member variables.

    S _v[linear_size];   //!< Data.
};

//------------------------------------------------------------------------------

// Convenient types, add more if appropriate.

typedef mat<2,float32>	mat2f32;
typedef mat<2,float64>	mat2f64;
typedef mat<2,int8>		mat2i8;
typedef mat<2,int16>	mat2i16;
typedef mat<2,int32>	mat2i32;
typedef mat<2,int64>	mat2i64;
typedef mat<2,uint8>	mat2ui8;
typedef mat<2,uint16>	mat2ui16;
typedef mat<2,uint32>	mat2ui32;
typedef mat<2,uint64>	mat2ui64;

typedef mat<3,float32>	mat3f32;
typedef mat<3,float64>	mat3f64;
typedef mat<3,int8>		mat3i8;
typedef mat<3,int16>	mat3i16;
typedef mat<3,int32>	mat3i32;
typedef mat<3,int64>	mat3i64;
typedef mat<3,uint8>	mat3ui8;
typedef mat<3,uint16>	mat3ui16;
typedef mat<3,uint32>	mat3ui32;
typedef mat<3,uint64>	mat3ui64;

typedef mat<4,float32>	mat4f32;
typedef mat<4,float64>	mat4f64;
typedef mat<4,int8>		mat4i8;
typedef mat<4,int16>	mat4i16;
typedef mat<4,int32>	mat4i32;
typedef mat<4,int64>	mat4i64;
typedef mat<4,uint8>	mat4ui8;
typedef mat<4,uint16>	mat4ui16;
typedef mat<4,uint32>	mat4ui32;
typedef mat<4,uint64>	mat4ui64;

}	// Namespace: thx.

//------------------------------------------------------------------------------

namespace std
{

//! Binary operator: std::ostream << mat<N,S>
template<thx::int64 N, typename S>
ostream&
operator<<(ostream &os, const thx::mat<N,S> &rhs)
{
    for(thx::int64 i = 0; i < N; ++i) {
        os	<< "[";
        for (thx::int64 j = 0; j < N; ++j) {
            os << rhs(i,j) << (j != (N - 1) ? ", " : "");
        }
        os << "]\n";
    }
    //os.flags(f0);
    return os;
}

}	// Namespace: std.

//------------------------------------------------------------------------------

#endif	// THX_MAT_HPP_INCLUDED
