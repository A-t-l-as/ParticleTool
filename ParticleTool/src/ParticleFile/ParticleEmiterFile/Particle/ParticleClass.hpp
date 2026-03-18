#ifndef PARTICLE_CLASS_HPP
#define PARTICLE_CLASS_HPP

#include <string>
#include <cstdint>
#include <unordered_map>
#include "../../../AodCompilator/GlobalQueues.hpp"
#include "ParticleData.hpp"
#include "../../ParticleFileVersionInfo.hpp"
#include "File/BinFile.hpp"

class ParticleClass
{
public:
    ParticleClass   (
                        const ParticleGlobals::ENAppModes& arg_app_mode,
                        ParticleFileVersionInfo arg_prt_file_version_info = ParticleFileVersionInfo(),
                        std::string arg_particle_name = std::string()
                    );


    void ReadFrom(BinFile& buff);
    void ExportTo(std::stringstream& output);


    void ParseFrom(std::string& arg_line, GlobalQueues& arg_queues);
    void WriteTo(BinFile& output_file_buff);


    void SetPrtVersion(ParticleFileVersionInfo arg_prt_file_version_info)
    {
        m_particle_data.linked_min_max.resize
            (arg_prt_file_version_info.number_of_linked_min_max_in_particle, ParticleGlobals::locked_linked_min_max);

        m_particle_data.ConvertTeselatesAndCurvesWholeFormat
            (m_prt_file_version_info.particle_version, arg_prt_file_version_info.particle_version);

        m_prt_file_version_info = arg_prt_file_version_info;
    }



private:

    void ReadFromParticleGenAndTwoWorldsFile(BinFile& buff);
    void ReadFromE2160File(BinFile& buff);
    void ReadFromKsFile(BinFile& buff);


    void ExportAsParticleGenAndTwoWorldsFormat(std::stringstream& output);
    void ExportAsE2160Format(std::stringstream& output);
    void ExportAsKsFormat(std::stringstream& output);


    void InitializeHashMap();

    void WriteToParticleGenAndTwoWorldsFormat(BinFile& output_file_buff);
    void WriteToE2160Format(BinFile& output_file_buff);
    void WriteToKsFormat(BinFile& output_file_buff);


    ParticleGlobals::ENCurveOrTeselateMode m_mode;

    int64_t m_curve_iel_index;
    size_t m_number_of_single_curve_points_checksum;

    int64_t m_teselate_iel_index;
    size_t m_number_of_single_teselate_points_checksum;

    std::unordered_map<std::string, int64_t> m_labels_map = {};

    ParticleData m_particle_data = {};

    ParticleFileVersionInfo m_prt_file_version_info = {};


    static uint32_t particle_number;
};


#endif // !PARTICLE_CLASS_HPP
