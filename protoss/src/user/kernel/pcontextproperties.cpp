// pcontextproperties.cpp
//
// Copyright 2013 Cooee. All rights reserved.
//
// Hongwei Li lihw81@gmail.com
//


#include "pcontextproperties.h"

PContextProperties::PContextProperties()
    : m_contextName("default")
{
    m_screenWidth  = 960;
    m_screenHeight = 540;

    m_rgba[0] = m_rgba[1] = m_rgba[2] = m_rgba[3] = 8;
    m_depth = 16;    
    m_stencil = 0;
    m_multisamples  = 1;
}

