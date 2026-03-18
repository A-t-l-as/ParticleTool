#ifndef PARTICLE_FILE_VERSION_CONSTS_HPP
#define PARTICLE_FILE_VERSION_CONSTS_HPP

#include "ParticleFileVersionInfo.hpp"
#include "../ParticleGlobals.hpp"

namespace ParticleFileVersionConsts
{

const ParticleFileVersionInfo earth2150_dynamic_file_type =
{
        ParticleGlobals::ENParticleTypeValue::dynamic_particle,  //particle_version
        ParticleGlobals::size_of_e2150_root_data_block / sizeof(uint32_t) ,  //custom_data_block_size

        0, // number_of_iel_in_effect
        0, // number_of_iel_in_emiter
        0, // number_of_iel_in_particle

        0, // number_of_linked_min_max_in_effect
        0, // number_of_linked_min_max_in_emiter
        0, // number_of_linked_min_max_in_particle

        0, // size_of_end_bonus_data
        ParticleGlobals::ENOldDynamicParticleTypeValue::e2150_old_dynamic_particle
};


const ParticleFileVersionInfo ww3_or_heli_heroes_dynamic_file_type =
{
        ParticleGlobals::ENParticleTypeValue::dynamic_particle,  //particle_version
        ParticleGlobals::size_of_ww3_or_heli_heroes_root_data_block / sizeof(uint32_t) ,  //custom_data_block_size

        0, // number_of_iel_in_effect
        0, // number_of_iel_in_emiter
        0, // number_of_iel_in_particle

        0, // number_of_linked_min_max_in_effect
        0, // number_of_linked_min_max_in_emiter
        0, // number_of_linked_min_max_in_particle

        0, // size_of_end_bonus_data
        ParticleGlobals::ENOldDynamicParticleTypeValue::ww3_of_hh_old_dynamic_particle
};

const ParticleFileVersionInfo ww2_or_fa_or_pc2_dynamic_file_type =
{
        ParticleGlobals::ENParticleTypeValue::dynamic_particle,  //particle_version
        ParticleGlobals::size_of_ww2_or_fa_or_pc2_root_data_block / sizeof(uint32_t) ,  //custom_data_block_size

        0, // number_of_iel_in_effect
        0, // number_of_iel_in_emiter
        0, // number_of_iel_in_particle

        0, // number_of_linked_min_max_in_effect
        0, // number_of_linked_min_max_in_emiter
        0, // number_of_linked_min_max_in_particle

        0, // size_of_end_bonus_data
        ParticleGlobals::ENOldDynamicParticleTypeValue::ww2_or_fa_or_pc2_old_dynamic_particle
};


const ParticleFileVersionInfo ks_dynamic_file_type =
{
        ParticleGlobals::ENParticleTypeValue::dynamic_particle,  //particle_version
        ParticleGlobals::size_of_ks_root_data_block / sizeof(uint32_t) ,  //custom_data_block_size

        0, // number_of_iel_in_effect
        0, // number_of_iel_in_emiter
        0, // number_of_iel_in_particle

        0, // number_of_linked_min_max_in_effect
        0, // number_of_linked_min_max_in_emiter
        0, // number_of_linked_min_max_in_particle

        0, // size_of_end_bonus_data
        ParticleGlobals::ENOldDynamicParticleTypeValue::ks_old_dynamic_particle
};


const ParticleFileVersionInfo ks_particle_file_type =
{
        ParticleGlobals::ENParticleTypeValue::ks_particles_emiter,  //particle_version
        ParticleGlobals::size_of_ks_root_data_block / sizeof(uint32_t) ,  //custom_data_block_size

        0, // number_of_iel_in_effect
        27, // number_of_iel_in_emiter
        27, // number_of_iel_in_particle

        0, // number_of_linked_min_max_in_effect
        4, // number_of_linked_min_max_in_emiter
        8, // number_of_linked_min_max_in_particle

        0, // size_of_end_bonus_data
        ParticleGlobals::ENOldDynamicParticleTypeValue::not_old_dynamic_particle
};


const ParticleFileVersionInfo particle_gen_file_type =
{
        ParticleGlobals::ENParticleTypeValue::particle_gen_particle,
        0,

        12,
        42,
        28,

        12 / 2,
        42 / 2,
        28 / 2,

        16,
        ParticleGlobals::ENOldDynamicParticleTypeValue::not_old_dynamic_particle
};

const ParticleFileVersionInfo two_worlds_particle_edit_file_type =
{
        ParticleGlobals::ENParticleTypeValue::two_worlds_particle,
        0,

        12,
        44,
        28,

        12 / 2,
        44 / 2,
        28 / 2,

        16,
        ParticleGlobals::ENOldDynamicParticleTypeValue::not_old_dynamic_particle
};

const ParticleFileVersionInfo e2160_particle_edit_file_type =
{
        ParticleGlobals::ENParticleTypeValue::e2160_particle, //particle_version
        0, //custom_data_block_size

        0, //number_of_iel_in_effect
        31, //number_of_iel_in_emiter
        25, //number_of_iel_in_particle

        0, //number_of_linked_min_max_in_effect
        10, //number_of_linked_min_max_in_emiter
        11, //number_of_linked_min_max_in_particle

        18, //size_of_end_bonus_data
        ParticleGlobals::ENOldDynamicParticleTypeValue::not_old_dynamic_particle
};



};


#endif // !PARTICLE_FILE_VERSION_CONSTS_HPP
