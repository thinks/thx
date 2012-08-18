//------------------------------------------------------------------------------
//
// Contributors: 
//             1) Tommy Hinks
//
//------------------------------------------------------------------------------

#ifndef THX_PIXEL_HPP_INCLUDED
#define THX_PIXEL_HPP_INCLUDED

#include "thx_types.hpp"
#include "thx_vec.hpp"
#include <cassert>

//------------------------------------------------------------------------------

namespace thx
{

template<int64 N, typename S = int8>
class pixel
{
public:

	typedef vec<N,S>::value_type value_type;

	static const int64 channel_count = vec<N,S>::dim;

public:

	//! CTOR.
	explicit 
	pixel(const S value = 0)
		: _data(value)
	{}

	//! Copy CTOR.
	explicit
	pixel(const pixel<N,S> &rhs)
		: _data(rhs._data)
	{}

	//! DTOR.
	~pixel()
	{}

	//! Assignment operator.
	pixel<N,S>&
	operator=(const pixel<N,S> &rhs)
	{
		_data = rhs._data;
		return *this;
	}

public:		// Operator access.

	//! Returns the value of channel c.
	value_type 
	operator[](const int64 c) const
	{ return _data[c]; }

	//! Returns the value of channel c.
	value_type& 
	operator[](const int64 c)
	{ return _data[c]; }

private:	// Member variables.

	vec<N,S> _data;	//!< Channel data.
};

// -----------------------------------------------------------------------------

// Convenient types.

typedef pixel<1,uint8> luminance_pixel;
typedef pixel<3,uint8> rgb_pixel;
typedef pixel<4,uint8> rgba_pixel;

}	// Namespace: thx.

#endif	// THX_PIXEL_HPP_INCLUDED
