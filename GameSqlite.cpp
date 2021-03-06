#include "GameSqlite.h"


GameSqlite::GameSqlite()
{
	Sql_group[0] = "D://xx//cocos//Dcg_database_Card.db";
	Sql_group[1] = "D://xx//cocos//Dcg_database_Character.db";
	Sql_group[2] = "D://xx//cocos//Dcg_database_Skill.db";
	Sql_group[3] = "";
	Sql_group[4] = "";
	Sql_group[5] = "";
	Sql_group[6] = "";
	
	
	//sqlite3_open("D://xx//cocos//CardGame//Resources//sql//Dcg_database_Card", &sql[0]);
	//sqlite3_open("D://xx//cocos//CardGame//Resources//sql//Dcg_database_Users", &sql[1]);
	//sqlite3_open("D://xx//cocos//CardGame//Resources//sql//Dcg_database_Link_UsersCardArray", &sql[2]);
	//sqlite3_open("D://xx//cocos//CardGame//Resources//sql//Dcg_database_Link_UsersCard", &sql[3]);
	//sqlite3_open("D://xx//cocos//CardGame//Resources//sql//Dcg_database_CardArray", &sql[4]);
	sqlite3_open("sql/Dcg_database_Card", &sql[0]);
	sqlite3_open("sql/Dcg_database_Users", &sql[1]);
	sqlite3_open("sql/Dcg_database_Link_UsersCardArray", &sql[2]);
	sqlite3_open("sql/Dcg_database_Link_UsersCard", &sql[3]);
	sqlite3_open("sql/Dcg_database_CardArray", &sql[4]);
	//sqlite3_open("sql/Dcg_database_Character", &sql[1]);
	//sqlite3_open("sql/Dcg_database_Skill", &sql[2]);
	//SetData();
}


GameSqlite::~GameSqlite()
{}

//接口函数
/********************************************************/
//卡牌
char*	GameSqlite::getCardData(int ID, int Type)
{
	int i = WITCHCRAFT;
	char **errmsg = NULL;
	//ID的转换int->string
	char s[10];
	sprintf(s, "%d", ID);

	string sqlstr, sqlstr1 = s;
	//获得SQL指令
	sqlstr = "select * from sqlTable where ID=" + sqlstr1;

	Sql_Type = SQL_CARD;
	//sqlite3_exec(sql[0], sqlstr.c_str(), GameSqlite::loadRecord, NULL, errmsg);

	//获得相应ID的字段，并存入Column_Value中
	char** Column_Value = { '\0' };
	int count, r, c;
	sqlite3_get_table(sql[Sql_Type], sqlstr.c_str(), &Column_Value, &r, &c, NULL);

	//将Column_Value中的每个值分别存入相应的参数中
	return Column_Value[c+Type];

}

vector<char *>	GameSqlite::selectCardData(int Type, string number)
{
	string sqlstr;
	//获得SQL指令
	sqlstr = "select * from sqlTable where ID=" + number;
					
				

	switch (Type)
	{
	case	CARD_ID:
		sqlstr = "select * from sqlTable where ID=" + number;
		break;
	case	CARD_NAME:
		sqlstr = "select * from sqlTable where CardName=" + number;
		break;
	case	CARD_COST:
		sqlstr = "select * from sqlTable where Cost=" + number;
		break;
	case	CARD_HEALTH:
		sqlstr = "select * from sqlTable where Health=" + number;
		break;
	case	CARD_ATTACK:
		sqlstr = "select * from sqlTable where Attack=" + number;
		break;
	case	CARD_DESCRIBE:
		sqlstr = "select * from sqlTable where CardDescribe=" + number;
		break;
	case	CARD_QUALITY:
		sqlstr = "select * from sqlTable where Quality=" + number;
		break;
	case	CARD_SPELL_1:
		sqlstr = "select * from sqlTable where Spell0=" + number;
		break;
	case	CARD_SPELL_2:
		sqlstr = "select * from sqlTable where Spell1=" + number;
		break;
	case	CARD_SPELL_3:
		sqlstr = "select * from sqlTable where Spell2=" + number;
		break;
	case	CARD_SPELL_4:
		sqlstr = "select * from sqlTable where Spell3=" + number;
		break;
	
		default:
			break;
	}




	//获得相应ID的字段，并存入Column_Value中
	char** Column_Value = { '\0' };

	//c内存字段的条数，r内存搜索结果的数量
	int  r, c;
	Sql_Type = SQL_CARD;	
	
	//用来储存结果
	vector<char*> relust;
	
	
	sqlite3_get_table(sql[Sql_Type], sqlstr.c_str(), &Column_Value, &r, &c, NULL);


	for (int i = 1; i <= r; i++)
		relust.push_back(Column_Value[i*c]);
		
	cout << r << endl;
	
	return relust;
}


/*********************************************************/
//用户
char* GameSqlite::getUsersID(string Account)
{
	char **errmsg = NULL;


	string sqlstr;
	//获得SQL指令
	sqlstr = "select * from sqlTable where Account='" + Account+"'";

	Sql_Type = SQL_USERS;

	//获得相应ID的字段，并存入Column_Value中
	char** Column_Value = { '\0' };
	int count, r, c;
	sqlite3_get_table(sql[Sql_Type], sqlstr.c_str(), &Column_Value, &r, &c, NULL);

	//将Column_Value中的每个值分别存入相应的参数中
	return Column_Value[c + CARD_ID];
}

char* GameSqlite::getUsersData(string ID, int type)
{
	
	char **errmsg = NULL;

	string sqlstr;
	sqlstr = "select * from sqlTable where ID=" + ID;
	
	Sql_Type = SQL_USERS;


	//获得相应ID的字段，并存入Column_Value中
	char** Column_Value = { '\0' };
	int count, r, c;
	sqlite3_get_table(sql[Sql_Type], sqlstr.c_str(), &Column_Value, &r, &c, NULL);

	//将Column_Value中的每个值分别存入相应的参数中
	return Column_Value[c + type];

}

void GameSqlite::upDateUserData(string ID, int type, string src)
{
	char **errmsg = NULL;

	string sqlstr;
	switch (type)
	{
	case	USER_ID:
		sqlstr = "update sqlTable set ID=" + src + " where ID=" + ID;
		break;
	case	USER_ACCOUNT:
		sqlstr = "update sqlTable set Account='" + src + "' where ID=" + ID;
		break;
	case	USER_PASSWORD:
		sqlstr = "update sqlTable set PassWord='" + src + "' where ID=" + ID;
		break;
	case	USER_NAME:
		sqlstr = "update sqlTable set UserName='" + src + "' where ID=" + ID;
		break;
	case	USER_MONEY:
		sqlstr = "update sqlTable set Money=" + src + " where ID=" + ID;
		break;	

	default:
		break;
	}

	Sql_Type = SQL_USERS;


	//获得相应ID的字段，并存入Column_Value中
	char** Column_Value = { '\0' };
	int count, r, c;
	sqlite3_get_table(sql[Sql_Type], sqlstr.c_str(), &Column_Value, &r, &c, NULL);
}


