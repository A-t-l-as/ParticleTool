#ifndef PARTICLE_FILE_VERSION_INFO_HPP
#define PARTICLE_FILE_VERSION_INFO_HPP

#include <cstdint>
#include <sstream>

#include "../ParticleGlobals.hpp"

struct ParticleFileVersionInfo
{
    ParticleGlobals::particle_type_value particle_version =
        ParticleGlobals::particle_type_value::not_particle;


    size_t custom_data_block_size = 0;

    size_t number_of_iel_in_effect = 0;
    size_t number_of_iel_in_emiter = 0;
    size_t number_of_iel_in_particle = 0;

    uint32_t number_of_linked_min_max_in_effect = 0;
    uint32_t number_of_linked_min_max_in_emiter = 0;
    uint32_t number_of_linked_min_max_in_particle = 0;

    int size_of_end_bonus_data = 0;


    ParticleGlobals::old_dynamic_particle_type_value dynamic_particle_version =
        ParticleGlobals::old_dynamic_particle_type_value::not_old_dynamic_particle;

    std::string ToString()
    {
        std::stringstream ss;

        ss <<
                "ParticleGlobals::particle_type_value particle_version = " << static_cast<int>(this->particle_version)
           << std::endl <<
        "size_t custom_data_block_size = "  << this->custom_data_block_size << std::endl<<
        "size_t number_of_iel_in_effect = "  << this->number_of_iel_in_effect << std::endl<<
        "size_t number_of_iel_in_emiter = "  << this->number_of_iel_in_emiter << std::endl<<
        "size_t number_of_iel_in_particle = "  << this->number_of_iel_in_particle << std::endl<<
        "uint32_t number_of_linked_min_max_in_effect = "  << this->number_of_linked_min_max_in_effect << std::endl<<
        "uint32_t number_of_linked_min_max_in_emiter = "  << this->number_of_linked_min_max_in_emiter << std::endl<<
        "uint32_t number_of_linked_min_max_in_particle = "  << this->number_of_linked_min_max_in_particle << std::endl<<
        "int size_of_end_bonus_data = " << this->size_of_end_bonus_data << std::endl<<
            "ParticleGlobals::old_dynamic_particle_type_value dynamic_particle_version = "
           << static_cast<int>(this->dynamic_particle_version) << std::endl;

        return ss.str();
    }
};


#endif // !PARTICLE_FILE_VERSION_INFO_HPP
