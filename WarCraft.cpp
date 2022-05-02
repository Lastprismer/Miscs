#include <iostream>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <string>
#include <vector>
#include <memory>
using namespace std;
#define NPC_NUM 5
#define WEAPON_NUM 3


#pragma region ID_List

const int DRAGON = 0, NINJA = 1, ICEMAN = 2, LION = 3, WOLF = 4, RED = 0, BLUE = 1, UNOCCUPIED = 2, SWORD = 0, BOMB = 1, ARROW = 2;

#pragma endregion

#pragma region Basic_Data

const int SpawnOrderArray[2][5] = { { ICEMAN,LION,WOLF,NINJA,DRAGON }, { LION,DRAGON,NINJA,ICEMAN,WOLF } };
int healthData[5] = { 0 }, damageData[5] = { 0 }, initialHeadquarterElement = 0, cityNum = 0, maxTimer = 0, arrowDamage = 0, lionLoyaltyDecrease = 0;
const char* NPCName[5] = { "dragon", "ninja", "iceman", "lion", "wolf" }, * PartyName[3] = { "red", "blue", "unoccupied" }, * WeaponName[3] = { "sword", "bomb", "arrow" };
bool GameOver = false;
enum GameState { Spawn_Npc, Lion_Kaqituolitai, Npc_Move, City_Regeneration, Take_Away_Elements, Shoot_Arrow, Bomb_Perish_Together, Npc_Battle, Headquarter_Report_Element, Npc_Report_Data, Lie_Down_And_Rotten_Hugely };
enum BattleHelper { Normal, Stop_Self, Stop_Global };
class Headquarter;
class City;
class NPC;
class Dragon;
class Ninja;
class Iceman;
class Lion;
class Wolf;
class Weapon;
class Sword;
class Bomb;
class Arrow;

vector<NPC*> npc;
vector<City> city;

#pragma endregion

#pragma region Basic_Func

void Initialize();
void PrintTime(int timer);
GameState CheckTime(int timer);

bool cmpnpcMove(const NPC*, const NPC*);
bool cmpnpcReport(const NPC*, const NPC*);
void CheckNpcActive();

void LionRun(int timer);
void CityRegenerate();
void NPCTakeElements(int timer);
void NPCShootArrows(int timer);
void Explosion(int timer);
void NPCBattle(int timer);
void NPCMove(int timer, Headquarter&, Headquarter&);
void NPCReportOwnedWeapons(int timer);

#pragma endregion

class Weapon
{
public:
	bool active;
	int durability = 0;
	int damage = 0;
	Weapon() :active(false) {}
	Weapon(int _dura, int _damage) :durability(_dura), damage(_damage), active(true) {}
	Weapon(Weapon& a) :durability(a.durability), damage(a.damage), active(a.active) {}
	void SwordWearing() { damage = damage * 8 / 10; if (damage == 0) active = false; }
};

class NPC
{
public:
	Headquarter* home;
	bool inEnemyHeadquarter;
	bool win_in_battle;
	int position;
	int type;
	int id;
	int health;
	int damage;
	bool active;
	Weapon ownedWeapons[3];
	NPC() :home(nullptr), inEnemyHeadquarter(false), active(false) {}
	NPC(Headquarter* p, int _id);
	void ReportData(int timer);
	void NewWeapon(int id);
	bool ShouldIUseBombToYou(NPC* target);
	void Fight(NPC* target, int timer);

	virtual ~NPC()
	{
		for (int i = 0; i < 3; i++)
			ownedWeapons[i].active = false;
	}
	virtual void SafePrintResult(int _type);
	virtual void PrintResult() = 0;
};

class Headquarter
{
private:
	int currentArrayIndex;
	int HeadquarterSpawnedNPCNum;
public:
	int party;
	int lifeElement;
	int elementCache;
	int enemyInHeadquarter;
	friend class NPC;
	Headquarter() {}
	~Headquarter() {}
	void Init(int color_, int lv);
	int NewNPC(int timer);
	void ReportLifeElement(int timer);
	void getCacheElement()
	{
		lifeElement += elementCache;
		elementCache = 0;
	}
};

