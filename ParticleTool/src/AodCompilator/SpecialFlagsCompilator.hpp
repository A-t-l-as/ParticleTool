#ifndef SPECIAL_FLAGS_COMPILATOR_HPP
#define SPECIAL_FLAGS_COMPILATOR_HPP

#include <string>
#include <vector>
#include <filesystem>
#include <unordered_map>
#include "../ParticleFile/ParticleFileVersionConsts.hpp"
#include "../ParticleFile/ParticleFileVersionInfo.hpp"
#include "File/TextFile.hpp"
#include "Utils/Globals.hpp"

class SpecialFlagsCompilator
{
public:

    SpecialFlagsCompilator(bool& arg_error_handler) :
        r_error_handler(arg_error_handler)
    {}

    void CompileFile(const std::filesystem::path& arg_input_path)
    {
        TextFile input_file;
        input_file.LoadFrom(arg_input_path);

        input_file.Informations();
        this->r_error_handler = !(input_file.GetIsOpened());

        if ((input_file.Empty() == false) && (this->r_error_handler == Globals::success_code))
        {
            InitializeHashMaps();

            input_file.DeleteComments();

            input_file.CleanCppFileBufferFromContrChars();

            CompileCppFileToBin(input_file.GetCleanFileBuffer());
        }
    }

    ParticleFileVersionInfo GetDynamicParticleVersion() const { return this->m_dynamic_particle_file_version_info; }

private:
    bool& r_error_handler;


    ParticleFileVersionInfo m_dynamic_particle_file_version_info = {};
    std::unordered_map<std::string, ParticleFileVersionInfo> m_dynamic_particle_file_version_info_hash_map = {};

    void CompileCppFileToBin(const std::vector<char>& arg_clean_file)
    {
        std::string_view file_view(arg_clean_file.data(), arg_clean_file.size());

        std::string ins_value_type;
        std::string ins_name;
        std::string ins_value;

        size_t start = 0;
        while (true)
        {
            std::size_t end = file_view.find(';', start);

            if (end == std::string_view::npos)
                break;

            std::string instruction(file_view.substr(start, end - start + 1));

            CONSOLE_OUT.PrintLn("----", Mess::endl, instruction, Mess::endl);

            GetValuesFromString(instruction, ins_value_type, ins_name, ins_value);
            WriteInstructionToBin(ins_value_type, ins_name, ins_value);

            CONSOLE_OUT.PrintLn(ins_value_type, Mess::endl, ins_name, Mess::endl, ins_value, Mess::endl, "----", Mess::endl);

            // Reset wartosci
            ins_value_type.clear();
            ins_name.clear();
            ins_value.clear();

            start = end + 1;
        }
    }

    constexpr static char __compiler_var__value_type_str[] = "__compiler_var__";

    void InitializeHashMaps()
    {
        m_dynamic_particle_file_version_info_hash_map[""] = ParticleFileVersionInfo();

        m_dynamic_particle_file_version_info_hash_map[ParticleGlobals::e2150_format_str] =
            ParticleFileVersionConsts::earth2150_dynamic_file_type;

        m_dynamic_particle_file_version_info_hash_map[ParticleGlobals::ww3_or_hh_format_str] =
            ParticleFileVersionConsts::ww3_or_heli_heroes_dynamic_file_type;

        m_dynamic_particle_file_version_info_hash_map[ParticleGlobals::ww2_or_fa_or_pc2_format_str] =
            ParticleFileVersionConsts::ww2_or_fa_or_pc2_dynamic_file_type;

        m_dynamic_particle_file_version_info_hash_map[ParticleGlobals::ks_format_str] =
            ParticleFileVersionConsts::ks_dynamic_file_type;
    }


    void GetValuesFromString
    (
        const std::string& arg_instruction,
        std::string& arg_value_type,
        std::string& arg_name,
        std::string& arg_value
    )
    {
        bool nopswitch = true;

        //Sprawdzenie czy jest prawidlowy typ
        if (arg_instruction.starts_with(__compiler_var__value_type_str))
        {
            arg_value_type = __compiler_var__value_type_str;
            nopswitch = false;
        }

        // Jesli typ byl nieprawidlowy czyli nopswitch == true to wychodze
        if (nopswitch == true)
        {
            arg_value_type = "nop";
            arg_name = std::string();
            arg_value = std::string();
            return;
        }

        //Wyodrebnienie nazwy od instrukcji
        const std::size_t arg_instruction_len = arg_instruction.length();
        const std::size_t equal_symbol_index = arg_instruction.find("=");
        const std::size_t arg_value_type_len = arg_value_type.length();
        arg_name = arg_instruction.substr( arg_value_type_len, equal_symbol_index - arg_value_type_len);

        //Wyodrebnienie wartosci od instrukcji
        const std::size_t valueindex = equal_symbol_index + 1;
        arg_value = arg_instruction.substr(valueindex, arg_instruction_len - valueindex - 1);

        CONSOLE_OUT.PrintLn("ARG_TYPE = \"", arg_value_type, "\"");
        CONSOLE_OUT.PrintLn("ARG_NAME = \"", arg_name, "\"");
        CONSOLE_OUT.PrintLn("ARG_VALUE = \"", arg_value, "\"");

    }


    void WriteInstructionToBin(std::string& value_type, std::string& name, std::string& value)
    {

        // __compiler_var__
        if(value_type == __compiler_var__value_type_str)
        {
            if (name == "dynamic_particle_version")
            {
                const static std::vector<std::string> dynamic_particle_correct_formats =
                {
                    ParticleGlobals::e2150_format_str,
                    ParticleGlobals::ks_format_str,
                    ParticleGlobals::ww3_or_hh_format_str,
                    ParticleGlobals::ww2_or_fa_or_pc2_format_str
                };

                if (!(Misc::CheckAnswerWithEveryElementInVec(value, dynamic_particle_correct_formats)))
                {
                    CONSOLE_ERR.PrintLn
                        ("Error: The __compilator_flags__.cfg file contains an incorrect dynamic particle format.",
                                        Mess::endl,
                                        "       Please correct the __compilator_flags__.cfg file.", Mess::endl,
                                        "       At this point, the program will assume that it is ks format.");

                    value = ParticleGlobals::ks_format_str;
                }

                m_dynamic_particle_file_version_info = m_dynamic_particle_file_version_info_hash_map[value];

                CONSOLE_OUT.PrintLn(Mess::endl,
                                    "----------------------------------------------------------------------------------",
                                    Mess::endl,
                                    "The following format was found in the file __compilator_flags__.cfg: ", value,
                                    Mess::endl,
                                    "----------------------------------------------------------------------------------",
                                    Mess::endl);

                return;
            }

            if (name != "dynamic_particle_version")
            {
                CONSOLE_ERR.PrintLn("Error: The __compilator_flags__.cfg file contains an incorrect __compiler_var__ flag.",
                                    Mess::endl,
                                    "       Please correct the __compilator_flags__.cfg file.");

                value_type = std::string();
                name = std::string();
                value = std::string();

                exit(EXIT_FAILURE);
            }

            return;
        }

    }


};



#endif // !SPECIAL_FLAGS_COMPILATOR_HPP
