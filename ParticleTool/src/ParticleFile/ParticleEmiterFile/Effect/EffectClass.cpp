#include "EffectClass.hpp"
#include "Utils/Misc.hpp"
#include "../../../AodCompilator/GlobalQueues.hpp"

#include "Utils/TxtUtils.hpp"


#include "../../BasicParticleStructures/CurvesAndTeselatesUtils.hpp"

using namespace std;

std::vector<std::string> PgEffectStrings = 
{
                    // particle gen      // two worlds
"trajectoryXMin",   // ok                // ok
"trajectoryXMax",   // ok                // ok

"trajectoryYMin",   // ok                // ok
"trajectoryYMax",   // ok                // ok

"trajectoryZMin",   // ok                // ok
"trajectoryZMax",   // ok                // ok

"rotationZMin",     // ok                // ok
"rotationZMax",     // ok                // ok

"rotationXMin",     // ok                // ok
"rotationXMax",     // ok                // ok

"rotationYMin",     // ok                // ok
"rotationYMax"      // ok                // ok

};




void EffectClass::InitializeHashMap()
{
    switch (m_prt_file_version_info.particle_version)
    {
        case ParticleGlobals::particle_type_value::particle_gen_particle:
        case ParticleGlobals::particle_type_value::two_worlds_particle:
            Misc::InitializeHashMapViaLabelsVector(m_labels_map, PgEffectStrings);
        break;

        case ParticleGlobals::particle_type_value::e2160_particle:
        case ParticleGlobals::particle_type_value::dynamic_particle:
        case ParticleGlobals::particle_type_value::ks_particles_emiter:
        break;

        default: break;
    }

}

EffectClass::EffectClass(
                            const ParticleGlobals::ENAppModes& arg_app_mode,
                            ParticleFileVersionInfo arg_prt_file_version_info,
                            string arg_effect_name
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
        InitializeHashMap();

        m_effect_data.linked_min_max.resize(m_prt_file_version_info.number_of_linked_min_max_in_effect,
                                            ParticleGlobals::locked_linked_min_max);

        m_effect_data.curves_groups.Resize(m_prt_file_version_info.number_of_iel_in_effect);
        m_effect_data.teselates_groups.Resize(m_prt_file_version_info.number_of_iel_in_effect);
    }

}


void EffectClass::ParseFrom(string& arg_line, GlobalQueues& arg_queues)
{
    TU::GetOneValue<uint32_t>(arg_line, "particle2D", m_effect_data.particle_2D_switch);
    TU::GetOneValue<uint32_t>(arg_line, "width", m_effect_data.width);
    TU::GetOneValue<uint32_t>(arg_line, "height", m_effect_data.height);
    TU::GetOneValue<float>(arg_line, "startTime", m_effect_data.start_time);
    TU::GetOneValue<float>(arg_line, "time", m_effect_data.time);

    TU::GetOneValue<uint32_t>(arg_line, "loops", m_effect_data.loops);
    TU::GetOneValue<uint32_t>(arg_line, "unknownValue1", m_effect_data.unknown_value_1);
    TU::GetOneValue<uint32_t>(arg_line, "unknownValue2", m_effect_data.unknown_value_2);

    TU::GetSingleStringFromQueue(arg_line, "annotation", m_effect_data.annotation, arg_queues.m_annotations_q);

    TU::GetOneValue<uint32_t>(arg_line, "allTeselateZeroMask", m_effect_data.all_teselate_zero_mask);

    if (!m_effect_data.linked_min_max.empty())
    {
        TU::GetArrayValues<uint32_t>(arg_line,
            "linkedMinMax",
            "%d",
            &m_effect_data.linked_min_max[0],
            static_cast<int>(m_effect_data.linked_min_max.size()));
    }

    TU::GetOneValue<uint32_t>(arg_line, "scale", m_effect_data.e2160_effect_scale);

    TwoTypeArray<float, EffectData::scale_a_size, uint32_t, EffectData::scale_b_size> ::
    ParseArrayOfTwoTypeArrayFrom ( arg_line, "scales", "%f", "%d", m_effect_data.scales, m_effect_data.scales_size );

    m_effect_data.curves_groups.ParseFrom (arg_line,
        m_curve_iel_index,
        m_number_of_single_curve_points_checksum,
        m_labels_map,
        m_mode);

    m_effect_data.teselates_groups.ParseFrom(arg_line,
        m_teselate_iel_index,
        m_number_of_single_teselate_points_checksum,
        m_labels_map,
        m_mode);

}


void EffectClass::WriteTo(BinFile& output_file_buff)
{
    switch (m_prt_file_version_info.particle_version)
    {
        case ParticleGlobals::particle_type_value::particle_gen_particle:
        case ParticleGlobals::particle_type_value::two_worlds_particle:
            WriteToParticleGenAndTwoWorldsFormat(output_file_buff);
        break;

        case ParticleGlobals::particle_type_value::e2160_particle:
            WriteToE2160Format(output_file_buff);
        break;

        case ParticleGlobals::particle_type_value::dynamic_particle:
        case ParticleGlobals::particle_type_value::ks_particles_emiter:
        break;

        default: break;
    }

}


