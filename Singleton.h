#pragma once

template<class T>
class Singleton
{
public:
	Singleton()
	{
		assert(!m_singleton);						/*���̎��_�ł̓V���O���g�������݂��Ȃ����Ƃ��m�F����*/
		m_singleton = reinterpret_cast<T*> (this);
		assert(m_singleton);						/*�V���O���g�����쐬����Ă��邱�Ƃ��m�F����*/
	}

	virtual ~Singleton()
	{
		assert(m_singleton);						/*�V���O���g�������݂��邱�Ƃ��m�F����*/
		m_singleton = nullptr;
	}

	static inline T& GetInstance()
	{
		assert(m_singleton);						/*�V���O���g�������݂��邱�Ƃ��m�F����*/
		return *m_singleton;
	}

private:
	static T* m_singleton;

	void operator=(const Singleton& obj) {}			/*������Z�q���폜*/
	Singleton(const Singleton& obj) {}				/*�R�s�[�R���X�g���N�^���폜*/
};

template<typename T> T* Singleton<T>::m_singleton = nullptr;