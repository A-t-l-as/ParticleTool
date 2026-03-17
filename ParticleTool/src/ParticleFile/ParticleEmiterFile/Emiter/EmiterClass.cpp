#include "EmiterClass.hpp"
#include "Utils/Misc.hpp"
#include "../../../AodCompilator/GlobalQueues.hpp"

#include "../../BasicParticleStructures/CurvesAndTeselatesUtils.hpp"

#include "Utils/TxtUtils.hpp"


using namespace std;

uint32_t EmiterClass::emiter_number = 0;

std::vector<std::string> PgEmiterStrings =
{
    // particle gen:    
"trajectoryXMin",       // ok                
"trajectoryXMax",       // ok                

"trajectoryYMin",       // ok                
"trajectoryYMax",       // ok                

"trajectoryZMin",       // ok                
"trajectoryZMax",       // ok                


"rotationZMin",         // ok                
"rotationZMax",         // ok                


"rotationXMin",         // ok                
"rotationXMax",         // ok                

"rotationYMin",         // ok                
"rotationYMax",         // ok                

"countMin",             // ok                
"countMax",             // ok                

"speedMulMin",          // ok                
"speedMulMax",          // ok                

"sizeMulMin",           // ok                
"sizeMulMax",           // ok                

"timeMulMin",           // ok               
"timeMulMax",           // ok                

"lightRangeMin",        // ok                
"lightRangeMax",        // ok                

"lightColorRMin",       // ok               
"lightColorRMax",       // ok                

"lightColorGMin",       // ok                
"lightColorGMax",       // ok                

"lightColorBMin",       // ok                
"lightColorBMax",       // ok                

"surfaceScaleXMin",     // ok                
"surfaceScaleXMax",     // ok                

"surfaceScaleYMin",     // ok                
"surfaceScaleYMax",     // ok                

"surfaceScaleZMin",     // ok                
"surfaceScaleZMax",     // ok                

"sphereScaleOMin_Min",  // ok                
"sphereScaleOMin_Max",  // ok                

"sphereScaleOMax_Min",  // ok                
"sphereScaleOMax_Max",  // ok                

"sphereScaleWMin_Min",  // ok                
"sphereScaleWMin_Max",  // ok                

"sphereScaleWMax_Min",  // ok                
"sphereScaleWMax_Max"  // ok                

};


std::vector<std::string> TwEmiterStrings =
{
    // two worlds :
"trajectoryXMin",       // ok
"trajectoryXMax",       // ok

"trajectoryYMin",       // ok
"trajectoryYMax",       // ok

"trajectoryZMin",       // ok
"trajectoryZMax",       // ok


"rotationZMin",         // ok
"rotationZMax",         // ok


"rotationXMin",         // ok
"rotationXMax",         // ok

"rotationYMin",         // ok
"rotationYMax",         // ok

"countMin",             // ok
"countMax",             // ok

"speedMulMin",          // ok
"speedMulMax",          // ok

"sizeMulMin",           // ok
"sizeMulMax",           // ok

"timeMulMin",           // ok
"timeMulMax",           // ok


"lightRangeMin",        // ok
"lightRangeMax",        // ok

"lightColorRMin",       // ok
"lightColorRMax",       // ok

"lightColorGMin",       // ok
"lightColorGMax",       // ok

"lightColorBMin",       // ok
"lightColorBMax",       // ok

"lightIntensityMin",    // ok
"lightIntensityMax",    // ok

"surfaceScaleXMin",     // ok
"surfaceScaleXMax",     // ok

"surfaceScaleYMin",     // ok
"surfaceScaleYMax",     // ok

"surfaceScaleZMin",     // ok
"surfaceScaleZMax",     // ok

"sphereScaleOMin_Min",  // ok
"sphereScaleOMin_Max",  // ok

"sphereScaleOMax_Min",  // ok
"sphereScaleOMax_Max",  // ok

"sphereScaleWMin_Min",  // ok
"sphereScaleWMin_Max",  // ok

"sphereScaleWMax_Min",  // ok
"sphereScaleWMax_Max"   // ok

};


std::vector<std::string> E2160EmiterStrings =
{
    // e2160 :
"trajectoryXMin",       // ok
"trajectoryXMax",       // ok

"trajectoryYMin",       // ok
"trajectoryYMax",       // ok

"trajectoryZMin",       // ok
"trajectoryZMax",       // ok


"rotationZMin",         // ok
"rotationZMax",         // ok


"rotationXMin",         // ok
"rotationXMax",         // ok

"rotationYMin",         // ok
"rotationYMax",         // ok

"countMin",             // ok
"countMax",             // ok

"speedMulMin",          // ok 
"speedMulMax",          // ok

"sizeMulMin",           // ok
"sizeMulMax",           // ok

"timeMulMin",           // ok
"timeMulMax",           // ok

"lightRange",           //?

"lightColorR",          // ok     

"lightColorG",          // ok   

"lightColorB",          // ok        

"surfaceScaleX",       // ok
"surfaceScaleY",       // ok
"surfaceScaleZ",       // ok

"sphereScaleOMin",     // ok

"sphereScaleOMax",     // ok

"sphereScaleWMin",     // ok

"sphereScaleWMax"     // ok

};


