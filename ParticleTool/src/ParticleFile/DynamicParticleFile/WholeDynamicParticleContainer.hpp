#ifndef WHOLE_DYNAMIC_PARTICLE_CONTAINER_HPP
#define WHOLE_DYNAMIC_PARTICLE_CONTAINER_HPP

#include "DynamicParticle/DynamicParticleClass.hpp"
#include <list>

class WholeDynamicParticleContainer
{
public:

    inline void Insert(const DynamicParticleClass& dynamic_particle)
    {
        m_dynamic_particles.push_back( std::move(dynamic_particle) );
    }

    void WriteToFileBuffer(BinFile& output_file_buff)
    {
        for (DynamicParticleClass& single_dynamic_particle : m_dynamic_particles)
            single_dynamic_particle.WriteTo(output_file_buff);
    }

    void ExportTo(std::stringstream& ss)
    {
        // ...
    }

private:

    std::list<DynamicParticleClass> m_dynamic_particles = {};

};



#endif // !WHOLE_DYNAMIC_PARTICLE_CONTAINER_HPP
