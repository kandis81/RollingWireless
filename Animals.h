/*
 * General animal functionalities.
 */

/* 
 * File:   Animals.h
 * Author: johnny
 *
 * Created on 2023. február 20., 12:33
 */

#pragma once

#include "IParentAnimal.h"

namespace Animals
{
    using NewBornColony = std::vector<ParentAnimal>;

    /*
     * Get the children of the parents.
     */
    extern const NewBornColony& GetNewBorns( const IParentAnimal& aParent1
                                           , const IParentAnimal& aParent2
                                           , NewBornColony& aChildren );
}