/***************************************************/
//用户和卡组的link,包括卡组本身的数据
vector<int>		GameSqlite::getUserAllArray(int UserID)			//返回卡组ID
{
	char **errmsg = NULL;
	char s[10];
	sprintf(s, "%d", UserID);
	string s_userID = s;
	string sqlstr;
	//获得SQL指令
	sqlstr = "select * from sqlTable where UsersID=" + s_userID;

	//获得相应ID的字段，并存入Column_Value中
	char** Column_Value = { '\0' };
	//c内存字段的条数，r内存搜索结果的数量
	int  r, c;
	Sql_Type = SQL_LINK_USERCARDARRAY;
	sqlite3_get_table(sql[Sql_Type], sqlstr.c_str(), &Column_Value, &r, &c, NULL);

	//用来储存结果
	vector<int> relust;

	for (int i = 1; i <= r; i++)
		relust.push_back(atoi(Column_Value[i*c]));

	cout << r << endl;

	return relust;

}
int				GameSqlite::getArrayID(string ArrayName)
{
	char **errmsg = NULL;
	string sqlstr;
	//获得SQL指令
	sqlstr = "select * from sqlTable where CardArrayName='" + ArrayName + "'";

	Sql_Type = SQL_LINK_USERCARDARRAY;

	//获得相应ID的字段，并存入Column_Value中
	char** Column_Value = { '\0' };
	int count, r, c;
	sqlite3_get_table(sql[Sql_Type], sqlstr.c_str(), &Column_Value, &r, &c, NULL);

	//将Column_Value中的每个值分别存入相应的参数中
	return atoi(Column_Value[c + ARRAY_ID]);
}
char*			GameSqlite::getArrayData(int ID, int Type)
{
	char **errmsg = NULL;
	char s[10];
	sprintf(s, "%d", ID);
	string s_ID = s;
	string sqlstr;
	//获得SQL指令
	sqlstr = "select * from sqlTable where ID=" + s_ID;

	Sql_Type = SQL_LINK_USERCARDARRAY;


	//获得相应ID的字段，并存入Column_Value中
	char** Column_Value = { '\0' };
	int count, r, c;
	sqlite3_get_table(sql[Sql_Type], sqlstr.c_str(), &Column_Value, &r, &c, NULL);

	//将Column_Value中的每个值分别存入相应的参数中
	return Column_Value[c + Type];
}
void			GameSqlite::upDateArrayData(int ID, int type, string src)
{
	char **errmsg = NULL;
	char s[10];
	sprintf(s, "%d", ID);
	string s_ID = s;
	string sqlstr;
	//获得SQL指令
	sqlstr = "select * from sqlTable where ID=" + s_ID;

	switch (type)
	{
	case ARRAY_NAME:
		sqlstr = "update sqlTable set CardArrayName='" + src + "' where ID=" + s_ID;
		break;
	case ARRAY_ROLEID:
		sqlstr = "update sqlTable set RoleID=" + src + " where ID=" + s_ID;
		break;
	case ARRAY_USERID:
		sqlstr = "update sqlTable set UsersID=" + src + " where ID=" + s_ID;
		break;
	default:
		break;
	}	
	
	Sql_Type = SQL_LINK_USERCARDARRAY;
	
	//获得相应ID的字段，并存入Column_Value中
	char** Column_Value = { '\0' };
	int count, r, c;
	sqlite3_get_table(sql[Sql_Type], sqlstr.c_str(), &Column_Value, &r, &c, NULL);
}
void			GameSqlite::addCardArray(int UserID, int RoleID, string CardArrayName)
{
	char **errmsg = NULL;
	char s[10];
	sprintf(s, "%d", UserID);
	string s_userID = s;
	sprintf(s, "%d", RoleID);
	string s_roleID = s;

	string sqlstr;
	sqlstr = "insert into sqlTable( UsersID, RoleID, CardArrayName) values(" + s_userID + "," + s_roleID + ",'" + CardArrayName + "')";
	sqlite3_exec(sql[2], sqlstr.c_str(), NULL, NULL, errmsg);

}
void			GameSqlite::delCardArray(int ID)
{
	char **errmsg = NULL;
	char s[10];
	sprintf(s, "%d", ID);
	string s_ID = s;
	string sqlstr;

	//同时删除卡组数据库中相关卡组的所有卡牌信息
	vector<int> ArrayCard;
	ArrayCard = GameSqlite::getArrayAllCard(ID);
	for (int i = 0; i < ArrayCard.size(); i++)
	{
		GameSqlite::delArrayCard(ID, ArrayCard.at(i) % 10000000);
	}

	//删除该卡组
	//获得SQL指令
	sqlstr = "delete from sqlTable where ID=" + s_ID;

	Sql_Type = SQL_LINK_USERCARDARRAY;

	//获得相应ID的字段，并存入Column_Value中
	char** Column_Value = { '\0' };
	int count, r, c;
	sqlite3_get_table(sql[Sql_Type], sqlstr.c_str(), &Column_Value, &r, &c, NULL);

	

}

/**********************************************************/
//用户和卡牌的link操作
vector<int>		GameSqlite::getUserAllCard(int UserID)
{
	char **errmsg = NULL;
	char s[10];
	sprintf(s, "%d", UserID);
	string s_userID = s;
	string sqlstr;
	//获得SQL指令
	sqlstr = "select * from sqlTable where UsersID=" + s_userID;

	//获得相应ID的字段，并存入Column_Value中
	char** Column_Value = { '\0' };
	//c内存字段的条数，r内存搜索结果的数量
	int  r, c;
	Sql_Type = SQL_LINK_USERCARD;
	sqlite3_get_table(sql[Sql_Type], sqlstr.c_str(), &Column_Value, &r, &c, NULL);

	//用来储存结果
	vector<int> relust;

	for (int i = 1; i <= r; i++)
		relust.push_back(atoi(Column_Value[i*c + 2]) + atoi(Column_Value[i*c + 3]) * 10000000);

	cout << r << endl;

	return relust;
}
void			GameSqlite::addUserCard(int CardID, int UserID)
{
	char **errmsg = NULL;
	char s[10];
	sprintf(s, "%d", UserID);
	string s_userID = s;
	sprintf(s, "%d", CardID);
	string s_cardID = s;

	string sqlstr;
	//先查找，如果有number+1，没有新增数据	
	sqlstr = "select * from sqlTable where UsersID=" + s_userID + " and CardID=" + s_cardID;

	//获得相应ID的字段，并存入Column_Value中
	char** Column_Value = { '\0' };
	//c内存字段的条数，r内存搜索结果的数量
	int  r, c;
	Sql_Type = SQL_LINK_USERCARD;
	sqlite3_get_table(sql[Sql_Type], sqlstr.c_str(), &Column_Value, &r, &c, NULL);
	
	//用户没有对应的卡
	if (r == 0)
	{
		sqlstr = "insert into sqlTable( UsersID, CardID, CardNumber) values(" + s_userID + "," + s_cardID + "," + "1" + ")";
		sqlite3_exec(sql[3], sqlstr.c_str(), NULL, NULL, errmsg);
	}
	else
	{
		sqlstr = "update sqlTable set CardNumber=CardNumber+1 where UsersID=" + s_userID + " and CardID=" + s_cardID;
		sqlite3_get_table(sql[3], sqlstr.c_str(), &Column_Value, &r, &c, NULL);
	}
}

