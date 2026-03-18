#ifndef PARTICLE_DATA_HPP
#define PARTICLE_DATA_HPP

#include <string>
#include <vector>
#include <cstdint>

#include "BasicDataStructures/TwoTypeArray.hpp"

#include "../../BasicParticleStructures/TeselateAndCurvePair.hpp"
#include "../../BasicParticleStructures/ParticleCurvesAndTeselatesBase.hpp"

class ParticleData : public ParticleCurvesAndTeselatesBase
{
public:

    std::string particle_name = {};

    float start_time = 0.0;
    float time = 0.0;

    uint32_t coordinates = 0;
    uint32_t type = 0;

    std::string mesh = {};

    // face a, b, b, b, b, b
    static constexpr std::size_t face_a_size = 1;
    static constexpr std::size_t face_b_size = 5;
    TwoTypeArray<uint32_t, face_a_size, float, face_b_size> face = {};

    float triangle_a = 0.0;
    float screen_depth_offset = 0.0;

    uint32_t multiply_dxy_by_prt_scale_switch = 0;

    // trail a, b
    static constexpr std::size_t trail_a_size = 1;
    static constexpr std::size_t trail_b_size = 1;
    TwoTypeArray<float, trail_a_size, uint32_t, trail_b_size> trail = {};

    float y_texture_mul = 0.0;

    std::vector<std::string> textures = {};

    std::vector<std::string> bump_textures = {};

    // texAnim a, a, a, a, a, a, a, a, a, b, a
    static constexpr std::size_t tex_anim_a_size = 10;
    static constexpr std::size_t tex_anim_b_size = 1;
    TwoTypeArray<uint32_t, tex_anim_a_size, float, tex_anim_b_size> tex_anim = {};


    static constexpr std::size_t coordinates_ltrb_size = 4;
    float coordinates_ltrb[coordinates_ltrb_size] = { 0.0 };

    uint32_t distortion_particle_switch = 0;

    uint32_t x_mirrored = 0;
    uint32_t y_mirrored = 0;

    uint32_t color_rand_type = 0;

    uint32_t unknown_value_1 = 0;
    uint32_t unknown_value_2 = 0;
    uint32_t unknown_value_3 = 0;

    static constexpr std::size_t trajectory_size = 2;
    uint32_t trajectory[trajectory_size] = { 0 };

    // gravity a, a, a, a, a, a, a, b
    static constexpr std::size_t gravity_a_size = 7;
    static constexpr std::size_t gravity_b_size = 1;
    TwoTypeArray<float, gravity_a_size, uint32_t, gravity_b_size> gravity = {};

    uint32_t enable_light = 0;

    uint32_t gravity_rot_from_trajectory_z_switch = 0;
    uint32_t gravity_rot_from_trajectory_x_switch = 0;
    uint32_t gravity_rot_from_trajectory_y_switch = 0;

    uint32_t dissappears_on_ground = 0 ;

    uint32_t create_on_ground_switch = 0;
    uint32_t trajectory_z_from_ground = 0;


    static constexpr std::size_t scale_a_size = 3;
    static constexpr std::size_t scale_b_size = 1;
    static constexpr std::size_t scales_size = 3;
    TwoTypeArray<float, scale_a_size, uint32_t, scale_b_size> scales[scales_size] = {};

    float scales_end = 0;

    uint32_t all_teselate_zero_mask = 0;

    uint32_t layer = 0;

    //------

    TeselateAndCurvePair convert_backup = {};



void ConvertTeselatesAndCurves
        (ParticleGlobals::ENParticleTypeValue& src, ParticleGlobals::ENParticleTypeValue& dst) override;



};


#endif // !PARTICLE_DATA_HPP
