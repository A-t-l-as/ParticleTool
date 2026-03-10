#ifndef PARTICLE_END_CLASS_HPP
#define PARTICLE_END_CLASS_HPP

#include <string>
#include "ParticleEndData.hpp"
#include "../../ParticleFileVersionInfo.hpp"

#include "File/BinFile.hpp"

class ParticleEndClass
{
public:
    ParticleEndClass(ParticleFileVersionInfo arg_prt_file_version_info = ParticleFileVersionInfo());

    void ReadFrom(BinFile& buff);
    void ExportTo(std::stringstream& output);

    void ParseFrom(std::string& arg_line);
    void WriteTo(BinFile& output_file_buff);


    void SetPrtVersion(ParticleFileVersionInfo arg_prt_file_version_info)
    {
        m_prt_file_version_info = arg_prt_file_version_info;
    }


private:

    void ReadFromPgAndTwFile(BinFile& buff);
    void ReadFromE2160File(BinFile& buff);
    void ReadFromKsFile(BinFile& buff);


    void ExportAsPgAndTwAndE2160Format(std::stringstream& output) const;
    void ExportAsKsFormat(std::stringstream& output) const;


    void WriteToPgAndTwFormat(BinFile& output_file_buff) const;
    void WriteToE2160Format(BinFile& output_file_buff) const;
    void WriteToKsFormat(BinFile& output_file_buff) const;


    ParticleEndData m_particle_end_data = {};
    ParticleFileVersionInfo m_prt_file_version_info = {};
};



#endif // !PARTICLE_END_CLASS_HPP
