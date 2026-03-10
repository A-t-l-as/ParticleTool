#include "ParticleEndClass.hpp"
#include "../../../ParticleGlobals.hpp"

#include "Utils/TxtUtils.hpp"

using namespace std;

ParticleEndClass::ParticleEndClass(ParticleFileVersionInfo arg_prt_file_version_info)
	: m_prt_file_version_info(arg_prt_file_version_info)
{
}

void ParticleEndClass::ParseFrom(string& arg_line)
{
    TU::GetOneValue<uint32_t>(arg_line, "gameRate", m_particle_end_data.gamerate);

	for (int i = 0; i < m_prt_file_version_info.size_of_end_bonus_data; ++i)
        TU::GetOneValue<float>(arg_line, "endValue_" + to_string(i), m_particle_end_data.end_particle_values[i]);
	
}

void ParticleEndClass::WriteTo(BinFile& output_file_buff)
{
    switch (m_prt_file_version_info.particle_version)
    {
        case ParticleGlobals::particle_type_value::ks_particles_emiter:
            WriteToKsFormat(output_file_buff);
        break;

        case ParticleGlobals::particle_type_value::dynamic_particle:
        break;


        case ParticleGlobals::particle_type_value::particle_gen_particle:
        case ParticleGlobals::particle_type_value::two_worlds_particle:
            WriteToPgAndTwFormat(output_file_buff);
        break;

        case ParticleGlobals::particle_type_value::e2160_particle:
            WriteToE2160Format(output_file_buff);
        break;


        default: break;
    }

}

void ParticleEndClass::WriteToPgAndTwFormat(BinFile& output_file_buff) const
{
    output_file_buff.WriteArrayFromTo(m_particle_end_data.end_particle_values, 0,
                                      m_prt_file_version_info.size_of_end_bonus_data - 1);
}

void ParticleEndClass::WriteToE2160Format(BinFile& output_file_buff) const
{
    output_file_buff.WriteValue(m_particle_end_data.gamerate);

    output_file_buff.WriteArrayFromTo(m_particle_end_data.end_particle_values, 0,
                                      m_prt_file_version_info.size_of_end_bonus_data - 1);
}

void ParticleEndClass::WriteToKsFormat(BinFile& output_file_buff) const
{
    output_file_buff.WriteValue(m_particle_end_data.gamerate);
}


void ParticleEndClass::ReadFromPgAndTwFile(BinFile& buff)
{

    buff.ReadArray(m_particle_end_data.end_particle_values, m_prt_file_version_info.size_of_end_bonus_data);

    m_particle_end_data.gamerate = 0;
}



void ParticleEndClass::ReadFromE2160File(BinFile& buff)
{
    buff.ReadValue(m_particle_end_data.gamerate);

    buff.ReadArray(m_particle_end_data.end_particle_values, m_prt_file_version_info.size_of_end_bonus_data);
}


void ParticleEndClass::ReadFromKsFile(BinFile& buff)
{
    buff.ReadValue(m_particle_end_data.gamerate);
}


void ParticleEndClass::ReadFrom(BinFile& buff)
{
    switch (m_prt_file_version_info.particle_version)
    {
        case ParticleGlobals::particle_type_value::ks_particles_emiter:
            ReadFromKsFile(buff);
        break;

        case ParticleGlobals::particle_type_value::dynamic_particle:
        break;


        case ParticleGlobals::particle_type_value::particle_gen_particle:
        case ParticleGlobals::particle_type_value::two_worlds_particle:
            ReadFromPgAndTwFile(buff);
        break;

        case ParticleGlobals::particle_type_value::e2160_particle:
            ReadFromE2160File(buff);
        break;


        default: break;
    }

}


void ParticleEndClass::ExportAsPgAndTwAndE2160Format(std::stringstream& output) const
{
    TU::WriteOneValueToSs
        ("gameRate", m_particle_end_data.gamerate, output, Globals::one_quad);

    for (int i = 0; i < m_prt_file_version_info.size_of_end_bonus_data; ++i)
    {
        TU::WriteOneValueToSs
            ("endValue_" + to_string(i), m_particle_end_data.end_particle_values[i], output, Globals::one_quad);
    }
}


void ParticleEndClass::ExportAsKsFormat(std::stringstream& output) const
{
    TU::WriteOneValueToSs("gameRate", m_particle_end_data.gamerate, output, Globals::one_quad);
}


void ParticleEndClass::ExportTo(std::stringstream& output)
{
    switch (m_prt_file_version_info.particle_version)
    {

        case ParticleGlobals::particle_type_value::ks_particles_emiter:
            ExportAsKsFormat(output);
        break;

        case ParticleGlobals::particle_type_value::dynamic_particle:
        break;


        case ParticleGlobals::particle_type_value::e2160_particle:
        case ParticleGlobals::particle_type_value::two_worlds_particle:
        case ParticleGlobals::particle_type_value::particle_gen_particle:
            ExportAsPgAndTwAndE2160Format(output);
        break;

        default: break;
    }

}









