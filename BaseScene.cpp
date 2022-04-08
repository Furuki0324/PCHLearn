#include "BaseScene.h"
#include "Application.h"
#include "Actor.h"
#include "Camera.h"

Direct2D* const BaseScene::GetDirect2D()
{
	return p_app->GetDirect2D();
}

const Vector2& BaseScene::GetCameraOrigin()
{
	if (p_camera) { return p_camera->GetOrigin(); }
	else
	{
		std::cout << "Current scene doesn't have camera." << std::endl;
		return Vector2::Zero;
	}
}

void BaseScene::AddActor(Actor* actor)
{
	int order = actor->GetUpdateOrder();
	auto iter = m_actors.begin();

	for (; iter != m_actors.end(); ++iter)
	{
		if (order < (*iter)->GetUpdateOrder())
		{
			break;
		}
	}

	m_actors.insert(iter, actor);
}

void BaseScene::RemoveActor(Actor* actor)
{
	auto iter = std::find(m_actors.begin(), m_actors.end(), actor);
	if (iter != m_actors.end()) { m_actors.erase(iter); }
}