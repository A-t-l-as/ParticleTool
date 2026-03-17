#ifndef ALL_CURVES_GROUPS_HPP
#define ALL_CURVES_GROUPS_HPP

#include <unordered_map>
#include <vector>
#include "File/BinFile.hpp"
#include "../../ParticleGlobals.hpp"
#include "SingleCurvePoint.hpp"
#include "Utils/TxtUtils.hpp"

class AllCurvesGroups
{
public:

    inline void Resize(size_t size = 0)
    {
        curves.resize(size);
        curve_scalars.resize(size);
        curve_bonus_values.resize(size);
    }

    inline void ResizeOnlyCurveBonusValues(size_t size = 0)
    {
        curve_bonus_values.resize(size);
    }

    void ReadFrom
    (
        size_t number_of_iel,
        BinFile& buff,
        bool e2160_switch = false
    )
    {

        uint64_t curve_vector_size = 0;
        SingleCurvePoint single_curve_point = {};
        std::vector<SingleCurvePoint> single_curve_vector = {};
        float curve_scalar = 0.0;
        float bonus_value = 0.0;

        for (size_t i = 0; i < number_of_iel; ++i)
        {
            buff.ReadValue( curve_vector_size );

            for (uint64_t j = 0; j < curve_vector_size; ++j)
            {
                buff.ReadValue(single_curve_point.x);
                buff.ReadValue(single_curve_point.y);
                buff.ReadArray(single_curve_point.bonus_data, single_curve_point.bonus_data_size);

                single_curve_vector.push_back(single_curve_point);
            }

            this->curves.push_back(std::move(single_curve_vector));
            single_curve_vector.clear();

            buff.ReadValue(curve_scalar);
            this->curve_scalars.push_back(curve_scalar);

            if (e2160_switch == true)
            {
                buff.ReadValue( bonus_value );
                this->curve_bonus_values.push_back(bonus_value);
            }

        }

    }



    void WriteTo(BinFile& output_file_buff, bool e2160_switch = false)
    {
        size_t i = 0;

        for (const std::vector<SingleCurvePoint>& curve : this->curves)
        {
            uint64_t number_of_points = curve.size();

            output_file_buff.WriteValue( number_of_points );
            output_file_buff.WriteVector( curve );

            output_file_buff.WriteValue( this->curve_scalars[i] );

            if (e2160_switch == true)
            {
                output_file_buff.WriteValue( this->curve_bonus_values[i] );
            }

            ++i;
        }

    }

    void ParseFrom
    (
        const std::string& arg_line,
        int64_t& label_index,
        size_t& number_of_single_curve_points_checksum,
        std::unordered_map<std::string, int64_t>& mapped_labels,
        ParticleGlobals::curve_or_teselate_mode& mode
    )
    {
        ParseCurveHeader
        (
            arg_line,
            label_index,
            number_of_single_curve_points_checksum,
            mapped_labels,
            mode
        );

        ParseCurves
        (
            arg_line,
            label_index,
            number_of_single_curve_points_checksum,
            mode
        );
    }


    void ParseCurveHeader
    (
        const std::string& arg_line,
        int64_t& label_index,
        size_t& number_of_single_curve_points_checksum,
        std::unordered_map<std::string, int64_t>& mapped_labels,
        ParticleGlobals::curve_or_teselate_mode& mode
    )
    {

        if ( arg_line.starts_with(ParticleGlobals::curve_type_name_str_with_space) )
        {

            DEBUG_PRINT("ITS CURVE HEADER!\n");

            std::string help_str =
                arg_line.substr
                (
                    ParticleGlobals::curve_type_name_with_space_len,
                    arg_line.length() - ParticleGlobals::curve_type_name_with_space_len
                );


            std::istringstream iss(help_str);

            float curve_scalar = 0.0f;
            std::string curve_string;

            if (!(iss >> number_of_single_curve_points_checksum >> curve_scalar >> curve_string))
            {
                DEBUG_PRINT("ParseCurveHeader: failed to parse curve header line\n");
                return;
            }

            label_index = mapped_labels[curve_string];

            if (label_index >= 0)
            {
                this->curve_scalars[label_index] = curve_scalar;
                this->curve_bonus_values[label_index] = ParticleGlobals::example_curve_bonus_value;
            }

            mode = ParticleGlobals::curve_or_teselate_mode::curve;
        }


    }


    void ParseCurves
    (
        const std::string& arg_line,
        int64_t& label_index,
        size_t& number_of_single_curve_points_checksum,
        ParticleGlobals::curve_or_teselate_mode& mode
    )
    {

        if (!arg_line.starts_with(ParticleGlobals::curve_type_name_str_with_space) &&
            arg_line != "{" &&
            arg_line != "}" &&
            number_of_single_curve_points_checksum > 0 &&
            mode == ParticleGlobals::curve_or_teselate_mode::curve)
        {
            if (arg_line.find(".") != std::string::npos)
            {
                DEBUG_PRINT("AU::GetCurves\n");
                std::string curve_instruction = "crv " + arg_line;

                DEBUG_PRINT(curve_instruction.c_str(), Mess::endl);

                const int temporary_array_size = 5;
                float temporary_array[temporary_array_size] = { 0.0 };

                TU::GetArrayValues<float>(curve_instruction, "crv", "%f", temporary_array, temporary_array_size);

                SingleCurvePoint temporary_single_curve_point =
                {
                    temporary_array[0],
                    temporary_array[1],

                    {
                        temporary_array[2],
                        temporary_array[3],
                        temporary_array[4]
                    }

                };

                this->curves[label_index].push_back(temporary_single_curve_point);


                --number_of_single_curve_points_checksum;
            }
        }

        if (mode == ParticleGlobals::curve_or_teselate_mode::curve && number_of_single_curve_points_checksum == 0)
        {
            mode = ParticleGlobals::curve_or_teselate_mode::null;
        }

    }

    void CopyCurveToDestination(std::size_t destination, std::size_t source)
    {
        this->curves[destination] = this->curves[source];
        this->curve_bonus_values[destination] = this->curve_bonus_values[source];
        this->curve_scalars[destination] = this->curve_scalars[source];
    }

private:

    friend class CurvesAndTeselatesUtils;

    std::vector <std::vector<SingleCurvePoint> > curves = { };
    std::vector< float > curve_scalars = {};
    std::vector< float > curve_bonus_values = {};


};

#endif // !ALL_CURVES_GROUPS_HPP
