#include <fstream>

#include "CfgCompilator.hpp"
#include "Console/Console.hpp"
#include "File/TextFile.hpp"
#include "Utils/StringUtils.hpp"


using namespace std;


CfgCompilator::CfgCompilator(const std::filesystem::path& arg_cfg_file_path)
{
    if (!filesystem::exists(arg_cfg_file_path))
    {
        CONSOLE_OUT.PrintLn(ParticleGlobals::dynamic_particle_cfg_file_name_str,
                            " file does not exist so I created a new one....");

        fstream new_cfg_file;
        new_cfg_file.open(arg_cfg_file_path, ios::out);

        new_cfg_file << "// Dynamic Particle Config:" << endl
                     << CfgCompilatorUtils::value_types[0] << " = " << ParticleGlobals::ks_format_str << ";" << endl
                     << CfgCompilatorUtils::value_types[1] << " = " << "false;" << endl
                     << CfgCompilatorUtils::value_types[2] << " = " << ParticleGlobals::ks_format_str << ";" << endl
                     << "// Available formats:" << endl
                     << "// " << ParticleGlobals::e2150_format_str << endl
                     << "// " << ParticleGlobals::ww3_or_hh_format_str << endl
                     << "// " << ParticleGlobals::ww2_or_fa_or_pc2_format_str << endl
                     << "// " << ParticleGlobals::ks_format_str << endl << endl;

        new_cfg_file.close();
    }


    TextFile cfg_file;
    cfg_file.LoadFrom(arg_cfg_file_path);
    cfg_file.Informations();
    cfg_file.ExitWhenFileDontExist();

    cfg_file.DeleteComments();
    cfg_file.CleanCppFileBufferFromContrChars();

    GetInfoFromCfg( cfg_file.GetCleanFileBuffer() );
}


void CfgCompilator::GetInfoFromCfg(const std::vector <char>& arg_clean_file)
{
    InitializeHashMap();

    CONSOLE_OUT.PrintLn("DynamicParticle.cfg:", Mess::endl,
                        "####################", Mess::endl);


    string_view file_view(arg_clean_file.data(), arg_clean_file.size());

    string ins_value_type;
    string ins_value;

    size_t start = 0;
    while (true)
    {
        size_t end = file_view.find(';', start);

        if (end == string_view::npos)
            break;

        string instruction(file_view.substr(start, end - start + 1));

        DEBUG_PRINT("----", Mess::endl, instruction, Mess::endl);

        GetValuesFromString(instruction, ins_value_type, ins_value);
        InitializeSwitches(ins_value_type, ins_value);

        DEBUG_PRINT(ins_value_type, Mess::endl, ins_name, Mess::endl, ins_value, Mess::endl, "----", Mess::endl);

        // Reset wartosci
        ins_value_type.clear();
        ins_value.clear();

        start = end + 1;
    }

    CONSOLE_OUT.PrintLn("-----------------");

    DEBUG_PRINT("dynamic_particle_input_format : ", Mess::endl);
    DEBUG_PRINT(this->m_cfg_file_data.input_dynamic_particle_file_version_info.ToString(), Mess::endl);

    DEBUG_PRINT("force_specific_export_format : ", Mess::endl);
    DEBUG_PRINT(this->m_cfg_file_data.force_dynamic_particle_export_format_switch, Mess::endl);

    DEBUG_PRINT("forced_export_format : ", Mess::endl);
    DEBUG_PRINT(this->m_cfg_file_data.forced_dynamic_particle_file_version_info_for_export.ToString(), Mess::endl);
}

void CfgCompilator::InitializeHashMap()
{

    for (size_t i = 0; i < CfgCompilatorUtils::number_of_false_and_true_config_values_str; ++i)
    {
        this->m_config_values_hash_map[ CfgCompilatorUtils::true_config_values_str [i] ] = "1";
        this->m_config_values_hash_map[ CfgCompilatorUtils::false_config_values_str[i] ] = "0";
    }

    m_dynamic_particle_file_version_map[""] = ParticleFileVersionInfo();


    m_dynamic_particle_file_version_map[ StringUtils::GetToUpper(ParticleGlobals::e2150_format_str) ] =
        ParticleFileVersionConsts::earth2150_dynamic_file_type;

    m_dynamic_particle_file_version_map[ StringUtils::GetToUpper(ParticleGlobals::ww3_or_hh_format_str) ] =
        ParticleFileVersionConsts::ww3_or_heli_heroes_dynamic_file_type;

    m_dynamic_particle_file_version_map[ StringUtils::GetToUpper(ParticleGlobals::ww2_or_fa_or_pc2_format_str) ] =
        ParticleFileVersionConsts::ww2_or_fa_or_pc2_dynamic_file_type;

    m_dynamic_particle_file_version_map[ StringUtils::GetToUpper(ParticleGlobals::ks_format_str) ] =
        ParticleFileVersionConsts::ks_dynamic_file_type;


    m_dynamic_particle_file_version_map_str[""] = "";
    m_dynamic_particle_file_version_map_str[ StringUtils::GetToUpper(ParticleGlobals::e2150_format_str) ] = "1";
    m_dynamic_particle_file_version_map_str[ StringUtils::GetToUpper(ParticleGlobals::ww3_or_hh_format_str) ] = "1";
    m_dynamic_particle_file_version_map_str[ StringUtils::GetToUpper(ParticleGlobals::ww2_or_fa_or_pc2_format_str) ] = "1";
    m_dynamic_particle_file_version_map_str[ StringUtils::GetToUpper(ParticleGlobals::ks_format_str) ] = "1";


    for (size_t i = 0; i < CfgCompilatorUtils::number_of_value_types; ++i)
    {
        m_config_en_value_types_hash_map[ string(CfgCompilatorUtils::value_types[i]) ] =
            static_cast<CfgCompilatorUtils::ENCfgValueTypes>(i);
    }

    m_config_en_value_types_hash_map[""] = CfgCompilatorUtils::ENCfgValueTypes::invalid;
}


