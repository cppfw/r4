#include <tst/set.hpp>
#include <tst/check.hpp>

#include "../../../src/r4/matrix.hpp"

using namespace std::string_literals;

namespace{
tst::set set("matrix4", [](tst::suite& suite){
    suite.add("constructor_4x_vector4", []{
        r4::matrix4<int> m{
		 	{1, 2, 3, 4},
			{5, 6, 7, 8},
			{9, 10, 11, 12},
			{13, 14, 15, 16}
		};

		std::stringstream ss;
		ss << m;
		auto str = ss.str();
		auto cmp =
				"|1 2 3 4" "\n"
				"|5 6 7 8" "\n"
				"|9 10 11 12" "\n"
				"|13 14 15 16" "\n"s;
		tst::check_eq(str, cmp, SL);
    });

    suite.add("constructor_quaternion", []{
        r4::quaternion<float> q;
		q.set_rotation(1, 2, 3, utki::pi<float>() / 6);

		r4::matrix4<float> m(q);

		m *= 1000.0f;

		std::stringstream ss;
		ss << m.to<int>();
		auto str = ss.str();
		auto cmp =
				"|-741 -1232 1401 0" "\n"
				"|1767 -339 303 0" "\n"
				"|-598 1303 330 0" "\n"
				"|0 0 0 1000" "\n"s;
		tst::check_eq(str, cmp, SL);
    });

    suite.add("operator_multiply_vector2", []{
        r4::matrix4<int> m{
		 	{1, 2, 3, 4},
			{5, 6, 7, 8},
			{9, 10, 11, 12},
			{13, 14, 15, 16}
		};

		auto r = m * r4::vector2<int>{3, 4};

		tst::check_eq(r[0], 1 * 3 + 2 * 4 + 4, SL);
		tst::check_eq(r[1], 5 * 3 + 6 * 4 + 8, SL);
    });

    suite.add("operator_multiply_vector3", []{
        r4::matrix4<int> m{
		 	{1, 2, 3, 4},
			{5, 6, 7, 8},
			{9, 10, 11, 12},
			{13, 14, 15, 16}
		};

		auto r = m * r4::vector3<int>{3, 4, 5};

		tst::check_eq(r[0], 1 * 3 + 2 * 4 + 3 * 5 + 4, SL);
		tst::check_eq(r[1], 5 * 3 + 6 * 4 + 7 * 5 + 8, SL);
		tst::check_eq(r[2], 9 * 3 + 10 * 4 + 11 * 5 + 12, SL);
    });

    suite.add("operator_multiply_vector4", []{
        r4::matrix4<int> m{
		 	{1, 2, 3, 4},
			{5, 6, 7, 8},
			{9, 10, 11, 12},
			{13, 14, 15, 16}
		};

		auto r = m * r4::vector4<int>{3, 4, 5, 6};

		tst::check_eq(r[0], 1 * 3 + 2 * 4 + 3 * 5 + 4 * 6, SL);
		tst::check_eq(r[1], 5 * 3 + 6 * 4 + 7 * 5 + 8 * 6, SL);
		tst::check_eq(r[2], 9 * 3 + 10 * 4 + 11 * 5 + 12 * 6, SL);
		tst::check_eq(r[3], 13 * 3 + 14 * 4 + 15 * 5 + 16 * 6, SL);
    });

    suite.add("operator_multiply_matrix4", []{
        r4::matrix4<int> m{
		 	{1, 2, 3, 4},
			{5, 6, 7, 8},
			{9, 10, 11, 12},
			{13, 14, 15, 16}
		};

		r4::matrix4<int> m2{
		 	{17, 18, 19, 20},
			{21, 22, 23, 24},
			{25, 26, 27, 28},
			{29, 30, 31, 32}
		};

		auto r = m * m2;

		tst::check_eq(r[0][0], 1 * 17 + 2 * 21 + 3 * 25 + 4 * 29, SL);
		tst::check_eq(r[1][0], 5 * 17 + 6 * 21 + 7 * 25 + 8 * 29, SL);
		tst::check_eq(r[2][0], 9 * 17 + 10 * 21 + 11 * 25 + 12 * 29, SL);
		tst::check_eq(r[3][0], 13 * 17 + 14 * 21 + 15 * 25 + 16 * 29, SL);
		tst::check_eq(r[0][1], 1 * 18 + 2 * 22 + 3 * 26 + 4 * 30, SL);
		tst::check_eq(r[1][1], 5 * 18 + 6 * 22 + 7 * 26 + 8 * 30, SL);
		tst::check_eq(r[2][1], 9 * 18 + 10 * 22 + 11 * 26 + 12 * 30, SL);
		tst::check_eq(r[3][1], 13 * 18 + 14 * 22 + 15 * 26 + 16 * 30, SL);
		tst::check_eq(r[0][2], 1 * 19 + 2 * 23 + 3 * 27 + 4 * 31, SL);
		tst::check_eq(r[1][2], 5 * 19 + 6 * 23 + 7 * 27 + 8 * 31, SL);
		tst::check_eq(r[2][2], 9 * 19 + 10 * 23 + 11 * 27 + 12 * 31, SL);
		tst::check_eq(r[3][2], 13 * 19 + 14 * 23 + 15 * 27 + 16 * 31, SL);
		tst::check_eq(r[0][3], 1 * 20 + 2 * 24 + 3 * 28 + 4 * 32, SL);
		tst::check_eq(r[1][3], 5 * 20 + 6 * 24 + 7 * 28 + 8 * 32, SL);
		tst::check_eq(r[2][3], 9 * 20 + 10 * 24 + 11 * 28 + 12 * 32, SL);
		tst::check_eq(r[3][3], 13 * 20 + 14 * 24 + 15 * 28 + 16 * 32, SL);
    });

    suite.add("transpose", []{
        r4::matrix4<int> m{
		 	{1, 2, 3, 4},
			{5, 6, 7, 8},
			{9, 10, 11, 12},
			{13, 14, 15, 16}
		};

		m.transpose();

		std::stringstream ss;
		ss << m;
		auto str = ss.str();
		auto cmp =
				"|1 5 9 13" "\n"
				"|2 6 10 14" "\n"
				"|3 7 11 15" "\n"
				"|4 8 12 16" "\n"s;
		tst::check_eq(str, cmp, SL);
    });

    suite.add("tpose", []{
        r4::matrix4<int> matrix{
		 	{1, 2, 3, 4},
			{5, 6, 7, 8},
			{9, 10, 11, 12},
			{13, 14, 15, 16}
		};

		auto m = matrix.tpose();

		std::stringstream ss;
		ss << m;
		auto str = ss.str();
		auto cmp =
				"|1 5 9 13" "\n"
				"|2 6 10 14" "\n"
				"|3 7 11 15" "\n"
				"|4 8 12 16" "\n"s;
		tst::check_eq(str, cmp, SL);
    });

    suite.add("operator_multiply_equals_matrix4", []{
        r4::matrix4<int> r{
		 	{1, 2, 3, 4},
			{5, 6, 7, 8},
			{9, 10, 11, 12},
			{13, 14, 15, 16}
		};

		r4::matrix4<int> m2{
		 	{17, 18, 19, 20},
			{21, 22, 23, 24},
			{25, 26, 27, 28},
			{29, 30, 31, 32}
		};

		r *= m2;

		tst::check_eq(r[0][0], 1 * 17 + 2 * 21 + 3 * 25 + 4 * 29, SL);
		tst::check_eq(r[1][0], 5 * 17 + 6 * 21 + 7 * 25 + 8 * 29, SL);
		tst::check_eq(r[2][0], 9 * 17 + 10 * 21 + 11 * 25 + 12 * 29, SL);
		tst::check_eq(r[3][0], 13 * 17 + 14 * 21 + 15 * 25 + 16 * 29, SL);
		tst::check_eq(r[0][1], 1 * 18 + 2 * 22 + 3 * 26 + 4 * 30, SL);
		tst::check_eq(r[1][1], 5 * 18 + 6 * 22 + 7 * 26 + 8 * 30, SL);
		tst::check_eq(r[2][1], 9 * 18 + 10 * 22 + 11 * 26 + 12 * 30, SL);
		tst::check_eq(r[3][1], 13 * 18 + 14 * 22 + 15 * 26 + 16 * 30, SL);
		tst::check_eq(r[0][2], 1 * 19 + 2 * 23 + 3 * 27 + 4 * 31, SL);
		tst::check_eq(r[1][2], 5 * 19 + 6 * 23 + 7 * 27 + 8 * 31, SL);
		tst::check_eq(r[2][2], 9 * 19 + 10 * 23 + 11 * 27 + 12 * 31, SL);
		tst::check_eq(r[3][2], 13 * 19 + 14 * 23 + 15 * 27 + 16 * 31, SL);
		tst::check_eq(r[0][3], 1 * 20 + 2 * 24 + 3 * 28 + 4 * 32, SL);
		tst::check_eq(r[1][3], 5 * 20 + 6 * 24 + 7 * 28 + 8 * 32, SL);
		tst::check_eq(r[2][3], 9 * 20 + 10 * 24 + 11 * 28 + 12 * 32, SL);
		tst::check_eq(r[3][3], 13 * 20 + 14 * 24 + 15 * 28 + 16 * 32, SL);
    });

    suite.add("operator_multiply_equals_number", []{
        r4::matrix4<int> m{
		 	{1, 2, 3, 4},
			{5, 6, 7, 8},
			{9, 10, 11, 12},
			{13, 14, 15, 16}
		};

		m *= 3;

		std::stringstream ss;
		ss << m;
		auto str = ss.str();
		auto cmp =
				"|3 6 9 12" "\n"
				"|15 18 21 24" "\n"
				"|27 30 33 36" "\n"
				"|39 42 45 48" "\n"s;
		tst::check_eq(str, cmp, SL);
    });

    suite.add("left_mul_matrix4", []{
        r4::matrix4<int> m2{
		 	{1, 2, 3, 4},
			{5, 6, 7, 8},
			{9, 10, 11, 12},
			{13, 14, 15, 16}
		};

		r4::matrix4<int> r{
		 	{17, 18, 19, 20},
			{21, 22, 23, 24},
			{25, 26, 27, 28},
			{29, 30, 31, 32}
		};

		r.left_mul(m2);

		tst::check_eq(r[0][0], 1 * 17 + 2 * 21 + 3 * 25 + 4 * 29, SL);
		tst::check_eq(r[1][0], 5 * 17 + 6 * 21 + 7 * 25 + 8 * 29, SL);
		tst::check_eq(r[2][0], 9 * 17 + 10 * 21 + 11 * 25 + 12 * 29, SL);
		tst::check_eq(r[3][0], 13 * 17 + 14 * 21 + 15 * 25 + 16 * 29, SL);
		tst::check_eq(r[0][1], 1 * 18 + 2 * 22 + 3 * 26 + 4 * 30, SL);
		tst::check_eq(r[1][1], 5 * 18 + 6 * 22 + 7 * 26 + 8 * 30, SL);
		tst::check_eq(r[2][1], 9 * 18 + 10 * 22 + 11 * 26 + 12 * 30, SL);
		tst::check_eq(r[3][1], 13 * 18 + 14 * 22 + 15 * 26 + 16 * 30, SL);
		tst::check_eq(r[0][2], 1 * 19 + 2 * 23 + 3 * 27 + 4 * 31, SL);
		tst::check_eq(r[1][2], 5 * 19 + 6 * 23 + 7 * 27 + 8 * 31, SL);
		tst::check_eq(r[2][2], 9 * 19 + 10 * 23 + 11 * 27 + 12 * 31, SL);
		tst::check_eq(r[3][2], 13 * 19 + 14 * 23 + 15 * 27 + 16 * 31, SL);
		tst::check_eq(r[0][3], 1 * 20 + 2 * 24 + 3 * 28 + 4 * 32, SL);
		tst::check_eq(r[1][3], 5 * 20 + 6 * 24 + 7 * 28 + 8 * 32, SL);
		tst::check_eq(r[2][3], 9 * 20 + 10 * 24 + 11 * 28 + 12 * 32, SL);
		tst::check_eq(r[3][3], 13 * 20 + 14 * 24 + 15 * 28 + 16 * 32, SL);
    });

    suite.add("set_identity", []{
        r4::matrix4<int> m{
		 	{1, 2, 3, 4},
			{5, 6, 7, 8},
			{9, 10, 11, 12},
			{13, 14, 15, 16}
		};

		m.set_identity();

		std::stringstream ss;
		ss << m;
		auto str = ss.str();
		auto cmp =
				"|1 0 0 0" "\n"
				"|0 1 0 0" "\n"
				"|0 0 1 0" "\n"
				"|0 0 0 1" "\n"s;
		tst::check_eq(str, cmp, SL);
    });

    suite.add("set_frustum_l_r_b_t_n_f", []{
        r4::matrix4<float> m{
		 	{1, 2, 3, 4},
			{5, 6, 7, 8},
			{9, 10, 11, 12},
			{13, 14, 15, 16}
		};

		m.set_frustum(-2, 2, -1.5, 1.5, 2, 100);
		m *= 1000.0f;

		std::stringstream ss;
		ss << m.to<int>();
		auto str = ss.str();
		auto cmp =
				"|1000 0 0 0" "\n"
				"|0 1333 0 0" "\n"
				"|0 0 -1040 -4081" "\n"
				"|0 0 -1000 0" "\n"s;
		tst::check_eq(str, cmp, SL);
    });

    suite.add("set_quaternion", []{
        r4::matrix4<float> m{
		 	{1, 2, 3, 4},
			{5, 6, 7, 8},
			{9, 10, 11, 12},
			{13, 14, 15, 16}
		};

		m.set(r4::quaternion<float>{2, 3, 4, 5});

		std::stringstream ss;
		ss << m.to<int>();
		auto str = ss.str();
		auto cmp =
				"|-49 -28 46 0" "\n"
				"|52 -39 4 0" "\n"
				"|-14 44 -25 0" "\n"
				"|0 0 0 1" "\n"s;
		tst::check_eq(str, cmp, SL);
    });

    suite.add("scale_x_y", []{
        r4::matrix4<int> m{
		 	{1, 2, 3, 4},
			{5, 6, 7, 8},
			{9, 10, 11, 12},
			{13, 14, 15, 16}
		};

		m.scale(3, 4);

		std::stringstream ss;
		ss << m;
		auto str = ss.str();
		auto cmp =
				"|3 8 3 4" "\n"
				"|15 24 7 8" "\n"
				"|27 40 11 12" "\n"
				"|39 56 15 16" "\n"s;
		tst::check_eq(str, cmp, SL);
    });

    suite.add("scale_x_y_z", []{
        r4::matrix4<int> m{
		 	{1, 2, 3, 4},
			{5, 6, 7, 8},
			{9, 10, 11, 12},
			{13, 14, 15, 16}
		};

		m.scale(3, 4, 5);

		std::stringstream ss;
		ss << m;
		auto str = ss.str();
		auto cmp =
				"|3 8 15 4" "\n"
				"|15 24 35 8" "\n"
				"|27 40 55 12" "\n"
				"|39 56 75 16" "\n"s;
		tst::check_eq(str, cmp, SL);
    });

    suite.add("scale_number", []{
        r4::matrix4<int> m{
		 	{1, 2, 3, 4},
			{5, 6, 7, 8},
			{9, 10, 11, 12},
			{13, 14, 15, 16}
		};

		m.scale(3);

		std::stringstream ss;
		ss << m;
		auto str = ss.str();
		auto cmp =
				"|3 6 9 4" "\n"
				"|15 18 21 8" "\n"
				"|27 30 33 12" "\n"
				"|39 42 45 16" "\n"s;
		tst::check_eq(str, cmp, SL);
    });

    suite.add("scale_vector2", []{
        r4::matrix4<int> m{
		 	{1, 2, 3, 4},
			{5, 6, 7, 8},
			{9, 10, 11, 12},
			{13, 14, 15, 16}
		};

		m.scale(r4::vector2<int>{3, 4});

		std::stringstream ss;
		ss << m;
		auto str = ss.str();
		auto cmp =
				"|3 8 3 4" "\n"
				"|15 24 7 8" "\n"
				"|27 40 11 12" "\n"
				"|39 56 15 16" "\n"s;
		tst::check_eq(str, cmp, SL);
    });

    suite.add("scale_vector3", []{
        r4::matrix4<int> m{
		 	{1, 2, 3, 4},
			{5, 6, 7, 8},
			{9, 10, 11, 12},
			{13, 14, 15, 16}
		};

		m.scale(r4::vector3<int>{3, 4, 5});

		std::stringstream ss;
		ss << m;
		auto str = ss.str();
		auto cmp =
				"|3 8 15 4" "\n"
				"|15 24 35 8" "\n"
				"|27 40 55 12" "\n"
				"|39 56 75 16" "\n"s;
		tst::check_eq(str, cmp, SL);
    });

    suite.add("translate_x_y", []{
        r4::matrix4<int> m{
		 	{1, 2, 3, 4},
			{5, 6, 7, 8},
			{9, 10, 11, 12},
			{13, 14, 15, 16}
		};

		m.translate(3, 4);

		std::stringstream ss;
		ss << m;
		auto str = ss.str();
		auto cmp =
				"|1 2 3 15" "\n"
				"|5 6 7 47" "\n"
				"|9 10 11 79" "\n"
				"|13 14 15 111" "\n"s;
		tst::check_eq(str, cmp, SL);
    });

    suite.add("translate_x_y_z", []{
        r4::matrix4<int> m{
		 	{1, 2, 3, 4},
			{5, 6, 7, 8},
			{9, 10, 11, 12},
			{13, 14, 15, 16}
		};

		m.translate(3, 4, 5);

		std::stringstream ss;
		ss << m;
		auto str = ss.str();
		auto cmp =
				"|1 2 3 30" "\n"
				"|5 6 7 82" "\n"
				"|9 10 11 134" "\n"
				"|13 14 15 186" "\n"s;
		tst::check_eq(str, cmp, SL);
    });

    suite.add("translate_vector2", []{
        r4::matrix4<int> m{
		 	{1, 2, 3, 4},
			{5, 6, 7, 8},
			{9, 10, 11, 12},
			{13, 14, 15, 16}
		};

		m.translate(r4::vector2<int>{3, 4});

		std::stringstream ss;
		ss << m;
		auto str = ss.str();
		auto cmp =
				"|1 2 3 15" "\n"
				"|5 6 7 47" "\n"
				"|9 10 11 79" "\n"
				"|13 14 15 111" "\n"s;
		tst::check_eq(str, cmp, SL);
    });

    suite.add("translate_vector3", []{
        r4::matrix4<int> m{
		 	{1, 2, 3, 4},
			{5, 6, 7, 8},
			{9, 10, 11, 12},
			{13, 14, 15, 16}
		};

		m.translate(r4::vector3<int>{3, 4, 5});

		std::stringstream ss;
		ss << m;
		auto str = ss.str();
		auto cmp =
				"|1 2 3 30" "\n"
				"|5 6 7 82" "\n"
				"|9 10 11 134" "\n"
				"|13 14 15 186" "\n"s;
		tst::check_eq(str, cmp, SL);
    });

    suite.add("rotate_quaternion", []{
        r4::matrix4<float> m{
		 	{1, 2, 3, 4},
			{5, 6, 7, 8},
			{9, 10, 11, 12},
			{13, 14, 15, 16}
		};

		r4::quaternion<float> quat{2, 3, 4, 5};

		r4::matrix4<float> rot;
		rot.set(quat);

		auto cmp = m * rot;

		m.rotate(quat);

		tst::check_eq(m.to<int>(), cmp.to<int>(), SL);
    });

    suite.add("rotate_vector3", []{
        r4::matrix4<float> m{
		 	{1, 2, 3, 4},
			{5, 6, 7, 8},
			{9, 10, 11, 12},
			{13, 14, 15, 16}
		};

		r4::vector3<float> vec{2, 3, 4};

		r4::matrix4<float> rot;
		rot.set(r4::quaternion<float>{vec});

		auto cmp = m * rot;

		m.rotate(vec);

		cmp *= 1000.0f;
		m *= 1000.0f;

		tst::check_eq(m.to<int>(), cmp.to<int>(), SL);
    });

    suite.add("rotate_number", []{
        r4::matrix4<float> m{
		 	{1, 2, 3, 4},
			{5, 6, 7, 8},
			{9, 10, 11, 12},
			{13, 14, 15, 16}
		};

		float angle = 4;

		r4::vector3<float> vec{0, 0, angle};

		r4::matrix4<float> rot;
		rot.set(r4::quaternion<float>{vec});

		auto cmp = m * rot;

		m.rotate(angle);

		cmp *= 1000.0f;
		m *= 1000.0f;

		tst::check_eq(m.to<int>(), cmp.to<int>(), SL);
    });

    suite.add("remove_r_c_and_minor_r_c", []{
        r4::matrix4<int> m{
		 	{1 , 2 , 3 , 4 },
			{5 , 6 , 7 , 8 },
			{9 , 10, 11, 12},
			{13, 14, 15, 16}
		};

		// row 0
		r4::matrix3<int> m00{
			{6, 7, 8},
			{10, 11, 12},
			{14, 15, 16}
		};

		r4::matrix3<int> m01{
			{5, 7, 8},
			{9, 11, 12},
			{13, 15, 16}
		};

		r4::matrix3<int> m02{
			{5, 6, 8},
			{9, 10, 12},
			{13, 14, 16}
		};

		r4::matrix3<int> m03{
			{5, 6, 7},
			{9, 10, 11},
			{13, 14, 15}
		};

		// row 1
		r4::matrix3<int> m10{
		 	{2,  3,  4 },
			{10, 11, 12},
			{14, 15, 16}
		};

		r4::matrix3<int> m11{
		 	{1,  3,  4 },
			{9,  11, 12},
			{13, 15, 16}
		};

		r4::matrix3<int> m12{
		 	{1,  2,  4 },
			{9,  10, 12},
			{13, 14, 16}
		};

		r4::matrix3<int> m13{
		 	{1,  2,  3 },
			{9,  10, 11},
			{13, 14, 15}
		};

		// row 2
		r4::matrix3<int> m20{
		 	{2 , 3 , 4 },
			{6 , 7 , 8 },
			{14, 15, 16}
		};

		r4::matrix3<int> m21{
		 	{1 , 3 , 4 },
			{5 , 7 , 8 },
			{13, 15, 16}
		};

		r4::matrix3<int> m22{
		 	{1 , 2 , 4 },
			{5 , 6 , 8 },
			{13, 14, 16}
		};

		r4::matrix3<int> m23{
		 	{1 , 2 , 3 },
			{5 , 6 , 7 },
			{13, 14, 15}
		};

		// row 3
		r4::matrix3<int> m30{
		 	{2 , 3 , 4 },
			{6 , 7 , 8 },
			{10, 11, 12}
		};

		r4::matrix3<int> m31{
		 	{1 , 3 , 4 },
			{5 , 7 , 8 },
			{9 , 11, 12}
		};

		r4::matrix3<int> m32{
		 	{1 , 2 , 4 },
			{5 , 6 , 8 },
			{9 , 10, 12}
		};

		r4::matrix3<int> m33{
		 	{1 , 2 , 3 },
			{5 , 6 , 7 },
			{9 , 10, 11}
		};

		tst::check_eq(m.remove(0, 0), m00, SL);
		tst::check_eq(m.remove(0, 1), m01, SL);
		tst::check_eq(m.remove(0, 2), m02, SL);
		tst::check_eq(m.remove(0, 3), m03, SL);

		tst::check_eq(m.remove(1, 0), m10, SL);
		tst::check_eq(m.remove(1, 1), m11, SL);
		tst::check_eq(m.remove(1, 2), m12, SL);
		tst::check_eq(m.remove(1, 3), m13, SL);

		tst::check_eq(m.remove(2, 0), m20, SL);
		tst::check_eq(m.remove(2, 1), m21, SL);
		tst::check_eq(m.remove(2, 2), m22, SL);
		tst::check_eq(m.remove(2, 3), m23, SL);

		tst::check_eq(m.remove(3, 0), m30, SL);
		tst::check_eq(m.remove(3, 1), m31, SL);
		tst::check_eq(m.remove(3, 2), m32, SL);
		tst::check_eq(m.remove(3, 3), m33, SL);

		tst::check_eq(m.minor(0, 0), m00.det(), SL);
		tst::check_eq(m.minor(0, 1), m01.det(), SL);
		tst::check_eq(m.minor(0, 2), m02.det(), SL);
		tst::check_eq(m.minor(0, 3), m03.det(), SL);

		tst::check_eq(m.minor(1, 0), m10.det(), SL);
		tst::check_eq(m.minor(1, 1), m11.det(), SL);
		tst::check_eq(m.minor(1, 2), m12.det(), SL);
		tst::check_eq(m.minor(1, 3), m13.det(), SL);

		tst::check_eq(m.minor(2, 0), m20.det(), SL);
		tst::check_eq(m.minor(2, 1), m21.det(), SL);
		tst::check_eq(m.minor(2, 2), m22.det(), SL);
		tst::check_eq(m.minor(2, 3), m23.det(), SL);

		tst::check_eq(m.minor(3, 0), m30.det(), SL);
		tst::check_eq(m.minor(3, 1), m31.det(), SL);
		tst::check_eq(m.minor(3, 2), m32.det(), SL);
		tst::check_eq(m.minor(3, 3), m33.det(), SL);
    });

    suite.add("det", []{
        r4::matrix4<int> m{
		 	{1, 3, 5, 9},
			{1, 3, 1, 7},
			{4, 3, 9, 7},
			{5, 2, 0, 9}
		};
		
		tst::check_eq(m.det(), -376, SL);
    });

    suite.add("inv", []{
        r4::matrix4<float> m{
		 	{1, 3, 5, 9},
			{1, 3, 1, 7},
			{4, 3, 9, 7},
			{5, 2, 0, 9}
		};

		auto inv = m.inv();

		auto i = m * inv;

		const float epsilon = 1e-6f;

		auto diff = decltype(m)().set_identity() - i;

		diff.snap_to_zero(epsilon);

		tst::check_eq(diff, decltype(m)().set(0), SL);
    });

    suite.add("operator_output", []{
        r4::matrix4<int> m;
		m.set_identity();

		std::stringstream ss;

		ss << m;

		auto cmp =
				"|1 0 0 0" "\n"
				"|0 1 0 0" "\n"
				"|0 0 1 0" "\n"
				"|0 0 0 1" "\n"s;

		tst::check_eq(ss.str(), cmp, SL);
    });
});
}
