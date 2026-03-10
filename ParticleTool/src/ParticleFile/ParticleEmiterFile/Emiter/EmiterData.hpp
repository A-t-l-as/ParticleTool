#ifndef EMITER_DATA_HPP
#define EMITER_DATA_HPP

#include <cstdint>
#include <string>
#include <vector>

#include "BasicDataStructures/TwoTypeArray.hpp"
#include "../../BasicParticleStructures/TeselateAndCurvePair.hpp"

#include "../../BasicParticleStructures/ParticleCurvesAndTeselatesBase.hpp"

class EmiterData : public ParticleCurvesAndTeselatesBase
{
public:

    std::string emiter_name = {};
    float start_time = 0.0;
    float time = 0.0;

    uint32_t coordinates = 0;
    uint32_t budget_type = 0;

    std::vector<std::string> slot_strings = {}; //ok

    static constexpr std::size_t surface_size = 3; //ok
    uint32_t surface[surface_size] = { 0 }; //ok
    uint32_t sun_ray_direction_switch = 0;


    static constexpr std::size_t sphere_size = 5; //ok
    float sphere[sphere_size] = { 0.0 }; //ok

    // cubic a, a, a, b
    static constexpr std::size_t cubic_a_size = 3; //ok
    static constexpr std::size_t cubic_b_size = 1; //ok
    TwoTypeArray<float, cubic_a_size, uint32_t, cubic_b_size> cubic = {}; //ok

    // plane a, a, b
    static constexpr std::size_t plane_a_size = 2; //ok
    static constexpr std::size_t plane_b_size = 1; //ok
    TwoTypeArray<float, plane_a_size, uint32_t, plane_b_size> plane = {}; //ok
    uint32_t use_color_switch = 0;

    std::string texture = {};

    uint32_t create_on_ground = 0;
    uint32_t trajectory_z_from_ground = 0;

    static constexpr std::size_t rotation_size = 3; //ok
    uint32_t rotation[rotation_size] = { 0 }; //ok


    uint32_t enable_light = 0;
    float umbra_distance_mul = 0.0;


    // only for two worlds:
    //------------------------
    uint32_t cast_shadows = 0;
    //------------------------

    static constexpr std::size_t scales_a_size = 14; //ok
    static constexpr std::size_t scales_b_size = 2; //ok
    TwoTypeArray<float, scales_a_size, uint32_t, scales_b_size> scales = {}; //ok

    uint32_t move_end_of_laser_switch = 0;
    uint32_t attach_to_end_of_laser_switch = 0;

    static constexpr std::size_t random_seed_size = 2; //ok
    uint32_t random_seed[random_seed_size] = { 0 }; //ok

    uint32_t unknown_value_1 = 0;
    uint32_t unknown_value_2 = 0;
    uint32_t unknown_value_3 = 0;
    uint32_t unknown_value_4 = 0;
    uint32_t unknown_value_5 = 0;

    uint32_t all_teselate_zero_mask = 0;

    //----------------------

    TeselateAndCurvePair convert_backup = {};

//----------------------------------------------

void ConvertTeselatesAndCurves
    (ParticleGlobals::particle_type_value& src, ParticleGlobals::particle_type_value& dst) override;





};



#endif // EMITERDATA_HPP
