/*
 * General animal functionalities.
 */

#include <vector>

#include "Animals.h"

namespace Animals
{
    const NewBornColony& GetNewBorns( const IParentAnimal& aParent1
                                    , const IParentAnimal& aParent2
                                    , NewBornColony& aChildren )
    {
        aChildren.resize( 4U );
        aChildren[0] = aParent1.GetNewBorn();
        aChildren[1] = aParent2.GetNewBorn();
        aChildren[2] = aParent1.GetNewBorn( aParent2 );
        aChildren[3] = aParent2.GetNewBorn( aParent1 );
        return aChildren;
    }
}
