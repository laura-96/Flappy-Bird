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
                "#define GET_POS(p,vp) ((float(p)*2.0/float(vp))-1.0)\n"
                "attribute vec2 pos;\n"
                "attribute vec4 color;\n"
                "varying vec4 vColor;\n"
                "uniform vec2 viewport;\n"

                "void main() {\n"
                "    vec2 new_pos = vec2(GET_POS(pos.x, viewport.x), GET_POS(pos.y, viewport.y));\n"
                "    gl_Position = vec4(new_pos, 0.0, 1.0);\n"
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

    GLint vpAttrib;
    GLint posAttrib;
    GLint colorAttrib;

    float viewport[2];

    std::vector<Quad*> quads;
    Circle* circle;
};

#endif //FLAPPYBIRD_MODULERENDERER_H