class City
{
public:
	int id;
	int element;
	int flag;
	int npc_in_city;
	int flagHelper;
	City(int _id) :id(_id), element(0), npc_in_city(0), flag(UNOCCUPIED), flagHelper(UNOCCUPIED) {}
	inline int Attacker()
	{
		bool red = (flag == RED || (flag == UNOCCUPIED && ((id & 1) == 1)));
		return red ? RED : BLUE;
	}
	void changeFlag(int winner, int timer)
	{
		if (winner != flag && flagHelper == winner)
		{
			flag = winner;
			PrintTime(timer);
			printf(" %s flag raised in city %d\n", PartyName[winner], id);
			return;
		}
		flagHelper = winner;
		return;
		/*		printf("[DEBUG] ## flag:%d    flagh:%d      win:%d\n", flag, flagHelper, winner);*/
	}
};

class Dragon :public NPC
{
private:
	void CalculateMorale() { morale = home->lifeElement / (double)healthData[DRAGON]; }
public:
	double morale;
	Dragon(Headquarter* p, int _id) : NPC(p, _id)
	{
		type = DRAGON;
		health = healthData[DRAGON];
		damage = damageData[DRAGON];
		NewWeapon(id % WEAPON_NUM);
		CalculateMorale();
	}
	void PrintResult()
	{
		NPC::SafePrintResult(DRAGON);
		printf("Its morale is %.2f\n", morale);
	}
	void DragonYelled(int timer)
	{
		PrintTime(timer);
		NPC* temp = ((NPC*)this);
		printf(" %s dragon %d yelled in city %d\n", PartyName[temp->home->party], temp->id, temp->position);
	}
};
class Ninja : public NPC
{
public:
	Ninja(Headquarter* p, int _id) :NPC(p, _id)
	{
		type = NINJA;
		health = healthData[NINJA];
		damage = damageData[NINJA];
		NewWeapon(id % WEAPON_NUM);
		NewWeapon((id + 1) % WEAPON_NUM);
	}
	void PrintResult()
	{
		NPC::SafePrintResult(NINJA);
	}
	void Reward() {}
};
class Iceman : public NPC
{
public:
	int stepTimer;
	Iceman(Headquarter* p, int _id) :NPC(p, _id)
	{
		type = ICEMAN;
		health = healthData[ICEMAN];
		damage = damageData[ICEMAN];
		NewWeapon(id % WEAPON_NUM);
		stepTimer = 0;
	};
	void PrintResult()
	{
		NPC::SafePrintResult(ICEMAN);
	}
	void IcemanStatAfterMove()
	{
		stepTimer++;
		if (stepTimer >= 2)
		{
			stepTimer = 0;
			damage += 20;
			health -= 9;
			if (health <= 0)
				health = 1;
		}

	}
};
class Lion : public NPC
{
public:
	int loyalty;
	int hp_before_battle = 0;
	void CountLoyalty()
	{
		loyalty = home->lifeElement;
	}
	Lion(Headquarter* p, int _id) : NPC(p, _id)
	{
		type = LION;
		health = healthData[LION];
		damage = damageData[LION];
		CountLoyalty();
	}
	void PrintResult()
	{
		NPC::SafePrintResult(LION);
		CountLoyalty();
		printf("Its loyalty is %d\n", loyalty);
	}
};
class Wolf : public NPC
{
public:
	Wolf(Headquarter* p, int _id) : NPC(p, _id)
	{
		type = WOLF;
		health = healthData[WOLF];
		damage = damageData[WOLF];
	};
	void PrintResult()
	{
		NPC::SafePrintResult(WOLF);
	}
	void Steal(NPC* target)
	{
		for (int i = SWORD; i <= ARROW; i++)
			if (target->ownedWeapons[i].active && !ownedWeapons[i].active)
				ownedWeapons[i] = target->ownedWeapons[i];
	}
};