/******************************************************/
//卡组
vector<int>		GameSqlite::getArrayAllCard(int ArrayID)
{
	char **errmsg = NULL;
	char s[10];
	sprintf(s, "%d", ArrayID);
	string s_arrayID = s;
	string sqlstr;
	//获得SQL指令
	sqlstr = "select * from sqlTable where ArrayID=" + s_arrayID;

	//获得相应ID的字段，并存入Column_Value中
	char** Column_Value = { '\0' };
	//c内存字段的条数，r内存搜索结果的数量
	int  r, c;
	Sql_Type = SQL_CARDARRAY;
	sqlite3_get_table(sql[Sql_Type], sqlstr.c_str(), &Column_Value, &r, &c, NULL);

	//用来储存结果
	vector<int> relust;

	for (int i = 1; i <= r; i++)
		relust.push_back(atoi(Column_Value[i*c + 2]) + atoi(Column_Value[i*c + 3]) * 10000000);

	cout << r << endl;

	return relust;
	
}
void			GameSqlite::addArrayCard(int ArrayID, int CardID)
{
	char **errmsg = NULL;
	char s[10];
	sprintf(s, "%d", ArrayID);
	string s_arrayID = s;
	sprintf(s, "%d", CardID);
	string s_cardID = s;

	string sqlstr;
	//先查找，如果有number+1，没有新增数据	
	sqlstr = "select * from sqlTable where ArrayID=" + s_arrayID + " and CardID=" + s_cardID;

	//获得相应ID的字段，并存入Column_Value中
	char** Column_Value = { '\0' };
	//c内存字段的条数，r内存搜索结果的数量
	int  r, c;
	Sql_Type = SQL_CARDARRAY;
	sqlite3_get_table(sql[Sql_Type], sqlstr.c_str(), &Column_Value, &r, &c, NULL);

	//用户没有对应的卡
	if (r == 0)
	{
		sqlstr = "insert into sqlTable( ArrayID, CardID, CardNumber) values(" + s_arrayID + "," + s_cardID + "," + "1" + ")";
		sqlite3_exec(sql[Sql_Type], sqlstr.c_str(), NULL, NULL, errmsg);
	}
	else
	{
		sqlstr = "update sqlTable set CardNumber=CardNumber+1 where ArrayID=" + s_arrayID + " and CardID=" + s_cardID;
		sqlite3_get_table(sql[Sql_Type], sqlstr.c_str(), &Column_Value, &r, &c, NULL);
	}
}
void			GameSqlite::delArrayCard(int ArrayID, int CardID)
{
	char **errmsg = NULL;
	char s[10];
	sprintf(s, "%d", ArrayID);
	string s_arrayID = s;
	sprintf(s, "%d", CardID);
	string s_cardID = s;

	string sqlstr;
	sqlstr = "delete from sqlTable where ArrayID=" + s_arrayID + " and CardID=" + s_cardID;

	//获得相应ID的字段，并存入Column_Value中
	char** Column_Value = { '\0' };
	//c内存字段的条数，r内存搜索结果的数量
	int  r, c;
	Sql_Type = SQL_CARDARRAY;
	sqlite3_get_table(sql[Sql_Type], sqlstr.c_str(), &Column_Value, &r, &c, NULL);
}
/******************************************************/
//设置数据
//卡牌
void GameSqlite::SetData()
{
	//char **errmsg = NULL;
	//sqlite3_exec(sql[0], "create table Table( ID integer ,CardName nvarchar(32), Cost integer, Health integer, Attack integer,CardDescribe nvarchar(32), Quality integer,Spell0 integer,Spell1 nvarchar(32),Spell2 integer,Spell3 integer,GraphPath1 nvarchar(32),GraphPath2 nvarchar(32))", NULL, NULL, errmsg);
	////法术
	//sqlite3_exec(sql[0], "insert into Table(ID,CardName, Cost, Health, Attack, CardDescribe, Quality, Spell0,Spell1,Spell2,Spell3,GraphPath1,GraphPath2) values()", 0, 0, errmsg);
	//sqlite3_exec(sql[0], "insert into Table(ID,CardName, Cost, Health, Attack, CardDescribe, Quality, Spell0,Spell1,Spell2,Spell3,GraphPath1,GraphPath2) values()", 0, 0, errmsg);


	////技能
	///************************************************************************************/

	char **errmsg = NULL;
	sqlite3_exec(sql[0], "create table sqlTable( ID integer ,CardName nvarchar(32), Cost integer, Health integer, Attack integer,CardDescribe nvarchar(32), Quality integer,Spell0 integer,Spell1 nvarchar(32),Spell2 integer,Spell3 integer,GraphPath1 nvarchar(32),GraphPath2 nvarchar(32))", NULL, NULL, errmsg);
	/*sqlite3_exec(sql[0], "select * from sqlTable ", GameSqlite::loadRecord, NULL, errmsg);*/
	//*************************************************************************************//
	
	//随从
	sqlite3_exec(sql[0], "insert into sqlTable(ID,CardName, Cost, Health, Attack, CardDescribe, Quality, Spell0,Spell1,Spell2,Spell3,GraphPath1,GraphPath2) values(0110000,'黑市刺客',4,1,1,'战吼：消灭所有受伤的敌方随从',0,300002,2,3,4,7,7)", 0, 0, errmsg);
	sqlite3_exec(sql[0], "insert into sqlTable(ID,CardName, Cost, Health, Attack, CardDescribe, Quality, Spell0,Spell1,Spell2,Spell3,GraphPath1,GraphPath2) values(0110001,'贪婪的佣兵',2,5,5,'回合开始失去两点能量',0,301000,2,3,4,7,7)", 0, 0, errmsg);
	sqlite3_exec(sql[0], "insert into sqlTable(ID,CardName, Cost, Health, Attack, CardDescribe, Quality, Spell0,Spell1,Spell2,Spell3,GraphPath1,GraphPath2) values(0110002,'熟练的冒险者',5,6,7,'',0,6904001,2,3,4,7,7)", 0, 0, errmsg);
	sqlite3_exec(sql[0], "insert into sqlTable(ID,CardName, Cost, Health, Attack, CardDescribe, Quality, Spell0,Spell1,Spell2,Spell3,GraphPath1,GraphPath2) values(0110003,'探险专家',3,1,1,'若回合内放弃攻击，回合结束抽一张牌',0,302003,2,3,4,7,7)", 0, 0, errmsg);
	sqlite3_exec(sql[0], "insert into sqlTable(ID,CardName, Cost, Health, Attack, CardDescribe, Quality, Spell0,Spell1,Spell2,Spell3,GraphPath1,GraphPath2) values(0110004,'年迈的神父',6,4,7,'回合结束,回复所有友方随从2点生命',0,303003,2,3,4,7,7)", 0, 0, errmsg);
	sqlite3_exec(sql[0], "insert into sqlTable(ID,CardName, Cost, Health, Attack, CardDescribe, Quality, Spell0,Spell1,Spell2,Spell3,GraphPath1,GraphPath2) values(0110005,'酒馆暴徒',2,4,2,'冲锋',0,701002,2,3,4,7,7)", 0, 0, errmsg);
	sqlite3_exec(sql[0], "insert into sqlTable(ID,CardName, Cost, Health, Attack, CardDescribe, Quality, Spell0,Spell1,Spell2,Spell3,GraphPath1,GraphPath2) values(0110006,'酒馆保镖',6,6,5,'战吼:眩晕一个敌方随从，并造成两点伤害',0,304102,2,3,4,7,7)", 0, 0, errmsg);
	sqlite3_exec(sql[0], "insert into sqlTable(ID,CardName, Cost, Health, Attack, CardDescribe, Quality, Spell0,Spell1,Spell2,Spell3,GraphPath1,GraphPath2) values(0110007,'魔导师阿塔尼斯',9,9,9,'战吼：将所有敌方随从的变成1/1',0,305002,2,3,4,7,7)", 0, 0, errmsg);

	///战士5801003
	//sqlite3_exec(sql[0], "insert into sqlTable(ID,CardName, Cost, Health, Attack, CardDescribe, Quality, Spell0,Spell1,Spell2,Spell3,GraphPath1,GraphPath2) values(0000000,'低阶步兵',0,1,1,'护甲1',0,3703001,2,3,4,7,7)", 0, 0, errmsg);
	sqlite3_exec(sql[0], "insert into sqlTable(ID,CardName, Cost, Health, Attack, CardDescribe, Quality, Spell0,Spell1,Spell2,Spell3,GraphPath1,GraphPath2) values(0000000,'低阶步兵',0,1,1,'护甲1',0,1600002,2,3,4,7,7)", 0, 0, errmsg);
	sqlite3_exec(sql[0], "insert into sqlTable(ID,CardName, Cost, Health, Attack, CardDescribe, Quality, Spell0,Spell1,Spell2,Spell3,GraphPath1,GraphPath2) values(0000001,'提枪侍从',1,3,1,'降临：使英雄的装备获得耐久+1',0,5802002,2,3,4,7,7)", 0, 0, errmsg);
	sqlite3_exec(sql[0], "insert into sqlTable(ID,CardName, Cost, Health, Attack, CardDescribe, Quality, Spell0,Spell1,Spell2,Spell3,GraphPath1,GraphPath2) values(0000002,'装甲锻造者',3,3,3,'降临：使一名随从获得护甲+2',0,2601802,2,3,4,7,7)", 0, 0, errmsg);
	sqlite3_exec(sql[0], "insert into sqlTable(ID,CardName, Cost, Health, Attack, CardDescribe, Quality, Spell0,Spell1,Spell2,Spell3,GraphPath1,GraphPath2) values(0000003,'巨人战士',5,3,4,'降临：眩晕一个随从直到你的下个回合开始',1,1602902,2,3,4,7,7)", 0, 0, errmsg);
	sqlite3_exec(sql[0], "insert into sqlTable(ID,CardName, Cost, Health, Attack, CardDescribe, Quality, Spell0,Spell1,Spell2,Spell3,GraphPath1,GraphPath2) values(0000004,'英灵',6,5,7,'返场：6',1,6904001,2,3,4,7,7)", 0, 0, errmsg);
	sqlite3_exec(sql[0], "insert into sqlTable(ID,CardName, Cost, Health, Attack, CardDescribe, Quality, Spell0,Spell1,Spell2,Spell3,GraphPath1,GraphPath2) values(0000005,'铁甲武士',8,7,7,'每个回合结束获得护甲+2',1,2603001,2,3,4,7,7)", 0, 0, errmsg);
	sqlite3_exec(sql[0], "insert into sqlTable(ID,CardName, Cost, Health, Attack, CardDescribe, Quality, Spell0,Spell1,Spell2,Spell3,GraphPath1,GraphPath2) values(0000006,'前线指挥官',2,3,3,'友方角色每有一点护甲值，获得+1攻击力',2,1604099,2,3,4,7,7)", 0, 0, errmsg);
	sqlite3_exec(sql[0], "insert into sqlTable(ID,CardName, Cost, Health, Attack, CardDescribe, Quality, Spell0,Spell1,Spell2,Spell3,GraphPath1,GraphPath2) values(0000007,'铁骑',4,1,5,'友方角色每有一点护甲值，获得+1攻击力',2,5001002,2,3,4,7,7)", 0, 0, errmsg);
	sqlite3_exec(sql[0], "insert into sqlTable(ID,CardName, Cost, Health, Attack, CardDescribe, Quality, Spell0,Spell1,Spell2,Spell3,GraphPath1,GraphPath2) values(0000008,'战神',11,10,10,'护甲4 随从豁免 攻击反制',3,4001002,90199,3,4,7,7)", 0, 0, errmsg);
	
	//弓箭手
	sqlite3_exec(sql[0], "insert into sqlTable(ID,CardName, Cost, Health, Attack, CardDescribe, Quality, Spell0,Spell1,Spell2,Spell3,GraphPath1,GraphPath2) values(0010000,'侦查鹰',1,4,0,'友方所有其他随从攻击加1',0,1700002,2,3,4,7,7)", 0, 0, errmsg);
	sqlite3_exec(sql[0], "insert into sqlTable(ID,CardName, Cost, Health, Attack, CardDescribe, Quality, Spell0,Spell1,Spell2,Spell3,GraphPath1,GraphPath2) values(0010001,'猎鹰',2,1,3,'冲锋',0,1709002,2,3,4,7,7)", 0, 0, errmsg);
	sqlite3_exec(sql[0], "insert into sqlTable(ID,CardName, Cost, Health, Attack, CardDescribe, Quality, Spell0,Spell1,Spell2,Spell3,GraphPath1,GraphPath2) values(0010002,'见习游侠',0,1,2,'降临：造成1点伤害',0,1707902,2,3,4,7,7)", 0, 0, errmsg);
	sqlite3_exec(sql[0], "insert into sqlTable(ID,CardName, Cost, Health, Attack, CardDescribe, Quality, Spell0,Spell1,Spell2,Spell3,GraphPath1,GraphPath2) values(0010003,'神射手',3,3,4,'降临：对一个角色造成2点伤害',1,1707902,2,3,4,7,7)", 0, 0, errmsg);
	sqlite3_exec(sql[0], "insert into sqlTable(ID,CardName, Cost, Health, Attack, CardDescribe, Quality, Spell0,Spell1,Spell2,Spell3,GraphPath1,GraphPath2) values(0010004,'重弩手',4,4,5,'攻击产生晕眩效果',0,2702004,2,3,4,7,7)", 0, 0, errmsg);
	sqlite3_exec(sql[0], "insert into sqlTable(ID,CardName, Cost, Health, Attack, CardDescribe, Quality, Spell0,Spell1,Spell2,Spell3,GraphPath1,GraphPath2) values(0010005,'美杜莎',7,4,3,'降临：石化1个随从',2,1711902,2,3,4,7,7)", 0, 0, errmsg);
	sqlite3_exec(sql[0], "insert into sqlTable(ID,CardName, Cost, Health, Attack, CardDescribe, Quality, Spell0,Spell1,Spell2,Spell3,GraphPath1,GraphPath2) values(0010006,'迫击炮小队',7,7,5,'回合结束时对随机1个敌方角色造成3点伤害',0,3703001,2,3,4,7,7)", 0, 0, errmsg);
	sqlite3_exec(sql[0], "insert into sqlTable(ID,CardName, Cost, Health, Attack, CardDescribe, Quality, Spell0,Spell1,Spell2,Spell3,GraphPath1,GraphPath2) values(0010007,'风行者',5,3,5,'一回合可以攻击两次',2,1708002,2,3,4,7,7)", 0, 0, errmsg);
	sqlite3_exec(sql[0], "insert into sqlTable(ID,CardName, Cost, Health, Attack, CardDescribe, Quality, Spell0,Spell1,Spell2,Spell3,GraphPath1,GraphPath2) values(0010008,'魔羽',11,12,8,'降临：晕眩场上所有随从',3,1705002,2,3,4,7,7)", 0, 0, errmsg);
	sqlite3_exec(sql[0], "insert into sqlTable(ID,CardName, Cost, Health, Attack, CardDescribe, Quality, Spell0,Spell1,Spell2,Spell3,GraphPath1,GraphPath2) values(0010009,'游侠首领',2,3,2,'降临：使他左右的随从攻击+1',1,1706002,2,3,4,7,7)", 0, 0, errmsg);
	sqlite3_exec(sql[0], "insert into sqlTable(ID,CardName, Cost, Health, Attack, CardDescribe, Quality, Spell0,Spell1,Spell2,Spell3,GraphPath1,GraphPath2) values(0010010,'暗影射手',3,4,3,'降临：当前回合使一个随从攻击减3',1,3712102,2,3,4,7,7)", 0, 0, errmsg);

	//中立																																									
	sqlite3_exec(sql[0], "insert into sqlTable(ID,CardName, Cost, Health, Attack, CardDescribe, Quality, Spell0,Spell1,Spell2,Spell3,GraphPath1,GraphPath2) values(0100000,'冒险家',1,2,1,'降临：抽1张牌',1,1,2,3,4,7,7)", 0, 0, errmsg);
	sqlite3_exec(sql[0], "insert into sqlTable(ID,CardName, Cost, Health, Attack, CardDescribe, Quality, Spell0,Spell1,Spell2,Spell3,GraphPath1,GraphPath2) values(0100001,'毒刺蜂',2,2,5,'每个回合结束获得护甲+2',1,1,2,3,4,7,7)", 0, 0, errmsg);
	sqlite3_exec(sql[0], "insert into sqlTable(ID,CardName, Cost, Health, Attack, CardDescribe, Quality, Spell0,Spell1,Spell2,Spell3,GraphPath1,GraphPath2) values(0100002,'XX村守卫',4,6,3,'嘲讽',2,1,2,3,4,7,7)", 0, 0, errmsg);
	sqlite3_exec(sql[0], "insert into sqlTable(ID,CardName, Cost, Health, Attack, CardDescribe, Quality, Spell0,Spell1,Spell2,Spell3,GraphPath1,GraphPath2) values(0100003,'持伞少女',3,4,2,'攻击可对相邻随从造成伤害',1,1,2,3,4,7,7)", 0, 0, errmsg);
	sqlite3_exec(sql[0], "insert into sqlTable(ID,CardName, Cost, Health, Attack, CardDescribe, Quality, Spell0,Spell1,Spell2,Spell3,GraphPath1,GraphPath2) values(0100004,'市井强盗',3,3,3,'冲锋',1,1,2,3,4,7,7)", 0, 0, errmsg);
	sqlite3_exec(sql[0], "insert into sqlTable(ID,CardName, Cost, Health, Attack, CardDescribe, Quality, Spell0,Spell1,Spell2,Spell3,GraphPath1,GraphPath2) values(0100005,'下水道老鼠',0,1,2,'每个回合结束获得护甲+2',0,1,2,3,4,7,7)", 0, 0, errmsg);
	sqlite3_exec(sql[0], "insert into sqlTable(ID,CardName, Cost, Health, Attack, CardDescribe, Quality, Spell0,Spell1,Spell2,Spell3,GraphPath1,GraphPath2) values(0100006,'长尾猫',2,4,3,'友方角色每有一点护甲值，获得+1攻击力',0,1,2,3,4,7,7)", 0, 0, errmsg);
	sqlite3_exec(sql[0], "insert into sqlTable(ID,CardName, Cost, Health, Attack, CardDescribe, Quality, Spell0,Spell1,Spell2,Spell3,GraphPath1,GraphPath2) values(0100007,'花妖',1,3,2,'护甲4 随从豁免 攻击反制',0,1,2,3,4,7,7)", 0, 0, errmsg);
	sqlite3_exec(sql[0], "insert into sqlTable(ID,CardName, Cost, Health, Attack, CardDescribe, Quality, Spell0,Spell1,Spell2,Spell3,GraphPath1,GraphPath2) values(0100008,'哭泣的灵魂',5,5,4,'遗言：对随机敌人1~3点伤害；随从豁免',1,1,2,3,4,7,7)", 0, 0, errmsg);
		
	//Boss 0110000
	sqlite3_exec(sql[0], "insert into sqlTable(ID,CardName, Cost, Health, Attack, CardDescribe, Quality, Spell0,Spell1,Spell2,Spell3,GraphPath1,GraphPath2) values(0110000,'哭泣的灵魂',4,1,1,'战吼：消灭所有受伤的敌方随从',1,300002,2,3,4,7,7)", 0, 0, errmsg);
	sqlite3_exec(sql[0], "insert into sqlTable(ID,CardName, Cost, Health, Attack, CardDescribe, Quality, Spell0,Spell1,Spell2,Spell3,GraphPath1,GraphPath2) values(0110001,'哭泣的灵魂',2,5,5,'回合开始失去两点能量',1,301000,2,3,4,7,7)", 0, 0, errmsg);
	sqlite3_exec(sql[0], "insert into sqlTable(ID,CardName, Cost, Health, Attack, CardDescribe, Quality, Spell0,Spell1,Spell2,Spell3,GraphPath1,GraphPath2) values(0110002,'哭泣的灵魂',5,7,6,'遗言',1,1,2,3,4,7,7)", 0, 0, errmsg);
	sqlite3_exec(sql[0], "insert into sqlTable(ID,CardName, Cost, Health, Attack, CardDescribe, Quality, Spell0,Spell1,Spell2,Spell3,GraphPath1,GraphPath2) values(0110003,'哭泣的灵魂',3,1,1,'若回合内放弃攻击，回合结束抽一张牌',1,302003,2,3,4,7,7)", 0, 0, errmsg);
	sqlite3_exec(sql[0], "insert into sqlTable(ID,CardName, Cost, Health, Attack, CardDescribe, Quality, Spell0,Spell1,Spell2,Spell3,GraphPath1,GraphPath2) values(0110004,'哭泣的灵魂',6,7,4,'回合结束 回复所有友方随从2点生命',1,303003,2,3,4,7,7)", 0, 0, errmsg);
	sqlite3_exec(sql[0], "insert into sqlTable(ID,CardName, Cost, Health, Attack, CardDescribe, Quality, Spell0,Spell1,Spell2,Spell3,GraphPath1,GraphPath2) values(0110005,'哭泣的灵魂',2,2,4,'冲锋',1,701002,2,3,4,7,7)", 0, 0, errmsg);
	sqlite3_exec(sql[0], "insert into sqlTable(ID,CardName, Cost, Health, Attack, CardDescribe, Quality, Spell0,Spell1,Spell2,Spell3,GraphPath1,GraphPath2) values(0110006,'哭泣的灵魂',6,5,6,'战吼，眩晕一个敌方随从，并对他造成两点伤害',1,304102,2,3,4,7,7)", 0, 0, errmsg);
	sqlite3_exec(sql[0], "insert into sqlTable(ID,CardName, Cost, Health, Attack, CardDescribe, Quality, Spell0,Spell1,Spell2,Spell3,GraphPath1,GraphPath2) values(0110007,'哭泣的灵魂',9,9,9,'战吼：将所有敌方随从的变成1/1',1,305002,2,3,4,7,7)", 0, 0, errmsg);

	//法术
	//战士
	sqlite3_exec(sql[0], "insert into sqlTable(ID,CardName, Cost, Health, Attack, CardDescribe, Quality, Spell0,Spell1,Spell2,Spell3,GraphPath1,GraphPath2) values(0001000,'重返战场',0,0,0,'回复一名随从所有生命值，并使其获得护甲+1',0,620807,2,3,4,7,7)", 0, 0, errmsg);
	sqlite3_exec(sql[0], "insert into sqlTable(ID,CardName, Cost, Health, Attack, CardDescribe, Quality, Spell0,Spell1,Spell2,Spell3,GraphPath1,GraphPath2) values(0001001,'紧急包扎',2,0,0,'本回合死亡的随从，回合结束重新返回战场并有1点生命值',2,621007,2,3,4,7,7)", 0, 0, errmsg);
	sqlite3_exec(sql[0], "insert into sqlTable(ID,CardName, Cost, Health, Attack, CardDescribe, Quality, Spell0,Spell1,Spell2,Spell3,GraphPath1,GraphPath2) values(0001002,'战事准备',4,0,0,'每有一个友方角色有护甲，摸一张牌',2,622007,2,3,4,7,7)", 0, 0, errmsg);

	
	//猎人
	sqlite3_exec(sql[0], "insert into sqlTable(ID,CardName, Cost, Health, Attack, CardDescribe, Quality, Spell0,Spell1,Spell2,Spell3,GraphPath1,GraphPath2) values(0011000,'石化之箭',4,0,0,'3回合无法攻击',0,711907,2,3,4,7,7)", 0, 0, errmsg);
	sqlite3_exec(sql[0], "insert into sqlTable(ID,CardName, Cost, Health, Attack, CardDescribe, Quality, Spell0,Spell1,Spell2,Spell3,GraphPath1,GraphPath2) values(0011001,'夺命射击',5,0,0,'消灭1个指定随从',1,720907,2,3,4,7,7)", 0, 0, errmsg);
	sqlite3_exec(sql[0], "insert into sqlTable(ID,CardName, Cost, Health, Attack, CardDescribe, Quality, Spell0,Spell1,Spell2,Spell3,GraphPath1,GraphPath2) values(0011002,'箭雨',3,0,0,'对敌方所有随从造成2伤害',2,721007,2,3,4,7,7)", 0, 0, errmsg);
	sqlite3_exec(sql[0], "insert into sqlTable(ID,CardName, Cost, Health, Attack, CardDescribe, Quality, Spell0,Spell1,Spell2,Spell3,GraphPath1,GraphPath2) values(0011003,'震荡射击',1,0,0,'晕眩',2,602907,2,3,4,7,7)", 0, 0, errmsg);
	sqlite3_exec(sql[0], "insert into sqlTable(ID,CardName, Cost, Health, Attack, CardDescribe, Quality, Spell0,Spell1,Spell2,Spell3,GraphPath1,GraphPath2) values(0011004,'烈炎射击',3,0,0,'对目标造成6伤害',1,722907,2,3,4,7,7)", 0, 0, errmsg);
	sqlite3_exec(sql[0], "insert into sqlTable(ID,CardName, Cost, Health, Attack, CardDescribe, Quality, Spell0,Spell1,Spell2,Spell3,GraphPath1,GraphPath2) values(0011005,'治愈箭雨',2,0,0,'友方所有随从恢复3生命值',2,723007,2,3,4,7,7)", 0, 0, errmsg);
	
	 
	
	//武器

	//战士
	sqlite3_exec(sql[0], "insert into sqlTable(ID,CardName, Cost, Health, Attack, CardDescribe, Quality, Spell0,Spell1,Spell2,Spell3,GraphPath1,GraphPath2) values(0002000,'新手之剑',1,2,2,'武器',0,1,2,3,4,7,7)", 0, 0, errmsg);
	sqlite3_exec(sql[0], "insert into sqlTable(ID,CardName, Cost, Health, Attack, CardDescribe, Quality, Spell0,Spell1,Spell2,Spell3,GraphPath1,GraphPath2) values(0002001,'精钢剑',3,2,4,'武器',0,1,2,3,4,7,7)", 0, 0, errmsg);
	
	//猎人
	sqlite3_exec(sql[0], "insert into sqlTable(ID,CardName, Cost, Health, Attack, CardDescribe, Quality, Spell0,Spell1,Spell2,Spell3,GraphPath1,GraphPath2) values(0012000,'群星之怒',6,2,3,'武器；攻击所有敌方角色',2,1,2,3,4,7,7)", 0, 0, errmsg);
	sqlite3_exec(sql[0], "insert into sqlTable(ID,CardName, Cost, Health, Attack, CardDescribe, Quality, Spell0,Spell1,Spell2,Spell3,GraphPath1,GraphPath2) values(0012001,'十字弩',2,3,2,'武器',2,1,2,3,4,7,7)", 0, 0, errmsg);


	//装备	
	sqlite3_exec(sql[0], "insert into sqlTable(ID,CardName, Cost, Health, Attack, CardDescribe, Quality, Spell0,Spell1,Spell2,Spell3,GraphPath1,GraphPath2) values(0003000,'反击装甲',4,3,0,'回合外英雄获得护甲+1，攻击+1',1,1,2,3,4,7,7)", 0, 0, errmsg);
	sqlite3_exec(sql[0], "insert into sqlTable(ID,CardName, Cost, Health, Attack, CardDescribe, Quality, Spell0,Spell1,Spell2,Spell3,GraphPath1,GraphPath2) values(0003001,'鲜血祭品',2,2,1,'攻击受伤的随从时，直接消灭',2,1,2,3,4,7,7)", 0, 0, errmsg);




}

