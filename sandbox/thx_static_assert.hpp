//------------------------------------------------------------------------------
//
// Contributors: 
//             1) Tommy Hinks
//
//------------------------------------------------------------------------------

#ifndef THX_STATIC_ASSERT_HPP_INCLUDED
#define THX_STATIC_ASSERT_HPP_INCLUDED

//------------------------------------------------------------------------------

// Lifted directly from:
// Modern C++ Design: Generic Programming and Design Patterns Applied
// Section 2.1
// by Andrei Alexandrescu

namespace thx
{

template<bool> 
class compile_time_check
{
public:
    compile_time_check(...) {}
};

template<> 
class compile_time_check<false> 
{};

}	// Namespace: thx.

//------------------------------------------------------------------------------

//! THX_STATIC_ASSERT will test its first argument at compile time and will on 
//! failure report the error message of the second argument, which must be a 
//! valid c++ classname, i.e. no spaces, punctuation or reserved keywords.

//#ifndef NDEBUG
#define THX_STATIC_ASSERT(test, errormsg)                   \
do {                                                        \
    struct ERROR_##errormsg {};                             \
    typedef thx::compile_time_check<(test) != 0> tmpl_impl; \
    tmpl_impl aTemp = tmpl_impl(ERROR_##errormsg());        \
    sizeof(aTemp);                                          \
} while( 0 )
//#else
//#   define StaticAssert(test, errormsg)                         \
//    do {} while (0)
//#endif

#endif	// THX_STATIC_ASSERT_HPP_INCLUDED
