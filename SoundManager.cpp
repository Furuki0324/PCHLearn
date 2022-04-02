#include "SoundManager.h"

/*�ő�{�C�X���𑝂₷���߂̃p�����[�^*/
#define MAX_VOICE			(24)
#define MAX_VIRTUAL_VOICE	(MAX_VOICE + 8)
#define MAX_CRIFS_LOADED	(MAX_VOICE + 8)

/*�ő�T���v�����O���[�g*/
#define MAX_SAMPLING_RATE	(48000 * 4)

/*ACF/ACB�̃}�N����`�w�b�_*/
#include "../PCHLearn/CRI/Public/RPGCueSheet.h"
#include "../PCHLearn/CRI/Public/SimpleRPG_acf.h"

/*�g�p����t�@�C����*/
#define ACF_FILE "SimpleRPG.acf"
#define ACB_FILE "RPGCueSheet.acb"
#define AWB_FILE "RPGCueSheet.awb"

SoundManager::SoundManager()
{
	/*�R�[���o�b�N�֐��̓o�^*/
	criErr_SetCallback(user_error_callback_func);

	/*�������A���P�[�^�̓o�^*/
	criAtomEx_SetUserAllocator(user_alloc_func, user_free_func, NULL);

	/*���C�u�����̏�����*/
	CriAtomExConfig_WASAPI lib_config;
	CriFsConfig fs_config;
	criAtomEx_SetDefaultConfig_WASAPI(&lib_config);
	criFs_SetDefaultConfig(&fs_config);
	lib_config.atom_ex.max_virtual_voices = MAX_VIRTUAL_VOICE;
	fs_config.num_loaders = MAX_CRIFS_LOADED;
	lib_config.atom_ex.fs_config = &fs_config;
	criAtomEx_Initialize_WASAPI(&lib_config, NULL, 0);

	/*ACF�t�@�C���̓ǂݍ��݂Ɠo�^*/
	criAtomEx_RegisterAcfFile(NULL, PATH ACF_FILE, NULL, 0);

	/*DSP�ݒ�̃A�^�b�`*/
	criAtomEx_AttachDspBusSetting("DspBusSetting_0", NULL, 0);

	/*�{�C�X�v�[���̍쐬*/
	CriAtomExStandardVoicePoolConfig voicePool_config;
	criAtomExVoicePool_SetDefaultConfigForStandardVoicePool(&voicePool_config);
	voicePool_config.num_voices = MAX_VOICE;									/*�ő�{�C�X���̐ݒ�*/
	voicePool_config.player_config.max_sampling_rate = MAX_SAMPLING_RATE;		/*�ő�s�b�`�̐ݒ�*/
	voicePool_config.player_config.streaming_flag = CRI_TRUE;					/*�X�g���[���Đ��Ή�*/
	voice_pool = criAtomExVoicePool_AllocateStandardVoicePool(&voicePool_config, NULL, 0);

	/*ACB�t�@�C����ǂݍ���*�AACB�n���h�����쐬*/
	acb_hn = criAtomExAcb_LoadAcbFile(NULL, PATH ACB_FILE, NULL, PATH AWB_FILE, NULL, 0);

	/*�v���C���[�̍쐬*/
	player = criAtomExPlayer_Create(NULL, NULL, 0);

	criAtomExPlayer_SetCueId(player, acb_hn, CRI_RPGCUESHEET_MAOU_OLD_BATTLE_36_01);
}

SoundManager::~SoundManager()
{
	/*DSP�̃f�^�b�`*/
	criAtomEx_DetachDspBusSetting();

	/*�v���C���[�n���h���̔j��*/
	criAtomExPlayer_Destroy(player);

	/*�{�C�X�v�[���̔j��*/
	criAtomExVoicePool_Free(voice_pool);

	/*ACB�n���h���̔j��*/
	criAtomExAcb_Release(acb_hn);

	/*ACF�̓o�^����*/
	criAtomEx_UnregisterAcf();

	/*���C�u�����̏I��*/
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

	/*�G���[������̕\��*/
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