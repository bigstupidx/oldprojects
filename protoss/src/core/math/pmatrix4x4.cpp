// pmatrix4x4.cpp
// 4x4 matrix math. The matrix is represented in column order as
// OpenGL
//
// Copyright 2012 by Hongwei Li. All rights reserved.
//
// Hongwei Li lihw81@gmail.com
//

#include "pmatrix4x4.h"

#include <PCore/pvector3.h>
#include <PCore/pmathutility.h>

#include <PSystem/pdebug.h>

#include <math.h>

pFloat32 * P_APIENTRY pMatrix4x4Identity(pFloat32* matrix)
{
    matrix[0] = 1;
    matrix[1] = 0;
    matrix[2] = 0;
    matrix[3] = 0;

    matrix[4] = 0;
    matrix[5] = 1;
    matrix[6] = 0;
    matrix[7] = 0;
    
    matrix[8]  = 0;
    matrix[9]  = 0;
    matrix[10] = 1;
    matrix[11] = 0;
    
    matrix[12] = 0;
    matrix[13] = 0;
    matrix[14] = 0;
    matrix[15] = 1;

    return matrix;
}

pFloat32 * P_APIENTRY pMatrix4x4SetTranslation(pFloat32 x, 
    pFloat32 y, 
    pFloat32 z, 
    pFloat32* out)
{
    out[12] = x;
    out[13] = y;
    out[14] = z;

    return out;
}

pFloat32 * P_APIENTRY pMatrix4x4SetCreateTranslation(pFloat32 x, 
    pFloat32 y, 
    pFloat32 z,
    pFloat32 *out)
{
    out[0] = 1;
    out[1] = 0;
    out[2] = 0;
    out[3] = 0;

    out[4] = 0;
    out[5] = 1;
    out[6] = 0;
    out[7] = 0;
    
    out[8]  = 0;
    out[9]  = 0;
    out[10] = 1;
    out[11] = 0;
    
    out[12] = x;
    out[13] = y;
    out[14] = z;
    out[15] = 1;

    return out;
}

pFloat32 * P_APIENTRY pMatrix4x4Multiply(const pFloat32 *a, const pFloat32 *b, pFloat32 *out)
{
    pFloat32 tempMatrix[16]; // out can be a or b.

    tempMatrix[0] = a[0] * b[0] + a[4] * b[1] + a[8] * b[2] + a[12] * b[3]; 
    tempMatrix[1] = a[1] * b[0] + a[5] * b[1] + a[9] * b[2] + a[13] * b[3]; 
    tempMatrix[2] = a[2] * b[0] + a[6] * b[1] + a[10] * b[2] + a[14] * b[3]; 
    tempMatrix[3] = a[3] * b[0] + a[7] * b[1] + a[11] * b[2] + a[15] * b[3]; 
    
    tempMatrix[4] = a[0] * b[4] + a[4] * b[5] + a[8] * b[6] + a[12] * b[7]; 
    tempMatrix[5] = a[1] * b[4] + a[5] * b[5] + a[9] * b[6] + a[13] * b[7]; 
    tempMatrix[6] = a[2] * b[4] + a[6] * b[5] + a[10] * b[6] + a[14] * b[7]; 
    tempMatrix[7] = a[3] * b[4] + a[7] * b[5] + a[11] * b[6] + a[15] * b[7]; 
    
    tempMatrix[8]  = a[0] * b[8] + a[4] * b[9] + a[8] * b[10] + a[12] * b[11]; 
    tempMatrix[9]  = a[1] * b[8] + a[5] * b[9] + a[9] * b[10] + a[13] * b[11]; 
    tempMatrix[10] = a[2] * b[8] + a[6] * b[9] + a[10] * b[10] + a[14] * b[11]; 
    tempMatrix[11] = a[3] * b[8] + a[7] * b[9] + a[11] * b[10] + a[15] * b[11]; 
    
    tempMatrix[12] = a[0] * b[12] + a[4] * b[13] + a[8] * b[14] + a[12] * b[15]; 
    tempMatrix[13] = a[1] * b[12] + a[5] * b[13] + a[9] * b[14] + a[13] * b[15]; 
    tempMatrix[14] = a[2] * b[12] + a[6] * b[13] + a[10] * b[14] + a[14] * b[15]; 
    tempMatrix[15] = a[3] * b[12] + a[7] * b[13] + a[11] * b[14] + a[15] * b[15]; 

    pMatrix4x4Copy(tempMatrix, out);

    return out;
}

