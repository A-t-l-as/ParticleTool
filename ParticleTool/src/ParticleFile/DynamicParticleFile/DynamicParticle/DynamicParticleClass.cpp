#include "DynamicParticleClass.hpp"
#include "Console/Console.hpp"
#include "../../IntroHeader/IntroductionHeaderClass.hpp"
#include "../../../AodCompilator/GlobalQueues.hpp"
#include "Utils/Misc.hpp"
#include "Utils/TxtUtils.hpp"

#include "../../../ParticleFile/CustomBlock/CustomBlockClass.hpp"

using namespace std;

void DynamicParticleClass::InitializeImportHashMaps()
{
    if (m_prt_file_version_info.dynamic_particle_version !=
        ParticleGlobals::old_dynamic_particle_type_value::e2150_old_dynamic_particle)
	{
        m_list_of_type_consts_for_import[""]					= 0;
        m_list_of_type_consts_for_import["Explosion"]			= 1;
        m_list_of_type_consts_for_import["Track"]				= 2;
        m_list_of_type_consts_for_import["ScaleableObject"]	= 3;
        m_list_of_type_consts_for_import["MappedExplosion"]	= 4;
        m_list_of_type_consts_for_import["FlatExplosion"]		= 5;
        m_list_of_type_consts_for_import["Laser"]				= 6;
        m_list_of_type_consts_for_import["LaserWall"]			= 7;
        m_list_of_type_consts_for_import["Shockwave"]			= 8;
        m_list_of_type_consts_for_import["Line"]				= 9;
        m_list_of_type_consts_for_import["ElectricalCannon"]	= 10;
        m_list_of_type_consts_for_import["Lighting"]			= 11;
        m_list_of_type_consts_for_import["Smoke"]				= 12;
        m_list_of_type_consts_for_import["Kilwater"]			= 13;
        m_list_of_type_consts_for_import["Blood"]				= 14;


        m_list_of_lighttype_consts_for_import["Const"]			= 1;
        m_list_of_lighttype_consts_for_import["Pyramid"]		= 2;
        m_list_of_lighttype_consts_for_import["Trapezium"]		= 3;
        m_list_of_lighttype_consts_for_import["Random"]		= 4;
	}


    if (m_prt_file_version_info.dynamic_particle_version ==
        ParticleGlobals::old_dynamic_particle_type_value::e2150_old_dynamic_particle)
	{
        m_list_of_type_consts_for_import[""]					= 0;
        m_list_of_type_consts_for_import["Explosion"]			= 1;
        m_list_of_type_consts_for_import["Track"]				= 2;
        m_list_of_type_consts_for_import["ScaleableObject"]	= 3;
        m_list_of_type_consts_for_import["MappedExplosion"]	= 4;
        m_list_of_type_consts_for_import["FlatExplosion"]		= 5;
        m_list_of_type_consts_for_import["Laser"]				= 6;
        m_list_of_type_consts_for_import["LaserWall"]			= 7;
        m_list_of_type_consts_for_import["Shockwave"]			= 8;
        m_list_of_type_consts_for_import["Line"]				= 9;
        m_list_of_type_consts_for_import["Sphere"]				= 10;
        m_list_of_type_consts_for_import["ElectricalCannon"]	= 11;
        m_list_of_type_consts_for_import["Lighting"]			= 12;
        m_list_of_type_consts_for_import["Smoke"]				= 13;
        m_list_of_type_consts_for_import["Kilwater"]			= 14;
        m_list_of_type_consts_for_import["Blood"]				= 15;

        m_list_of_lighttype_consts_for_import["Const"]			= 0;
        m_list_of_lighttype_consts_for_import["Pyramid"]		= 1;
        m_list_of_lighttype_consts_for_import["Trapezium"]		= 2;
        m_list_of_lighttype_consts_for_import["Random"]		= 3;

	}

}

