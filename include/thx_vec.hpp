//------------------------------------------------------------------------------
//
// Contributors: 
//             1) Tommy Hinks
//
//------------------------------------------------------------------------------

#ifndef THX_VEC_HPP_INCLUDED
#define THX_VEC_HPP_INCLUDED

#include "thx_namespace.hpp"
#include "thx_arithmetic_type.hpp"
#include "thx_define.hpp"
#include "thx_types.hpp"

//------------------------------------------------------------------------------

BEGIN_THX_NAMESPACE

// vec<N,S> anatomy:
// -----------------
//
// typedef arithmetic_type<S>::value value_type;
// typedef std::size_t size_type;
// typedef value_type& reference;
// typedef const value_type& const_reference;   
// typedef value_type* pointer;
// typedef const value_type* const_pointer;   
//
// define linear_size = N
// define dim = N
// 
// Default constexpr (specializations only) CTOR (set all zeros by default)
// Array constexpr CTOR (specializations only)
// Value constexpr CTOR (specializations only)
// (All vec's have compiler-generated DTOR)
// (All vec's have compiler-generated copy CTOR)
// (All vec's have compiler-generated operator=)
//
// operator+=(vec<N,S>)
// operator-=(vec<N,S>)
// operator*=(scalar)
//
// const_reference  operator[size_type] const
// reference operator[size_type]
//
// const_pointer const_data() const
// pointer data()

//------------------------------------------------------------------------------


//! DOCS
template<std::size_t N, typename S>
class vec
{
private:

  // TODO: find replacement!
  static_assert(N > 4, "vector dimension must be > 4"); 

public:

  typedef typename arithmetic_type<S>::value value_type;
  typedef std::size_t size_type;
  typedef value_type& reference;
  typedef const value_type& const_reference;   
  typedef value_type* pointer;
  typedef const value_type* const_pointer;   

  static const size_type linear_size = N;
  static const size_type dim = N;

public: // CTOR's.

  // Copy CTOR and DTOR implicitly defined.

  //! Default CTOR.
  explicit 
  vec(const value_type x = 0)
  { 
    for (size_type i = 0; i < linear_size; ++i) { 
      _v[i] = x; 
    }
  }

  //! Array CTOR.
  explicit 
  vec(const_pointer v)
  { 
    for (size_type i = 0; i < linear_size; ++i) { 
      _v[i] = v[i]; 
    }
  }		

public:		// Operators.

  //! DOCS
  vec<linear_size,value_type>& 
  operator+=(const vec<linear_size,value_type> &u)
  {
    for (size_type i = 0; i < linear_size; ++i) { 
      _v[i] += u[i]; 
    }
    return *this;
  }

  //! DOCS
  vec<linear_size,value_type>& 
  operator-=(const vec<linear_size,value_type> &u)
  {
    for (size_type i = 0; i < linear_size; ++i) { 
      _v[i] -= u[i]; 
    }
    return *this;
  }

  //! Scalar multiplication.
  vec<linear_size,value_type>& 
  operator*=(const value_type x)
  {
    for (size_type i = 0; i < linear_size; ++i) { 
      _v[i] *= x; 
    }
    return *this;
  }

public:     // Access operators.

  //! Return i'th component. No bounds checking!
  const_reference 
  operator[](const size_type i) const
  { 
    return _v[i];	
  }

  //! Return i'th component. No bounds checking!
  reference 
  operator[](const size_type i)
  { 
    return _v[i];	
  }

public:		// Data.

  //! Const data.
  const_pointer
  const_data() const
  { 
    return &_v[0]; 
  }

  //! Mutable data.
  pointer 
  data()
  { 
    return &_v[0]; 
  }

private:	    // Member variables.

  value_type _v[linear_size];    //!< Data.
};

//------------------------------------------------------------------------------

//! DOCS
template<typename S>
class vec<2,S>
{
public:

  typedef typename arithmetic_type<S>::value value_type;
  typedef std::size_t size_type;
  typedef value_type& reference;
  typedef const value_type& const_reference;   
  typedef value_type* pointer;
  typedef const value_type* const_pointer;   

  static const size_type linear_size = 2;
  static const size_type dim = 2;

public: // CTOR's.

  //! Default CTOR.
  explicit THX_CONST_EXPR 
  vec(const value_type x = 0) 
#if 0 // C++11
    : _v{x, x}
#endif
  {
    _v[0] = x; 
    _v[1] = x;
  }	
  
