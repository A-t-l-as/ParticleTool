#include "PairParticleEmiterClass.hpp"

#include "../../../AodCompilator/GlobalQueues.hpp"

#include "Utils/TxtUtils.hpp"

using namespace std;

uint32_t PairParticleEmiterClass::group_number = 0;



PairParticleEmiterClass::PairParticleEmiterClass(
                                                    const ParticleGlobals::ENAppModes& arg_app_mode,
                                                    ParticleFileVersionInfo arg_prt_file_version_info,
                                                    string arg_pair_particle_emiter_name
                                                ) :
    m_prt_file_version_info(arg_prt_file_version_info)
{
    if(arg_app_mode == ParticleGlobals::ENAppModes::m_import)
    {
        m_pair_particle_emiter_data.group_name = arg_pair_particle_emiter_name;
    }
}


void PairParticleEmiterClass::ParseFrom(string& arg_line, GlobalQueues& arg_queues)
{
    TU::GetSingleString(arg_line, "Emiter", m_pair_particle_emiter_data.emiter_name);

    TU::GetSingleStringFromQueue
        (arg_line, "annotation", m_pair_particle_emiter_data.annotation, arg_queues.m_annotations_q);

    TU::GetSingleString(arg_line, "Particle", m_pair_particle_emiter_data.particle_name);

    TU::GetOneValue<uint32_t>(arg_line, "EmiterIndex", m_pair_particle_emiter_data.emiter_index);

    TU::GetOneValue<uint32_t>(arg_line, "ParticleIndex", m_pair_particle_emiter_data.particle_index);

    TU::GetOneValue<float>(arg_line, "time", m_pair_particle_emiter_data.time);

    TU::GetOneValue<uint32_t>(arg_line, "simpleOneParticleSwitch", m_pair_particle_emiter_data.simple_one_particle_switch);

    TU::GetOneValue<uint32_t>(arg_line, "2Dmask", m_pair_particle_emiter_data.mask_2d_switch);

    TU::GetOneValue<uint32_t>(arg_line, "hardwareCursor", m_pair_particle_emiter_data.hardware_cursor_switch);

    TU::GetOneValue<uint32_t>(arg_line, "stopInPartialPause", m_pair_particle_emiter_data.stop_in_partial_pause_switch);

    TU::GetOneValue<uint32_t>(arg_line, "finishMissile", m_pair_particle_emiter_data.finish_missile_switch);

    TU::GetOneValue<uint32_t>(arg_line, "emitsGroupsSwitch", m_pair_particle_emiter_data.emits_groups_switch);

    TU::GetOneValue<uint32_t>(arg_line,
                              "onlyEmitedByOtherEmiterSwitch", 
                              m_pair_particle_emiter_data.only_emited_by_other_emiter_switch);

    TU::GetOneValue<uint32_t>(arg_line, "drawParticleEmiter", m_pair_particle_emiter_data.draw_particle_emiter);

    TU::GetVectorOfStringsFromQueue
        (arg_line, "emitsGroups", m_pair_particle_emiter_data.emits_groups, arg_queues.m_emits_groups_q);


    m_pair_particle_emiter_data.looped_emission.ParseFrom( arg_line, "loopedEmission", "%d", "%f");

}


void PairParticleEmiterClass::WriteTo(BinFile& output_file_buff)
{
    switch (m_prt_file_version_info.particle_version)
    {
        case ParticleGlobals::ENParticleTypeValue::ks_particles_emiter:
            WriteToKsFormat(output_file_buff);
        break;

        case ParticleGlobals::ENParticleTypeValue::dynamic_particle:
        break;

        case ParticleGlobals::ENParticleTypeValue::e2160_particle:
        case ParticleGlobals::ENParticleTypeValue::particle_gen_particle:
        case ParticleGlobals::ENParticleTypeValue::two_worlds_particle:
            WriteToPgAndTwAndE2160Format(output_file_buff);
        break;

        default: break;
    }
}