std::vector<std::string> KsEmiterStrings =
{
"trajectoryX",
"trajectoryY",
"trajectoryZ",

"rotationAlpha",
"rotationBeta",
"rotationPhi",

"countMin",
"countMax",
"speedMulMin",
"speedMulMax",
"sizeMulMin",
"sizeMulMax",
"timeMulMin",
"timeMulMax",
"budget",
"lightRange",
"lightIntensity",
"lightColorR",
"lightColorG",
"lightColorB",
"surfaceScaleX",
"surfaceScaleY",
"surfaceScaleZ",
"sphereScaleOMin",
"sphereScaleOMax",
"sphereScaleWMin",
"sphereScaleWMax"
};


void EmiterClass::InitializeHashMap()
{
    switch (m_prt_file_version_info.particle_version)
    {
        case ParticleGlobals::particle_type_value::particle_gen_particle:
            Misc::InitializeHashMapViaLabelsVector(m_labels_map, PgEmiterStrings);
        break;

        case ParticleGlobals::particle_type_value::two_worlds_particle:
            Misc::InitializeHashMapViaLabelsVector(m_labels_map, TwEmiterStrings);
        break;

        case ParticleGlobals::particle_type_value::e2160_particle:
            Misc::InitializeHashMapViaLabelsVector(m_labels_map, E2160EmiterStrings);
        break;

        case ParticleGlobals::particle_type_value::ks_particles_emiter:
            Misc::InitializeHashMapViaLabelsVector(m_labels_map, KsEmiterStrings);
        break;

        case ParticleGlobals::particle_type_value::dynamic_particle:
        break;

        default: break;
    }

}

EmiterClass::EmiterClass(
                            const ParticleGlobals::ENAppModes& arg_app_mode,
                            ParticleFileVersionInfo arg_prt_file_version_info,
                            string arg_emiter_name,
                            uint8_t arg_fourth_byte_of_header
                        ):

    m_prt_file_version_info(arg_prt_file_version_info),

    m_curve_iel_index(-1),
    m_number_of_single_curve_points_checksum(0),

    m_teselate_iel_index(-1),
    m_number_of_single_teselate_points_checksum(0),

    m_mode( ParticleGlobals::curve_or_teselate_mode::null ),

    m_write_cast_shadows_to_bin(static_cast<uint32_t>(false)),

    m_fourth_byte_of_header( arg_fourth_byte_of_header )
{

    if(arg_app_mode == ParticleGlobals::ENAppModes::m_import)
    {
        m_emiter_data.emiter_name = arg_emiter_name;

        InitializeHashMap();

        m_emiter_data.linked_min_max.resize(m_prt_file_version_info.number_of_linked_min_max_in_emiter,
                                            ParticleGlobals::locked_linked_min_max);

        m_emiter_data.curves_groups.Resize(m_prt_file_version_info.number_of_iel_in_emiter);
        m_emiter_data.teselates_groups.Resize(m_prt_file_version_info.number_of_iel_in_emiter);
    }
}

