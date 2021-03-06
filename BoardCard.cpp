#include"BoardCard.h"
#include"Tool.h"
#include"BoardEffect.h"
#include"BoardCardBuilder.h"
#include"GameResource.h"
#include"audio\include\SimpleAudioEngine.h" //音频
using namespace CocosDenshion;

//*类初始化
void BoardCard::onEnter()
{
	Node::onEnter();
	
	addChild(_normal); //默认显示正常图片
	addChild(_frame);
	addChild(_cardBack);
	_normal->setVisible(false);
	_cardside = true;//默认反面，真为反面
	//_cardBack->setVisible(false);
}


//*静态创建卡牌显示类
BoardCard *BoardCard::create(CCard& card)
{
	auto boardcard = new (std::nothrow) BoardCard();
	if (boardcard   && boardcard->init())
	{
		boardcard->initElement(card);
	}
	else
	{
		CC_SAFE_DELETE(boardcard);
	}
	return boardcard;
}
void BoardCard::initElement(CCard& card)
{
	/*
	card由2大部分组成
	1.卡背
	2.卡框：包括卡片图画,数值等
	*/
	/*建立卡牌框*/
	_frame = Sprite::create("battleScene/card/frameMM.png");
	_frame->setRotation3D(Vec3(0, 180, 0));

	/*建立卡牌图片*/
	_normal = BoardCardBuilder::buildCardInBattle(card.get_cardID());
	_normal->setRotation3D(Vec3(0, 180, 0));

	/*建立卡背*/
	_cardBack = Sprite::create("battleScene/card/back.png");
	_cardBack->setScale(0.25f);

	/*建立护甲*/
	_armor = Sprite::create(s_png_battle_armor);
	//_armor->setScale(0.5f);
	_armor->setPosition(80, 29.5);
	_card = &card;
	//初始攻击,生命,费用
	_oAttack = card.get_attack();
	_oHealth = card.get_health();
	_oCost = card.get_cost();
	//添加名称label
	_laName = Tool::createTitleLabel();
	Tool::setLabelString(_laName, _card->get_cardName());
	_laName->setPosition(_frame->getContentSize().width / 2, _frame->getContentSize().height *0.35);
	//添加描述label
	_laDescription = Tool::createTextLabel();
	Tool::setLabelString(_laDescription, _card->get_cardDescribe());
	_laDescription->setDimensions(75, 45);
	_laDescription->setPosition(_frame->getContentSize().width / 2, _frame->getContentSize().height*0.185);
	//添加攻击label
	char s[3];
	sprintf(s, "%d", _card->getFinalAttack());//取最终
	_laAttack = Tool::createEnglishLabel();
	_laAttack->setString(s);
	_laAttack->setPosition(20, 9.5);
	//添加生命label
	char h[3];
	sprintf(h, "%d", _card->getFinalHealth());//取实际
	_laHealth = Tool::createEnglishLabel();
	_laHealth->setString(h);
	_laHealth->setPosition(80, 9.5);
	//添加费用label
	char c[3];
	sprintf(c, "%d", _card->getFinalCost());
	_laCost = Tool::createEnglishLabel();
	_laCost->setString(c);
	_laCost->setPosition(17, 105);

	//sprintf(c, "%d", _card->get_armor());
	_laArmor = Tool::createEnglishLabel();
	//setCurrentArmor(_card->get_armor());
	//_laArmor->setString(c);
	//setCurrentArmor(1);
	_laArmor->setPosition(80, 29.5);
	setCurrentArmor(_card->get_armor(),false);
	
	this->setContentSize(_frame->getContentSize());

	_frame->addChild(_laName);
	_frame->addChild(_laCost);
	_frame->addChild(_laDescription);
	_frame->addChild(_laHealth);
	_frame->addChild(_laAttack);
	_frame->addChild(_armor);
	_frame->addChild(_laArmor);
	_state = CARD_STATE_UNDEFINE;
	autorelease();



}

//*卡牌爆炸,销毁对象,等同于die()
void BoardCard::exploside()
{
	die();
}
//*卡牌爆炸,销毁对象
void BoardCard::die()
{
	SimpleAudioEngine::getInstance()->playEffect("bgm/CS2_050_Death_SearingTotem.mp3");
	auto die_par = ParticleSystemQuad::create("particles/MISS.plist");
	die_par->setPosition(_frame->getContentSize().width / 2, _frame->getContentSize().height*0.05);
	die_par->setScale(0.2);
	addChild(die_par, 2);
	_state = 0;
	this->retain();
	this->runAction(TintTo::create(0.3f, Color3B::GRAY));
	this->runAction(Sequence::create(
		JumpBy::create(0.3f, Vec2(0, 0), 10, 50),
		ScaleTo::create(0.2f, 0, 0),
		CallFunc::create(CC_CALLBACK_0(Node::removeFromParent, this)),
		NULL));

}


