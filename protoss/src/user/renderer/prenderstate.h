// prenderstate.h
// The rendering state
//
// Copyright 2013 Cooee. All rights reserved.
//
// Hongwei Li lihw81@gmail.com
//

#ifndef PRENDERSTATE_H
#define PRENDERSTATE_H

#include <PGlobal/pglobal.h>

// DESIGN GUIDE (to be deleted after design review)
//
// PRenderState monitors and manages which shader, framebuffer, vertex buffer object
// and textures are in use. It also exposes the OpenGL state to other modules in
// the user layer.
//
// - PRenderState has a PGlState member. It should include a get method to return
// the reference to this PGlState.
// - Move the clearFramebuffer function to PFramebuffer
// - It should help the internal profiling.
//     * Return FPS information
//     * Return the number of triangles and vertices drawn in the previous frame
//     * Return the shader switch times in the previous frame
//     * Return the vertex buffer switch times in the previous frame
//     * Return the texture switch times in the previous frame


class PGlState;
class PShader;
class PFrameBuffer;
class PVertexBuffer;
class PTexture;

class P_DLLEXPORT PRenderState
{
public:
    PRenderState(pUint32 screenWidth, pUint32 screenHeight);
    ~PRenderState();

    // Bind the current shader to GPU. It is already the current one, return immediately.
    void useShader(PShader* shader);
    // Ditto.
    void useFrameBuffer(PFrameBuffer* frameBuffer);
    // Ditto.
    void useVertexBuffer(PVertexBuffer* vertexBuffer);
    // Ditto.
    void useTexture(PTexture* texture, pUint32 textureUnit);

    // TODO: move this function to famebuffer manipulation.
    void clearFramebuffer(bool colorBuffer, bool depthBuffer, bool stencilBuffer);

    // Reset the rendering state to initial value.
    void reset();

private:
    PGlState* m_state;
};

#endif // !PRENDERSTATE_H
