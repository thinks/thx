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
#include "thx_quat.hpp"

//#include "thx_array1.hpp"
//#include "thx_bbox2.hpp"
//#include "thx_bbox3.hpp"
//#include "thx_hplane.hpp"

#include <iostream>
#include <iomanip>

//------------------------------------------------------------------------------

namespace std
{

//! Binary operator: std::ostream << vec<N,S>
template<thx::int64 N, typename S>
ostream&
operator<<(ostream &os, const thx::vec<N,S> &rhs)
{
    //ios_base::fmtflags f0 = os.flags();
    os	<< "[";
    //os	<< fixed << right << setprecision(3);
    for (thx::int64 i(0); i < N; ++i) {
        //os << setw(8) << rhs[i] << (i != (N - 1)) ? ", " : "";
        os << rhs[i] << (i != (N - 1) ? ", " : "");
    }
    os << "]";
    //os.flags(f0);

    return os;
}

//------------------------------------------------------------------------------

//! Binary operator: ostream << mat<N,S>
template<thx::int64 N, typename S>
ostream&
operator<<(ostream &os, const thx::mat<N,S> &rhs)
{
    //ios_base::fmtflags f0 = os.flags();
    //os	<< fixed << right << setprecision(3);
    for(thx::int64 i(0); i < N; ++i) {
        os	<< "[";
        for (thx::int64 j(0); j < N; ++j) {
            //os	<< setw(8) << rhs[c][r] << (c != (C - 1)) ? ", " : "";
            os << rhs(i,j) << (j != (N - 1) ? ", " : "");
        }
        os << "]\n";
    }
    //os.flags(f0);
    return os;
}

//------------------------------------------------------------------------------

//! Binary operator: std::ostream << quat<S>
template<typename S>
ostream&
operator<<(ostream& os, const thx::quat<S>& rhs)
{

    os	<< "[" << rhs[0] 
        << "(" << rhs[1] << ", " << rhs[2] << ", " << rhs[3] << ")]";
    return os;
}


#if 0





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


#endif

}	// Namespace: std.

#endif	// THX_IO_INCLUDED_HPP
