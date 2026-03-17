#include "ParticleClass.hpp"

#include "../../../AodCompilator/GlobalQueues.hpp"
#include "Utils/Misc.hpp"

#include "Utils/TxtUtils.hpp"


#include "../../BasicParticleStructures/CurvesAndTeselatesUtils.hpp"


using namespace std;

uint32_t ParticleClass::particle_number = 0;

vector<string> PgAndTwParticleStrings =
{
                    // pg particle:   // two worlds:
"trajectoryXMin",   // ok             // ok
"trajectoryXMax",   // ok             // ok

"trajectoryYMin",   // ok             // ok
"trajectoryYMax",   // ok             // ok

"trajectoryZMin",   // ok             // ok
"trajectoryZMax",   // ok             // ok

"scaleXMin",        // ok             // ok
"scaleXMax",        // ok             // ok

"scaleYMin",        // ok             // ok
"scaleYMax",        // ok             // ok

"scaleZMin",        // ok             // ok
"scaleZMax",        // ok             // ok

"colorRMin",        // ok             // ok
"colorRMax",        // ok             // ok

"colorGMin",        // ok             // ok
"colorGMax",        // ok             // ok

"colorBMin",        // ok             // ok
"colorBMax",        // ok             // ok


"alphaMin",         // ok             // ok
"alphaMax",         // ok             // ok

"rotationZMin",     // ok             // ok
"rotationZMax",     // ok             // ok

"rotationXMin",     // ok             // ok
"rotationXMax",     // ok             // ok

"rotationYMin",     // ok             // ok
"rotationYMax",     // ok             // ok

"speedMulMin",      // ok             // ok
"speedMulMax"       // ok             // ok
};



vector<string> E2160ParticleStrings =
{

"trajectoryXMin",   // ok
"trajectoryXMax",   // ok

"trajectoryYMin",   // ok
"trajectoryYMax",   // ok

"trajectoryZMin",   // ok
"trajectoryZMax",   // ok

"scaleX",           // ok
"scaleY",           // ok
"scaleZ",           // ok

"colorRMin",        // ok
"colorRMax",        // ok

"colorGMin",        // ok
"colorGMax",        // ok

"colorBMin",        // ok
"colorBMax",        // ok

"alphaMin",         // ok 
"alphaMax",         // ok

"rotationZMin",     // ok
"rotationZMax",     // ok

"rotationXMin",     // ok
"rotationXMax",     // ok

"rotationYMin",     // ok
"rotationYMax",     // ok

"speedMulMin",      // ok             
"speedMulMax"       // ok             

};


vector<string> KsParticleStrings =
{
"trajectoryXMin",
"trajectoryXMax",
"trajectoryYMin",
"trajectoryYMax",
"trajectoryZMin",
"trajectoryZMax",
"scaleX",
"scaleY",
"scaleZ",
"colorRMin",
"colorRMax",
"colorGMin",
"colorGMax",
"colorBMin",
"colorBMax",
"colorAMin",
"colorAMax",
"rotationAlpha",
"rotationBeta",
"rotationPhi",
"speedMulMin",
"speedMulMax",
"lightRange",
"lightIntensity",
"lightColorR",
"lightColorG",
"lightColorB"
};



void ParticleClass::InitializeHashMap()
{
    switch (m_prt_file_version_info.particle_version)
    {
        case ParticleGlobals::particle_type_value::particle_gen_particle:
        case ParticleGlobals::particle_type_value::two_worlds_particle:
            Misc::InitializeHashMapViaLabelsVector(m_labels_map, PgAndTwParticleStrings);
        break;

        case ParticleGlobals::particle_type_value::e2160_particle:
            Misc::InitializeHashMapViaLabelsVector(m_labels_map, E2160ParticleStrings);
        break;

        case ParticleGlobals::particle_type_value::ks_particles_emiter:
            Misc::InitializeHashMapViaLabelsVector(m_labels_map, KsParticleStrings);
        break;

        case ParticleGlobals::particle_type_value::dynamic_particle:
        break;

        default: break;
    }
}

ParticleClass::ParticleClass(
                             const ParticleGlobals::ENAppModes& arg_app_mode,
                             ParticleFileVersionInfo arg_prt_file_version_info,
                             string arg_particle_name
                             ):

    m_prt_file_version_info(arg_prt_file_version_info),

    m_curve_iel_index(-1),
    m_number_of_single_curve_points_checksum(0),

    m_teselate_iel_index(-1),
    m_number_of_single_teselate_points_checksum(0),

    m_mode(ParticleGlobals::curve_or_teselate_mode::null)
{
    if(arg_app_mode == ParticleGlobals::ENAppModes::m_import)
    {
        m_particle_data.particle_name = arg_particle_name;

        InitializeHashMap();

        m_particle_data.linked_min_max.resize(  m_prt_file_version_info.number_of_linked_min_max_in_particle,
                                                ParticleGlobals::locked_linked_min_max);

        m_particle_data.curves_groups.Resize(m_prt_file_version_info.number_of_iel_in_particle);

        m_particle_data.teselates_groups.Resize(m_prt_file_version_info.number_of_iel_in_particle);

    }
}

