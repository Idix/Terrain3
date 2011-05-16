#ifndef TUBE_H
#define TUBE_H

#include "project.h"
#include <Renderable.h>

class Tube : public Renderable
{
	public:
		Tube(unsigned int segments = 8, unsigned int lengthSegments = 1);
		virtual ~Tube();
		virtual void render() const;
	protected:
	private:
		unsigned int m_Segments;
		unsigned int m_LengthSegments;
};

#endif // TUBE_H