  //! Array CTOR.
  explicit THX_CONST_EXPR 
  vec(const_pointer v)
#if 0 // C++11
    : _v{v[0], v[1]}
#endif
  {
    _v[0] = v[0];
    _v[1] = v[1];
  }		

  //! Value CTOR.
  explicit THX_CONST_EXPR
  vec(const value_type v0, const value_type v1)
#if 0 // C++11
    : _v{v0, v1}
#endif
  {
    _v[0] = v0;
    _v[1] = v1;
  }

public: // Operators.

  //! DOCS
  vec<linear_size,value_type>& 
  operator+=(const vec<linear_size,value_type> &u)
  {
    _v[0] += u._v[0]; 
    _v[1] += u._v[1];
    return *this;
  }

  //! DOCS
  vec<linear_size,value_type>& 
  operator-=(const vec<linear_size,value_type> &u)
  {
    _v[0] -= u._v[0]; 
    _v[1] -= u._v[1];
    return *this;
  }

  //! Scalar multiplication.
  vec<linear_size,value_type>& 
  operator*=(const S x)
  {
    _v[0] *= x; 
    _v[1] *= x;
    return *this;
  }

public: // Access operators.

  //! Return i'th component. No bounds checking!
  const_reference
  operator[](const size_type i) const
  { 
    return _v[i];	
  }

  //! Return i'th component. No bounds checking!
  reference
  operator[](const size_type i)
  { 
    return _v[i];	
  }

public:		// Data.

  //! Const data.
  const_pointer 
  const_data() const
  { 
    return &_v[0]; 
  }

  //! Mutable data.
  pointer
  data()
  { 
    return &_v[0]; 
  }

private:  // Member variables.

  value_type _v[linear_size];    //!< Data.
};

//------------------------------------------------------------------------------

//! DOCS
template<typename S>
class vec<3,S>
{
public:

  typedef typename arithmetic_type<S>::value value_type;
  typedef std::size_t size_type;
  typedef value_type& reference;
  typedef const value_type& const_reference;   
  typedef value_type* pointer;
  typedef const value_type* const_pointer;   

  static const size_type linear_size = 3;
  static const size_type dim = 3;

public: // CTOR's.

  //! Default CTOR.
  explicit THX_CONST_EXPR
  vec(const value_type x = 0) 
#if 0 // C++11
    : _v{x, x, x}
#endif
  {
    _v[0] = x;
    _v[1] = x;
    _v[2] = x;
  }	
  
  //! Array CTOR.
  explicit THX_CONST_EXPR
  vec(const_pointer v)
#if 0 // C++11
    : _v{v[0], v[1], v[2]}
#endif
  {
    _v[0] = v[0];
    _v[1] = v[1];
    _v[2] = v[2];
  }

  //! Value CTOR.
  explicit THX_CONST_EXPR
  vec(const value_type v0, const value_type v1, const value_type v2)
#if 0 // C++11
    : _v{v0, v1, v2}
#endif
  {
    _v[0] = v0;
    _v[1] = v1;
    _v[2] = v2;
  }

public: // Operators.

  //! DOCS
  vec<linear_size,value_type>& 
  operator+=(const vec<linear_size,value_type> &u)
  {
    _v[0] += u._v[0]; 
    _v[1] += u._v[1]; 
    _v[2] += u._v[2];
    return *this;
  }

  //! DOCS
  vec<linear_size,value_type>& 
  operator-=(const vec<linear_size,value_type> &u)
  {
    _v[0] -= u._v[0]; 
    _v[1] -= u._v[1]; 
    _v[2] -= u._v[2];
    return *this;
  }

  //! Scalar multiplication.
  vec<linear_size,value_type>& 
  operator*=(const value_type x)
  {
    _v[0] *= x; 
    _v[1] *= x; 
    _v[2] *= x;
    return *this;
  }

public: // Access operators.

  //! Return i'th component. No bounds checking!
  const_reference
  operator[](const size_type i) const
  { 
    return _v[i];	
  }

  //! Return i'th component. No bounds checking!
  reference 
  operator[](const size_type i)
  { 
    return _v[i];	
  }

public: // Data.

  //! Const data.
  const_pointer 
  const_data() const
  { 
    return &_v[0]; 
  }

  //! Mutable data.
  pointer 
  data()
  { 
    return &_v[0]; 
  }

private:  // Member variables.

  value_type _v[linear_size];    //!< Data.
};

//------------------------------------------------------------------------------

//! DOCS
template<typename S>
class vec<4,S>
{
public:

  typedef typename arithmetic_type<S>::value value_type;
  typedef std::size_t size_type;
  typedef value_type& reference;
  typedef const value_type& const_reference;   
  typedef value_type* pointer;
  typedef const value_type* const_pointer;   

  static const size_type linear_size = 4;
  static const size_type dim = 4;

public: // CTOR's.

  //! Default CTOR.
  explicit THX_CONST_EXPR
  vec(const value_type x = 0)
#if 0 // C++11
    : _v{x, x, x, x}
#endif
  {
      _v[0] = x; 
      _v[1] = x; 
      _v[2] = x; 
      _v[3] = x; 
  }	
  
  //! Array CTOR.
  explicit THX_CONST_EXPR 
  vec(const_pointer v)
#if 0 // C++11
    : _v{v[0], v[1], v[2], v[3]}
#endif
  {
      _v[0] = v[0]; 
      _v[1] = v[1]; 
      _v[2] = v[2]; 
      _v[3] = v[3]; 
  }		

  //! Value CTOR.
  explicit THX_CONST_EXPR
  vec(const value_type v0, 
      const value_type v1, 
      const value_type v2, 
      const value_type v3)
#if 0 // C++11
    : _v{v0, v1, v2, v3}
#endif
  {
      _v[0] = v0; 
      _v[1] = v1; 
      _v[2] = v2; 
      _v[3] = v3; 
  }

public: // Operators.

  //! DOCS
  vec<linear_size,value_type>& 
  operator+=(const vec<linear_size,value_type> &u)
  {
    _v[0] += u._v[0]; 
    _v[1] += u._v[1]; 
    _v[2] += u._v[2]; 
    _v[3] += u._v[3];
    return *this;
  }

  //! DOCS
  vec<linear_size,value_type>& 
  operator-=(const vec<linear_size,value_type> &u)
  {
    _v[0] -= u._v[0]; 
    _v[1] -= u._v[1]; 
    _v[2] -= u._v[2]; 
    _v[3] -= u._v[3];
    return *this;
  }

  //! Scalar multiplication.
  vec<linear_size,value_type>& 
  operator*=(const S x)
  {
    _v[0] *= x; 
    _v[1] *= x; 
    _v[2] *= x; 
    _v[3] *= x;
    return *this;
  }

public: // Access operators.

  //! Return i'th component. No bounds checking!
  const_reference
  operator[](const size_type i) const
  { 
    return _v[i];	
  }

  //! Return i'th component. No bounds checking!
  reference 
  operator[](const size_type i)
  { 
    return _v[i];	
  }

public: // Data.

  //! Const data.
  const_pointer 
  const_data() const
  { 
    return &_v[0]; 
  }

  //! Mutable data.
  pointer 
  data()
  { 
    return &_v[0]; 
  }

private:  // Member variables.

  value_type _v[linear_size];    //!< Data.
};

//------------------------------------------------------------------------------

// Convenient types, add more if appropriate.

typedef vec<2,float32>  vec2f32;
typedef vec<2,float64>  vec2f64;
typedef vec<2,int8>     vec2i8;
typedef vec<2,int16>    vec2i16;
typedef vec<2,int32>    vec2i32;
typedef vec<2,int64>    vec2i64;
typedef vec<2,uint8>    vec2ui8;
typedef vec<2,uint16>   vec2ui16;
typedef vec<2,uint32>   vec2ui32;
typedef vec<2,uint64>   vec2ui64;

typedef vec<3,float32>  vec3f32;
typedef vec<3,float64>  vec3f64;
typedef vec<3,int8>     vec3i8;
typedef vec<3,int16>    vec3i16;
typedef vec<3,int32>    vec3i32;
typedef vec<3,int64>    vec3i64;
typedef vec<3,uint8>    vec3ui8;
typedef vec<3,uint16>   vec3ui16;
typedef vec<3,uint32>   vec3ui32;
typedef vec<3,uint64>   vec3ui64;

typedef vec<4,float32>  vec4f32;
typedef vec<4,float64>  vec4f64;
typedef vec<4,int8>     vec4i8;
typedef vec<4,int16>    vec4i16;
typedef vec<4,int32>    vec4i32;
typedef vec<4,int64>    vec4i64;
typedef vec<4,uint8>    vec4ui8;
typedef vec<4,uint16>   vec4ui16;
typedef vec<4,uint32>   vec4ui32;
typedef vec<4,uint64>   vec4ui64;

END_THX_NAMESPACE

#endif	// THX_VEC_HPP_INCLUDED
