/*
 * The life space of the animals
 */

/* 
 * File:   LifeSpace.h
 * Author: johnny
 *
 * Created on 2023. február 20., 13:35
 */

#pragma once

#include "IAnimalGenes.h"

#include <tuple>
#include <limits>

namespace World
{
    using Coordinate = std::tuple<int32_t, int32_t>;

    static constexpr size_t INVALID_FITNESS = std::numeric_limits<size_t>::max();

    /*
     * The life space of the animals.
     */
    class LifeSpace
    {
        public:
            LifeSpace( const Coordinate aFoodDistance );
            virtual ~LifeSpace() {}

            /*
             * It calculates the best closeness of the food.
             */
            const size_t GetFitness( const Animals::IAnimalGenes& aAnimal ) const;
            
        private:
            /*
             * Default constructor is ignored.
             */
            LifeSpace();

            /*
             * Copy constructor is ignored.
             */
            LifeSpace( LifeSpace& );

            const Coordinate mFood;
            const size_t     mMinGenCount;
    };
}