void EmiterClass::ParseFrom(string& arg_line, GlobalQueues& arg_queues)
{
    TU::GetOneValue<float>(arg_line, "startTime", m_emiter_data.start_time);

    TU::GetOneValue<float>(arg_line, "time", m_emiter_data.time);

    TU::GetOneValue<uint32_t>(arg_line, "coordinates", m_emiter_data.coordinates);

    TU::GetOneValue<uint32_t>(arg_line, "budgetType", m_emiter_data.budget_type);

    TU::GetOneValue<uint32_t>(arg_line, "sunRayDirection", m_emiter_data.sun_ray_direction_switch);

    TU::GetOneValue<uint32_t>(arg_line, "useColor", m_emiter_data.use_color_switch);

    TU::GetOneValue<uint32_t>(arg_line, "createOnGround", m_emiter_data.create_on_ground);

    TU::GetOneValue<uint32_t>(arg_line, "trajectoryZFromGround", m_emiter_data.trajectory_z_from_ground);

    TU::GetOneValue<uint32_t>(arg_line, "enableLight",  m_emiter_data.enable_light);

    TU::GetOneValue<float>(arg_line, "umbraDistanceMul", m_emiter_data.umbra_distance_mul);

    //------------------------------------------------- special -------------------------------------
    TU::GetOneValue<uint32_t>(arg_line, "writeCastShadowsToBin",  m_write_cast_shadows_to_bin);
    //------------------------------------------------- special -------------------------------------

    TU::GetOneValue<uint32_t>(arg_line, "castShadows", m_emiter_data.cast_shadows);
    //-----------------------------------------------------------------------------------------------

    TU::GetOneValue<uint32_t>(arg_line, "moveEndOfLaser",  m_emiter_data.move_end_of_laser_switch);

    TU::GetOneValue<uint32_t>(arg_line, "attachToEndOfLaser",  m_emiter_data.attach_to_end_of_laser_switch);

    TU::GetOneValue<uint32_t>(arg_line, "unknownValue1",  m_emiter_data.unknown_value_1);
    TU::GetOneValue<uint32_t>(arg_line, "unknownValue2",  m_emiter_data.unknown_value_2);
    TU::GetOneValue<uint32_t>(arg_line, "unknownValue3",  m_emiter_data.unknown_value_3);
    TU::GetOneValue<uint32_t>(arg_line, "unknownValue4",  m_emiter_data.unknown_value_4);
    TU::GetOneValue<uint32_t>(arg_line, "unknownValue5",  m_emiter_data.unknown_value_5);

    TU::GetOneValue<uint32_t>(arg_line, "allTeselateZeroMask", m_emiter_data.all_teselate_zero_mask);

    TU::GetArrayValues<uint32_t>(arg_line, "surface", "%d", m_emiter_data.surface, m_emiter_data.surface_size);

    TU::GetArrayValues<float>(arg_line, "sphere", "%f", m_emiter_data.sphere, m_emiter_data.sphere_size);

    TU::GetArrayValues<uint32_t>(arg_line, "rotation", "%d", m_emiter_data.rotation, m_emiter_data.rotation_size);

    TU::GetArrayValues<uint32_t>(arg_line, "randomSeed", "%d", m_emiter_data.random_seed, m_emiter_data.random_seed_size);

    TU::GetArrayValues<uint32_t>(arg_line,
                               "linkedMinMax", 
                               "%d", 
                               &m_emiter_data.linked_min_max[0], 
                               static_cast<int>(m_emiter_data.linked_min_max.size()));

    TU::GetSingleStringFromQueue(arg_line, "texture", m_emiter_data.texture, arg_queues.m_texture_q);

    m_emiter_data.cubic.ParseFrom(arg_line, "cubic", "%f", "%d");

    m_emiter_data.plane.ParseFrom(arg_line, "plane", "%f", "%d");

    TU::GetVectorOfStringsFromQueue(arg_line, "slotStrings", m_emiter_data.slot_strings, arg_queues.m_slot_strings_q);

    m_emiter_data.scales.ParseViaSchemeFrom(arg_line, "scales", "%f", "%d", "a,a,a,b,a,a,a,b,a,a,a,a,a,a,a,a");

    m_emiter_data.curves_groups.ParseFrom(arg_line,
        m_curve_iel_index,
        m_number_of_single_curve_points_checksum,
        m_labels_map,
        m_mode);


    m_emiter_data.teselates_groups.ParseFrom(arg_line,
        m_teselate_iel_index,
        m_number_of_single_teselate_points_checksum,
        m_labels_map,
        m_mode);


}

void EmiterClass::WriteTo(BinFile& output_file_buff)
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

void EmiterClass::WriteToKsFormat(BinFile& output_file_buff)
{

    output_file_buff.WriteValue(m_emiter_data.time);

    output_file_buff.WriteValue(m_emiter_data.coordinates);

    output_file_buff.WriteValue(m_emiter_data.budget_type);

    output_file_buff.WriteValue(m_emiter_data.surface[0]);

    output_file_buff.WriteValue(m_emiter_data.sphere);

    output_file_buff.WriteValue(m_emiter_data.cubic);

    output_file_buff.WriteValue(m_emiter_data.plane.a);

    output_file_buff.WriteStringWithLen(m_emiter_data.texture, true);

    output_file_buff.WriteValue(m_emiter_data.plane.b);

    output_file_buff.WriteValue(m_emiter_data.surface[1]);

    output_file_buff.WriteValue(m_emiter_data.surface[2]);

    output_file_buff.WriteValue(m_emiter_data.enable_light);

    output_file_buff.WriteArrayFromTo(m_emiter_data.scales.a, 0, 2);

    output_file_buff.WriteValue(m_emiter_data.scales.b[0]);

    output_file_buff.WriteValue(m_emiter_data.scales.a[12]);

    output_file_buff.WriteArrayFromTo(m_emiter_data.scales.a, 3, 5);

    output_file_buff.WriteValue(m_emiter_data.scales.b[1]);

    output_file_buff.WriteArrayFromTo(m_emiter_data.scales.a, 6, 11);

    m_emiter_data.teselates_groups.WriteTo<uint32_t>(output_file_buff);

    m_emiter_data.teselates_groups.WriteTeselateFlagsTo(output_file_buff);

    output_file_buff.WriteVector(m_emiter_data.linked_min_max);

    output_file_buff.WriteValue(m_emiter_data.all_teselate_zero_mask);

}

