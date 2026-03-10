#ifndef TESELATE_AND_CURVE_PAIR_CONSTS_HPP
#define TESELATE_AND_CURVE_PAIR_CONSTS_HPP

#include "TeselateAndCurvePair.hpp"
#include "SingleCurvePointConsts.hpp"
#include "../../ParticleGlobals.hpp"

namespace TeselateAndCurvePairConsts
{

const TeselateAndCurvePair e2160_standard_teselate_and_curve_pair =
{
    { SingleCurvePointConsts::e2160_example_curve_point_beg, SingleCurvePointConsts::e2160_example_curve_point_end },
    ParticleGlobals::e2160_standard_curve_scalar,
    ParticleGlobals::e2160_standard_bonus_value,

    {},
    0.0,
    0
};


};


#endif // !TESELATE_AND_CURVE_PAIR_CONSTS_HPP