//用户
void GameSqlite::SetUsersData()
{
	char **errmsg = NULL;
	sqlite3_exec(sql[1], "create table sqlTable( ID integer ,Account nvarchar(32), PassWord nvarchar(32),UserName nvarchar(32), Money integer)", NULL, NULL, errmsg);

	sqlite3_exec(sql[1], "insert into sqlTable( ID ,Account, PassWord ,UserName , Money) values(0,'test1','test1','yanyiji',1000)", NULL, NULL, errmsg);
	sqlite3_exec(sql[1], "insert into sqlTable( ID ,Account, PassWord ,UserName , Money) values(1,'test2','test2','yanyiji2',1000)", NULL, NULL, errmsg);

	//sqlite3_exec(sql[1], "select * from sqlTable ", GameSqlite::loadRecord, NULL, errmsg);
}

//用户和卡组的link
void GameSqlite::SetLinkUserCardArrayData()
{
	char **errmsg = NULL;
	sqlite3_exec(sql[2], "create table sqlTable( ID integer PRIMARY KEY, UsersID integer, RoleID integer, CardArrayName nvarchar(32))", NULL, NULL, errmsg);
	sqlite3_exec(sql[2], "insert into sqlTable( ID, UsersID, RoleID, CardArrayName) values(0,0,0,'yanyiji1')", NULL, NULL, errmsg);
	sqlite3_exec(sql[2], "insert into sqlTable( ID, UsersID, RoleID, CardArrayName) values(1,0,1,'yanyiji2')", NULL, NULL, errmsg);
	sqlite3_exec(sql[2], "insert into sqlTable(  UsersID, RoleID, CardArrayName) values(1,1,'yanyiji3')", NULL, NULL, errmsg);

	//sqlite3_exec(sql[2], "select * from sqlTable ", GameSqlite::loadRecord, NULL, errmsg);

}

