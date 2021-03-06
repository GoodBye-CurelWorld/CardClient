#pragma once
#include"BoardChess.h"
#include"Card.h"
/*卡牌状态*/
#define CARD_STATE_STOKE 0  //卡牌在牌库
#define CARD_STATE_HAND 1   //卡牌在手里
#define CARD_STATE_BATTLE 2 //卡牌在战场上
#define CARD_STATE_DEAD 3   //卡牌在墓地
#define CARD_STATE_UNDEFINE 4 //卡牌状态未定义
/*
*@BoardCard
*@brief Card in board.负责卡牌的显示
*@状态:
*在牌库池 CARD_STATE_STOKE 
*在手牌池 CARD_STATE_HAND
*在战斗池 CARD_STATE_BATTLE
*在墓地池 CARD_STATE_DEAD
*不明	  CARD_STATE_UNDEFINE
*@卡牌构成:
*由卡牌框架,卡牌封面图片1,2,卡背构成
*/
class BoardCard :public BoardChess
{
	friend class GameBoard;
public:
	void initElement(CCard& card);
	virtual void onEnter()override;

	//根据卡牌类的对象来创建对象
	static BoardCard*create(CCard &card);
	//卡牌翻面
	virtual void turnSide(float time=1.f);
	void turnSideNow();
private:
	//设置卡牌当前生命
	void setCurrentHealth(int curhealth);

	//设置卡牌当前攻击
	void setCurrentAttack(int curattack);

	//设置卡牌当前费用
	void setCurrentCost(int curcost);  
	
	//设置卡牌当前护甲
	void setCurrentArmor(int curArmor,bool volume=true);

	//获取卡牌当前护甲
	int getCurrentArmor();

	//卡牌被沉默,删去文字描述
	void silent(); 

	//卡牌死亡,将销毁对象,等同于die()
	void exploside();  

	//卡牌死亡,将销毁对象
	void die();

	

	//*从牌库移到手牌里的动画，目前写到2张卡牌的情况
	//*动画持续1s
	float transFromDeckToHand(int PosOrder, int TotalNum, int Camp = 0);
	//从手牌移到战场 ，1s
	float transFromHandToBattle(int PosOrder,int Camp=0); 

	void removeToHand(int posOrder);


	//攻击
	float attack(Vec2 Position);
	float attackHero(int Dest_Camp);
	float attackCard(int Place, int Dest_Camp);
	float attackCard(BoardCard* Dest_Card);
	float getAttackTime(Vec2 pos);
	float getAttackTime(BoardCard* destCard);
	//get，set函数。。。以后补																
	//void setAttack(int attcak);
	//int  getAttack();

	void setCardState(int state);
	int getCardState();

	CCard *_card;
	bool _cardside;
public:
	Sprite *_frame;

private:
	void calculatePosAndAngle(int place,int size,float &angle,float &x,float &y,int camp=0);
private:
	
	Sprite  *_normal,*_battle, *_cardBack;//普通,战斗，卡背
	Sprite *_armor;
	Label *_laAttack, *_laHealth, *_laCost, *_laDescription,*_laName,*_laArmor;
private:
	int _state;  //状态
	int _curHealth, _curAttack, _curCost,_curArmor;
	int _oHealth, _oAttack, _oCost,_oArmor;
	void turnSideCallback();
};