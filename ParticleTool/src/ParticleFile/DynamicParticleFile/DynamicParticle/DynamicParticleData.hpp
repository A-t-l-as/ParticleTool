#ifndef DYNAMIC_PARTICLE_DATA_HPP
#define DYNAMIC_PARTICLE_DATA_HPP

#include <cstdint>
#include <string>
#include <vector>
#include "BasicDataStructures/TwoTypeArray.hpp"

struct DynamicParticleData
{

    // --------------
    std::string m_obj_name = {};
    // --------------

    uint32_t type = 0;
    uint32_t light_type = 0;

    static constexpr std::size_t frames_size = 5;
    int32_t frames[frames_size] = { 0 };

    static constexpr std::size_t time_size = 2;
    float time[time_size] = { 0.0 }; //wczesniej int64_t

    static constexpr std::size_t frames_ratio_size = 2;
    float frames_ratio[frames_ratio_size] = { 0.0 };

    static constexpr std::size_t size_size = 5;
    float size[size_size] = { 0.0 };

    static constexpr std::size_t size_2_size = 4;
    float size_2[size_2_size] = { 0.0 };

    float delta_size = 0.0;

    uint32_t null_space = 0;

    uint32_t additive = 0;

    static constexpr std::size_t light_size = 4;
    float light[light_size] = { 0.0, 0.0, 0.0, 1.0 };

    static constexpr std::size_t color_size = 4;
    float color[color_size] = { 0.0 };

    static constexpr std::size_t alpha_a_size = 2;
    static constexpr std::size_t alpha_b_size = 1;
    TwoTypeArray<float, alpha_a_size, uint32_t, alpha_b_size> alpha = {};

    static constexpr std::size_t scale_size = 2;
    float scale[scale_size] = { 0.0 };

    static constexpr std::size_t position_size = 3;
    float position[position_size] = { 0.0 };

    static constexpr std::size_t position_2_size = 3;
    float position_2[position_2_size] = { 0.0 };

    std::string mesh = {};
    std::string texture = {};

    uint32_t number_of_nested_particles = 0;

    std::vector<DynamicParticleData> children = {};

    uint32_t layer = 0;

};


#endif // !DYNAMIC_PARTICLE_DATA_HPP
