#pragma once

template<class T>
class Singleton
{
public:
	Singleton()
	{
		assert(!m_singleton);						/*この時点ではシングルトンが存在しないことを確認する*/
		m_singleton = reinterpret_cast<T*> (this);
		assert(m_singleton);						/*シングルトンが作成されていることを確認する*/
	}

	virtual ~Singleton()
	{
		assert(m_singleton);						/*シングルトンが存在することを確認する*/
		m_singleton = nullptr;
	}

	static inline T& GetInstance()
	{
		assert(m_singleton);						/*シングルトンが存在することを確認する*/
		return *m_singleton;
	}

private:
	static T* m_singleton;

	void operator=(const Singleton& obj) {}			/*代入演算子を削除*/
	Singleton(const Singleton& obj) {}				/*コピーコンストラクタを削除*/
};

template<typename T> T* Singleton<T>::m_singleton = nullptr;