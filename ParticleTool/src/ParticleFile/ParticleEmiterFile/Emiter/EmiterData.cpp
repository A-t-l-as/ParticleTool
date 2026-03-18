#include "EmiterData.hpp"
#include "../../ParticleFileVersionConsts.hpp"

#include "../../BasicParticleStructures/CurvesAndTeselatesUtils.hpp"

#include "../../BasicParticleStructures/TeselateAndCurvePairConsts.hpp"


using namespace std;


void EmiterData::ConvertTeselatesAndCurves(ParticleGlobals::ENParticleTypeValue& src, ParticleGlobals::ENParticleTypeValue& dst)
{
        if (src == dst)
        {
            return;
        }

        EmiterData& emiter_data = *this;

        constexpr size_t e2160_rotation_y_min_index = 10;

        constexpr size_t tw_light_range_min_index = 20;
        constexpr size_t tw_light_intensity_min_index = 28;
        constexpr size_t tw_light_intensity_max_index = 29;

        constexpr size_t knightshift_light_intensity_index = 16;
        constexpr size_t knightshift_budget_index = 14;

        constexpr size_t pg_linked_min_max_surface_scale_x_index = 14;
        constexpr size_t tw_linked_min_max_light_intensity_index = 14;

        constexpr int64_t e2160_linked_min_max_rotation_y_index = 5;


        if (src == ParticleGlobals::ENParticleTypeValue::two_worlds_particle
            &&
            dst == ParticleGlobals::ENParticleTypeValue::particle_gen_particle)
        {
            CurvesAndTeselatesUtils::EraseSetOfTeselateAndCurveGroup(emiter_data.curves_groups, emiter_data.teselates_groups,
                                                     tw_light_intensity_min_index, tw_light_intensity_max_index);

            emiter_data.EraseLinkedMinMax(tw_linked_min_max_light_intensity_index);

            return;
        }

        if (src == ParticleGlobals::ENParticleTypeValue::particle_gen_particle
            &&
            dst == ParticleGlobals::ENParticleTypeValue::two_worlds_particle)
        {
            CurvesAndTeselatesUtils::InsertTeselateAndCurveGroup
                (emiter_data.curves_groups, emiter_data.teselates_groups, tw_light_intensity_min_index);

            CurvesAndTeselatesUtils::InsertTeselateAndCurveGroup
                (emiter_data.curves_groups, emiter_data.teselates_groups, tw_light_intensity_max_index);

            emiter_data.InsertLinkedMinMax(pg_linked_min_max_surface_scale_x_index);

            return;
        }


        if (src == ParticleGlobals::ENParticleTypeValue::two_worlds_particle
            &&
            dst == ParticleGlobals::ENParticleTypeValue::e2160_particle)
        {
            CurvesAndTeselatesUtils::CopyTeselateAndCurvePairToBackup(emiter_data.curves_groups,
                                                      emiter_data.teselates_groups,
                                                      emiter_data.convert_backup,
                                                      tw_light_intensity_min_index);

            for(size_t i = 21; i <= 24; ++i)
                CurvesAndTeselatesUtils::EraseTeselateAndCurveGroup(emiter_data.curves_groups, emiter_data.teselates_groups, i);


            CurvesAndTeselatesUtils::EraseSetOfTeselateAndCurveGroup(emiter_data.curves_groups,
                                                     emiter_data.teselates_groups,
                                                     tw_light_intensity_min_index - 4,
                                                     tw_light_intensity_max_index - 4);

            for (size_t i = 25; i <= 31; ++i)
                CurvesAndTeselatesUtils::EraseTeselateAndCurveGroup(emiter_data.curves_groups,
                                                    emiter_data.teselates_groups,
                                                    i);

            emiter_data.linked_min_max.resize
                (ParticleFileVersionConsts::e2160_particle_edit_file_type.number_of_linked_min_max_in_emiter);

            return;
        }

        if (src == ParticleGlobals::ENParticleTypeValue::e2160_particle
            &&
            dst == ParticleGlobals::ENParticleTypeValue::two_worlds_particle)
        {
            for
            (
                size_t i = ParticleFileVersionConsts::e2160_particle_edit_file_type.number_of_iel_in_emiter /*31*/ ;
                i >= 24 ;
                --i
            )
            {
                CurvesAndTeselatesUtils::InsertTeselateAndCurveGroup(emiter_data.curves_groups, emiter_data.teselates_groups, i);
            }

            CurvesAndTeselatesUtils::InsertTeselateAndCurveGroup(emiter_data.curves_groups,
                                                 emiter_data.teselates_groups,
                                                 tw_light_intensity_min_index - 4,
                                                 emiter_data.convert_backup);

            for (size_t i = 24; i >= 21; --i)
                CurvesAndTeselatesUtils::InsertTeselateAndCurveGroup(emiter_data.curves_groups, emiter_data.teselates_groups, i);

            for
            (
                size_t i = tw_light_range_min_index;
                i < ParticleFileVersionConsts::two_worlds_particle_edit_file_type.number_of_iel_in_emiter;
                i +=2
            )
            {
                emiter_data.curves_groups.CopyCurveToDestination(i+1, i);
            }


            emiter_data.linked_min_max.resize
            (
                ParticleFileVersionConsts::two_worlds_particle_edit_file_type.number_of_linked_min_max_in_emiter,
                ParticleGlobals::locked_linked_min_max
            );

            return;
        }


        if (src == ParticleGlobals::ENParticleTypeValue::e2160_particle
            &&
            dst == ParticleGlobals::ENParticleTypeValue::ks_particles_emiter)
        {
            for(size_t i = 1 ; i <= 6; ++i)
                CurvesAndTeselatesUtils::EraseTeselateAndCurveGroup(emiter_data.curves_groups, emiter_data.teselates_groups, i);



            CurvesAndTeselatesUtils::InsertTeselateAndCurveGroup(emiter_data.curves_groups,
                                                 emiter_data.teselates_groups,
                                                 knightshift_budget_index,
                                                 TeselateAndCurvePairConsts::e2160_standard_teselate_and_curve_pair);

            CurvesAndTeselatesUtils::InsertTeselateAndCurveGroup(emiter_data.curves_groups,
                                                 emiter_data.teselates_groups,
                                                 knightshift_light_intensity_index,
                                                 emiter_data.convert_backup);

            for(int64_t i = e2160_linked_min_max_rotation_y_index; i >= 0 ; --i)
                emiter_data.EraseLinkedMinMax(i);

            return;
        }


        if (src == ParticleGlobals::ENParticleTypeValue::ks_particles_emiter
            &&
            dst == ParticleGlobals::ENParticleTypeValue::e2160_particle)
        {
            CurvesAndTeselatesUtils::CopyTeselateAndCurvePairToBackup(emiter_data.curves_groups,
                                                      emiter_data.teselates_groups,
                                                      emiter_data.convert_backup,
                                                      knightshift_light_intensity_index);

            CurvesAndTeselatesUtils::EraseTeselateAndCurveGroup
                (emiter_data.curves_groups, emiter_data.teselates_groups, knightshift_light_intensity_index);

            CurvesAndTeselatesUtils::EraseTeselateAndCurveGroup
                (emiter_data.curves_groups, emiter_data.teselates_groups, knightshift_budget_index);

            for (size_t i = 6; i >= 1; --i)
                CurvesAndTeselatesUtils::InsertTeselateAndCurveGroup(emiter_data.curves_groups,
                                                     emiter_data.teselates_groups,
                                                     i,
                                                     TeselateAndCurvePairConsts::e2160_standard_teselate_and_curve_pair);

            for (size_t i = 0; i <= e2160_rotation_y_min_index; i += 2)
                emiter_data.curves_groups.CopyCurveToDestination(i + 1, i);

            for(int64_t i = 0 ; i <= e2160_linked_min_max_rotation_y_index; ++i)
                emiter_data.InsertLinkedMinMax(i);

            return;
        }

}