//*设置卡牌的状态:在牌库=0;在手上=1;在场上=2;在墓地=3;状态不明=4
void BoardCard::setCardState(int state)
{
	_state = state;
}


//*获取卡牌的状态:在牌库=0;在手上=1;在场上=2;在墓地=3;状态不明=4
int BoardCard::getCardState()
{
	return _state;
}


//*卡牌被沉默
void BoardCard::silent()
{
	_laDescription->removeFromParent();
	
	auto silent = Sprite::create("ChessBoard/chess/silent.png");
	silent->setPosition(150, 200);
	_normal->addChild(silent);
}


//*设置当前生命为CurHealth
//*每当当前生命发生改变需要调用，改变图像上的显示
void BoardCard::setCurrentHealth(int CurHealth)
{
	_curHealth = CurHealth;
	char s[3];
	sprintf(s, "%d", CurHealth);
	_laHealth->setString(s);

	if (CurHealth < _oHealth)
		_laHealth->setColor(Color3B::RED);
	else if (CurHealth == _oHealth)
		_laHealth->setColor(Color3B::WHITE);
	else
	{
		BoardEffect::getInstance()->addEffect(EFFECT_BUFF, -1, NULL, this);
		_laHealth->setColor(Color3B::GREEN);
	}
}


//*设置当前攻击为CurAttack
//*每当当前攻击发生改变需要调用，改变图像上的显示
void BoardCard::setCurrentAttack(int CurAttack)
{
	_curAttack = CurAttack;
	char s[3];
	sprintf(s, "%d", CurAttack);
	_laAttack->setString(s);
	if (CurAttack>_oAttack)
		_laAttack->setColor(Color3B::GREEN);
	else if (CurAttack < _oAttack)
		_laAttack->setColor(Color3B::GRAY);
	else
		_laAttack->setColor(Color3B::WHITE);
}

void BoardCard::setCurrentCost(int CurCost)
{
	_curCost = CurCost;
	char s[3];
	sprintf(s, "%d", CurCost);

	_laCost->setString(s);
	if (CurCost>_oCost)
		_laCost->setColor(Color3B::GREEN);
	else if (CurCost < _oCost)
		_laCost->setColor(Color3B::GRAY);
	else
		_laCost->setColor(Color3B::WHITE);
}

void BoardCard::setCurrentArmor(int CurArmor,bool volume)
{
	if (CurArmor>_curArmor&&volume)
	{
		SimpleAudioEngine::getInstance()->playEffect(s_wav_shield);
	}
	_curArmor = CurArmor;
	if (CurArmor)
	{
		_armor->setVisible(true);
		_laArmor->setVisible(true);
		char s[3];
		sprintf(s, "%d", CurArmor);
		_laArmor->setString(s);	
	
	}
	else
	{	
		_armor->setVisible(false);
		_laArmor->setVisible(false);
	}
}
//*卡牌翻面,动画长度为1s
void BoardCard::turnSide(float time)
{

	this->runAction(Sequence::create(RotateBy::create(time/2, Vec3(0, 90, 0)), CallFunc::create(CC_CALLBACK_0(BoardCard::turnSideCallback, this)), RotateBy::create(time/2, Vec3(0, 90, 0)), NULL));
}


//*卡牌翻面的内部回调
void BoardCard::turnSideCallback()
{
	if (this->_normal&&this->_cardBack)
	{
		_cardside = !_cardside;
		this->_normal->setVisible(!this->_normal->isVisible());
		this->_cardBack->setVisible(!this->_cardBack->isVisible());
	}
}
void BoardCard::turnSideNow()
{
	if (this->_normal&&this->_cardBack)
	{
		_cardside = !_cardside;
		this->_normal->setVisible(!this->_normal->isVisible());
		this->_cardBack->setVisible(!this->_cardBack->isVisible());
	}
}

//*卡牌攻击动画,时长为卡牌中心与目标位置（Position）的距离/400 s.
//*返回攻击到达的时间
//*另设有attackHero和attackCard供快捷使用
float BoardCard::attack(Vec2 Position)
{
	auto aa=this->getPositionX();
	int PosX = Position.x-this->getPositionX();
	int PosY = Position.y - this->getPositionY();
	float time = sqrt(PosX*PosX + PosY*PosY) / 400;
	auto action1 = MoveBy::create(time, Vec2(PosX,PosY));
	auto easeaction1 = EaseOut::create(action1, 0.2f);
	auto easeaction2 = EaseIn::create(action1->reverse(), 0.4);
	auto action2 = Sequence::create(easeaction1, easeaction2, NULL);
	this->runAction(action2);
	return time;
}

