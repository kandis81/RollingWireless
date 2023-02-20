/*
 * Ant simaultaion.
 */

/* 
 * File:   Ant.h
 * Author: Istvan hajdu
 *
 * Created on 2023. február 20., 10:01
 */

#pragma once

#include "IParentAnimal.h"
#include "IAnimalGenes.h"

namespace Animals
{
    class Ant : public IParentAnimal, public IAnimalGenes
    {
        static const uint8_t DEFAULT_GENE_POOL_NUMBER = 20U;
        
        public:
        
            /*
             * Constructor.
             */
            Ant( const uint8_t aGenePoolNumber = DEFAULT_GENE_POOL_NUMBER );
            
            /*
             * Copies only the gene pool!
             */
            Ant( const Ant& aAnt );
            
            virtual ~Ant() {}
            
            static const std::string ToString(const Ant& aAnt);
            
        private: // Overrides of the IAnimalGenes interface
            /*
             * See at IAnimalGenes interface.
             */
            void ResetGene() const override;

            /*
             * See at IAnimalGenes interface.
             */
            const Gene GetCurrentGene() const override;
            
            /*
             * See at IAnimalGenes interface.
             */
            const Gene GetNextGene() const override;
            
            /*
             * See at IAnimalGenes interface.
             */
            size_t GetGeneCount() const override;


        private: // Overrides of the IParentAnimal interface
            /*
             * See at IParentAnimal interface.
             */
            const ParentAnimal GetNewBorn( const IParentAnimal& aPartner ) const override;
        
            /*
             * See at IParentAnimal interface.
             */
            const ParentAnimal GetNewBorn( ) const override;
            
        private:
            
            /*
             * Create newborn with specific gene pool.
             * Note: The newborn can change the one item in its genepool.
             */
            Ant( const GenePoolType& aGenePool );
            
            GenePoolType    mGenePool;
            mutable uint8_t mCurrentGeneIndex;
            mutable bool    mCurrentDirectionIsForward;
    };
    
    using AntColony = std::vector<Ant>;
}