void EmiterClass::WriteToParticleGenAndTwoWorldsFormat(BinFile& output_file_buff)
{
    output_file_buff.WriteStringWithLen(m_emiter_data.emiter_name);

    output_file_buff.WriteValue(m_emiter_data.start_time);

    output_file_buff.WriteValue(m_emiter_data.time);

    output_file_buff.WriteValue(m_emiter_data.coordinates);

    output_file_buff.WriteVectorOfStringsWithLen(m_emiter_data.slot_strings);

    output_file_buff.WriteValue(m_emiter_data.surface[0]);

    output_file_buff.WriteValue(m_emiter_data.sphere);

    output_file_buff.WriteValue(m_emiter_data.cubic);

    output_file_buff.WriteValue(m_emiter_data.plane.a);

    output_file_buff.WriteStringWithLen(m_emiter_data.texture);

    output_file_buff.WriteValue(m_emiter_data.plane.b);

    output_file_buff.WriteValue(m_emiter_data.use_color_switch);

    output_file_buff.WriteArrayFromTo(m_emiter_data.surface, 1, 2);

    output_file_buff.WriteValue(m_emiter_data.sun_ray_direction_switch);

    output_file_buff.WriteValue(m_emiter_data.create_on_ground);

    output_file_buff.WriteValue(m_emiter_data.trajectory_z_from_ground);

    output_file_buff.WriteArrayViaIndexes(m_emiter_data.rotation, { 2, 0, 1 });

    output_file_buff.WriteValue(m_emiter_data.enable_light);

    if( (m_prt_file_version_info.particle_version == ParticleGlobals::particle_type_value::two_worlds_particle)
        && (static_cast<bool>(m_write_cast_shadows_to_bin) == true) )
    {
        output_file_buff.WriteValue(m_emiter_data.cast_shadows);
    }

    output_file_buff.WriteValue(m_emiter_data.umbra_distance_mul);

    output_file_buff.WriteArrayFromTo(m_emiter_data.scales.a, 0, 2);

    output_file_buff.WriteValue(m_emiter_data.scales.b[0]);

    output_file_buff.WriteValue(m_emiter_data.scales.a[12]);

    output_file_buff.WriteArrayFromTo(m_emiter_data.scales.a, 3, 5);

    output_file_buff.WriteValue(m_emiter_data.scales.b[1]);

    output_file_buff.WriteArrayFromTo(m_emiter_data.scales.a, 6, 10);

    output_file_buff.WriteValue(m_emiter_data.move_end_of_laser_switch);

    output_file_buff.WriteValue(m_emiter_data.attach_to_end_of_laser_switch);

    output_file_buff.WriteValue(m_emiter_data.random_seed);

    output_file_buff.WriteArrayViaIndexes(m_emiter_data.scales.a, { 11, 13 });

    output_file_buff.WriteValue(m_emiter_data.unknown_value_1);
    output_file_buff.WriteValue(m_emiter_data.unknown_value_2);
    output_file_buff.WriteValue(m_emiter_data.unknown_value_3);
    output_file_buff.WriteValue(m_emiter_data.unknown_value_4);
    output_file_buff.WriteValue(m_emiter_data.unknown_value_5);

    m_emiter_data.curves_groups.WriteTo(output_file_buff);

    
    if (m_prt_file_version_info.particle_version == ParticleGlobals::particle_type_value::two_worlds_particle)
    {

        m_emiter_data.teselates_groups.WriteTo<uint64_t>(output_file_buff, true);
    }
    else
    {

        m_emiter_data.teselates_groups.WriteTo<uint64_t>(output_file_buff);

        m_emiter_data.teselates_groups.WriteTeselateFlagsTo(output_file_buff);
    }

    output_file_buff.WriteVector(m_emiter_data.linked_min_max);
    output_file_buff.WriteValue(m_emiter_data.all_teselate_zero_mask);

}


void EmiterClass::WriteToE2160Format(BinFile& output_file_buff)
{
    output_file_buff.WriteStringWithLen(m_emiter_data.emiter_name);

    output_file_buff.WriteValue(m_emiter_data.start_time);

    output_file_buff.WriteValue(m_emiter_data.time);

    output_file_buff.WriteValue(m_emiter_data.coordinates);

    output_file_buff.WriteValue(m_emiter_data.surface[0]);

    output_file_buff.WriteValue(m_emiter_data.sphere);

    output_file_buff.WriteValue(m_emiter_data.cubic);

    output_file_buff.WriteValue(m_emiter_data.plane.a);

    output_file_buff.WriteStringWithLen(m_emiter_data.texture);

    output_file_buff.WriteValue(m_emiter_data.plane.b);

    output_file_buff.WriteArrayFromTo(m_emiter_data.surface, 1, 2);

    output_file_buff.WriteValue(m_emiter_data.enable_light);

    output_file_buff.WriteValue(m_emiter_data.umbra_distance_mul);

    output_file_buff.WriteArrayFromTo(m_emiter_data.scales.a, 0, 2);

    output_file_buff.WriteValue(m_emiter_data.scales.b[0]);

    output_file_buff.WriteValue(m_emiter_data.scales.a[12]);

    output_file_buff.WriteArrayFromTo(m_emiter_data.scales.a, 3, 5);

    output_file_buff.WriteValue(m_emiter_data.scales.b[1]);

    output_file_buff.WriteArrayFromTo(m_emiter_data.scales.a, 6, 10);

    output_file_buff.WriteValue(m_emiter_data.move_end_of_laser_switch);

    output_file_buff.WriteValue(m_emiter_data.attach_to_end_of_laser_switch);

    output_file_buff.WriteValue(m_emiter_data.random_seed);

    output_file_buff.WriteArrayViaIndexes(m_emiter_data.scales.a, { 11, 13 } );

    //BW::WriteCurves(output_file_buff, m_emiter_data.curves_groups, true);
    m_emiter_data.curves_groups.WriteTo(output_file_buff, true);

    //BW::WriteTeselates<uint64_t>(output_file_buff, m_emiter_data.teselates_groups);
    m_emiter_data.teselates_groups.WriteTo<uint64_t>(output_file_buff);

    //output_file_buff.WriteVector(m_emiter_data.teselates_groups.teselate_flags);
    m_emiter_data.teselates_groups.WriteTeselateFlagsTo(output_file_buff);

    output_file_buff.WriteVector(m_emiter_data.linked_min_max);
    output_file_buff.WriteValue(m_emiter_data.all_teselate_zero_mask);
}



