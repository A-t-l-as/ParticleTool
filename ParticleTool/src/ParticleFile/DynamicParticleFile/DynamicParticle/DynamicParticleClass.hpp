#ifndef DYNAMIC_PARTICLE_CLASS_HPP
#define DYNAMIC_PARTICLE_CLASS_HPP

#include <filesystem>
#include <vector>
#include <unordered_map>
#include "DynamicParticleData.hpp"
#include "File/BinFile.hpp"
#include "../../ParticleFileVersionInfo.hpp"
#include "../../../AodCompilator/GlobalQueues.hpp"

#include "../../../Cfg/CfgFileData.hpp"

class DynamicParticleClass
{
public:
    DynamicParticleClass(
                            const ParticleGlobals::ENAppModes& arg_app_mode,
                            CfgFileData arg_cfg_file_data = CfgFileData(),
                            ParticleFileVersionInfo arg_prt_file_version_info = ParticleFileVersionInfo(),
                            std::filesystem::path arg_particle_directory_path = std::filesystem::path()
                        );



    std::filesystem::path GetParticleDirectoryPath() const { return m_particle_directory_path; };

    void ParseFrom(std::string& arg_line, GlobalQueues& arg_queues, const std::vector<char>& arg_clean_file_buffer);
    void WriteTo(BinFile& output_file_buff);


    void ReadAndSetAndExportDynamicParticleToAod(BinFile& buffer, std::stringstream& output, std::string& particle_name);


private:

    bool ReadData(BinFile& buffer, std::string particle_name, DynamicParticleData& dynamic_particle_data);

    void ExportTo
    (
        const DynamicParticleData& dynamic_particle_data,
        std::stringstream& output,
        std::string particle_name,
        int count_of_tabulation
    );


    void SetPrtVersion(ParticleFileVersionInfo arg_prt_file_version_info)
    {
        m_dynamic_particle_cfg.input_dynamic_particle_file_version_info = arg_prt_file_version_info;
    }


    void GetWholeObject
    (
        std::stringstream& dynamic_particle_file_stream,
        DynamicParticleData& arg_dynamic_particle_data,
        std::string& arg_line,
        GlobalQueues& arg_queues
    );
    //{
    void GetSingleObject
    (
        std::stringstream& dynamic_particle_file_stream,
        DynamicParticleData& arg_dynamic_particle_data,
        std::string& arg_line,
        GlobalQueues& arg_queues
    );

    void GetTime(DynamicParticleData& arg_dynamic_particle_data, std::string& arg_line);
    //}

    void WriteDynamicParticleDataToFileBuffer(BinFile& output_file_buff,
                                              DynamicParticleData& arg_dynamic_particle_data);
    //{
    void CalculateImportantValues(DynamicParticleData& arg_dynamic_particle_data);
    //}

    void InitializeImportHashMaps();
    void InitializeExportHashMaps();

    DynamicParticleData m_dynamic_particle_data = {};

    ParticleFileVersionInfo m_prt_file_version_info = {};

    std::unordered_map<std::string, uint32_t> m_list_of_type_consts_for_import = {};
    std::unordered_map<std::string, uint32_t> m_list_of_lighttype_consts_for_import = {};

    std::filesystem::path m_particle_directory_path;

    CfgFileData m_dynamic_particle_cfg = {};

    std::unordered_map<uint32_t, std::string> m_list_of_type_consts_for_export = {};
    std::unordered_map<uint32_t, std::string> m_list_of_lighttype_consts_for_export = {};


    void WriteCompilatorFlagsFile() const;
};




#endif // !DYNAMIC_PARTICLE_CLASS_HPP
