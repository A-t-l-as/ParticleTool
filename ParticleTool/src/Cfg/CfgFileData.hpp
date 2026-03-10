#ifndef CFG_FILE_DATA_HPP
#define CFG_FILE_DATA_HPP

#include "../ParticleFile/ParticleFileVersionInfo.hpp"
#include "../ParticleFile/ParticleFileVersionConsts.hpp"

struct CfgFileData
{
    ParticleFileVersionInfo input_dynamic_particle_file_version_info =
        ParticleFileVersionConsts::ks_dynamic_file_type;

    bool force_dynamic_particle_export_format_switch = false;

    ParticleFileVersionInfo forced_dynamic_particle_file_version_info_for_export =
        ParticleFileVersionConsts::ks_dynamic_file_type;
};

#endif // !CFG_FILE_DATA_HPP
