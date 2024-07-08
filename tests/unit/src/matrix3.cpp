#include <tst/set.hpp>
#include <tst/check.hpp>

#include "../../../src/r4/matrix.hpp"

using namespace std::string_literals;

// declare templates to instantiate all template methods to include all methods to gcov coverage
template class r4::matrix<int, 3, 3>;

namespace{
const tst::set set("matrix3", [](tst::suite& suite){
	suite.add("operator_output", []{
		r4::matrix3<int> m;
		m.set_identity();

		std::stringstream ss;

		ss << m;

		auto cmp =
				"|1 0 0" "\n"
				"|0 1 0" "\n"
				"|0 0 1" "\n"s;

		auto str = ss.str();

		tst::check_eq(str, cmp, SL);
	});

	suite.add("operator_square_brackets", []{
		r4::matrix3<int> m;

		m[0][0] = 1;
		m[0][1] = 2;
		m[0][2] = 3;
		m[1][0] = 4;
		m[1][1] = 5;
		m[1][2] = 6;
		m[2][0] = 7;
		m[2][1] = 8;
		m[2][2] = 9;

		std::stringstream ss;

		ss << m;

		auto cmp =
				"|1 2 3" "\n"
				"|4 5 6" "\n"
				"|7 8 9" "\n"s;
		auto str = ss.str();

		tst::check_eq(str, cmp, SL);
	});

	suite.add("constructor_3x_vector4", []{
		r4::vector3<int> r0(1, 2, 3);
		r4::vector3<int> r1(5, 6, 7);
		r4::vector3<int> r2(9, 10, 11);

		r4::matrix3<int> m(r0, r1, r2);

		std::stringstream ss;

		ss << m;

		auto cmp =
				"|1 2 3" "\n"
				"|5 6 7" "\n"
				"|9 10 11" "\n"s;
		auto str = ss.str();

		tst::check_eq(str, cmp, SL);
	});

	suite.add("to", []{
		r4::matrix3<float> mf{
			{ 1.1f, 2.2f, 3.3f },
			{ 4.4f, 5.5f, 6.6f },
			{ 7.7f, 8.8f, 9.9f }
		};

		auto mi = mf.to<int>();

		std::stringstream ss;

		ss << mi;

		auto cmp =
				"|1 2 3" "\n"
				"|4 5 6" "\n"
				"|7 8 9" "\n"s;
		auto str = ss.str();

		tst::check_eq(str, cmp, SL);
	});

	suite.add("submatrix", []{
		r4::matrix3<int> mf{
			{ 1, 2, 3 },
			{ 4, 5, 6 },
			{ 7, 8, 9 }
		};

		auto mi = mf.submatrix<0, 0, 2, 3>();

		std::stringstream ss;

		ss << mi;

		auto cmp =
				"|1 2 3" "\n"
				"|4 5 6" "\n"s;
		auto str = ss.str();

		tst::check_eq(str, cmp, SL);
	});

	suite.add("operator_multiply_vector2", []{
		r4::vector2<int> v(2, 3);

		r4::matrix3<int> m{
				{ 2, 3, 4 },
				{ 5, 6, 7 },
				{ 8, 9, 10 }
			};
		
		auto r = m * v;

		tst::check_eq(r[0], 13, SL);
		tst::check_eq(r[1], 28, SL);
	});

	suite.add("operator_multiply_vector3", []{
		r4::vector3<int> v(2, 3, 4);

		r4::matrix3<int> m{
				{ 2, 3, 4 },
				{ 5, 6, 7 },
				{ 8, 9, 10 }
			};
		
		auto r = m * v;

		tst::check_eq(r[0], 2 * 2 + 3 * 3 + 4 * 4, SL);
		tst::check_eq(r[1], 2 * 5 + 3 * 6 + 4 * 7, SL);
		tst::check_eq(r[2], 2 * 8 + 3 * 9 + 4 * 10, SL);
	});

	suite.add("transpose", []{
		r4::matrix3<int> m{
			{ 1, 2, 3 },
			{ 4, 5, 6 },
			{ 7, 8, 9 }
		};

		m.transpose();

		std::stringstream ss;

		ss << m;

		auto cmp =
				"|1 4 7" "\n"
				"|2 5 8" "\n"
				"|3 6 9" "\n"s;
		auto str = ss.str();

		tst::check_eq(str, cmp, SL);
	});

	suite.add("operator_multiply_matrix3", []{
		r4::matrix3<int> m1{
				{ 1, 2, 3 },
				{ 4, 5, 6 },
				{ 7, 8, 9 }
			};

		r4::matrix3<int> m2{
				{ 2, 3, 4 },
				{ 5, 6, 7 },
				{ 8, 9, 10 }
			};

		auto r = m1 * m2;

		tst::check_eq(r[0][0], 1 * 2 + 2 * 5 + 3 * 8, SL);
		tst::check_eq(r[1][0], 4 * 2 + 5 * 5 + 6 * 8, SL);
		tst::check_eq(r[2][0], 7 * 2 + 8 * 5 + 9 * 8, SL);
		tst::check_eq(r[0][1], 1 * 3 + 2 * 6 + 3 * 9, SL);
		tst::check_eq(r[1][1], 4 * 3 + 5 * 6 + 6 * 9, SL);
		tst::check_eq(r[2][1], 7 * 3 + 8 * 6 + 9 * 9, SL);
		tst::check_eq(r[0][2], 1 * 4 + 2 * 7 + 3 * 10, SL);
		tst::check_eq(r[1][2], 4 * 4 + 5 * 7 + 6 * 10, SL);
		tst::check_eq(r[2][2], 7 * 4 + 8 * 7 + 9 * 10, SL);
	});

	suite.add("operator_multiply_equals_matrix3", []{
		r4::matrix3<int> m1{
				{ 1, 2, 3 },
				{ 4, 5, 6 },
				{ 7, 8, 9 }
			};

		r4::matrix3<int> m2{
				{ 2, 3, 4 },
				{ 5, 6, 7 },
				{ 8, 9, 10 }
			};
		
		auto r = m1 * m2;

		m1 *= m2;

		tst::check_eq(m1, r, SL);
	});

	suite.add("left_mul_matrix3", []{
		r4::matrix3<int> m1{
				{ 1, 2, 3 },
				{ 4, 5, 6 },
				{ 7, 8, 9 }
			};

		r4::matrix3<int> m2{
				{ 2, 3, 4 },
				{ 5, 6, 7 },
				{ 8, 9, 10 }
			};
		
		auto r = m1 * m2;

		m2.left_mul(m1);

		tst::check_eq(m2, r, SL);
	});

	suite.add("scale_x_y_z", []{
		r4::matrix3<int> m{
				{ 1, 2, 3 },
				{ 4, 5, 6 },
				{ 7, 8, 9 }
			};
		
		m.scale(2, 3, 4);

		std::stringstream ss;

		ss << m;

		auto cmp =
				"|2 6 12" "\n"
				"|8 15 24" "\n"
				"|14 24 36" "\n"s;
		auto str = ss.str();

		tst::check_eq(str, cmp, SL);
	});

	suite.add("scale_x_y", []{
		r4::matrix3<int> m{
				{ 1, 2, 3 },
				{ 4, 5, 6 },
				{ 7, 8, 9 }
			};
		
		m.scale(2, 3);

		std::stringstream ss;

		ss << m;

		auto cmp =
				"|2 6 3" "\n"
				"|8 15 6" "\n"
				"|14 24 9" "\n"s;
		auto str = ss.str();

		tst::check_eq(str, cmp, SL);
	});

	suite.add("scale_number", []{
		r4::matrix3<int> m{
				{ 1, 2, 3 },
				{ 4, 5, 6 },
				{ 7, 8, 9 }
			};
		
		m.scale(2);

		std::stringstream ss;

		ss << m;

		auto cmp =
				"|2 4 6" "\n"
				"|8 10 12" "\n"
				"|14 16 18" "\n"s;
		auto str = ss.str();

		tst::check_eq(str, cmp, SL);
	});

	suite.add("translate_x_y", []{
		r4::matrix3<int> m{
				{ 1, 2, 3 },
				{ 4, 5, 6 },
				{ 7, 8, 9 }
			};
		
		m.translate(2, 3);

		std::stringstream ss;

		ss << m;

		auto cmp =
				"|1 2 11" "\n"
				"|4 5 29" "\n"
				"|7 8 47" "\n"s;
		auto str = ss.str();

		tst::check_eq(str, cmp, SL);
	});

	suite.add("translate_vector2", []{
		r4::matrix3<int> m{
				{ 1, 2, 3 },
				{ 4, 5, 6 },
				{ 7, 8, 9 }
			};
		
		m.translate(r4::vector2<int>{2, 3});

		std::stringstream ss;

		ss << m;

		auto cmp =
			"|1 2 11" "\n"
			"|4 5 29" "\n"
			"|7 8 47" "\n"s;
		auto str = ss.str();

		tst::check_eq(str, cmp, SL);
	});

	suite.add("rotate__quaternion", []{
		r4::matrix3<float> m{
				{ 10, 20, 30 },
				{ 40, 50, 60 },
				{ 70, 80, 90 }
			};
		
		float a = float(utki::pi) / 6;

		decltype(m) res(m);
		res.rotate(r4::quaternion<float>(a));

		using std::sin;
		using std::cos;

		r4::matrix3<float> rot{
			{cos(a), -sin(a), 0},
			{sin(a), cos(a), 0},
			{0, 0, 1}
		};

		auto cmp = m * rot;

		cmp *= 1000.0f;
		res *= 1000.0f;

		tst::check_eq(res.to<int>(), cmp.to<int>(), SL);
	});

	suite.add("minor_r_c", []{
		r4::matrix3<int> m{
			{3, 0, 2},
			{2, 0, -2},
			{0, 1, 1}
		};

		tst::check_eq(m.minor(0, 0), 2, SL);
		tst::check_eq(m.minor(0, 1), 2, SL);
		tst::check_eq(m.minor(0, 2), 2, SL);
		tst::check_eq(m.minor(1, 0), -2, SL);
		tst::check_eq(m.minor(1, 1), 3, SL);
		tst::check_eq(m.minor(1, 2), 3, SL);
		tst::check_eq(m.minor(2, 0), 0, SL);
		tst::check_eq(m.minor(2, 1), -10, SL);
		tst::check_eq(m.minor(2, 2), 0, SL);
	});

	suite.add("det", []{
		r4::matrix3<int> m{
				{ 10, 20, 30 },
				{ 40, 50, 60 },
				{ 70, 80, 100 }
			};
		
		tst::check_eq(m.det(), -3000, SL);
	});

	suite.add("inv", []{
		r4::matrix3<float> m{
			{1, 3, 5},
			{1, 3, 1},
			{4, 3, 9},
		};

		auto i = m * m.inv();

		const float epsilon = 1e-6f;

		auto diff = decltype(m)().set_identity() - i;

		diff.snap_to_zero(epsilon);

		tst::check_eq(diff, decltype(m)().set(0), SL);
	});
});
}
