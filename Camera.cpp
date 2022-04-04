#include "Camera.h"
#include "Actor.h"
#include "Game.h"

Camera::Camera(unsigned int windowWidth, unsigned int windowHeight, unsigned int stageWidth, unsigned int stageHeight)
	:m_location(Vector2::Zero)
	,m_windowWidth(windowWidth)
	,m_windowHeight(windowHeight)
	,m_stageWidth(stageWidth)
	,m_stageHeight(stageHeight)
{}

void Camera::UpdateCamera()
{
	if (p_followTarget)
	{
		m_location = p_followTarget->GetActorWorldLocation();
	}

	/*
	スクリーンの原点を求める。
	もし原点がエリア外になる場合は補正する。
	*/
	m_origin = Vector2(m_location.x - m_windowWidth / 2, m_location.y - m_windowHeight / 2);
	if (m_origin.x <= 0)
	{
		m_origin.x = 0;
	}
	if (m_origin.x + m_windowWidth >= m_stageWidth)
	{
		m_origin.x = m_stageWidth - m_windowWidth;
	}

	if (m_origin.y <= 0)
	{
		m_origin.y = 0;
	}
	if (m_origin.y + m_windowHeight >= m_stageHeight)
	{
		m_origin.y = m_stageHeight - m_windowHeight;
	}
}

const Vector2& Camera::GetOrigin()
{
	return m_origin;
}

void Camera::SetFollowTarget(Actor* actor)
{
	p_followTarget = actor;
}