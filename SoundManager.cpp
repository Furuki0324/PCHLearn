#include "SoundManager.h"

/*最大ボイス数を増やすためのパラメータ*/
#define MAX_VOICE			(24)
#define MAX_VIRTUAL_VOICE	(MAX_VOICE + 8)
#define MAX_CRIFS_LOADED	(MAX_VOICE + 8)

/*最大サンプリングレート*/
#define MAX_SAMPLING_RATE	(48000 * 4)

/*ACF/ACBのマクロ定義ヘッダ*/
#include "../PCHLearn/CRI/Public/RPGCueSheet.h"
#include "../PCHLearn/CRI/Public/SimpleRPG_acf.h"

/*使用するファイル名*/
#define ACF_FILE "SimpleRPG.acf"
#define ACB_FILE "RPGCueSheet.acb"
#define AWB_FILE "RPGCueSheet.awb"

SoundManager::SoundManager()
{
	/*コールバック関数の登録*/
	criErr_SetCallback(user_error_callback_func);

	/*メモリアロケータの登録*/
	criAtomEx_SetUserAllocator(user_alloc_func, user_free_func, NULL);

	/*ライブラリの初期化*/
	CriAtomExConfig_WASAPI lib_config;
	CriFsConfig fs_config;
	criAtomEx_SetDefaultConfig_WASAPI(&lib_config);
	criFs_SetDefaultConfig(&fs_config);
	lib_config.atom_ex.max_virtual_voices = MAX_VIRTUAL_VOICE;
	fs_config.num_loaders = MAX_CRIFS_LOADED;
	lib_config.atom_ex.fs_config = &fs_config;
	criAtomEx_Initialize_WASAPI(&lib_config, NULL, 0);

	/*ACFファイルの読み込みと登録*/
	criAtomEx_RegisterAcfFile(NULL, PATH ACF_FILE, NULL, 0);

	/*DSP設定のアタッチ*/
	criAtomEx_AttachDspBusSetting("DspBusSetting_0", NULL, 0);

	/*ボイスプールの作成*/
	CriAtomExStandardVoicePoolConfig voicePool_config;
	criAtomExVoicePool_SetDefaultConfigForStandardVoicePool(&voicePool_config);
	voicePool_config.num_voices = MAX_VOICE;									/*最大ボイス数の設定*/
	voicePool_config.player_config.max_sampling_rate = MAX_SAMPLING_RATE;		/*最大ピッチの設定*/
	voicePool_config.player_config.streaming_flag = CRI_TRUE;					/*ストリーム再生対応*/
	voice_pool = criAtomExVoicePool_AllocateStandardVoicePool(&voicePool_config, NULL, 0);

	/*ACBファイルを読み込み*、ACBハンドルを作成*/
	acb_hn = criAtomExAcb_LoadAcbFile(NULL, PATH ACB_FILE, NULL, PATH AWB_FILE, NULL, 0);

	/*プレイヤーの作成*/
	player = criAtomExPlayer_Create(NULL, NULL, 0);

	criAtomExPlayer_SetCueId(player, acb_hn, CRI_RPGCUESHEET_MAOU_OLD_BATTLE_36_01);
}

SoundManager::~SoundManager()
{
	/*DSPのデタッチ*/
	criAtomEx_DetachDspBusSetting();

	/*プレイヤーハンドルの破棄*/
	criAtomExPlayer_Destroy(player);

	/*ボイスプールの破棄*/
	criAtomExVoicePool_Free(voice_pool);

	/*ACBハンドルの破棄*/
	criAtomExAcb_Release(acb_hn);

	/*ACFの登録解除*/
	criAtomEx_UnregisterAcf();

	/*ライブラリの終了*/
	criAtomEx_Finalize_WASAPI();
}

void SoundManager::Play(CriAtomExCueId id)
{
	criAtomExPlayer_SetCueId(player, acb_hn, id);
	playback_id = criAtomExPlayer_Start(player);

	//{
	//	while (true)
	//	{
	//		if (criAtomExPlayer_GetStatus(player) == CriAtomExPlayerStatus::CRIATOMEXPLAYER_STATUS_STOP) break;
	//		if (criAtomExPlayer_GetStatus(player) == CriAtomExPlayerStatus::CRIATOMEXPLAYER_STATUS_ERROR) break;
	//		if (criAtomExPlayer_GetStatus(player) == CriAtomExPlayerStatus::CRIATOMEXPLAYER_STATUS_PLAYEND) break;

	//		Sleep(0);
	//	}

	//	std::cout << "End" << std::endl;
	//	criAtomExPlayer_Stop(player);
	//}
}

void SoundManager::user_error_callback_func(const CriChar8* errid, CriUint32 p1, CriUint32 p2, CriUint32* parray)
{
	const CriChar8* errmsg;

	/*エラー文字列の表示*/
	errmsg = criErr_ConvertIdToMessage(errid, p1, p2);
	std::cout << ("%s\n", errmsg);
}

void* SoundManager::user_alloc_func(void* obj, CriUint32 size)
{
	void* ptr;
	ptr = malloc(size);
	return ptr;
}

void SoundManager::user_free_func(void* obj, void* ptr)
{
	free(ptr);
}