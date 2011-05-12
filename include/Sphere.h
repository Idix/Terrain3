#ifndef SPHERE_H
#define SPHERE_H

#include "project.h"
#include <Renderable.h>

class Sphere : public Renderable
{
    public:
        Sphere(int steps);
        virtual ~Sphere();
        virtual void render() const;
    protected:
    private:
        unsigned int m_Steps;
};

#endif // SPHERE_H
