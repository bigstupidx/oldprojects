// pabstractculler.h
// The base class of all culling alogirthm.
//
// Copyright 2013 Cooee. All rights reserved.
//
// Hongwei Li lihw81@gmail.com
//

#ifndef PABSTRACTCULLER_H
#define PABSTRACTCULLER_H

#include <PGlobal/pglobal.h>


class PRenderPass;


class PAbstractCuller
{
public:
    PAbstractCuller(PRenderPass* renderPass);
    virtual ~PAbstractCuller();

    void cull();

private:
    PRenderPass* m_renderPass;
};

#endif // !PABSTRACTCULLER_H
