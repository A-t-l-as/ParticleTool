#ifndef PAIR_PARTICLE_EMITER_DATA_HPP
#define PAIR_PARTICLE_EMITER_DATA_HPP

#include <cstdint>
#include <string>
#include <vector>

#include "BasicDataStructures/TwoTypeArray.hpp"

struct PairParticleEmiterData
{

    std::string group_name = {};

    std::string annotation = {};

    std::string emiter_name = {};
    std::string particle_name = {};

    std::uint32_t emiter_index = 0;
    std::uint32_t particle_index = 0;

    float time = 0.0;

    // loopedemission a, a, a, b
    static constexpr std::size_t looped_emission_a_size = 3; //ok
    static constexpr std::size_t looped_emission_b_size = 1; //ok
    TwoTypeArray<uint32_t, looped_emission_a_size, float, looped_emission_b_size> looped_emission = {}; //ok

    uint32_t simple_one_particle_switch = 0;
    uint32_t mask_2d_switch = 0;
    uint32_t hardware_cursor_switch = 0;
    uint32_t stop_in_partial_pause_switch = 0;
    uint32_t finish_missile_switch = 0;

    uint32_t emits_groups_switch = 0;

    std::vector<std::string> emits_groups = {};

    uint32_t only_emited_by_other_emiter_switch = 0;
    uint32_t draw_particle_emiter = 0;

};


#endif // !PAIR_PARTICLE_EMITER_DATA_HPP
