#pragma once

/*‘O•ûéŒ¾*/
class Actor;

class Camera
{
public:
	Camera(unsigned int windowWidth, unsigned int windowHeight, unsigned int stageWidth, unsigned int stageHeight);

	void UpdateCamera();

	const Vector2& GetLocation() const { return m_location; }
	const Vector2& GetOrigin();
	void SetFollowTarget(Actor* actor);

private:
	unsigned int m_windowWidth;
	unsigned int m_windowHeight;
	unsigned int m_stageWidth;
	unsigned int m_stageHeight;
	Vector2 m_location;
	Vector2 m_origin;
	Actor* p_followTarget;
};