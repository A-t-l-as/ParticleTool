#include "CustomBlockClass.hpp"
#include "Compilator/CompilatorValueTypes.hpp"

#include <format>

using namespace std;

CustomBlockClass::CustomBlockClass(ParticleFileVersionInfo arg_prt_file_version_info, bool arg_is_child) : 
    m_prt_file_version_info(arg_prt_file_version_info),
    m_is_child(arg_is_child)
{
}


void CustomBlockClass::SetPrtVersion(const ParticleFileVersionInfo& arg_prt_file_version_info)
{
    if (m_prt_file_version_info.particle_version ==
            ParticleGlobals::particle_type_value::dynamic_particle
        &&
        m_prt_file_version_info.dynamic_particle_version !=
               ParticleGlobals::old_dynamic_particle_type_value::not_old_dynamic_particle
        &&
        arg_prt_file_version_info.particle_version ==
               ParticleGlobals::particle_type_value::dynamic_particle
        &&
        arg_prt_file_version_info.dynamic_particle_version !=
               ParticleGlobals::old_dynamic_particle_type_value::not_old_dynamic_particle
        )
    {
        m_custom_block_data.SetCustomBlockVersion
        (
            m_prt_file_version_info.dynamic_particle_version,
            arg_prt_file_version_info.dynamic_particle_version,
            m_is_child
        );
    }


    m_prt_file_version_info = arg_prt_file_version_info;
}


void CustomBlockClass::ReadFromKsFile(BinFile& buff)
{
    
    for (int i = 0; i < sizeof(uint32_t); ++i)
        buff.ReadValue(m_custom_block_data.format[i]);


    for (size_t i = 0; i < m_prt_file_version_info.custom_data_block_size; ++i)
    {
        uint32_t temp_value = 0;
        buff.ReadValue(temp_value);
        m_custom_block_data.data.push_back(temp_value);
    }

}


void CustomBlockClass::ReadFromPgAndTwAndE2160File(BinFile& buff)
{
    m_custom_block_data.format[0] = 'M';
    m_custom_block_data.format[1] = 'E';
    m_custom_block_data.format[2] = 'S';
    m_custom_block_data.format[3] = 'H';

    m_custom_block_data.data = { 1, 2, 0xFFFFFFFF };

    constexpr size_t number_of_zeros = 0x264 / 0x4;
    for (size_t i = 0; i < number_of_zeros; ++i)
        m_custom_block_data.data.push_back(0);


    constexpr size_t number_of_mini_blocks = 77;

    constexpr uint64_t dot_euro_dot_euro_ascii = 0x80008000;
    constexpr uint64_t dot_euro_dot_dot_ascii = 0x00008000;

    constexpr size_t number_of_zeros_in_mini_block = 0x24 / 0x4;

    for (size_t j = 0; j < number_of_mini_blocks; ++j)
    {
        m_custom_block_data.data.push_back(dot_euro_dot_euro_ascii);
        m_custom_block_data.data.push_back(dot_euro_dot_dot_ascii);

        for (size_t i = 0; i < number_of_zeros_in_mini_block; ++i)
            m_custom_block_data.data.push_back(0);
    
    }

    constexpr size_t number_of_end_ints = 2;
    for (size_t i = 0; i < number_of_end_ints; ++i)
        m_custom_block_data.data.push_back(0);

}


void CustomBlockClass::ReadFrom(BinFile& buff)
{
    switch (m_prt_file_version_info.particle_version)
    {
        case ParticleGlobals::particle_type_value::dynamic_particle:
        case ParticleGlobals::particle_type_value::ks_particles_emiter:
            ReadFromKsFile(buff);
        break;

        case ParticleGlobals::particle_type_value::e2160_particle:
        case ParticleGlobals::particle_type_value::particle_gen_particle:
        case ParticleGlobals::particle_type_value::two_worlds_particle:
            ReadFromPgAndTwAndE2160File(buff);
        break;

        default: break;
    }

}


void CustomBlockClass::ExportAsKsFormat(std::stringstream& output)
{

    output << CompilatorValueTypes::c_struct_type_str << " DataBlock" << endl << "{" << endl;

    for (int i = 0; i < m_custom_block_data.c_format_size; ++i)
    {
        output << "\t"
               << CompilatorValueTypes::c_uint8_t_type_str
               << " format"
               << i
               << " = "
               << static_cast<uint32_t>(m_custom_block_data.format[i])
               << "; // "
               << m_custom_block_data.format[i]
               << endl;
    }

    for (size_t i = 0; i < m_custom_block_data.data.size(); ++i)
        output  << "\t"
                << CompilatorValueTypes::c_uint32_t_type_str
                << " data_var"
                << std::format("{:04}", i)
                << " = "
                << m_custom_block_data.data[i]
                << ";"
                << endl;

    output << "};" << endl << endl;

}

void CustomBlockClass::ExportTo(std::stringstream& output)
{
    switch (m_prt_file_version_info.particle_version)
    {

        case ParticleGlobals::particle_type_value::dynamic_particle:
        case ParticleGlobals::particle_type_value::ks_particles_emiter:
            ExportAsKsFormat(output);
        break;


        case ParticleGlobals::particle_type_value::e2160_particle:
        case ParticleGlobals::particle_type_value::particle_gen_particle:
        case ParticleGlobals::particle_type_value::two_worlds_particle:
        break;

        default: break;
    }

}

