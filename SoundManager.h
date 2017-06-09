#pragma once

#include "resource\sound\FMOD\include\fmod.hpp"

#define MAX_SOUND 50

// BGM ä�� ��ȣ
#define BGM_INTRO 0
#define BGM_MAINMENU 1
#define BGM_MANAGE 2
#define BGM_STAGE 3
// stage bgm�� �� �þ �� ����

// EFFECT ä�� ��ȣ

// �ý��� ���� ȿ����
#define EFFECT_CLICK_BUTTON_00 10

// ���� ���� ȿ����
#define EFFECT_INFANT_ATTACK_00 20


class CSoundManager {
public:
	CSoundManager();
	~CSoundManager();

	void SetSounds();

	bool AddSound(
		size_t idx
		, LPCSTR szPath
		, bool bBGM = false
	);

	void Stop(bool bMasterStop = false);
	void PlayEffect(size_t idx);
	void PlayBGM(size_t idx);


private:
	FMOD::System	*m_System{ nullptr };
	FMOD::Channel	*m_Channel{ nullptr };	// bgm�� ���� ä��
	FMOD::Sound		*m_Sound[MAX_SOUND];
};
