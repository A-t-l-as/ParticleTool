#ifndef GLOBAL_QUEUES_HPP
#define GLOBAL_QUEUES_HPP

#include <queue>
#include <string>

struct GlobalQueues
{
    std::queue<std::string> m_effect_names_q = {};
    std::queue<std::string> m_emiter_names_q = {};
    std::queue<std::string> m_particle_names_q = {};
    std::queue<std::string> m_pair_particle_emiter_names_q = {};

    std::queue<std::string> m_annotations_q = {};

    std::queue<std::string> m_slot_strings_q = {};
    std::queue<std::string> m_texture_q = {};
    std::queue<std::string> m_mesh_q = {};
    std::queue<std::string> m_bump_texture_q = {};
    std::queue<std::string> m_emits_groups_q = {};

    //Only For Dynamic Particle:
    std::queue<std::string> m_dynamic_particle_Texture_q = {};
    std::queue<std::string> m_dynamic_particle_Mesh_q = {};
};



#endif // !GLOBAL_QUEUES_HPP
