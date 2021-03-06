
#include"BattleScene.h"
#include"MainScene.h"
#include "renderer/CCRenderer.h"
#include "renderer/CCCustomCommand.h"
#include "renderer/CCGroupCommand.h"


//
////
////将层按顺序设置，并定义返回，重载，前进的回调函数
////测试用
////
static std::function<Layer*()> createFunctions[] =
{
	//CL(MyLayer1),
	CL(MyLayer2)
};
//
static int sceneIdx = 0;//order of scene
#define MAX_LAYER (sizeof(createFunctions)/sizeof(createFunctions[0]));
//
static Layer*next()
{
	sceneIdx++;
	sceneIdx = sceneIdx%MAX_LAYER;

	auto layer = (createFunctions[sceneIdx])();
	return layer;
}

static Layer*restart()
{
	auto layer = (createFunctions[sceneIdx])();
	return layer;
}

static Layer*back()
{
	sceneIdx--;
	int total = MAX_LAYER;
	sceneIdx = (sceneIdx + total) % MAX_LAYER;

	auto layer = (createFunctions[sceneIdx])();
	return layer;
}


void MyLayer2::onEnter()
{
	Layer::onEnter();
	auto s = Director::getInstance()->getWinSize();
	
	if (!_boss)
		SimpleAudioEngine::getInstance()->playBackgroundMusic("bgm/battle0.mp3",true);
	else
		SimpleAudioEngine::getInstance()->playBackgroundMusic("bgm/battle1.mp3", true);
	//SimpleAudioEngine::getInstance()->playEffect("bgm/battle.mp3",true);
	

	/*初始化棋盘*/
	_gameBoard = GameBoard::getNewInstance();
	_gameBoard->setPosition(Vec2(s.width / 2, s.height / 2));
	addChild(_gameBoard);
	/*初始化棋盘完毕*/

	/*初始化牌库*/
	
	int mySet[30];
	int enemySet[30];

	for (int i = 0; i < 30; i++)
	{
		mySet[i] = rand() % 8 ;
		enemySet[i] = rand() % 8 + (_boss ? 110000 : 10000);

	}
	int myNum = 0;
	auto cards = _user->getCardformArray(0);
	for (int i = 0; i < cards.size(); i++)
	{
		int num = cards[i] / 10000000;
		auto id = cards[i] % 10000000;
		for (int j = 0; j < num; j++)
		{
			mySet[myNum] = id;
			myNum++;
		}
	}
	for (int i = 0; i < cards.size(); i++)
	{
		int num = cards[i] / 10000000;
		auto id = cards[i] % 10000000;
		for (int j = 0; j < num; j++)
		{
			mySet[myNum] = id;
			myNum++;
		}
	}
	/*armorId[29] = 0;*/
	/*初始化牌库完毕*/

	/*先后手顺序*/
	bool firstHand[2];
	firstHand[0] = false;
	firstHand[1] = true;
	//if (_firstHand)
	//{
	//	firstHand[0] = true;
	//	firstHand[1] = false;
	//}

	/*初始化Battle*/
	for (int i = 0; i < 2; i++)
	{
		if (i==0)
			_battles[i] = new CBattle(_gameBoard,mySet, i,_socket,_mode,firstHand[i]);
		else
			_battles[i] = new CBattle(_gameBoard, enemySet, i, _socket, _mode, firstHand[i]);
		this->addChild(_battles[i]);	
	}

	_battles[2] = new CBattle(_gameBoard, enemySet, 2, _socket, _mode, firstHand[1]);
	_battles[2]->setEnemy(_battles[1]);
	_battles[2]->setWild(_battles[0]);
	_battles[2]->addWild();
	this->addChild(_battles[2]);
	_battles[0]->setEnemy(_battles[1]);
	_battles[1]->setEnemy(_battles[0]);
	_battles[0]->setWild(_battles[2]);
	_battles[1]->setWild(_battles[2]);
	_battles[0]->gameStart();
	_battles[1]->gameStart();

	

	
	//_gameBoard->addCard(card, POOL_MONSTER, 0, 0, 0);

	/*初始化Command*/

	Command::getInstance()->setBattles(_battles[0], _battles[1]);

	/*初始化tool2D*/
	_tool = new BattleTool2D(_gameBoard, _battles[0], _battles[1],_battles[2]);
	addChild(_tool);

	/*返回按钮*/
	auto backBn = Button::create(s_png_battle_exit);
	backBn->setPosition(Vec2(s.width*0.9,s.height*0.1));
	backBn->addTouchEventListener(this, toucheventselector(MyLayer2::backToMainEvent));
	addChild(backBn);


}

void MyLayer2::backToMain(){
	Scene* s = new Scene();
	auto l = new MainLayer();
	l->setGameSocket(_socket);
	l->setMode(_mode);
	l->_user = _user;
	s->addChild(l);
	Director::getInstance()->replaceScene(s);
	s->release();
	l->release();
}

void MyLayer2::backToMainEvent(Ref*pSender, TouchEventType type) //返回主界面
{
	SimpleAudioEngine::getInstance()->stopBackgroundMusic();
	switch (type)
	{
	case TOUCH_EVENT_ENDED:
	{
		backToMain();
	}
		break;
	default:
		break;
	}
}