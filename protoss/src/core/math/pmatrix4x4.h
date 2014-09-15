// pmatrix4x4.h 
// 4x4 matrix math used for 3D scaling, rotation and translation. The matrix is
// represented in column order as OpenGL
//
// Copyright 2013 Cooee. All rights reserved.
//
// Hongwei Li lihw81@gmail.com
//

#ifndef PMATRIX4X4_H
#define PMATRIX4X4_H

#include <PGlobal/pglobal.h>

// Set the matrix to be identity.
pFloat32 * P_APIENTRY pMatrix4x4Identity(pFloat32 *matrix);

// out = a * b (out can be either a or b)
pFloat32 * P_APIENTRY pMatrix4x4Multiply(const pFloat32 *a, const pFloat32 *b, pFloat32 *out);

// Create a translation matrix.
pFloat32 * P_APIENTRY pMatrix4x4CreateTranslation(pFloat32 x,
    pFloat32 y,
    pFloat32 z, 
    pFloat32 *out);

// Directly modify the translation of the matrix. 
pFloat32 * P_APIENTRY pMatrix4x4SetTranslation(pFloat32 x,
    pFloat32 y, 
    pFloat32 z, 
    pFloat32 *out);

// Create a rotation matrix that rotate with x axis.
pFloat32 * P_APIENTRY pMatrix4x4CreateRotationX(pFloat32 radians, pFloat32 *out);

// Create a rotation matrix that rotate with y axis.
pFloat32 * P_APIENTRY pMatrix4x4CreateRotationY(pFloat32 radians, pFloat32 *out);

// Create a rotation matrix that rotate with z axis.
pFloat32 * P_APIENTRY pMatrix4x4CreateRotationZ(pFloat32 radians, pFloat32 *out);

// Create a lookat matrix.
pFloat32 * P_APIENTRY pMatrix4x4LookAt(const pFloat32 *cameraPos, 
    const pFloat32 *lookAt, 
    const pFloat32 *upVector, 
    pFloat32 *out);

// Create a perspective projection matrix.
pFloat32 * P_APIENTRY pMatrix4x4PerspectiveProjection(pFloat32 fovY,
    pFloat32 aspect,
    pFloat32 zNear, 
    pFloat32 zFar, 
    pFloat32 *out);

// Create a orthographic projection matrix.
pFloat32 * P_APIENTRY pMatrix4x4OrthographicProjection(pFloat32 left,
    pFloat32 right, 
    pFloat32 bottom, 
    pFloat32 top, 
    pFloat32 nearVal,
    pFloat32 farVal,
    pFloat32 *out);

// Matrix copy
P_INLINE pFloat32 * P_APIENTRY pMatrix4x4Copy(const pFloat32 *in, pFloat32 *out)
{
    out[0] = in[0];
    out[1] = in[1];
    out[2] = in[2];
    out[3] = in[3];
    out[4] = in[4];
    out[5] = in[5];
    out[6] = in[6];
    out[7] = in[7];
    out[8] = in[8];
    out[9] = in[9];
    out[10] = in[10];
    out[11] = in[11];
    out[12] = in[12];
    out[13] = in[13];
    out[14] = in[14];
    out[15] = in[15];

    return out;
}

// TODO: C++ wrapper

#endif // !PMATRIX4X4_H
