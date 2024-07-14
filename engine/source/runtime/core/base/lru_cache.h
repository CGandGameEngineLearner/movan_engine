//
// Created by lifesize on 2024/7/14.
// Email Address: lifesize1@qq.com
// Document: https://zhuanlan.zhihu.com/p/685835993
//

#include "hash.h"

/*
 * 淘汰最近最少使用的 lru_cache
 */
template <typename K, typename V, typename Hash>
class LRUCache
{
private:
    int capacity;
    std::list<std::pair<K, V>> cacheList;
    std::unordered_map<K, typename std::list<std::pair<K, V>>::iterator, Hash> cacheMap;

public:
    LRUCache(int capacity) : capacity(capacity = 1024) {}
    bool contain(const K &key)
    {
        auto it = cacheMap.find(key);
        if (it == cacheMap.end())
        {
            return false;
        }
        else
        {
            return true;
        }
    }
    V get(const K &key)
    {
        auto it = cacheMap.find(key);
        if (it == cacheMap.end())
        {
            return V(); // 返回默认值
        }
        else
        {
            cacheList.splice(cacheList.begin(), cacheList, it->second);
            return it->second->second;
        }
    }

    void put(const K &key, const V &value)
    {
        auto it = cacheMap.find(key);
        if (it != cacheMap.end())
        {
            cacheList.erase(it->second);
            cacheMap.erase(it);
        }
        cacheList.push_front(std::make_pair(key, value));
        cacheMap[key] = cacheList.begin();

        if (cacheMap.size() > capacity)
        {
            K keyToRemove = cacheList.back().first;
            cacheMap.erase(keyToRemove);
            cacheList.pop_back();
        }
    }
};

/*
定义在需要lru_cache的函数的{的后面 第一个参数为返回值类型 第二个参数为lru cache的容量 后面的参数为组成key的参数
*/
#define LRU_CACHE_FUCTION_BEGIN(ReturnType, Capacity, ...)                                       \
    auto _key = std::make_tuple(__VA_ARGS__);                                                    \
    using _TupleType = decltype(_key);                                                           \
    static LRUCache<_TupleType, ReturnType, HashTupleStruct<_TupleType>> _lru_cache_s(Capacity); \
    int _contain = _lru_cache_s.contain(_key);                                                   \
    if (_contain)                                                                                \
    {                                                                                            \
        return _lru_cache_s.get(_key);                                                           \
    }

/*
定义在需要lru_cache的函数的}的return处
*/
#define LRU_CACHE_FUCTION_RETURN(Result) \
    _lru_cache_s.put(_key, Result);      \
    return Result;