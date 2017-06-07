#pragma once

#include "resource\sound\FMOD\include\fmod.hpp"

#define MAX_SOUND 50

// BGM 채널 번호
#define INTRO_BGM 0
#define MAINMENU_BGM 1
#define MANAGE_BGM 2
#define STAGE_BGM 3
// stage bgm은 더 늘어날 수 있음

// EFFECT 채널 번호
// ...


class CSoundManager {
public:
	CSoundManager();
	~CSoundManager();

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
