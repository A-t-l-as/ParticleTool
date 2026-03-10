#include "EffectData.hpp"

#include "../../ParticleFileVersionConsts.hpp"

#include "../../BasicParticleStructures/CurvesAndTeselatesUtils.hpp"

#include "../../BasicParticleStructures/TeselateAndCurvePairConsts.hpp"

using namespace std;

void EffectData::ConvertTeselatesAndCurves(ParticleGlobals::particle_type_value& src, ParticleGlobals::particle_type_value& dst)
{
    if (src == dst)
    {
        return;
    }

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

    EffectData& effect_data = *this;

    if (src == ParticleGlobals::particle_type_value::two_worlds_particle
        &&
        dst == ParticleGlobals::particle_type_value::e2160_particle)
    {
        effect_data.linked_min_max.resize
            (ParticleFileVersionConsts::e2160_particle_edit_file_type.number_of_linked_min_max_in_effect,
                                          ParticleGlobals::locked_linked_min_max);

        /*
        effect_data.curves_groups.curves.resize
            (ParticleFileVersionConsts::e2160_particle_edit_file_type.number_of_iel_in_effect);

        effect_data.curves_groups.curve_scalars.resize
            (ParticleFileVersionConsts::e2160_particle_edit_file_type.number_of_iel_in_effect);

        effect_data.curves_groups.curve_bonus_values.resize
            (ParticleFileVersionConsts::e2160_particle_edit_file_type.number_of_iel_in_effect);
        */

        effect_data.curves_groups.Resize(ParticleFileVersionConsts::e2160_particle_edit_file_type.number_of_iel_in_effect);

        /*
        effect_data.teselates_groups.teselates.resize
            (ParticleFileVersionConsts::e2160_particle_edit_file_type.number_of_iel_in_effect);

        effect_data.teselates_groups.iel_scalars.resize
            (ParticleFileVersionConsts::e2160_particle_edit_file_type.number_of_iel_in_effect);

        effect_data.teselates_groups.teselate_flags.resize
            (ParticleFileVersionConsts::e2160_particle_edit_file_type.number_of_iel_in_effect);
        */

        effect_data.teselates_groups.Resize(ParticleFileVersionConsts::e2160_particle_edit_file_type.number_of_iel_in_effect);

        return;
    }

    if (src == ParticleGlobals::particle_type_value::e2160_particle
        &&
        dst == ParticleGlobals::particle_type_value::two_worlds_particle)
    {
        for
        (
            size_t i = 0;
            i < ParticleFileVersionConsts::two_worlds_particle_edit_file_type.number_of_iel_in_effect;
            ++i
        )
        {
            CurvesAndTeselatesUtils::InsertTeselateAndCurveGroup(effect_data.curves_groups,
                                                 effect_data.teselates_groups,
                                                 i,
                                                 TeselateAndCurvePairConsts::e2160_standard_teselate_and_curve_pair);
        }

        effect_data.linked_min_max.resize
        (
            ParticleFileVersionConsts::two_worlds_particle_edit_file_type.number_of_linked_min_max_in_effect,
            ParticleGlobals::locked_linked_min_max
        );

        return;
    }


    if (src == ParticleGlobals::particle_type_value::e2160_particle
        &&
        dst == ParticleGlobals::particle_type_value::ks_particles_emiter)
    {
        return;
    }


    if (src == ParticleGlobals::particle_type_value::ks_particles_emiter
        &&
        dst == ParticleGlobals::particle_type_value::e2160_particle)
    {
        return;
    }

}