void ParticleClass::ParseFrom(string& arg_line, GlobalQueues& arg_queues)
{
    TU::GetOneValue<float>(arg_line, "startTime", m_particle_data.start_time);

    TU::GetOneValue<float>(arg_line, "time", m_particle_data.time);

    TU::GetOneValue<uint32_t>(arg_line, "coordinates", m_particle_data.coordinates);

    TU::GetOneValue<uint32_t>(arg_line, "type", m_particle_data.type);

    TU::GetSingleStringFromQueue(arg_line, "mesh", m_particle_data.mesh, arg_queues.m_mesh_q);

    m_particle_data.face.ParseFrom(arg_line, "face", "%d", "%f");

    TU::GetOneValue<float>(arg_line, "triangleA", m_particle_data.triangle_a);

    TU::GetOneValue<float>(arg_line, "screenDepthOffset", m_particle_data.screen_depth_offset);

    TU::GetOneValue<uint32_t>(arg_line, "multiplyDxyByPrtScale", m_particle_data.multiply_dxy_by_prt_scale_switch);

    m_particle_data.trail.ParseFrom(arg_line, "trail", "%f", "%d");

    TU::GetOneValue<float>(arg_line, "yTextureMul", m_particle_data.y_texture_mul);

    TU::GetVectorOfStringsFromQueue(arg_line, "texture", m_particle_data.textures, arg_queues.m_texture_q);

    TU::GetVectorOfStringsFromQueue(arg_line, "bumpTexture", m_particle_data.bump_textures, arg_queues.m_bump_texture_q);


    m_particle_data.tex_anim.ParseViaSchemeFrom(arg_line, "texAnim", "%d", "%f", "a,a,a,a,a,a,a,a,a,b,a");


    TU::GetArrayValues<float>
        (arg_line, "coordinatesLTRB", "%f", m_particle_data.coordinates_ltrb, m_particle_data.coordinates_ltrb_size);

    TU::GetOneValue<uint32_t>(arg_line, "distortionParticleSwitch", m_particle_data.distortion_particle_switch);

    TU::GetOneValue<uint32_t>(arg_line, "xMirrored", m_particle_data.x_mirrored);

    TU::GetOneValue<uint32_t>(arg_line, "yMirrored", m_particle_data.y_mirrored);

    TU::GetOneValue<uint32_t>(arg_line, "colorRandType", m_particle_data.color_rand_type);

    TU::GetOneValue<uint32_t>(arg_line, "unknownValue1", m_particle_data.unknown_value_1);

    TU::GetOneValue<uint32_t>(arg_line, "unknownValue2", m_particle_data.unknown_value_2);

    TU::GetOneValue<uint32_t>(arg_line, "unknownValue3", m_particle_data.unknown_value_3);

    TU::GetArrayValues<uint32_t>(arg_line, "trajectory", "%d", m_particle_data.trajectory, m_particle_data.trajectory_size);

    m_particle_data.gravity.ParseFrom(arg_line, "gravity", "%f", "%d");

    TU::GetOneValue<uint32_t>(arg_line, "enableLight", m_particle_data.enable_light);

    TU::GetOneValue<uint32_t>(arg_line, "gravityRotFromTrajectoryX", m_particle_data.gravity_rot_from_trajectory_x_switch);

    TU::GetOneValue<uint32_t>(arg_line, "gravityRotFromTrajectoryY", m_particle_data.gravity_rot_from_trajectory_y_switch);

    TU::GetOneValue<uint32_t>(arg_line, "gravityRotFromTrajectoryZ", m_particle_data.gravity_rot_from_trajectory_z_switch);

    TU::GetOneValue<uint32_t>(arg_line, "disappearsOnGround", m_particle_data.dissappears_on_ground);

    TU::GetOneValue<uint32_t>(arg_line, "createOnGround", m_particle_data.create_on_ground_switch);

    TU::GetOneValue<uint32_t>(arg_line, "trajectoryZFromGround", m_particle_data.trajectory_z_from_ground);


    TwoTypeArray<float, ParticleData::scale_a_size, uint32_t, ParticleData::scale_b_size> ::
    ParseArrayOfTwoTypeArrayPlusBonusFrom
    (
        arg_line,
        "scales",
        "%f",
        "%d",
        m_particle_data.scales,
        m_particle_data.scales_size,
        m_particle_data.scales_end
    );


    TU::GetOneValue<uint32_t>(arg_line, "allTeselateZeroMask", m_particle_data.all_teselate_zero_mask);

    TU::GetOneValue<uint32_t>(arg_line, "layer", m_particle_data.layer);

    TU::GetArrayValues<uint32_t>(arg_line,
                               "linkedMinMax", 
                               "%d", 
                               &m_particle_data.linked_min_max[0], 
                               static_cast<int>(m_particle_data.linked_min_max.size()) );

    m_particle_data.curves_groups.ParseFrom(arg_line,
        m_curve_iel_index,
        m_number_of_single_curve_points_checksum,
        m_labels_map,
        m_mode);


    m_particle_data.teselates_groups.ParseFrom(arg_line,
        m_teselate_iel_index,
        m_number_of_single_teselate_points_checksum,
        m_labels_map,
        m_mode);


}


void ParticleClass::WriteTo(BinFile& output_file_buff)
{
    switch (m_prt_file_version_info.particle_version)
    {
        case ParticleGlobals::particle_type_value::dynamic_particle:
        break;

        case ParticleGlobals::particle_type_value::ks_particles_emiter:
            WriteToKsFormat(output_file_buff);
        break;

        case ParticleGlobals::particle_type_value::particle_gen_particle:
        case ParticleGlobals::particle_type_value::two_worlds_particle:
            WriteToParticleGenAndTwoWorldsFormat(output_file_buff);
        break;

        case ParticleGlobals::particle_type_value::e2160_particle:
            WriteToE2160Format(output_file_buff);
        break;

        default:
        break;
    }

}


