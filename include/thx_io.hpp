//------------------------------------------------------------------------------
//
// Contributors: 
//             1) Tommy Hinks
//
//------------------------------------------------------------------------------

#ifndef THX_IO_INCLUDED_HPP
#define THX_IO_INCLUDED_HPP

#include "thx_vec.hpp"
#include "thx_mat.hpp"

//#include "thx_array1.hpp"
//#include "thx_bbox2.hpp"
//#include "thx_bbox3.hpp"
//#include "thx_hplane.hpp"
//#include "thx_quaternion.hpp"

#include <iostream>
#include <iomanip>

//------------------------------------------------------------------------------

namespace std
{

// vec<N,S>

template<thx::int64 N, typename S>
ostream&
operator<<(ostream& os, const thx::vec<N,S>& rhs)
{
	ios_base::fmtflags f0 = os.flags();
	os	<< "[";
	os	<< fixed << right << setprecision(3);
	for (thx::int64 i(0); i < N; ++i) {
		os << setw(8) << rhs[i] << (i != (N - 1)) ? ", " : "";
	}
	os << "]";
	os.flags(f0);

	return os;
}

//------------------------------------------------------------------------------

// mat<C,R,S>

template<thx::int64 C, thx::int64 R, typename S>
ostream&
operator<<(ostream& os, const thx::mat<C,R,S>& rhs)
{
	ios_base::fmtflags f0 = os.flags();
	os	<< fixed << right << setprecision(3);
	for(thx::int64 r(0); r < R; ++r) {
		os	<< "[";
		for (thx::int64 c(0); c < C; ++c) {
			os	<< setw(8) << rhs[c][r] << (c != (C - 1)) ? ", " : "";
		}
		os << "]\n";
	}
	os.flags(f0);
	return os;
}

//------------------------------------------------------------------------------




#if 0

// Write to an ostream.
//

// array1
//
template<typename S, class T>
ostream&
operator<<(ostream& os, const thx::array1<S,T>& rhs)
{
	os	<< "array1::size:  " << rhs.size()		<< "\n"
		<< "array1::mem:   " << rhs.mem_used()	<< " [bytes]\n";
	return os;
}

//=============================================================================

// bbox2
//
template<typename S, class T>
ostream&
operator<<(ostream& os, const thx::bbox2<S,T>& rhs)
{
	os	<< "bbox2::min:  " << rhs.min()		<< "\n"
		<< "bbox2::max:  " << rhs.max()		<< "\n"
		<< "bbox3::dim:  " << rhs.dim()		<< "\n"
		<< "bbox3::mid:  " << rhs.mid()		<< "\n"
		<< "bbox2::area: " << rhs.area()	<< "\n";
	return os;
}

//=============================================================================

// bbox3
//
template<typename S, class T>
ostream&
operator<<(ostream& os, const thx::bbox3<S,T>& rhs)
{
	os	<< "bbox3::min:    " << rhs.min()		<< "\n"
		<< "bbox3::max:    " << rhs.max()		<< "\n"
		<< "bbox3::dim:    " << rhs.dim()		<< "\n"
		<< "bbox3::mid:    " << rhs.mid()		<< "\n"
		<< "bbox3::volume: " << rhs.volume()	<< "\n";
	return os;
}

//=============================================================================

// hplane
//
template<typename S, class T>
ostream&
operator<<(ostream& os, const thx::hplane<S,T>& rhs)
{
	os	<< "hplane::normal:    " << rhs.normal() << "\n"
		<< "hplane::distance:  " << rhs.d()		 << "\n";
	return os;
}

//=============================================================================


//=============================================================================

template<typename S, class T>
ostream&
operator<<(ostream& os, const thx::quaternion<S,T>& rhs)
{
	os << rhs.v;
	return os;
}

#endif

}	// Namespace: std.

#endif	// THX_IO_INCLUDED_HPP
