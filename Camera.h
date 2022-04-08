#pragma once
#include "Actor.h"

class BaseScene;

class Camera : public Actor
{
public:
	Camera(BaseScene* scene, unsigned int windowWidth, unsigned int windowHeight, unsigned int stageWidth, unsigned int stageHeight);
	~Camera();

	void UpdateActor(float deltaTime) override;

	const Vector2& GetOrigin();
	void SetFollowTarget(Actor* actor);

private:
	unsigned int m_windowWidth;
	unsigned int m_windowHeight;
	unsigned int m_stageWidth;
	unsigned int m_stageHeight;
	Vector2 m_origin;
	Actor* p_followTarget;
};