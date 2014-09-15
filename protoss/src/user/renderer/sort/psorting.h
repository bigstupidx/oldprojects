// psorting.h
// The culling algorithm factory.
//
// Copyright 2013 Cooee. All rights reserved.
//
// Hongwei Li lihw81@gmail.com
//

#ifndef PSORTING_H
#define PSORTING_H

#include <PGlobal/pglobal.h>


enum PSortingAlgorithmEnum
{
    P_SORTING_NONE,
    P_SORTING_Z,

    P_SORTING_DEFAULT = P_SORTING_NONE,
    P_SORTING_ALGORITHM_FIRST = P_SORTING_NONE,
    P_SORTING_ALGORITHM_LAST = P_SORTING_Z,
    P_SORTING_ALGORITHM_NUMBER = P_SORTING_ALGORITHM_LAST - P_SORTING_ALGORITHM_FIRST + 1,
};


class P_DLLEXPORT PSorting
{
public:
    PSorting(PRenderPass* renderPass);
    ~PSorting();

    void setSorting(PSortingAlgorithmEnum sorting);
    PSortingAlgorithmEnum getSorting() const;

private:
    PRenderPass* m_renderPass;
};

#endif //! PSORTING_H