void ParticleClass::WriteToParticleGenAndTwoWorldsFormat(BinFile& output_file_buff)
{
    output_file_buff.WriteStringWithLen(m_particle_data.particle_name);

    output_file_buff.WriteValue(m_particle_data.start_time);

    output_file_buff.WriteValue(m_particle_data.time);

    output_file_buff.WriteValue(m_particle_data.coordinates);

    output_file_buff.WriteValue(m_particle_data.type);

    output_file_buff.WriteStringWithLen(m_particle_data.mesh);

    output_file_buff.WriteArrayFromTo(m_particle_data.face.b, 3, 4);

    output_file_buff.WriteValue(m_particle_data.screen_depth_offset);

    output_file_buff.WriteArrayFromTo(m_particle_data.face.b, 1, 2);

    output_file_buff.WriteValue(m_particle_data.multiply_dxy_by_prt_scale_switch);

    output_file_buff.WriteValue(m_particle_data.trail.a);

    output_file_buff.WriteValue(m_particle_data.y_texture_mul);

    output_file_buff.WriteValue(m_particle_data.trail.b);

    output_file_buff.WriteVectorOfStringsWithLen(m_particle_data.textures);

    output_file_buff.WriteVectorOfStringsWithLen(m_particle_data.bump_textures);

    output_file_buff.WriteValue(m_particle_data.trajectory[1]);

    output_file_buff.WriteArrayFromTo(m_particle_data.tex_anim.a, 0, m_particle_data.tex_anim_a_size - 5);

    output_file_buff.WriteArrayViaIndexes(m_particle_data.tex_anim.a, { 8, 9 } );

    output_file_buff.WriteValue(m_particle_data.coordinates_ltrb);

    output_file_buff.WriteValue(m_particle_data.tex_anim.a[6]);

    output_file_buff.WriteValue(m_particle_data.face.b[0]);

    output_file_buff.WriteValue(m_particle_data.distortion_particle_switch);

    output_file_buff.WriteValue(m_particle_data.tex_anim.a[7]);

    output_file_buff.WriteValue(m_particle_data.tex_anim.b[0]);

    output_file_buff.WriteValue(m_particle_data.x_mirrored);

    output_file_buff.WriteValue(m_particle_data.y_mirrored);

    output_file_buff.WriteValue(m_particle_data.color_rand_type);

    output_file_buff.WriteValue(m_particle_data.unknown_value_1);

    output_file_buff.WriteValue(m_particle_data.unknown_value_2);

    output_file_buff.WriteValue(m_particle_data.unknown_value_3);

    output_file_buff.WriteValue(m_particle_data.trajectory[0]);

    output_file_buff.WriteValue(m_particle_data.gravity.a);

    output_file_buff.WriteValue(m_particle_data.gravity_rot_from_trajectory_z_switch);

    output_file_buff.WriteValue(m_particle_data.gravity_rot_from_trajectory_x_switch);

    output_file_buff.WriteValue(m_particle_data.gravity_rot_from_trajectory_y_switch);

    output_file_buff.WriteValue(m_particle_data.dissappears_on_ground);

    output_file_buff.WriteValue(m_particle_data.create_on_ground_switch);

    output_file_buff.WriteValue(m_particle_data.trajectory_z_from_ground);

    output_file_buff.WriteValue(m_particle_data.scales);

    m_particle_data.curves_groups.WriteTo(output_file_buff);


    if (m_prt_file_version_info.particle_version == ParticleGlobals::particle_type_value::two_worlds_particle)
    {

        m_particle_data.teselates_groups.WriteTo<uint64_t>(output_file_buff, true);
    }
    else
    {

        m_particle_data.teselates_groups.WriteTo<uint64_t>(output_file_buff);

        m_particle_data.teselates_groups.WriteTeselateFlagsTo(output_file_buff);

    }

    output_file_buff.WriteVector(m_particle_data.linked_min_max);

    output_file_buff.WriteValue(m_particle_data.all_teselate_zero_mask);

    output_file_buff.WriteValue(m_particle_data.layer);

}