void DynamicParticleClass::InitializeExportHashMaps()
{

    if (m_dynamic_particle_cfg.input_dynamic_particle_file_version_info.dynamic_particle_version !=
        ParticleGlobals::old_dynamic_particle_type_value::e2150_old_dynamic_particle)
    {
        m_list_of_type_consts_for_export[0] = "";
        m_list_of_type_consts_for_export[1] = "Explosion";
        m_list_of_type_consts_for_export[2] = "Track";
        m_list_of_type_consts_for_export[3] = "ScaleableObject";
        m_list_of_type_consts_for_export[4] = "MappedExplosion";
        m_list_of_type_consts_for_export[5] = "FlatExplosion";
        m_list_of_type_consts_for_export[6] = "Laser";
        m_list_of_type_consts_for_export[7] = "LaserWall";
        m_list_of_type_consts_for_export[8] = "Shockwave";
        m_list_of_type_consts_for_export[9] = "Line";
        m_list_of_type_consts_for_export[10] = "ElectricalCannon";
        m_list_of_type_consts_for_export[11] = "Lighting";
        m_list_of_type_consts_for_export[12] = "Smoke";
        m_list_of_type_consts_for_export[13] = "Kilwater";
        m_list_of_type_consts_for_export[14] = "Blood";

        m_list_of_lighttype_consts_for_export[1] = "Const";
        m_list_of_lighttype_consts_for_export[2] = "Pyramid";
        m_list_of_lighttype_consts_for_export[3] = "Trapezium";
        m_list_of_lighttype_consts_for_export[4] = "Random";
    }

    if (m_dynamic_particle_cfg.input_dynamic_particle_file_version_info.dynamic_particle_version ==
        ParticleGlobals::old_dynamic_particle_type_value::e2150_old_dynamic_particle)
    {
        m_list_of_type_consts_for_export[0] = "";
        m_list_of_type_consts_for_export[1] = "Explosion";
        m_list_of_type_consts_for_export[2] = "Track";
        m_list_of_type_consts_for_export[3] = "ScaleableObject";
        m_list_of_type_consts_for_export[4] = "MappedExplosion";
        m_list_of_type_consts_for_export[5] = "FlatExplosion";
        m_list_of_type_consts_for_export[6] = "Laser";
        m_list_of_type_consts_for_export[7] = "LaserWall";
        m_list_of_type_consts_for_export[8] = "Shockwave";
        m_list_of_type_consts_for_export[9] = "Line";
        m_list_of_type_consts_for_export[10] = "Sphere";
        m_list_of_type_consts_for_export[11] = "ElectricalCannon";
        m_list_of_type_consts_for_export[12] = "Lighting";
        m_list_of_type_consts_for_export[13] = "Smoke";
        m_list_of_type_consts_for_export[14] = "Kilwater";
        m_list_of_type_consts_for_export[15] = "Blood";

        m_list_of_lighttype_consts_for_export[0] = "Const";
        m_list_of_lighttype_consts_for_export[1] = "Pyramid";
        m_list_of_lighttype_consts_for_export[2] = "Trapezium";
        m_list_of_lighttype_consts_for_export[3] = "Random";

    }

}

DynamicParticleClass::DynamicParticleClass(
                                            const ParticleGlobals::ENAppModes& arg_app_mode,
                                            CfgFileData arg_cfg_file_data,
                                            ParticleFileVersionInfo arg_prt_file_version_info,
                                            std::filesystem::path arg_particle_directory_path
                                           ) :
    m_dynamic_particle_cfg(arg_cfg_file_data),
	m_prt_file_version_info(arg_prt_file_version_info),

    m_particle_directory_path(arg_particle_directory_path)
{
    if(arg_app_mode == ParticleGlobals::ENAppModes::m_import)
    {
        InitializeImportHashMaps();
    }

    if(arg_app_mode == ParticleGlobals::ENAppModes::m_export)
    {
        InitializeExportHashMaps();
    }
}


