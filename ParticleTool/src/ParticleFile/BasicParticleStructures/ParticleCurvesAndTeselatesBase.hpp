#ifndef PARTICLE_CURVES_AND_TESELATES_BASE_HPP
#define PARTICLE_CURVES_AND_TESELATES_BASE_HPP

#include <vector>
#include <cstdint>

#include "../../ParticleGlobals.hpp"
#include "../BasicParticleStructures/AllCurvesGroups.hpp"
#include "../BasicParticleStructures/AllTeselatesGroups.hpp"

class ParticleCurvesAndTeselatesBase
{
public:

    std::vector<uint32_t> linked_min_max = {};

    AllCurvesGroups curves_groups = {}; //ok
    AllTeselatesGroups teselates_groups = {}; //ok

    inline void InsertLinkedMinMax(std::size_t index, uint32_t value = ParticleGlobals::locked_linked_min_max)
    {
        this->linked_min_max.insert(linked_min_max.begin() + index, value);
    }

    inline void EraseLinkedMinMax(size_t index)
    {
        this->linked_min_max.erase(linked_min_max.begin() + index);
    }



    virtual void ConvertTeselatesAndCurves
        (ParticleGlobals::ENParticleTypeValue& src, ParticleGlobals::ENParticleTypeValue& dst) = 0;


    void ConvertTeselatesAndCurvesWholeFormat
        (ParticleGlobals::ENParticleTypeValue& src, ParticleGlobals::ENParticleTypeValue& dst)
    {
        ParticleGlobals::ENParticleTypeValue copy_of_src = src;
        ParticleGlobals::ENParticleTypeValue copy_of_dst;

        if (src > dst)
        {
            while (copy_of_src > dst)
            {
                int next_val = static_cast<int>(copy_of_src) - 1;

                if(!ParticleGlobals::IsValidParticleTypeValue(next_val)) break;

                copy_of_dst = static_cast<ParticleGlobals::ENParticleTypeValue>(next_val);

                this->ConvertTeselatesAndCurves(copy_of_src, copy_of_dst);

                copy_of_src = copy_of_dst;
            }

            return;
        }

        if (src == dst)
        {
            return;
        }

        if (src < dst)
        {
            while (copy_of_src < dst)
            {
                int next_val = static_cast<int>(copy_of_src) + 1;

                if(!ParticleGlobals::IsValidParticleTypeValue(next_val)) break;

                copy_of_dst = static_cast<ParticleGlobals::ENParticleTypeValue>(next_val);

                this->ConvertTeselatesAndCurves(copy_of_src, copy_of_dst);

                copy_of_src = copy_of_dst;
            }

            return;
        }

    }

};


#endif // !PARTICLE_CURVES_AND_TESELATES_BASE_HPP
