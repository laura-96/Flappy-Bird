//
// Created by Laura on 14/06/2018.
//

#include "ModuleRenderer.h"

#include "Shapes.h"
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <android/log.h>


#define LOG_TAG "NativeLibrary"
#define LOG_E(...)  __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)

ModuleRenderer::ModuleRenderer(Application *app) :
                        Module(app),
                        context(eglGetCurrentContext()),
                        program(0),
                        vertexBuff(0),
                        circleVBuff(0),
                        vpAttrib(-1),
                        posAttrib(-1),
                        colorAttrib(-1)
{}


bool ModuleRenderer::Init() {

    int sx, sy;
    GetViewportSize(sx, sy);

    viewport[0] = (float)sx;
    viewport[1] = (float)sy;

    program = createProgram(vertex, fragment);

    if (!program)
        return false;

    posAttrib = glGetAttribLocation(program, "pos");
    colorAttrib = glGetAttribLocation(program, "color");
    vpAttrib = glGetUniformLocation(program, "viewport");

    glGenBuffers(1, &vertexBuff);
    glGenBuffers(1, &circleVBuff);
    return true;
}

ModuleRenderer::~ModuleRenderer() {

    if (eglGetCurrentContext() != context)
        return;
    glDeleteBuffers(1, &vertexBuff);
    glDeleteBuffers(1, &circleVBuff);
    glDeleteProgram(program);
}

Circle* ModuleRenderer::CreateCircle(float radius, float x, float y)
{
    circle = new Circle(radius, x, y);

    return circle;

}

void ModuleRenderer::AddQuad(Quad* quad) {

    quads.push_back(quad);
}

void ModuleRenderer::RemoveQuad(Quad* toRemove)
{
    if(quads.empty()) return;

    for(std::vector<Quad*>::iterator it = quads.begin(); it != quads.end() && !quads.empty(); ++it)
    {
        if((*it) == toRemove)
        {
            quads.erase(it);
        }
    }
}


void ModuleRenderer::Draw() {
    glUseProgram(program);

    glBindBuffer(GL_ARRAY_BUFFER, vertexBuff);

    for(int i = 0; i < quads.size(); ++i)
    {

        glBufferData(GL_ARRAY_BUFFER, sizeof(*quads[i]), &(*quads[i]).vertices[0], GL_STATIC_DRAW);

        glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)offsetof(Vertex, pos));
        glVertexAttribPointer(colorAttrib, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (const GLvoid*)offsetof(Vertex, rgba));

        glEnableVertexAttribArray(posAttrib);
        glEnableVertexAttribArray(colorAttrib);

        glUniform2fv(vpAttrib, 1, viewport);
        glDrawArrays(GL_TRIANGLES, 0, 6);

    }

    glBindBuffer(GL_ARRAY_BUFFER, circleVBuff);

    glBufferData(GL_ARRAY_BUFFER, sizeof(*circle), &(*circle).vertices[0], GL_STATIC_DRAW);
    glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)offsetof(Vertex, pos));
    glVertexAttribPointer(colorAttrib, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (const GLvoid*)offsetof(Vertex, rgba));


    glEnableVertexAttribArray(posAttrib);
    glEnableVertexAttribArray(colorAttrib);

    glUniform2fv(vpAttrib, 1, viewport);
    glDrawArrays(GL_TRIANGLE_FAN, 0, 20);

}


bool ModuleRenderer::checkError(const char *function) {
    GLint err = glGetError();
    if (err != GL_NO_ERROR) {
        LOG_E("GL error after %s(): 0x%08x\n", function, err);
        return true;
    }
    return false;
}

GLuint ModuleRenderer::createShader(GLenum shaderType, const char* src) {
    GLuint shader = glCreateShader(shaderType);
    if (!shader) {
        checkError("glCreateShader");
        return 0;
    }
    glShaderSource(shader, 1, &src, NULL);

    GLint compiled = GL_FALSE;
    glCompileShader(shader);
    glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
    if (!compiled) {
        GLint infoLogLen = 0;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLen);
        if (infoLogLen > 0) {
            GLchar* infoLog = (GLchar*)malloc(infoLogLen);
            if (infoLog) {
                glGetShaderInfoLog(shader, infoLogLen, NULL, infoLog);
                LOG_E("Could not compile %s shader:\n%s\n",
                        shaderType == GL_VERTEX_SHADER ? "vertex" : "fragment",
                        infoLog);
                free(infoLog);
            }
        }
        glDeleteShader(shader);
        return 0;
    }

    return shader;
}

GLuint ModuleRenderer::createProgram(const char* vtxSrc, const char* fragSrc) {
    GLuint vtxShader = 0;
    GLuint fragShader = 0;
    GLuint program = 0;
    GLint linked = GL_FALSE;

    vtxShader = createShader(GL_VERTEX_SHADER, vtxSrc);
    if (!vtxShader)
        goto exit;

    fragShader = createShader(GL_FRAGMENT_SHADER, fragSrc);
    if (!fragShader)
        goto exit;

    program = glCreateProgram();
    if (!program) {
        checkError("glCreateProgram");
        goto exit;
    }
    glAttachShader(program, vtxShader);
    glAttachShader(program, fragShader);

    glLinkProgram(program);
    glGetProgramiv(program, GL_LINK_STATUS, &linked);
    if (!linked) {
        LOG_E("Could not link program");
        GLint infoLogLen = 0;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &infoLogLen);
        if (infoLogLen) {
            GLchar* infoLog = (GLchar*)malloc(infoLogLen);
            if (infoLog) {
                glGetProgramInfoLog(program, infoLogLen, NULL, infoLog);
                LOG_E("Could not link program:\n%s\n", infoLog);
                free(infoLog);
            }
        }
        glDeleteProgram(program);
        program = 0;
    }

exit:
    glDeleteShader(vtxShader);
    glDeleteShader(fragShader);
    return program;
}

bool ModuleRenderer::Update() {

    Render();
    return true;
}

bool ModuleRenderer::CleanUp() {
    quads.clear();
    circle = nullptr;

    return true;
}

void ModuleRenderer::Render() {

    glClearColor(0.2f, 0.2f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    Draw();
    checkError("ModuleRenderer::Render");
}


void ModuleRenderer::GetViewportSize(int &width, int &height) const
{
    GLint vp[4];
    glGetIntegerv(GL_VIEWPORT, vp);

    width = vp[2];
    height = vp[3];
}