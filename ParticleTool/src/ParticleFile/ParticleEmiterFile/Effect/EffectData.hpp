#ifndef EFFECT_DATA_HPP
#define EFFECT_DATA_HPP

#include <cstdint>
#include <string>
#include "BasicDataStructures/TwoTypeArray.hpp"

#include "../../BasicParticleStructures/ParticleCurvesAndTeselatesBase.hpp"

class EffectData : public ParticleCurvesAndTeselatesBase
{
public:

    uint32_t particle_2D_switch = 0;
    uint32_t width = 0;
    uint32_t height = 0;

    //only for e2160:
    uint32_t e2160_effect_scale = 0;

    float start_time = 0.0;
    float time = 0.0;
    uint32_t loops = 0;

    static constexpr std::size_t scale_a_size = 3; //ok
    static constexpr std::size_t scale_b_size = 1; //ok
    static constexpr std::size_t scales_size = 2; //ok
    TwoTypeArray<float, scale_a_size, uint32_t, scale_b_size> scales[scales_size] = {}; //ok

    std::string annotation = {};

    //-------------------------------
    uint32_t unknown_value_1 = 0;
    uint32_t unknown_value_2 = 0;
    //-------------------------------

    uint32_t all_teselate_zero_mask = 0;


void ConvertTeselatesAndCurves
        (ParticleGlobals::particle_type_value& src, ParticleGlobals::particle_type_value& dst) override;



};


#endif // !EFFECT_DATA_HPP
