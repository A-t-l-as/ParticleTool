#include "EffectData.hpp"

#include "../../ParticleFileVersionConsts.hpp"

#include "../../BasicParticleStructures/CurvesAndTeselatesUtils.hpp"

#include "../../BasicParticleStructures/TeselateAndCurvePairConsts.hpp"

using namespace std;

void EffectData::ConvertTeselatesAndCurves(ParticleGlobals::ENParticleTypeValue& src, ParticleGlobals::ENParticleTypeValue& dst)
{
    if (src == dst)
    {
        return;
    }

    if (src == ParticleGlobals::ENParticleTypeValue::two_worlds_particle
        &&
        dst == ParticleGlobals::ENParticleTypeValue::particle_gen_particle)
    {
        return;
    }

    if (src == ParticleGlobals::ENParticleTypeValue::particle_gen_particle
        &&
        dst == ParticleGlobals::ENParticleTypeValue::two_worlds_particle)
    {
        return;
    }

    EffectData& effect_data = *this;

    if (src == ParticleGlobals::ENParticleTypeValue::two_worlds_particle
        &&
        dst == ParticleGlobals::ENParticleTypeValue::e2160_particle)
    {
        effect_data.linked_min_max.resize
            (ParticleFileVersionConsts::e2160_particle_edit_file_type.number_of_linked_min_max_in_effect,
                                          ParticleGlobals::locked_linked_min_max);

        effect_data.curves_groups.Resize(ParticleFileVersionConsts::e2160_particle_edit_file_type.number_of_iel_in_effect);

        effect_data.teselates_groups.Resize(ParticleFileVersionConsts::e2160_particle_edit_file_type.number_of_iel_in_effect);

        return;
    }

    if (src == ParticleGlobals::ENParticleTypeValue::e2160_particle
        &&
        dst == ParticleGlobals::ENParticleTypeValue::two_worlds_particle)
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


    if (src == ParticleGlobals::ENParticleTypeValue::e2160_particle
        &&
        dst == ParticleGlobals::ENParticleTypeValue::ks_particles_emiter)
    {
        return;
    }


    if (src == ParticleGlobals::ENParticleTypeValue::ks_particles_emiter
        &&
        dst == ParticleGlobals::ENParticleTypeValue::e2160_particle)
    {
        return;
    }

}


