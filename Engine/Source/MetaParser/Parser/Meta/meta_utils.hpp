#pragma once
namespace Utils
{
    template<typename A, typename B>
    bool rangeEqual(A startA, A endA, B startB, B endB)//检查是否相同
    {
        while (startA != endA && startB != endB)
        {
            if (*startA != *startB)
                return false;

            ++startA;
            ++startB;
        }

        return (startA == endA) && (startB == endB);
    }