void DynamicParticleClass::ParseFrom
    (string& arg_line, GlobalQueues& arg_queues, const std::vector<char>& arg_clean_file_buffer)
{
    std::stringstream dynamic_particle_file_stream;

    if (arg_clean_file_buffer.empty() == false)
    {
        dynamic_particle_file_stream = stringstream(&arg_clean_file_buffer[0]);
    }

	const int introduction_number_of_lines = 3;

	// 1//DynamicParticle
	// 2//{
	// 3//}

    Misc::MoveByLinesInSS(dynamic_particle_file_stream, introduction_number_of_lines);

    getline(dynamic_particle_file_stream, arg_line);

    GetWholeObject(dynamic_particle_file_stream, m_dynamic_particle_data, arg_line, arg_queues);
}


void DynamicParticleClass::GetSingleObject
(
    std::stringstream& dynamic_particle_file_stream,
    DynamicParticleData& arg_dynamic_particle_data,
    string& arg_line,
    GlobalQueues& arg_queues
)
{


    if (arg_line.starts_with(ParticleGlobals::object_name_str_with_space))
	{
		DynamicParticleData child;

        GetWholeObject(dynamic_particle_file_stream, child, arg_line, arg_queues);

        arg_dynamic_particle_data.children.push_back( std::move(child) );

		++arg_dynamic_particle_data.number_of_nested_particles;
	}

}

void DynamicParticleClass::GetTime(DynamicParticleData& arg_dynamic_particle_data, string& arg_line)
{

    if ( arg_line.starts_with(ParticleGlobals::time_name_str_with_space) )
	{
        string m_help_str =
            arg_line.substr
            (
                ParticleGlobals::time_name_str_with_space_len,
                arg_line.length() - ParticleGlobals::time_name_str_with_space_len
            );

        float help_time_1 = 0.0f, help_time_2 = 0.0f;
        char comma = 0;

        std::istringstream iss(m_help_str);
        iss >> help_time_1 >> comma >> help_time_2;
        //sscanf_s(m_help_str.c_str(), "%f, %f", &help_time_1, &help_time_2);

		DEBUG_PRINT("Time = ");
        DEBUG_PRINT(help_time_1);
		DEBUG_PRINT(", ");
        DEBUG_PRINT(help_time_2);
		DEBUG_PRINT("\n");

		arg_dynamic_particle_data.time[0] = static_cast<float>(static_cast<int64_t>( help_time_1 * 1000.0 ));
		arg_dynamic_particle_data.time[1] = static_cast<float>(static_cast<int64_t>( (1.0 - help_time_2) * 1000.0 ));

	}

}


