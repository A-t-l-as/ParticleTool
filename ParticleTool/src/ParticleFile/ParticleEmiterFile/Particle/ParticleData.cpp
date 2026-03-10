#include "ParticleData.hpp"

#include "../../ParticleFileVersionConsts.hpp"

#include "../../BasicParticleStructures/CurvesAndTeselatesUtils.hpp"

#include "../../BasicParticleStructures/TeselateAndCurvePairConsts.hpp"


using namespace std;

void ParticleData::ConvertTeselatesAndCurves
    (ParticleGlobals::particle_type_value& src, ParticleGlobals::particle_type_value& dst)
{
    if (src == dst)
    {
        return;
    }

    ParticleData& particle_data = *this;

    constexpr size_t tw_and_pg_scale_x_min_index = 6;
    constexpr size_t tw_and_pg_scale_z_min_index = 10;

    constexpr size_t e2160_rotation_z_min_index = 17;
    constexpr size_t e2160_rotation_y_min_index = 21;

    if (src == ParticleGlobals::particle_type_value::two_worlds_particle
        &&
        dst == ParticleGlobals::particle_type_value::particle_gen_particle)
    {
        return;
    }

    if (src == ParticleGlobals::particle_type_value::particle_gen_particle
        &&
        dst == ParticleGlobals::particle_type_value::two_worlds_particle)
    {
        return;
    }

    if (src == ParticleGlobals::particle_type_value::two_worlds_particle
        &&
        dst == ParticleGlobals::particle_type_value::e2160_particle)
    {
        for(size_t i = 7 ; i <= 9 ; ++i)
            CurvesAndTeselatesUtils::EraseTeselateAndCurveGroup(particle_data.curves_groups, particle_data.teselates_groups, i);

        return;
    }

    if (src == ParticleGlobals::particle_type_value::e2160_particle
        &&
        dst == ParticleGlobals::particle_type_value::two_worlds_particle)
    {
        for (size_t i = 9; i >= 7; --i)
            CurvesAndTeselatesUtils::InsertTeselateAndCurveGroup(particle_data.curves_groups, particle_data.teselates_groups, i);

        for(size_t i = tw_and_pg_scale_x_min_index; i <= tw_and_pg_scale_z_min_index; i += 2)
            particle_data.curves_groups.CopyCurveToDestination(i+1, i);

        return;
    }


    if (src == ParticleGlobals::particle_type_value::e2160_particle
        &&
        dst == ParticleGlobals::particle_type_value::ks_particles_emiter)
    {
        for(size_t i = 18; i <= 20 ; ++i)
            CurvesAndTeselatesUtils::EraseTeselateAndCurveGroup(particle_data.curves_groups,particle_data.teselates_groups, i);

        for (size_t i = 22; i <= ParticleFileVersionConsts::ks_particle_file_type.number_of_iel_in_particle - 1 /*26*/; ++i)
            CurvesAndTeselatesUtils::InsertTeselateAndCurveGroup(particle_data.curves_groups,
                                                 particle_data.teselates_groups, 
                                                 i,
                                                 TeselateAndCurvePairConsts::e2160_standard_teselate_and_curve_pair);

        return;
    }


    if (src == ParticleGlobals::particle_type_value::ks_particles_emiter
        &&
        dst == ParticleGlobals::particle_type_value::e2160_particle)
    {
        for (size_t i = ParticleFileVersionConsts::ks_particle_file_type.number_of_iel_in_particle - 1 /*26*/; i >= 22; --i)
            CurvesAndTeselatesUtils::EraseTeselateAndCurveGroup(particle_data.curves_groups,particle_data.teselates_groups, i);

        for (size_t i = 20; i >= 18; --i)
            CurvesAndTeselatesUtils::InsertTeselateAndCurveGroup(particle_data.curves_groups,
                                                 particle_data.teselates_groups, 
                                                 i,
                                                 TeselateAndCurvePairConsts::e2160_standard_teselate_and_curve_pair);

        for (size_t i = e2160_rotation_z_min_index; i <= e2160_rotation_y_min_index; i += 2)
            particle_data.curves_groups.CopyCurveToDestination(i + 1, i);

        return;
    }

}
