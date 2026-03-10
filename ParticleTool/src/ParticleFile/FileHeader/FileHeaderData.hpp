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

    ParticleGlobals::particle_type_value particle_file_type =
        ParticleGlobals::particle_type_value::not_particle;

    std::string guid = MyGuid().ToString();

};

#endif // !FILE_HEADER_DATA_HPP
