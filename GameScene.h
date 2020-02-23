#pragma once
#include "BaseScene.h"

class GameScene : public BaseScene {

public:
	GameScene();
	~GameScene();
	
	void init();
	BaseScene* update();
	void draw();
	void finalize();
};