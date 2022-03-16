#ifndef __RECIPE_HPP_
#define __RECIPE_HPP_

#include <iostream>
#include <string>

using namespace std;

template <class T>

class Recipe
{
private:
    T* pattern;
    T result;
    int quantity;

public:
    // 4 Sekawan
    Recipe();
    Recipe(pattern, result, quantity);
    // Recipe(const Recipe& other);
    ~Recipe();
    // Item &operator=( const Item &other);

    // Getter
    T* getPattern() const;
    T getResult() const;
    int getQuantity() const;

    // Setter
    void setPattern(pattern);
    void setResult(result);
    void setQuantity(quantity);

    void printInfo();
};

#endif
