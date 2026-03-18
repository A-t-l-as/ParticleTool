#ifndef ALL_TESELATES_GROUPS_HPP
#define ALL_TESELATES_GROUPS_HPP

#include "File/BinFile.hpp"
#include "../../ParticleGlobals.hpp"
#include <unordered_map>
#include <vector>
#include <cstdint>

class AllTeselatesGroups
{
public:


    inline void Resize(size_t size = 0)
    {
        teselates.resize(size);
        iel_scalars.resize(size);
        teselate_flags.resize(size);
    }


    template<typename T>
    void ReadFrom
    (
        size_t number_of_iel,
        BinFile& buff,
        bool two_worlds_switch = false
    )
    {
        T teselate_vector_size = 0;
        std::vector<float> teselate_vector = {};
        float teselate = 0.0;
        uint32_t teselate_flag = 0;
        float iel_scalar = 0.0;

        for (size_t i = 0; i < number_of_iel; ++i)
        {

            buff.ReadValue(teselate_vector_size);

            for (T j = 0; j < teselate_vector_size; ++j)
            {
                buff.ReadValue(teselate);
                teselate_vector.push_back(teselate);
            }

            this->teselates.push_back(std::move(teselate_vector));
            teselate_vector.clear();

            if (two_worlds_switch == true)
            {
                bool temp_teselate_flag = 0;
                buff.ReadValue(temp_teselate_flag);

                teselate_flag = static_cast<uint32_t>(temp_teselate_flag);
                this->teselate_flags.push_back(teselate_flag);
            }

            buff.ReadValue(iel_scalar);
            this->iel_scalars.push_back(iel_scalar);

        }
    }

    template<typename T>
    void WriteTo(BinFile& buff, bool two_worlds_switch = false)
    {
        size_t i = 0;

        for (const std::vector<float>& teselate : this->teselates)
        {
            T number_of_points = static_cast<T>(teselate.size());
            buff.WriteValue(number_of_points);

            buff.WriteVector(teselate);

            if (two_worlds_switch == true)
            {
                bool single_teselate_flag = static_cast<bool>(this->teselate_flags[i]);
                buff.WriteValue(single_teselate_flag);
            }

            buff.WriteValue(this->iel_scalars[i]);

            ++i;
        }
    }

    inline void WriteTeselateFlagsTo(BinFile& buff)
    {
        buff.WriteVector(this->teselate_flags);
    }

    void ParseFrom
    (
        const std::string& arg_line,
        int64_t& label_index,
        size_t& number_of_single_teselate_points_checksum,
        std::unordered_map<std::string, int64_t>& mapped_labels,
        ParticleGlobals::ENCurveOrTeselateMode& mode
    )
    {
        ParseTeselateHeader(arg_line, label_index, number_of_single_teselate_points_checksum, mapped_labels, mode);
        ParseTeselates(arg_line, label_index, number_of_single_teselate_points_checksum, mode);
    }


    void ParseTeselateHeader
    (
        const std::string& arg_line,
        int64_t& label_index,
        size_t& number_of_single_teselate_points_checksum,
        std::unordered_map<std::string, int64_t>& mapped_labels,
        ParticleGlobals::ENCurveOrTeselateMode& mode
    )
    {

        if ( arg_line.starts_with(ParticleGlobals::teselate_type_name_str_with_space) )
        {

            uint32_t single_teselate_flag = 0;
            float teselate_scalar = 0.0f;
            std::string teselate_string;

            std::string help_str =
                arg_line.substr
                (
                    ParticleGlobals::teselate_type_name_len_with_space,
                    arg_line.length() - ParticleGlobals::teselate_type_name_len_with_space
                );

            std::istringstream iss(help_str);
            iss >> number_of_single_teselate_points_checksum
                >> single_teselate_flag
                >> teselate_scalar
                >> teselate_string;

            label_index = mapped_labels[teselate_string];

            if (label_index >= 0)
            {
                this->teselate_flags[label_index] = single_teselate_flag;
                this->iel_scalars[label_index] = teselate_scalar;
            }

            mode = ParticleGlobals::ENCurveOrTeselateMode::teselate;
        }


    }


    void ParseTeselates
    (
        const std::string& arg_line,
        int64_t& label_index,
        size_t& number_of_single_teselate_points_checksum,
        ParticleGlobals::ENCurveOrTeselateMode& mode
    )
    {
        if (!arg_line.starts_with(ParticleGlobals::teselate_type_name_str_with_space) &&
            arg_line != "{" &&
            arg_line != "}" &&
            number_of_single_teselate_points_checksum > 0 &&
            mode == ParticleGlobals::ENCurveOrTeselateMode::teselate)
        {
            if (arg_line.find(".") != std::string::npos)
            {
                this->teselates[label_index].push_back(stof(arg_line));

                --number_of_single_teselate_points_checksum;
            }
        }

        if (mode == ParticleGlobals::ENCurveOrTeselateMode::teselate && number_of_single_teselate_points_checksum == 0)
        {
            mode = ParticleGlobals::ENCurveOrTeselateMode::null;
        }

    }


    void ReadOnlyTeselateFlags(BinFile& buff, std::size_t how_much)
    {
        for (size_t i = 0; i < how_much; ++i)
        {
            uint32_t temp_teselate_flag = 0 ;
            buff.ReadValue(temp_teselate_flag);
            this->teselate_flags.push_back(temp_teselate_flag);
        }
    }


private:

    friend class CurvesAndTeselatesUtils;

    std::vector< std::vector<float> > teselates = {};
    std::vector<float> iel_scalars = {};
    std::vector<uint32_t> teselate_flags = {};


};


#endif // !ALL_TESELATES_GROUPS_HPP
