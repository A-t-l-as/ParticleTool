#ifndef SINGLE_CURVE_POINT_HPP
#define SINGLE_CURVE_POINT_HPP

#include <cstddef>

struct SingleCurvePoint
{
    float x = 0;
    float y = 0;

    static constexpr std::size_t bonus_data_size = 3;
    float bonus_data[bonus_data_size] = { 0.0 };
};


#endif // !SINGLE_CURVE_POINT_HPP
