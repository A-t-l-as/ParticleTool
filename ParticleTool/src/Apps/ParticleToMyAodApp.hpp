#ifndef PARTICLE_TO_MY_AOD_APP_HPP
#define PARTICLE_TO_MY_AOD_APP_HPP

#include "File/BinFile.hpp"
#include "System/IApp.hpp"
#include "../ParticleFile/ParticleFileVersionInfo.hpp"
#include "../ParticleFile/ParticleFileVersionConsts.hpp"
#include "../ParticleGlobals.hpp"
#include <filesystem>
#include <vector>
#include <cmath>
#include <sstream>
#include <unordered_map>

class ParticleToMyAodApp : public IApp
{
public:
    //Metody:
    ParticleToMyAodApp();

    void Run(int my_argc, char* my_argv[]) override;


private:
    std::string m_obj_name;
    std::filesystem::path m_program_parent_path;
    std::filesystem::path m_input_file_path;

    const std::vector<std::string> correct_formats =
    {
        ParticleGlobals::ks_format_str,
        ParticleGlobals::earth2160_format_str,
        ParticleGlobals::tw_format_str,
        ParticleGlobals::pg_format_str
    };

    std::unordered_map<ParticleGlobals::particle_type_value, std::string> m_format_names = {};

    std::unordered_map<std::string, ParticleFileVersionInfo> m_format_containers = {};


    //output file
    std::stringstream m_output_stream;

    //additional data file
    std::stringstream m_bonus_file_stream;

    ParticleFileVersionInfo m_forced_format = {};

    ParticleGlobals::particle_type_value m_my_particle_file_type;

    uint8_t m_fourth_byte_of_header;

    void WriteIntroToFile(ParticleGlobals::particle_type_value& my_particle_file_type);

    void DecompileDynamicParticleToMyAod
        (const std::filesystem::path& particle_directory_path, BinFile& input_file);

    void DecompileParticleEditFileToMyAod
    (
        const std::filesystem::path& particle_directory_path,
        ParticleFileVersionInfo arg_particle_file_type,
        BinFile& input_file,
        bool force_end_format
    );
    
    void InitializeFormatHashMaps()
    {
        m_format_names[ParticleGlobals::particle_type_value::not_particle] =
            "NULL (NOT PARTICLE)";

        m_format_names[ParticleGlobals::particle_type_value::dynamic_particle] =
            "Dynamic";

        m_format_names[ParticleGlobals::particle_type_value::ks_particles_emiter] =
            "Ks ParticlesEmiter";

        m_format_names[ParticleGlobals::particle_type_value::e2160_particle] =
            "E2160 Particle Edit";

        m_format_names[ParticleGlobals::particle_type_value::two_worlds_particle] =
            "Two Worlds Particle Edit";

        m_format_names[ParticleGlobals::particle_type_value::particle_gen_particle] =
            "Particle Gen";

        m_format_containers[ParticleGlobals::ks_format_str] =
            ParticleFileVersionConsts::ks_particle_file_type;

        m_format_containers[ParticleGlobals::earth2160_format_str] =
            ParticleFileVersionConsts::e2160_particle_edit_file_type;

        m_format_containers[ParticleGlobals::tw_format_str] =
            ParticleFileVersionConsts::two_worlds_particle_edit_file_type;

        m_format_containers[ParticleGlobals::pg_format_str] =
            ParticleFileVersionConsts::particle_gen_file_type;
    }

    void ShowInfoAboutParticle(ParticleGlobals::particle_type_value& arg_particle_file_type)
    {
        const int32_t i32_arg_particle_file_type = static_cast<int32_t>(arg_particle_file_type);

        CONSOLE_OUT.PrintLn
        (
            "I detected particle type: ",
            m_format_names[arg_particle_file_type],
            " (",
            i32_arg_particle_file_type,
            ")",
            Mess::endl,
            "version: ",
            i32_arg_particle_file_type - 1,
            Mess::endl
        );
    }


    void GetInformationAboutEndFormat(bool& force_end_format);

};

#endif // !PARTICLE_TO_MY_AOD_APP_HPP