void ParticleClass::WriteToE2160Format(BinFile& output_file_buff)
{
    output_file_buff.WriteStringWithLen(m_particle_data.particle_name);

    output_file_buff.WriteValue(m_particle_data.start_time);

    output_file_buff.WriteValue(m_particle_data.time);

    output_file_buff.WriteValue(m_particle_data.coordinates);

    output_file_buff.WriteValue(m_particle_data.type);

    output_file_buff.WriteStringWithLen(m_particle_data.mesh);

    output_file_buff.WriteValue(m_particle_data.face.a[0]);

    output_file_buff.WriteValue(m_particle_data.triangle_a);

    output_file_buff.WriteArrayViaIndexes(m_particle_data.face.b, { 3, 4, 0, 1, 2 });

    output_file_buff.WriteValue(m_particle_data.multiply_dxy_by_prt_scale_switch);

    output_file_buff.WriteValue(m_particle_data.trail.a);

    output_file_buff.WriteValue(m_particle_data.y_texture_mul);

    output_file_buff.WriteValue(m_particle_data.trail.b);

    output_file_buff.WriteFirstStringFromVectorWithLen(m_particle_data.textures);

    output_file_buff.WriteFirstStringFromVectorWithLen(m_particle_data.bump_textures);

    output_file_buff.WriteValue(m_particle_data.trajectory[1]);

    output_file_buff.WriteArrayFromTo(m_particle_data.tex_anim.a, 0, m_particle_data.tex_anim_a_size - 5);

    output_file_buff.WriteArrayViaIndexes(m_particle_data.tex_anim.a, { 8, 9 });

    output_file_buff.WriteValue(m_particle_data.coordinates_ltrb);

    output_file_buff.WriteArrayViaIndexes(m_particle_data.tex_anim.a, { 6, 7 });

    output_file_buff.WriteValue(m_particle_data.tex_anim.b[0]);

    output_file_buff.WriteValue(m_particle_data.x_mirrored);

    output_file_buff.WriteValue(m_particle_data.y_mirrored);

    output_file_buff.WriteValue(m_particle_data.color_rand_type);

    output_file_buff.WriteValue(m_particle_data.trajectory[0]);

    output_file_buff.WriteValue(m_particle_data.gravity);

    output_file_buff.WriteValue(m_particle_data.dissappears_on_ground);

    output_file_buff.WriteValue(m_particle_data.scales);

    m_particle_data.curves_groups.WriteTo(output_file_buff, true);

    m_particle_data.teselates_groups.WriteTo<uint64_t>(output_file_buff);

    m_particle_data.teselates_groups.WriteTeselateFlagsTo(output_file_buff);

    output_file_buff.WriteVector(m_particle_data.linked_min_max);

    output_file_buff.WriteValue(m_particle_data.all_teselate_zero_mask);

    output_file_buff.WriteValue(m_particle_data.layer);
}


void ParticleClass::WriteToKsFormat(BinFile& output_file_buff)
{
    output_file_buff.WriteValue(m_particle_data.time);

    output_file_buff.WriteValue(m_particle_data.coordinates);

    output_file_buff.WriteValue(m_particle_data.type);

    output_file_buff.WriteStringWithLen(m_particle_data.mesh, true);

    output_file_buff.WriteValue(m_particle_data.face.a[0]);

    output_file_buff.WriteValue(m_particle_data.trajectory[1]);

    output_file_buff.WriteArrayViaIndexes(m_particle_data.face.b, { 3, 4, 0, 1, 2 });

    output_file_buff.WriteValue(m_particle_data.trail);

    output_file_buff.WriteFirstStringFromVectorWithLen(m_particle_data.textures, true);

    output_file_buff.WriteArrayFromTo(m_particle_data.tex_anim.a, 0, m_particle_data.tex_anim_a_size - 5);

    output_file_buff.WriteArrayViaIndexes(m_particle_data.tex_anim.a, { 8, 9, 6, 7 });

    output_file_buff.WriteValue(static_cast<uint32_t>(m_particle_data.tex_anim.b[0]) );

    output_file_buff.WriteValue(m_particle_data.color_rand_type);

    output_file_buff.WriteValue(m_particle_data.trajectory[0]);

    output_file_buff.WriteValue(m_particle_data.gravity);

    output_file_buff.WriteValue(m_particle_data.enable_light);

    output_file_buff.WriteValue(m_particle_data.dissappears_on_ground);

    output_file_buff.WriteValue(m_particle_data.scales);

    output_file_buff.WriteValue(m_particle_data.scales_end);

    m_particle_data.teselates_groups.WriteTo<uint32_t>(output_file_buff);

    m_particle_data.teselates_groups.WriteTeselateFlagsTo(output_file_buff);

    output_file_buff.WriteVector(m_particle_data.linked_min_max);

    output_file_buff.WriteValue(m_particle_data.all_teselate_zero_mask);

    output_file_buff.WriteValue(m_particle_data.layer);

}