void DynamicParticleClass::GetWholeObject(
                                            std::stringstream& dynamic_particle_file_stream,
                                            DynamicParticleData& arg_dynamic_particle_data,
                                            string& arg_line,
                                            GlobalQueues& arg_queues
                                         )
{
	
    TU::GetSingleString(arg_line, "Object", arg_dynamic_particle_data.m_obj_name);

    Misc::MoveByLinesInSS(dynamic_particle_file_stream, 1);

	while(true)
	{
        getline(dynamic_particle_file_stream, arg_line);

		if (arg_line.substr(0, 1) == "}")
		{
			break;
		}

        GetSingleObject(dynamic_particle_file_stream, arg_dynamic_particle_data, arg_line, arg_queues);

        TU::GetSingleStringAndInterpretConst
            (arg_line, "Type", arg_dynamic_particle_data.type, m_list_of_type_consts_for_import);

        TU::GetSingleStringAndInterpretConst
            (arg_line, "LightType", arg_dynamic_particle_data.light_type, m_list_of_lighttype_consts_for_import);

        TU::GetOneValue<uint32_t>(arg_line, "Additive", arg_dynamic_particle_data.additive);

        TU::GetArrayValues<int32_t>
            (arg_line, "Frames", "%d", arg_dynamic_particle_data.frames, arg_dynamic_particle_data.frames_size);
		// /\ Dodatkowe obliczenia w metodzie CalculateImportantValues...

        TU::GetArrayValues<float>
            (arg_line, "Light", "%f", arg_dynamic_particle_data.light, arg_dynamic_particle_data.light_size);
		// /\ Dodatkowe obliczenia w metodzie CalculateImportantValues...

        TU::GetArrayValues<float>
            (arg_line, "Size", "%f", arg_dynamic_particle_data.size, arg_dynamic_particle_data.size_size);
		// /\ Dodatkowe obliczenia w metodzie CalculateImportantValues...

        TU::GetArrayValues<float>
            (arg_line, "Size2", "%f", arg_dynamic_particle_data.size_2, arg_dynamic_particle_data.size_2_size);

        TU::GetArrayValues<float>
            (arg_line, "Color", "%f", arg_dynamic_particle_data.color, arg_dynamic_particle_data.color_size);

        arg_dynamic_particle_data.alpha.ParseFrom(arg_line, "Alpha", "%f", "%d");

        TU::GetArrayValues<float>
            (arg_line, "Scale", "%f", arg_dynamic_particle_data.scale, arg_dynamic_particle_data.scale_size);
		 
        TU::GetArrayValues<float>
            (arg_line, "Position", "%f", arg_dynamic_particle_data.position, arg_dynamic_particle_data.position_size);
		// /\ Dodatkowe obliczenia w metodzie CalculateImportantValues...
		
        TU::GetArrayValues<float>(arg_line,
							    "Position2", 
								"%f", 
								arg_dynamic_particle_data.position_2, 
								arg_dynamic_particle_data.position_2_size);
		// /\ Dodatkowe obliczenia w metodzie CalculateImportantValues...

		GetTime(arg_dynamic_particle_data, arg_line);
		 
        TU::GetSingleStringFromQueue(arg_line, "Texture", arg_dynamic_particle_data.texture, arg_queues.m_dynamic_particle_Texture_q);
        TU::GetSingleStringFromQueue(arg_line, "Mesh", arg_dynamic_particle_data.mesh, arg_queues.m_dynamic_particle_Mesh_q);

        TU::GetOneValue<uint32_t>(arg_line, "Layer", arg_dynamic_particle_data.layer);

		DEBUG_PRINT("\n");
		DEBUG_PRINT("-----------------------\n");
		DEBUG_PRINT(arg_line.c_str()); DEBUG_PRINT("\n");
		DEBUG_PRINT("-----------------------\n");
		DEBUG_PRINT("\n");

	}
	
}


void DynamicParticleClass::WriteTo(BinFile& output_file_buff)
{
	WriteDynamicParticleDataToFileBuffer(output_file_buff, m_dynamic_particle_data);
}

void DynamicParticleClass::CalculateImportantValues(DynamicParticleData& arg_dynamic_particle_data)
{
	//---------------------------------------
	// frames ratio:
	arg_dynamic_particle_data.frames[1] = arg_dynamic_particle_data.frames[1] - arg_dynamic_particle_data.frames[0] + 1;


	if (arg_dynamic_particle_data.frames[3] != 0)
	{
		arg_dynamic_particle_data.frames_ratio[0] =
			static_cast<float>(1.0 / static_cast<double>(arg_dynamic_particle_data.frames[3]));
	}
	else
	{
		arg_dynamic_particle_data.frames_ratio[0] = 0;
	}

	if (arg_dynamic_particle_data.frames[4] != 0)
	{
		arg_dynamic_particle_data.frames_ratio[1] =
			static_cast<float>(1.0 / static_cast<double>(arg_dynamic_particle_data.frames[4]));
	}
	else
	{
		arg_dynamic_particle_data.frames_ratio[1] = 0;
	}


	//---------------------------------------
	//Light:
	arg_dynamic_particle_data.light[0] *= arg_dynamic_particle_data.light[3]; // Light_1 = Light_1 * Light_4
	arg_dynamic_particle_data.light[1] *= arg_dynamic_particle_data.light[3]; // Light_2 = Light_2 * Light_4
	arg_dynamic_particle_data.light[2] *= arg_dynamic_particle_data.light[3]; // Light_3 = Light_3 * Light_4

	//---------------------------------------
	// Delta Size:

	arg_dynamic_particle_data.delta_size =
		static_cast<float>((arg_dynamic_particle_data.size[2] - arg_dynamic_particle_data.size[0]) * 0.5);

	//---------------------------------------
	// Position:

	arg_dynamic_particle_data.position[1] *= -1.0;

	//---------------------------------------
	// Position2:
	arg_dynamic_particle_data.position_2[1] *= -1.0;
	//---------------------------------------
}