void EffectClass::WriteToParticleGenAndTwoWorldsFormat(BinFile& output_file_buff)
{
    output_file_buff.WriteStringWithLen(m_effect_data.annotation);

    output_file_buff.WriteValue(m_effect_data.particle_2D_switch);
    output_file_buff.WriteValue(m_effect_data.width);
    output_file_buff.WriteValue(m_effect_data.height);

    output_file_buff.WriteValue(m_effect_data.start_time);
    output_file_buff.WriteValue(m_effect_data.time);
    output_file_buff.WriteValue(m_effect_data.loops);
   
    output_file_buff.WriteValue(m_effect_data.scales);

    output_file_buff.WriteValue(m_effect_data.unknown_value_1);
    output_file_buff.WriteValue(m_effect_data.unknown_value_2);

    //BW::WriteCurves(output_file_buff, m_effect_data.curves_groups);
    m_effect_data.curves_groups.WriteTo(output_file_buff);
    
    if (m_prt_file_version_info.particle_version == ParticleGlobals::particle_type_value::two_worlds_particle)
    {
        // BW::WriteTeselates<uint64_t>(output_file_buff,
        //                              m_effect_data.teselates_groups,
        //                              true);

        m_effect_data.teselates_groups.WriteTo<uint64_t>(output_file_buff, true);
    }
    else
    {
        // BW::WriteTeselates<uint64_t>(output_file_buff,
        //                              m_effect_data.teselates_groups);

        m_effect_data.teselates_groups.WriteTo<uint64_t>(output_file_buff);

        //output_file_buff.WriteVector( m_effect_data.teselates_groups.teselate_flags);
        m_effect_data.teselates_groups.WriteTeselateFlagsTo(output_file_buff);
    }

    output_file_buff.WriteVector(m_effect_data.linked_min_max );
    output_file_buff.WriteValue(m_effect_data.all_teselate_zero_mask);
}


void EffectClass::WriteToE2160Format(BinFile& output_file_buff)
{

    output_file_buff.WriteValue(m_effect_data.particle_2D_switch);
    output_file_buff.WriteValue(m_effect_data.width);
    output_file_buff.WriteValue(m_effect_data.height);

    output_file_buff.WriteValue(m_effect_data.e2160_effect_scale);

    output_file_buff.WriteStringWithLen(m_effect_data.annotation);
}



void EffectClass::ReadFromParticleGenAndTwoWorldsFile(BinFile& buff)
{
    m_effect_data.annotation = buff.ReadStringWithNullTerminator();

    buff.ReadValue(m_effect_data.particle_2D_switch);
    buff.ReadValue(m_effect_data.width);
    buff.ReadValue(m_effect_data.height);

    buff.ReadValue(m_effect_data.start_time);
    buff.ReadValue(m_effect_data.time);
    buff.ReadValue(m_effect_data.loops);


    for (int i = 0; i < m_effect_data.scales_size; ++i)
    {
        buff.ReadArray(m_effect_data.scales[i].a, m_effect_data.scale_a_size);
        buff.ReadValue(m_effect_data.scales[i].b[0]);
    }


    float avg_of_scales = 0.0;
    for (int i = 0; i < m_effect_data.scales_size; ++i)
    {
        for (int j = 0; j < m_effect_data.scale_a_size; ++j)
        {
            avg_of_scales += m_effect_data.scales[i].a[j];
        }
    }

    avg_of_scales /= (m_effect_data.scales_size * m_effect_data.scale_a_size);
    m_effect_data.e2160_effect_scale = static_cast<uint32_t>(avg_of_scales);

    buff.ReadValue(m_effect_data.unknown_value_1);
    buff.ReadValue(m_effect_data.unknown_value_2);

     m_effect_data.curves_groups.ReadFrom(m_prt_file_version_info.number_of_iel_in_effect, buff);


    if (m_prt_file_version_info.particle_version == ParticleGlobals::particle_type_value::two_worlds_particle)
    {
        m_effect_data.teselates_groups.ReadFrom<uint64_t>(m_prt_file_version_info.number_of_iel_in_effect, buff, true);
    }
    else
    {
        m_effect_data.teselates_groups.ReadFrom<uint64_t>(m_prt_file_version_info.number_of_iel_in_effect, buff);


        m_effect_data.teselates_groups.ReadOnlyTeselateFlags(buff, m_prt_file_version_info.number_of_iel_in_effect);
    }

    for (uint32_t i = 0; i < m_prt_file_version_info.number_of_linked_min_max_in_effect; ++i)
    {
        uint32_t single_linked_min_max = 0;
        buff.ReadValue(single_linked_min_max);
        m_effect_data.linked_min_max.push_back(single_linked_min_max);
    }

    buff.ReadValue(m_effect_data.all_teselate_zero_mask);
}