//用户和卡牌的link
void GameSqlite::SetLinkUserCardData()
{
	char **errmsg = NULL;
	sqlite3_exec(sql[3], "create table sqlTable( ID integer PRIMARY KEY, UsersID integer, CardID integer, CardNumber integer)", NULL, NULL, errmsg);
	sqlite3_exec(sql[3], "insert into sqlTable(  UsersID, CardID, CardNumber) values(1,1,1)", NULL, NULL, errmsg);



}


//卡组的创建
void GameSqlite::SetCardArrayData()
{
	char **errmsg = NULL;
	sqlite3_exec(sql[4], "create table sqlTable( ID integer PRIMARY KEY,  ArrayID integer, CardID integer, CardNumber integer)", NULL, NULL, errmsg);

}



/***************************************************************************************************************************/

//
void GameSqlite::getBaseDate(int type)
{
	char **errmsg = NULL;
	sqlite3_exec(sql[type], "select * from sqlTable ", GameSqlite::loadRecord, NULL, errmsg);
}


//////////////////////////////////////////回调函数
//获得响应ID字段的回调函数
int GameSqlite::loadRecord(void * para, int n_column, char ** column_value, char ** column_name)
{
	//printf("ID=%s,name=%s,cost=%s\n", column_value[0], column_value[1], column_value[2]);

	//char **Column_Value = (char **)para;
	//*Column_Value = column_value[1];
	//int *count = (int*)para;
	//*count = n_column;



	/**/int i;
	printf("记录包含 %d 个字段 \n", n_column);
	for (i = 0; i < n_column; i++)
	{
		printf("字段名:%s ; 字段值:%s \n", column_name[i], column_value[i]);
	}
	printf("------------------\n");
	return 0;

}



