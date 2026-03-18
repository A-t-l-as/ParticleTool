#ifndef FILE_HEADER_DATA_HPP
#define FILE_HEADER_DATA_HPP

#include <string>
#include <cstdint>
#include "../../ParticleGlobals.hpp"
#include "System/MyGuid.hpp"


struct FileHeaderData
{
    constexpr const unsigned int static c_header_size = 4;
    uint8_t header[c_header_size] = {0};

    ParticleGlobals::ENParticleTypeValue particle_file_type =
        ParticleGlobals::ENParticleTypeValue::not_particle;

    std::string guid = MyGuid().ToString();

};

#endif // !FILE_HEADER_DATA_HPP