void PairParticleEmiterClass::WriteToPgAndTwAndE2160Format(BinFile& output_file_buff)
{
    output_file_buff.WriteStringWithLen(m_pair_particle_emiter_data.group_name);

    output_file_buff.WriteStringWithLen(m_pair_particle_emiter_data.annotation);

    output_file_buff.WriteStringWithLen(m_pair_particle_emiter_data.emiter_name);

    output_file_buff.WriteStringWithLen(m_pair_particle_emiter_data.particle_name);

    output_file_buff.WriteValue(m_pair_particle_emiter_data.emiter_index);

    output_file_buff.WriteValue(m_pair_particle_emiter_data.particle_index);

    output_file_buff.WriteValue(m_pair_particle_emiter_data.time);

    output_file_buff.WriteValue(m_pair_particle_emiter_data.looped_emission.a[0]);

    output_file_buff.WriteValue(m_pair_particle_emiter_data.looped_emission.a[1]);

    output_file_buff.WriteValue(m_pair_particle_emiter_data.looped_emission.b[0]);

    output_file_buff.WriteValue(m_pair_particle_emiter_data.looped_emission.a[2]);

    output_file_buff.WriteValue(m_pair_particle_emiter_data.simple_one_particle_switch);

    output_file_buff.WriteValue(m_pair_particle_emiter_data.mask_2d_switch);

    output_file_buff.WriteValue(m_pair_particle_emiter_data.hardware_cursor_switch);

    output_file_buff.WriteValue(m_pair_particle_emiter_data.stop_in_partial_pause_switch);

    output_file_buff.WriteValue(m_pair_particle_emiter_data.finish_missile_switch);

    output_file_buff.WriteValue(m_pair_particle_emiter_data.emits_groups_switch);

    output_file_buff.WriteVectorOfStringsWithLen(m_pair_particle_emiter_data.emits_groups);

    output_file_buff.WriteValue(m_pair_particle_emiter_data.only_emited_by_other_emiter_switch);

    output_file_buff.WriteValue(m_pair_particle_emiter_data.draw_particle_emiter);

}



void PairParticleEmiterClass::WriteToKsFormat(BinFile& output_file_buff)
{

    output_file_buff.WriteValue(m_pair_particle_emiter_data.emiter_index);

    output_file_buff.WriteValue(m_pair_particle_emiter_data.particle_index);

    output_file_buff.WriteValue(m_pair_particle_emiter_data.time);

    output_file_buff.WriteValue(m_pair_particle_emiter_data.looped_emission.a[0]);

    output_file_buff.WriteValue(m_pair_particle_emiter_data.looped_emission.a[1]);

    output_file_buff.WriteValue(m_pair_particle_emiter_data.looped_emission.b[0]);

    output_file_buff.WriteValue(m_pair_particle_emiter_data.looped_emission.a[2]);

}



void PairParticleEmiterClass::ReadFromKsFile(BinFile& buff)
{
    ++group_number;

    m_pair_particle_emiter_data.group_name = "G" + to_string(group_number);

    m_pair_particle_emiter_data.emiter_name = "E" + to_string(group_number);

    m_pair_particle_emiter_data.particle_name = "P" + to_string(group_number);


    buff.ReadValue(m_pair_particle_emiter_data.emiter_index);

    buff.ReadValue(m_pair_particle_emiter_data.particle_index);

    buff.ReadValue(m_pair_particle_emiter_data.time);

    buff.ReadValue(m_pair_particle_emiter_data.looped_emission.a[0]);
    buff.ReadValue(m_pair_particle_emiter_data.looped_emission.a[1]);
    buff.ReadValue(m_pair_particle_emiter_data.looped_emission.b[0]);
    buff.ReadValue(m_pair_particle_emiter_data.looped_emission.a[2]);

    m_pair_particle_emiter_data.draw_particle_emiter = 1;
}


void PairParticleEmiterClass::ReadFromPgAndTwAndE2160File(BinFile& buff)
{
    m_pair_particle_emiter_data.group_name = buff.ReadStringWithNullTerminator();

    m_pair_particle_emiter_data.annotation = buff.ReadStringWithNullTerminator();

    m_pair_particle_emiter_data.emiter_name = buff.ReadStringWithNullTerminator();
    m_pair_particle_emiter_data.particle_name = buff.ReadStringWithNullTerminator();

    buff.ReadValue(m_pair_particle_emiter_data.emiter_index);
    buff.ReadValue(m_pair_particle_emiter_data.particle_index);

    buff.ReadValue(m_pair_particle_emiter_data.time);

    buff.ReadValue(m_pair_particle_emiter_data.looped_emission.a[0]);
    buff.ReadValue(m_pair_particle_emiter_data.looped_emission.a[1]);
    buff.ReadValue(m_pair_particle_emiter_data.looped_emission.b[0]);
    buff.ReadValue(m_pair_particle_emiter_data.looped_emission.a[2]);

    buff.ReadValue(m_pair_particle_emiter_data.simple_one_particle_switch);
    buff.ReadValue(m_pair_particle_emiter_data.mask_2d_switch);
    buff.ReadValue(m_pair_particle_emiter_data.hardware_cursor_switch);
    buff.ReadValue(m_pair_particle_emiter_data.stop_in_partial_pause_switch);
    buff.ReadValue(m_pair_particle_emiter_data.finish_missile_switch);

    buff.ReadValue(m_pair_particle_emiter_data.emits_groups_switch);


    uint64_t size_of_emits_groups_data;
    buff.ReadValue(size_of_emits_groups_data);

    for (uint64_t i = 0; i < size_of_emits_groups_data; ++i)
    {
        m_pair_particle_emiter_data.emits_groups.push_back(  buff.ReadStringWithNullTerminator()   );
    }

    buff.ReadValue(m_pair_particle_emiter_data.only_emited_by_other_emiter_switch);

    buff.ReadValue(m_pair_particle_emiter_data.draw_particle_emiter);

}