int main()
{
	/*FILE* stream;
	freopen_s(&stream, "in.txt", "r", stdin);
	freopen_s(&stream, "out.txt", "w", stdout);*/
	int n;
	cin >> n;
	for (int k = 1; k <= n; k++)
	{
		printf("Case %d:\n", k);
		Initialize();
		Headquarter redHQ, blueHQ;
		redHQ.Init(RED, initialHeadquarterElement);
		blueHQ.Init(BLUE, initialHeadquarterElement);
		for (int timer = 0; timer <= maxTimer && !GameOver; timer++)
		{
			GameState state = CheckTime(timer);
			switch (state)
			{
			case Spawn_Npc:
				redHQ.NewNPC(timer);
				blueHQ.NewNPC(timer);
				break;
			case Lion_Kaqituolitai:
				LionRun(timer);
				break;
			case Npc_Move:
				NPCMove(timer, redHQ, blueHQ);
				break;
			case City_Regeneration:
				CityRegenerate();
				break;
			case Take_Away_Elements:
				NPCTakeElements(timer);
				break;
			case Shoot_Arrow:
				NPCShootArrows(timer);
				break;
			case Bomb_Perish_Together:
				Explosion(timer);
				break;
			case Npc_Battle:
				redHQ.elementCache = 0;
				blueHQ.elementCache = 0;
				NPCBattle(timer);
				redHQ.getCacheElement();
				blueHQ.getCacheElement();
				break;
			case Headquarter_Report_Element:
				redHQ.ReportLifeElement(timer);
				blueHQ.ReportLifeElement(timer);
				break;
			case Npc_Report_Data:
				NPCReportOwnedWeapons(timer);
			}
		}
	}
}


#pragma region Headquater

void Headquarter::Init(int _color, int element)
{
	lifeElement = element;
	elementCache = 0;
	party = _color;
	currentArrayIndex = 0;
	HeadquarterSpawnedNPCNum = 0;
	enemyInHeadquarter = 0;
}

int Headquarter::NewNPC(int timer)
{
	int type = SpawnOrderArray[party][currentArrayIndex % NPC_NUM];
	if (healthData[type] > lifeElement)
		return -1;
	lifeElement -= healthData[type];
	currentArrayIndex = (currentArrayIndex + 1) % NPC_NUM;
	PrintTime(timer);
	switch (type)
	{
	case DRAGON:
		npc.push_back(new Dragon(this, HeadquarterSpawnedNPCNum + 1));
		break;
	case NINJA:
		npc.push_back(new Ninja(this, HeadquarterSpawnedNPCNum + 1));
		break;
	case ICEMAN:
		npc.push_back(new Iceman(this, HeadquarterSpawnedNPCNum + 1));
		break;
	case WOLF:
		npc.push_back(new Wolf(this, HeadquarterSpawnedNPCNum + 1));
		break;
	case LION:
		npc.push_back(new Lion(this, HeadquarterSpawnedNPCNum + 1));
		break;
	}
	npc[npc.size() - 1]->PrintResult();
	HeadquarterSpawnedNPCNum++;
	return type;
}

void Headquarter::ReportLifeElement(int timer)
{
	PrintTime(timer);
	printf(" %d elements in %s headquarter\n", lifeElement, PartyName[party]);
}

#pragma endregion

#pragma region NPC

NPC::NPC(Headquarter* p, int _id) : home(p), id(_id), inEnemyHeadquarter(false), active(true), win_in_battle(false)
{
	if (p->party == RED)
		position = 0;
	else position = cityNum + 1;
}

void NPC::ReportData(int timer)
{
	int flag = 0;
	PrintTime(timer);
	printf(" %s %s %d has ", PartyName[home->party], NPCName[type], id);
	if (ownedWeapons[ARROW].active)
	{
		if (flag) printf(",");
		flag++, printf("arrow(%d)", ownedWeapons[ARROW].durability + 1);
	}
	if (ownedWeapons[BOMB].active)
	{
		if (flag) printf(",");
		flag++, printf("bomb");
	}
	if (ownedWeapons[SWORD].active)
	{
		if (flag) printf(",");
		flag++, printf("sword(%d)", ownedWeapons[SWORD].damage);
	}
	if (!flag) printf("no weapon");
	printf("\n");
}

