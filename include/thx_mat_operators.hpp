//------------------------------------------------------------------------------
//
// Contributors: 
//             1) Tommy Hinks
//
//------------------------------------------------------------------------------

#ifndef THX_MAT_OPERATORS_HPP_INCLUDED
#define THX_MAT_OPERATORS_HPP_INCLUDED

#include "thx_mat.hpp"

//------------------------------------------------------------------------------

namespace thx 
{

// Binary operator: mat == mat

template<int64 C, int64 R, typename S>
bool
operator==(const mat<C,R,S> &a, const mat<C,R,S> &b)
{
	const S *pa(a[0]);
	const S *pb(b[0]);

	bool t(pa[0] == pb[0]);
	int64 i(1);
	while (i < (C*R) && t) {
		t = (t && (pa[i] == pb[i])); 
		++i;
	}
	return t;
}

template<typename S>
bool 
operator==(const mat<2,2,S> &a, const mat<2,2,S> &b)
{
	return (a[0][0] == b[0][0] &&  
			a[0][1] == b[0][1] &&  
			a[1][0] == b[1][0] &&
			a[1][1] == b[1][1]);
}

template<typename S>
bool 
operator==(const mat<3,3,S> &a, const mat<3,3,S> &b)
{
	return (a[0][0] == b[0][0] &&  
			a[0][1] == b[0][1] &&  
			a[0][2] == b[0][2] &&  
			a[1][0] == b[1][0] &&
			a[1][1] == b[1][1] &&
			a[1][2] == b[1][2] &&
			a[2][0] == b[2][0] &&
			a[2][1] == b[2][1] &&
			a[2][2] == b[2][2]);
}

template<typename S>
bool 
operator==(const mat<4,4,S> &a, const mat<4,4,S> &b)
{
	return (a[0][0] == b[0][0] &&  
			a[0][1] == b[0][1] &&  
			a[0][2] == b[0][2] &&
			a[0][3] == b[0][3] &&
			a[1][0] == b[1][0] &&
			a[1][1] == b[1][1] &&
			a[1][2] == b[1][2] &&
			a[1][3] == b[1][3] &&
			a[2][0] == b[2][0] &&
			a[2][1] == b[2][1] &&
			a[2][2] == b[2][2] &&
			a[2][3] == b[2][3] &&
			a[3][0] == b[3][0] &&
			a[3][1] == b[3][1] &&
			a[3][2] == b[3][2] &&
			a[3][3] == b[3][3]);
}

//------------------------------------------------------------------------------

// Binary operator: mat != mat

template<int64 C, int64 R, typename S>
bool
operator!=(const mat<C,R,S> &a, const mat<C,R,S> &b)
{
	const S *pa(a[0]);
	const S *pb(b[0]);

	bool t(pa[0] != pb[0]);
	int64 i(1);
	while (i < (C*R) && !t) {
		t = (t && (pa[i] != pb[i])); 
		++i;
	}
	return t;
}

template<typename S>
bool 
operator!=(const mat<2,2,S> &a, const mat<2,2,S> &b)
{
	return !(a == b);
}

template<typename S>
bool 
operator!=(const mat<3,3,S> &a, const mat<3,3,S> &b)
{
	return !(a == b);
}

template<typename S>
bool 
operator!=(const mat<4,4,S> &a, const mat<4,4,S> &b)
{
	return !(a == b);
}

//------------------------------------------------------------------------------

// Binary operator: mat + mat
 
template<int64 C, int64 R, typename S>
bool
operator+(const mat<C,R,S> &a, const mat<C,R,S> &b)
{
	const S *pa(a[0]);
	const S *pb(b[0]);
    mat<C,R,S> c;
    S* pc(c[0]);

    for (int i(0); i < (C*R); ++i) {
        pc[i] = pa[i] + pb[i];
    }
    return c;
}

template<typename S> 
mat<2,2,S> 
operator+(const mat<2,2,S> &a, const mat<2,2,S> &b)
{
	return mat<2,2,S>(
        a[0][0] + b[0][0], a[1][0] + b[1][0],
		a[0][1] + b[0][1], a[1][1] + b[1][1]);
}

template<typename S>
mat<3,3,S> 
operator+(const mat<3,3,S> &a, const mat<3,3,S> &b)
{
	return mat<3,3,S>(
	    a[0][0] + b[0][0], a[1][0] + b[1][0], a[2][0] + b[2][0], 
	    a[0][1] + b[0][1], a[1][1] + b[1][1], a[2][1] + b[2][1], 
	    a[0][2] + b[0][2], a[1][2] + b[1][2], a[2][2] + b[2][2]);
}

template<typename S>
mat<4,4,S> 
operator+(const mat<4,4,S> &a, const mat<4,4,S,T> &b)
{
	return mat<4,4,S>(
        a[0][0]+b[0][0], a[1][0]+b[1][0], a[2][0]+b[2][0], a[3][0]+b[3][0], 
        a[0][1]+b[0][1], a[1][1]+b[1][1], a[2][1]+b[2][1], a[3][1]+b[3][1], 
        a[0][2]+b[0][2], a[1][2]+b[1][2], a[2][2]+b[2][2], a[3][2]+b[3][2], 
        a[0][3]+b[0][3], a[1][3]+b[1][3], a[2][3]+b[2][3], a[3][3]+b[3][3]);
}

//------------------------------------------------------------------------------

// Binary operator: mat - mat

template<int64 C, int64 R, typename S>
bool
operator+(const mat<C,R,S> &a, const mat<C,R,S> &b)
{
	const S *pa(a[0]);
	const S *pb(b[0]);
    mat<C,R,S> c;
    S* pc(c[0]);

    for (int i(0); i < (C*R); ++i) {
        pc[i] = pa[i] - pb[i];
    }
    return c;
}

template<typename S>
mat<2,2,S> 
operator-(const mat<2,2,S> &a, const mat<2,2,S> &b)
{
	return mat<2,2,S>(
        a[0][0] - b[0][0], a[1][0] - b[1][0],
		a[0][1] - b[0][1], a[1][1] - b[1][1]);
}

template<typename S>
mat<3,3,S> 
operator-(const mat<3,3,S> &a, const mat<3,3,S> &b)
{
	return mat<3,3,S>(
		a[0][0] - b[0][0], a[1][0] - b[1][0], a[2][0] - b[2][0], 
		a[0][1] - b[0][1], a[1][1] - b[1][1], a[2][1] - b[2][1], 
		a[0][2] - b[0][2], a[1][2] - b[1][2], a[2][2] - b[2][2]);
}

template<typename S>
mat<4,4,S> 
operator-(const mat<4,4,S> &a, const mat<4,4,S> &b)
{
	return mat<4,4,S,T>(
		a[0][0]-b[0][0], a[1][0]-b[1][0], a[2][0]-b[2][0], a[3][0]-b[3][0], 
		a[0][1]-b[0][1], a[1][1]-b[1][1], a[2][1]-b[2][1], a[3][1]-b[3][1], 
		a[0][2]-b[0][2], a[1][2]-b[1][2], a[2][2]-b[2][2], a[3][2]-b[3][2], 
		a[0][3]-b[0][3], a[1][3]-b[1][3], a[2][3]-b[2][3], a[3][3]-b[3][3]);
}

//------------------------------------------------------------------------------

// Binary operator: scalar * mat

template<int64 C, int64 R, typename S>
bool
operator*(const S a, const mat<C,R,S> &b)
{
	const S *pb(b[0]);
    mat<C,R,S> c;
    S* pc(c[0]);

    for (int i(0); i < (C*R); ++i) {
        pc[i] = a*pb[i];
    }
    return c;
}

template<typename S>
mat<2,2,S> 
operator*(const S a, const mat<2,2,S> &b)
{
	return mat<2,2,S>(
        a*b[0][0], a*b[1][0], 
		a*b[0][1], a*b[1][1]);
}

template<typename S>
mat<3,3,S> 
operator*(const S a, const mat<3,3,S> &b)
{
	return mat<3,3,S>(
		a*b[0][0], a*b[1][0], a*b[2][0], 
		a*b[0][1], a*b[1][1], a*b[2][1], 
		a*b[0][2], a*b[1][2], a*b[2][2]);
}

template<typename S>
mat<4,4,S> 
operator*(const S a, const mat<4,4,S> &b)
{
	return mat<4,4,S>(
		a*b[0][0], a*b[1][0], a*b[2][0], a*b[3][0], 
		a*b[0][1], a*b[1][1], a*b[2][1], a*b[3][1], 
		a*b[0][2], a*b[1][2], a*b[2][2], a*b[3][2], 
		a*b[0][3], a*b[1][3], a*b[2][3], a*b[3][3]);
}

//------------------------------------------------------------------------------

// Binary operator: mat * scalar

template<int64 C, int64 R, typename S>
bool
operator*(const mat<C,R,S> &a, const S b)
{ return b*a; }

template<typename S>
mat<2,2,S> 
operator*(const mat<2,2,S> &a, const S b)
{ return b*a; }

template<typename S>
mat<3,3,S> 
operator*(const mat<3,3,S> &a, const S b)
{ return b*a; }

template<typename S>
mat<4,4,S> 
operator*(const mat<4,4,S> &a, const S b)
{ return b*a; }

//------------------------------------------------------------------------------

// Binary operator: mat * mat

// TODO: <C,R,S>

template<typename S>
mat<2,2,S> 
operator*(const mat<2,2,S> &a, const mat<2,2,S> &b)
{	
	return mat<2,2,S>(
		a[0][0]*b[0][0] + a[1][0]*b[0][1], a[0][0]*b[1][0] + a[1][0]*b[1][1],
		a[0][1]*b[0][0] + a[1][1]*b[0][1], a[0][1]*b[1][0] + a[1][1]*b[1][1]);
}

template<typename S>
mat<3,3,S> 
operator*(const mat<3,3,S> &a, const mat<3,3,S> &b)
{	
	return mat<3,3,S,T>(
		a[0][0]*b[0][0] + a[1][0]*b[0][1] + a[2][0]*b[0][2],
		a[0][0]*b[1][0] + a[1][0]*b[1][1] + a[2][0]*b[1][2], 
		a[0][0]*b[2][0] + a[1][0]*b[2][1] + a[2][0]*b[2][2],
		a[0][1]*b[0][0] + a[1][1]*b[0][1] + a[2][1]*b[0][2],
		a[0][1]*b[1][0] + a[1][1]*b[1][1] + a[2][1]*b[1][2], 
		a[0][1]*b[2][0] + a[1][1]*b[2][1] + a[2][1]*b[2][2],
		a[0][2]*b[0][0] + a[1][2]*b[0][1] + a[2][2]*b[0][2],
		a[0][2]*b[1][0] + a[1][2]*b[1][1] + a[2][2]*b[1][2], 
		a[0][2]*b[2][0] + a[1][2]*b[2][1] + a[2][2]*b[2][2]);
}

template<typename S>
mat<4,4,S> 
operator*(const mat<4,4,S> &a, const mat<4,4,S> &b)
{	
	return mat<4,4,S,T>(
        a[0][0]*b[0][0] + a[1][0]*b[0][1] + a[2][0]*b[0][2] + a[3][0]*b[0][3],
        a[0][0]*b[1][0] + a[1][0]*b[1][1] + a[2][0]*b[1][2] + a[3][0]*b[1][3],
        a[0][0]*b[2][0] + a[1][0]*b[2][1] + a[2][0]*b[2][2] + a[3][0]*b[2][3],
        a[0][0]*b[3][0] + a[1][0]*b[3][1] + a[2][0]*b[3][2] + a[3][0]*b[3][3],
        a[0][1]*b[0][0] + a[1][1]*b[0][1] + a[2][1]*b[0][2] + a[3][1]*b[0][3],
        a[0][1]*b[1][0] + a[1][1]*b[1][1] + a[2][1]*b[1][2] + a[3][1]*b[1][3],
        a[0][1]*b[2][0] + a[1][1]*b[2][1] + a[2][1]*b[2][2] + a[3][1]*b[2][3],
        a[0][1]*b[3][0] + a[1][1]*b[3][1] + a[2][1]*b[3][2] + a[3][1]*b[3][3],
        a[0][2]*b[0][0] + a[1][2]*b[0][1] + a[2][2]*b[0][2] + a[3][2]*b[0][3],
        a[0][2]*b[1][0] + a[1][2]*b[1][1] + a[2][2]*b[1][2] + a[3][2]*b[1][3],
        a[0][2]*b[2][0] + a[1][2]*b[2][1] + a[2][2]*b[2][2] + a[3][2]*b[2][3],
        a[0][2]*b[3][0] + a[1][2]*b[3][1] + a[2][2]*b[3][2] + a[3][2]*b[3][3],
        a[0][3]*b[0][0] + a[1][3]*b[0][1] + a[2][3]*b[0][2] + a[3][3]*b[0][3],
        a[0][3]*b[1][0] + a[1][3]*b[1][1] + a[2][3]*b[1][2] + a[3][3]*b[1][3],
        a[0][3]*b[2][0] + a[1][3]*b[2][1] + a[2][3]*b[2][2] + a[3][3]*b[2][3],
        a[0][3]*b[3][0] + a[1][3]*b[3][1] + a[2][3]*b[3][2] + a[3][3]*b[3][3]);
}

//------------------------------------------------------------------------------

// Binary operator: mat * vec

// TODO: <C,R,S>

template<typename S>
vec<2,S> 
operator*(const mat<2,2,S> &a, const vec<2,S> &b)
{	
    return vec<2,S>(a[0][0]*b[0] + a[1][0]*b[1], a[0][1]*b[0] + a[1][1]*b[1]);
}

template<typename S>
vec<3,S> 
operator*(const mat<3,3,S> &a, const vec<3,S> &b)
{	
	return vec<3,S,T>(
        a[0][0]*b[0] + a[1][0]*b[1] + a[2][0]*b[2], 
        a[0][1]*b[0] + a[1][1]*b[1] + a[2][1]*b[2],
        a[0][2]*b[0] + a[1][2]*b[1] + a[2][2]*b[2]);
}

template<typename S>
vec<4,S> 
operator*(const mat<4,4,S> &a, const vec<4,S> &b)
{	
    return vec<4,S,T>(
        a[0][0]*b[0] + a[1][0]*b[1] + a[2][0]*b[2] + a[3][0]*b[3], 
        a[0][1]*b[0] + a[1][1]*b[1] + a[2][1]*b[2] + a[3][1]*b[3],
        a[0][2]*b[0] + a[1][2]*b[1] + a[2][2]*b[2] + a[3][2]*b[3],
        a[0][3]*b[0] + a[1][3]*b[1] + a[2][3]*b[2] + a[3][3]*b[3]);
}

//------------------------------------------------------------------------------

// Binary operator: vec * mat

// TODO: <C,R,S>

template<typename S>
vec<2,S> 
operator*(const vec<2,S> &a, const mat<2,2,S> &b)
{	
    return vec<2,S>(a[0]*b[0][0] + a[1]*b[0][1], a[0]*b[1][0] + a[1]*b[1][1]);
}

template<typename S>
vec<3,S> 
operator*(const vec<3,S> &a, const mat<3,3,S> &b)
{	
	return vec<3,S,T>(
        a[0]*b[0][0] + a[1]*b[0][1] + a[2]*b[0][2],
        a[0]*b[1][0] + a[1]*b[1][1] + a[2]*b[1][2],
        a[0]*b[2][0] + a[1]*b[2][1] + a[2]*b[2][2]);
}

template<typename S, class T>
vec<4,S,T> 
operator*(const vec<4,S,T>& a, const mat<4,4,S,T>& b)
{	
    return vec<4,S,T>(
		a[0]*b[0][0] + a[1]*b[0][1] + a[2]*b[0][2] + a[3]*b[0][3],
		a[0]*b[1][0] + a[1]*b[1][1] + a[2]*b[1][2] + a[3]*b[1][3],
		a[0]*b[2][0] + a[1]*b[2][1] + a[2]*b[2][2] + a[3]*b[2][3],
		a[0]*b[3][0] + a[1]*b[3][1] + a[2]*b[3][2] + a[3]*b[3][3]);
}

}	// Namespace: thx.

#endif	// THX_MAT_OPERATORS_HPP_INCLUDED
