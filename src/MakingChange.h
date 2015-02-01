#pragma once

#include <vector>


namespace prob
{
   /**
    * Find the minimum amount of coins needed to exchange the amount with the given coin values.
    * The coin values are strictly increasing and higher than 1 as we assume with have the coin 1 by default.
    */
   size_t makingChange(size_t amount, std::vector<size_t> const& coinValues);

   /** Tests */
   void makingChangeTests();
}
