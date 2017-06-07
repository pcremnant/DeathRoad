#include"CObject.h"

void CMainCharacter::MF_Init() {
	Mv_obj.left = CHARACTERLEFT;
	Mv_obj.right = Mv_obj.left + 20;
	Mv_obj.top = CHARACTERTOP;
	Mv_obj.bottom = Mv_obj.top + 20;
	direction = 0;
	damage = 30 + STAGE.PlayerUpgrade;
	Mv_speed = 100;
	Z = 5;
}
void CMainCharacter::MF_DrawObj(HDC hdc) {


}
void CMainCharacter::MF_Move() {
	if (direction == 1) {//위로
		if (Z < 0) {
			Z = 1;
			Mv_obj.left = Mv_obj.left;
			Mv_obj.right = Mv_obj.right;
			Mv_obj.top = Mv_obj.top;
			Mv_obj.bottom = Mv_obj.bottom;

		}
		else {
			Mv_obj.left += 10;
			Mv_obj.right = Mv_obj.left + 20;
			Mv_obj.top -= 10;
			Mv_obj.bottom = Mv_obj.top + 20;
			Z--;
		}

	}
	if (direction == 2) {//아래로
		if (Z >5) {
			Z = 5;
			Mv_obj.left = Mv_obj.left;
			Mv_obj.right = Mv_obj.right;
			Mv_obj.top = Mv_obj.top;
			Mv_obj.bottom = Mv_obj.bottom;

		}
		else {
			Mv_obj.left -= 10;
			Mv_obj.right = Mv_obj.left + 20;
			Mv_obj.top += 10;
			Mv_obj.bottom = Mv_obj.top + 20;
			Z++;
		}
	}
}
void CMainCharacter::MF_Attack() {
	if (Ready) {


	}

}//보류
void CEnemyArcher::MF_Init() {
	Mv_speed = 10;
	MV_Hp = 10 * STAGE.Stage;
	MV_range = 400;
	MV_damage = 10 + STAGE.Stage;
	Z = rand() % 5 + 1;
	Mv_obj.left = ENEMYLEFT;
	Mv_obj.right = Mv_obj.left + 20;
	if (Z == 1) {
		Mv_obj.top = ENEMYTOP;
		Mv_obj.bottom = Mv_obj.top + 20;
	}
	else if (Z == 2)
	{
		Mv_obj.top = ENEMYTOP + 10;
		Mv_obj.bottom = Mv_obj.top + 20;
	}
	else if (Z == 3)
	{
		Mv_obj.top = ENEMYTOP + 20;
		Mv_obj.bottom = Mv_obj.top + 20;
	}
	else if (Z == 4)
	{
		Mv_obj.top = ENEMYTOP + 30;
		Mv_obj.bottom = Mv_obj.top + 20;
	}
	else if (Z == 5)
	{
		Mv_obj.top = ENEMYTOP + 40;
		Mv_obj.bottom = Mv_obj.top + 20;
	}
}
void CEnemyArcher::MF_DrawObj(HDC hdc) {



}
void CEnemyArcher::MF_Move() {
	if (MV_Stop != true) {
		Mv_obj.left += Mv_speed;
		Mv_obj.right = Mv_obj.left + 20;
	}
}
void CEnemyArcher::MF_Attack() {

}
void CEnemyArcher::MF_Death() {}
void CEnemyWarrior::MF_Init() {
	Mv_speed = 10;
	MV_Hp = 10 * STAGE.Stage;
	MV_Shield = 1 + STAGE.Stage;
	MV_range = 20;
	MV_damage = 20 + STAGE.Stage;
	Z = rand() % 5 + 1;
	Mv_obj.left = ENEMYLEFT;
	Mv_obj.right = Mv_obj.left + 20;
	if (Z == 1) {
		Mv_obj.top = ENEMYTOP;
		Mv_obj.bottom = Mv_obj.top + 20;
	}
	else if (Z == 2)
	{
		Mv_obj.top = ENEMYTOP + 10;
		Mv_obj.bottom = Mv_obj.top + 20;
	}
	else if (Z == 3)
	{
		Mv_obj.top = ENEMYTOP + 20;
		Mv_obj.bottom = Mv_obj.top + 20;
	}
	else if (Z == 4)
	{
		Mv_obj.top = ENEMYTOP + 30;
		Mv_obj.bottom = Mv_obj.top + 20;
	}
	else if (Z == 5)
	{
		Mv_obj.top = ENEMYTOP + 40;
		Mv_obj.bottom = Mv_obj.top + 20;
	}
}
void CEnemyWarrior::MF_DrawObj(HDC hdc) {

}
void CEnemyWarrior::MF_Death() {}
void CEnemyWarrior::MF_Move() {
	if (MV_Stop != true) {
		Mv_obj.left += Mv_speed;
		Mv_obj.right = Mv_obj.left + 20;
	}
}
void CEnemyWarrior::MF_Attack() {


}