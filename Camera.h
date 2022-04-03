#pragma once

/*‘O•ûéŒ¾*/
class Actor;

class Camera
{
public:
	Camera(unsigned int width, unsigned int height);

	void UpdateCamera();

	const Vector2& GetLocation() const { return m_location; }
	const Vector2& GetOrigin();
	void SetFollowTarget(Actor* actor);

private:
	unsigned int m_width;
	unsigned int m_height;
	Vector2 m_location;
	Vector2 m_origin;
	Actor* p_followTarget;
};