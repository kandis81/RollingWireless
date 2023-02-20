/*
 * The life space of the animals
 */

#include "LifeSpace.h"

#include <cstdlib>
#include <stdexcept>
#include <cmath>

namespace World
{
    LifeSpace::LifeSpace( const Coordinate aFoodDistance )
            : mFood( aFoodDistance )
            , mMinGenCount( static_cast<size_t>(std::min( std::abs(std::get<0>(mFood)), std::abs(std::get<1>(mFood)) ) ) )
    {}
    
    const size_t LifeSpace::GetFitness( const Animals::IAnimalGenes& aAnimal ) const
    {
        if ( aAnimal.GetGeneCount() < mMinGenCount )
        {
            return INVALID_FITNESS;
        }

        aAnimal.ResetGene();
        Coordinate    currentCoordinate = { 0, 0 };
        Animals::Gene currentGene       = aAnimal.GetCurrentGene();
        size_t        bestFitness       = INVALID_FITNESS;
        while ( currentGene != Animals::Gene::END )
        {
            // update the coordinate
            switch ( static_cast<int>(currentGene) )
            {
                case static_cast<int>(Animals::Gene::LEFT) :
                    currentCoordinate = { (std::get<0>(currentCoordinate) - 1), std::get<1>(currentCoordinate) };
                    break;
                case static_cast<int>(Animals::Gene::RIGHT) :
                    currentCoordinate = { (std::get<0>(currentCoordinate) + 1), std::get<1>(currentCoordinate) };
                    break;
                case static_cast<int>(Animals::Gene::UP) :
                    currentCoordinate = { std::get<0>(currentCoordinate), (std::get<1>(currentCoordinate) + 1) };
                    break;
                case static_cast<int>(Animals::Gene::DOWN) :
                    currentCoordinate = { std::get<0>(currentCoordinate), (std::get<1>(currentCoordinate) - 1) };
                    break;
            }
            
            if ( currentGene == Animals::Gene::END )
            {
                break;
            }
            
            {// calc the fitness
                const size_t fitness = std::abs( std::get<0>(mFood) - std::get<0>(currentCoordinate) )
                                     + std::abs( std::get<1>(mFood) - std::get<1>(currentCoordinate) );
                bestFitness          = (fitness < bestFitness ? fitness : bestFitness);
            }
            
            if ( bestFitness == 0 )
            {
                // Food is found by animal
                break;
            }

            currentGene = aAnimal.GetNextGene();
        }
        
        return bestFitness;
    }
}
