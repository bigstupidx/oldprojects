// pcamera.cpp
// The rendering state
//
// Copyright 2013 Cooee. All rights reserved.
//
// Jihao Xu xujihao@cooee.cn
//

#include "pcamera.h"

#include <PCore/pmatrix4x4.h>
#include <PCore/pvector3.h>

#include <PSystem/passert.h>

PCamera::PCamera(PRenderPass *renderPass)
{
    pMatrix4x4Identity(m_cameraMatrix);
    pMatrix4x4Identity(m_projectionMatrix);
    m_renderPass = renderPass;
}

PCamera::~PCamera()
{
}

void PCamera::setPosition(pFloat32 x, pFloat32 y, pFloat32 z)
{
    pMatrix4x4SetTranslation(x, y, z, m_cameraMatrix);
}

void PCamera::setX(pFloat32 x)
{
    m_cameraMatrix[12] = x;
}

void PCamera::setY(pFloat32 y)
{
    m_cameraMatrix[13] = y;
}

void PCamera::setZ(pFloat32 z)
{
    m_cameraMatrix[14] = z;
}


void PCamera::setOrientation(pFloat32 lookAtX, pFloat32 lookAtY, pFloat32 lookAtZ,
                    pFloat32 upX, pFloat32 upY, pFloat32 upZ)
{
    pFloat32 lookAt[3];
    pFloat32 up[3];

    lookAt[0] = lookAtX;
    lookAt[1] = lookAtY;
    lookAt[2] = lookAtZ;

    up[0] = upX;
    up[1] = upY;
    up[2] = upZ;

    pMatrix4x4LookAt(&m_cameraMatrix[12], lookAt, up, m_cameraMatrix);
}

// Temporarily delete these three functions.
//void PCamera::setRx(pFloat32 radians)
//{
//    m_rotationX = radians;
//    m_dirty = true;
//}
//
//void PCamera::setRy(pFloat32 radians)
//{
//    m_rotationY = radians;
//    m_dirty = true;
//}
//
//void PCamera::setRz(pFloat32 radians)
//{
//    m_rotationZ = radians;
//    m_dirty = true;
//}

void PCamera::setProjection(PCameraProjectionTypeEnum projection)
{
    m_projection = projection;
    calculateProjectionMatrix();
}

void PCamera::setNearZ(pFloat32 nearz)
{
    m_nearZ = nearz;
    calculateProjectionMatrix();
}

void PCamera::setFarZ(pFloat32 farz)
{
    m_farZ = farz;
    calculateProjectionMatrix();
}

void PCamera::setNearSize(pFloat32 w, pFloat32 h)
{
    m_nearWidth = w;
    m_nearHeight = h;
    calculateProjectionMatrix();
}

void PCamera::setFov(pFloat32 fov)
{
    m_fov = fov;
    calculateProjectionMatrix();
}

void PCamera::setCameraMatrix(pFloat32 *matrix)
{
    pMatrix4x4Copy(matrix, m_cameraMatrix);
}

void PCamera::setProjectionMatrix(pFloat32 *matrix)
{
    pMatrix4x4Copy(matrix, m_projectionMatrix);
}

void PCamera::calculateProjectionMatrix()
{
    if (m_projection == P_CAMERA_ORTHOGONAL)
    {
        pMatrix4x4OrthographicProjection(-m_nearWidth / 2.0f, 
            m_nearWidth / 2.0f, 
            -m_nearHeight / 2.0f,
            m_nearHeight / 2.0f,
            m_nearZ, 
            m_farZ,
            m_projectionMatrix); 
    }
    else if (m_projection == P_CAMERA_PERSPECTIVE)
    {
        pMatrix4x4PerspectiveProjection(m_fov,
            m_nearWidth / m_nearHeight,
            m_nearZ,
            m_farZ, 
            m_projectionMatrix); 
    }
    else
    {
        pAssertNotReachable();
    }
}
