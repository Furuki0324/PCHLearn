#pragma once
#include "Component.h"

class Actor;

class TextComponent :public Component
{
public:
	TextComponent(Actor* owner, int updateOrder);
	~TextComponent();
};