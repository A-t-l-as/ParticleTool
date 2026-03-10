#ifndef TESELATE_AND_CURVE_PAIR_HPP
#define TESELATE_AND_CURVE_PAIR_HPP

#include <vector>
#include <cstdint>

#include "SingleCurvePoint.hpp"
#include "SingleCurvePointConsts.hpp"

struct TeselateAndCurvePair
{
    std::vector<SingleCurvePoint> curve =
    {
        SingleCurvePointConsts::tw_and_pg_example_curve_point_beg,
        SingleCurvePointConsts::tw_and_pg_example_curve_point_end
    };

    float curve_scalar = 0.0;
    float curve_bonus_value = 0.0;

    std::vector<float> teselate = {};
    float iel_scalar = 0.0;
    uint32_t teselate_flag = 0;

};



#endif // !TESELATE_AND_CURVE_PAIR_HPP
