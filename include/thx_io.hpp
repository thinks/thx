//------------------------------------------------------------------------------
//
// Contributors: 
//             1) Tommy Hinks
//
//------------------------------------------------------------------------------

#ifndef THX_IO_INCLUDED_HPP
#define THX_IO_INCLUDED_HPP

#include "thx_mat.hpp"
#include <iostream>
#include <iomanip>

//------------------------------------------------------------------------------

namespace std
{

//------------------------------------------------------------------------------

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

//------------------------------------------------------------------------------

}	// Namespace: std.

#endif	// THX_IO_INCLUDED_HPP
