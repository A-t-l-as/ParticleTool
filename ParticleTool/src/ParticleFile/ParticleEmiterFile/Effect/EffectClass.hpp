#ifndef EFFECT_CLASS_HPP
#define EFFECT_CLASS_HPP

#include <string>
#include <unordered_map>
#include <cstdint>
#include "EffectData.hpp"
#include "File/BinFile.hpp"
#include "../../ParticleFileVersionInfo.hpp"
#include "../../../AodCompilator/GlobalQueues.hpp"

class EffectClass
{
public:
    EffectClass(
                    const ParticleGlobals::ENAppModes& arg_app_mode,
                    ParticleFileVersionInfo arg_prt_file_version_info = ParticleFileVersionInfo(),
                    std::string arg_effect_name = std::string()
                );

    void ReadFrom(BinFile& input_file_buff);
    void ExportTo(std::stringstream& output);

    void ParseFrom(std::string& arg_line, GlobalQueues& arg_queues);
    void WriteTo(BinFile& output_file_buff);


    void SetPrtVersion(ParticleFileVersionInfo arg_prt_file_version_info)
    {
        m_effect_data.ConvertTeselatesAndCurvesWholeFormat
            (m_prt_file_version_info.particle_version, arg_prt_file_version_info.particle_version);

        m_prt_file_version_info = arg_prt_file_version_info;
    }


private:
    void InitializeHashMap();

    void ReadFromParticleGenAndTwoWorldsFile(BinFile& input_file_buff);
    void ReadFromE2160File(BinFile& input_file_buff);


    void ExportAsParticleGenAndTwoWorldsFormat(std::stringstream& output);
    void ExportAsE2160Format(std::stringstream& output) const;


    void WriteToParticleGenAndTwoWorldsFormat(BinFile& output_file_buff);
    void WriteToE2160Format(BinFile& output_file_buff);

    ParticleGlobals::ENCurveOrTeselateMode m_mode;

    int64_t m_curve_iel_index;
    size_t m_number_of_single_curve_points_checksum;

    int64_t m_teselate_iel_index;
    size_t m_number_of_single_teselate_points_checksum;

    std::unordered_map<std::string, int64_t> m_labels_map = {};

    EffectData m_effect_data = {};

    ParticleFileVersionInfo m_prt_file_version_info = {};
};


#endif // !EFFECT_CLASS_HPP
