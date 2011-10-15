//------------------------------------------------------------------------------
//
// Contributors: 
//             1) Tommy Hinks
//
//------------------------------------------------------------------------------

#include <thx.hpp>
#include <iostream>
#include <limits>

//------------------------------------------------------------------------------

int
main(int argc, char* argv[])
{
    using std::cerr;
    using std::numeric_limits;
    using namespace thx;

#if 1
    {
    cerr
        << "\n"
        << "thx::types:\n"
        << "sizeof(thx::float64): " << 8*sizeof(float64) << " [bits] | "
        << "min: " << (numeric_limits<float64>::min)() << ", "
        << "max: " << (numeric_limits<float64>::max)() << "\n"
        << "sizeof(thx::float32): " << 8*sizeof(float32) << " [bits] | "
        << "min: " << (numeric_limits<float32>::min)() << ", "
        << "max: " << (numeric_limits<float32>::max)() << "\n"
        << "sizeof(thx::int8):    " << 8*sizeof(int8) << "  [bits] | "
        << "min: " << static_cast<int64>((numeric_limits<int8>::min)()) << ", "
        << "max: " << static_cast<int64>((numeric_limits<int8>::max)()) << "\n"
        << "sizeof(thx::int16):   " << 8*sizeof(int16) << " [bits] | "
        << "min: " << (std::numeric_limits<int16>::min)() << ", "
        << "max: " << (std::numeric_limits<int16>::max)() << "\n"
        << "sizeof(thx::int32):   " << 8*sizeof(int32) << " [bits] | "
        << "min: " << (std::numeric_limits<int32>::min)() << ", "
        << "max: " << (std::numeric_limits<int32>::max)() << "\n"
        << "sizeof(thx::int64):   " << 8*sizeof(int64) << " [bits] | "
        << "min: " << (std::numeric_limits<int64>::min)() << ", "
        << "max: " << (std::numeric_limits<int64>::max)() << "\n"
        << "sizeof(thx::uint8):   " << 8*sizeof(uint8) << "  [bits] | "
        << "min: " << static_cast<int64>((numeric_limits<uint8>::min)()) << ", "
        << "max: " << static_cast<int64>((numeric_limits<uint8>::max)()) << "\n"
        << "sizeof(thx::uint16):  " << 8*sizeof(thx::uint16) << " [bits] | "
        << "min: " << (numeric_limits<thx::uint16>::min)() << ", "
        << "max: " << (numeric_limits<thx::uint16>::max)() << "\n"
        << "sizeof(thx::uint32):  " << 8*sizeof(uint32) << " [bits] | "
        << "min: " << (numeric_limits<uint32>::min)() << ", "
        << "max: " << (numeric_limits<uint32>::max)() << "\n"
        << "sizeof(thx::uint64):  " << 8*sizeof(uint64) << " [bits] | "
        << "min: " << (numeric_limits<uint64>::min)() << ", "
        << "max: " << (numeric_limits<uint64>::max)() << "\n"
        << "\n";
    }
#endif

#if 1
    {
    vec2f32 v2;
    vec3f32 v3;
    vec4f32 v4;
    vec<7,float32> v7(7.f);
    cerr
        << "\n"
        << "sizeof(vec2f32): " << sizeof(vec2f32) << " [bytes]\n"
        << "sizeof(vec3f32): " << sizeof(vec3f32) << " [bytes]\n"
        << "sizeof(vec4f32): " << sizeof(vec4f32) << " [bytes]\n"
        << "sizeof(vec<7,float32>): " << sizeof(vec<7,float32>) << " [bytes]\n"
        << "v2: " << v2 << "\n"
        << "v3: " << v3 << "\n"
        << "v4: " << v4 << "\n"
        << "v7: " << v7 << "\n"
        << "\n";
    }

    {
    vec<7,int32> u(3);
    vec<7,int32> v(4);
    cerr 
        << "u: " << u << "\n"
        << "v: " << v << "\n"
        << "u == v: " << ((u == v)  ? "true" : "false") << "\n"
        << "v != v: " << ((u != v)  ? "true" : "false") << "\n";
    }

    {
    vec3f32 u(1, 1, 1);
    vec3f32 v(2, 2, 2);
    cerr 
        << "u: " << u << "\n"
        << "v: " << v << "\n"
        << "dot(u,v): " << dot(u,v) << "\n"
        << "mag2(u): " << mag2(u) << "\n"
        << "mag(u): " << mag(u) << "\n"
        << "dist2(u,v): " << dist2(u,v) << "\n"
        << "dist(u,v): " << dist(u,v) << "\n"
        << "normalized(u): " << normalized(u) << "\n";
    }

#endif

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

    //srand(1981);
    //mat<5,float32> m5;
    //for (int i(0); i < 5; ++i) {
    //    for (int j(0); j < 5; ++j) {
    //        m5[i][j] = static_cast<float32>(rand())/RAND_MAX;
    //    }
    //}

    cerr
        << "\n"
        << "sizeof(thx::mat2f32): " << sizeof(mat2f32) << " [bytes]\n"
        << "sizeof(thx::mat3f32): " << sizeof(mat3f32) << " [bytes]\n"
        << "sizeof(thx::mat4f32): " << sizeof(mat4f32) << " [bytes]\n"
        << "\n"
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
        //<< "mat<3>:\n"
        //<< m3 << "\n"
        //<< "Transposed:\n"
        //<< transposed(m3) << "\n"
        //<< "Determinant:\n"
        //<< determinant(m3) << "\n\n"
        //<< "Inverted:\n"
        //<< inverted(m3) << "\n"
        //<< "M*M_inv:\n"
        //<< m3*inverted(m3) << "\n"
        //<< "\n\n"
        //<< "mat<4>:\n"
        //<< m4 << "\n"
        //<< "Transposed:\n"
        //<< transposed(m4) << "\n"
        //<< "Determinant:\n"
        //<< determinant(m4) << "\n\n"
        //<< "Inverted:\n"
        //<< inverted(m4) << "\n"
        //<< "M*M_inv:\n"
        //<< m4*inverted(m4) << "\n"
        //<< "\n\n"
        //<< "mat<5>:\n"
        //<< m5 << "\n"
        //<< "Inverted:\n"
        //<< inverted(m5) << "\n"
        //<< "M*M_inv:\n"
        //<< m5*inverted(m5) << "\n"
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