void EffectClass::ReadFromE2160File(BinFile& buff)
{
    buff.ReadValue(m_effect_data.particle_2D_switch);
    buff.ReadValue(m_effect_data.width);
    buff.ReadValue(m_effect_data.height);

    buff.ReadValue(m_effect_data.e2160_effect_scale);

    for (int i = 0; i < m_effect_data.scales_size; ++i)
    {
        for (int j = 0; j < m_effect_data.scale_a_size; ++j)
        {
            m_effect_data.scales[i].a[j] = static_cast<float>(m_effect_data.e2160_effect_scale);
        }
    }

    m_effect_data.annotation = buff.ReadStringWithNullTerminator();
}


void EffectClass::ReadFrom(BinFile& buff)
{
    switch (m_prt_file_version_info.particle_version)
    {

        case ParticleGlobals::particle_type_value::particle_gen_particle:
        case ParticleGlobals::particle_type_value::two_worlds_particle:
            ReadFromParticleGenAndTwoWorldsFile(buff);
        break;

        case ParticleGlobals::particle_type_value::e2160_particle:
            ReadFromE2160File(buff);
        break;

        case ParticleGlobals::particle_type_value::dynamic_particle:
        case ParticleGlobals::particle_type_value::ks_particles_emiter:
        break;

        default: break;
    }

}


void EffectClass::ExportAsParticleGenAndTwoWorldsFormat(std::stringstream& output)
{
    TU::WriteOneValueToSs("Effect", "EF", output, Globals::one_quad);

    TU::WriteSingleStringToSs("{", output);

    TU::WriteOneValueToSs("particle2D", m_effect_data.particle_2D_switch, output);

    TU::WriteOneValueToSs("width", m_effect_data.width, output);

    TU::WriteOneValueToSs("height", m_effect_data.height, output);

    TU::WriteOneValueToSs("annotation", m_effect_data.annotation, output);

    TU::WriteOneValueToSs("startTime", m_effect_data.start_time, output);

    TU::WriteOneValueToSs("time", m_effect_data.time, output);

    TU::WriteOneValueToSs("loops", m_effect_data.loops, output);

    TwoTypeArray<float, EffectData::scale_a_size, uint32_t, EffectData::scale_b_size>::ExportArrayOfTwoTypeArrayToSs
        ("scales",
         m_effect_data.scales,
         m_effect_data.scales_size,
         Globals::two_quads,
         output,
         true);

    TU::WriteOneValueToSs("unknownValue1", m_effect_data.unknown_value_1, output);

    TU::WriteOneValueToSs("unknownValue2", m_effect_data.unknown_value_2, output);

    TU::WriteVectorToSs<uint32_t>("linkedMinMax", m_effect_data.linked_min_max, output);

    TU::WriteOneValueToSs("allTeselateZeroMask", m_effect_data.all_teselate_zero_mask, output);

    if (PgEffectStrings.size() < m_prt_file_version_info.number_of_iel_in_effect)
    {
        size_t delta = m_prt_file_version_info.number_of_iel_in_effect - PgEffectStrings.size();

        for (size_t j = 0; j < delta; ++j)
            PgEffectStrings.push_back("ExtraField" + to_string(j));
    }

    CurvesAndTeselatesUtils::ExportCurvesAndTeselatesToSs
        (m_effect_data.curves_groups, m_effect_data.teselates_groups, PgEffectStrings, output);

    TU::WriteSingleStringToSs("}", output);
}


void EffectClass::ExportAsE2160Format(stringstream& output) const
{
    TU::WriteOneValueToSs("Effect", "EF", output, Globals::one_quad);

    TU::WriteSingleStringToSs("{", output);

    TU::WriteOneValueToSs("particle2D", m_effect_data.particle_2D_switch, output);

    TU::WriteOneValueToSs("width", m_effect_data.width, output);

    TU::WriteOneValueToSs("height", m_effect_data.height, output);

    TU::WriteOneValueToSs("scale", m_effect_data.e2160_effect_scale, output);

    TU::WriteOneValueToSs("annotation", m_effect_data.annotation, output);

    TU::WriteSingleStringToSs("}", output);
}


void EffectClass::ExportTo(std::stringstream& output)
{
    switch (m_prt_file_version_info.particle_version)
    {
        case ParticleGlobals::particle_type_value::particle_gen_particle:
        case ParticleGlobals::particle_type_value::two_worlds_particle:
            ExportAsParticleGenAndTwoWorldsFormat(output);
        break;

        case ParticleGlobals::particle_type_value::e2160_particle:
            ExportAsE2160Format(output);
        break;

        case ParticleGlobals::particle_type_value::dynamic_particle:
        case ParticleGlobals::particle_type_value::ks_particles_emiter:
        break;

        default: break;
    }

}
