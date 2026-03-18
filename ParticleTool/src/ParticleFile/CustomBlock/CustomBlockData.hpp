#ifndef CUSTOM_BLOCK_DATA_HPP
#define CUSTOM_BLOCK_DATA_HPP

#include <vector>
#include <cstdint>

#include "../../ParticleGlobals.hpp"
#include "../IntroHeader/MshCustomBlockVectors.hpp"

struct CustomBlockData
{
    constexpr const unsigned int static c_format_size = 4;
    uint8_t format[c_format_size] = { 0 };
    std::vector<uint32_t> data = {};


    void SetCustomBlockVersion( const ParticleGlobals::ENOldDynamicParticleTypeValue& src,
                                const ParticleGlobals::ENOldDynamicParticleTypeValue& dst,
                                bool& is_child)
    {
        if (src == dst)
        {
            return;
        }

        this->data.clear();

        if (is_child == false)
        {
            MshCustomBlockVectors::SetCustomBlockVersionForNotChild(this->data, dst);
            return;
        }


        if (is_child == true)
        {
            MshCustomBlockVectors::SetCustomBlockVersionForChild(this->data, dst);
            return;
        }

    }
};


#endif // !CUSTOM_BLOCK_DATA_HPP
