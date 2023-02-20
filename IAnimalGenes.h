/*
 * The animal genes and its operations.
 */

/* 
 * File:   IAnimalGenes.h
 * Author: johnny
 *
 * Created on 2023. február 20., 12:51
 */

#pragma once

#include <memory>
#include <vector>

namespace Animals
{
    static const uint8_t VALID_GENE_COUNT = 4U;
    
    enum class Gene : uint8_t
    {
          END = 0
        , UP
        , DOWN
        , RIGHT
        , LEFT
    };
    using GenePoolType = std::vector<Gene>;
    
    class IAnimalGenes
    {
        public:
            virtual ~IAnimalGenes() {}
        
            /*
             * Resets the walkthrough of the gene pool.
             */
            virtual void ResetGene() const = 0;

            /*
             * Get the current gene. If it is the end of the genes, returns with Gene::END.
             */
            virtual const Gene GetCurrentGene() const = 0;
            
            /*
             * Get the next gene. If it is the end of the genes, returns with Gene::END.
             * If you want to run it again, you have to call ResetGene first.
             */
            virtual const Gene GetNextGene() const = 0;
            
            /*
             * Get the count of genes.
             */
            virtual size_t GetGeneCount() const = 0;
    };
}
