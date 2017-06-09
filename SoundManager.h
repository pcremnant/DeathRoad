#pragma once

#include "resource\sound\FMOD\include\fmod.hpp"

#define MAX_SOUND 50

// BGM 채널 번호
#define BGM_INTRO 0
#define BGM_MAINMENU 1
#define BGM_MANAGE 2
#define BGM_STAGE 3
// stage bgm은 더 늘어날 수 있음

// EFFECT 채널 번호

// 시스템 관련 효과음
#define EFFECT_CLICK_BUTTON_00 10

// 유닛 관련 효과음
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
	FMOD::Channel	*m_Channel{ nullptr };	// bgm을 위한 채널
	FMOD::Sound		*m_Sound[MAX_SOUND];
};
