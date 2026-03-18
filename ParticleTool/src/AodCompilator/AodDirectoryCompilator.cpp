#include "AodDirectoryCompilator.hpp"
#include "SpecialFlagsCompilator.hpp"
#include "GlobalQueues.hpp"
#include "../ParticleFile/IntroHeader/IntroductionHeaderClass.hpp"
#include "File/TextFile.hpp"
#include "../ParticleFile/ParticleFileVersionConsts.hpp"
#include "Utils/TxtUtils.hpp"

using namespace std;

void AodDirectoryCompilator::InitializeFormatHashMaps()
{
    m_list_of_prt_file_ver_info[ParticleGlobals::ENParticleTypeValue::not_particle] = ParticleFileVersionInfo();

    m_list_of_prt_file_ver_info[ParticleGlobals::ENParticleTypeValue::dynamic_particle] =
        ParticleFileVersionConsts::ks_dynamic_file_type;

    m_list_of_prt_file_ver_info[ParticleGlobals::ENParticleTypeValue::ks_particles_emiter] =
        ParticleFileVersionConsts::ks_particle_file_type;

    m_list_of_prt_file_ver_info[ParticleGlobals::ENParticleTypeValue::e2160_particle] =
        ParticleFileVersionConsts::e2160_particle_edit_file_type;

    m_list_of_prt_file_ver_info[ParticleGlobals::ENParticleTypeValue::two_worlds_particle] =
        ParticleFileVersionConsts::two_worlds_particle_edit_file_type;

    m_list_of_prt_file_ver_info[ParticleGlobals::ENParticleTypeValue::particle_gen_particle] =
        ParticleFileVersionConsts::particle_gen_file_type;
}

void AodDirectoryCompilator::GetPrtVersion(const std::string& arg_line,
                                  ParticleGlobals::ENParticleTypeValue& dst,
                                  ParticleFileVersionInfo& arg_particle_file_version_info)
{

    if ( arg_line.starts_with(ParticleGlobals::version_str_with_space) )
	{
        const std::string m_help_str =
            arg_line.substr
            (
                ParticleGlobals::version_str_with_space_len, arg_line.length() - ParticleGlobals::version_str_with_space_len
            );


        dst = static_cast<ParticleGlobals::ENParticleTypeValue>(stoull(m_help_str, nullptr, ParticleGlobals::dec_base) + 1);

		DEBUG_PRINT("PRT VERSION = ");
		DEBUG_PRINT(to_string(static_cast<uint32_t>(dst)).c_str());
		DEBUG_PRINT("\n");

		arg_particle_file_version_info = m_list_of_prt_file_ver_info[dst];

		m_is_version_getted = true;
	}
}

void AodDirectoryCompilator::GetDynamicParticleVersion(  const std::string& arg_line,
                                                ParticleGlobals::ENParticleTypeValue& dst,
                                                ParticleFileVersionInfo& arg_particle_file_version_info)
{

    if (  arg_line.starts_with(ParticleGlobals::dynamic_name_str)  )
	{
        dst = ParticleGlobals::ENParticleTypeValue::dynamic_particle;
		arg_particle_file_version_info = m_list_of_prt_file_ver_info[dst];

		DEBUG_PRINT("PRT VERSION = ");
		DEBUG_PRINT(to_string(static_cast<uint32_t>(dst)).c_str());
		DEBUG_PRINT("\n");

		m_is_version_getted = true;
	}

}


AodDirectoryCompilator::AodDirectoryCompilator    (
                                    BinFile& arg_output_file_buffer,
                                    GlobalQueues& arg_queues
                                ) :

    r_output_file_buffer(arg_output_file_buffer),
    r_queues(arg_queues),

    m_particle_type_version(ParticleGlobals::ENParticleTypeValue::not_particle),
	m_is_version_getted(false),
    m_inside_obj_type(std::string()),
    m_inside_obj_name(std::string()),
	bracket_counter(-1),

    its_pair_particle_emiter( false ),
    m_end_of_file_initialize_switch(true)
{}


