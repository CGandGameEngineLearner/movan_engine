#pragma once

#include <algorithm>
#include <cfloat>
#include <random>

namespace Movan
{

	//https://blog.csdn.net/qq_38158479/article/details/122504026
	template<typename NumericType>
	using uniform_distribution = typename std::conditional<std::is_integral<NumericType>::value,
		std::uniform_int_distribution<NumericType>,
		std::uniform_real_distribution<NumericType>>::type;

	template<typename RandomEngine

}