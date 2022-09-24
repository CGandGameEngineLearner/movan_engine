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

    template<typename RandomEngine = std::default_random_engine>
    class RandomNumberGenerator
    {

    private:
        RandomEngine engine_;

    public:
        template<typename... Params>
        explicit RandomNumberGenerator(Params&&... params) : engine_(std::forward<Params>(params)...)
        {}

        template<typename... Params>
        void seed(Params&&... seeding)
        {
            engine_.seed(std::forward<Params>(seeding)...);
        }

        template<typename DistributionFunc, typename... Params>
        typename DistributionFunc::result_type distribution(Params&&... params)
        {
            DistributionFunc dist(std::forward<Params>(params)...);
            return dist(engine_);
        }

        template<typename NumericType>
        NumericType uniformDistribution(NumericType lower, NumericType upper)
        {
            if (lower == upper)
            {
                return lower;
            }
            return distribution<uniform_distribution<NumericType>>(lower, upper);
        }

        float uniformUnit() { return uniformDistribution(0.f, std::nextafter(1.f, FLT_MAX)); }

        float uniformSymmetry() { return uniformDistribution(-1.f, std::nextafter(1.f, FLT_MAX)); }

        bool bernoulliDistribution(float probability) { return distribution<std::bernoulli_distribution>(probability); }

        float normalDistribution(float mean, float stddev)
        {
            return distribution<std::normal_distribution<float>>(mean, stddev);
        }

        template<typename DistributionFunc, typename Range, typename... Params>
        void generator(Range&& range, Params&&... params)
        {
            // using ResultType = typename DistributionFunc::result_type;

            DistributionFunc dist(std::forward<Params>(params)...);
            return std::generate(std::begin(range), std::end(range), [&] { return dist(engine_); });
        }
    };

    template<typename DistributionFunc,
        typename RandomEngine = std::default_random_engine,
        typename SeedType = std::seed_seq>
        class DistRandomNumberGenerator
    {
        using ResultType = typename DistributionFunc::result_type;

    private:
        RandomEngine      engine_;
        DistributionFunc* dist_ = nullptr;

    public:
        template<typename... Params>
        explicit DistRandomNumberGenerator(SeedType&& seeding, Params&&...  /*params*/) : engine_(seeding)
        {
            // m_dist = CHAOS_NEW_T(DistributionFunc)(std::forward<Params>(params)...);
        }

        ~DistRandomNumberGenerator() { CHAOS_DELETE_T(dist_); }

        template<typename... Params>
        void seed(Params&&... params)
        {
            engine_.seed(std::forward<Params>(params)...);
        }

        ResultType next() { return (*dist_)(engine_); }
    };

    using DefaultRNG = RandomNumberGenerator<std::mt19937>;

}