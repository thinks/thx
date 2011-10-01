//------------------------------------------------------------------------------
//
// Contributors: 
//             1) Tommy Hinks
//
//------------------------------------------------------------------------------

#ifndef THX_QUATERNION_HPP_INCLUDED
#define THX_QUATERNION_HPP_INCLUDED

#include "thx_vec.hpp"

//------------------------------------------------------------------------------

namespace thx 
{

template<typename S>
class quat
{
public:

	typedef S value_type;

public:
    
    //! Empty CTOR.
    explicit
    quat(const S real = 1)
		: _v(real, 0, 0, 0)
    {}

    //! Copy CTOR.
    explicit 
    quat(const quat<S> &rhs)
        : _v(rhs._v)
    {}

    //! CTOR.
	explicit
    quat(const S v0, const S v1, const S v2, const S v3)
		: _v(v0, v1, v2, v3)
    {}

    //! CTOR.
	explicit
    quat(const vec<4,S>& v)
		: _v(v)
    {}

    //! CTOR.
	explicit
    quat(const S real, const vec<3,S> &imag)
		: v(real, imag[0], imag[1], imag[2])
    {}

    //! DTOR.
    ~quat()
    {}

public:     // Operators.

    //! Assign.
    quat<S>&
    operator=(const quat<S> &rhs)
    {
        _v = rhs._v;
        return *this;
    }

	quat<S>&
    operator+=(const quat<S> &rhs)
    {
		_v += rhs._v;
        return *this;
    }

    quat<S>&
    operator-=(const quat<S> &rhs)
    {
		_v -= rhs._v;
        return *this;
    }

    quat<S>&
    operator*=(const S s)
    {
		_v *= s;
        return *this;
    }

    //! Quaternion multiplication.
    quat<S>&
    operator*=(const quat<S> &r)
    {	
		const quat<S> t(*this);
		_v[0] = t[0]*r[0] - t[1]*r[1] - t[2]*r[2] - t[3]*r[3];
        _v[1] = t[0]*r[1] + t[1]*r[0] + t[2]*r[3] - t[3]*r[2];
		_v[2] = t[0]*r[2] + t[2]*r[0] + t[3]*r[1] - t[1]*r[3];
		_v[3] = t[0]*r[3] + t[3]*r[0] + t[1]*r[2] - t[2]*r[1];
        return *this;
    }

    S  
    operator[](const int64 i) const	
    { return _v[i]; }

	S& 
    operator[](const int64 i)		
    { return _v[i]; }

private:	// Member variables.

    vec<4,S> _v;
};

//------------------------------------------------------------------------------

// Convenient types.

typedef quat<float32>	quatf32;
typedef quat<float64>	quatf64;

}  // Namespace: thx.

#endif  // THX_QUATERNION_HPP_INCLUDED
