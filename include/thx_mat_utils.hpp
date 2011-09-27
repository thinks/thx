//------------------------------------------------------------------------------
//
// Contributors: 
//             1) Tommy Hinks
//
//------------------------------------------------------------------------------

#ifndef THX_MAT_UTILS_HPP_INCLUDED
#define THX_MAT_UTILS_HPP_INCLUDED

#include "thx_mat.hpp"
#include "thx_vec.hpp"
#include "thx_utils.hpp"
#include <cassert>

//------------------------------------------------------------------------------

namespace thx
{
//==============================================================================


	explicit
	mat(const quaternion<S,T>& q)
	{
		m[0][0] = T::one() - static_cast<S>(2)*(q.v.z*q.v.z + q.v.w*q.v.w);
        m[0][1] =		     static_cast<S>(2)*(q.v.y*q.v.z + q.v.w*q.v.x);
        m[0][2] =		     static_cast<S>(2)*(q.v.y*q.v.w - q.v.z*q.v.x);
        
        m[1][0] =		     static_cast<S>(2)*(q.v.y*q.v.z - q.v.w*q.v.x);
        m[1][1] = T::one() - static_cast<S>(2)*(q.v.w*q.v.w + q.v.y*q.v.y);
        m[1][2] =		     static_cast<S>(2)*(q.v.z*q.v.w + q.v.y*q.v.x);
        
        m[2][0] =		     static_cast<S>(2)*(q.v.w*q.v.y + q.v.z*q.v.x);
        m[2][1] =		     static_cast<S>(2)*(q.v.z*q.v.w - q.v.y*q.v.x);
        m[2][2] = T::one() - static_cast<S>(2)*(q.v.z*q.v.z + q.v.y*q.v.y);
	}

		explicit
	mat(const quaternion<S,T>& q)
	{
		m[0][0] = T::one() - static_cast<S>(2)*(q.v.z*q.v.z + q.v.w*q.v.w);
        m[0][1] =		     static_cast<S>(2)*(q.v.y*q.v.z + q.v.w*q.v.x);
        m[0][2] =		     static_cast<S>(2)*(q.v.y*q.v.w - q.v.z*q.v.x);
		m[0][3] = T::zero();
        
        m[1][0] =		     static_cast<S>(2)*(q.v.y*q.v.z - q.v.w*q.v.x);
        m[1][1] = T::one() - static_cast<S>(2)*(q.v.w*q.v.w + q.v.y*q.v.y);
        m[1][2] =		     static_cast<S>(2)*(q.v.z*q.v.w + q.v.y*q.v.x);
        m[1][3] = T::zero();
        
        m[2][0] =		     static_cast<S>(2)*(q.v.w*q.v.y + q.v.z*q.v.x);
        m[2][1] =		     static_cast<S>(2)*(q.v.z*q.v.w - q.v.y*q.v.x);
        m[2][2] = T::one() - static_cast<S>(2)*(q.v.z*q.v.z + q.v.y*q.v.y);
        m[2][3] = T::zero();
        
        m[3][0] = T::zero();
        m[3][1] = T::zero();
        m[3][2] = T::zero();
        m[3][3] = T::one();
	}

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

// Function definitions

//------------------------------------------------------------------------------

// determinant

template<typename S>	
S 
determinant(const mat<2,2,S> &m) 
{
	return (m[0][0]*m[1][1] - m[0][1]*m[1][0]);
}

template<typename S>	
S 
determinant(const mat<3,3,S> &m) 
{
	return (m[0][0]*(m[1][1]*m[2][2] - m[2][1]*m[1][2]) - 
			m[1][0]*(m[0][1]*m[2][2] - m[2][1]*m[0][2]) + 
			m[2][0]*(m[0][1]*m[1][2] - m[1][1]*m[0][2]));
}

template<typename S>	
S 
determinant(const mat<4,4,S> &m) 
{ 
	return (m[0][0]*m[1][1]*m[2][2]*m[3][3] + 
		    m[1][0]*m[2][1]*m[3][2]*m[0][3] + 
		    m[2][0]*m[3][1]*m[0][2]*m[1][3] + 
		    m[3][0]*m[0][1]*m[1][2]*m[2][3] - 
		    m[0][0]*m[3][1]*m[2][2]*m[1][3] -
		    m[1][0]*m[0][1]*m[3][2]*m[2][3] -
		    m[2][0]*m[1][1]*m[0][2]*m[3][3] -
		    m[3][0]*m[2][1]*m[1][2]*m[0][3]);
}

//------------------------------------------------------------------------------

// transpose

template<typename S>	
void 
transpose(mat<2,2,S> &m) 
{
	const S tmp(m[0][1]);
	m[0][1] = m[1][0];
	m[1][0] = tmp;
}

template<typename S>	
void 
transpose(mat<3,3,S> &m) 
{
	S tmp(m[1][0]);
	m[1][0] = m[0][1];
	m[0][1] = tmp;

	tmp = m[2][0];
	m[2][0] = m[0][2];
	m[0][2] = tmp;

	tmp = m[2][1];
	m[2][1] = m[1][2];
	m[1][2] = tmp;
}

template<typename S>	
void 
transpose(mat<4,4,S> &m) 
{
	S tmp(m[1][0]);
	m[1][0] = m[0][1];
	m[0][1] = tmp;

	tmp = m[2][0];
	m[2][0] = m[0][2];
	m[0][2] = tmp;

	tmp = m[3][0];
	m[3][0] = m[0][3];
	m[0][3] = tmp;

	tmp = m[2][1];
	m[2][1] = m[1][2];
	m[1][2] = tmp;

	tmp = m[3][1];
	m[3][1] = m[1][3];
	m[1][3] = tmp;

	tmp = m[3][2];
	m[3][2] = m[2][3];
	m[2][3] = tmp;
}

//------------------------------------------------------------------------------

// transposed

template<typename S> 
mat<2,2,S> 
transposed(const mat<2,2,S> &m)
{
	return mat<2,2,S>(m[0][0], m[0][1],
					  m[1][0], m[1][1]);
}

template<typename S> 
mat<3,3,S> 
transposed(const mat<3,3,S> &m)
{
	return mat<3,3,S>(m[0][0], m[0][1], m[0][2],
					  m[1][0], m[1][1], m[1][2],
					  m[2][0], m[2][1], m[2][2]);
}

template<typename S>
mat<4,4,S> 
transposed(const mat<4,4,S> &m)
{
	return mat<4,4,S>(m[0][0], m[0][1], m[0][2], m[0][3],
					  m[1][0], m[1][1], m[1][2], m[1][3],
					  m[2][0], m[2][1], m[2][2], m[2][3],
					  m[3][0], m[3][1], m[3][2], m[3][3]);
}

//------------------------------------------------------------------------------

template<typename S> 
void 
invert(mat<2,2,S> &m)
{
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

}	// Namespace: thx.

#endif	// THX_MAT_UTILS_HPP_INCLUDED
