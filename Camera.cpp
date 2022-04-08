#include "Camera.h"
#include "Actor.h"
#include "BaseScene.h"

Camera::Camera(BaseScene* scene, unsigned int windowWidth, unsigned int windowHeight, unsigned int stageWidth, unsigned int stageHeight)
	:Actor(scene, -1)			//�K���S�ẴA�N�^�[������ɍX�V�����悤��updateOrder��-1�ŌŒ肷��
	,m_windowWidth(windowWidth)
	,m_windowHeight(windowHeight)
	,m_stageWidth(stageWidth)
	,m_stageHeight(stageHeight)
	,p_followTarget(nullptr)
{}

Camera::~Camera()
{
	
}

void Camera::UpdateActor(float deltaTime)
{
	if (p_followTarget)
	{
		m_worldLocation = p_followTarget->GetActorWorldLocation();
	}

	/*
	�X�N���[���̌��_�����߂�B
	�������_���G���A�O�ɂȂ�ꍇ�͕␳����B
	*/
	m_origin = Vector2(m_worldLocation.x - m_windowWidth / 2, m_worldLocation.y - m_windowHeight / 2);
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
	if (actor == this)
	{
		std::cout << "Can't set myself as follow target." << std::endl;
	}
	else
	{
		p_followTarget = actor;
	}
}