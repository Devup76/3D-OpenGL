#pragma once
class GameEngine
{
public:

	GameEngine();
	~GameEngine();

	enum class GAMESTATE {
		PLAY,
		END
	};

	void init();
	void run();
	void render();
	void update();


private:

};