void ParticleClass::ReadFromParticleGenAndTwoWorldsFile(BinFile& buff)
{
    m_particle_data.particle_name = buff.ReadStringWithNullTerminator();

    buff.ReadValue(m_particle_data.start_time);

    buff.ReadValue(m_particle_data.time);

    buff.ReadValue(m_particle_data.coordinates);

    buff.ReadValue(m_particle_data.type);

    m_particle_data.mesh = buff.ReadStringWithNullTerminator();

    buff.ReadArrayViaIndexes(m_particle_data.face.b, { 3, 4 });

    buff.ReadValue(m_particle_data.screen_depth_offset);

    buff.ReadArrayViaIndexes(m_particle_data.face.b, { 1, 2 });

    buff.ReadValue(m_particle_data.multiply_dxy_by_prt_scale_switch);

    buff.ReadValue(m_particle_data.trail.a[0]);

    buff.ReadValue(m_particle_data.y_texture_mul);

    buff.ReadValue(m_particle_data.trail.b[0]);


    uint64_t size_of_textures_vec;
    buff.ReadValue(size_of_textures_vec);

    for (uint64_t i = 0; i < size_of_textures_vec; ++i)
    {
        m_particle_data.textures.push_back(  buff.ReadStringWithNullTerminator()  );
    }


    uint64_t size_of_bump_textures_vec;
    buff.ReadValue(size_of_bump_textures_vec);
    for (uint64_t i = 0; i < size_of_bump_textures_vec; ++i)
    {
        m_particle_data.bump_textures.push_back(  buff.ReadStringWithNullTerminator()  );
    }

    buff.ReadValue(m_particle_data.trajectory[1]);

    buff.ReadArray(m_particle_data.tex_anim.a, m_particle_data.tex_anim_a_size - 4);

    buff.ReadArrayViaIndexes(m_particle_data.tex_anim.a, { 8, 9 });

    buff.ReadArray(m_particle_data.coordinates_ltrb, m_particle_data.coordinates_ltrb_size);

    buff.ReadValue(m_particle_data.tex_anim.a[6]);

    buff.ReadValue(m_particle_data.face.b[0]);

    buff.ReadValue(m_particle_data.distortion_particle_switch);

    buff.ReadValue(m_particle_data.tex_anim.a[7]);

    buff.ReadValue(m_particle_data.tex_anim.b[0]);


    buff.ReadValue(m_particle_data.x_mirrored);
    buff.ReadValue(m_particle_data.y_mirrored);

    buff.ReadValue(m_particle_data.color_rand_type);

    buff.ReadValue(m_particle_data.unknown_value_1);
    buff.ReadValue(m_particle_data.unknown_value_2);
    buff.ReadValue(m_particle_data.unknown_value_3);

    buff.ReadValue(m_particle_data.trajectory[0]);

    buff.ReadArray(m_particle_data.gravity.a, m_particle_data.gravity_a_size);

    buff.ReadValue(m_particle_data.gravity_rot_from_trajectory_z_switch);
    buff.ReadValue(m_particle_data.gravity_rot_from_trajectory_x_switch);
    buff.ReadValue(m_particle_data.gravity_rot_from_trajectory_y_switch);

    buff.ReadValue(m_particle_data.dissappears_on_ground);

    buff.ReadValue(m_particle_data.create_on_ground_switch);
    buff.ReadValue(m_particle_data.trajectory_z_from_ground);

    for (int i = 0; i < m_particle_data.scales_size; ++i)
    {
        buff.ReadArray(m_particle_data.scales[i].a, m_particle_data.scale_a_size);
        buff.ReadValue(m_particle_data.scales[i].b[0]);
    }

    m_particle_data.curves_groups.ReadFrom(m_prt_file_version_info.number_of_iel_in_particle, buff);

    m_particle_data.curves_groups.ResizeOnlyCurveBonusValues(m_prt_file_version_info.number_of_iel_in_emiter);


    if (m_prt_file_version_info.particle_version == ParticleGlobals::particle_type_value::two_worlds_particle)
    {
        m_particle_data.teselates_groups.
            ReadFrom<uint64_t>(m_prt_file_version_info.number_of_iel_in_particle, buff, true);

    }
    else
    {
        m_particle_data.teselates_groups.ReadFrom<uint64_t>(m_prt_file_version_info.number_of_iel_in_particle, buff);

        m_particle_data.teselates_groups.ReadOnlyTeselateFlags(buff, m_prt_file_version_info.number_of_iel_in_particle);
    }


    for (uint32_t i = 0; i < m_prt_file_version_info.number_of_linked_min_max_in_particle; ++i)
    {
        uint32_t temp_linked_min_max = 0;
        buff.ReadValue(temp_linked_min_max);
        m_particle_data.linked_min_max.push_back(temp_linked_min_max);
    }

    buff.ReadValue(m_particle_data.all_teselate_zero_mask);

    buff.ReadValue(m_particle_data.layer);
}



void ParticleClass::ReadFromE2160File(BinFile& buff)
{
    m_particle_data.particle_name = buff.ReadStringWithNullTerminator();

    buff.ReadValue(m_particle_data.start_time);
    buff.ReadValue(m_particle_data.time);

    buff.ReadValue(m_particle_data.coordinates);

    buff.ReadValue(m_particle_data.type);

    m_particle_data.mesh = buff.ReadStringWithNullTerminator();

    buff.ReadValue(m_particle_data.face.a[0]);

    buff.ReadValue(m_particle_data.triangle_a);

    buff.ReadArrayViaIndexes(m_particle_data.face.b, { 3, 4, 0, 1, 2 });

    buff.ReadValue(m_particle_data.multiply_dxy_by_prt_scale_switch);

    buff.ReadValue(m_particle_data.trail.a[0]);

    buff.ReadValue(m_particle_data.y_texture_mul);

    buff.ReadValue(m_particle_data.trail.b[0]);

    m_particle_data.textures.push_back( buff.ReadStringWithNullTerminator() );

    m_particle_data.bump_textures.push_back( buff.ReadStringWithNullTerminator() );

    buff.ReadValue(m_particle_data.trajectory[1]);

    buff.ReadArray(m_particle_data.tex_anim.a, m_particle_data.tex_anim_a_size - 4);

    buff.ReadArrayViaIndexes(m_particle_data.tex_anim.a, { 8, 9 });

    buff.ReadArray(m_particle_data.coordinates_ltrb, m_particle_data.coordinates_ltrb_size);

    buff.ReadArrayViaIndexes(m_particle_data.tex_anim.a, { 6, 7 });

    buff.ReadValue(m_particle_data.tex_anim.b[0]);

    buff.ReadValue(m_particle_data.x_mirrored);
    buff.ReadValue(m_particle_data.y_mirrored);

    buff.ReadValue(m_particle_data.color_rand_type);

    buff.ReadValue(m_particle_data.trajectory[0]);

    buff.ReadArray(m_particle_data.gravity.a, m_particle_data.gravity_a_size);
    buff.ReadValue(m_particle_data.gravity.b[0]);

    buff.ReadValue(m_particle_data.dissappears_on_ground);

    for (int i = 0; i < m_particle_data.scales_size; ++i)
    {
        buff.ReadArray(m_particle_data.scales[i].a, m_particle_data.scale_a_size);
        buff.ReadValue(m_particle_data.scales[i].b[0]);
    }

    m_particle_data.curves_groups.ReadFrom(m_prt_file_version_info.number_of_iel_in_particle, buff, true);

    m_particle_data.teselates_groups.ReadFrom<uint64_t>(m_prt_file_version_info.number_of_iel_in_particle, buff);


    m_particle_data.teselates_groups.ReadOnlyTeselateFlags(buff, m_prt_file_version_info.number_of_iel_in_particle);



    for (uint32_t i = 0; i < m_prt_file_version_info.number_of_linked_min_max_in_particle; ++i)
    {
        uint32_t temp_linked_min_max = 0;
        buff.ReadValue(temp_linked_min_max);
        m_particle_data.linked_min_max.push_back(temp_linked_min_max);
    }


    buff.ReadValue(m_particle_data.all_teselate_zero_mask);

    buff.ReadValue(m_particle_data.layer);


}




