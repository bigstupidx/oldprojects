// pvector3.cpp
// vector 3 functions.
//
// Copyright 2013 Cooee. All rights reserved.
//
// Jihao Xu xujihao@cooee.cn
//

#include "pvector3.h"

#include <math.h>



pFloat32 P_APIENTRY pVector3Length(const pFloat32* in)
{
    return sqrtf(in[0] * in[0] + in[1] * in[1] + in[2] * in[2]);
}

pFloat32 * P_APIENTRY pVector3Normalize(const pFloat32 *in, pFloat32 *out)
{
    pFloat32 length = 1.0f / pVector3Length(in);

    out[0] = in[0] * length;
    out[1] = in[1] * length;
    out[2] = in[2] * length;

    return out;
}

pFloat32 * P_APIENTRY pVector3Assign(const pFloat32 *in, pFloat32 *out)
{
    if(out == in)
    {
        return out;
    }

    out[0] = in[0];
    out[1] = in[1];
    out[2] = in[2];

    return out;
}

pFloat32 * P_APIENTRY pVector3Cross(const pFloat32 *v1, const pFloat32 *v2, pFloat32 *out)
{
    pFloat32 v[3];

    v[0] = (v1[1] * v2[2]) - (v1[2] * v2[1]);
    v[1] = (v1[2] * v2[0]) - (v1[0] * v2[2]);
    v[2] = (v1[0] * v2[1]) - (v1[1] * v2[0]);

    out[0] = v[0];
    out[1] = v[1];
    out[2] = v[2];

    return out;
}