void NPC::NewWeapon(int id)
{
	switch (id)
	{
	case SWORD:
	{
		int dmg = damage * 2 / 10;
		if (dmg <= 0) return;
		ownedWeapons[SWORD] = Weapon(0, dmg);
		break;
	}
	case ARROW:
		ownedWeapons[ARROW] = Weapon(2, 0);
		break;
	case BOMB:
		ownedWeapons[BOMB] = Weapon(0, 0);
		break;
	}
}

bool NPC::ShouldIUseBombToYou(NPC* t)
{
	int dmg = ownedWeapons[SWORD].active ? ownedWeapons[SWORD].damage : 0;
	int dmg2 = t->ownedWeapons[SWORD].active ? t->ownedWeapons[SWORD].damage : 0;
	if (home->party == city[position - 1].Attacker())
	{
		return ownedWeapons[BOMB].active && (dmg + damage < t->health && (t->type != NINJA) && health <= t->damage / 2 + dmg2); //打不死，反击死
	}
	else return ownedWeapons[BOMB].active && health <= t->damage + dmg2;	//被打死
}

void NPC::Fight(NPC* target, int timer)
{
	target->health -= damage + (ownedWeapons[SWORD].active ? ownedWeapons[SWORD].damage : 0);
	ownedWeapons[SWORD].SwordWearing();
	PrintTime(timer);
	printf(" %s %s %d attacked %s %s %d in city %d with %d elements and force %d\n", PartyName[home->party], NPCName[type], id, PartyName[target->home->party], NPCName[target->type], target->id, position, health, damage);
	if (target->health > 0 && target->type != NINJA)
	{
		health -= target->damage / 2 + (target->ownedWeapons[SWORD].active ? target->ownedWeapons[SWORD].damage : 0);
		target->ownedWeapons[SWORD].SwordWearing();
		PrintTime(timer);
		printf(" %s %s %d fought back against %s %s %d in city %d\n", PartyName[target->home->party], NPCName[target->type], target->id, PartyName[home->party], NPCName[type], id, position);
	}
}

void NPC::SafePrintResult(int _type)
{
	printf(" %s %s %d born\n", PartyName[home->party], NPCName[type], id);
}

#pragma endregion

#pragma region Basic_Func

void Initialize()
{
	city.clear();
	npc.clear();
	GameOver = false;
	cin >> initialHeadquarterElement;
	cin >> cityNum;
	cin >> arrowDamage;
	cin >> lionLoyaltyDecrease;
	cin >> maxTimer;
	for (int i = 0; i < 5; i++)
	{
		cin >> healthData[i];
	}
	for (int i = 0; i < 5; i++)
	{
		cin >> damageData[i];
	}
	for (int i = 1; i <= cityNum; i++)
		city.push_back(City(i));
}

inline void PrintTime(int timer)
{
	printf("%03d:%02d", timer / 60, timer % 60);
}

GameState CheckTime(int timer)
{
	GameState state = Lie_Down_And_Rotten_Hugely;
	switch (timer % 60)
	{
	case 0:
		state = Spawn_Npc;
		break;
	case 5:
		state = Lion_Kaqituolitai;
		break;
	case 10:
		state = Npc_Move;
		break;
	case 20:
		state = City_Regeneration;
		break;
	case 30:
		state = Take_Away_Elements;
		break;
	case 35:
		state = Shoot_Arrow;
		break;
	case 38:
		state = Bomb_Perish_Together;
		break;
	case 40:
		state = Npc_Battle;
		break;
	case 50:
		state = Headquarter_Report_Element;
		break;
	case 55:
		state = Npc_Report_Data;
		break;
	}
	return state;
}


bool cmpnpcMove(const NPC* a, const NPC* b)
{
	if (a->position != b->position)
		return a->position < b->position;
	return a->home->party == RED;
	//位置小的靠前，红靠前
}
bool cmpnpcReport(const NPC* a, const NPC* b)
{
	if (a->home->party != b->home->party)
	{
		return a->home->party == RED;
	}
	else return a->position < b->position;
}

