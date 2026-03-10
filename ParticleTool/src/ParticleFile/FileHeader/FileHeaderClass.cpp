#include "FileHeaderClass.hpp"

using namespace std;


void FileHeaderClass::SetPrtVersion(const ParticleGlobals::particle_type_value& arg_particle_type_value)
{
     switch (arg_particle_type_value)
     {
        case ParticleGlobals::particle_type_value::two_worlds_particle:
             m_file_header_data.header[0] = 'P';
             m_file_header_data.header[1] = 'R';
             m_file_header_data.header[2] = '\0';
             m_file_header_data.header[3] = '\2';
             m_file_header_data.particle_file_type = ParticleGlobals::particle_type_value::not_particle;
        break;

        case ParticleGlobals::particle_type_value::particle_gen_particle:
             m_file_header_data.header[0] = 'P';
             m_file_header_data.header[1] = 'R';
             m_file_header_data.header[2] = '\0';
             m_file_header_data.header[3] = '\0';
             m_file_header_data.particle_file_type = ParticleGlobals::particle_type_value::not_particle;
        break;

        case ParticleGlobals::particle_type_value::e2160_particle:
        break;

        case ParticleGlobals::particle_type_value::dynamic_particle:
            m_file_header_data.header[0] = 0xFF;
            m_file_header_data.header[1] = 0xA1;
            m_file_header_data.header[2] = 0xD0;
            m_file_header_data.header[3] = 0x30;
            m_file_header_data.particle_file_type = ParticleGlobals::particle_type_value::dynamic_particle;
        break;

        case ParticleGlobals::particle_type_value::ks_particles_emiter:
            m_file_header_data.header[0] = 0xFF;
            m_file_header_data.header[1] = 0xA1;
            m_file_header_data.header[2] = 0xD0;
            m_file_header_data.header[3] = 0x30;
            m_file_header_data.particle_file_type = ParticleGlobals::particle_type_value::ks_particles_emiter;
        break;

        default: break;
    }

    m_app_particle_file_type = arg_particle_type_value;
}



void FileHeaderClass::ReadFrom(BinFile& buff)
{

    for (int i = 0; i < m_file_header_data.c_header_size; ++i)
    {
        buff.ReadValue( m_file_header_data.header[i] );
    }

    if(m_file_header_data.header[0] == 'P'  && 
       m_file_header_data.header[1] == 'R'  && 
       m_file_header_data.header[2] == '\0' &&
        m_file_header_data.header[3] == '\0'
        )
    {
        m_app_particle_file_type = ParticleGlobals::particle_type_value::particle_gen_particle;
    }

    if (m_file_header_data.header[0] == 'P' &&
        m_file_header_data.header[1] == 'R' &&
        m_file_header_data.header[2] == '\0' &&
        m_file_header_data.header[3] == '\1'
        )
    {
        m_app_particle_file_type = ParticleGlobals::particle_type_value::two_worlds_particle;
    }


    if (m_file_header_data.header[0] == 'P' &&
        m_file_header_data.header[1] == 'R' &&
        m_file_header_data.header[2] == '\0' &&
        m_file_header_data.header[3] == '\2'
        )
    {
        m_app_particle_file_type = ParticleGlobals::particle_type_value::two_worlds_particle;
    }

    if (//m_file_header_data.header[0] == '\0' &&
        m_file_header_data.header[1] == '\0' &&
        m_file_header_data.header[2] == '\0' &&
        m_file_header_data.header[3] == '\0'
        )
    {
        m_app_particle_file_type = ParticleGlobals::particle_type_value::e2160_particle;

        buff.MoveOverBy( - static_cast<int64_t>( sizeof(uint32_t) ) );
        return;
    }


    if (m_file_header_data.header[0] == 0xFF && 
        m_file_header_data.header[1] == 0xA1 &&
        m_file_header_data.header[2] == 0xD0 &&
        m_file_header_data.header[3] == 0x30)
    {

        buff.ReadValue(m_file_header_data.particle_file_type);

        m_app_particle_file_type = m_file_header_data.particle_file_type;

        m_file_header_data.guid = buff.ReadGuid();
    }
}



void FileHeaderClass::ExportAsKsFormat(std::stringstream& output) const
{
    output << "struct Header" << endl
        << "{" << endl;


    for (int i = 0; i < m_file_header_data.c_header_size; ++i)
    {
        output << "\tuint8_t header_main_flag_" << i << " = "
               << static_cast<int>(m_file_header_data.header[i]) << ";";

        if (isalpha(m_file_header_data.header[i]))
           output << " // " << m_file_header_data.header[i];

        output << endl;

    }

    output << "\tint32_t particle_file_type" << " = "
           << static_cast<int32_t>(m_file_header_data.particle_file_type) << ";" << endl;

    output << "\tGUID header_guid = " << m_file_header_data.guid << ";" << endl;

    output << "};" << endl << endl;

}

void FileHeaderClass::ExportAsPgAndTwFormat(std::stringstream& output) const
{
    output << "struct Header" << endl
           << "{" << endl;

    for (int i = 0; i < m_file_header_data.c_header_size; ++i)
    {
        output << "\tuint8_t header_main_flag_" << i << " = "
               << static_cast<int>(m_file_header_data.header[i]) << ";";

        if (isalpha(m_file_header_data.header[i]))
           output << " // " << m_file_header_data.header[i];

        output << endl;

    }
    
    output << "};" << endl << endl;
}

void FileHeaderClass::ExportAsE2160Format(std::stringstream& output) const
{
    output << "struct Header" << endl
           << "{"             << endl 
           << "};"            << endl << endl;
}


void FileHeaderClass::ExportTo(std::stringstream& output)
{
    switch (m_app_particle_file_type)
    {

        case ParticleGlobals::particle_type_value::particle_gen_particle:
        case ParticleGlobals::particle_type_value::two_worlds_particle:
            ExportAsPgAndTwFormat(output);
        break;

        case ParticleGlobals::particle_type_value::e2160_particle:
            ExportAsE2160Format(output);
        break;

        case ParticleGlobals::particle_type_value::dynamic_particle:
        case ParticleGlobals::particle_type_value::ks_particles_emiter:
            ExportAsKsFormat(output);
        break;

        default: break;
    }

}