void ParticleClass::ReadFromKsFile(BinFile& buff)
{
    ++particle_number;

    m_particle_data.particle_name = "P" + to_string(particle_number);


    buff.ReadValue(m_particle_data.time);

    buff.ReadValue(m_particle_data.coordinates);

    buff.ReadValue(m_particle_data.type);

    m_particle_data.mesh = buff.ReadStringWithNullTerminator();

    buff.ReadValue(m_particle_data.face.a[0]);

    buff.ReadValue(m_particle_data.trajectory[1]);

    buff.ReadArrayViaIndexes(m_particle_data.face.b, { 3, 4, 0, 1, 2 });

    buff.ReadValue(m_particle_data.trail.a[0]);

    buff.ReadValue(m_particle_data.trail.b[0]);

    m_particle_data.textures.push_back( buff.ReadStringWithNullTerminator() );

    buff.ReadArray(m_particle_data.tex_anim.a, m_particle_data.tex_anim_a_size - 4);

    buff.ReadArrayViaIndexes(m_particle_data.tex_anim.a, { 8, 9, 6, 7 });

    uint32_t temp_tex_anim_b = 0;
    buff.ReadValue(temp_tex_anim_b);
    m_particle_data.tex_anim.b[0] = static_cast<float>(temp_tex_anim_b);

    buff.ReadValue(m_particle_data.color_rand_type);

    buff.ReadValue(m_particle_data.trajectory[0]);

    buff.ReadArray(m_particle_data.gravity.a, m_particle_data.gravity_a_size);
    buff.ReadValue(m_particle_data.gravity.b[0]);


    buff.ReadValue(m_particle_data.enable_light);

    buff.ReadValue(m_particle_data.dissappears_on_ground);


    for (int i = 0; i < m_particle_data.scales_size; ++i)
    {
        buff.ReadArray(m_particle_data.scales[i].a, m_particle_data.scale_a_size);
        buff.ReadValue(m_particle_data.scales[i].b[0]);
    }

    buff.ReadValue(m_particle_data.scales_end);


    m_particle_data.teselates_groups.ReadFrom<uint32_t>(m_prt_file_version_info.number_of_iel_in_particle, buff);

    m_particle_data.teselates_groups.ReadOnlyTeselateFlags(buff, m_prt_file_version_info.number_of_iel_in_particle);


    for (uint32_t i = 0; i < m_prt_file_version_info.number_of_linked_min_max_in_particle; ++i)
    {
        uint32_t temp_linked_min_max = 0;
        buff.ReadValue(temp_linked_min_max);

        m_particle_data.linked_min_max.push_back(temp_linked_min_max);
    }


    buff.ReadValue(m_particle_data.all_teselate_zero_mask);

    buff.ReadValue(m_particle_data.layer);


    //Interpolacja:
    CurvesAndTeselatesUtils::MakeCurves
        (m_particle_data.teselates_groups, m_particle_data.curves_groups, SingleCurvePointConsts::e2160_example_curve_point);

}




void ParticleClass::ReadFrom(BinFile& buff)
{
    switch (m_prt_file_version_info.particle_version)
    {
        case ParticleGlobals::particle_type_value::dynamic_particle:
        break;

        case ParticleGlobals::particle_type_value::ks_particles_emiter:
            ReadFromKsFile(buff);
        break;

        case ParticleGlobals::particle_type_value::particle_gen_particle:
        case ParticleGlobals::particle_type_value::two_worlds_particle:
            ReadFromParticleGenAndTwoWorldsFile(buff);
        break;

        case ParticleGlobals::particle_type_value::e2160_particle:
            ReadFromE2160File(buff);
        break;

        default:
        break;
    }

}





