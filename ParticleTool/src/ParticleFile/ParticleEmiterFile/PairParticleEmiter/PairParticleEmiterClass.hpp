#ifndef PAIR_PARTICLE_EMITER_CLASS_HPP
#define PAIR_PARTICLE_EMITER_CLASS_HPP

#include <string>
#include "PairParticleEmiterData.hpp"
#include "../../ParticleFileVersionInfo.hpp"
#include "File/BinFile.hpp"
#include "../../../AodCompilator/GlobalQueues.hpp"

class PairParticleEmiterClass
{
public:
    PairParticleEmiterClass (
                            const ParticleGlobals::ENAppModes& arg_app_mode,
                            ParticleFileVersionInfo arg_prt_file_version_info = ParticleFileVersionInfo(),
                            std::string arg_pair_particle_emiter_name = std::string()
                            );

    void ReadFrom(BinFile& buff);
    void ExportTo(std::stringstream& output);


    void ParseFrom(std::string& arg_line, GlobalQueues& arg_queues);
    void WriteTo(BinFile& output_file_buff);

    void SetPrtVersion(ParticleFileVersionInfo arg_prt_file_version_info)
    {
        m_prt_file_version_info = arg_prt_file_version_info;
    }

private:

    void ReadFromPgAndTwAndE2160File(BinFile& buff);
    void ReadFromKsFile(BinFile& buff);

    void ExportAsPgAndTwAndE2160Format(std::stringstream& output);
    void ExportAsKsFormat(std::stringstream& output);

    void WriteToPgAndTwAndE2160Format(BinFile& output_file_buff);
    void WriteToKsFormat(BinFile& output_file_buff);


    PairParticleEmiterData m_pair_particle_emiter_data = {};
    ParticleFileVersionInfo m_prt_file_version_info = {};


    static uint32_t group_number;
};



#endif // !PAIR_PARTICLE_EMITER_CLASS_HPP
