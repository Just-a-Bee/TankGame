
#include "OverState.h"

void OverState::enterState() {

}

void OverState::nextFrame() {
	BeginDrawing();
	ClearBackground(RAYWHITE);

	DrawText("Press enter to retry", 10, 10, 10, BLACK);

	// Get the high score as a string and draw it
	char score[3];
	_itoa_s(GameData::getInstance()->getHighScore(), score, 10);
	DrawText(score, 350, 40, 20, BLACK);

	EndDrawing();
}
GameState* OverState::shouldChangeTo() {

	if (IsKeyPressed(KEY_ENTER)) {
		return new MenuState;
	}

	return nullptr;

}