void DynamicParticleClass::WriteDynamicParticleDataToFileBuffer(BinFile& output_file_buff,
															    DynamicParticleData& arg_dynamic_particle_data)
{
	CalculateImportantValues(arg_dynamic_particle_data);

    output_file_buff.WriteValue(arg_dynamic_particle_data.type);

    output_file_buff.WriteValue(arg_dynamic_particle_data.light_type);

    output_file_buff.WriteArrayViaIndexes(arg_dynamic_particle_data.frames, { 0, 1, 3, 4, 2 });

    if (m_prt_file_version_info.dynamic_particle_version !=
        ParticleGlobals::old_dynamic_particle_type_value::e2150_old_dynamic_particle)
	{
        output_file_buff.WriteValue(static_cast<int32_t>(arg_dynamic_particle_data.time[0]));
        output_file_buff.WriteValue(static_cast<int32_t>(arg_dynamic_particle_data.time[1]));
	}

    output_file_buff.WriteValue(arg_dynamic_particle_data.frames_ratio);

    output_file_buff.WriteArrayFromTo(arg_dynamic_particle_data.size, 0, arg_dynamic_particle_data.size_size - 1 - 1);

    output_file_buff.WriteValue(arg_dynamic_particle_data.size_2);

    output_file_buff.WriteValue(arg_dynamic_particle_data.size[4]);

    output_file_buff.WriteValue(arg_dynamic_particle_data.delta_size);

    output_file_buff.WriteValue(arg_dynamic_particle_data.null_space);

    output_file_buff.WriteValue(arg_dynamic_particle_data.additive);

    output_file_buff.WriteArrayFromTo(arg_dynamic_particle_data.light, 0, arg_dynamic_particle_data.light_size - 1 - 1);

    output_file_buff.WriteValue(arg_dynamic_particle_data.color);

    output_file_buff.WriteValue(arg_dynamic_particle_data.alpha.b[0]);

    output_file_buff.WriteArrayFromToReverse(arg_dynamic_particle_data.alpha.a, arg_dynamic_particle_data.alpha_a_size - 1, 0);

    output_file_buff.WriteArrayFromToReverse(arg_dynamic_particle_data.scale, arg_dynamic_particle_data.scale_size - 1, 0);

    output_file_buff.WriteValue(arg_dynamic_particle_data.position);

    output_file_buff.WriteValue(arg_dynamic_particle_data.position_2);

    output_file_buff.WriteStringWithLen(arg_dynamic_particle_data.mesh);

    output_file_buff.WriteStringWithLen(arg_dynamic_particle_data.texture);

    output_file_buff.WriteValue(arg_dynamic_particle_data.number_of_nested_particles);

	// Rekurencyjne wczytywanie dzieci
	for (uint32_t i = 0; i < arg_dynamic_particle_data.number_of_nested_particles; ++i)
	{
        std::filesystem::path child_extra_data_file_path =
            m_particle_directory_path / (arg_dynamic_particle_data.children[i].m_obj_name + "_extra_data.cpp");

		//cout << child_extra_data_file_name << endl;


        IntroductionHeaderClass my_introduction_header(m_prt_file_version_info, child_extra_data_file_path);
		my_introduction_header.ParseAndWriteTo(output_file_buff, true);

		WriteDynamicParticleDataToFileBuffer(output_file_buff, arg_dynamic_particle_data.children[i]);
	}


    if (m_prt_file_version_info.dynamic_particle_version !=
        ParticleGlobals::old_dynamic_particle_type_value::e2150_old_dynamic_particle)
	{
        output_file_buff.WriteValue(arg_dynamic_particle_data.layer);
	}
}


