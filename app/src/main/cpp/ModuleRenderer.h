//
// Created by Laura on 14/06/2018.
//

#ifndef FLAPPYBIRD_MODULERENDERER_H
#define FLAPPYBIRD_MODULERENDERER_H

#include "Module.h"

#include <math.h>
#include <vector>

#include <EGL/egl.h>
#include <GLES2/gl2.h>

class Quad;
class Circle;

static const char vertex[] =
        "#version 100\n"
                "attribute vec2 pos;\n"
                "attribute vec4 color;\n"
                "varying vec4 vColor;\n"
                "void main() {\n"
                "    gl_Position = vec4(pos, 0.0, 1.0);\n"
                "    vColor = color;\n"
                "}\n";

static const char fragment[] =
        "#version 100\n"
                "precision mediump float;\n"
                "varying vec4 vColor;\n"
                "void main() {\n"
                "    gl_FragColor = vColor;\n"
                "}\n";

class ModuleRenderer : public Module {
public:
    ModuleRenderer(Application* app);
    ~ModuleRenderer();

    bool Init();
    bool Update();
    bool CleanUp();

    void AddQuad(Quad* quad);
    Circle* CreateCircle(float radius, float x, float y);
    void RemoveQuad(Quad* toRemove);
    void Render();

    void GetViewportSize(int &width, int &height) const;

private:
    bool checkError(const char* function);
    GLuint createShader(GLenum shaderType, const char* src);
    GLuint createProgram(const char* vtxSrc, const char* fragSrc);

    virtual void Draw();

    const EGLContext context;
    GLuint program;
    GLuint vertexBuff;
    GLuint circleVBuff;

    GLint posAttrib;
    GLint colorAttrib;

    std::vector<Quad*> quads;
    Circle* circle;
};

#endif //FLAPPYBIRD_MODULERENDERER_H
