//
// Created by Laura on 13/06/2018.
//
#include <jni.h>

#include "Application.h"


Application::Application() {

    module_renderer = new ModuleRenderer(this);
    module_main_scene = new ModuleMainScene(this);
    module_collision = new ModuleCollision(this);

    //render
    AddModule(module_renderer);
    AddModule(module_collision);
    AddModule(module_main_scene);
}

bool Application::Init()
{
    bool ret = true;

    for(std::vector<Module*>::iterator iterator = modules.begin(); iterator != modules.end(); ++iterator)
    {
        ret = (*iterator)->Init();
    }

    for(std::vector<Module*>::iterator iterator = modules.begin(); iterator != modules.end(); ++iterator)
    {
        ret = (*iterator)->Start();
    }

    return ret;
}

bool Application::Update()
{
    bool ret = true;

    for(std::vector<Module*>::iterator iterator = modules.begin(); iterator != modules.end(); ++iterator)
    {
        ret = (*iterator)->PreUpdate();
    }

    for(std::vector<Module*>::iterator iterator = modules.begin(); iterator != modules.end(); ++iterator)
    {
        ret = (*iterator)->Update();
    }

    for(std::vector<Module*>::iterator iterator = modules.begin(); iterator != modules.end(); ++iterator)
    {
        ret = (*iterator)->PostUpdate();
    }

    return ret;
}

void Application::Input()
{
    for(std::vector<Module*>::iterator iterator = modules.begin(); iterator != modules.end(); ++iterator)
    {
        (*iterator)->Input();
    }
}

void Application::OnCollision(Collider *c1, Collider *c2)
{
    for(std::vector<Module*>::iterator iterator = modules.begin(); iterator != modules.end(); ++iterator)
    {
        (*iterator)->OnCollision(c1, c2);
    }
}

bool Application::CleanUp() {

    bool ret = true;

    for (std::vector<Module*>::reverse_iterator module_iterator = modules.rbegin(); module_iterator != modules.rend(); ++module_iterator)
    {
        ret = (*module_iterator)->CleanUp();
    }
    return ret;
}

void Application::AddModule(Module* module)
{
    modules.push_back(module);
}

Application::~Application() {

    delete module_renderer;
    delete module_collision;
    delete module_main_scene;
}


extern "C" {

JNIEXPORT jboolean JNICALL Java_laud_ripoll_flappybird_FlappyBirdLib_Init(JNIEnv* env, jobject object);
JNIEXPORT jboolean JNICALL Java_laud_ripoll_flappybird_FlappyBirdLib_Update(JNIEnv* env, jobject object);
JNIEXPORT jboolean JNICALL Java_laud_ripoll_flappybird_FlappyBirdLib_CleanUp(JNIEnv* env, jobject obj);
JNIEXPORT void JNICALL Java_laud_ripoll_flappybird_FlappyBirdLib_SendTap(JNIEnv* env, jobject obj);

};


static Application* app = NULL;

JNIEXPORT jboolean JNICALL
Java_laud_ripoll_flappybird_FlappyBirdLib_Init(JNIEnv* env, jobject obj) {

    app = new Application();

    app->Init();

    return true;
}

JNIEXPORT jboolean JNICALL
Java_laud_ripoll_flappybird_FlappyBirdLib_Update(JNIEnv* env, jobject obj) {

    if(app)
        app->Update();

    return true;
}


JNIEXPORT jboolean JNICALL
Java_laud_ripoll_flappybird_FlappyBirdLib_CleanUp(JNIEnv* env, jobject obj) {
    if(app)
        app->CleanUp();

    return true;
}

JNIEXPORT void JNICALL
Java_laud_ripoll_flappybird_FlappyBirdLib_SendTap(JNIEnv* env, jobject obj) {
    if(app)
        app->Input();

}