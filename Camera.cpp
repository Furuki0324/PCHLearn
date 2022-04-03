#include "Camera.h"
#include "Actor.h"

Camera::Camera(unsigned int width, unsigned int height)
	:m_location(Vector2::Zero)
	,m_width(width)
	,m_height(height)
{}

void Camera::UpdateCamera()
{
	if (p_followTarget)
	{
		m_location = p_followTarget->GetActorWorldLocation();
	}

	m_origin = Vector2(m_location.x - m_width / 2, m_location.y - m_height / 2);
}

const Vector2& Camera::GetOrigin()
{
	return m_origin;
}

void Camera::SetFollowTarget(Actor* actor)
{
	p_followTarget = actor;
}