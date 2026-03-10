#ifndef CURVES_AND_TESELATES_UTILS_HPP
#define CURVES_AND_TESELATES_UTILS_HPP

#include <cmath>
#include <vector>
#include <string>
#include <sstream>
#include "AllCurvesGroups.hpp"
#include "AllTeselatesGroups.hpp"
#include "Utils/Misc.hpp"
#include "TeselateAndCurvePair.hpp"

class CurvesAndTeselatesUtils
{
public:

static void ExportCurvesAndTeselatesToSs
(
    const AllCurvesGroups& curves_groups,
    const AllTeselatesGroups& teselates_groups,
    const std::vector<std::string>& labels,
    std::stringstream& output
)
{
    const size_t teselates_groups_teselates_size = teselates_groups.teselates.size();

    for (size_t i = 0; i < teselates_groups_teselates_size; ++i)
    {
        const auto& single_curve = curves_groups.curves[i];

        Misc::Margin(output, Globals::two_quads); output << "curve"
               << " "
               << single_curve.size()
               << " "
               << curves_groups.curve_scalars[i]
               << " "
               << labels[i]
               << std::endl;

        Misc::Margin(output, Globals::two_quads); output << "{" << std::endl;


        for (const auto& single_curve_point : single_curve)
        {
            Misc::Margin(output, Globals::three_quads); output << single_curve_point.x << ", "
                   << single_curve_point.y << ", "
                   << single_curve_point.bonus_data[0] << ", "
                   << single_curve_point.bonus_data[1] << ", "
                   << single_curve_point.bonus_data[2] << std::endl;
        }

        Misc::Margin(output, Globals::two_quads); output << "}" << std::endl;


        const auto& teselate_vector = teselates_groups.teselates[i];

        Misc::Margin(output, Globals::two_quads); output << "teselate"
               << " "
               << teselate_vector.size()
               << " "
               << teselates_groups.teselate_flags[i]
               << " "
               << teselates_groups.iel_scalars[i]
               << " "
               << labels[i]
               << std::endl;

        Misc::Margin(output, Globals::two_quads); output << "{" << std::endl;

        for (const auto& single_teselate : teselate_vector)
        {
            Misc::Margin(output, Globals::three_quads); output << single_teselate << std::endl;
        }

        Misc::Margin(output, Globals::two_quads); output << "}" << std::endl;
    }

}


static void CopyTeselateAndCurvePairToBackup
(
    const AllCurvesGroups& curves_groups,
    const AllTeselatesGroups& teselates_groups,
    TeselateAndCurvePair& backup,
    size_t index
)
{
    backup.curve = curves_groups.curves[index];
    backup.curve_bonus_value = curves_groups.curve_bonus_values[index];
    backup.curve_scalar = curves_groups.curve_scalars[index];
    backup.iel_scalar = teselates_groups.iel_scalars[index];
    backup.teselate = teselates_groups.teselates[index];
    backup.teselate_flag = teselates_groups.teselate_flags[index];
}


static void InsertTeselateAndCurveGroup
(
    AllCurvesGroups& curves_groups,
    AllTeselatesGroups& teselates_groups,
    size_t index,
    TeselateAndCurvePair arg_tes_and_curve = TeselateAndCurvePair()
)
{
    curves_groups.curves.insert(curves_groups.curves.begin() + index, arg_tes_and_curve.curve);
    curves_groups.curve_scalars.insert(curves_groups.curve_scalars.begin() + index, arg_tes_and_curve.curve_scalar);
    curves_groups.curve_bonus_values.insert(curves_groups.curve_bonus_values.begin() + index, arg_tes_and_curve.curve_bonus_value);

    teselates_groups.teselates.insert(teselates_groups.teselates.begin() + index, arg_tes_and_curve.teselate);
    teselates_groups.iel_scalars.insert(teselates_groups.iel_scalars.begin() + index, arg_tes_and_curve.iel_scalar);
    teselates_groups.teselate_flags.insert(teselates_groups.teselate_flags.begin() + index, arg_tes_and_curve.teselate_flag);

}


static void EraseTeselateAndCurveGroup
(
    AllCurvesGroups& curves_groups,
    AllTeselatesGroups& teselates_groups,
    size_t index
)
{
    curves_groups.curves.erase(curves_groups.curves.begin() + index);

    curves_groups.curve_scalars.erase(curves_groups.curve_scalars.begin() + index);

    curves_groups.curve_bonus_values.erase(curves_groups.curve_bonus_values.begin() + index);

    teselates_groups.teselates.erase(teselates_groups.teselates.begin() + index);

    teselates_groups.iel_scalars.erase(teselates_groups.iel_scalars.begin() + index);

    teselates_groups.teselate_flags.erase(teselates_groups.teselate_flags.begin() + index);
}


static void EraseSetOfTeselateAndCurveGroup
(
    AllCurvesGroups& curves_groups,
    AllTeselatesGroups& teselates_groups,
    size_t index_from,
    size_t index_to
)
{
    curves_groups.curves.erase(curves_groups.curves.begin() + index_from,
                               curves_groups.curves.begin() + index_to + 1);

    curves_groups.curve_scalars.erase(curves_groups.curve_scalars.begin() + index_from,
                                      curves_groups.curve_scalars.begin() + index_to + 1);

    curves_groups.curve_bonus_values.erase(curves_groups.curve_bonus_values.begin() + index_from,
                                           curves_groups.curve_bonus_values.begin() + index_to + 1);


    teselates_groups.teselates.erase(teselates_groups.teselates.begin() + index_from,
                                     teselates_groups.teselates.begin() + index_to + 1);

    teselates_groups.iel_scalars.erase(teselates_groups.iel_scalars.begin() + index_from,
                                       teselates_groups.iel_scalars.begin() + index_to + 1);

    teselates_groups.teselate_flags.erase(teselates_groups.teselate_flags.begin() + index_from,
                                          teselates_groups.teselate_flags.begin() + index_to + 1);
}



static void MakeCurves
(
    const AllTeselatesGroups& teselates_groups,
    AllCurvesGroups& curves_groups,
    const SingleCurvePoint& template_curve_point
)
{
    constexpr long double domain_begin = 0.0;
    constexpr long double domain_end = 1.0;

    SingleCurvePoint single_curve_point = template_curve_point;

    std::vector<SingleCurvePoint> single_curve_vector = {};

    const size_t teselates_groups_teselates_size = teselates_groups.teselates.size();
    for (size_t j = 0; j < teselates_groups_teselates_size; ++j)
    {
        const auto& line = teselates_groups.teselates[j];

        if (line.empty() == true)
        {
            single_curve_point = template_curve_point;
            single_curve_vector.push_back(single_curve_point);

            single_curve_point.x = domain_end;
            single_curve_vector.push_back(single_curve_point);

            curves_groups.curves.push_back(single_curve_vector);
            curves_groups.curve_scalars.push_back(ParticleGlobals::e2160_standard_curve_scalar);
            curves_groups.curve_bonus_values.push_back(ParticleGlobals::e2160_standard_bonus_value);

            single_curve_vector.clear();
            single_curve_point = template_curve_point;

            continue;
        }

        long double sampleRate = sqrt(line.size());

        if ( (static_cast<size_t>(sampleRate) != 0) && (line.size() % static_cast<size_t>(sampleRate) == 0) )
        {
            sampleRate = sqrt(line.size() + 1.0);
        }

        //ratio:
        long double sampleRatio = line.size() / sampleRate;
        long double h = (domain_end - domain_begin) / sampleRate;

        for (long double i = 0; i < sampleRate; ++i)
        {
            auto&& calc = i * sampleRatio;
            auto&& arg_x = i * h;

            if (calc >= line.size())
                throw;

            if (arg_x >= domain_end)
                throw;

            if (i == domain_begin)
            {
                single_curve_point.x = domain_begin;
                single_curve_point.y = line[0];
            }

            if (sampleRate < i + 1.0)
            {
                single_curve_point.x = domain_end;
                single_curve_point.y = line[line.size() - 1];
            }

            if ((!(i == domain_begin)) && (!(sampleRate < i + 1.0)))
            {
                single_curve_point.x = static_cast<float>(arg_x);
                single_curve_point.y = line[ static_cast<std::size_t>(calc) ];
            }

            single_curve_vector.push_back(single_curve_point);
        }

        curves_groups.curves.push_back(std::move(single_curve_vector));
        single_curve_vector.clear();

        curves_groups.curve_scalars.push_back
            (ParticleGlobals::ks_example_curve_scalar);

        curves_groups.curve_bonus_values.push_back
            (ParticleGlobals::e2160_standard_bonus_value);


    }

}



};


#endif // !CURVES_AND_TESELATES_UTILS_HPP
