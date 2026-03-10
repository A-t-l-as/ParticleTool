#ifndef WHOLE_PARTICLE_EMITER_CONTAINER_HPP
#define WHOLE_PARTICLE_EMITER_CONTAINER_HPP

#include <list>
#include "Emiter/EmiterClass.hpp"
#include "Particle/ParticleClass.hpp"
#include "Effect/EffectClass.hpp"
#include "PairParticleEmiter/PairParticleEmiterClass.hpp"
#include "EndOfParticle/ParticleEndClass.hpp"

class WholeParticleEmiterContainer
{
public:

    WholeParticleEmiterContainer()
    {}


    void WriteTo(BinFile& output_file_buff)
    {

        for (EffectClass& single_effect : m_effects)
            single_effect.WriteTo(output_file_buff);


        output_file_buff.WriteValue(static_cast<uint32_t>(m_emiters.size()));

        for (auto& single_emiter : m_emiters)
            single_emiter.WriteTo(output_file_buff);


        output_file_buff.WriteValue(static_cast<uint32_t>(m_particles.size()));

        for (auto& single_particle : m_particles)
            single_particle.WriteTo(output_file_buff);


        output_file_buff.WriteValue(static_cast<uint32_t>(m_pair_particles_emiters.size()));

        for (auto& single_pair_particle_emiter : m_pair_particles_emiters)
            single_pair_particle_emiter.WriteTo(output_file_buff);

        m_single_particle_end.WriteTo(output_file_buff);

    }

    inline void Insert(const EffectClass& effect)
    {
        m_effects.push_back(effect);
    }

    inline void Insert(const EmiterClass& emiter)
    {
        m_emiters.push_back(emiter);
    }

    inline void Insert(const ParticleClass& particle)
    {
        m_particles.push_back(particle);
    }

    inline void Insert(const PairParticleEmiterClass& group)
    {
        m_pair_particles_emiters.push_back(group);
    }

    ParticleEndClass& GetEndOfParicleRef()
    {
        return this->m_single_particle_end;
    }

    void ReadFrom
    (
        BinFile& input_file,
        ParticleFileVersionInfo arg_particle_file_type,
        uint8_t arg_fourth_byte_of_header
    )
    {
        //--- effects ---

        EffectClass my_effect(ParticleGlobals::ENAppModes::m_export, arg_particle_file_type);
        my_effect.ReadFrom(input_file);
        this->Insert(my_effect);

        //--- emiters ---

        uint32_t number_of_emiters = 0;;
        input_file.ReadValue( number_of_emiters );
        CONSOLE_OUT.PrintLn("Number of emiters: ", number_of_emiters);

        for (uint32_t h = 0; h < number_of_emiters; ++h)
        {
            EmiterClass my_emiter
            (
                ParticleGlobals::ENAppModes::m_export,
                arg_particle_file_type,
                std::string(),
                arg_fourth_byte_of_header
            );

            my_emiter.ReadFrom(input_file);
            this->Insert(my_emiter);
        }

        //--- particles ---

        uint32_t number_of_particles = 0;
        input_file.ReadValue(number_of_particles);

        CONSOLE_OUT.PrintLn("Number of particles: ", number_of_particles);

        for (uint32_t h = 0; h < number_of_particles; ++h)
        {
            ParticleClass my_particle
                (ParticleGlobals::ENAppModes::m_export, arg_particle_file_type);

            my_particle.ReadFrom(input_file);
            this->Insert(my_particle);
        }

        //--- pairs ---

        uint32_t number_of_pairs = 0;
        input_file.ReadValue(number_of_pairs);
        CONSOLE_OUT.PrintLn("Number of particle-emiter pairs: ", number_of_pairs);

        for (uint32_t h = 0; h < number_of_pairs; ++h)
        {
            PairParticleEmiterClass my_pair_particle_emiter
                (ParticleGlobals::ENAppModes::m_export, arg_particle_file_type);

            my_pair_particle_emiter.ReadFrom(input_file);
            this->Insert(my_pair_particle_emiter);
        }

        //--- end ---

        this->m_single_particle_end = ParticleEndClass(arg_particle_file_type);
        m_single_particle_end.ReadFrom(input_file);

    }

    void SetPrtVersion(bool force_end_format, const ParticleFileVersionInfo& m_forced_format)
    {
        if (force_end_format)
        {
            for(EffectClass& effect : m_effects)
                effect.SetPrtVersion(m_forced_format);

            for(EmiterClass& emiter : m_emiters)
                emiter.SetPrtVersion(m_forced_format);

            for(ParticleClass& particle : m_particles)
                particle.SetPrtVersion(m_forced_format);

            for(PairParticleEmiterClass& pair : m_pair_particles_emiters)
                pair.SetPrtVersion(m_forced_format);

            m_single_particle_end.SetPrtVersion(m_forced_format);
        }
    }

    void ExportTo(const std::string& obj_name, std::stringstream& ss)
    {
        ss << std::fixed << std::setprecision(ParticleGlobals::aod_float_precision);
        ss << "ParticlesEmiter" << " " << obj_name << std::endl << "{" << std::endl;

        for(EffectClass& effect : m_effects)
            effect.ExportTo(ss);

        for(EmiterClass& emiter : m_emiters)
            emiter.ExportTo(ss);

        for(ParticleClass& particle : m_particles)
            particle.ExportTo(ss);

        for(PairParticleEmiterClass& pair : m_pair_particles_emiters)
            pair.ExportTo(ss);

        m_single_particle_end.ExportTo(ss);

        ss << "}";
    }


private:
    std::list<EffectClass> m_effects = {};

    std::list<EmiterClass> m_emiters = {};

    std::list<ParticleClass> m_particles = {};

    std::list<PairParticleEmiterClass> m_pair_particles_emiters = {};

    ParticleEndClass m_single_particle_end;


};


#endif // !WHOLE_PARTICLE_EMITER_CONTAINER_HPP