void EmiterClass::ReadFromParticleGenAndTwoWorldsFile(BinFile& buff)
{
    m_emiter_data.emiter_name = buff.ReadStringWithNullTerminator();

    buff.ReadValue(m_emiter_data.start_time);

    buff.ReadValue(m_emiter_data.time);

    buff.ReadValue(m_emiter_data.coordinates);

    uint64_t size_of_slot_strings = 0;
    buff.ReadValue(size_of_slot_strings);

    for (uint64_t i = 0; i < size_of_slot_strings; ++i)
    {
        m_emiter_data.slot_strings.push_back( buff.ReadStringWithNullTerminator() );
    }

    buff.ReadValue(m_emiter_data.surface[0]);

    buff.ReadArray(m_emiter_data.sphere, m_emiter_data.sphere_size);

    buff.ReadArray(m_emiter_data.cubic.a, m_emiter_data.cubic_a_size);

    buff.ReadArray(m_emiter_data.cubic.b, m_emiter_data.cubic_b_size);

    buff.ReadArray(m_emiter_data.plane.a, m_emiter_data.plane_a_size);

    m_emiter_data.texture = buff.ReadStringWithNullTerminator();

    buff.ReadArray(m_emiter_data.plane.b, m_emiter_data.plane_b_size);

    buff.ReadValue(m_emiter_data.use_color_switch);

    buff.ReadArrayViaIndexes(m_emiter_data.surface, { 1, 2});

    buff.ReadValue(m_emiter_data.sun_ray_direction_switch);

    buff.ReadValue(m_emiter_data.create_on_ground);

    buff.ReadValue(m_emiter_data.trajectory_z_from_ground);


    buff.ReadArrayViaIndexes(m_emiter_data.rotation, { 2, 0, 1});

    buff.ReadValue(m_emiter_data.enable_light);

    if( (m_prt_file_version_info.particle_version == ParticleGlobals::particle_type_value::two_worlds_particle) &&
        (m_fourth_byte_of_header == ParticleGlobals::tw_new_format_fourth_byte_of_header) )
    {
        buff.ReadValue(m_emiter_data.cast_shadows);
    }

    buff.ReadValue(m_emiter_data.umbra_distance_mul);


    buff.ReadArrayFromTo(m_emiter_data.scales.a, 0, 2);

    buff.ReadValue(m_emiter_data.scales.b[0]);

    buff.ReadValue(m_emiter_data.scales.a[12]);

    buff.ReadArrayFromTo(m_emiter_data.scales.a, 3, 5);

    buff.ReadValue(m_emiter_data.scales.b[1]);

    buff.ReadArrayFromTo(m_emiter_data.scales.a, 6, 10);

    buff.ReadValue(m_emiter_data.move_end_of_laser_switch);
    buff.ReadValue(m_emiter_data.attach_to_end_of_laser_switch);

    buff.ReadArray(m_emiter_data.random_seed, m_emiter_data.random_seed_size);

    buff.ReadArrayViaIndexes(m_emiter_data.scales.a, { 11, 13 });

    buff.ReadValue(m_emiter_data.unknown_value_1);
    buff.ReadValue(m_emiter_data.unknown_value_2);
    buff.ReadValue(m_emiter_data.unknown_value_3);
    buff.ReadValue(m_emiter_data.unknown_value_4);
    buff.ReadValue(m_emiter_data.unknown_value_5);

    m_emiter_data.curves_groups.ReadFrom(m_prt_file_version_info.number_of_iel_in_emiter, buff);

    m_emiter_data.curves_groups.ResizeOnlyCurveBonusValues(m_prt_file_version_info.number_of_iel_in_emiter);


    if (m_prt_file_version_info.particle_version == ParticleGlobals::particle_type_value::two_worlds_particle)
    {
        m_emiter_data.teselates_groups.ReadFrom<uint64_t>(m_prt_file_version_info.number_of_iel_in_emiter, buff, true);
    }
    else
    {
        m_emiter_data.teselates_groups.ReadFrom<uint64_t>(m_prt_file_version_info.number_of_iel_in_emiter, buff);

        m_emiter_data.teselates_groups.ReadOnlyTeselateFlags(buff, m_prt_file_version_info.number_of_iel_in_emiter);

    }


    for (uint32_t i = 0; i < m_prt_file_version_info.number_of_linked_min_max_in_emiter; ++i)
    {
        uint32_t temp_linked_min_max = 0;
        buff.ReadValue(temp_linked_min_max);
        m_emiter_data.linked_min_max.push_back(temp_linked_min_max);
    }

    buff.ReadValue(m_emiter_data.all_teselate_zero_mask);


}




