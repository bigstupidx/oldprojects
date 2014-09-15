// pculling.h
// The culling algorithm factory.
//
// Copyright 2013 Cooee. All rights reserved.
//
// Hongwei Li lihw81@gmail.com
//

#ifndef PCULLING_H
#define PCULLING_H

#include <PGlobal/pglobal.h>


enum PCullingAlgorithmEnum
{
    P_CULLING_NONE     = 0x00,
    P_CULLING_CCW      = 0x01,
    P_CULLING_CW       = 0x02,
    P_CULLING_CAMERA   = 0x04,

    P_CULLING_DEFAULT = P_CULLING_NONE,
};


class P_DLLEXPORT PCulling
{
public:
    PCulling(PRenderPass* renderPass);
    ~PCulling();

    void setCulling(pUint32 culling);

private:
    PRenderPass* m_renderPass;
};

#endif //! PCULLING_H