void DynamicParticleClass::WriteCompilatorFlagsFile() const
{
    std::unordered_map<ParticleGlobals::old_dynamic_particle_type_value, std::string>
        dynamic_particle_formats_hash_map = {};

    dynamic_particle_formats_hash_map[ParticleGlobals::old_dynamic_particle_type_value::not_old_dynamic_particle] =
        "not_dynamic_particle";

    dynamic_particle_formats_hash_map[ParticleGlobals::old_dynamic_particle_type_value::e2150_old_dynamic_particle] =
        ParticleGlobals::e2150_format_str;

    dynamic_particle_formats_hash_map[ParticleGlobals::old_dynamic_particle_type_value::ww3_of_hh_old_dynamic_particle] =
        ParticleGlobals::ww3_or_hh_format_str;

    dynamic_particle_formats_hash_map[ParticleGlobals::old_dynamic_particle_type_value::ww2_or_fa_or_pc2_old_dynamic_particle] =
        ParticleGlobals::ww2_or_fa_or_pc2_format_str;

    dynamic_particle_formats_hash_map[ParticleGlobals::old_dynamic_particle_type_value::ks_old_dynamic_particle] =
        ParticleGlobals::ks_format_str;

    stringstream compilator_flags_file_stream;
    const char compilator_flags_file_name[] = "__compilator_flags__.cfg";

    compilator_flags_file_stream << "__compiler_var__ dynamic_particle_version = "
                                 << dynamic_particle_formats_hash_map[m_dynamic_particle_cfg .
                                                                      input_dynamic_particle_file_version_info .
                                                                      dynamic_particle_version] << ";" << endl << endl;

    const std::filesystem::path compilator_flags_file_path = this->m_particle_directory_path / compilator_flags_file_name;

    TU::WriteSsToFile(compilator_flags_file_stream, compilator_flags_file_path);

}



void DynamicParticleClass::ReadAndSetAndExportDynamicParticleToAod(BinFile& buffer,
                                                                 std::stringstream& output,
                                                                 std::string& particle_name)
{
    ReadData(buffer, particle_name, m_dynamic_particle_data);
    if (m_dynamic_particle_cfg.force_dynamic_particle_export_format_switch)
    {
        SetPrtVersion(m_dynamic_particle_cfg.forced_dynamic_particle_file_version_info_for_export);
    }
    ExportTo(m_dynamic_particle_data, output, particle_name, Globals::one_quad);

    WriteCompilatorFlagsFile();
}