void EmiterClass::ReadFromE2160File(BinFile& buff)
{
    m_emiter_data.emiter_name = buff.ReadStringWithNullTerminator();

    buff.ReadValue(m_emiter_data.start_time);

    buff.ReadValue(m_emiter_data.time);

    buff.ReadValue(m_emiter_data.coordinates);

    buff.ReadValue(m_emiter_data.surface[0]);


    buff.ReadArray(m_emiter_data.sphere, m_emiter_data.sphere_size);

    buff.ReadArray(m_emiter_data.cubic.a, m_emiter_data.cubic_a_size);

    buff.ReadArray(m_emiter_data.cubic.b, m_emiter_data.cubic_b_size);

    buff.ReadArray(m_emiter_data.plane.a, m_emiter_data.plane_a_size);

    m_emiter_data.texture = buff.ReadStringWithNullTerminator();

    buff.ReadValue(m_emiter_data.plane.b[0]);

    buff.ReadArrayViaIndexes(m_emiter_data.surface, { 1, 2 });

    buff.ReadValue(m_emiter_data.enable_light);
    buff.ReadValue(m_emiter_data.umbra_distance_mul);

    buff.ReadArrayFromTo(m_emiter_data.scales.a, 0, 2);

    buff.ReadValue(m_emiter_data.scales.b[0]);

    buff.ReadValue(m_emiter_data.scales.a[12]);

    buff.ReadArrayFromTo(m_emiter_data.scales.a, 3, 5);

    buff.ReadValue(m_emiter_data.scales.b[1]);

    buff.ReadArrayFromTo(m_emiter_data.scales.a, 6, 10);

    buff.ReadValue(m_emiter_data.move_end_of_laser_switch);
    buff.ReadValue(m_emiter_data.attach_to_end_of_laser_switch);

    buff.ReadArray(m_emiter_data.random_seed, m_emiter_data.random_seed_size);

    buff.ReadArrayViaIndexes(m_emiter_data.scales.a, { 11, 13 });

    m_emiter_data.curves_groups.ReadFrom(m_prt_file_version_info.number_of_iel_in_emiter, buff, true);

    m_emiter_data.teselates_groups.ReadFrom<uint64_t>(m_prt_file_version_info.number_of_iel_in_emiter, buff);

    m_emiter_data.teselates_groups.ReadOnlyTeselateFlags(buff, m_prt_file_version_info.number_of_iel_in_emiter);


    for (uint32_t i = 0; i < m_prt_file_version_info.number_of_linked_min_max_in_emiter; ++i)
    {
        uint32_t temp_linked_min_max = 0;
        buff.ReadValue(temp_linked_min_max);
        m_emiter_data.linked_min_max.push_back(temp_linked_min_max);
    }

    buff.ReadValue(m_emiter_data.all_teselate_zero_mask);

}



void EmiterClass::ReadFromKsFile(BinFile& buff)
{
    ++emiter_number;

    m_emiter_data.emiter_name = "E" + to_string(emiter_number);

    buff.ReadValue(m_emiter_data.time);

    buff.ReadValue(m_emiter_data.coordinates);

    buff.ReadValue(m_emiter_data.budget_type);

    buff.ReadValue(m_emiter_data.surface[0]);

    buff.ReadArray(m_emiter_data.sphere, m_emiter_data.sphere_size);

    buff.ReadArray(m_emiter_data.cubic.a, m_emiter_data.cubic_a_size);
    buff.ReadArray(m_emiter_data.cubic.b, m_emiter_data.cubic_b_size);


    buff.ReadValue(m_emiter_data.plane.a[0]);
    buff.ReadValue(m_emiter_data.plane.a[1]);

    m_emiter_data.texture = buff.ReadStringWithNullTerminator();

    buff.ReadValue(m_emiter_data.plane.b[0]);

    buff.ReadValue(m_emiter_data.surface[1]);
    buff.ReadValue(m_emiter_data.surface[2]);

    buff.ReadValue(m_emiter_data.enable_light);

    buff.ReadArrayFromTo(m_emiter_data.scales.a, 0, 2);

    buff.ReadValue(m_emiter_data.scales.b[0]);
    buff.ReadValue(m_emiter_data.scales.a[12]);

    buff.ReadArrayFromTo(m_emiter_data.scales.a, 3, 5);

    buff.ReadValue(m_emiter_data.scales.b[1]);

    buff.ReadArrayFromTo(m_emiter_data.scales.a, 6, 11);

    m_emiter_data.teselates_groups.ReadFrom<uint32_t>(m_prt_file_version_info.number_of_iel_in_emiter, buff);

    m_emiter_data.teselates_groups.ReadOnlyTeselateFlags(buff, m_prt_file_version_info.number_of_iel_in_emiter);


    for (uint32_t i = 0; i < m_prt_file_version_info.number_of_linked_min_max_in_emiter; ++i)
    {
        uint32_t temp_linked_min_max = 0;
        buff.ReadValue(temp_linked_min_max);
        m_emiter_data.linked_min_max.push_back(temp_linked_min_max);
    }

    buff.ReadValue(m_emiter_data.all_teselate_zero_mask);

    //Interpolacja:
    CurvesAndTeselatesUtils::MakeCurves
        (m_emiter_data.teselates_groups, m_emiter_data.curves_groups, SingleCurvePointConsts::e2160_example_curve_point);

}



