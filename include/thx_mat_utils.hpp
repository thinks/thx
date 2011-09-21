//==============================================================================
// Contributors: 
//             1) Tommy Hinks
//==============================================================================

#ifndef THX_MAT_UTILS_HPP_INCLUDED
#define THX_MAT_UTILS_HPP_INCLUDED

#include "thx_mat.hpp"
#include "thx_vec.hpp"
#include "thx_utils.hpp"
#include <cassert>


namespace thx
{
//==============================================================================

// Function declarations.

template<typename S, class T> S determinant(const mat<2,2,S,T>& m);
template<typename S, class T> S determinant(const mat<3,3,S,T>& m);
template<typename S, class T> S determinant(const mat<4,4,S,T>& m);

template<typename S, class T> void transpose(mat<2,2,S,T>* m);
template<typename S, class T> void transpose(mat<3,3,S,T>* m);
template<typename S, class T> void transpose(mat<4,4,S,T>* m);

template<typename S, class T> mat<2,2,S,T> transposed(const mat<2,2,S,T>& m);
template<typename S, class T> mat<3,3,S,T> transposed(const mat<3,3,S,T>& m);
template<typename S, class T> mat<4,4,S,T> transposed(const mat<4,4,S,T>& m);

template<typename S, class T> void invert(mat<2,2,S,T>* m);
template<typename S, class T> void invert(mat<3,3,S,T>* m);
template<typename S, class T> void invert(mat<4,4,S,T>* m);

template<typename S, class T> mat<2,2,S,T> inverted(const mat<2,2,S,T>& m);
template<typename S, class T> mat<3,3,S,T> inverted(const mat<3,3,S,T>& m);
template<typename S, class T> mat<4,4,S,T> inverted(const mat<4,4,S,T>& m);

//==============================================================================

// Operator declarations.

// Binary operator==
template<typename S, class T>
bool operator==(const mat<2,2,S,T>& lhs, const mat<2,2,S,T>& rhs);
template<typename S, class T>
bool operator==(const mat<3,3,S,T>& lhs, const mat<3,3,S,T>& rhs);
template<typename S, class T>
bool operator==(const mat<4,4,S,T>& lhs, const mat<4,4,S,T>& rhs);
//template<unsigned int C, unsigned int R, typename S, class T> 
//bool operator==(const mat<C,R,S,T>& lhs, const mat<C,R,S,T>& rhs);

// Binary operator!=
template<typename S, class T>
bool operator!=(const mat<2,2,S,T>& lhs, const mat<2,2,S,T>& rhs);
template<typename S, class T>
bool operator!=(const mat<3,3,S,T>& lhs, const mat<3,3,S,T>& rhs);
template<typename S, class T>
bool operator!=(const mat<4,4,S,T>& lhs, const mat<4,4,S,T>& rhs);
//template<unsigned int C, unsigned int R, typename S, class T> 
//bool operator!=(const mat<C,R,S,T>& lhs, const mat<C,R,S,T>& rhs);

// Binary operator+
template<typename S, class T>
mat<2,2,S,T> operator+(const mat<2,2,S,T>& lhs, const mat<2,2,S,T>& rhs);
template<typename S, class T>
mat<3,3,S,T> operator+(const mat<3,3,S,T>& lhs, const mat<3,3,S,T>& rhs);
template<typename S, class T>
mat<4,4,S,T> operator+(const mat<4,4,S,T>& lhs, const mat<4,4,S,T>& rhs);
//template<unsigned int C, unsigned int R, typename S, class T> 
//mat<C,R,S,T> operator+(const mat<C,R,S,T>& lhs, const mat<C,R,S,T>& rhs);

// Binary operator-
template<typename S, class T>
mat<2,2,S,T> operator-(const mat<2,2,S,T>& lhs, const mat<2,2,S,T>& rhs);
template<typename S, class T>
mat<3,3,S,T> operator-(const mat<3,3,S,T>& lhs, const mat<3,3,S,T>& rhs);
template<typename S, class T>
mat<4,4,S,T> operator-(const mat<4,4,S,T>& lhs, const mat<4,4,S,T>& rhs);
//template<unsigned int C, unsigned int R, typename S, class T> 
//mat<C,R,S,T> operator-(const mat<C,R,S,T>& lhs, const mat<C,R,S,T>& rhs);

// Binary operator*(scalar, mat)
template<typename S, class T>
mat<2,2,S,T> operator*(const S lhs, const mat<2,2,S,T>& rhs);
template<typename S, class T>
mat<3,3,S,T> operator*(const S lhs, const mat<3,3,S,T>& rhs);
template<typename S, class T>
mat<4,4,S,T> operator*(const S lhs, const mat<4,4,S,T>& rhs);
//template<unsigned int C, unsigned int R, typename S, class T> 
//mat<C,R,S,T> operator*(const S lhs, const mat<C,R,S,T>& rhs);

// Binary operator*(mat, scalar)
template<typename S, class T>
mat<2,2,S,T> operator*(const mat<2,2,S,T>& lhs, const S rhs);
template<typename S, class T>
mat<3,3,S,T> operator*(const mat<3,3,S,T>& lhs, const S rhs);
template<typename S, class T>
mat<4,4,S,T> operator*(const mat<4,4,S,T>& lhs, const S rhs);
//template<unsigned int C, unsigned int R, typename S, class T> 
//mat<C,R,S,T> operator*(const mat<C,R,S,T>& lhs, const S rhs);

// Binary operator*(mat, mat)
template<typename S, class T>
mat<2,2,S,T> operator*(const mat<2,2,S,T>& lhs, const mat<2,2,S,T>& rhs);
template<typename S, class T>
mat<3,3,S,T> operator*(const mat<3,3,S,T>& lhs, const mat<3,3,S,T>& rhs);
template<typename S, class T>
mat<4,4,S,T> operator*(const mat<4,4,S,T>& lhs, const mat<4,4,S,T>& rhs);
//template<unsigned int C, unsigned int R, typename S, class T> 
//mat<C,R,S,T> operator*(const mat<C,R,S,T>& lhs, const mat<C,R,S,T>& rhs);

// Binary operator*(mat, vec)
template<typename S, class T>
vec<2,S,T> operator*(const mat<2,2,S,T>& lhs, const vec<2,S,T>& rhs);
template<typename S, class T>
vec<3,S,T> operator*(const mat<3,3,S,T>& lhs, const vec<3,S,T>& rhs);
template<typename S, class T>
vec<4,S,T> operator*(const mat<4,4,S,T>& lhs, const vec<4,S,T>& rhs);
template<typename S, class T>
vec<3,S,T> operator*(const mat<4,4,S,T>& lhs, const vec<3,S,T>& rhs);
//template<unsigned int C, unsigned int R, typename S, class T> 
//vec<C,S,T> operator*(const mat<C,R,S,T>& lhs, const vec<C,S,T>& rhs);

// Binary operator*(vec, mat)
template<typename S, class T>
vec<2,S,T> operator*(const vec<2,S,T>& lhs, const mat<2,2,S,T>& rhs);
template<typename S, class T>
vec<3,S,T> operator*(const vec<3,S,T>& lhs, const mat<3,3,S,T>& rhs);
template<typename S, class T>
vec<4,S,T> operator*(const vec<4,S,T>& lhs, const mat<4,4,S,T>& rhs);
//template<unsigned int C, unsigned int R, typename S, class T> 
//mat<C,R,S,T> operator*(const mat<C,R,S,T>& lhs, const vec<C,S,T>& rhs);

// Binary operator/(mat, scalar)
template<typename S, class T>
mat<2,2,S,T> operator/(const mat<2,2,S,T>& lhs, const S rhs);
template<typename S, class T>
mat<3,3,S,T> operator/(const mat<3,3,S,T>& lhs, const S rhs);
template<typename S, class T>
mat<4,4,S,T> operator/(const mat<4,4,S,T>& lhs, const S rhs);
//template<unsigned int C, unsigned int R, typename S, class T> 
//mat<C,R,S,T> operator/(const mat<C,R,S,T>& lhs, const S rhs);

//==============================================================================

// Function definitions

// determinant

template<typename S, class T>	
S 
determinant(const mat<2,2,S,T>& m) 
{
	return (m[0][0]*m[1][1] - m[0][1]*m[1][0]);
}

template<typename S, class T>	
S 
determinant(const mat<3,3,S,T>& m) 
{
	return (m[0][0]*(m[1][1]*m[2][2] - m[2][1]*m[1][2]) - 
			m[1][0]*(m[0][1]*m[2][2] - m[2][1]*m[0][2]) + 
			m[2][0]*(m[0][1]*m[1][2] - m[1][1]*m[0][2]));
}

template<typename S, class T>	
S 
determinant(const mat<4,4,S,T>& m) 
{ 
	return (
		m[0][0]*m[1][1]*m[2][2]*m[3][3] + 
		m[1][0]*m[2][1]*m[3][2]*m[0][3] + 
		m[2][0]*m[3][1]*m[0][2]*m[1][3] + 
		m[3][0]*m[0][1]*m[1][2]*m[2][3] - 
		m[0][0]*m[3][1]*m[2][2]*m[1][3] -
		m[1][0]*m[0][1]*m[3][2]*m[2][3] -
		m[2][0]*m[1][1]*m[0][2]*m[3][3] -
		m[3][0]*m[2][1]*m[1][2]*m[0][3]);
}

//==============================================================================

// transpose

template<typename S, class T>	
void 
transpose(mat<2,2,S,T>* m) 
{
	assert(0 != m);
	const S tmp((*m)[0][1]);
	(*m)[0][1] = (*m)[1][0];
	(*m)[1][0] = tmp;
}

template<typename S, class T>	
void 
transpose(mat<3,3,S,T>* m) 
{
	assert(0 != m);
	S tmp((*m)[1][0]);
	(*m)[1][0] = (*m)[0][1];
	(*m)[0][1] = tmp;

	tmp = (*m)[2][0];
	(*m)[2][0] = (*m)[0][2];
	(*m)[0][2] = tmp;

	tmp = (*m)[2][1];
	(*m)[2][1] = (*m)[1][2];
	(*m)[1][2] = tmp;
}

template<typename S, class T>	
void 
transpose(mat<4,4,S,T>* m) 
{
	assert(0 != m);
	S tmp((*m)[1][0]);
	(*m)[1][0] = (*m)[0][1];
	(*m)[0][1] = tmp;

	tmp = (*m)[2][0];
	(*m)[2][0] = (*m)[0][2];
	(*m)[0][2] = tmp;

	tmp = (*m)[3][0];
	(*m)[3][0] = (*m)[0][3];
	(*m)[0][3] = tmp;

	tmp = (*m)[2][1];
	(*m)[2][1] = (*m)[1][2];
	(*m)[1][2] = tmp;

	tmp = (*m)[3][1];
	(*m)[3][1] = (*m)[1][3];
	(*m)[1][3] = tmp;

	tmp = (*m)[3][2];
	(*m)[3][2] = (*m)[2][3];
	(*m)[2][3] = tmp;
}

//==============================================================================

// transposed

template<typename S, class T> 
mat<2,2,S,T> 
transposed(const mat<2,2,S,T>& m)
{
	return mat<2,2,S,T>(m[0][0], m[0][1],
						m[1][0], m[1][1]);
}

template<typename S, class T> 
mat<3,3,S,T> 
transposed(const mat<3,3,S,T>& m)
{
	return mat<3,3,S,T>(m[0][0], m[0][1], m[0][2],
						m[1][0], m[1][1], m[1][2],
						m[2][0], m[2][1], m[2][2]);
}

template<typename S, class T>
mat<4,4,S,T> 
transposed(const mat<4,4,S,T>& m)
{
	return mat<4,4,S,T>(m[0][0], m[0][1], m[0][2], m[0][3],
						m[1][0], m[1][1], m[1][2], m[1][3],
						m[2][0], m[2][1], m[2][2], m[2][3],
						m[3][0], m[3][1], m[3][2], m[3][3]);
}

//==============================================================================

template<typename S, class T> 
void 
invert(mat<2,2,S,T>* m)
{
	assert(0 != m);
	assert(!is_zero(determinant(*m)));
	const S inv_det(T::one()/determinant(*m));
	const S c0r0_tmp((*m)[0][0]);
	(*m)[0][0]  =  inv_det*(*m)[1][1];
	(*m)[0][1] *= -inv_det;
	(*m)[1][0] *= -inv_det;
	(*m)[1][1]  =  inv_det*c0r0_tmp;
}

template<typename S, class T> 
void 
invert(mat<3,3,S,T>* m)
{	// Compute inverse by method of sub-determinants.
	//
	assert(0 != m);
	assert(!is_zero(determinant(*m)));
	const mat<3,3,S,T> b(*m);
	const S inv_det(T::one()/determinant(*m));
	(*m)[0][0] = inv_det*(b[1][1]*b[2][2] - b[2][1]*b[1][2]);	
	(*m)[0][1] = inv_det*(b[2][1]*b[0][2] - b[0][1]*b[2][2]);	
	(*m)[0][2] = inv_det*(b[0][1]*b[1][2] - b[1][1]*b[0][2]);	
	(*m)[1][0] = inv_det*(b[2][0]*b[1][2] - b[1][0]*b[2][2]);	
	(*m)[1][1] = inv_det*(b[0][0]*b[2][2] - b[2][0]*b[0][2]);	
	(*m)[1][2] = inv_det*(b[1][0]*b[0][2] - b[0][0]*b[1][2]);	
	(*m)[2][0] = inv_det*(b[1][0]*b[2][1] - b[2][0]*b[1][1]);	
	(*m)[2][1] = inv_det*(b[2][0]*b[0][1] - b[0][0]*b[2][1]);	
	(*m)[2][2] = inv_det*(b[0][0]*b[1][1] - b[1][0]*b[0][1]);	
}

template<typename S, class T>
void 
invert(mat<4,4,S,T>* m)
{	// Taken from Numerical Recipes in C++;
	// void NR::gaussj(Mat_IO_DP &a, Mat_IO_DP &b)
	//
	assert(0 != m);
	assert(!is_zero(determinant(*m)));

	static const int64 dim(mat<4,4,S,T>::dim);
	//enum { dim = mat<4,4,S,T>::dim };

	mat<4,4,S,T> b(mat<4,4,S,T>::identity);
   
	int64 i, icol = 0, irow = 0, j, k, l, ll;
	S big, dum, pivinv;

	int64 indxc[dim];
	int64 indxr[dim];
	int64 ipiv[dim];
	memset(ipiv, 0, dim*sizeof(int64));	// TODO: std:: ?

	for(i = 0; i < dim; ++i) 
	{
		big = T::zero();
		for(j = 0; j < dim; ++j)
		{
			if( 1 != ipiv[j] )
			{
				for(k = 0; k < dim; ++k) 
				{
					if( 0 == ipiv[k] && T::abs((*m)[j][k]) >= big ) 
					{
						big = T::abs((*m)[j][k]);
						irow = j;
						icol = k;
					}
				}
			}
		}

		++ipiv[icol];
		if( irow != icol ) 
		{
			for(l = 0; l < dim; ++l)
			{	// Swap.
				//
				const S tmp((*m)[irow][l]);
				(*m)[irow][l] = (*m)[icol][l];
				(*m)[icol][l] = tmp;
			}

			for(l = 0; l < dim; ++l)
			{	// Swap.
				//
				const S tmp(b[irow][l]);
				b[irow][l] = b[icol][l];
				b[icol][l] = tmp;
			}
		}

		indxr[i] = irow;
		indxc[i] = icol;

		assert(!is_zero((*m)[icol][icol]));
		pivinv = T::one()/(*m)[icol][icol];

		(*m)[icol][icol] = T::one();

		for(l = 0; l < dim; ++l)
		{
			(*m)[icol][l] *= pivinv;
		}

		for(l = 0; l < dim; ++l)
		{	
			b[icol][l] *= pivinv;
		}

		for(ll = 0; ll < dim; ++ll)
		{
			if( ll != icol ) 
			{
				dum = (*m)[ll][icol];
				(*m)[ll][icol] = T::zero();

				for(l = 0; l < dim; ++l)
				{
					(*m)[ll][l] -= (*m)[icol][l]*dum;
				}

				for(l = 0; l < dim; ++l)
				{
					b[ll][l] -= b[icol][l]*dum;
				}
			}
		}
	}

	for(l = dim - 1; l >= 0; --l) 
	{
		if( indxr[l] != indxc[l] )
		{
			for(k = 0; k < dim; ++k)
			{
				const S tmp((*m)[k][indxr[l]]);
				(*m)[k][indxr[l]] = (*m)[k][indxc[l]];
				(*m)[k][indxc[l]] = tmp;
			}
		}
	}
}

//==============================================================================

template<typename S, class T> 
mat<2,2,S,T> 
inverted(const mat<2,2,S,T>& m)
{
	assert(!is_zero(determinant(m)));
	const S inv_det(T::one()/determinant(m));
	return mat<2,2,S,T>( inv_det*m[1][1], -inv_det*m[1][0],
						-inv_det*m[0][1],  inv_det*m[0][0]);
}

template<typename S, class T> 
mat<3,3,S,T> 
inverted(const mat<3,3,S,T>& m)
{
	assert(!is_zero(determinant(m)));
	//const mat<3,3,S,T> b(m);
	const S i(T::one()/determinant(m));
	return 
	  mat<3,3,S,T>(i*(m[1][1]*m[2][2] - m[2][1]*m[1][2]), 
				   i*(m[2][0]*m[1][2] - m[1][0]*m[2][2]), 
				   i*(m[1][0]*m[2][1] - m[2][0]*m[1][1]),
				   i*(m[2][1]*m[0][2] - m[0][1]*m[2][2]), 
				   i*(m[0][0]*m[2][2] - m[2][0]*m[0][2]), 
				   i*(m[2][0]*m[0][1] - m[0][0]*m[2][1]),
				   i*(m[0][1]*m[1][2] - m[1][1]*m[0][2]), 
				   i*(m[1][0]*m[0][2] - m[0][0]*m[1][2]), 
				   i*(m[0][0]*m[1][1] - m[1][0]*m[0][1]));
}

template<typename S, class T> 
mat<4,4,S,T> 
inverted(const mat<4,4,S,T>& m)
{
	mat<4,4,S,T> b(m);
	invert(&b);
	return b;
}

//==============================================================================

// Operator definitions

// Binary operator==

template<typename S, class T>
bool 
operator==(const mat<2,2,S,T>& lhs, const mat<2,2,S,T>& rhs)
{
	return (equal(lhs[0][0], rhs[0][0]) &&  
			equal(lhs[0][1], rhs[0][1]) &&  
			equal(lhs[1][0], rhs[1][0]) &&
			equal(lhs[1][1], rhs[1][1]));
}

template<typename S, class T>
bool 
operator==(const mat<3,3,S,T>& lhs, const mat<3,3,S,T>& rhs)
{
	return (equal(lhs[0][0], rhs[0][0]) &&  
			equal(lhs[0][1], rhs[0][1]) &&  
			equal(lhs[0][2], rhs[0][2]) &&  
			equal(lhs[1][0], rhs[1][0]) &&
			equal(lhs[1][1], rhs[1][1]) &&
			equal(lhs[1][2], rhs[1][2]) &&
			equal(lhs[2][0], rhs[2][0]) &&
			equal(lhs[2][1], rhs[2][1]) &&
			equal(lhs[2][2], rhs[2][2]));
}

template<typename S, class T>
bool 
operator==(const mat<4,4,S,T>& lhs, const mat<4,4,S,T>& rhs)
{
	return (equal(lhs[0][0], rhs[0][0]) &&  
			equal(lhs[0][1], rhs[0][1]) &&  
			equal(lhs[0][2], rhs[0][2]) &&
			equal(lhs[0][3], rhs[0][3]) &&
			equal(lhs[1][0], rhs[1][0]) &&
			equal(lhs[1][1], rhs[1][1]) &&
			equal(lhs[1][2], rhs[1][2]) &&
			equal(lhs[1][3], rhs[1][3]) &&
			equal(lhs[2][0], rhs[2][0]) &&
			equal(lhs[2][1], rhs[2][1]) &&
			equal(lhs[2][2], rhs[2][2]) &&
			equal(lhs[2][3], rhs[2][3]) &&
			equal(lhs[3][0], rhs[3][0]) &&
			equal(lhs[3][1], rhs[3][1]) &&
			equal(lhs[3][2], rhs[3][2]) &&
			equal(lhs[3][3], rhs[3][3]));
}

//==============================================================================

// Binary operator!=

template<typename S, class T>
bool 
operator!=(const mat<2,2,S,T>& lhs, const mat<2,2,S,T>& rhs)
{
	return !(lhs == rhs);
}

template<typename S, class T>
bool 
operator!=(const mat<3,3,S,T>& lhs, const mat<3,3,S,T>& rhs)
{
	return !(lhs == rhs);
}

template<typename S, class T>
bool 
operator!=(const mat<4,4,S,T>& lhs, const mat<4,4,S,T>& rhs)
{
	return !(lhs == rhs);
}

//==============================================================================

// Binary operator+

template<typename S, class T>
mat<2,2,S,T> 
operator+(const mat<2,2,S,T>& lhs, const mat<2,2,S,T>& rhs)
{
	return mat<2,2,S,T>(lhs[0][0] + rhs[0][0], lhs[1][0] + rhs[1][0],
						lhs[0][1] + rhs[0][1], lhs[1][1] + rhs[1][1]);
}

template<typename S, class T>
mat<3,3,S,T> operator+(const mat<3,3,S,T>& lhs, const mat<3,3,S,T>& rhs)
{
	return mat<3,3,S,T>(
		lhs[0][0] + rhs[0][0], lhs[1][0] + rhs[1][0], lhs[2][0] + rhs[2][0], 
		lhs[0][1] + rhs[0][1], lhs[1][1] + rhs[1][1], lhs[2][1] + rhs[2][1], 
		lhs[0][2] + rhs[0][2], lhs[1][2] + rhs[1][2], lhs[2][2] + rhs[2][2]);
}

template<typename S, class T>
mat<4,4,S,T> operator+(const mat<4,4,S,T>& l, const mat<4,4,S,T>& r)
{
	return 
		mat<4,4,S,T>(
			l[0][0]+r[0][0], l[1][0]+r[1][0], l[2][0]+r[2][0], l[3][0]+r[3][0], 
			l[0][1]+r[0][1], l[1][1]+r[1][1], l[2][1]+r[2][1], l[3][1]+r[3][1], 
			l[0][2]+r[0][2], l[1][2]+r[1][2], l[2][2]+r[2][2], l[3][2]+r[3][2], 
			l[0][3]+r[0][3], l[1][3]+r[1][3], l[2][3]+r[2][3], l[3][3]+r[3][3]);
}

//==============================================================================

// Binary operator-

template<typename S, class T>
mat<2,2,S,T> 
operator-(const mat<2,2,S,T>& lhs, const mat<2,2,S,T>& rhs)
{
	return mat<2,2,S,T>(lhs[0][0] - rhs[0][0], lhs[1][0] - rhs[1][0],
						lhs[0][1] - rhs[0][1], lhs[1][1] - rhs[1][1]);
}

template<typename S, class T>
mat<3,3,S,T> operator-(const mat<3,3,S,T>& lhs, const mat<3,3,S,T>& rhs)
{
	return mat<3,3,S,T>(
		lhs[0][0] - rhs[0][0], lhs[1][0] - rhs[1][0], lhs[2][0] - rhs[2][0], 
		lhs[0][1] - rhs[0][1], lhs[1][1] - rhs[1][1], lhs[2][1] - rhs[2][1], 
		lhs[0][2] - rhs[0][2], lhs[1][2] - rhs[1][2], lhs[2][2] - rhs[2][2]);
}

template<typename S, class T>
mat<4,4,S,T> operator-(const mat<4,4,S,T>& l, const mat<4,4,S,T>& r)
{
	return 
		mat<4,4,S,T>(
			l[0][0]-r[0][0], l[1][0]-r[1][0], l[2][0]-r[2][0], l[3][0]-r[3][0], 
			l[0][1]-r[0][1], l[1][1]-r[1][1], l[2][1]-r[2][1], l[3][1]-r[3][1], 
			l[0][2]-r[0][2], l[1][2]-r[1][2], l[2][2]-r[2][2], l[3][2]-r[3][2], 
			l[0][3]-r[0][3], l[1][3]-r[1][3], l[2][3]-r[2][3], l[3][3]-r[3][3]);
}

//==============================================================================

// Binary operator*(scalar, mat)

template<typename S, class T>
mat<2,2,S,T> 
operator*(const S lhs, const mat<2,2,S,T>& rhs)
{
	return mat<2,2,S,T>(lhs*rhs[0][0], lhs*rhs[1][0], 
						lhs*rhs[0][1], lhs*rhs[1][1]);

}

template<typename S, class T>
mat<3,3,S,T> 
operator*(const S lhs, const mat<3,3,S,T>& rhs)
{
	return mat<3,3,S,T>(
		lhs*rhs[0][0], lhs*rhs[1][0], lhs*rhs[2][0], 
		lhs*rhs[0][1], lhs*rhs[1][1], lhs*rhs[2][1], 
		lhs*rhs[0][2], lhs*rhs[1][2], lhs*rhs[2][2]);
}

template<typename S, class T>
mat<4,4,S,T> 
operator*(const S lhs, const mat<4,4,S,T>& rhs)
{
	return mat<4,4,S,T>(
		lhs*rhs[0][0], lhs*rhs[1][0], lhs*rhs[2][0], lhs*rhs[3][0], 
		lhs*rhs[0][1], lhs*rhs[1][1], lhs*rhs[2][1], lhs*rhs[3][1], 
		lhs*rhs[0][2], lhs*rhs[1][2], lhs*rhs[2][2], lhs*rhs[3][2], 
		lhs*rhs[0][3], lhs*rhs[1][3], lhs*rhs[2][3], lhs*rhs[3][3]);
}

//==============================================================================

// Binary operator*(mat, scalar)
template<typename S, class T>
mat<2,2,S,T> 
operator*(const mat<2,2,S,T>& lhs, const S rhs)
{
	return rhs*lhs;
}

template<typename S, class T>
mat<3,3,S,T> 
operator*(const mat<3,3,S,T>& lhs, const S rhs)
{
	return rhs*lhs;
}

template<typename S, class T>
mat<4,4,S,T> 
operator*(const mat<4,4,S,T>& lhs, const S rhs)
{
	return rhs*lhs;
}

//==============================================================================

// Binary operator*(mat, mat)

template<typename S, class T>
mat<2,2,S,T> 
operator*(const mat<2,2,S,T>& lhs, const mat<2,2,S,T>& rhs)
{	// Matrix multiplication.
	//
	return mat<2,2,S,T>(
				lhs[0][0]*rhs[0][0] + lhs[1][0]*rhs[0][1],
				lhs[0][0]*rhs[1][0] + lhs[1][0]*rhs[1][1],
				lhs[0][1]*rhs[0][0] + lhs[1][1]*rhs[0][1],
				lhs[0][1]*rhs[1][0] + lhs[1][1]*rhs[1][1]);
}

template<typename S, class T>
mat<3,3,S,T> 
operator*(const mat<3,3,S,T>& lhs, const mat<3,3,S,T>& rhs)
{	// Matrix multiplication.
	//
	return mat<3,3,S,T>(
		lhs[0][0]*rhs[0][0] + lhs[1][0]*rhs[0][1] + lhs[2][0]*rhs[0][2],
		lhs[0][0]*rhs[1][0] + lhs[1][0]*rhs[1][1] + lhs[2][0]*rhs[1][2], 
		lhs[0][0]*rhs[2][0] + lhs[1][0]*rhs[2][1] + lhs[2][0]*rhs[2][2],
		lhs[0][1]*rhs[0][0] + lhs[1][1]*rhs[0][1] + lhs[2][1]*rhs[0][2],
		lhs[0][1]*rhs[1][0] + lhs[1][1]*rhs[1][1] + lhs[2][1]*rhs[1][2], 
		lhs[0][1]*rhs[2][0] + lhs[1][1]*rhs[2][1] + lhs[2][1]*rhs[2][2],
		lhs[0][2]*rhs[0][0] + lhs[1][2]*rhs[0][1] + lhs[2][2]*rhs[0][2],
		lhs[0][2]*rhs[1][0] + lhs[1][2]*rhs[1][1] + lhs[2][2]*rhs[1][2], 
		lhs[0][2]*rhs[2][0] + lhs[1][2]*rhs[2][1] + lhs[2][2]*rhs[2][2]);
}

template<typename S, class T>
mat<4,4,S,T> 
operator*(const mat<4,4,S,T>& l, const mat<4,4,S,T>& r)
{	// Matrix multiplication.
	//
	return 
	  mat<4,4,S,T>(
		 l[0][0]*r[0][0] + l[1][0]*r[0][1] + l[2][0]*r[0][2] + l[3][0]*r[0][3],
		 l[0][0]*r[1][0] + l[1][0]*r[1][1] + l[2][0]*r[1][2] + l[3][0]*r[1][3],
		 l[0][0]*r[2][0] + l[1][0]*r[2][1] + l[2][0]*r[2][2] + l[3][0]*r[2][3],
		 l[0][0]*r[3][0] + l[1][0]*r[3][1] + l[2][0]*r[3][2] + l[3][0]*r[3][3],
		 l[0][1]*r[0][0] + l[1][1]*r[0][1] + l[2][1]*r[0][2] + l[3][1]*r[0][3],
		 l[0][1]*r[1][0] + l[1][1]*r[1][1] + l[2][1]*r[1][2] + l[3][1]*r[1][3],
		 l[0][1]*r[2][0] + l[1][1]*r[2][1] + l[2][1]*r[2][2] + l[3][1]*r[2][3],
		 l[0][1]*r[3][0] + l[1][1]*r[3][1] + l[2][1]*r[3][2] + l[3][1]*r[3][3],
		 l[0][2]*r[0][0] + l[1][2]*r[0][1] + l[2][2]*r[0][2] + l[3][2]*r[0][3],
		 l[0][2]*r[1][0] + l[1][2]*r[1][1] + l[2][2]*r[1][2] + l[3][2]*r[1][3],
		 l[0][2]*r[2][0] + l[1][2]*r[2][1] + l[2][2]*r[2][2] + l[3][2]*r[2][3],
		 l[0][2]*r[3][0] + l[1][2]*r[3][1] + l[2][2]*r[3][2] + l[3][2]*r[3][3],
		 l[0][3]*r[0][0] + l[1][3]*r[0][1] + l[2][3]*r[0][2] + l[3][3]*r[0][3],
		 l[0][3]*r[1][0] + l[1][3]*r[1][1] + l[2][3]*r[1][2] + l[3][3]*r[1][3],
		 l[0][3]*r[2][0] + l[1][3]*r[2][1] + l[2][3]*r[2][2] + l[3][3]*r[2][3],
		 l[0][3]*r[3][0] + l[1][3]*r[3][1] + l[2][3]*r[3][2] + l[3][3]*r[3][3]);
}

//==============================================================================

// Binary operator*(mat, vec)

template<typename S, class T>
vec<2,S,T> 
operator*(const mat<2,2,S,T>& lhs, const vec<2,S,T>& rhs)
{	// v' = M*v.
	//
	return 
		vec<2,S,T>(
			lhs[0][0]*rhs.x + lhs[1][0]*rhs.y, 
			lhs[0][1]*rhs.x + lhs[1][1]*rhs.y);
}

template<typename S, class T>
vec<3,S,T> 
operator*(const mat<3,3,S,T>& lhs, const vec<3,S,T>& rhs)
{	// v' = M*v.
	//
	return 
		vec<3,S,T>(
			lhs[0][0]*rhs.x + lhs[1][0]*rhs.y + lhs[2][0]*rhs.z, 
			lhs[0][1]*rhs.x + lhs[1][1]*rhs.y + lhs[2][1]*rhs.z,
			lhs[0][2]*rhs.x + lhs[1][2]*rhs.y + lhs[2][2]*rhs.z);
}

template<typename S, class T>
vec<4,S,T> 
operator*(const mat<4,4,S,T>& lhs, const vec<4,S,T>& rhs)
{	// v' = M*v.
	//
	return 
		vec<4,S,T>(
			lhs[0][0]*rhs.x+lhs[1][0]*rhs.y+lhs[2][0]*rhs.z+lhs[3][0]*rhs.w, 
			lhs[0][1]*rhs.x+lhs[1][1]*rhs.y+lhs[2][1]*rhs.z+lhs[3][1]*rhs.w,
			lhs[0][2]*rhs.x+lhs[1][2]*rhs.y+lhs[2][2]*rhs.z+lhs[3][2]*rhs.w,
			lhs[0][3]*rhs.x+lhs[1][3]*rhs.y+lhs[2][3]*rhs.z+lhs[3][3]*rhs.w);
}

template<typename S, class T>
vec<3,S,T> operator*(const mat<4,4,S,T>& lhs, const vec<3,S,T>& rhs)
{	// v' = M*v.
	//
	// Multiply as if w = 1. 
	//
	return 
		vec<3,S,T>(
			lhs[0][0]*rhs.x + lhs[1][0]*rhs.y + lhs[2][0]*rhs.z + lhs[3][0], 
			lhs[0][1]*rhs.x + lhs[1][1]*rhs.y + lhs[2][1]*rhs.z + lhs[3][1],
			lhs[0][2]*rhs.x + lhs[1][2]*rhs.y + lhs[2][2]*rhs.z + lhs[3][2]);
}


//==============================================================================

// Binary operator*(vec, mat)

template<typename S, class T>
vec<2,S,T> 
operator*(const vec<2,S,T>& lhs, const mat<2,2,S,T>& rhs)
{	// v' = v*M.
	//
	return 
		vec<2,S,T>(
			lhs.x*rhs[0][0] + lhs.y*rhs[0][1], 
			lhs.x*rhs[1][0] + lhs.y*rhs[1][1]);
}

template<typename S, class T>
vec<3,S,T> 
operator*(const vec<3,S,T>& lhs, const mat<3,3,S,T>& rhs)
{	// v' = v*M.
	//
	return 
		vec<3,S,T>(
			lhs.x*rhs[0][0] + lhs.y*rhs[0][1] + lhs.z*rhs[0][2],
			lhs.x*rhs[1][0] + lhs.y*rhs[1][1] + lhs.z*rhs[1][2],
			lhs.x*rhs[2][0] + lhs.y*rhs[2][1] + lhs.z*rhs[2][2]);
}

template<typename S, class T>
vec<4,S,T> 
operator*(const vec<4,S,T>& lhs, const mat<4,4,S,T>& rhs)
{	// v' = v*M.
	//
	return 
		vec<4,S,T>(
			lhs.x*rhs[0][0]+lhs.y*rhs[0][1]+lhs.z*rhs[0][2]+lhs.w*rhs[0][3],
			lhs.x*rhs[1][0]+lhs.y*rhs[1][1]+lhs.z*rhs[1][2]+lhs.w*rhs[1][3],
			lhs.x*rhs[2][0]+lhs.y*rhs[2][1]+lhs.z*rhs[2][2]+lhs.w*rhs[2][3],
			lhs.x*rhs[3][0]+lhs.y*rhs[3][1]+lhs.z*rhs[3][2]+lhs.w*rhs[3][3]);
}

//==============================================================================

// Binary operator/(mat, scalar)

template<typename S, class T>
mat<2,2,S,T> 
operator/(const mat<2,2,S,T>& lhs, const S rhs)
{
	assert(!is_zero(rhs));
	if( T::is_floating )
	{	// Compile-time branching.
		//
		const S inv_fact(T::one()/rhs);
		return mat<2,2,S,T>(lhs[0][0]*inv_fact, lhs[1][0]*inv_fact, 
							lhs[0][1]*inv_fact, lhs[1][1]*inv_fact);
	}
	else
	{
		return mat<2,2,S,T>(lhs[0][0]/rhs, lhs[1][0]/rhs, 
							lhs[0][1]/rhs, lhs[1][1]/rhs);
	}
}

template<typename S, class T>
mat<3,3,S,T> 
operator/(const mat<3,3,S,T>& lhs, const S rhs)
{
	assert(!is_zero(rhs));
	if( T::is_floating )
	{	// Compile-time branching.
		//
		const S inv_fact(T::one()/rhs);
		return mat<3,3,S,T>(
			lhs[0][0]*inv_fact, lhs[1][0]*inv_fact, lhs[2][0]*inv_fact, 
			lhs[0][1]*inv_fact, lhs[1][1]*inv_fact, lhs[2][1]*inv_fact, 
			lhs[0][2]*inv_fact, lhs[1][2]*inv_fact, lhs[2][2]*inv_fact);
	}
	else
	{
		return mat<3,3,S,T>(
			lhs[0][0]/rhs, lhs[1][0]/rhs, lhs[2][0]/rhs, 
			lhs[0][1]/rhs, lhs[1][1]/rhs, lhs[2][1]/rhs, 
			lhs[0][2]/rhs, lhs[1][2]/rhs, lhs[2][2]/rhs);
	}
}

template<typename S, class T>
mat<4,4,S,T> 
operator/(const mat<4,4,S,T>& lhs, const S rhs)
{
	assert(!T::is_zero(rhs));
	if( T::is_floating )
	{	// Compile-time branching.
		//
		const S f(T::one()/rhs);
		return 
			mat<4,4,S,T>(
				lhs[0][0]*f, lhs[1][0]*f, lhs[2][0]*f, lhs[3][0]*f,
				lhs[0][1]*f, lhs[1][1]*f, lhs[2][1]*f, lhs[3][1]*f,
				lhs[0][2]*f, lhs[1][2]*f, lhs[2][2]*f, lhs[3][2]*f,
				lhs[0][3]*f, lhs[1][3]*f, lhs[2][3]*f, lhs[3][3]*f);
	}
	else
	{
		return 
			matrix4<S,T>(
				lhs[0][0]/rhs, lhs[1][0]/rhs, lhs[2][0]/rhs, lhs[3][0]/rhs, 
				lhs[0][1]/rhs, lhs[1][1]/rhs, lhs[2][1]/rhs, lhs[3][1]/rhs, 
				lhs[0][2]/rhs, lhs[1][2]/rhs, lhs[2][2]/rhs, lhs[3][2]/rhs, 
				lhs[0][3]/rhs, lhs[1][3]/rhs, lhs[2][3]/rhs, lhs[3][3]/rhs);
	}
}

//==============================================================================
}	// Namespace: thx.

#endif	// THX_MAT_UTILS_HPP_INCLUDED
