#include "ParticleToMyAodApp.hpp"
#include "../ParticleFile/FileHeader/FileHeaderClass.hpp"
#include "Utils/Misc.hpp"
#include "Utils/TxtUtils.hpp"
#include "../Cfg/CfgCompilator.hpp"
#include "../ParticleFile/CustomBlock/CustomBlockClass.hpp"
#include "../ParticleFile/DynamicParticleFile/DynamicParticle/DynamicParticleClass.hpp"
#include "../ParticleFile/ParticleEmiterFile/WholeParticleEmiterContainer.hpp"

using namespace std;

namespace fs = filesystem;


void ParticleToMyAodApp::WriteIntroToFile(ParticleGlobals::particle_type_value& my_particle_file_type)
{
    switch (my_particle_file_type)
    {
        case ParticleGlobals::particle_type_value::dynamic_particle:
            m_output_stream << "Dynamic" << endl
                << "{" << endl
            << "}" << endl;
        break;

        case ParticleGlobals::particle_type_value::ks_particles_emiter:
        case ParticleGlobals::particle_type_value::particle_gen_particle:
        case ParticleGlobals::particle_type_value::two_worlds_particle:
        case ParticleGlobals::particle_type_value::e2160_particle:

            m_output_stream << "ParticlesEmiter" << endl
            << "{" << endl
            << '\t' << "version " << static_cast<int32_t>(my_particle_file_type) - 1 << endl
            << "}" << endl;
        break;

        default:
        break;
    }
}






void ParticleToMyAodApp::GetInformationAboutEndFormat(bool& force_end_format)
{
    CONSOLE_OUT.PrintLn("Force a specific output format? [y/n]");

    string answer = string();
    string format = string();

    const vector<string> possible_answers = { "y","n","Y","N" };
    const vector<string> yes_answers = { "y","Y" };

    do
    {
        CONSOLE_IN.Scan(answer);

        if (!(Misc::CheckAnswerWithEveryElementInVec(answer, possible_answers)))
        {
            CONSOLE_OUT.PrintLn("Give the answer in y or n form...");
        }

    } 
    while (!(Misc::CheckAnswerWithEveryElementInVec(answer, possible_answers)));

    if (Misc::CheckAnswerWithEveryElementInVec(answer, yes_answers))
    {
        force_end_format = true;

        CONSOLE_OUT.PrintLn("Select the format: ["
                   , ParticleGlobals::ks_format_str , "/"
                   , ParticleGlobals::earth2160_format_str , "/"
                   , ParticleGlobals::tw_format_str , "/"
                   , ParticleGlobals::pg_format_str
                   , "]");

        do
        {
            CONSOLE_IN.Scan(format);

            if (!(Misc::CheckAnswerWithEveryElementInVec(format, correct_formats)))
            {
                CONSOLE_OUT.PrintLn("Choose from the given formats...");
            }

        } 
        while(!(Misc::CheckAnswerWithEveryElementInVec(format, correct_formats)));

        m_forced_format = m_format_containers[format];
    }
    else
    {
        force_end_format = false;
    }

}


ParticleToMyAodApp::ParticleToMyAodApp() :
    m_input_file_path(fs::path()),

    m_obj_name(string()),

    m_my_particle_file_type( ParticleGlobals::particle_type_value::not_particle ),
    m_fourth_byte_of_header(0),

    m_program_parent_path(fs::path())
{}