void EmiterClass::ReadFrom(BinFile& buff)
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




void EmiterClass::ExportAsParticleGenAndTwoWorldsFormat(std::stringstream& output)
{
    TU::WriteOneValueToSs("Emiter", m_emiter_data.emiter_name, output, Globals::one_quad);

    TU::WriteSingleStringToSs("{", output);

    TU::WriteOneValueToSs("startTime", m_emiter_data.start_time, output);

    TU::WriteOneValueToSs("time", m_emiter_data.time, output);

    TU::WriteOneValueToSs("coordinates", m_emiter_data.coordinates, output);

    TU::WriteVectorToSs<string>("slotStrings", m_emiter_data.slot_strings, output);

    TU::WriteArrayToSs<uint32_t>("surface",
                                  m_emiter_data.surface,
                                  m_emiter_data.surface_size,
                                  output);

    TU::WriteOneValueToSs("sunRayDirection", m_emiter_data.sun_ray_direction_switch, output);

    TU::WriteArrayToSs<float>("sphere",
                               m_emiter_data.sphere,
                               m_emiter_data.sphere_size,
                               output);

    m_emiter_data.cubic.ExportToSs("cubic", output);

    m_emiter_data.plane.ExportToSs("plane", output);

    TU::WriteOneValueToSs("useColor", m_emiter_data.use_color_switch, output);

    TU::WriteOneValueToSs("texture", m_emiter_data.texture, output);

    TU::WriteOneValueToSs("enableLight", m_emiter_data.enable_light, output);

    if(m_prt_file_version_info.particle_version == ParticleGlobals::particle_type_value::two_worlds_particle)
    {
        if (m_fourth_byte_of_header == ParticleGlobals::tw_old_format_fourth_byte_of_header)
        {
            TU::WriteOneValueToSs("writeCastShadowsToBin", false, output);
        }

        if (m_fourth_byte_of_header == ParticleGlobals::tw_new_format_fourth_byte_of_header)
        {
            TU::WriteOneValueToSs("writeCastShadowsToBin", true, output);
            TU::WriteOneValueToSs("castShadows", m_emiter_data.cast_shadows, output);
        }
    }

    TU::WriteOneValueToSs("umbraDistanceMul", m_emiter_data.umbra_distance_mul, output);

    m_emiter_data.scales.ExportToSsViaScheme("scales", "a,a,a,b,a,a,a,b,a,a,a,a,a,a,a,a", output);

    TU::WriteOneValueToSs("moveEndOfLaser", m_emiter_data.move_end_of_laser_switch, output);

    TU::WriteOneValueToSs("attachToEndOfLaser", m_emiter_data.attach_to_end_of_laser_switch, output);

    TU::WriteArrayToSs<uint32_t>("randomSeed",
                                  m_emiter_data.random_seed,
                                  m_emiter_data.random_seed_size,
                                  output);

    TU::WriteOneValueToSs("createOnGround", m_emiter_data.create_on_ground, output);

    TU::WriteOneValueToSs("trajectoryZFromGround", m_emiter_data.trajectory_z_from_ground, output);

    TU::WriteArrayToSs<uint32_t>("rotation",
                                  m_emiter_data.rotation,
                                  m_emiter_data.rotation_size,
                                  output);

    TU::WriteOneValueToSs("unknownValue1", m_emiter_data.unknown_value_1, output);

    TU::WriteOneValueToSs("unknownValue2", m_emiter_data.unknown_value_2, output);

    TU::WriteOneValueToSs("unknownValue3", m_emiter_data.unknown_value_3, output);

    TU::WriteOneValueToSs("unknownValue4", m_emiter_data.unknown_value_4, output);

    TU::WriteOneValueToSs("unknownValue5", m_emiter_data.unknown_value_5, output);

    TU::WriteVectorToSs<uint32_t>("linkedMinMax", m_emiter_data.linked_min_max, output);

    TU::WriteOneValueToSs("allTeselateZeroMask", m_emiter_data.all_teselate_zero_mask, output);


    if (PgEmiterStrings.size() < m_prt_file_version_info.number_of_iel_in_emiter)
    {
        size_t delta = m_prt_file_version_info.number_of_iel_in_emiter - PgEmiterStrings.size();

        for (size_t j = 0; j < delta; ++j)
            PgEmiterStrings.push_back("ExtraField" + to_string(j));
    }

    if (m_prt_file_version_info.particle_version == ParticleGlobals::particle_type_value::two_worlds_particle)
    {
        CurvesAndTeselatesUtils::ExportCurvesAndTeselatesToSs
            (m_emiter_data.curves_groups, m_emiter_data.teselates_groups, TwEmiterStrings, output);
    }
    else
    {
        CurvesAndTeselatesUtils::ExportCurvesAndTeselatesToSs
            (m_emiter_data.curves_groups, m_emiter_data.teselates_groups, PgEmiterStrings, output);
    }

    TU::WriteSingleStringToSs("}", output);

}




