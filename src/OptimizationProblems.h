#pragma once

#include <vector>


namespace prob
{
   /** CtuRobots - http://community.topcoder.com/stat?c=problem_statement&pm=13595 */


   /**
    * JumpFurther
    * http://community.topcoder.com/stat?c=problem_statement&pm=12300
    */
   struct JumpFurther
   {
      static int furthest(int N, int badStep);
   };


   /**
    * TheConsecutiveIntegersDivOne
    * http://community.topcoder.com/stat?c=problem_statement&pm=13625
    */
   struct TheConsecutiveIntegersDivOne
   {
      static int find(std::vector<int> const& numbers, int k);
   };

   /**
    * JanuszTheBusinessman
    * http://community.topcoder.com/stat?c=problem_statement&pm=13603
    */
   struct JanuszTheBusinessman
   {
      static int minPromotions(std::vector<int> const& arrivals, std::vector<int> const& departures);
   };


   /**
    * TheKingsArmyDiv1
    * http://community.topcoder.com/stat?c=problem_statement&pm=13526
    */


   /**
    * BuildingTowersEasy
    * http://community.topcoder.com/stat?c=problem_statement&pm=13634
    */
   struct BuildingTowersEasy
   {
      static int maxHeight(int n, std::vector<int> const& restrictionIndices, std::vector<int> const& restrictions);
   };

   /**
    * BuildingRoutes
    * http://community.topcoder.com/stat?c=problem_statement&pm=13193
    */
   struct BuildingRoutes
   {
      static int build(std::vector<std::string> const& distances, int safeThreshold);
   };

   /**
    * ZooExchangeProgram
    * http://community.topcoder.com/stat?c=problem_statement&pm=13268
    */
   struct ZooExchangeProgram
   {
      static int minGroup(std::vector<int> const& labels, int lower, int upper);
   };


   /**
    * ShoppingSurveyDiv1
    * http://community.topcoder.com/stat?c=problem_statement&pm=13455
    */
   struct ShoppingSurveyDiv1
   {
      static int minValue(int customerCount, int bigShopperThreshold, std::vector<int> const& sellCounts);
   };

}
