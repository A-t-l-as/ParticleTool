#ifndef CUSTOM_BLOCK_CLASS_HPP
#define CUSTOM_BLOCK_CLASS_HPP

#include "CustomBlockData.hpp"
#include "File/BinFile.hpp"
#include "../ParticleFileVersionInfo.hpp"

#include <sstream>

class CustomBlockClass
{
public:
    CustomBlockClass(ParticleFileVersionInfo arg_prt_file_version_info = ParticleFileVersionInfo(),
                     bool arg_is_child = false);

    void ReadFrom(BinFile& buff);
    void ExportTo(std::stringstream& output);

    void SetPrtVersion(const ParticleFileVersionInfo& arg_prt_file_version_info);

private:
    void ReadFromKsFile(BinFile& buff);
    void ReadFromPgAndTwAndE2160File(BinFile& buff);

    void ExportAsKsFormat(std::stringstream& output);

    bool m_is_child;

    CustomBlockData m_custom_block_data = {};
    ParticleFileVersionInfo m_prt_file_version_info = {};
};


#endif // !CUSTOM_BLOCK_CLASS_HPP