void ParticleToMyAodApp::Run(int my_argc, char* my_argv[])
{
    const unsigned int c_correct_number_of_args = 3;
    const unsigned int c_number_of_args_with_force_format = 5;
    this->m_program_parent_path = fs::current_path();
    bool force_end_format = false;

    InitializeFormatHashMaps();

    bool standard_program_exec = false;

    if (my_argc != c_correct_number_of_args && my_argc != c_number_of_args_with_force_format)
    {
        standard_program_exec = true;
    }

    if (my_argc == c_correct_number_of_args)
    {

        m_input_file_path = my_argv[2];
        CONSOLE_OUT.PrintLn("File = ", m_input_file_path.string());
    }

    if (my_argc == c_number_of_args_with_force_format)
    {

        m_input_file_path = my_argv[2];
        CONSOLE_OUT.PrintLn("File = ", m_input_file_path.string());

        string force_command = my_argv[3];
        string format = my_argv[4];
        CONSOLE_OUT.PrintLn("Forced format = ", format);

        if (force_command == "--force" || force_command == "-force")
        {
            if (Misc::CheckAnswerWithEveryElementInVec(format, correct_formats))
            {
                force_end_format = true;
                m_forced_format = m_format_containers[format];
            }
            else
            {
                standard_program_exec = true;
            }
        }
        else
        {
            standard_program_exec = true;
        }
    }

    if (standard_program_exec == true)
    {
        CONSOLE_OUT.PrintLn("Specify the name of the input file:");
        CONSOLE_IN.Scan(m_input_file_path);
    }

    //Określ dodatkowe informacje
    this->m_obj_name = this->m_input_file_path.stem().string();

    const fs::path particle_directory_path = this->m_input_file_path.parent_path() / m_obj_name;

    //Dwa proste komunikaty:
    CONSOLE_OUT.PrintLn("I open the file: ", m_input_file_path.string(), Mess::endl,
                        "Object found: ", m_obj_name, Mess::endl);

    // Zaciągam plik input do pamięci
    BinFile input_file;
    input_file.LoadFrom(m_input_file_path);
    input_file.Informations();
    input_file.ExitWhenFileDontExist();

    FileHeaderClass file_header;
    file_header.ReadFrom(input_file);
    m_my_particle_file_type = file_header.GetParticleFileType();
    m_fourth_byte_of_header = file_header.GetFourthByteOfHeader();


    if (m_my_particle_file_type == ParticleGlobals::particle_type_value::not_particle)
    {
        CONSOLE_OUT.PrintLn("The file being opened is not a particle file...");
        exit(EXIT_FAILURE);
    }

    filesystem::create_directory(particle_directory_path); // tworze folder na output
    
    ShowInfoAboutParticle(m_my_particle_file_type);

    if (standard_program_exec == true && m_my_particle_file_type != ParticleGlobals::particle_type_value::dynamic_particle)
    {
        GetInformationAboutEndFormat(force_end_format);
    }

    if (force_end_format == true && m_my_particle_file_type != ParticleGlobals::particle_type_value::dynamic_particle)
    {
        file_header.SetPrtVersion(m_forced_format.particle_version);
    }
    file_header.ExportTo(m_bonus_file_stream);

   
    switch (m_my_particle_file_type)
    {
       
        case ParticleGlobals::particle_type_value::dynamic_particle:
            DecompileDynamicParticleToMyAod
                (particle_directory_path, input_file);
        break;

        case ParticleGlobals::particle_type_value::ks_particles_emiter:
            DecompileParticleEditFileToMyAod
                (particle_directory_path, ParticleFileVersionConsts::ks_particle_file_type, input_file, force_end_format);
        break;

        case ParticleGlobals::particle_type_value::particle_gen_particle:
            DecompileParticleEditFileToMyAod
                (particle_directory_path, ParticleFileVersionConsts::particle_gen_file_type, input_file, force_end_format);
        break;

        case ParticleGlobals::particle_type_value::two_worlds_particle:
            DecompileParticleEditFileToMyAod
                (particle_directory_path, ParticleFileVersionConsts::two_worlds_particle_edit_file_type, input_file, force_end_format);
        break;

        case ParticleGlobals::particle_type_value::e2160_particle:
            DecompileParticleEditFileToMyAod
                (particle_directory_path, ParticleFileVersionConsts::e2160_particle_edit_file_type, input_file, force_end_format);
        break;

        default: break;
    }


    TU::WriteSsToFile
        (m_bonus_file_stream,
                      particle_directory_path / (this->m_obj_name + ParticleGlobals::bonus_file_rest_name_str));

    CONSOLE_OUT.PrintLn("The file named ", m_input_file_path.string(), " has been decompiled!");
}


void ParticleToMyAodApp::DecompileDynamicParticleToMyAod(const fs::path& particle_directory_path, BinFile& input_file)
{

    WriteIntroToFile(m_my_particle_file_type); //Wypisuję informację wstępną do pliku wyjściowego...

    CfgCompilator dynamic_particle_cfg_file
        (this->m_program_parent_path / ParticleGlobals::dynamic_particle_cfg_file_name_str);

    CfgFileData temp_cfg_file_data = dynamic_particle_cfg_file.GetCfgFileData();

    CustomBlockClass custom_block( temp_cfg_file_data.input_dynamic_particle_file_version_info );
    custom_block.ReadFrom(input_file);

    if (temp_cfg_file_data.force_dynamic_particle_export_format_switch)
    {
        custom_block.SetPrtVersion(temp_cfg_file_data.forced_dynamic_particle_file_version_info_for_export);
    }

    custom_block.ExportTo(m_bonus_file_stream);

    m_output_stream << fixed << setprecision(ParticleGlobals::aod_float_precision);

    DynamicParticleClass my_dynamic_particle
        (ParticleGlobals::ENAppModes::m_export, temp_cfg_file_data, ParticleFileVersionInfo(), particle_directory_path);

    my_dynamic_particle.ReadAndSetAndExportDynamicParticleToAod
        (input_file, m_output_stream, m_obj_name);


    TU::WriteSsToFile
        (m_output_stream, particle_directory_path / (this->m_obj_name + ParticleGlobals::my_aod_format_str));


}

void ParticleToMyAodApp::DecompileParticleEditFileToMyAod
(
    const std::filesystem::path& particle_directory_path,
    ParticleFileVersionInfo arg_particle_file_type,
    BinFile& input_file,
    bool force_end_format
)
{
    if (force_end_format)
    {
        WriteIntroToFile(m_forced_format.particle_version);
    }
    else
    {
        WriteIntroToFile(arg_particle_file_type.particle_version);
    }

    CustomBlockClass custom_block(arg_particle_file_type);
    custom_block.ReadFrom(input_file);

    if (force_end_format)
    {
        custom_block.SetPrtVersion(m_forced_format);
    }

    custom_block.ExportTo(m_bonus_file_stream);

    WholeParticleEmiterContainer particle_emiter_container;
    particle_emiter_container.ReadFrom(input_file, arg_particle_file_type, this->m_fourth_byte_of_header);

    particle_emiter_container.SetPrtVersion(force_end_format, m_forced_format);

    particle_emiter_container.ExportTo(this->m_obj_name, m_output_stream);


    TU::WriteSsToFile
        (m_output_stream, particle_directory_path / (this->m_obj_name + ParticleGlobals::my_aod_format_str));

    
}
