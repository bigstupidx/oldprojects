// pabstractsorter.h
// The base class of all sorting alogirthm.
//
// Copyright 2013 Cooee. All rights reserved.
//
// Hongwei Li lihw81@gmail.com
//

#ifndef PABSTRACTSORTER_H
#define PABSTRACTSORTER_H

#include <PGlobal/pglobal.h>


class PRenderPass;


class PAbstractSorter
{
public:
    PAbstractSorter(PRenderPass* renderPass);
    virtual ~PAbstractSorter();

    void sort();

private:
    PRenderPass* m_renderPass;
};

#endif // !PABSTRACTSORTER_H
