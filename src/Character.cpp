#include "character.h"
#include <raymath.h>



Character::Character(const int window_dimensions[]) :
	windowWidth(window_dimensions[0]), windowHeight(window_dimensions[1])
{
	texture = LoadTexture("assets/characters/knight_idle_spritesheet.png");
	idle = LoadTexture("assets/characters/knight_idle_spritesheet.png");
	run = LoadTexture("assets/characters/knight_run_spritesheet.png");

	width = texture.width / static_cast<float>(maxFrames);
	height = texture.height;

}

Vector2 Character::getScreenPos()
{
	return Vector2{
		static_cast<float>(windowWidth) / 2.0f - scale * (0.5f * width),
		static_cast<float>(windowHeight) / 2.0f - scale * (0.5f * height)
	};
}

Character::~Character() {
	UnloadTexture(texture);
	UnloadTexture(idle);
	UnloadTexture(run);
}


void Character::tick(float deltaTime)
{

	if (IsKeyDown(KEY_A)) velocity.x -= 1.0f;
	if (IsKeyDown(KEY_D)) velocity.x += 1.0f;
	if (IsKeyDown(KEY_W)) velocity.y -= 1.0f;
	if (IsKeyDown(KEY_S)) velocity.y += 1.0f;
	BaseCharacter::tick(deltaTime);

	Vector2 origin{};
	Vector2 offset{};
	float rotation{};
	if (rightLeft > 0.f) {
		origin = { 0.f, weapon.height * scale };
		offset = { 35.f, 55.f };
		weaponCollisionRec = {
			getScreenPos().x + offset.x,
			getScreenPos().y + offset.y - weapon.width * scale,
			weapon.width* scale,
			weapon.height* scale
		};
		rotation = 35.f;
	}
	else {
		origin = { weapon.width * scale, weapon.height * scale };
		offset = { 25.f, 55.f };
		weaponCollisionRec = {
		getScreenPos().x + offset.x - weapon.width * scale,
		getScreenPos().y + offset.y - weapon.width * scale,
		weapon.width * scale,
		weapon.height * scale
		};
		rotation = -35.f;
	}
	// Draw the sword
	Rectangle source{ 0.f, 0.f, static_cast<float>(weapon.width) * rightLeft, static_cast<float>(weapon.height) };
	Rectangle dest{ getScreenPos().x + offset.x, getScreenPos().y + offset.y, weapon.width * scale, weapon.height * scale };
	DrawTexturePro(weapon, source, dest, origin, rotation, WHITE);

	DrawRectangleLines(
		weaponCollisionRec.x,
		weaponCollisionRec.y,
		weaponCollisionRec.width,
		weaponCollisionRec.height,
		RED
	);



}