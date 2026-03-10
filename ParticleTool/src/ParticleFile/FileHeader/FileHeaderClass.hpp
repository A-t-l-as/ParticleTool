#ifndef FILE_HEADER_CLASS_HPP
#define FILE_HEADER_CLASS_HPP


#include "File/BinFile.hpp"
#include "../../ParticleGlobals.hpp"
#include "FileHeaderData.hpp"

class FileHeaderClass
{
public:
    FileHeaderClass() :
        m_app_particle_file_type(ParticleGlobals::particle_type_value::not_particle)
    {}

    void ReadFrom(BinFile& buff);
    void ExportTo(std::stringstream& output);

    void SetPrtVersion(const ParticleGlobals::particle_type_value& arg_particle_type_value);

    ParticleGlobals::particle_type_value GetParticleFileType() const { return m_app_particle_file_type; }

    uint8_t GetFourthByteOfHeader() const { return m_file_header_data.header[3]; }

private:

    void ExportAsKsFormat(std::stringstream& output) const;
    void ExportAsPgAndTwFormat(std::stringstream& output) const;
    void ExportAsE2160Format(std::stringstream& output) const;

    FileHeaderData m_file_header_data = {};
    ParticleGlobals::particle_type_value m_app_particle_file_type;
};


#endif // !FILE_HEADER_CLASS_HPP
