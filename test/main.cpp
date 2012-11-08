//------------------------------------------------------------------------------
//
// Contributors: 
//             1) Tommy Hinks
//
//------------------------------------------------------------------------------

#include <thx.hpp>
#include <iostream>
#include <limits>
#include <string>
#include <sstream>
#include <exception>
#include <vector>
#include <functional>
#include <cstdlib>

//------------------------------------------------------------------------------

#define TEST_THX_TYPES
#define TEST_THX_VEC

//------------------------------------------------------------------------------

template<typename T>
struct BitSize 
{
  static const std::size_t value = 8*sizeof(T);
};

//------------------------------------------------------------------------------

//! Generic version.
template<typename S>
struct ScalarTypeName
{ static std::string value() { return std::string("S"); } };

template<>
struct ScalarTypeName<thx::float64>
{ static std::string value() { return std::string("float64"); } };

template<>
struct ScalarTypeName<thx::float32>
{ static std::string value() { return std::string("float32"); } };

template<>
struct ScalarTypeName<thx::int8>
{ static std::string value() { return std::string("int8"); } };

template<>
struct ScalarTypeName<thx::int16>
{ static std::string value() { return std::string("int16"); } };

template<>
struct ScalarTypeName<thx::int32>
{ static std::string value() { return std::string("int32"); } };

template<>
struct ScalarTypeName<thx::int64>
{ static std::string value() { return std::string("int64"); } };

template<>
struct ScalarTypeName<thx::uint8>
{ static std::string value() { return std::string("uint8"); } };

template<>
struct ScalarTypeName<thx::uint16>
{ static std::string value() { return std::string("uint16"); } };

template<>
struct ScalarTypeName<thx::uint32>
{ static std::string value() { return std::string("uint32"); } };

template<>
struct ScalarTypeName<thx::uint64>
{ static std::string value() { return std::string("uint64"); } };

//------------------------------------------------------------------------------

template<class V>
struct VecTypeName
{
  static std::string 
  value() 
  {
    std::stringstream ss;
    switch (V::dim) {
    case 2:
    case 3:
    case 4:
      ss << "vec<" << V::dim << "," 
         << ScalarTypeName<typename V::value_type>::value() 
         << "> (specialization)";
      break;
    default:
      ss << "vec<N," 
         << ScalarTypeName<typename V::value_type>::value() 
         << "> (generic)";
      break;
    }
    return ss.str();
  }
};

//------------------------------------------------------------------------------

template<typename S>
S
makeRandScalar(const int offset = 0, const int range = 1000)
{
  int r = rand()%range + offset;
  return static_cast<S>(r);
}

template<typename V> 
V 
makeRandVec(const int offset = 0, const int range = 1000) 
{
  typedef typename V::value_type value_type;
  typedef typename V::size_type size_type;
  static const size_type size = typename V::linear_size;

  V v;
  for (size_type i = 0; i < size; ++i) {
    v[i] = makeRandScalar<value_type>(offset, range);
  }
  return v;
}

template<typename S>
std::vector<S> 
makeRandArray(const std::size_t size, 
              const int offset = 0, 
              const int range = 1000) 
{
  using std::vector;
  using std::size_t;

  vector<S> v(size);
  for (size_t i = 0; i < v.size(); ++i) {
    v[i] = makeRandScalar<S>(offset, range);
  }
  return v;
}

//------------------------------------------------------------------------------

template<typename V> 
void 
testVecDefaultCtor() 
{
  using std::cout;
  using std::logic_error;
  using std::exception;

  typedef typename V::size_type size_type;
  static const size_type size = typename V::linear_size;

  try {
    cout << "Testing " << VecTypeName<V>::value() << " default CTOR... ";
    V v;
    if (v == V(0)) {
      cout << "OK!\n";  
    }
    else {
      throw logic_error("must initialize elements to zero");
    }
  }
  catch (exception& ex) {
    cout << "FAILED: " << ex.what() << "\n";
  }
}

//------------------------------------------------------------------------------