void CheckNpcActive()
{
	vector<NPC*>::iterator iter = npc.begin();
	while (iter != npc.end())
	{
		if (!(*iter)->active)
			iter = npc.erase(iter);
		else iter++;
	}
}


void LionRun(int timer)
{
	std::sort(npc.begin(), npc.end(), cmpnpcMove);
	vector<NPC*>::iterator iter = npc.begin();
	while (iter != npc.end())
	{
		if ((*iter)->type == LION && ((Lion*)(*iter))->loyalty <= 0 && ((Lion*)(*iter))->inEnemyHeadquarter == false)
		{
			PrintTime(timer);
			printf(" %s lion %d ran away\n", PartyName[(*iter)->home->party], (*iter)->id);
			iter = npc.erase(iter);
		}
		else iter++;
	}
}

void CityRegenerate()
{
	for (vector<City>::iterator iter = city.begin(); iter != city.end(); iter++)
	{
		(*iter).element += 10;
		(*iter).npc_in_city = 0;
	}
}

void NPCTakeElements(int timer)
{
	for (vector<NPC*>::iterator iter = npc.begin(); iter != npc.end(); iter++)
	{
		if (!(*iter)->inEnemyHeadquarter)
			city[(*iter)->position - 1].npc_in_city++;
	}
	for (vector<NPC*>::iterator iter = npc.begin(); iter != npc.end(); iter++)
	{
		if (!(*iter)->inEnemyHeadquarter)
			if (city[(*iter)->position - 1].npc_in_city == 1)
			{
				int grabElement = city[(*iter)->position - 1].element;
				PrintTime(timer);
				printf(" %s %s %d earned %d elements for his headquarter\n", PartyName[(*iter)->home->party], NPCName[(*iter)->type], (*iter)->id, grabElement);
				city[(*iter)->position - 1].element = 0;
				(*iter)->home->lifeElement += grabElement;
			}
	}
}

void NPCShootArrows(int timer)
{
	vector<NPC*>::iterator iter;
	for (iter = npc.begin(); iter != npc.end(); iter++)
	{
		if (!(*iter)->ownedWeapons[ARROW].active) continue;
		if (((*iter)->home->party == BLUE && (*iter)->position == 1) || ((*iter)->home->party == RED && (*iter)->position == cityNum)) continue; // 在将走进司令部时，不射
		for (vector<NPC*>::iterator n = npc.begin(); n != npc.end(); n++)
		{
			if (((*iter)->home->party == BLUE && (*n)->home->party == RED && (*n)->position == (*iter)->position - 1) ||
				((*iter)->home->party == RED && (*n)->home->party == BLUE && (*n)->position == (*iter)->position + 1)) // 下一个城市的敌对玩家
			{
				(*iter)->ownedWeapons[ARROW].durability--;
				if ((*iter)->ownedWeapons[ARROW].durability < 0)
					(*iter)->ownedWeapons[ARROW].active = false;
				(*n)->health -= arrowDamage;
				PrintTime(timer);
				printf(" %s %s %d shot", PartyName[(*iter)->home->party], NPCName[(*iter)->type], (*iter)->id);
				if ((*n)->health <= 0)
					(*n)->health = 0, printf(" and killed %s %s %d\n", PartyName[(*n)->home->party], NPCName[(*n)->type], (*n)->id);
				else printf("\n");
			}
		}
	}
}