void AodDirectoryCompilator::CompileDirectory(const std::filesystem::path& input_dir_path)
{
    const string input_directory_name = input_dir_path.stem().string();

    TextFile aod_file;
    aod_file.LoadFrom( input_dir_path / (input_directory_name + ParticleGlobals::my_aod_format_str) );
    aod_file.Informations();
    aod_file.ExitWhenFileDontExist();

    std::vector<char> file_buffer = aod_file.GetFileBuffer();

    InitializeFormatHashMaps();

    string temporary_string_file_buffer = aod_file.GetRepresentationInString();

    const std::string particles_emiter_macro_text = "__PARTICLES_EMITER_MACRO__";

    StringUtils::ReplaceAllOccurrences
        (temporary_string_file_buffer, ParticleGlobals::particles_emiter_name_str, particles_emiter_macro_text);

    this->r_queues.m_effect_names_q =
        Misc::FindLineStrings(temporary_string_file_buffer.data(),
                                 temporary_string_file_buffer.size(), ParticleGlobals::effect_type_name_str_with_space);

    this->r_queues.m_emiter_names_q =
        Misc::FindLineStrings(temporary_string_file_buffer.data(),
                                 temporary_string_file_buffer.size(), ParticleGlobals::emiter_type_name_str_with_space);

    this->r_queues.m_particle_names_q =
        Misc::FindLineStrings(temporary_string_file_buffer.data(),
                                 temporary_string_file_buffer.size(), ParticleGlobals::particle_type_name_str_with_space);

    this->r_queues.m_pair_particle_emiter_names_q =
        Misc::FindLineStrings(temporary_string_file_buffer.data(),
                                 temporary_string_file_buffer.size(), ParticleGlobals::pair_particle_type_name_str_with_space);

    StringUtils::ReplaceAllOccurrences
        (temporary_string_file_buffer, particles_emiter_macro_text, ParticleGlobals::particles_emiter_name_str);

    this->r_queues.m_annotations_q = Misc::FindLineStrings(file_buffer.data(), file_buffer.size(), "annotation ");

    this->r_queues.m_slot_strings_q = Misc::FindLineStrings(file_buffer.data(), file_buffer.size(), "slotStrings ");
    this->r_queues.m_texture_q = Misc::FindLineStrings(file_buffer.data(), file_buffer.size(), "texture ");
    this->r_queues.m_mesh_q = Misc::FindLineStrings(file_buffer.data(), file_buffer.size(), "mesh ");
    this->r_queues.m_bump_texture_q = Misc::FindLineStrings(file_buffer.data(), file_buffer.size(), "bumpTexture ");
    this->r_queues.m_emits_groups_q = Misc::FindLineStrings(file_buffer.data(), file_buffer.size(), "emitsGroups ");

    // Only For Dynamic Particle:
    this->r_queues.m_dynamic_particle_Texture_q = Misc::FindLineStrings(file_buffer.data(), file_buffer.size(), "Texture ");
    this->r_queues.m_dynamic_particle_Mesh_q = Misc::FindLineStrings(file_buffer.data(), file_buffer.size(), "Mesh ");

    aod_file.CleanTxtFileBufferFromMultiSpaces(true);
    CompileTxtFileToBinBuffer(aod_file, input_dir_path, input_directory_name);
}

// MyAod txt
void AodDirectoryCompilator::CompileTxtFileToBinBuffer(
                                                TextFile& aod_file,
                                                const std::filesystem::path& input_dir_path,
                                                const std::string& input_dir_name
                                              )
{
    EffectClass single_effect(ParticleGlobals::ENAppModes::m_import);
    EmiterClass single_emiter(ParticleGlobals::ENAppModes::m_import);
    ParticleClass single_particle(ParticleGlobals::ENAppModes::m_import);
    PairParticleEmiterClass single_pair_particle_emiter(ParticleGlobals::ENAppModes::m_import);

    const std::vector<char>& clean_file = aod_file.GetCleanFileBuffer();
    std::string_view file_view(clean_file.data(), clean_file.size());

    std::size_t start = 0;
    while (true)
	{
        std::size_t end = file_view.find(';', start);

        if (end == std::string_view::npos)
            break;

        std::string instruction( file_view.substr(start, end - start ) );

        //CONSOLE_OUT.Print("----\n\"", instruction, "\"\n");
        DEBUG_PRINT("----\n\"", instruction, "\"\n");

        if (
            InterpretInstructions   (
                                        instruction,
                                        single_effect,
                                        single_emiter,
                                        single_particle,
                                        single_pair_particle_emiter
                                    )
                                    ==
                                    true
           )
        {
            break;
        }

        DEBUG_PRINT("----\n");

        start = end + 1;

	}


    const std::filesystem::path extra_data_file_path = input_dir_path / (input_dir_name + "_extra_data.cpp");

    if (m_particle_type_version == ParticleGlobals::ENParticleTypeValue::dynamic_particle)
	{
        bool error_handler = Globals::success_code;

        SpecialFlagsCompilator flags_compilator(error_handler);

        const char compilator_flags_cfg_file_name[] = "__compilator_flags__.cfg";

        flags_compilator.CompileFile( input_dir_path / compilator_flags_cfg_file_name );
		m_particle_file_version_info = flags_compilator.GetDynamicParticleVersion();

        IntroductionHeaderClass my_dynamic_prt_introduction_header(m_particle_file_version_info, extra_data_file_path);

        my_dynamic_prt_introduction_header.ParseAndWriteTo(r_output_file_buffer);

        CompileDynamicParticle(aod_file, input_dir_path);
        m_whole_dynamic_particle_container.WriteToFileBuffer(r_output_file_buffer);
	}
	

    if (m_particle_type_version != ParticleGlobals::ENParticleTypeValue::dynamic_particle)
    {
        IntroductionHeaderClass my_introduction_header(m_particle_file_version_info, extra_data_file_path);
        my_introduction_header.ParseAndWriteTo(r_output_file_buffer);
        m_whole_particle_emiter_container.WriteTo(r_output_file_buffer);
	}


}


