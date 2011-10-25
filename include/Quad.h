#ifndef QUAD_H
#define QUAD_H

#include <Renderable.h>


class Quad : public Renderable
{
    public:
        Quad();
        virtual ~Quad();
        virtual void render() const { Renderable::render(GL_TRIANGLE_STRIP); };
    protected:
    private:
};

#endif // QUAD_H