template<typename V> 
void 
testVecCopyCtor() 
{
  using std::cout;
  using std::logic_error;
  using std::exception;

  try {
    cout << "Testing " << VecTypeName<V>::value() << " copy CTOR... ";
    V v = makeRandVec<V>();  
    V u(v); // u is a copy of v. They should be equal.
    if (u == v) {
      cout << "OK!\n";
    }
    else {
      throw logic_error("copy not equal to original");
    }
  }
  catch (exception& ex) {
    cout << "FAILED: " << ex.what() << "\n";
  }
}

//------------------------------------------------------------------------------

template<typename V> 
void 
testVecArrayCtor() 
{
  using std::cout;
  using std::logic_error;
  using std::exception;

  try {
    typedef typename V::value_type value_type;
    typedef typename V::size_type size_type;
    static const size_type size = typename V::linear_size;

    std::vector<value_type> randArray = makeRandArray<value_type>(size);

    cout << "Testing " << VecTypeName<V>::value() << " array CTOR... ";
    V v(&randArray[0]);
    for (size_type i = 0; i < typename V::linear_size; ++i) {
      if (v[i] != randArray[i]) {
        throw logic_error("array copy error");
      }
    }
    cout << "OK!\n";
  }
  catch (exception& ex) {
    cout << "FAILED: " << ex.what() << "\n";
  }
}

//------------------------------------------------------------------------------

template<std::size_t N, typename S>
struct TestVecValueCtor;

template<typename S>
struct TestVecValueCtor<2, S>
{
  TestVecValueCtor()
  {
    using std::cout;
    using std::logic_error;
    using std::exception;

    try {
      typedef typename thx::vec<2,S> Vec;
      typedef Vec::value_type value_type;

      cout << "Testing " << VecTypeName<Vec>::value() << " value CTOR... ";

      const value_type r0 = makeRandScalar<value_type>();  
      const value_type r1 = makeRandScalar<value_type>();  

      Vec v(r0, r1);
      if (v[0] == r0 && v[1] == r1) {
        cout << "OK!\n";  
      }
      else {
        throw logic_error("value copy error");
      }
    }
    catch (exception& ex) {
      cout << "FAILED: " << ex.what() << "\n";
    }
  }
};

template<typename S>
struct TestVecValueCtor<3, S>
{
  TestVecValueCtor()
  {
    using std::cout;
    using std::logic_error;
    using std::exception;

    try {
      typedef typename thx::vec<3,S> Vec;
      typedef Vec::value_type value_type;

      cout << "Testing " << VecTypeName<Vec>::value() << " value CTOR... ";

      const value_type r0 = makeRandScalar<value_type>();  
      const value_type r1 = makeRandScalar<value_type>();  
      const value_type r2 = makeRandScalar<value_type>();  

      Vec v(r0, r1, r2);
      if (v[0] == r0 && v[1] == r1 && v[2] == r2) {
        cout << "OK!\n";  
      }
      else {
        throw logic_error("value copy error");
      }
    }
    catch (exception& ex) {
      cout << "FAILED: " << ex.what() << "\n";
    }
  }
};

template<typename S>
struct TestVecValueCtor<4, S>
{
  TestVecValueCtor()
  {
    using std::cout;
    using std::logic_error;
    using std::exception;

    try {
      typedef typename thx::vec<4,S> Vec;
      typedef Vec::value_type value_type;

      cout << "Testing " << VecTypeName<Vec>::value() << " value CTOR... ";

      const value_type r0 = makeRandScalar<value_type>();  
      const value_type r1 = makeRandScalar<value_type>();  
      const value_type r2 = makeRandScalar<value_type>();  
      const value_type r3 = makeRandScalar<value_type>();  

      Vec v(r0, r1, r2, r3);
      if (v[0] == r0 && v[1] == r1 && v[2] == r2 && v[3] == r3) {
        cout << "OK!\n";  
      }
      else {
        throw logic_error("value copy error");
      }
    }
    catch (exception& ex) {
      cout << "FAILED: " << ex.what() << "\n";
    }
  }
};

