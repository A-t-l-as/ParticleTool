#ifndef MY_AOD_TO_PARTICLE_APP_HPP
#define MY_AOD_TO_PARTICLE_APP_HPP

#include <filesystem>
#include "File/BinFile.hpp"
#include "System/IApp.hpp"
#include "Console/Console.hpp"
#include "../ParticleGlobals.hpp"
#include "../AodCompilator/AodDirectoryCompilator.hpp"

class MyAodToParticleApp : public IApp
{

public:

    MyAodToParticleApp()
    {}

    void Run(int my_argc, char* my_argv[]) override
    {
        std::filesystem::path input_directory_path;

        if (my_argc == c_correct_number_of_args)
        {
            input_directory_path = my_argv[2];
            CONSOLE_OUT.PrintLn("Directory = ", input_directory_path.string());
        }
        else
        {
            StandardProgramExecution(input_directory_path);
        }

        GlobalQueues my_queues;
        BinFile my_new_particle_file;

        AodDirectoryCompilator my_aod_compilator(my_new_particle_file, my_queues);
        my_aod_compilator.CompileDirectory(input_directory_path);

        std::filesystem::path m_output_file_path =
            CreateOutputFileName(input_directory_path , my_aod_compilator.GetParticleVersion() );

        my_new_particle_file.SaveTo( m_output_file_path );

        CONSOLE_OUT.PrintLn(Mess::endl,"-----------------------------------------------------",
                            Mess::endl, "The directory named ", input_directory_path.string(), " was successfully compiled...");
    }


private:
    //Pola:
    constexpr const unsigned int static c_correct_number_of_args = 3;


    void StandardProgramExecution(std::filesystem::path& arg_path)
    {
        CONSOLE_OUT.PrintLn("Specify the name of the input directory:");
        CONSOLE_IN.Scan(arg_path);
    }


    std::filesystem::path CreateOutputFileName(const std::filesystem::path& arg_path,
                                               const ParticleGlobals::particle_type_value& version) const
    {
        std::string dir_name = arg_path.stem().string();

        switch (version)
        {
            case ParticleGlobals::particle_type_value::dynamic_particle:
            case ParticleGlobals::particle_type_value::ks_particles_emiter:
                return arg_path.parent_path() / (dir_name + ".msh" );
            break;

            case ParticleGlobals::particle_type_value::e2160_particle:
            case ParticleGlobals::particle_type_value::two_worlds_particle:
            case ParticleGlobals::particle_type_value::particle_gen_particle:
                return arg_path.parent_path() / (dir_name + ".prt");
            break;

            case ParticleGlobals::particle_type_value::not_particle:
                return arg_path.parent_path() / (dir_name + ".error");
            break;

            default:
                return std::filesystem::path();
            break;
        }
    }


};



#endif // !MY_AOD_TO_PARTICLE_APP_HPP