void Explosion(int timer)
{
	std::sort(npc.begin(), npc.end(), cmpnpcMove);
	NPC* attacker = nullptr, * target = nullptr;
	for (vector<NPC*>::iterator iter = npc.begin(); iter != npc.end(); iter++)
	{
		if (iter + 1 != npc.end() &&							//不在末尾，防止爆vector
			(*(iter + 1))->position == (*iter)->position &&		//下一个在同城
			(*(iter + 1))->health > 0 && (*iter)->health > 0	//没死
			)
		{
			attacker = ((*iter)->home->party == city[(*iter)->position - 1].Attacker()) ? *iter : *(iter + 1);
			target = (attacker == *iter) ? *(iter + 1) : *iter;
			NPC* winner = nullptr, * loser = nullptr;
			bool explode = false;
			if (attacker->ShouldIUseBombToYou(target))
				winner = attacker, loser = target, explode = true;
			else if (target->ShouldIUseBombToYou(attacker))
				winner = target, loser = attacker, explode = true;
			if (explode)
			{
				PrintTime(timer);
				printf(" %s %s %d used a bomb and killed %s %s %d\n", PartyName[winner->home->party], NPCName[winner->type], winner->id, PartyName[loser->home->party], NPCName[loser->type], loser->id);
				winner->active = false;
				loser->active = false;
			}
		}
	}
	CheckNpcActive();
}

void NPCBattle(int timer)
{
	std::sort(npc.begin(), npc.end(), cmpnpcMove);
	NPC* attacker = nullptr, * target = nullptr;
	for (vector<NPC*>::iterator iter = npc.begin(); iter != npc.end(); iter++)
	{
		(*iter)->win_in_battle = false;
	}
	for (vector<NPC*>::iterator iter = npc.begin(); iter != npc.end(); iter++)
	{
		if (iter + 1 != npc.end() &&							//不在末尾，防止爆vector
			(*(iter + 1))->position == (*iter)->position &&		//下一个在同城
			(*iter)->active && (*(iter + 1))->active			//不是打输的
			)
		{
			attacker = ((*iter)->home->party == city[(*iter)->position - 1].Attacker()) ? *iter : *(iter + 1);
			target = (attacker == *iter) ? *(iter + 1) : *iter;
			if (attacker->type == LION)
				dynamic_cast<Lion*>(attacker)->hp_before_battle = attacker->health;
			if (target->type == LION)
				dynamic_cast<Lion*>(target)->hp_before_battle = target->health;
			bool is_not_shot = attacker->health > 0 && target->health > 0;
			if (is_not_shot)
				attacker->Fight(target, timer);
			if (attacker->health > 0 && target->health > 0)
			{
				if (attacker->type == LION)
					dynamic_cast<Lion*>(attacker)->loyalty -= lionLoyaltyDecrease;
				else if (attacker->type == DRAGON)
				{
					Dragon* d = dynamic_cast<Dragon*>(attacker);
					d->morale -= 0.2;
					if (d->morale > 0.8) d->DragonYelled(timer);
				}
				if (target->type == LION)
					dynamic_cast<Lion*>(target)->loyalty -= lionLoyaltyDecrease;
				else if (target->type == DRAGON)
					dynamic_cast<Dragon*>(target)->morale -= 0.2;
				city[attacker->position - 1].flagHelper = UNOCCUPIED;
				continue;
			}
			if (attacker->health <= 0 && target->health <= 0)
			{
				attacker->active = false; target->active = false;/*
				city[attacker->position - 1].flagHelper = UNOCCUPIED;*/
				continue;
			}
			NPC* winner = nullptr, * loser = nullptr;
			if (attacker->health > 0) winner = attacker, loser = target;
			else winner = target, loser = attacker;
			if (is_not_shot)
			{
				PrintTime(timer);
				printf(" %s %s %d was killed in city %d\n", PartyName[loser->home->party], NPCName[loser->type], loser->id, loser->position);
			}
			if (loser->type == LION) winner->health += dynamic_cast<Lion*>(loser)->hp_before_battle;
			if (winner->type == DRAGON)
			{
				Dragon* d = dynamic_cast<Dragon*>(winner);
				d->morale += 0.2;
				if (d->morale > 0.8 && winner == attacker) d->DragonYelled(timer);
			}
			else if (winner->type == WOLF)
			{
				dynamic_cast<Wolf*>(winner)->Steal(loser);
			}
			winner->home->elementCache += city[winner->position - 1].element;
			PrintTime(timer);
			printf(" %s %s %d earned %d elements for his headquarter\n", PartyName[winner->home->party], NPCName[winner->type], winner->id, city[winner->position - 1].element);
			city[winner->position - 1].element = 0;
			winner->win_in_battle = true;
			loser->active = false;
			city[winner->position - 1].changeFlag(winner->home->party, timer);
		}
	}
	for (vector<NPC*>::iterator iter = npc.begin(); iter != npc.end(); iter++)
	{
		if ((*iter)->health <= 0)(*iter)->active = false;
	}
	CheckNpcActive();
	for (vector<NPC*>::iterator iter = npc.begin(); iter != npc.end(); iter++)
	{
		if ((*iter)->home->party == BLUE && (*iter)->home->lifeElement >= 8 && (*iter)->win_in_battle)
			(*iter)->health += 8, (*iter)->home->lifeElement -= 8;
		if ((*iter)->home->lifeElement < 8) break;
	}
	for (vector<NPC*>::reverse_iterator iter = npc.rbegin(); iter != npc.rend(); iter++)
	{
		if ((*iter)->home->party == RED && (*iter)->home->lifeElement >= 8 && (*iter)->win_in_battle)
			(*iter)->health += 8, (*iter)->home->lifeElement -= 8;
		if ((*iter)->home->lifeElement < 8) break;
	}
}

