// pcontextproperties.h
// The properties of a context.
//
// Copyright 2013 by Hongwei Li. All rights reserved.
//
// Hongwei Li lihw81@gmail.com
//

#ifndef KW_CONTEXT_PROPERTIES_H
#define KW_CONTEXT_PROPERTIES_H

#include <PCore/pstring.h>

struct PContextProperties 
{
    // Default constructor.
    PContextProperties();

    PString m_contextName; // Default value is "kiwi"

    pUint32 m_screenWidth; // Default value is 960. Only effective in PC platform.
    pUint32 m_screenHeight; // Default value is 540.

    pInt32  m_rgba[4];    // the number of bits per color channel; the default values are all 8.
    pInt32  m_depth;      // the number of bits of depth buffer; the default value is 16.
    pInt32  m_stencil;    // the number of bits of stencil buffer; the default value is 0.
    
    pUint32 m_multisamples; // the number of subpixels; the default value is 1 (no multisampling).
};


#endif // !KW_CONTEXT_PROPERTIES_H
