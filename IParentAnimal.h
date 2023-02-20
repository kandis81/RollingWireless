/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   IParentAnimal.h
 * Author: johnny
 *
 * Created on 2023. február 20., 12:22
 */

#pragma once

#include <memory>

namespace Animals
{
    class IParentAnimal;
    using ParentAnimal = std::shared_ptr<IParentAnimal>;
    
    class IParentAnimal
    {
        public:
            virtual ~IParentAnimal() {}
        
            /*
             * Create a child with mixed genes.
             */
            virtual const ParentAnimal GetNewBorn( const IParentAnimal& aPartner ) const = 0;
        
            /*
             * Create a child with more or less the same genes.
             * One gene difference max.
             */
            virtual const ParentAnimal GetNewBorn( ) const = 0;
    };
}
