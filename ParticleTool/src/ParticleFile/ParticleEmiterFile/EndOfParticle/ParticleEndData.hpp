#ifndef PARTICLE_END_DATA_HPP
#define PARTICLE_END_DATA_HPP

#include <cstdint>

struct ParticleEndData
{
    static constexpr std::size_t end_particle_values_size = 18;
    float end_particle_values[end_particle_values_size] = { 0.0 };
    uint32_t gamerate = 0;
};


#endif // !PARTICLE_END_DATA_HPP