void ParticleClass::ExportAsParticleGenAndTwoWorldsFormat(std::stringstream& output)
{
    TU::WriteOneValueToSs("Particle", m_particle_data.particle_name, output, Globals::one_quad);

    TU::WriteSingleStringToSs("{", output);

    TU::WriteOneValueToSs("startTime", m_particle_data.start_time, output);

    TU::WriteOneValueToSs("time", m_particle_data.time, output);

    TU::WriteOneValueToSs("coordinates", m_particle_data.coordinates, output);

    TU::WriteOneValueToSs("type", m_particle_data.type, output);

    TU::WriteOneValueToSs("mesh", m_particle_data.mesh, output);

    m_particle_data.face.ExportToSs("face", output);

    TU::WriteOneValueToSs("screenDepthOffset", m_particle_data.screen_depth_offset, output);

    TU::WriteOneValueToSs("multiplyDxyByPrtScale", m_particle_data.multiply_dxy_by_prt_scale_switch, output);

    m_particle_data.trail.ExportToSs("trail", output);

    TU::WriteOneValueToSs("yTextureMul", m_particle_data.y_texture_mul, output);

    TU::WriteVectorToSs<string>("texture", m_particle_data.textures, output);

    TU::WriteVectorToSs<string>("bumpTexture", m_particle_data.bump_textures, output);

    m_particle_data.tex_anim.ExportToSsViaScheme("texAnim", "a,a,a,a,a,a,a,a,a,b,a", output);

    TU::WriteArrayToSs<float>("coordinatesLTRB",
                               m_particle_data.coordinates_ltrb,
                               m_particle_data.coordinates_ltrb_size,
                               output);

    TU::WriteOneValueToSs("distortionParticleSwitch", m_particle_data.distortion_particle_switch, output);

    TU::WriteOneValueToSs("xMirrored", m_particle_data.x_mirrored, output);

    TU::WriteOneValueToSs("yMirrored", m_particle_data.y_mirrored, output);

    TU::WriteOneValueToSs("colorRandType", m_particle_data.color_rand_type, output);

    TU::WriteOneValueToSs("unknownValue1", m_particle_data.unknown_value_1, output);

    TU::WriteOneValueToSs("unknownValue2", m_particle_data.unknown_value_2, output);

    TU::WriteOneValueToSs("unknownValue3", m_particle_data.unknown_value_3, output);

    TU::WriteArrayToSs<uint32_t>("trajectory",
                                  m_particle_data.trajectory,
                                  m_particle_data.trajectory_size,
                                  output);

    m_particle_data.gravity.ExportToSs("gravity", output);

    TU::WriteOneValueToSs("gravityRotFromTrajectoryX", m_particle_data.gravity_rot_from_trajectory_x_switch, output);

    TU::WriteOneValueToSs("gravityRotFromTrajectoryY", m_particle_data.gravity_rot_from_trajectory_y_switch, output);

    TU::WriteOneValueToSs("gravityRotFromTrajectoryZ", m_particle_data.gravity_rot_from_trajectory_z_switch, output);

    TU::WriteOneValueToSs("disappearsOnGround", m_particle_data.dissappears_on_ground, output);

    TU::WriteOneValueToSs("createOnGround", m_particle_data.create_on_ground_switch, output);

    TU::WriteOneValueToSs("trajectoryZFromGround", m_particle_data.trajectory_z_from_ground, output);

    TwoTypeArray<float, ParticleData::scale_a_size, uint32_t, ParticleData::scale_b_size>::
        ExportArrayOfTwoTypeArrayToSs
        ("scales",
         m_particle_data.scales,
         m_particle_data.scales_size,
         Globals::two_quads,
         output,
         true);

    TU::WriteVectorToSs<uint32_t>("linkedMinMax", m_particle_data.linked_min_max, output);

    TU::WriteOneValueToSs("allTeselateZeroMask", m_particle_data.all_teselate_zero_mask, output);

    TU::WriteOneValueToSs("layer", m_particle_data.layer, output);

    if (PgAndTwParticleStrings.size() < m_prt_file_version_info.number_of_iel_in_particle)
    {
        size_t delta = m_prt_file_version_info.number_of_iel_in_particle - PgAndTwParticleStrings.size();

        for (size_t j = 0; j < delta; ++j)
            PgAndTwParticleStrings.push_back("ExtraField" + to_string(j));
    }

    CurvesAndTeselatesUtils::ExportCurvesAndTeselatesToSs
        (m_particle_data.curves_groups, m_particle_data.teselates_groups, PgAndTwParticleStrings, output);

    TU::WriteSingleStringToSs("}", output);
}



