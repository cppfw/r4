#include <r4/matrix.hpp>

#include <iostream>

int main(int argc, const char** argv){
	r4::matrix4<float> m;

	m.set_identity();

	std::cout << "Hello r4!" << '\n';
}
