#ifndef CFG_COMPILATOR_UTILS_HPP
#define CFG_COMPILATOR_UTILS_HPP


#include <cstddef>
namespace CfgCompilatorUtils
{
enum class ENCfgValueTypes
{
    dynamic_particle_input_format,
    force_specific_export_format,
    forced_export_format,
    invalid
};

constexpr size_t number_of_value_types = 3;
static const char* value_types[] = {
    "dynamic_particle_input_format",
    "force_specific_export_format",
    "forced_export_format"
};

constexpr std::size_t number_of_false_and_true_config_values_str = 3;
static const char* true_config_values_str[] =
{
        "1",
        "YES",
        "TRUE"
};

static const char* false_config_values_str[] =
{
        "0",
        "NO",
        "FALSE"
};



};




#endif // !CFG_COMPILATOR_UTILS_HPP
