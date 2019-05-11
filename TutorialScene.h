#pragma once

//クラスの前方宣言
class Scenebase;
class InputManager;
class FileManager;

class TutorialScene : public SceneBase
{
public:
	TutorialScene();
	~TutorialScene()override;
	SceneBase* Update() override;
	void Draw() override;

private:
	void GraphAnimation();

	InputManager* inputManager;
	FileManager* fileManager;

	int tutorialGraph1;
	int tutorialGraph2;
	int nextGraph;

	bool wasPushStartButton;
	bool needChangeTutorialGraph;

	int opacity;									//不透明度
	int changingOpacityValue;
	const int OPACITY_MAX = 80;
};

