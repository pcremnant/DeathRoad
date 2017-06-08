/*#include"CObject.h"

void CMainCharacter::MF_Init() {
	m_rcPosition.left = CHARACTERLEFT;
	m_rcPosition.right = m_rcPosition.left + 20;
	m_rcPosition.top = CHARACTERTOP;
	m_rcPosition.bottom = m_rcPosition.top + 20;
	direction = 0;
	damage = 30 + STAGE.PlayerUpgrade;
	m_nSpeed = 100;
	Z = 5;
}
void CMainCharacter::MF_DrawObj(HDC hdc) {


}
void CMainCharacter::MF_Move() {
	if (direction == 1) {//위로
		if (Z < 0) {
			Z = 1;
			m_rcPosition.left = m_rcPosition.left;
			m_rcPosition.right = m_rcPosition.right;
			m_rcPosition.top = m_rcPosition.top;
			m_rcPosition.bottom = m_rcPosition.bottom;
		}
		else {
			m_rcPosition.left += 10;
			m_rcPosition.right = m_rcPosition.left + 20;
			m_rcPosition.top -= 10;
			m_rcPosition.bottom = m_rcPosition.top + 20;
			Z--;
		}

	}
	if (direction == 2) {//아래로
		if (Z >5) {
			Z = 5;
			m_rcPosition.left = m_rcPosition.left;
			m_rcPosition.right = m_rcPosition.right;
			m_rcPosition.top = m_rcPosition.top;
			m_rcPosition.bottom = m_rcPosition.bottom;

		}
		else {
			m_rcPosition.left -= 10;
			m_rcPosition.right = m_rcPosition.left + 20;
			m_rcPosition.top += 10;
			m_rcPosition.bottom = m_rcPosition.top + 20;
			Z++;
		}
	}
}
void CMainCharacter::MF_Attack() {
	if (Ready) {


	}

}//보류
void CEnemyArcher::MF_Init() {
	m_nSpeed = 10;
	MV_Hp = 10 * STAGE.Stage;
	MV_range = 400;
	MV_damage = 10 + STAGE.Stage;
	Z = rand() % 5 + 1;
	m_rcPosition.left = ENEMYLEFT;
	m_rcPosition.right = m_rcPosition.left + 20;
	if (Z == 1) {
		m_rcPosition.top = ENEMYTOP;
		m_rcPosition.bottom = m_rcPosition.top + 20;
	}
	else if (Z == 2)
	{
		m_rcPosition.top = ENEMYTOP + 10;
		m_rcPosition.bottom = m_rcPosition.top + 20;
	}
	else if (Z == 3)
	{
		m_rcPosition.top = ENEMYTOP + 20;
		m_rcPosition.bottom = m_rcPosition.top + 20;
	}
	else if (Z == 4)
	{
		m_rcPosition.top = ENEMYTOP + 30;
		m_rcPosition.bottom = m_rcPosition.top + 20;
	}
	else if (Z == 5)
	{
		m_rcPosition.top = ENEMYTOP + 40;
		m_rcPosition.bottom = m_rcPosition.top + 20;
	}
}
void CEnemyArcher::MF_DrawObj(HDC hdc) {



}
void CEnemyArcher::MF_Move() {
	if (MV_Stop != true) {
		m_rcPosition.left += m_nSpeed;
		m_rcPosition.right = m_rcPosition.left + 20;
	}
}
void CEnemyArcher::MF_Attack() {

}
void CEnemyArcher::MF_Death() {}
void CEnemyWarrior::MF_Init() {
	m_nSpeed = 10;
	MV_Hp = 10 * STAGE.Stage;
	MV_Shield = 1 + STAGE.Stage;
	MV_range = 20;
	MV_damage = 20 + STAGE.Stage;
	Z = rand() % 5 + 1;
	m_rcPosition.left = ENEMYLEFT;
	m_rcPosition.right = m_rcPosition.left + 20;
	if (Z == 1) {
		m_rcPosition.top = ENEMYTOP;
		m_rcPosition.bottom = m_rcPosition.top + 20;
	}
	else if (Z == 2)
	{
		m_rcPosition.top = ENEMYTOP + 10;
		m_rcPosition.bottom = m_rcPosition.top + 20;
	}
	else if (Z == 3)
	{
		m_rcPosition.top = ENEMYTOP + 20;
		m_rcPosition.bottom = m_rcPosition.top + 20;
	}
	else if (Z == 4)
	{
		m_rcPosition.top = ENEMYTOP + 30;
		m_rcPosition.bottom = m_rcPosition.top + 20;
	}
	else if (Z == 5)
	{
		m_rcPosition.top = ENEMYTOP + 40;
		m_rcPosition.bottom = m_rcPosition.top + 20;
	}
}
void CEnemyWarrior::MF_DrawObj(HDC hdc) {

}
void CEnemyWarrior::MF_Death() {}
void CEnemyWarrior::MF_Move() {
	if (MV_Stop != true) {
		m_rcPosition.left += m_nSpeed;
		m_rcPosition.right = m_rcPosition.left + 20;
	}
}
void CEnemyWarrior::MF_Attack() {


}*/