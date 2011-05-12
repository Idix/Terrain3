#pragma once

#include "project.h"

#include "Math/Vector3D.h"
#include "Math/Matrix4.h"
#include "MatrixStack.h"

class Camera
{
private:
	Math::Vector3D position;
	Math::Vector3D direction;
	Math::Vector3D pitchAxis;
	const Math::Vector3D up;
	const Math::Vector3D baseDirection;
	Math::Matrix4 m_Projection;
	GLdouble m_Yaw;
	GLdouble m_Pitch;
	void computeDirection();
public:
	Camera(void);
	void forward(double speed);
	void backward(double speed);
	void left(double speed);
	void right(double speed);
	void rotateLeftRight(GLdouble angle);
	void rotateUpDown(GLdouble angle);
	void perspective(GLfloat fov, GLfloat aspect, GLfloat near, GLfloat far);
    void initModelViewStack(MatrixStack& stack) const;
	inline const Math::Vector3D& getPosition(void) const { return position; };
	inline const Math::Matrix4& getProjection(void) const { return m_Projection; };
};