//------------------------------------------------------------------------------

template<typename V> 
void 
testVecAddEquals() 
{
  using std::cout;
  using std::logic_error;
  using std::exception;

  try {
    cout << "Testing " << VecTypeName<V>::value() << " += operator... ";
    V v1(1);
    V v2(1);
    v1 += v2;
    for (auto i = 0; i < typename V::linear_size; ++i) {
      if (v1[i] != 2) {
        throw logic_error("invalid element");
      }
    }
    cout << "OK!\n";
  }
  catch (exception& ex) {
    cout << "FAILED: " << ex.what() << "\n";
  }
}

//------------------------------------------------------------------------------

template<typename V> 
void 
testVecSubtractEquals() 
{
  using std::cout;
  using std::logic_error;
  using std::exception;

  try {
    cout << "Testing " << VecTypeName<V>::value() << " -= operator... ";
    V v1(1);
    v1 -= v1; // Subtract vec from itself. Should be all zeros.
    if (v1 == V(0)) {
      cout << "OK!\n";
    }
    else {
      throw logic_error("invalid element");
    }
  }
  catch (exception& ex) {
    cout << "FAILED: " << ex.what() << "\n";
  }
}

//------------------------------------------------------------------------------

template<typename V> 
void 
testVecMultEquals() 
{
  using std::cout;
  using std::logic_error;
  using std::exception;

  try {
    cout << "Testing " << VecTypeName<V>::value() << " *= operator... ";
    V v1(1);
    v1 *= 2; // Multiply (1,1,1) by 2. Should be (2,2,2).
    if (v1 == V(2)) {
      cout << "OK!\n";
    }
    else {
      throw logic_error("invalid element");
    }
  }
  catch (exception& ex) {
    cout << "FAILED: " << ex.what() << "\n";
  }
}

//------------------------------------------------------------------------------

template<typename V> 
void 
testVecEquality() 
{
  using std::cout;
  using std::logic_error;
  using std::exception;

  try {
    cout << "Testing " << VecTypeName<V>::value() << " == operator... ";
    V v;
    if (v == v) { // Test that instance is equal to itself. 
      cout << "OK!\n";
    }
    else {
      throw logic_error("self-equality failed");
    }
  }
  catch (exception& ex) {
    cout << "FAILED: " << ex.what() << "\n";
  }
}

//------------------------------------------------------------------------------

template<typename V> 
void 
testVecInequality() 
{
  using std::cout;
  using std::logic_error;
  using std::exception;

  try {
    cout << "Testing " << VecTypeName<V>::value() << " != operator... ";
    V v(1);
    V u(2);
    if (u != v) { 
      cout << "OK!\n";
    }
    else {
      throw logic_error("inequality failed");
    }
  }
  catch (exception& ex) {
    cout << "FAILED: " << ex.what() << "\n";
  }
}

//------------------------------------------------------------------------------

