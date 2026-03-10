#ifndef SINGLE_CURVE_POINT_CONSTS_HPP
#define SINGLE_CURVE_POINT_CONSTS_HPP

#include "SingleCurvePoint.hpp"

namespace SingleCurvePointConsts
{

constexpr SingleCurvePoint e2160_example_curve_point = { 0.0, 1.0, {-1.0, -1.0, 0.0} };
constexpr SingleCurvePoint e2160_example_curve_point_beg = { 0.0, 1.0, {-1.0, -1.0, 0.0} };
constexpr SingleCurvePoint e2160_example_curve_point_end = { 1.0, 1.0, {-1.0, -1.0, 0.0} };

constexpr SingleCurvePoint tw_and_pg_example_curve_point = { 0.0, 0.0, { 3.0, 3.0, 0.0} };
constexpr SingleCurvePoint tw_and_pg_example_curve_point_beg = { 0.0, 0.0, { 3.0, 3.0, 0.0} };
constexpr SingleCurvePoint tw_and_pg_example_curve_point_end = { 1.0, 0.0, { 3.0, 3.0, 0.0} };


};


#endif // !SINGLE_CURVE_POINT_CONSTS_HPP
