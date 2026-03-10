#include "IntroductionHeaderClass.hpp"

#include "Console/Console.hpp"
#include "MshCustomBlockVectors.hpp"
#include "Utils/Globals.hpp"
#include "Compilator/SimpleCompilator.hpp"
#include <filesystem>

#include "System/MyGuid.hpp"

using namespace std;


void IntroductionHeaderClass::ParseAndWriteTo(BinFile& output_file_buff, bool is_child)
{
    if ( !std::filesystem::exists(m_extra_data_file_path) )
	{
        CONSOLE_OUT.PrintLn(m_extra_data_file_path,
                " was not found.", Mess::endl,
                "The program will attempt to generate headers and initial mesh data blocks...");

		switch (m_prt_file_version_info.particle_version)
		{
            case ParticleGlobals::particle_type_value::dynamic_particle:
                WriteToDynamicParticleFormat(output_file_buff, is_child);
            break;

            case ParticleGlobals::particle_type_value::ks_particles_emiter:
                WriteToKsParticleEmiterFormat(output_file_buff, is_child);
            break;

            case ParticleGlobals::particle_type_value::e2160_particle:
            break;

            case ParticleGlobals::particle_type_value::particle_gen_particle:
            case ParticleGlobals::particle_type_value::two_worlds_particle:
                WriteToPgAndTwFormat(output_file_buff);
            break;

            default:
            break;
		}
	}

    if (std::filesystem::exists(m_extra_data_file_path))
	{
        CONSOLE_OUT.PrintLn(m_extra_data_file_path.string(), " was found and opened for compilation.", Mess::endl);

        HashMapsBase simple_hash_maps;
        simple_hash_maps.Init();

        bool errror_handler = Globals::success_code;
        SimpleCompilator my_extra_data_cpp_compilator(output_file_buff, simple_hash_maps, errror_handler);
        my_extra_data_cpp_compilator.CompileFile(m_extra_data_file_path);
	}

}

void IntroductionHeaderClass::WriteToDynamicParticleFormat(BinFile& output_file_buff, bool is_child)
{
	uint8_t magic_bytes_format[] = { 'M', 'E', 'S', 'H' };
	vector<uint32_t> custom_block_data = {};

	if (!is_child)
	{
		uint8_t header_ff_a1_d0_30[] = { 0xFF, 0xA1, 0xD0, 0x30 };
		
		const uint32_t particle_file_type_value = static_cast<uint32_t>(m_prt_file_version_info.particle_version);

		//header
        output_file_buff.WriteValue(header_ff_a1_d0_30);
        output_file_buff.WriteValue(particle_file_type_value);

		//GUID
        MyGuid().WriteTo(output_file_buff);
		
        MCBV::SetCustomBlockVersionForNotChild(custom_block_data, m_prt_file_version_info.dynamic_particle_version);
	}

	if (is_child)
	{
        MCBV::SetCustomBlockVersionForChild(custom_block_data, m_prt_file_version_info.dynamic_particle_version);
	}

    output_file_buff.WriteValue(magic_bytes_format);
    output_file_buff.WriteVector(custom_block_data);
}

void IntroductionHeaderClass::WriteToKsParticleEmiterFormat(BinFile& output_file_buff, bool is_child)
{
	if (!is_child)
	{
		uint8_t header_ff_a1_d0_30[] = { 0xFF, 0xA1, 0xD0, 0x30 };

		const uint32_t particle_file_type_value = static_cast<uint32_t>(m_prt_file_version_info.particle_version);

		uint8_t magic_bytes_format[] = { 'M', 'E', 'S', 'H' };

		//header
        output_file_buff.WriteValue(header_ff_a1_d0_30);
        output_file_buff.WriteValue(particle_file_type_value);

		//GUID
        MyGuid().WriteTo(output_file_buff);
		
		//Magic bytes MESH
        output_file_buff.WriteValue(magic_bytes_format);

        output_file_buff.WriteVector( MCBV::GetKsParticleEmiterCustomBlockData() );
	}
}


void IntroductionHeaderClass::WriteToPgAndTwFormat(BinFile& output_file_buff) const
{
	uint8_t pg_and_tw_format_header[] = { 'P', 'R', 0, 0 };
	const uint8_t tw_unique_format_value = 2;

    if (m_prt_file_version_info.particle_version == ParticleGlobals::particle_type_value::particle_gen_particle)
	{
        output_file_buff.WriteValue(pg_and_tw_format_header);

		return;
	}

    if (m_prt_file_version_info.particle_version == ParticleGlobals::particle_type_value::two_worlds_particle)
	{
		pg_and_tw_format_header[3] = tw_unique_format_value;

        output_file_buff.WriteValue(pg_and_tw_format_header);

		return;
	}
}

