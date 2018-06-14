//
// Created by Laura on 13/06/2018.
//

#ifndef FLAPPYBIRD_MODULE_H
#define FLAPPYBIRD_MODULE_H

class Application;
class Collider;

class Module
{

public:
    Application* App;

    Module(){}
    Module(Application* parent) : App(parent)
    {}

    virtual bool Init()
    {
        return true;
    }

    virtual bool Start()
    {
        return true;
    }

    virtual bool PreUpdate()
    {
        return true;
    }

    virtual bool Update()
    {
        return true;
    }

    virtual bool PostUpdate()
    {
        return true;
    }

	virtual void Input()
	{

	}

	virtual void OnCollision(Collider* c1, Collider* c2)
	{

	}

    virtual bool CleanUp()
    {
        return true;
    }

};
#endif //FLAPPYBIRD_MODULE_H