bool AodDirectoryCompilator::InterpretInstructions(
                                            string& instruction,
                                            EffectClass& single_effect,
                                            EmiterClass& single_emiter,
                                            ParticleClass& single_particle,
                                            PairParticleEmiterClass& single_pair_particle_emiter
                                          )
{	
	if (!m_is_version_getted)
	{
		GetDynamicParticleVersion(instruction, m_particle_type_version, m_particle_file_version_info);
	}

	if (!m_is_version_getted)
	{
		GetPrtVersion(instruction, m_particle_type_version, m_particle_file_version_info);
	}

	switch (m_particle_type_version)
	{
        case ParticleGlobals::ENParticleTypeValue::dynamic_particle:

            return true;

        break;

        case ParticleGlobals::ENParticleTypeValue::ks_particles_emiter:
        case ParticleGlobals::ENParticleTypeValue::e2160_particle:
        case ParticleGlobals::ENParticleTypeValue::two_worlds_particle:
        case ParticleGlobals::ENParticleTypeValue::particle_gen_particle:
            InterpretParticlesEmiterInstructions
            (
                instruction,
                single_effect,
                single_emiter,
                single_particle,
                single_pair_particle_emiter
            );
        break;

        default: break;
	}

	return false;
}

void AodDirectoryCompilator::InterpretParticlesEmiterInstructions(
                                                            string& instruction,
                                                            EffectClass& single_effect,
                                                            EmiterClass& single_emiter,
                                                            ParticleClass& single_particle,
                                                            PairParticleEmiterClass& single_pair_particle_emiter
                                                        )
{
    string obj_name;
    TU::GetSingleString(instruction, ParticleGlobals::particles_emiter_name_str, obj_name);

	if (its_pair_particle_emiter == false)
	{
        TU::GetObjTypeFromQueue(instruction, m_inside_obj_type,
                       m_inside_obj_name, ParticleGlobals::effect_type_name_str_with_space, this->r_queues.m_effect_names_q);

        TU::GetObjTypeFromQueue(instruction, m_inside_obj_type,
                       m_inside_obj_name, ParticleGlobals::emiter_type_name_str_with_space, this->r_queues.m_emiter_names_q);

        TU::GetObjTypeFromQueue(instruction, m_inside_obj_type,
                       m_inside_obj_name, ParticleGlobals::particle_type_name_str_with_space, this->r_queues.m_particle_names_q);
	}

    TU::GetObjTypeFromQueue(instruction, m_inside_obj_type, m_inside_obj_name,
                   ParticleGlobals::pair_particle_type_name_str_with_space, this->r_queues.m_pair_particle_emiter_names_q);

    if (m_inside_obj_type == ParticleGlobals::effect_type_name_str)
	{
		DEBUG_PRINT("ITS EFFECT!!!\n");

        CompileObject<EffectClass>(
                                   instruction,
                                   single_effect,
                                   m_whole_particle_emiter_container
                                  );
	}

    if (m_inside_obj_type == ParticleGlobals::emiter_type_name_str)
	{
		DEBUG_PRINT("ITS EMITER!!!\n");

        CompileObject<EmiterClass>(
                                   instruction,
                                   single_emiter,
                                   m_whole_particle_emiter_container
                                  );
	}

    if (m_inside_obj_type == ParticleGlobals::particle_type_name_str)
	{
		DEBUG_PRINT("ITS PARTICLE!!!\n");

        CompileObject<ParticleClass>(
                                     instruction,
                                     single_particle,
                                     m_whole_particle_emiter_container
                                    );
	}

    if (m_inside_obj_type == ParticleGlobals::pair_particle_type_name_str)
	{
		its_pair_particle_emiter = true;
		DEBUG_PRINT("ITS PAIR PARTICLE EMITER!!!\n");

        CompileObject<PairParticleEmiterClass>(
                                                instruction,
                                                single_pair_particle_emiter,
                                                m_whole_particle_emiter_container
                                              );

	}


	if (m_inside_obj_type == "")
	{
        CompileEndOfFile(instruction, m_whole_particle_emiter_container.GetEndOfParicleRef());

		DEBUG_PRINT("ITS INTRO OR END OF FILE!!!\n");
	}

}


void AodDirectoryCompilator::CompileEndOfFile(string& instruction, ParticleEndClass& single_particle_end)
{
	if (m_end_of_file_initialize_switch == true)
	{
		single_particle_end = ParticleEndClass(m_particle_file_version_info);

		m_end_of_file_initialize_switch = false;
	}

	single_particle_end.ParseFrom(instruction);

}


void AodDirectoryCompilator::CompileDynamicParticle(TextFile& aod_file, const std::filesystem::path& input_dir_path)
{
    aod_file.ClearCleanBuffer();
    aod_file.CleanTxtFileBufferFromMultiSpaces(false);
    string instruction = string();

    DynamicParticleClass single_dynamic_particle
        (ParticleGlobals::ENAppModes::m_import, CfgFileData(), m_particle_file_version_info, input_dir_path);

    single_dynamic_particle.ParseFrom(instruction, this->r_queues, aod_file.GetCleanFileBuffer());

    m_whole_dynamic_particle_container.Insert( single_dynamic_particle );
}
