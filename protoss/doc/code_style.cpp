// code_style.cpp
// Hongwei Li (lihw81@gmail.com)
// Created at 2013/06/08
//
// <Description>


#include "code.h"

void aFunc(int a, 
    int b, 
    int c, 
    int d)
{
    if (false ||
        (someCondition1 && someCondition2) &&
        someCondition3 ||
        false)
    {
    }
    else if (otherCondition)
    {
    }
    else
    {
    }

    char c = getchar();
    while (c != EOF)
    {
        printf("%c", c);
        c = getchar();
    }

    switch ()
    {
        case 'a': 
            break;
        default:
            break;
    }

    std::vector<int> stlArray(10);
    for (int i = 0; i < 10; ++i)
    {
        stlArray[i] = i;
    }

    std::vector<int>::iterator it, ib = stlArray.begin(), 
        ie = stlArray.end();
    for (it = ib; it != ie; ++it)
    {
    }

    int i = 0;
    int b = ++i;
    int c = i++;

    do 
    {
    } 
    while ();

    int result = (a + b) * 2 + c + d;

}


class Iterator
{
public:
    // Prefix
    // ++i
    const Iterator& operator++(int);
    {
        // add 
        
        return *this;
    }

    // Postfix
    // i++
    const Iterator& operator++();
    {
        Iterator ret(*this);

        // add

        return ret;
    }

};
