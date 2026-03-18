#ifndef PARTICLE_GLOBALS_HPP
#define PARTICLE_GLOBALS_HPP

#include <cstdint>
#include <ios>

namespace ParticleGlobals
{

constexpr char my_aod_format_str[] = ".myaod";

constexpr std::size_t size_of_e2150_root_data_block = 0x364;                 // 868 (dec)

constexpr std::size_t size_of_ww3_or_heli_heroes_root_data_block = 0xAAC;    // 2732 (dec)

constexpr std::size_t size_of_ww2_or_fa_or_pc2_root_data_block = 0xCA4;      // 3236 (dec)

constexpr std::size_t size_of_ks_root_data_block = 0xFB4;                    // 4020 (dec)

constexpr char dynamic_name_str[] = "Dynamic";

constexpr char object_name_str_with_space[] = "Object ";

constexpr char time_name_str_with_space[] = "Time ";

constexpr std::size_t time_name_str_with_space_len =
    sizeof(ParticleGlobals::time_name_str_with_space) - 1;

constexpr char particles_emiter_name_str[] = "ParticlesEmiter";


constexpr char effect_type_name_str[] = "Effect";
constexpr char effect_type_name_str_with_space[] = "Effect ";

constexpr char emiter_type_name_str[] = "Emiter";
constexpr char emiter_type_name_str_with_space[] = "Emiter ";

constexpr char particle_type_name_str[] = "Particle";
constexpr char particle_type_name_str_with_space[] = "Particle ";

constexpr char pair_particle_type_name_str[] = "PairParticleEmiter";
constexpr char pair_particle_type_name_str_with_space[] = "PairParticleEmiter ";

constexpr char version_str_with_space[] = "version ";
constexpr std::size_t version_str_with_space_len = sizeof(ParticleGlobals::version_str_with_space) - 1;

constexpr char teselate_type_name_str_with_space[] = "teselate ";
constexpr std::size_t teselate_type_name_len_with_space = sizeof(ParticleGlobals::teselate_type_name_str_with_space) - 1;

constexpr char curve_type_name_str_with_space[] = "curve ";
constexpr std::size_t curve_type_name_with_space_len =  sizeof(ParticleGlobals::curve_type_name_str_with_space) - 1;;

constexpr float example_curve_bonus_value = 0.0;

constexpr uint32_t locked_linked_min_max = 1;
constexpr uint32_t unlocked_linked_min_max = 0;

constexpr int64_t initialize_signal_value = -1;
constexpr int64_t push_back_signal_value = 0;

constexpr int dec_base = 10;

constexpr char e2150_format_str[] = "e2150";
constexpr char ww3_or_hh_format_str[] = "ww3_or_hh";
constexpr char ww2_or_fa_or_pc2_format_str[] = "ww2_or_fa_or_pc2";
constexpr char ks_format_str[] = "ks";

constexpr char earth2160_format_str[] = "e2160";
constexpr char tw_format_str[] = "tw";
constexpr char pg_format_str[] = "pg";

constexpr char bonus_file_rest_name_str[] = "_extra_data.cpp";
constexpr char dynamic_particle_cfg_file_name_str[] = "DynamicParticle.cfg";


constexpr float e2160_standard_curve_scalar = 3.000000;
constexpr float e2160_standard_bonus_value = 0.0;
constexpr float ks_example_curve_scalar = 1.000000;

constexpr uint8_t tw_old_format_fourth_byte_of_header = 1;
constexpr uint8_t tw_new_format_fourth_byte_of_header = 2;

constexpr std::streamsize aod_float_precision = 17;

enum class ENParticleTypeValue
{
    not_particle,
    dynamic_particle,
    ks_particles_emiter,
    e2160_particle,
    two_worlds_particle,
    particle_gen_particle
};

static bool IsValidParticleTypeValue(int value)
{
    // Dostosuj zakres do rzeczywistych wartości enuma
    return value >= static_cast<int>(ParticleGlobals::ENParticleTypeValue::not_particle)
           && value <= static_cast<int>(ParticleGlobals::ENParticleTypeValue::particle_gen_particle);
}


enum class ENOldDynamicParticleTypeValue
{
    not_old_dynamic_particle,
    e2150_old_dynamic_particle,
    ww3_of_hh_old_dynamic_particle,
    ww2_or_fa_or_pc2_old_dynamic_particle,
    ks_old_dynamic_particle
};

enum class ENCurveOrTeselateMode
{
    null,
    curve,
    teselate
};

enum class ENAppModes
{
    m_invalid,
    m_export,
    m_import
};


};


#endif // !PARTICLE_GLOBALS_HPP