int
main(int argc, char* argv[])
{
  using std::cerr;
  using std::cout;
  using std::numeric_limits;
  using std::logic_error;
  using namespace thx;

  try {

    srand(1981);

#ifdef TEST_THX_TYPES
    {
      static_assert(BitSize<float64>::value == 64, 
                    "size of thx::float64 must be 64 bits");
      static_assert(BitSize<float32>::value == 32, 
                    "size of thx::float32 must be 32 bits");
      static_assert(BitSize<int8>::value == 8, 
                    "size of thx::int8 must be 8 bits");
      static_assert(BitSize<int16>::value == 16, 
                    "size of thx::int16 must be 16 bits");
      static_assert(BitSize<int32>::value == 32, 
                    "size of thx::int32 must be 32 bits");
      static_assert(BitSize<int64>::value == 64, 
                    "size of thx::int64 must be 64 bits");
      static_assert(BitSize<uint8>::value == 8, 
                    "size of thx::uint8 must be 8 bits");
      static_assert(BitSize<uint16>::value == 16, 
                    "size of thx::uint16 must be 16 bits");
      static_assert(BitSize<uint32>::value == 32, 
                    "size of thx::uint32 must be 32 bits");
      static_assert(BitSize<uint64>::value == 64, 
                    "size of thx::uint64 must be 64 bits");

      cout
        << "\n"
        << "thx::types:\n"
        << "sizeof(thx::float64) : " << BitSize<float64>::value << " [bits] | "
        << "min: " << (numeric_limits<float64>::min)() << ", "
        << "max: " << (numeric_limits<float64>::max)() << "\n"
        << "sizeof(thx::float32) : " << BitSize<float32>::value << " [bits] | "
        << "min: " << (numeric_limits<float32>::min)() << ", "
        << "max: " << (numeric_limits<float32>::max)() << "\n"
        << "sizeof(thx::int8)    : " << BitSize<int8>::value << "  [bits] | "
        << "min: " << static_cast<int64>((numeric_limits<int8>::min)()) << ", "
        << "max: " << static_cast<int64>((numeric_limits<int8>::max)()) << "\n"
        << "sizeof(thx::int16)   : " << BitSize<int16>::value << " [bits] | "
        << "min: " << (numeric_limits<int16>::min)() << ", "
        << "max: " << (numeric_limits<int16>::max)() << "\n"
        << "sizeof(thx::int32)   : " << BitSize<int32>::value << " [bits] | "
        << "min: " << (numeric_limits<int32>::min)() << ", "
        << "max: " << (numeric_limits<int32>::max)() << "\n"
        << "sizeof(thx::int64)   : " << BitSize<int64>::value << " [bits] | "
        << "min: " << (numeric_limits<int64>::min)() << ", "
        << "max: " << (numeric_limits<int64>::max)() << "\n"
        << "sizeof(thx::uint8)   : " << BitSize<uint8>::value << "  [bits] | "
        << "min: " << static_cast<int64>((numeric_limits<uint8>::min)()) << ", "
        << "max: " << static_cast<int64>((numeric_limits<uint8>::max)()) << "\n"
        << "sizeof(thx::uint16)  : " << BitSize<uint16>::value << " [bits] | "
        << "min: " << (numeric_limits<uint16>::min)() << ", "
        << "max: " << (numeric_limits<uint16>::max)() << "\n"
        << "sizeof(thx::uint32)  : " << BitSize<uint32>::value << " [bits] | "
        << "min: " << (numeric_limits<uint32>::min)() << ", "
        << "max: " << (numeric_limits<uint32>::max)() << "\n"
        << "sizeof(thx::uint64)  : " << BitSize<uint64>::value << " [bits] | "
        << "min: " << (numeric_limits<uint64>::min)() << ", "
        << "max: " << (numeric_limits<uint64>::max)() << "\n"
        << "\n";
    }
#endif

#ifdef TEST_THX_VEC
  {
#if 0
    {
      vec<1,float32> v1; // Should not compile, dimension must be >= 2.
      vec<2, int*> v; // Should not compile, int* is not an arithmetic type.
    }
#endif

    static_assert(BitSize<vec<2,float32>>::value == 2*BitSize<float32>::value, 
                  "thx::vec<N,S> must be perfectly aligned");
    static_assert(BitSize<vec<3,float32>>::value == 3*BitSize<float32>::value, 
                  "thx::vec<N,S> must be perfectly aligned");
    static_assert(BitSize<vec<4,float32>>::value == 4*BitSize<float32>::value, 
                  "thx::vec<N,S> must be perfectly aligned");
    static_assert(BitSize<vec<42,float32>>::value == 42*BitSize<float32>::value, 
                  "thx::vec<N,S> must be perfectly aligned");

    cout
      << "\n"
      << "thx::vec<N, S>:\n";

    { // Test vec default CTOR.
      typedef int32 ValueType;
      testVecDefaultCtor<vec<5,ValueType>>();
      testVecDefaultCtor<vec<2,ValueType>>();
      testVecDefaultCtor<vec<3,ValueType>>();
      testVecDefaultCtor<vec<4,ValueType>>();
    }

    { // Test vec copy CTOR.
      typedef int32 ValueType;
      testVecCopyCtor<vec<5,ValueType>>();
      testVecCopyCtor<vec<2,ValueType>>();
      testVecCopyCtor<vec<3,ValueType>>();
      testVecCopyCtor<vec<4,ValueType>>();
    }

    { // Test vec array CTOR.
      typedef int32 ValueType;
      testVecArrayCtor<vec<5,ValueType>>();
      testVecArrayCtor<vec<2,ValueType>>();
      testVecArrayCtor<vec<3,ValueType>>();
      testVecArrayCtor<vec<4,ValueType>>();
    }

    { // Test vec value CTOR. (only applicable to specializations)
      typedef int32 ValueType;
      TestVecValueCtor<2,ValueType>();
      TestVecValueCtor<3,ValueType>();
      TestVecValueCtor<4,ValueType>();
    }

    // TODO test assign?

    { // Test operator+= 
      typedef int32 ValueType;
      testVecAddEquals<vec<5,ValueType>>();
      testVecAddEquals<vec<2,ValueType>>();
      testVecAddEquals<vec<3,ValueType>>();
      testVecAddEquals<vec<4,ValueType>>();
    }

    { // Test operator-= 
      typedef int32 ValueType;
      testVecSubtractEquals<vec<5,ValueType>>();
      testVecSubtractEquals<vec<2,ValueType>>();
      testVecSubtractEquals<vec<3,ValueType>>();
      testVecSubtractEquals<vec<4,ValueType>>();
    }

    { // Test operator*= 
      typedef int32 ValueType;
      testVecMultEquals<vec<5,ValueType>>();
      testVecMultEquals<vec<2,ValueType>>();
      testVecMultEquals<vec<3,ValueType>>();
      testVecMultEquals<vec<4,ValueType>>();
    }

    { // Test operator!= (equality)
      typedef int32 ValueType;
      testVecEquality<vec<5,ValueType>>();
      testVecEquality<vec<2,ValueType>>();
      testVecEquality<vec<3,ValueType>>();
      testVecEquality<vec<4,ValueType>>();
    }

    { // Test operator== (inequality).
      typedef int32 ValueType;
      testVecInequality<vec<5,ValueType>>();
      testVecInequality<vec<2,ValueType>>();
      testVecInequality<vec<3,ValueType>>();
      testVecInequality<vec<4,ValueType>>();
    }

  }


    {
    vec3f32 u(1, 1, 1);
    vec3f32 v(2, 2, 2);
    cerr 
        << "u                 : " << u << "\n"
        << "v                 : " << v << "\n"
        << "dot(u,v)          : " << dot(u,v) << "\n"
        << "mag_squared(u)    : " << mag_squared(u) << "\n"
        << "mag(u)            : " << mag(u) << "\n"
        << "dist_squared(u,v) : " << dist_squared(u,v) << "\n"
        << "dist(u,v)         : " << dist(u,v) << "\n"
        << "normalized(u)     : " << normalized(u) << "\n";
    }
#endif

    cout << "\nTest Passed!\n";
    return EXIT_SUCCESS;
  }
  catch (const std::exception& ex) {
    cout 
      << ex.what() << "\n"
      << "\nTest Failed!\n";
    return EXIT_FAILURE;
  }



#if 1
    {
    mat2f32 m2(0.f, 2.f,
               1.f, 3.f);

    mat3f32 m3(1.f, 0.f, 6.f,
               0.f, 2.f, 7.f,
               0.f, 0.f, 3.5f);

    mat4f32 m4(1.f, 4.f, 8.f,  12.f,
               1.f, 0.1f, 9.f, 0.f,
               2.f, 6.f, -3.3f, 14.f,
               0.f, 0.f, 11.f, 150.f);

    srand(1981);
    mat<5,float32> m5;
    for (int64 i(0); i < 5; ++i) {
        for (int64 j(0); j < 5; ++j) {
            m5(i,j) = static_cast<float32>(rand())/RAND_MAX;
        }
    }

    const mat3f32 cm3(1.f, 0.f, 6.f,
                      0.f, 2.f, 7.f,
                      0.f, 0.f, 3.5f);


    cerr
        << "\n"
        << "sizeof(thx::mat2f32): " << sizeof(mat2f32) << " [bytes]\n"
        << "sizeof(thx::mat3f32): " << sizeof(mat3f32) << " [bytes]\n"
        << "sizeof(thx::mat4f32): " << sizeof(mat4f32) << " [bytes]\n"
        << "\n"
        //<< "mutable: &m3 | &m3[0]" << &m3 << " | " << &m3[0]
        //<< "const: &m3 | &m3[0]" << &cm3 << " | " << &cm3[0]
        //<< "\n"
        << "mat<2>:\n"
        << m2 << "\n"
        << "Transposed:\n"
        << transposed(m2) << "\n"
        << "Determinant:\n"
        << determinant(m2) << "\n\n"
        << "Inverted:\n"
        << inverted(m2) << "\n"
        << "M*M_inv:\n"
        << m2*inverted(m2) << "\n"
        << "\n\n"
        << "mat<3>:\n"
        << m3 << "\n"
        << "Transposed:\n"
        << transposed(m3) << "\n"
        << "Determinant:\n"
        << determinant(m3) << "\n\n"
        << "Inverted:\n"
        << inverted(m3) << "\n"
        << "M*M_inv:\n"
        << m3*inverted(m3) << "\n"
        << "\n\n"
        << "mat<4>:\n"
        << m4 << "\n"
        << "Transposed:\n"
        << transposed(m4) << "\n"
        << "Determinant:\n"
        << determinant(m4) << "\n\n"
        << "Inverted:\n"
        << inverted(m4) << "\n"
        << "M*M_inv:\n"
        << m4*inverted(m4) << "\n"
        << "\n\n"
        << "mat<5>:\n"
        << m5 << "\n"
        << "Inverted:\n"
        << inverted(m5) << "\n"
        << "M*M_inv:\n"
        << m5*inverted(m5) << "\n"
        << "\n";
    }
#endif


#if 1



#endif





#if 0
    {
    //thx::float32 x = 3.14f;
    //thx::int64 i = (std::numeric_limits<thx::int32>::max)()/2;
    thx::float32 big32 = 856015487.f;
    thx::float64 big64 = 856015487.0;
    std::cerr	
        << "\n"
        << "big32:  " << big32 << "\n"
        << "-big32: " << -big32 << "\n"
        << "thx::round_int32(big32):  " << thx::round_int32(big32) << "\n"
        << "thx::ceil_int32(big32):   " << thx::ceil_int32(big32) << "\n"
        << "thx::floor_int32(big32):  " << thx::floor_int32(big32) << "\n"
        << "thx::trunc_int32(big32):  " << thx::trunc_int32(big32) << "\n"
        << "thx::round_int32(-big32): " << thx::round_int32(-big32) << "\n"
        << "thx::ceil_int32(-big32):  " << thx::ceil_int32(-big32) << "\n"
        << "thx::floor_int32(-big32): " << thx::floor_int32(-big32) << "\n"
        << "thx::trunc_int32(-big32): " << thx::trunc_int32(-big32) << "\n"
        << "\n"
        << "big64:  " << big64 << "\n"
        << "-big64: " << -big64 << "\n"
        << "thx::round_int32(big64):  " << thx::round_int32(big64) << "\n"
        << "thx::ceil_int32(big64):   " << thx::ceil_int32(big64) << "\n"
        << "thx::floor_int32(big64):  " << thx::floor_int32(big64) << "\n"
        << "thx::trunc_int32(big64):  " << thx::trunc_int32(big64) << "\n"
        << "thx::round_int32(-big64): " << thx::round_int32(-big64) << "\n"
        << "thx::ceil_int32(-big64):  " << thx::ceil_int32(-big64) << "\n"
        << "thx::floor_int32(-big64): " << thx::floor_int32(-big64) << "\n"
        << "thx::trunc_int32(-big64): " << thx::trunc_int32(-big64) << "\n"
        << "\n";
    }
#endif


#if 0
    {
    thx::bbox2f32 bb2;
    thx::bbox3f32 bb3;
    std::cerr	
        << "\n" 
        << bb2 
        << "\n"
        << bb3
        << "\n";
    }
#endif

#if 0
    {
    thx::hplanef32 hp;
    std::cerr << hp;
    }
#endif

    //thx::array2<float> a2(4, 2.f);
    //std::cerr << a2;


#if 0
    {
    std::vector<thx::vec2f64> pvec2;
    pvec2.push_back(thx::vec2f64(-0.9, -0.9));
    pvec2.push_back(thx::vec2f64(-0.1, -0.2));
    pvec2.push_back(thx::vec2f64( 0.3,  1.1));
    pvec2.push_back(thx::vec2f64( 0.5,  0.7));
    pvec2.push_back(thx::vec2f64(23.4, 24.1));

    thx::vec2f64				nml2;
    thx::vec2f64				ctr2;
    thx::vec2f64::value_type	eval2[2];
    thx::vec2f64				evec2[2];
    thx::vec2f64::value_type	maxDist2;
    thx::vec2f64::value_type	confRate2;

    thx::line_fit(pvec2, &nml2, &ctr2, eval2, evec2, &maxDist2, &confRate2);
    std::cerr 
        << "\n"
        << "Nml2:       " << nml2 << "\n"
        << "Ctr2:       " << ctr2 << "\n"
        << "Eval2:      " << thx::vec2f64(eval2) << "\n"
        << "Evec2[0]:   " << evec2[0] << "\n"
        << "Evec2[1]:   " << evec2[1] << "\n"
        << "Max Dist2:  " << maxDist2 << "\n"
        << "Conf Rate2: " << confRate2 << "\n"
        << "\n";
    }
#endif

#if 0
    {
    std::vector<thx::vec3f64> pvec3;
    pvec3.push_back(thx::vec3f64(-0.9, -0.9, -0.7));
    pvec3.push_back(thx::vec3f64(-0.1, -0.2, -0.3));
    pvec3.push_back(thx::vec3f64( 0.3, 10.1,  0.5));
    pvec3.push_back(thx::vec3f64( 0.5,  0.7,  0.6));
    pvec3.push_back(thx::vec3f64(23.4, 23.1,  0.2));

    thx::vec3f64				nml3;
    thx::vec3f64				ctr3;
    thx::vec3f64::value_type	eval3[3];
    thx::vec3f64				evec3[3];
    thx::vec3f64::value_type	maxDist3;
    thx::vec3f64::value_type	confRate3;

    thx::plane_fit(pvec3, &nml3, &ctr3, eval3, evec3, &maxDist3, &confRate3);
    std::cerr 
        << "\n"
        << "Nml3:       " << nml3 << "\n"
        << "Ctr3:       " << ctr3 << "\n"
        << "Eval3:      " << thx::vec3f64(eval3) << "\n"
        << "Evec3[0]:   " << evec3[0] << "\n"
        << "Evec3[1]:   " << evec3[1] << "\n"
        << "Evec3[2]:   " << evec3[2] << "\n"
        << "Max Dist3:  " << maxDist3 << "\n"
        << "Conf Rate3: " << confRate3 << "\n"
        << "\n";
    }
#endif

#if 0
    {
    thx::quaternionf64 q(0.0, 1.0, 2.0, 3.0);
    std::cerr 
        << "\n" 
        << q 
        << "\n";

    thx::set_euler_angles(&q, thx::vec3f64(23.0, 97.0, 225.0));
    std::cerr
        << "set_euler_angles(23.0, 97.0, 225.0)\n" 
        << "euler_angles(): " << thx::euler_angles(q) << "\n"
        << "\n";
    }
#endif

    return 0;
}

#undef TEST_THX_TYPES
#undef TEST_THX_VEC
