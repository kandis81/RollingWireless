/*
 * The main file.
 */

/* 
 * File:   main.cpp
 * Author: johnny
 *
 * Created on 2023. február 20., 13:11
 */

#include "Ant.h"
#include "LifeSpace.h"
#include "Animals.h"

#include <iostream>
#include <algorithm>
#include <string>

static const size_t            POPULATION    = 100U;
static const World::Coordinate FOOD_LOCATION = { 10, 10 };
static const size_t            PARENTS_COUNT = 50U;

struct AntData
{
    Animals::Ant   mAnt;
    mutable size_t mFitness;
};

using Ants = std::vector<AntData>;

void RenewColony( Ants& aColony )
{
    Ants parents;
    std::copy_n(aColony.cbegin(), PARENTS_COUNT, std::back_inserter(parents));
    
    Animals::NewBornColony newBorns;
    constexpr size_t COUNT_OF_COUPLES = (PARENTS_COUNT / 2U);
    for (size_t index = 0; index < COUNT_OF_COUPLES; index++ )
    {
        Animals::Ant& parent1 = parents[index].mAnt;
        Animals::Ant& parent2 = parents[index + COUNT_OF_COUPLES].mAnt;
        Animals::GetNewBorns( parent1, parent2, newBorns );
        size_t newBornIndex = index * 4U;
        for ( auto newBorn : newBorns )
        {
            Animals::Ant* antChild = dynamic_cast<Animals::Ant*>(newBorn.get());
            if (antChild == nullptr)
            {
                throw std::runtime_error("Invalid newborn type!");
            }
            
            aColony[newBornIndex++] = AntData( { *antChild, 0U } );
        }
    }
}

const std::string ToString( const Ants aAnts )
{
    std::string test = "Fitnesses [";
    bool isFirst = true;
    for ( auto ant : aAnts )
    {
        if (!isFirst)
        {
            test += ",";
        }
        isFirst = false;
        test += std::to_string(ant.mFitness);
    }
    return test + "]";
}

bool FindPerfectAnt( const World::LifeSpace& aLifeSpace, const Ants& aColony )
{
    for ( const AntData& data : aColony )
    {
        data.mFitness = aLifeSpace.GetFitness( data.mAnt );
        if ( data.mFitness == 0U )
        {
            std::cout << "F:" << std::to_string(data.mFitness) << " " << Animals::Ant::ToString(data.mAnt) << std::endl;
            // The best is found
            return true;
        }
    }
    
    return false;
}

void printHelp( const std::string aBinName )
{
    std::cout << "Usage:" << std::endl;
    std::cout << "\t" << aBinName << " <count of generations>" << std::endl << std::endl;
    std::cout << "Example:" << std::endl;
    std::cout << "\t" << aBinName << " 100" << std::endl;
}

int main(int argc, char** argv)
{
    int32_t generationLimit = 100;
    if (argc < 2)
    {
        std::cout << "Missing argument!" << std::endl;
        printHelp(argv[0]);
        exit(-1);
    }

    try
    {
        generationLimit = std::stoi( argv[1] );
        if (generationLimit <= 0)
        {
            throw std::invalid_argument("Invalid generation value");
        }
    }
    catch (std::exception const& e)
    {
        std::cout << "Invalid argument: " << argv[1] << std::endl;
        std::cout << "Exception: " << e.what() << std::endl;
        printHelp(argv[0]);
        exit(-1);
    }

    try {
        Ants             colony(POPULATION);
        World::LifeSpace lifeSpace( FOOD_LOCATION );

        for ( int32_t index = 0; index < generationLimit; index++ )
        {
            std::cout << "Iteration nr.: " << index << std::endl;
            const bool found = FindPerfectAnt( lifeSpace , colony );
            if (found)
            {
                std::cout << "Best and found!" << std::endl;
                break;
            }

            std::sort( colony.begin(), colony.end(), []( AntData& aAnt1, AntData& aAnt2 ){
                return aAnt1.mFitness < aAnt2.mFitness;
            });
            std::cout << ToString( colony ) << std::endl;
            
            if ( colony[0].mFitness == World::INVALID_FITNESS )
            {
                throw std::runtime_error("No ant can reach the food!");
            }
            
            if ((index + 1) == generationLimit )
            {
                throw std::runtime_error("Cound not found the best ant!");
            }

            RenewColony( colony );
        }
    }
    catch (std::exception const& e)
    {
        std::cout << "Error: " << e.what() << std::endl;
    }
    
    return 0;
}