void ParticleClass::ExportAsE2160Format(std::stringstream& output)
{
    TU::WriteOneValueToSs("Particle", m_particle_data.particle_name, output, Globals::one_quad);

    TU::WriteSingleStringToSs("{", output);

    TU::WriteOneValueToSs("startTime", m_particle_data.start_time, output);

    TU::WriteOneValueToSs("time", m_particle_data.time, output);

    TU::WriteOneValueToSs("coordinates", m_particle_data.coordinates, output);

    TU::WriteOneValueToSs("type", m_particle_data.type, output);

    TU::WriteOneValueToSs("mesh", m_particle_data.mesh, output);

    m_particle_data.face.ExportToSs("face", output);

    TU::WriteOneValueToSs("triangleA", m_particle_data.triangle_a, output);

    TU::WriteOneValueToSs("multiplyDxyByPrtScale", m_particle_data.multiply_dxy_by_prt_scale_switch, output);

    m_particle_data.trail.ExportToSs("trail", output);

    TU::WriteOneValueToSs("yTextureMul", m_particle_data.y_texture_mul, output);

    TU::WriteVectorToSs<string>("texture", m_particle_data.textures, output);

    TU::WriteVectorToSs<string>("bumpTexture", m_particle_data.bump_textures, output);

    m_particle_data.tex_anim.ExportToSsViaScheme("texAnim", "a,a,a,a,a,a,a,a,a,b,a", output);

    TU::WriteArrayToSs<float>("coordinatesLTRB",
                               m_particle_data.coordinates_ltrb,
                               m_particle_data.coordinates_ltrb_size,
                               output);

    TU::WriteOneValueToSs("xMirrored", m_particle_data.x_mirrored, output);

    TU::WriteOneValueToSs("yMirrored", m_particle_data.y_mirrored, output);

    TU::WriteOneValueToSs("colorRandType", m_particle_data.color_rand_type, output);

    TU::WriteArrayToSs<uint32_t>("trajectory",
                                  m_particle_data.trajectory,
                                  m_particle_data.trajectory_size,
                                  output);

    m_particle_data.gravity.ExportToSs("gravity", output);

    TU::WriteOneValueToSs("disappearsOnGround", m_particle_data.dissappears_on_ground, output);

    TwoTypeArray<float, ParticleData::scale_a_size, uint32_t, ParticleData::scale_b_size>::
        ExportArrayOfTwoTypeArrayToSs
        ("scales",
         m_particle_data.scales,
         m_particle_data.scales_size,
         Globals::two_quads,
         output,
         true);

    TU::WriteVectorToSs<uint32_t>("linkedMinMax", m_particle_data.linked_min_max, output);

    TU::WriteOneValueToSs("allTeselateZeroMask", m_particle_data.all_teselate_zero_mask, output);

    TU::WriteOneValueToSs("layer", m_particle_data.layer, output);

    if (E2160ParticleStrings.size() < m_prt_file_version_info.number_of_iel_in_particle)
    {
        size_t delta = m_prt_file_version_info.number_of_iel_in_particle - E2160ParticleStrings.size();

        for (size_t j = 0; j < delta; ++j)
            E2160ParticleStrings.push_back("ExtraField" + to_string(j));
    }

    CurvesAndTeselatesUtils::ExportCurvesAndTeselatesToSs
        (m_particle_data.curves_groups, m_particle_data.teselates_groups, E2160ParticleStrings, output);

    TU::WriteSingleStringToSs("}", output);
}




void ParticleClass::ExportAsKsFormat(std::stringstream& output)
{
    TU::WriteOneValueToSs("Particle", m_particle_data.particle_name, output, Globals::one_quad);

    TU::WriteSingleStringToSs("{", output);

    TU::WriteOneValueToSs("time", m_particle_data.time, output);

    TU::WriteOneValueToSs("coordinates", m_particle_data.coordinates, output);

    TU::WriteOneValueToSs("type", m_particle_data.type, output);

    TU::WriteOneValueToSs("mesh", m_particle_data.mesh, output);

    m_particle_data.face.ExportToSs("face", output);

    m_particle_data.trail.ExportToSs("trail", output);

    TU::WriteVectorToSs<string>("texture", m_particle_data.textures, output);

    m_particle_data.tex_anim.ExportToSsViaScheme("texAnim", "a,a,a,a,a,a,a,a,a,b,a", output);

    TU::WriteArrayToSs<uint32_t>("trajectory",
                                  m_particle_data.trajectory,
                                  m_particle_data.trajectory_size,
                                  output);

    m_particle_data.gravity.ExportToSs("gravity", output);

    TU::WriteOneValueToSs("enableLight", m_particle_data.enable_light, output);

    TU::WriteOneValueToSs("disappearsOnGround", m_particle_data.dissappears_on_ground, output);

    TU::WriteOneValueToSs("colorRandType", m_particle_data.color_rand_type, output);

    TwoTypeArray<float, ParticleData::scale_a_size, uint32_t, ParticleData::scale_b_size>::
        ExportArrayOfTwoTypeArrayToSs
        ("scales",
         m_particle_data.scales,
         m_particle_data.scales_size,
         Globals::two_quads,
         output,
         false);

    output << m_particle_data.scales_end << endl;

    TU::WriteVectorToSs<uint32_t>("linkedMinMax", m_particle_data.linked_min_max, output);

    TU::WriteOneValueToSs("allTeselateZeroMask", m_particle_data.all_teselate_zero_mask, output);

    TU::WriteOneValueToSs("layer", m_particle_data.layer, output);

    if (KsParticleStrings.size() < m_prt_file_version_info.number_of_iel_in_particle)
    {
        size_t delta = m_prt_file_version_info.number_of_iel_in_particle - KsParticleStrings.size();

        for (size_t j = 0; j < delta; ++j)
            KsParticleStrings.push_back("ExtraField" + to_string(j));
    }

    CurvesAndTeselatesUtils::ExportCurvesAndTeselatesToSs
        (m_particle_data.curves_groups, m_particle_data.teselates_groups, KsParticleStrings, output);

    TU::WriteSingleStringToSs("}", output);
}


void ParticleClass::ExportTo(std::stringstream& output)
{
    switch (m_prt_file_version_info.particle_version)
    {
        case ParticleGlobals::particle_type_value::dynamic_particle:
        break;

        case ParticleGlobals::particle_type_value::ks_particles_emiter:
            ExportAsKsFormat(output);
        break;

        case ParticleGlobals::particle_type_value::particle_gen_particle:
        case ParticleGlobals::particle_type_value::two_worlds_particle:
            ExportAsParticleGenAndTwoWorldsFormat(output);
        break;

        case ParticleGlobals::particle_type_value::e2160_particle:
            ExportAsE2160Format(output);
        break;

        default: break;
    }

}








