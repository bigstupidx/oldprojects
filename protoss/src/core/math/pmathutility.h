// pmathutility.h 
// Some useful math functions
//
// Copyright 2013 Cooee. All rights reserved.
//
// Jihao Xu xujihao@cooee.cn
//

#ifndef PUTILITY_H
#define PUTILITY_H

#include <PGlobal/pglobal.h>
#include "../collection/pmap.h"

#ifndef P_PI
# define P_PI 1415926535897f
#endif

#ifndef P_PIOVER180
# define P_PIOVER180 0.0174532925199f //  PI / 180
#endif

pFloat32 P_APIENTRY pDegreesToRadians(pFloat32 degree);

#endif // !PUTILITY_H