void EmiterClass::ExportAsE2160Format(std::stringstream& output)
{
    TU::WriteOneValueToSs("Emiter", m_emiter_data.emiter_name, output, Globals::one_quad);

    TU::WriteSingleStringToSs("{", output);

    TU::WriteOneValueToSs("startTime", m_emiter_data.start_time, output);

    TU::WriteOneValueToSs("time", m_emiter_data.time, output);

    TU::WriteOneValueToSs("coordinates", m_emiter_data.coordinates, output);

    TU::WriteArrayToSs<uint32_t>("surface",
                                  m_emiter_data.surface,
                                  m_emiter_data.surface_size,
                                  output);

    TU::WriteArrayToSs<float>("sphere",
                               m_emiter_data.sphere,
                               m_emiter_data.sphere_size,
                               output);

    m_emiter_data.cubic.ExportToSs("cubic", output);

    m_emiter_data.plane.ExportToSs("plane", output);

    TU::WriteOneValueToSs("texture", m_emiter_data.texture, output);

    TU::WriteOneValueToSs("enableLight", m_emiter_data.enable_light, output);

    TU::WriteOneValueToSs("umbraDistanceMul", m_emiter_data.umbra_distance_mul, output);

    m_emiter_data.scales.ExportToSsViaScheme("scales", "a,a,a,b,a,a,a,b,a,a,a,a,a,a,a,a", output);

    TU::WriteOneValueToSs("moveEndOfLaser", m_emiter_data.move_end_of_laser_switch, output);

    TU::WriteOneValueToSs("attachToEndOfLaser", m_emiter_data.attach_to_end_of_laser_switch, output);

    TU::WriteArrayToSs<uint32_t>("randomSeed",
                                  m_emiter_data.random_seed,
                                  m_emiter_data.random_seed_size,
                                  output);

    TU::WriteVectorToSs<uint32_t>("linkedMinMax", m_emiter_data.linked_min_max, output);

    TU::WriteOneValueToSs("allTeselateZeroMask", m_emiter_data.all_teselate_zero_mask, output);

    if (E2160EmiterStrings.size() < m_prt_file_version_info.number_of_iel_in_emiter)
    {
        size_t delta = m_prt_file_version_info.number_of_iel_in_emiter - E2160EmiterStrings.size();

        for (size_t j = 0; j < delta; ++j)
            E2160EmiterStrings.push_back("ExtraField" + to_string(j));
    }

    CurvesAndTeselatesUtils::ExportCurvesAndTeselatesToSs
        (m_emiter_data.curves_groups, m_emiter_data.teselates_groups, E2160EmiterStrings, output);

    TU::WriteSingleStringToSs("}", output);
}




void EmiterClass::ExportAsKsFormat(std::stringstream& output)
{
    TU::WriteOneValueToSs("Emiter", m_emiter_data.emiter_name, output, Globals::one_quad);

    TU::WriteSingleStringToSs("{", output);

    TU::WriteOneValueToSs("time", m_emiter_data.time, output);

    TU::WriteOneValueToSs("coordinates", m_emiter_data.coordinates, output);

    TU::WriteOneValueToSs("budgetType", m_emiter_data.budget_type, output);

    TU::WriteArrayToSs<uint32_t>("surface",
                                  m_emiter_data.surface,
                                  m_emiter_data.surface_size,
                                  output);

    TU::WriteArrayToSs<float>("sphere",
                               m_emiter_data.sphere,
                               m_emiter_data.sphere_size,
                               output);

    m_emiter_data.cubic.ExportToSs("cubic", output);

    m_emiter_data.plane.ExportToSs("plane", output);

    TU::WriteOneValueToSs("enableLight", m_emiter_data.enable_light, output);

    m_emiter_data.scales.ExportToSsViaScheme("scales", "a,a,a,b,a,a,a,b,a,a,a,a,a,a,a", output);

    TU::WriteOneValueToSs("texture", m_emiter_data.texture, output);

    TU::WriteVectorToSs<uint32_t>("linkedMinMax", m_emiter_data.linked_min_max, output);

    TU::WriteOneValueToSs("allTeselateZeroMask", m_emiter_data.all_teselate_zero_mask, output);

    if (KsEmiterStrings.size() < m_prt_file_version_info.number_of_iel_in_emiter)
    {
        size_t delta = m_prt_file_version_info.number_of_iel_in_emiter - KsEmiterStrings.size();

        for (size_t j = 0; j < delta; ++j)
            KsEmiterStrings.push_back("ExtraField" + to_string(j));
    }

    CurvesAndTeselatesUtils::ExportCurvesAndTeselatesToSs
        (m_emiter_data.curves_groups, m_emiter_data.teselates_groups, KsEmiterStrings, output);

    TU::WriteSingleStringToSs("}", output);
}



void EmiterClass::ExportTo(std::stringstream& output)
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












