// pcamera.h
// The rendering state
//
// Copyright 2013 Cooee. All rights reserved.
//
// Hongwei Li lihw81@gmail.com
//

#ifndef PCAMERA_H
#define PCAMERA_H

#include <PGlobal/pglobal.h>

enum PCameraProjectionTypeEnum
{
    P_CAMERA_ORTHOGONAL = 0x00,
    P_CAMERA_PERSPECTIVE = 0x01,
};

class PRenderPass;


class P_DLLEXPORT PCamera
{
public:
    PCamera(PRenderPass *renderPass);
    ~PCamera();

    // Set the position
    void setPosition(pFloat32 x, pFloat32 y, pFloat32 z);
    void setX(pFloat32 x);
    P_INLINE pFloat32 getX() const { return m_cameraMatrix[12]; }
    void setY(pFloat32 y);
    P_INLINE pFloat32 getY() const { return m_cameraMatrix[13]; }
    void setZ(pFloat32 z);
    P_INLINE pFloat32 getZ() const { return m_cameraMatrix[14]; }
    // Set the rotation.
    void setOrientation(pFloat32 lookAtX, pFloat32 lookAtY, pFloat32 lookAtZ,
        pFloat32 upX, pFloat32 upY, pFloat32 upZ);

    // Temporarily delete these three functions.
    //void setRx(pFloat32 radians); 
    //void setRy(pFloat32 radians);
    //void setRz(pFloat32 radians);
    
    void setProjection(PCameraProjectionTypeEnum projection);
    P_INLINE PCameraProjectionTypeEnum getProjection() const { return m_projection; }

    void setNearZ(pFloat32 nearz);
    void setFarZ(pFloat32 farz);
    void setNearSize(pFloat32 w, pFloat32 h);
    void setFov(pFloat32 fov);

    // Matrix
    void setCameraMatrix(pFloat32 *matrix);
    P_INLINE const pFloat32 *getCameraMatrix() const { return m_cameraMatrix; }

    void setProjectionMatrix(pFloat32 *matrix);
    P_INLINE const pFloat32 *getProjectionMatrix() { return m_projectionMatrix; }
    
private:
    void calculateProjectionMatrix();

private:
    // Temporarily delete these three values.
    //pFloat32 m_rotationX;
    //pFloat32 m_rotationY;
    //pFloat32 m_rotationZ;

    pFloat32 m_nearZ;
    pFloat32 m_farZ;
    pFloat32 m_nearWidth;
    pFloat32 m_nearHeight;
    pFloat32 m_fov; // degrees

    PCameraProjectionTypeEnum m_projection;

    pFloat32 m_cameraMatrix[16];
    pFloat32 m_projectionMatrix[16];

    PRenderPass *m_renderPass;
};

#endif // !PCAMERA_H
