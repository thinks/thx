//------------------------------------------------------------------------------
//
// Contributors: 
//             1) Tommy Hinks
//
//------------------------------------------------------------------------------

#ifndef THX_ARITHMETIC_TYPE_HPP_INCLUDED
#define THX_ARITHMETIC_TYPE_HPP_INCLUDED

#include "thx_namespace.hpp"

//------------------------------------------------------------------------------

BEGIN_THX_NAMESPACE

template<typename S>
struct arithmetic_type
{
public:

  typedef S value;

private:

  static_assert(std::is_arithmetic<S>::value, "type must be arithmetic");
};

END_THX_NAMESPACE

#endif  // THX_ARITHMETIC_TYPE_HPP_INCLUDED