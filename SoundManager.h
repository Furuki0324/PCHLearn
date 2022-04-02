#pragma once
#include "Singleton.h"

class SoundManager : public Singleton<SoundManager>
{
public:
	SoundManager();
	virtual ~SoundManager();

	void Play(CriAtomExCueId id);

private:
	static void user_error_callback_func(const CriChar8* errid, CriUint32 p1, CriUint32 p2, CriUint32* parray);
	static void* user_alloc_func(void* obj, CriUint32 size);
	static void user_free_func(void* obj, void* ptr);

private:
	CriAtomExPlayerHn player;
	CriAtomExVoicePoolHn voice_pool;
	CriAtomExAcbHn acb_hn;

	CriAtomExPlaybackId playback_id;
};