float BoardCard::getAttackTime(Vec2 pos)
{
	auto aa = this->getPositionX();
	int PosX = pos.x - this->getPositionX();
	int PosY = pos.y - this->getPositionY();
	float time = sqrt(PosX*PosX + PosY*PosY) / 400;
	return time;
}

float BoardCard::getAttackTime(BoardCard* destCard)
{
	return getAttackTime(destCard->getPosition());
}

//*卡牌攻击英雄,参数为目标英雄的阵营
float BoardCard::attackHero(int Dest_Camp)
{
	return attack(Vec2(20, -190 + Dest_Camp * 280));
}


//*卡牌攻击卡牌,参数为目标卡牌的位置和目标卡牌的阵营
float BoardCard::attackCard(int Place, int Dest_Camp)
{
	return attack(Vec2(-155.2 + Place*82.5, -61 + 122 * Dest_Camp));
}

//*卡牌攻击卡牌,参数为目标卡牌
float BoardCard::attackCard(BoardCard* Dest_Card)
{
	return attack(Dest_Card->getPosition());
}


//*从牌库移到手牌里的动画 1s
float BoardCard::transFromDeckToHand(int PosOrder,int TotalNum,int camp)
{

	if (PosOrder > TotalNum )
		return -1;
	float x, y;
	float angle;
	calculatePosAndAngle(PosOrder, TotalNum,angle, x, y,camp);
	if (camp == 0)
	{
		///this->runAction(MoveTo::create(1.f, Vec2(-200+80 * PosOrder, -330)));//移到相应位置
		this->runAction(MoveTo::create(1.f, Vec2(x, y)));//移到相应位置
		this->runAction(Sequence::create(RotateBy::create(0.5f, Vec3(0, 90, -60 + angle / 2)), CallFunc::create(CC_CALLBACK_0(BoardCard::turnSideCallback, this)), RotateBy::create(0.5f, Vec3(0, 90, -30 + angle / 2)), NULL));
		this->runAction(ScaleTo::create(1, 1.2));//缩放
	
		
	}
	else if (camp== 1)
	{
		//this->runAction(MoveTo::create(1.f, Vec2(-200+80*PosOrder, 330)));
		this->runAction(MoveTo::create(1.f, Vec2(x, y)));//移到相应位置
		this->runAction(Sequence::create(RotateBy::create(0.5f, Vec3(0, 0,60 - angle / 2)), RotateBy::create(0.5f, Vec3(0, 0, 30 - angle / 2)), NULL));
		this->runAction(ScaleTo::create(1, 1.2));
	}


	return 1.f;
}




//*从手牌中移入场上
float BoardCard::transFromHandToBattle(int PosOrder,int Camp)
{ 
	if (PosOrder > 5 || PosOrder < 0)
		return -1;
	auto oPos = this->getPosition();
	auto cPos = Vec2(-155.2 + PosOrder*82.5, -61 + 122 * Camp);
	float distance = oPos.getDistance(cPos);
	float speed = 300.0f;
	float time = distance / speed;
	this->runAction(MoveTo::create(time, cPos));
	this->runAction(ScaleTo::create(time, 1.2));
	if (Camp)
	{
		auto a=this->getRotation3D();
		this->runAction(Sequence::create(RotateBy::create(time/2, Vec3(0, 90, 0)), CallFunc::create(CC_CALLBACK_0(BoardCard::turnSideCallback, this)), RotateTo::create(time/2, Vec3(0, 180, 360)), NULL));
	}
	return time;
}


void  BoardCard::calculatePosAndAngle(int place, int size,float &angle, float &x, float &y,int camp)
{
	if (size <= place)
		return;
	
	float a = 290.f;
	float b = 163.f;
	if (size == 1)
	{
		x = 0;
		y = 163 - 480;
		angle = 0;
	}
	else
	{
		angle = (-size * 10 + float(place)/ (size-1) * size*20) / 2;//为夹角的二分之一
		float theta = tan((90 - angle*2) / 180.0*3.1415926);
		x = sqrt(1.0 / (1.0 / (a*a) + theta*theta / (b*b)));
		if (angle < 0)
			x = -x;
		y = x*theta - 480;
	}
	if (camp == 1)
		y = -y;
}