pFloat32 * P_APIENTRY pMatrix4x4CreateRotationX(pFloat32 radians, pFloat32 *out)
{
    out[0] = 1.0f;
    out[1] = 0.0f;
    out[2] = 0.0f;
    out[3] = 0.0f;

    out[4] = 0.0f;
    out[5] = cosf(radians);
    out[6] = sinf(radians);
    out[7] = 0.0f;

    out[8] = 0.0f;
    out[9] = -sinf(radians);
    out[10] = cosf(radians);
    out[11] = 0.0f;

    out[12] = 0.0f;
    out[13] = 0.0f;
    out[14] = 0.0f;
    out[15] = 1.0f;

    return out;
}

pFloat32 * P_APIENTRY pMatrix4x4CreateRotationY(pFloat32 radians, pFloat32 *out)
{
    out[0] = cosf(radians);
    out[1] = 0.0f;
    out[2] = -sinf(radians);
    out[3] = 0.0f;

    out[4] = 0.0f;
    out[5] = 1.0f;
    out[6] = 0.0f;
    out[7] = 0.0f;

    out[8] = sinf(radians);
    out[9] = 0.0f;
    out[10] = cosf(radians);
    out[11] = 0.0f;

    out[12] = 0.0f;
    out[13] = 0.0f;
    out[14] = 0.0f;
    out[15] = 1.0f;

    return out;
}

pFloat32 * P_APIENTRY pMatrix4x4CreateRotationZ(pFloat32 radians, pFloat32 *out)
{
    out[0] = cosf(radians);
    out[1] = sinf(radians);
    out[2] = 0.0f;
    out[3] = 0.0f;

    out[4] = -sinf(radians);;
    out[5] = cosf(radians);
    out[6] = 0.0f;
    out[7] = 0.0f;

    out[8] = 0.0f;
    out[9] = 0.0f;
    out[10] = 1.0f;
    out[11] = 0.0f;

    out[12] = 0.0f;
    out[13] = 0.0f;
    out[14] = 0.0f;
    out[15] = 1.0f;

    return out;
}

// FIX ME! Optimize this function.
pFloat32 * P_APIENTRY pMatrix4x4LookAt(const pFloat32 *cameraPos, 
    const pFloat32 *lookAt, 
    const pFloat32 *upVector, 
    pFloat32 *out)
{
    pFloat32 fVec[3];
    pFloat32 upVec[3];
    pFloat32 sVec[3];
    pFloat32 uVec[3];
   
    pVector3Subtract(lookAt, cameraPos, fVec);
    pVector3Normalize(fVec, fVec);

    pVector3Normalize(upVector, upVec);

    pVector3Cross(fVec, upVec, sVec);
    pVector3Normalize(sVec, sVec);

    pVector3Cross(sVec, fVec, uVec);
    pVector3Normalize(sVec, sVec);

    out[0] = sVec[0];
    out[1] = uVec[0];
    out[2] = -fVec[0];
    out[3] = 0;
    out[4] = sVec[1];
    out[5] = uVec[1];
    out[6] = -fVec[1];
    out[7] = 0;
    out[8] = sVec[2];
    out[9] = uVec[2];
    out[10] = -fVec[2];
    out[11] = 0;
    out[12] = -cameraPos[0];
    out[13] = -cameraPos[1];
    out[14] = -cameraPos[2];
    out[15] = 1;

    return out;
}

pFloat32 * P_APIENTRY pMatrix4x4PerspectiveProjection(pFloat32 fovY, 
    pFloat32 aspect, 
    pFloat32 zNear, 
    pFloat32 zFar, 
    pFloat32 *out)
{
    pFloat32 r = pDegreesToRadians(fovY / 2);
    pFloat32 deltaZ = zFar - zNear;
    pFloat32 s = sinf(r);
    pFloat32 cotangent = 0;

    if (deltaZ == 0 || s == 0 || aspect == 0)
    {
        return P_NULL;
    }

    //cos(r) / sin(r) = cot(r)
    cotangent = cosf(r) / s;

    pMatrix4x4Identity(out);
    out[0] = cotangent / aspect;
    out[5] = cotangent;
    out[10] = -(zFar + zNear) / deltaZ;
    out[11] = -1;
    out[14] = -2.0f * zNear * zFar / deltaZ;
    out[15] = 0;

    return out;
}

pFloat32 * P_APIENTRY pMatrix4x4OrthographicProjection(pFloat32 left, 
    pFloat32 right, 
    pFloat32 bottom, 
    pFloat32 top, 
    pFloat32 nearVal, 
    pFloat32 farVal,
    pFloat32 *out)
{
    pFloat32 tx = -((right + left) / (right - left));
    pFloat32 ty = -((top + bottom) / (top - bottom));
    pFloat32 tz = -((farVal + nearVal) / (farVal - nearVal));

    pMatrix4x4Identity(out);
    out[0] = 2.0f / (right - left);
    out[5] = 2.0f / (top - bottom);
    out[10] = -2.0f / (farVal - nearVal);
    out[12] = tx;
    out[13] = ty;
    out[14] = tz;

    return out;
}
