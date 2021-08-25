#include "classifiable.hpp"
#ifndef KNN_HPP
#define KNN_HPP
//An interface of a knn algorithm class.
class classifier {
    //returns a vector similar to unclassified, but with categories. the categories are calculated with KNN algorithm.
    virtual std::vector<classifiable*> getCategories(std::vector<classifiable*> classified, std::vector<classifiable*> unclassified, int k) = 0;
};
#endif