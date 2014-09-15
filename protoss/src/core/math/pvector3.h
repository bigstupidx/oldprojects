// pvector3.h 
// vector3 fuctions
//
// Copyright 2013 Cooee. All rights reserved.
//
// Jihao Xu xujihao@cooee.cn
//


#ifndef PVECTOR3_H
#define PVECTOR3_H

#include <PGlobal/pglobal.h>

// Construct a vector3.
P_INLINE pFloat32 * P_APIENTRY pVector3Fill(pFloat32 x, pFloat32 y, pFloat32 z, pFloat32 *out)
{
    out[0] = x;
    out[1] = y;
    out[2] = z;

    return out;
}

// Returns the length of the vector
pFloat32 P_APIENTRY pVector3Length(const pFloat32 *in);

// Subtracts 2 vectors and returns the result 
P_INLINE pFloat32 *P_APIENTRY pVector3Subtract(const pFloat32 *v1, const pFloat32 *v2, pFloat32 *out)
{
    out[0] = v1[0] - v2[0];
    out[1] = v1[1] - v2[1];
    out[2] = v1[2] - v2[2];

    return out;
}

// Returns the vector passed in set to unit length 
pFloat32 * P_APIENTRY pVector3Normalize(const pFloat32 *in, pFloat32 *out); 

// Assigns in to out. Returns out. If in and out are the same
// then nothing happens but out is still returned
pFloat32 * P_APIENTRY pVector3Assign(const pFloat32 *in, pFloat32 *out);

// Returns a vector perpendicular to 2 other vectors
pFloat32 * P_APIENTRY pVector3Cross(const pFloat32 *v1, const pFloat32 *v2, pFloat32 *out); 


#endif // !PVECTOR3_H
