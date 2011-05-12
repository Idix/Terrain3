#include "Camera.h"
#include "Math/Rotation.h"
#include <math.h>

Camera::Camera(void)
: position(0.0, 0.0, 2.0), direction(0.0, 0.0, -1.0), up(0.0, 1.0, 0.0), baseDirection(0.0, 0.0, -1.0), m_Yaw(0.0), m_Pitch(0.0)
{
    direction.normalize();
    computeDirection();
}

void Camera::initModelViewStack(MatrixStack& stack) const
{
    stack.reset();

    stack.rotate(up, m_Yaw*PI/180);
    stack.rotate(pitchAxis, m_Pitch*PI/180);

    // Transform world in respect to camera
    stack.translate(-position.getX(), -position.getY(), -position.getZ());
}

void Camera::forward(double speed)
{
	position += direction * speed;
}

void Camera::backward(double speed)
{
	position -= direction * speed;
}

void Camera::left(double speed)
{
    Math::Vector3D straff(direction.cross(up));
    straff.normalize();
	position -= straff * speed;
}

void Camera::right(double speed)
{
    Math::Vector3D straff(direction.cross(up));
    straff.normalize();
	position += straff * speed;
}

void Camera::rotateLeftRight(GLdouble angle)
{
    m_Yaw += angle;
    computeDirection();
}

void Camera::rotateUpDown(GLdouble angle)
{
    m_Pitch -= angle;
    m_Pitch = m_Pitch >= 89.0 ? 89.0 : m_Pitch;
    m_Pitch = m_Pitch <= -89.0 ? -89.0 : m_Pitch;
    computeDirection();
}

void Camera::computeDirection()
{
    Math::Rotation yawRotation(up, m_Yaw*PI/180);
	direction = yawRotation.rotate(baseDirection);

    pitchAxis = up.cross(direction);
	pitchAxis.normalize();
	Math::Rotation pitchRotation(pitchAxis, m_Pitch*PI/180);
	direction = pitchRotation.rotate(direction);
}

void Camera::perspective(GLfloat fov, GLfloat aspect, GLfloat near, GLfloat far)
{
    m_Projection.set(Math::Matrix4::createPerspective(fov, aspect, near, far));
}
