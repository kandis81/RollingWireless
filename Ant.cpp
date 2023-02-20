/*
 * Ant simulation.
 */

#include "Ant.h"

#include <cstdlib>
#include <algorithm>
#include <stdexcept>

namespace Animals
{
    inline const Gene GetRandomGene()
    {
        return static_cast<Gene>( (std::rand() % VALID_GENE_COUNT) + 1U );
    }
    
    inline const uint8_t GetRandomIndex( const GenePoolType aGenePool )
    {
        return static_cast<uint8_t>( std::rand() % aGenePool.size() );
    }
    
    const std::string Ant::ToString(const Ant& aAnt)
    {
        std::string text = "Ant [";
        for ( auto gene : aAnt.mGenePool )
        {
            text += ( gene == Animals::Gene::LEFT  ? "L" :
                      gene == Animals::Gene::RIGHT ? "R" :
                      gene == Animals::Gene::UP    ? "U" : "D" );
        }
        return text + "]";
    }
    
    Ant::Ant( const uint8_t aGenePoolNumber )
        : mCurrentGeneIndex( 0U )
        , mCurrentDirectionIsForward( true )
    {
        for ( uint8_t index = 0; index < aGenePoolNumber; index++ )
        {
            mGenePool.push_back( GetRandomGene() );
        }
    }
    
    Ant::Ant( const Ant& aAnt )
    {
        std::copy(aAnt.mGenePool.cbegin(), aAnt.mGenePool.cend(), std::back_inserter(this->mGenePool) );

        // Copy of the current identifiers are ignored
        this->mCurrentGeneIndex          = 0U;
        this->mCurrentDirectionIsForward = true;
    }
    
    Ant::Ant(const GenePoolType& aGenePool)
        : mGenePool( aGenePool )
        , mCurrentGeneIndex( 0U )
        , mCurrentDirectionIsForward( true )
    {
        // The newborn sometimes changes only one gene.
        const bool changeGene = static_cast<bool>( std::rand()%2 );
        if (changeGene)
        {
            const uint8_t gene_index = GetRandomIndex( mGenePool );
            mGenePool[gene_index]    = GetRandomGene();
        }
    }

    void Ant::ResetGene() const
    {
        mCurrentGeneIndex          = 0U;
        mCurrentDirectionIsForward = true;
    }

    const Gene Ant::GetCurrentGene() const
    {
        return ( mCurrentGeneIndex != 0U || mCurrentDirectionIsForward )
                 ? mGenePool[mCurrentGeneIndex]
                 : Gene::END;
    }

    const Gene Ant::GetNextGene() const
    {
        mCurrentDirectionIsForward = (  mCurrentDirectionIsForward
                                     && mCurrentGeneIndex < mGenePool.size() );
        mCurrentGeneIndex         += ( mCurrentDirectionIsForward ?   1  :
                                       mCurrentGeneIndex > 0U     ? (-1) : 0);
        return GetCurrentGene();
    }
    
    const ParentAnimal Ant::GetNewBorn( const IParentAnimal& aPartner ) const
    {
        const Ant* ant = dynamic_cast<const Ant*>( &aPartner );
        if ( ant == nullptr )
        {
            throw std::runtime_error("Could not create newborn, due to the parent is not ant!");
        }
        
        if ( ant->mGenePool.size() != mGenePool.size())
        {
            throw std::runtime_error("Gene pool size missmatch. The current version is not adopted to this case!");
        }

        const uint8_t cut_index = GetRandomIndex(mGenePool);
        GenePoolType aNewBornGenePool;
        std::copy_n( ant->mGenePool.cbegin()
                   , cut_index
                   , std::back_inserter( aNewBornGenePool ) );
        std::copy_n( mGenePool.cbegin()
                   , ( mGenePool.size() - cut_index )
                   , std::back_inserter( aNewBornGenePool ) );
        
        ParentAnimal newBorn( new Ant( aNewBornGenePool ) );
        return newBorn;
    }
    
    const ParentAnimal Ant::GetNewBorn() const
    {
        ParentAnimal newBorn( new Ant( this->mGenePool ) );
        return newBorn;
    }
    
    size_t Ant::GetGeneCount() const
    {
        return mGenePool.size();
    }
    
}
