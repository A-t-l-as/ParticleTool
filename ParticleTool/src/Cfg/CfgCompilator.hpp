#ifndef CFG_COMPILATOR_HPP
#define CFG_COMPILATOR_HPP

#include <string>
#include <unordered_map>
#include <vector>
#include <filesystem>

#include "CfgFileData.hpp"
#include "CfgCompilatorUtils.hpp"

class CfgCompilator
{
public:
    CfgCompilator(const std::filesystem::path& arg_cfg_file_path);

    CfgFileData GetCfgFileData() const { return m_cfg_file_data; }

private:
    void GetInfoFromCfg(const std::vector <char>& arg_clean_file);

    void GetValuesFromString(
        const std::string& arg_instruction,
        std::string& arg_value_type,
        std::string& arg_value
        );

    void InitializeSwitches(const std::string& value_type, std::string& value);

    void InitializeHashMap();

    std::unordered_map<std::string, std::string> m_config_values_hash_map = {};
    std::unordered_map<std::string, CfgCompilatorUtils::en_cfg_value_types> m_config_en_value_types_hash_map = {};

    std::unordered_map<std::string, ParticleFileVersionInfo> m_dynamic_particle_file_version_map = {};
    std::unordered_map<std::string, std::string> m_dynamic_particle_file_version_map_str = {};

    CfgFileData m_cfg_file_data = {};

};


#endif // !CFG_COMPILATOR_HPP