void NPCMove(int timer, Headquarter& red, Headquarter& blue)
{
	vector<NPC*>::iterator iter = npc.begin();
	for (iter = npc.begin(); iter != npc.end(); iter++)
	{
		if ((*iter)->inEnemyHeadquarter == false)
		{
			//冰人伤血
			if ((*iter)->type == ICEMAN)
			{
				((Iceman*)(*iter))->IcemanStatAfterMove();
			}
			//真正走路
			if ((*iter)->home->party == RED) (*iter)->position++;
			else (*iter)->position--;
		}
	}
	std::sort(npc.begin(), npc.end(), cmpnpcMove);

	for (iter = npc.begin(); iter != npc.end(); iter++)
	{
		if (!(*iter)->inEnemyHeadquarter)
		{
			PrintTime(timer);
			if (((*iter)->position == 0 && (*iter)->home->party == BLUE) || ((*iter)->position == cityNum + 1 && (*iter)->home->party == RED))//走到司令部
			{
				(*iter)->inEnemyHeadquarter = true;
				printf(" %s %s %d reached %s headquarter with %d elements and force %d\n", PartyName[(*iter)->home->party], NPCName[(*iter)->type], (*iter)->id, PartyName[((*iter)->home->party + 1) % 2], (*iter)->health, (*iter)->damage);
				(*iter)->position += (*iter)->home->party == RED ? 1 : -1;
				if ((*iter)->home->party == RED)
					blue.enemyInHeadquarter++;
				else red.enemyInHeadquarter++;
				if ((*iter)->home->party == BLUE && red.enemyInHeadquarter > 1)
				{
					PrintTime(timer);
					printf(" red headquarter was taken\n");
					GameOver = true;
				}
				if ((*iter)->home->party == RED && blue.enemyInHeadquarter > 1)
				{
					PrintTime(timer);
					printf(" blue headquarter was taken\n");
					GameOver = true;
				}
			}
			else//走到下一个城市
			{
				printf(" %s %s %d marched to city %d with %d elements and force %d\n", PartyName[(*iter)->home->party], NPCName[(*iter)->type], (*iter)->id, (*iter)->position, (*iter)->health, (*iter)->damage);
			}
		}
	}
	iter = npc.begin();
	while (iter != npc.end())
	{
		//杀冰人
		if ((*iter)->type == ICEMAN && (*iter)->health <= 0)
		{
			iter = npc.erase(iter);
		}
		else iter++;
	}
}

void NPCReportOwnedWeapons(int timer)
{
	std::sort(npc.begin(), npc.end(), cmpnpcReport);
	for (vector<NPC*>::iterator iter = npc.begin(); iter != npc.end(); iter++)
	{
		(*iter)->ReportData(timer);
	}
}

#pragma endregion

//炸弹炸死后要立即清除数据，弓箭不要
//弓箭射死后血量归0，防止射死的是狮子而bug
//平局：双方都存活
//从第八组数据开始用，前面的都是寄