void CfgCompilator::GetValuesFromString
(
    const std::string& arg_instruction,
    string& arg_value_type,
    string& arg_value
)
{
    while (true)
    {
        bool nopswitch = true;

        //Sprawdzenie czy jest prawidlowy typ
        for (uint32_t i = 0; i < CfgCompilatorUtils::number_of_value_types; ++i)
        {
            if (arg_instruction.starts_with(CfgCompilatorUtils::value_types[i]))
            {
                arg_value_type = CfgCompilatorUtils::value_types[i];
                nopswitch = false;
                break;
            }
        }

        // Jesli typ byl nieprawidlowy czyli nopswitch == true to wychodze
        if (nopswitch == true)
        {
            arg_value_type = string();
            arg_value = string();
            return;
        }

        //Wyodrebnienie wartosci od instrukcji
        uint64_t valueindex = arg_instruction.find("=") + 1;
        arg_value = arg_instruction.substr(valueindex, arg_instruction.length() - valueindex - 1);

        StringUtils::ToUpper(arg_value);

        break;
    }

}

void CfgCompilator::InitializeSwitches(const std::string& value_type, std::string& value)
{
    CfgCompilatorUtils::ENCfgValueTypes arg_en_value_type = this->m_config_en_value_types_hash_map[value_type];
    std::string boolean_value_str_from_str = this->m_config_values_hash_map[value];


    if (arg_en_value_type == CfgCompilatorUtils::ENCfgValueTypes::invalid)
        return;

    // dynamic_particle_input_format
    if (arg_en_value_type == CfgCompilatorUtils::ENCfgValueTypes::dynamic_particle_input_format)
    {
        if( m_dynamic_particle_file_version_map_str[value] == "" )
        {
            DEBUG_PRINT("value = ", value, Mess::endl);
            CONSOLE_OUT.PrintLn("m_dynamic_particle_file_version_map_str[value] = ",
                                m_dynamic_particle_file_version_map_str[value]);

            CONSOLE_OUT.PrintLn("Error: The configuration file contains an incorrect dynamic particle INPUT format.", Mess::endl,
                "       Please correct the configuration file by specifying the available dynamic particle format." , Mess::endl,
                "       At this point, the program will assume that it is ks format.");

            value = StringUtils::GetToUpper(ParticleGlobals::ks_format_str);
        }

        m_cfg_file_data.input_dynamic_particle_file_version_info = m_dynamic_particle_file_version_map[value];

        CONSOLE_OUT.PrintLn(value_type, " = ", value);

        return;
    }

    // force_specific_export_format
    if (arg_en_value_type == CfgCompilatorUtils::ENCfgValueTypes::force_specific_export_format)
    {
        if (boolean_value_str_from_str == "")
        {
           CONSOLE_OUT.PrintLn("Error: The configuration file contains an incorrect switch value.", Mess::endl,
                 "       Please correct the configuration file.", Mess::endl,
                 "       At this point, the program will assume that it is \"false\" value.");

            boolean_value_str_from_str = "0";
        }

        DEBUG_PRINT("value = ", boolean_value_str_from_str, Mess::endl);

        m_cfg_file_data.force_dynamic_particle_export_format_switch = stoul(boolean_value_str_from_str, nullptr, 10);

        CONSOLE_OUT.PrintLn(value_type, " = ", m_cfg_file_data.force_dynamic_particle_export_format_switch);

        return;
    }

    // forced_export_format
    if (arg_en_value_type == CfgCompilatorUtils::ENCfgValueTypes::forced_export_format)
    {
        if ( m_dynamic_particle_file_version_map_str[value] == "" )
        {
            CONSOLE_OUT.PrintLn("Error: The configuration file contains an incorrect dynamic particle EXPORT format.",
                Mess::endl,
"       Please correct the configuration file by specifying the available dynamic particle format.", Mess::endl,
"       At this point, the program will assume that it is ks format.");

            value = StringUtils::GetToUpper(ParticleGlobals::ks_format_str);
        }

        m_cfg_file_data.forced_dynamic_particle_file_version_info_for_export = m_dynamic_particle_file_version_map[value];

        CONSOLE_OUT.PrintLn(value_type, " = ", value);

        return;
    }


}



