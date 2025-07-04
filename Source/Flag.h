#pragma once
#include "StageObject.h"

class Flag : public StageObject
{
public:
	Flag(const Vector2& _position);
	~Flag();

	void Draw() override;

	void OnPlayer() override;
};
