#ifndef AOD_DIRECTORY_COMPILATOR_HPP
#define AOD_DIRECTORY_COMPILATOR_HPP

#include <filesystem>
#include "File/BinFile.hpp"
#include "File/TextFile.hpp"
#include "../ParticleFile/DynamicParticleFile/WholeDynamicParticleContainer.hpp"
#include "../ParticleFile/ParticleEmiterFile/WholeParticleEmiterContainer.hpp"
#include "Console/Console.hpp"

class AodDirectoryCompilator
{
public:
    // metody:
    AodDirectoryCompilator(
                    BinFile& arg_output_file_buffer,
                    GlobalQueues& arg_queues
                 );

    void CompileDirectory(const std::filesystem::path& input_dir_path);
    ParticleGlobals::ENParticleTypeValue GetParticleVersion() const { return m_particle_type_version; }

private:
    BinFile& r_output_file_buffer;
    GlobalQueues& r_queues;

    WholeParticleEmiterContainer m_whole_particle_emiter_container;
    WholeDynamicParticleContainer m_whole_dynamic_particle_container;

    //Pola:
    bool its_pair_particle_emiter;

    bool m_end_of_file_initialize_switch;

    bool m_is_version_getted;

    int64_t bracket_counter;

    std::string m_inside_obj_type;
    std::string m_inside_obj_name;

    ParticleGlobals::ENParticleTypeValue m_particle_type_version;
    ParticleFileVersionInfo m_particle_file_version_info;

    std::unordered_map<ParticleGlobals::ENParticleTypeValue, ParticleFileVersionInfo> m_list_of_prt_file_ver_info = {};

    void CompileTxtFileToBinBuffer
    (
        TextFile& aod_file,
        const std::filesystem::path& input_dir_path,
        const std::string& input_dir_name
    );


    bool InterpretInstructions(
                                std::string& m_instruction,
                                EffectClass& single_effect,
                                EmiterClass& single_emiter,
                                ParticleClass& single_particle,
                                PairParticleEmiterClass& single_pair_particle_emiter
                              );
    //Dla dynamic_particle zwraca true
    //Dla innych false


    void InitializeFormatHashMaps();

    void GetPrtVersion(const std::string& arg_line,
                       ParticleGlobals::ENParticleTypeValue& dst,
                       ParticleFileVersionInfo& arg_particle_file_version_info);

    void GetDynamicParticleVersion(const std::string& arg_line,
                                   ParticleGlobals::ENParticleTypeValue& dst,
                                   ParticleFileVersionInfo& arg_particle_file_version_info);


    void InterpretParticlesEmiterInstructions(
                                                std::string& instruction,
                                                EffectClass& single_effect,
                                                EmiterClass& single_emiter,
                                                ParticleClass& single_particle,
                                                PairParticleEmiterClass& single_pair_particle_emiter
                                             );

    void CompileDynamicParticle(TextFile& aod_file, const std::filesystem::path& input_dir_path);



    template<class T>
    void CompileObject(std::string& instruction, T& single_object, WholeParticleEmiterContainer& container)
    {
        if (instruction == "{" && bracket_counter == ParticleGlobals::initialize_signal_value)
        {
            ++bracket_counter;
            DEBUG_PRINT("Initialize...", Mess::endl);
            single_object = T(ParticleGlobals::ENAppModes::m_import, m_particle_file_version_info, m_inside_obj_name);
        }

        if (instruction == "{")
        {
            ++bracket_counter;
        }

        if (bracket_counter > 0)
        {
            single_object.ParseFrom(instruction, this->r_queues);
        }

        if (instruction == "}")
        {
            --bracket_counter;
        }

        if (instruction == "}" && bracket_counter == ParticleGlobals::push_back_signal_value)
        {
            DEBUG_PRINT("PushBack", Mess::endl);
            container.Insert(single_object);
            single_object = T(ParticleGlobals::ENAppModes::m_import, m_particle_file_version_info);
            bracket_counter = ParticleGlobals::initialize_signal_value;

            m_inside_obj_type = std::string();
            m_inside_obj_name = std::string();
        }

    }

    void CompileEndOfFile(std::string& instruction, ParticleEndClass& single_particle_end);

};


#endif // !AOD_DIRECTORY_COMPILATOR_HPP
