#pragma once
#include "Actor.h"

class BaseScene;

class UI : public Actor
{
public:
	//UI�ȊO�̃A�N�^�[���X�V����Ă���UI���X�V�����悤��updateOrder�̃f�t�H���g��ݒ�
	UI(BaseScene* scene, int updateOrder = 200);
	//~UI();

	void UpdateActor(float deltaTime) override;
};
