#pragma once

#include <functional>
#include <algorithm>

template <class Iterable, class BinOp>
Iterable &update_with_op(Iterable &it, const Iterable &upd, const BinOp &op)
{
	std::transform(it.cbegin(), it.cend(), upd.cbegin(), it.begin(), op);
	return *it;
}

template <class Iterable, class BinOp>
Iterable componentwise_operation(const Iterable &lhs, const Iterable &rhs, const BinOp &op)
{
	Iterable res(lhs);
	update_with_op(lhs, rhs, op);
	return res;
}

template <class Iterable, class Scalar, class BinOp>
Iterable &update_with_scalar(Iterable &it, const Scalar &s, const BinOp &op)
{
	std::transform(it.cbegin(), it.cend(), it.begin(), [s, op](auto &x){return op(x, s);});
	return *it;
}

template <class Iterable, class Scalar, class BinOp>
Iterable scalar_operation(const Iterable &it, const Scalar &s, const BinOp &op)
{
	Iterable res(it);
	update_with_scalar(res, s, op);
	return res;
}

template <class Iterable>
Iterable &add(Iterable &it, const Iterable &another)
{
	return update_with_op(it, another, std::plus<void>());
}

template <class Iterable>
Iterable sum(const Iterable &lhs, const Iterable &rhs)
{
	return componentwise_operation(lhs, rhs, std::plus<void>());
}

template <class Iterable>
Iterable difference(const Iterable &lhs, const Iterable &rhs)
{
	return componentwise_operation(lhs, rhs, std::minus<void>());
}

template <class Iterable>
Iterable &subtract(Iterable &it, const Iterable &another)
{
	return update_with_op(it, another, std::minus<void>());
}

template<class Iterable, class Scalar>
Iterable &multiply(Iterable &it, const Scalar &s)
{
	return update_with_scalar(it, s, std::multiplies<>());
}

template<class Iterable, class Scalar>
Iterable product(Iterable &it, const Scalar &s)
{
	return scalar_operation(it, s, std::multiplies<>());
}