///////////////////////////////////////////////////////////////////////////////////////////
////////////
//获得数据

///////////卡牌
///********************************************************************************************/
////随从
//void GameSqlite::GetData(int SQL_Type, int ID, string CardName, int Cost, int Health, int Attack, string CardDescribe, int Quality, int Spell0, int Spell1, int Spell2, int Spell3, string GraphPath1, string GraphPath2)
//{
//
//
//	char **errmsg = NULL;
//	//ID的转换int->string
//	char s[10];
//	sprintf(s, "%d", ID);
//
//	string sqlstr, sqlstr1 = s;
//	//获得SQL指令
//	sqlstr = "select * from Table where ID=" + sqlstr1;
//	
//	Sql_Type = SQL_Type;
//	//sqlite3_exec(sql[SQL_Type], sqlstr.c_str(), GameSqlite::loadRecord, NULL, errmsg);
//
//	//获得相应ID的字段，并存入Column_Value中
//	char** Column_Value = { '\0' };
//	int count, r, c;
//	sqlite3_get_table(sql[SQL_Type], sqlstr.c_str(), &Column_Value, &r, &c, NULL);
//
//	//将Column_Value中的每个值分别存入相应的参数中
//	ID = atoi(Column_Value[c]);
//	CardName = Column_Value[c + 1];
//	Health = atoi(Column_Value[c + 2]);
//	Attack = atoi(Column_Value[c + 3]);
//	CardDescribe = Column_Value[c + 4];
//	Quality = atoi(Column_Value[c + 5]);
//	Spell0 = atoi(Column_Value[c + 6]);
//	Spell1 = atoi(Column_Value[c + 7]);
//	Spell2 = atoi(Column_Value[c + 8]);
//	Spell3 = atoi(Column_Value[c + 9]);
//	GraphPath1 = Column_Value[c + 10];
//	GraphPath2 = Column_Value[c + 11];
//
//}
/////法术
//void GameSqlite::GetData(int SQL_Type, int ID, string CardName, int Cost, string CardDescribe, int Quality, int Effect1, int Effect2, int Effect3, string GraphPath1, string GraphPath2)
//{
//	char **errmsg = NULL;
//	//ID的转换int->string
//	char s[10];
//	sprintf(s, "%d", ID);
//
//	string sqlstr, sqlstr1 = s;
//	//获得SQL指令
//	sqlstr = "select * from Table where ID=" + sqlstr1;
//
//	Sql_Type = SQL_Type;
//	//sqlite3_exec(sql[SQL_Type], sqlstr.c_str(), GameSqlite::loadRecord, NULL, errmsg);
//
//	//获得相应ID的字段，并存入Column_Value中
//	char** Column_Value = { '\0' };
//	int count, r, c;
//	sqlite3_get_table(sql[SQL_Type], sqlstr.c_str(), &Column_Value, &r, &c, NULL);
//
//	//将Column_Value中的每个值分别存入相应的参数中
//	ID = atoi(Column_Value[c]);
//	CardName = Column_Value[c + 1];
//	CardDescribe = Column_Value[c + 4];
//	Quality = atoi(Column_Value[c + 5]);
//	Effect1 = atoi(Column_Value[c + 6]);
//	Effect2 = atoi(Column_Value[c + 7]);
//	Effect3 = atoi(Column_Value[c + 8]);
//	GraphPath1 = Column_Value[c + 10];
//	GraphPath2 = Column_Value[c + 11];
//
//
//
//
//
//}
/////装备
//void GameSqlite::GetData(int SQL_Type, int ID, string CardName, int Health, int Attack, int Cost, string CardDescribe, int Quality, int Effect1, int Effect2, int Effect3, string GraphPath1, string GraphPath2)
//{
//	char **errmsg = NULL;
//	//ID的转换int->string
//	char s[10];
//	sprintf(s, "%d", ID);
//
//	string sqlstr, sqlstr1 = s;
//	//获得SQL指令
//	sqlstr = "select * from Table where ID=" + sqlstr1;
//
//	Sql_Type = SQL_Type;
//	//sqlite3_exec(sql[SQL_Type], sqlstr.c_str(), GameSqlite::loadRecord, NULL, errmsg);
//
//	//获得相应ID的字段，并存入Column_Value中
//	char** Column_Value = { '\0' };
//	int count, r, c;
//	sqlite3_get_table(sql[SQL_Type], sqlstr.c_str(), &Column_Value, &r, &c, NULL);
//
//	//将Column_Value中的每个值分别存入相应的参数中
//	ID = atoi(Column_Value[c]);
//	CardName = Column_Value[c + 1];
//	Health = atoi(Column_Value[c + 2]);
//	Attack = atoi(Column_Value[c + 3]);
//	CardDescribe = Column_Value[c + 4];
//	Quality = atoi(Column_Value[c + 5]);
//	Effect1 = atoi(Column_Value[c + 6]);
//	Effect2 = atoi(Column_Value[c + 7]);
//	Effect3 = atoi(Column_Value[c + 8]);
//
//	GraphPath1 = Column_Value[c + 10];
//	GraphPath2 = Column_Value[c + 11];
//}
///****************************************************************************************/
//
////////////////////
//////英雄
//void GameSqlite::GetData(int SQL_Type, int ID, string CharacterNmae, int SkillID1, int SkillID2, int SkillID3, string CharacterDescribe, string GraphPath)
//{
//
//	char **errmsg = NULL;
//	//ID的转换int->string
//	char s[10];
//	sprintf(s, "%d", ID);
//
//	string sqlstr, sqlstr1 = s;
//	//获得SQL指令
//	sqlstr = "select * from Table where ID=" + sqlstr1;
//
//	Sql_Type = SQL_Type;
//	//sqlite3_exec(sql[SQL_Type], sqlstr.c_str(), GameSqlite::loadRecord, NULL, errmsg);
//
//	//获得相应ID的字段，并存入Column_Value中
//	char** Column_Value = { '\0' };
//	int count, r, c;
//	sqlite3_get_table(sql[SQL_Type], sqlstr.c_str(), &Column_Value, &r, &c, NULL);
//
//	//将Column_Value中的每个值分别存入相应的参数中
//	ID = atoi(Column_Value[c]);
//	CharacterNmae = Column_Value[c + 1];
//	SkillID1 = atoi(Column_Value[c + 2]);
//	SkillID2 = atoi(Column_Value[c + 3]);
//	SkillID3 = atoi(Column_Value[c + 4]);
//	CharacterDescribe = Column_Value[c + 5];
//	GraphPath = Column_Value[c + 6];
//}
//
///////////////////
///////技能
//void GameSqlite::GetData(int SQL_Type, int ID, string SkillName, int Cost, string SkillDiscrible, string GraphPath)
//{
//
//	char **errmsg = NULL;
//	//ID的转换int->string
//	char s[10];
//	sprintf(s, "%d", ID);
//	
//	string sqlstr, sqlstr1 = s;
//	//获得SQL指令
//	sqlstr = "select * from Table where ID=" + sqlstr1;
//
//	Sql_Type = SQL_Type;
//	
//	//sqlite3_exec(sql[SQL_Type], sqlstr.c_str(), GameSqlite::loadRecord, NULL, errmsg);
//
//	//获得相应ID的字段，并存入Column_Value中
//	char** Column_Value = { '\0' };
//	int count, r, c;
//	sqlite3_get_table(sql[SQL_Type], sqlstr.c_str(), &Column_Value, &r, &c, NULL);
//
//	//将Column_Value中的每个值分别存入相应的参数中
//	ID = atoi(Column_Value[c]);
//	SkillName = Column_Value[c + 1];
//	Cost = atoi(Column_Value[c + 2]);
//	SkillDiscrible = Column_Value[c + 3];
//	GraphPath = Column_Value[c + 4];
//
//
//
//}
//
//void GameSqlite::GetData(int ID)
//{
//	sqlite3 * db = NULL;
//	int result;
//	char **errmsg = NULL;
//	char s[10];
//	sprintf(s, "%d", ID);
//	
//	string sqlstr, sqlstr1 = s;
//
//	sqlstr = "select * from MyTable_1 where ID="+sqlstr1;
//	
//
//	result = sqlite3_open("f://Dcg_database5.db", &db);
//	char** Column_Value = { '\0' };
//	int count,r,c;
//	//sqlite3_exec(db, sqlstr.c_str(), GameSqlite::loadRecord,NULL, errmsg);
//	//printf("ID=%s,name=%s,cost=%s", Column_Value[0], Column_Value[1], Column_Value[2]);
//	
//	sqlite3_get_table(db, sqlstr.c_str(), &Column_Value, &r, &c, NULL);
//	//printf("ID=%s", Column_Value[c]);
//	 //cout << Column_Value[r+1];
//	//cout << count;
//}


