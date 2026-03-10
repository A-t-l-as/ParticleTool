#ifndef INTRODUCTION_HEADER_CLASS_HPP
#define INTRODUCTION_HEADER_CLASS_HPP


#include "File/BinFile.hpp"
#include "../ParticleFileVersionInfo.hpp"

class IntroductionHeaderClass
{
public:
    IntroductionHeaderClass
    (
        ParticleFileVersionInfo arg_prt_file_version_info = ParticleFileVersionInfo(),
        std::filesystem::path arg_extra_data_file_path =  std::filesystem::path()
    ) :
        m_prt_file_version_info(arg_prt_file_version_info), m_extra_data_file_path(arg_extra_data_file_path)
    {}

    void ParseAndWriteTo(BinFile& output_bin_file_buff, bool is_child = false);


private:
    void WriteToDynamicParticleFormat(BinFile& output_bin_file_buff, bool is_child = false);

    void WriteToKsParticleEmiterFormat(BinFile& output_bin_file_buff, bool is_child = false);

    void WriteToPgAndTwFormat(BinFile& output_bin_file_buff) const;

    std::filesystem::path m_extra_data_file_path;
    ParticleFileVersionInfo m_prt_file_version_info = {};
};


#endif // !INTRODUCTION_HEADER_CLASS_HPP
