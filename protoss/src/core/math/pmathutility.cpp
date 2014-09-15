// pmathutility.cpp 
// Some useful math function
//
// Copyright 2013 Cooee. All rights reserved.
//
// Jihao Xu xujihao@cooee.cn
//

#include "pmathutility.h"

pFloat32 P_APIENTRY pDegreesToRadians(pFloat32 degrees)
{
    return degrees * P_PIOVER180;
}
