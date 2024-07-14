//
// Created by lifesize on 2024/7/14.
// Email Address: lifesize1@qq.com
//
#pragma once
#include <cstddef>
#include <functional>
#include <unordered_map>
#include <tuple>

template<typename T>
inline void hashCombine(std::size_t& seed, const T& v)
{   /**
    *  黄金比例乘以int的取值范围内的最大值得到的常数
    *  有助于均匀散列
    *  详细请看：https://softwareengineering.stackexchange.com/a/402543
    *
    *  Golden Ratio constant used for better hash scattering
    *  See https://softwareengineering.stackexchange.com/a/402543
    */
    const int golden_ratio = 0x9e3779b9;
    seed ^= std::hash<T> {}(v) + golden_ratio + (seed << 6) + (seed >> 2);
}

template<typename T, typename... Ts>
inline void hashCombine(std::size_t& seed, const T& v, Ts... rest)
{
    hashCombine(seed, v);
    if constexpr (sizeof...(Ts) > 1)
    {
        hashCombine(seed, rest...);
    }
}



/*
 * 实现std::tuple的hash函数
 * 请看：https://zhuanlan.zhihu.com/p/685835993 和 https://zhuanlan.zhihu.com/p/685835993
 *
 * see：https://zhuanlan.zhihu.com/p/685835993 and https://zhuanlan.zhihu.com/p/685835993
 */
template <std::size_t Index = 0, typename... Types>
size_t hashTuple(const std::tuple<Types...>& t, size_t sum_hash = 0)
{
    if constexpr (Index < sizeof...(Types))// C++ 17 特性 if constexpr
    {
        size_t current_hash = std::hash<typename std::tuple_element<Index, std::tuple<Types...>>::type>()(std::get<Index>(t));
        return hashTuple<Index + 1, Types...>(t, sum_hash^current_hash);
    }
    return sum_hash;
}

/*
* 给unordered_map用的哈希函数
*/
template<typename TupleType>
struct HashTupleStruct {
    size_t operator()(const TupleType& t) const {
        return hashTuple(t, 0);
    }
};
