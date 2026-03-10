#ifndef EMITER_CLASS_HPP
#define EMITER_CLASS_HPP

#include <cstdint>
#include <string>
#include <unordered_map>
#include "File/BinFile.hpp"
#include "EmiterData.hpp"
#include "../../ParticleFileVersionInfo.hpp"
#include "../../../AodCompilator/GlobalQueues.hpp"

class EmiterClass
{
public:
    EmiterClass(
                    const ParticleGlobals::ENAppModes& arg_app_mode,
                    ParticleFileVersionInfo arg_prt_file_version_info = ParticleFileVersionInfo(),
                    std::string arg_emiter_name = std::string(),
                    uint8_t arg_fourth_byte_of_header = 0
                );

    void ReadFrom(BinFile& buff);
    void ExportTo(std::stringstream& output);


    void ParseFrom(std::string& arg_line, GlobalQueues& arg_queues);
    void WriteTo(BinFile& output_file_buff);


    void SetPrtVersion(ParticleFileVersionInfo arg_prt_file_version_info)
    {
        if (arg_prt_file_version_info.particle_version ==
            ParticleGlobals::particle_type_value::two_worlds_particle)
        {
            m_fourth_byte_of_header = ParticleGlobals::tw_new_format_fourth_byte_of_header;
        }

        m_emiter_data.ConvertTeselatesAndCurvesWholeFormat
            (m_prt_file_version_info.particle_version, arg_prt_file_version_info.particle_version);

        m_prt_file_version_info = arg_prt_file_version_info;
    }

private:
    void InitializeHashMap();

    void ReadFromKsFile(BinFile& buff);
    void ReadFromParticleGenAndTwoWorldsFile(BinFile& buff);
    void ReadFromE2160File(BinFile& buff);


    void ExportAsKsFormat(std::stringstream& output);
    void ExportAsParticleGenAndTwoWorldsFormat(std::stringstream& output);
    void ExportAsE2160Format(std::stringstream& output);


    void WriteToKsFormat(BinFile& output_file_buff);
    void WriteToParticleGenAndTwoWorldsFormat(BinFile& output_file_buff);
    void WriteToE2160Format(BinFile& output_file_buff);

    uint8_t m_fourth_byte_of_header;
    static uint32_t emiter_number;

    ParticleGlobals::curve_or_teselate_mode m_mode;

    int64_t m_curve_iel_index;
    size_t m_number_of_single_curve_points_checksum;

    int64_t m_teselate_iel_index;
    size_t m_number_of_single_teselate_points_checksum;

    std::unordered_map<std::string, int64_t> m_labels_map = {};

    EmiterData m_emiter_data = {};

    ParticleFileVersionInfo m_prt_file_version_info = {};

    uint32_t m_write_cast_shadows_to_bin;
};


#endif // !EMITER_CLASS_HPP