void PairParticleEmiterClass::ReadFrom(BinFile& buff)
{
    switch(m_prt_file_version_info.particle_version)
    {
        case ParticleGlobals::ENParticleTypeValue::ks_particles_emiter:
            ReadFromKsFile(buff);
        break;

        case ParticleGlobals::ENParticleTypeValue::dynamic_particle:
        break;


        case ParticleGlobals::ENParticleTypeValue::e2160_particle:
        case ParticleGlobals::ENParticleTypeValue::particle_gen_particle:
        case ParticleGlobals::ENParticleTypeValue::two_worlds_particle:
            ReadFromPgAndTwAndE2160File(buff);
        break;

        default: break;
    }

}


void PairParticleEmiterClass::ExportAsKsFormat(std::stringstream& output)
{
    TU::WriteOneValueToSs("PairParticleEmiter", m_pair_particle_emiter_data.group_name, output, Globals::one_quad);

    TU::WriteSingleStringToSs("{", output);

    TU::WriteOneValueToSs("Emiter", m_pair_particle_emiter_data.emiter_name, output);

    TU::WriteOneValueToSs("EmiterIndex", m_pair_particle_emiter_data.emiter_index, output);

    TU::WriteOneValueToSs("Particle", m_pair_particle_emiter_data.particle_name, output);

    TU::WriteOneValueToSs("ParticleIndex", m_pair_particle_emiter_data.particle_index, output);

    TU::WriteOneValueToSs("time", m_pair_particle_emiter_data.time, output);

    m_pair_particle_emiter_data.looped_emission.ExportToSs("loopedEmission", output);

    TU::WriteOneValueToSs("drawParticleEmiter", m_pair_particle_emiter_data.draw_particle_emiter, output);

    TU::WriteSingleStringToSs("}", output);
}


void PairParticleEmiterClass::ExportAsPgAndTwAndE2160Format(std::stringstream& output)
{
    TU::WriteOneValueToSs("PairParticleEmiter", m_pair_particle_emiter_data.group_name, output, Globals::one_quad);

    TU::WriteSingleStringToSs("{", output);

    TU::WriteOneValueToSs("Emiter", m_pair_particle_emiter_data.emiter_name, output);

    TU::WriteOneValueToSs("EmiterIndex", m_pair_particle_emiter_data.emiter_index, output);

    TU::WriteOneValueToSs("Particle", m_pair_particle_emiter_data.particle_name, output);

    TU::WriteOneValueToSs("ParticleIndex", m_pair_particle_emiter_data.particle_index, output);

    TU::WriteOneValueToSs("annotation", m_pair_particle_emiter_data.annotation, output);

    TU::WriteOneValueToSs("time", m_pair_particle_emiter_data.time, output);

    m_pair_particle_emiter_data.looped_emission.ExportToSs("loopedEmission", output);

    TU::WriteOneValueToSs("drawParticleEmiter", m_pair_particle_emiter_data.draw_particle_emiter, output);

    TU::WriteOneValueToSs("simpleOneParticleSwitch", m_pair_particle_emiter_data.simple_one_particle_switch, output);

    TU::WriteOneValueToSs("2Dmask", m_pair_particle_emiter_data.mask_2d_switch, output);

    TU::WriteOneValueToSs("hardwareCursor", m_pair_particle_emiter_data.hardware_cursor_switch, output);

    TU::WriteOneValueToSs("stopInPartialPause", m_pair_particle_emiter_data.stop_in_partial_pause_switch, output);

    TU::WriteOneValueToSs("finishMissile", m_pair_particle_emiter_data.finish_missile_switch, output);

    TU::WriteOneValueToSs("emitsGroupsSwitch", m_pair_particle_emiter_data.emits_groups_switch, output);

    TU::WriteVectorToSs<string>("emitsGroups", m_pair_particle_emiter_data.emits_groups, output);

    TU::WriteOneValueToSs("onlyEmitedByOtherEmiterSwitch", m_pair_particle_emiter_data.only_emited_by_other_emiter_switch, output);

    TU::WriteSingleStringToSs("}", output);
}


void PairParticleEmiterClass::ExportTo(std::stringstream& output)
{
    switch (m_prt_file_version_info.particle_version)
    {
        case ParticleGlobals::ENParticleTypeValue::ks_particles_emiter:
            ExportAsKsFormat(output);
        break;

        case ParticleGlobals::ENParticleTypeValue::dynamic_particle:
        break;


        case ParticleGlobals::ENParticleTypeValue::e2160_particle:
        case ParticleGlobals::ENParticleTypeValue::particle_gen_particle:
        case ParticleGlobals::ENParticleTypeValue::two_worlds_particle:
            ExportAsPgAndTwAndE2160Format(output);
        break;

        default: break;
    }

}







