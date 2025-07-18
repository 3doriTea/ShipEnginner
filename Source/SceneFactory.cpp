#include "SceneFactory.h"
#include <windows.h>
#include <assert.h>
#include "BootScene.h"
#include "TitleScene.h"
#include "PlayScene.h"
#include "ClearScene.h"
#include "TutorialScene.h"

SceneBase* SceneFactory::CreateFirst()
{
	return new BootScene();
}

SceneBase * SceneFactory::Create(const std::string & name)
{
	if (name == "TITLE")
	{
		return new TitleScene();
	}
	if (name == "PLAY")
	{
		return new PlayScene();
	}
	if (name == "CLEAR")
	{
		return new ClearScene();
	}
	if (name == "TUTORIAL")
	{
		return new TutorialScene();
	}

	MessageBox(NULL, ("次のシーンはありません\n" + name).c_str(), "SceneFactory", MB_ICONERROR | MB_OK);
	assert(false);
	return nullptr;
}
