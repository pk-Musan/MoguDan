#pragma once

class BaseScene {

public:
	void init();
	virtual BaseScene* update() = 0;
	void draw();
	void finalize();
};