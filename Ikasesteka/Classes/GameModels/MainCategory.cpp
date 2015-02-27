//
//  MainCategory.cpp
//  IkasGame
//
//  Created by Sergio Garcia on 25/2/15.
//
//

#include "MainCategory.h"


vector<SubCategory*> MainCategory::getFilteredSubCategoriesByLevel(Difficulty difficulty)
{
    int minLevel = (int)difficulty;
    return this->getFilteredSubCategoriesByLevel(minLevel);
}

/**
 * Returns actual level and previuos level subcategories
 */
vector<SubCategory*> MainCategory::getFilteredSubCategoriesByLevel(int level)
{
    vector<SubCategory*> filteredSubcategories;
    filteredSubcategories.clear();
    for (int x = 0; x<m_SubCategories.size(); x++) {
        if (m_SubCategories.at(x)->getMinLevel() == level
            || m_SubCategories.at(x)->getMinLevel() == level - 1) {
            filteredSubcategories.push_back(m_SubCategories.at(x));
        }
    }
    return filteredSubcategories;
}