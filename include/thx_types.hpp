//==============================================================================
// Contributors: 
//             1) Tommy Hinks
//==============================================================================

#ifndef THX_TYPES_HPP_INCLUDED
#define THX_TYPES_HPP_INCLUDED

#include "thx_static_assert.hpp"


namespace thx
{
//==============================================================================

typedef double			 float64;
typedef float			 float32;
typedef __int8			 int8;
typedef __int16			 int16;
typedef __int32			 int32;
typedef __int64			 int64;
typedef unsigned __int8	 uint8;
typedef unsigned __int16 uint16;
typedef unsigned __int32 uint32;
typedef unsigned __int64 uint64;

//==============================================================================
}	// Namespace: thx.


namespace
{
//==============================================================================

class type_size_check
{
public:
	~type_size_check()
	{
		THX_STATIC_ASSERT(4 == sizeof(thx::float32),	invalid_type_size);
		THX_STATIC_ASSERT(8 == sizeof(thx::float64),	invalid_type_size);
		THX_STATIC_ASSERT(1 == sizeof(thx::int8),		invalid_type_size);
		THX_STATIC_ASSERT(2 == sizeof(thx::int16),		invalid_type_size);
		THX_STATIC_ASSERT(4 == sizeof(thx::int32),		invalid_type_size);
		THX_STATIC_ASSERT(8 == sizeof(thx::int64),		invalid_type_size);
		THX_STATIC_ASSERT(1 == sizeof(thx::uint8),		invalid_type_size);
		THX_STATIC_ASSERT(2 == sizeof(thx::uint16),		invalid_type_size);
		THX_STATIC_ASSERT(4 == sizeof(thx::uint32),		invalid_type_size);
	}
};

//==============================================================================
}	// Namespace: anonymous.

#endif	// THX_TYPES_HPP_INCLUDED