bool DynamicParticleClass::ReadData(BinFile& buffer, std::string particle_name,
                                   DynamicParticleData& dynamic_particle_data)
{
    buffer.ReadValue(dynamic_particle_data.type);

    buffer.ReadValue(dynamic_particle_data.light_type);

    buffer.ReadValue(dynamic_particle_data.frames[0]);

    int32_t frames_temp_value = 0;
    buffer.ReadValue(frames_temp_value);

    dynamic_particle_data.frames[1] = frames_temp_value + dynamic_particle_data.frames[0] - 1;
    //frames2 = mshvalue + frames1 - 1

    buffer.ReadValue(dynamic_particle_data.frames[3]);
    buffer.ReadValue(dynamic_particle_data.frames[4]);
    buffer.ReadValue(dynamic_particle_data.frames[2]);

    if (m_dynamic_particle_cfg.input_dynamic_particle_file_version_info.dynamic_particle_version !=
        ParticleGlobals::old_dynamic_particle_type_value::e2150_old_dynamic_particle)
    {
        int32_t i32_temp_value = 0;
        buffer.ReadValue(i32_temp_value);

        int64_t help_time = static_cast<int64_t>(i32_temp_value);

        dynamic_particle_data.time[0] = static_cast<float>(static_cast<double>(help_time) / 1000.0);

        buffer.ReadValue(i32_temp_value);
        help_time = static_cast<int64_t>(i32_temp_value);

        dynamic_particle_data.time[1] = static_cast<float>(1.0 - (static_cast<double>(help_time) / 1000.0));
    }

    buffer.ReadArray(dynamic_particle_data.frames_ratio, dynamic_particle_data.frames_ratio_size);

    buffer.ReadArray(dynamic_particle_data.size, dynamic_particle_data.size_size - 1);


    buffer.ReadArray(dynamic_particle_data.size_2, dynamic_particle_data.size_2_size);


    buffer.ReadValue(dynamic_particle_data.size[4]);

    buffer.ReadValue(dynamic_particle_data.delta_size);

    buffer.ReadValue(dynamic_particle_data.null_space);

    buffer.ReadValue(dynamic_particle_data.additive);

    for (int i = 0; i < dynamic_particle_data.light_size - 1; ++i)
    {
        float temp_light = 0.0;
        buffer.ReadValue(temp_light);
        dynamic_particle_data.light[i] = temp_light / dynamic_particle_data.light[3];
    }
    // dziele przez l4
    // i zakladam ze l4 = 1 zeby bylo prosciej


    buffer.ReadArray(dynamic_particle_data.color, dynamic_particle_data.color_size);

    buffer.ReadValue(dynamic_particle_data.alpha.b[0]);

    buffer.ReadArrayReverse(dynamic_particle_data.alpha.a, dynamic_particle_data.alpha_a_size);

    buffer.ReadArrayReverse(dynamic_particle_data.scale, dynamic_particle_data.scale_size);

    buffer.ReadArray(dynamic_particle_data.position, dynamic_particle_data.position_size);

    dynamic_particle_data.position[1] /= -1.0;

    buffer.ReadArray(dynamic_particle_data.position_2, dynamic_particle_data.position_2_size);

    dynamic_particle_data.position_2[1] /= -1.0;

    dynamic_particle_data.mesh = buffer.ReadStringWithNullTerminator();

    dynamic_particle_data.texture = buffer.ReadStringWithNullTerminator();

    buffer.ReadValue(dynamic_particle_data.number_of_nested_particles);

    int no = 1;
    string child_name;

    // Rekurencyjne wczytywanie dzieci
    for (uint32_t i = 0; i < dynamic_particle_data.number_of_nested_particles; ++i)
    {
        child_name = particle_name + "_" + to_string(no);

        CustomBlockClass custom_children_block(m_dynamic_particle_cfg.input_dynamic_particle_file_version_info, true);
        custom_children_block.ReadFrom(buffer);

        if (m_dynamic_particle_cfg.force_dynamic_particle_export_format_switch)
        {
            custom_children_block.SetPrtVersion(m_dynamic_particle_cfg.forced_dynamic_particle_file_version_info_for_export);
        }

        stringstream child_bonus_file_stream;
        custom_children_block.ExportTo(child_bonus_file_stream);

        TU::WriteSsToFile
            (child_bonus_file_stream,
                          this->m_particle_directory_path / (child_name + ParticleGlobals::bonus_file_rest_name_str));



        DynamicParticleData child;

        if (!ReadData(buffer, child_name, child)) break;

        dynamic_particle_data.children.push_back(std::move(child));

        //------- naprawa
        ++no;
    }

    if (m_dynamic_particle_cfg.input_dynamic_particle_file_version_info.dynamic_particle_version !=
        ParticleGlobals :: old_dynamic_particle_type_value :: e2150_old_dynamic_particle)
    {
        buffer.ReadValue(dynamic_particle_data.layer);
    }

    return true;
}




