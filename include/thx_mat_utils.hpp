//------------------------------------------------------------------------------
//
// Contributors: 
//             1) Tommy Hinks
//
//------------------------------------------------------------------------------

#ifndef THX_MAT_UTILS_HPP_INCLUDED
#define THX_MAT_UTILS_HPP_INCLUDED

#include "thx_mat.hpp"
#include "thx_utils.hpp"
#include "thx_static_assert.hpp"
#include <cassert>

//------------------------------------------------------------------------------

namespace thx
{
//==============================================================================

/*
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
*/


//------------------------------------------------------------------------------

//! Determinant.
template<int64 N, typename S>
S
determinant(const mat<N,S> &m)
{
    // TODO!
}

template<typename S>	
S 
determinant(const mat<2,S> &m) 
{
	return (m[0][0]*m[1][1] - m[0][1]*m[1][0]);
}

template<typename S>	
S 
determinant(const mat<3,S> &m) 
{
	return (m[0][0]*(m[1][1]*m[2][2] - m[2][1]*m[1][2]) - 
			m[1][0]*(m[0][1]*m[2][2] - m[2][1]*m[0][2]) + 
			m[2][0]*(m[0][1]*m[1][2] - m[1][1]*m[0][2]));
}

template<typename S>	
S 
determinant(const mat<4,S> &m) 
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

//! Transpose
template<int64 N, typename S>
void
transpose(mat<N,S> &m)
{
    // TODO!
}

template<typename S>	
void 
transpose(mat<2,S> &m) 
{
	const S tmp(m[0][1]);
	m[0][1] = m[1][0];
	m[1][0] = tmp;
}

template<typename S>	
void 
transpose(mat<3,S> &m) 
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
transpose(mat<4,S> &m) 
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

//! Transposed.
template<int64 N, typename S>
mat<N,S> 
transposed(const mat<N,S> &m)
{
    // TODO!
}

template<typename S> 
mat<2,S> 
transposed(const mat<2,S> &m)
{
	return mat<2,S>(m[0][0], m[0][1],
				    m[1][0], m[1][1]);
}

template<typename S> 
mat<3,S> 
transposed(const mat<3,S> &m)
{
	return mat<3,S>(m[0][0], m[0][1], m[0][2],
				    m[1][0], m[1][1], m[1][2],
				    m[2][0], m[2][1], m[2][2]);
}

template<typename S>
mat<4,S> 
transposed(const mat<4,S> &m)
{
	return mat<4,S>(m[0][0], m[0][1], m[0][2], m[0][3],
				    m[1][0], m[1][1], m[1][2], m[1][3],
				    m[2][0], m[2][1], m[2][2], m[2][3],
				    m[3][0], m[3][1], m[3][2], m[3][3]);
}

//------------------------------------------------------------------------------

//! Invert.
template<int64 N, typename S>
void 
invert(mat<N,S> &m)
{
    // TODO?

    /*
    THX_STATIC_ASSERT(traits<S>::is_floating);
	assert(!is_zero(determinant(m)));

    // Taken from Numerical Recipes in C++;
	// void NR::gaussj(Mat_IO_DP &a, Mat_IO_DP &b)

	static const int64 dim(mat<4,4,S,T>::dim);
	//enum { dim = mat<4,4,S,T>::dim };

	//mat<N,S> b(mat<4,4,S,T>::identity);
    mat<N,S> b(1);  // Identity.
   
	int64 i, icol = 0, irow = 0, j, k, l, ll;
	S big, dum, pivinv;

	int64 indxc[N];
	int64 indxr[N];
	int64 ipiv[N];

    for (int i(0); i < N; ++i) {
        ipiv[i] = 0;    
    }

	for (int i(0); i < N; ++i) {
		big = 0;
		for(int j(0); j < N; ++j) {
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
    */
}


template<typename S> 
void 
invert(mat<2,S> &m)
{
    THX_STATIC_ASSERT(traits<S>::is_floating);
	assert(!is_zero(determinant(m)));
    
    const S inv_det(1/determinant(m));

    // Swap and scale diagonal elements.

    const S tmp(m[0][0]);
    m[0][0] = inv_det*m[1][1];
    m[1][1] = inv_det*tmp;

    // Negate and scale off-diagonal elements.

	m[0][1] = -inv_det*m[0][1];
	m[1][0] = -inv_det*m[1][0];
}

template<typename S> 
void
invert(mat<3,S> &m)
{	
    THX_STATIC_ASSERT(traits<S>::is_floating);
	assert(!is_zero(determinant(m)));

    // Compute inverse by method of sub-determinants.

	const S inv_det(1/determinant(m));

    const mat<3,S> b(
	    inv_det*(m[1][1]*m[2][2] - m[2][1]*m[1][2]),	
	    inv_det*(m[2][1]*m[0][2] - m[0][1]*m[2][2]),	
	    inv_det*(m[0][1]*m[1][2] - m[1][1]*m[0][2]),	
	    inv_det*(m[2][0]*m[1][2] - m[1][0]*m[2][2]),
	    inv_det*(m[0][0]*m[2][2] - m[2][0]*m[0][2]),	
	    inv_det*(m[1][0]*m[0][2] - m[0][0]*m[1][2]),	
	    inv_det*(m[1][0]*m[2][1] - m[2][0]*m[1][1]),	
	    inv_det*(m[2][0]*m[0][1] - m[0][0]*m[2][1]),	
	    inv_det*(m[0][0]*m[1][1] - m[1][0]*m[0][1]));	

    m = b;
}

template<typename S>
void 
invert(mat<4,S>& m)
{	
    // TODO: Check Real-Time Rendering! Akenine et al.
}

//------------------------------------------------------------------------------

template<typename S> 
mat<2,S> 
inverted(const mat<2,S> &a)
{
    THX_STATIC_ASSERT(traits<S>::is_floating);
	assert(!is_zero(determinant(a)));

	const S inv_det(1/determinant(a));
	return mat<2,S>(
         inv_det*a[1][1], -inv_det*a[1][0],
  	    -inv_det*a[0][1],  inv_det*a[0][0]);
}

template<typename S> 
mat<3,S> 
inverted(const mat<3,S>& a)
{
    THX_STATIC_ASSERT(traits<S>::is_floating);
	assert(!is_zero(determinant(a)));

	const S inv_det(1/determinant(a));
	return mat<3,S>(
        inv_det*(a[1][1]*a[2][2] - a[2][1]*a[1][2]), 
        inv_det*(a[2][0]*a[1][2] - a[1][0]*a[2][2]), 
        inv_det*(a[1][0]*a[2][1] - a[2][0]*a[1][1]),
        inv_det*(a[2][1]*a[0][2] - a[0][1]*a[2][2]), 
        inv_det*(a[0][0]*a[2][2] - a[2][0]*a[0][2]), 
        inv_det*(a[2][0]*a[0][1] - a[0][0]*a[2][1]),
        inv_det*(a[0][1]*a[1][2] - a[1][1]*a[0][2]), 
        inv_det*(a[1][0]*a[0][2] - a[0][0]*a[1][2]), 
        inv_det*(a[0][0]*a[1][1] - a[1][0]*a[0][1]));
}

template<typename S> 
mat<4,S> 
inverted(const mat<4,S> &m)
{
	//mat<4,4,S> b(m);
	//invert(b);
	//return b;

    return mat<4,S>();
}

}	// Namespace: thx.

#endif	// THX_MAT_UTILS_HPP_INCLUDED