void DynamicParticleClass::ExportTo(const DynamicParticleData& dynamic_particle_data,
                                    std::stringstream& output, std::string particle_name, int count_of_tabulation)
{
    TU::WriteOneValueToSs("Object", particle_name, output, count_of_tabulation - 1);

    TU::WriteSingleStringToSs("{", output, count_of_tabulation - 1);

    TU::WriteConstValueToSs<uint32_t>("Type",
                                       dynamic_particle_data.type,
                                       m_list_of_type_consts_for_export,
                                       output,
                                       count_of_tabulation);

    TU::WriteOneValueToSs("Additive", dynamic_particle_data.additive, output, count_of_tabulation);

    TU::WriteConstValueToSs<uint32_t>("LightType",
                                       dynamic_particle_data.light_type,
                                       m_list_of_lighttype_consts_for_export,
                                       output,
                                       count_of_tabulation);

    TU::WriteArrayToSs<int32_t>("Frames",
                                 dynamic_particle_data.frames,
                                 dynamic_particle_data.frames_size,
                                 output,
                                 count_of_tabulation);

    TU::WriteArrayToSs<float>("Light",
                               dynamic_particle_data.light,
                               dynamic_particle_data.light_size,
                               output,
                               count_of_tabulation);

    TU::WriteArrayToSs<float>("Size",
                               dynamic_particle_data.size,
                               dynamic_particle_data.size_size,
                               output,
                               count_of_tabulation);

    TU::WriteArrayToSs<float>("Size2",
                               dynamic_particle_data.size_2,
                               dynamic_particle_data.size_2_size,
                               output,
                               count_of_tabulation);

    TU::WriteArrayToSs<float>("Color",
                               dynamic_particle_data.color,
                               dynamic_particle_data.color_size,
                               output,
                               count_of_tabulation);

    TwoTypeArray<float, DynamicParticleData::alpha_a_size, uint32_t, DynamicParticleData::alpha_b_size> help_alpha
        = dynamic_particle_data.alpha;

    help_alpha.ExportToSs("Alpha", output, count_of_tabulation);

    TU::WriteArrayToSs<float>("Scale",
                               dynamic_particle_data.scale,
                               dynamic_particle_data.scale_size,
                               output,
                               count_of_tabulation);

    TU::WriteArrayToSs<float>("Position",
                               dynamic_particle_data.position,
                               dynamic_particle_data.position_size,
                               output,
                               count_of_tabulation);

    TU::WriteArrayToSs<float>("Position2",
                               dynamic_particle_data.position_2,
                               dynamic_particle_data.position_2_size,
                               output,
                               count_of_tabulation);

    if (m_dynamic_particle_cfg.input_dynamic_particle_file_version_info.dynamic_particle_version !=
        ParticleGlobals::old_dynamic_particle_type_value::e2150_old_dynamic_particle)
    {
        TU::WriteArrayToSs<float>("Time",
                                   dynamic_particle_data.time,
                                   dynamic_particle_data.time_size,
                                   output,
                                   count_of_tabulation);
    }

    TU::WriteOneValueToSs("Texture", dynamic_particle_data.texture, output, count_of_tabulation);

    TU::WriteOneValueToSs("Mesh", dynamic_particle_data.mesh, output, count_of_tabulation);

    int no = 1;
    string child_name;
    for (const auto& child : dynamic_particle_data.children)
    {
        child_name = particle_name + "_" + to_string(no);

        ExportTo(child, output, child_name, count_of_tabulation + 1);

        ++no;
    }


    if (m_dynamic_particle_cfg.input_dynamic_particle_file_version_info.dynamic_particle_version !=
        ParticleGlobals::old_dynamic_particle_type_value::e2150_old_dynamic_particle)
    {
        TU::WriteOneValueToSs("Layer", dynamic_particle_data.layer, output, count_of_tabulation);
    }

    TU::WriteSingleStringToSs("}", output, count_of_tabulation - 1);

}















