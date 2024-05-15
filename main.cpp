/****************************************************************************************************************

Player Special Abilities:

Critical Hit   : unlocks after level 2 : Deals one more damage of same amount, total 2x damage
Blocker        : unlocks after level 3 : 0 damage on enemy hit
Life Steal     : unlocks after level 4 : after dealing damage, recovers a HP of same as that of that damage variable.
Ranged Attack  : unlocks after level 5 : Deals additional damage of 0.5x damage and takes 0 damage on next enemy hit.

Player Stats
Level 1 : HP = 100, minDamage = 25, maxDamage = 45, minHeal = 30, maxHeal = 45, minDef = 05, maxDef = 15
Level 2 : HP = 200, minDamage = 30, maxDamage = 50, minHeal = 32, maxHeal = 50, minDef = 08, maxDef = 20
Level 3 : HP = 300, minDamage = 35, maxDamage = 55, minHeal = 34, maxHeal = 55, minDef = 11, maxDef = 25
Level 4 : HP = 400, minDamage = 40, maxDamage = 60, minHeal = 36, maxHeal = 60, minDef = 14, maxDef = 30
Level 5 : HP = 500, minDamage = 45, maxDamage = 65, minHeal = 38, maxHeal = 65, minDef = 17, maxDef = 35
Level 6 : HP = 600, minDamage = 50, maxDamage = 70, minHeal = 40, maxHeal = 70, minDef = 20, maxDef = 40

i.e HP+=100, minDamage+=5, maxDamage+=5, minHeal += 2, maxHeal+=5, minDef=3, maxDef+=5

Guard    : HP = 200 , 20-35 , 6-24
Vanguard : HP = 500 , 35-50 , 15-35
Murloc   : HP = 1000, 40-70 , 15-40

Special Abilities of Murloc:

Summon minion  : summons a Minion of 150 HP. We have to destroy him to be able to touch Murloc.
Healing Elixir : Heals 100 HP.
Hypnotize      : Player hits himself with same damage that the player used

******************************************************************************************************************/

#include <iostream>
#include <ctime>
#include <iomanip>
using namespace std;

class Player 
{

  private:
  int health;
  int fullhealth;
  int minDamage;
  int maxDamage;
  int minHeal;
  int maxHeal;
  int minDef;
  int maxDef;
  int level;

  bool criticalHit = false;
  bool blocker = false;
  bool lifeSteal = false;
  bool rangedAttack = false;

  bool block = false;
  bool hypnotise = false;

  public:
  Player() 
  { 
    level = 1;
    health = 100;
    fullhealth = 100;
    minDamage = 25;
    maxDamage = 45;
    minHeal = 30;
    maxHeal = 45;
    minDef = 5;
    maxDef = 15;
  }
  void Item(string item)  // called from levelUP() function 
  {
    cout<<"\n$"<<setfill('=')<<setw(28)<<"$"<<endl;
    cout<<"$"<<string(3,' ')<<"Item obtained: "<<item<<string(3,' ')<<"$"<<endl;
    cout<<"$"<<setfill('=')<<setw(28)<<"$"<<endl;
  }

  void levelUP()   // All stuff that changes after a level
  {
    level += 1;
    fullhealth += 100;
    health = fullhealth;
    switch(level){
      case 3: 
        cout<<"\nSpecial Ability : Critical Hit unlocked !!!\n";
        criticalHit = true;
        Item(" Sword");
        break;
      case 4:
        cout<<"\nSpecial Ability : Blocker unlocked !!!\n";
        blocker = true;
        Item("Shield");
        break;
      case 5:
        cout<<"\nSpecial Ability : LifeSteal unlocked !!!\n";
        lifeSteal = true;
        Item("Armour");
        break;
      case 6:
        cout<<"\nSpecial Ability : Ranged Attack unlocked !!!\n";
        rangedAttack = true;
        Item("   Bow");
        break;
    }
    minDamage += 5;
    maxDamage += 5;
    minHeal += 2;
    maxHeal += 5;
    minDef += 3; 
    maxDef += 5;
  }
  int getHealth()
  {
    return health;
  }
  int getFullHealth()
  {
    return fullhealth;
  }
  int getLevel()
  {
    return level;
  }
  int GiveDamage()
  {
    srand(time(0));
    int Damage = (rand() % (maxDamage + 1 - minDamage) + minDamage);     //Random Damage
    
    if(hypnotise)
    {
      hypnotise = false;
      cout<<"Player is hypnotised.\n";
      cout<<"Player attacked himself with "<<Damage<<" points\n";
      health -= Damage;
      cout<<"Player's health after getting attacked is "<<health<<'\n';
      return 0;
    }
    srand(time(0));
    int specialAbility = (rand() % 11);         //Special Abilities having 10% probability.
    
    if (specialAbility == 1 && criticalHit == true)
    {
      cout<<"Player used special ability : Critical Hit !\n";
      cout<<"Damage will be now 2 x "<<Damage<<'\n';
      Damage = Damage*2;
    }
    else if (specialAbility == 2 && blocker == true)
    {  
      cout<<"Player used special ability : Blocker !\n";
      block = true;
      return 0; 
    }
    else if (specialAbility == 3 && lifeSteal == true) 
    {
      cout<<"Player used special ability : Life Steal !\n";
      health += Damage;
      if (health>fullhealth) {health = fullhealth;}
      cout<<"Player health recovered by "<<Damage<<" HP points\n";
      cout<<"Player drained "<<Damage<<" HP from enemy"<<'\n';
      return Damage+2000;        // Adding 2000 denotes health drain which enemy cannot block
    }
    else if (specialAbility == 4 && rangedAttack == true) 
    {  
      cout<<"Player used special ability : Ranged Attack !\n";
      cout<<"Damage will be now 1.5 x "<<Damage<<'\n';
      block = true;
      Damage = Damage*1.5;
    }
    
    cout<<"Player attacked wth "<<Damage<<" points"<<'\n';
    return Damage;
  }

  void TakeDamage(int dmg)
  {  
    if (block)
    {
      block = false;
      cout<<"Player blocked Enemy's attack completely. No Damage inflicted on Player\n";
      return;
    }
    if (dmg > 1000)       //I purposely send a damage over 1000 to detect Hypnotise being applied by Murloc
    {
      dmg-=1000;
      hypnotise = true;
    }
    srand(time(0));        //from here onwards, normal takedamage
    int def = (rand() % (maxDef + 1 - minDef) + minDef);
    cout<<"Player defended "<<def<<" points"<<'\n';
    dmg -= def;
    if (dmg >=0)
      health -= dmg;
    if (health <= 0 )
    {
      cout<<"Player died !!!"<<endl;
      health = 0;
      return;
    }
    cout<<"Player's health after getting attacked is "<<health<<'\n';
  } 
  void Healing()
  {
    if (health == fullhealth)
      cout<<"Healing is not applied. Player health is already full("<<health<<")\n";

    srand(time(0));
    int heal = (rand() % (maxHeal + 1 - minHeal) + minHeal);
    cout<<"Player used healing of "<<heal<<" points"<<'\n';
    health += heal;
    if (health>=fullhealth) {health = fullhealth;}
    cout<<"Player health after healing is "<<health<<'\n';
  }
};

class Enemy 
{
  protected:
  int health;
  int fullhealth;
  int minDamage;
  int maxDamage;
  int minDef;
  int maxDef;
  string name;

  public:
  Enemy()
  {   //nothing here 
  }
  int getHealth()
  {
    return health;
  }
  int getFullHealth()
  {
    return fullhealth;
  }
  string getName()
  {
    return name;
  }
  virtual int GiveDamage()
  {
    srand(time(0));
    int Damage = (rand() % (maxDamage + 1 - minDamage) + minDamage);
    cout<<name<<" attacked wth "<<Damage<<" points"<<"\n";
    return Damage;
  }
  virtual void TakeDamage(int dmg)
  {
    srand(time(0));
    int def = (rand() % (maxDef + 1 - minDef) + minDef);
    if (dmg > 2000){
      dmg -= 2000;
      goto skipDefence;
    }
    cout<<name<<" defended "<<def<<" points"<<'\n';
    dmg -= def;
    
    skipDefence:
    if (dmg >=0)
      health -= dmg;
    if (health <= 0 )
    {
      cout<<name<<" died !!!"<<endl;
      health = 0;
      return;
    }
    cout<<name<<"'s health after getting attacked is "<<health<<'\n';
  } 

  virtual int getMinionHealth() {return 0;}
  virtual bool minionEnabled() {return false;}
};

class Guard: public Enemy
{
  public:
  Guard() 
  {
    health = 200;
    fullhealth = 200;
    minDamage = 20;
    maxDamage = 35;
    minDef = 6;
    maxDef = 24;
    name = "Guard";
  }
};

class Vanguard: public Enemy
{
  public:
  Vanguard() 
  {
    health = 500;
    fullhealth = 500;
    minDamage = 35;
    maxDamage = 50;
    minDef = 15;
    maxDef = 35;
    name = "Vanguard";
  }
};

class Murloc: public Enemy
{  
  int minionHealth;
  bool minion = false;

  public:
  Murloc() 
  {
    health = 1000;
    fullhealth = 1000;
    minDamage = 40;
    maxDamage = 70;
    minDef = 15;
    maxDef = 40;
    name = "Murloc";
    minionHealth = 150;
  }
   
  int getMinionHealth()       //Minions are creatures released by Murloc's special ability
  {
    return minionHealth;
  }
  bool minionEnabled()
  {
    return minion;
  }
  int GiveDamage()
  {
    srand(time(0));
    int specialAbility = (rand() % 15);   /// 6.66% probability
    int Damage = (rand() % (maxDamage + 1 - minDamage) + minDamage);
    if (specialAbility == 1)
    {
      cout<<"Murloc used special ability : Summon Minion !\n";
      minion = true;
      minionHealth = 150;
    }
    else if (specialAbility == 2)
    {
      cout<<"Murloc used special ability : Healing Elixir !\n";
      if (health == fullhealth)
      {
        cout<<"No healing applied. Murloc's health is full\n";
        cout<<"Murloc attacked wth "<<Damage<<" points"<<"\n";
        return Damage;
      }
      health += 100;
      cout<<"Murloc healed by 100 HP\n";
      if (health > fullhealth){
        health = fullhealth;
      }
    }
    else if (specialAbility == 3)
    {
      cout<<"Murloc used special ability : Hypnotize !\n";
      cout<<"Murloc attacked wth "<<Damage<<" points"<<"\n";
      return Damage+1000;             // I purposely return damage over 1000 to indicate Hypnotised condition
    }
    if(minion)
    {
      srand(time(0));
      int dmg = (rand() % (11) + 5);
      cout<<"Murloc attacked wth "<<Damage<<" points and Minion attacked with "<<dmg<<" points"<<"\n";
      return Damage + dmg;
    }
    cout<<"Murloc attacked wth "<<Damage<<" points"<<"\n";
    return Damage;
  }
  void TakeDamage(int dmg)
  {
    if (dmg == 0){
      return;
    }
    if(minion)   // When minion is there, Murloc's doesn't take damage.
    {
      minionHealth -= dmg;
      if (minionHealth <= 0)
      {
        minionHealth = 0;
        minion = false;
        cout<<"Minion died !!!\n";
      }
      cout<<"Minion's health after getting attacked is "<<minionHealth<<" out of 150\n";
      return;
    }
    srand(time(0));
    int def = (rand() % (maxDef + 1 - minDef) + minDef);
    if (dmg > 2000){
      dmg -= 2000;
      goto skipDefence;
    }
    cout<<"Murloc defended "<<def<<" points"<<'\n';
    dmg -= def;

    skipDefence:
    if (dmg >=0)
      health -= dmg;
    if (health <= 0 )
    {
      cout<<"Murloc died !!!"<<endl;
      health = 0;
      return;
    }
    cout<<"Murloc's health after getting attacked is "<<health<<'\n';
  } 
};

enum PlayerState{
dead,
alive
};

void gameTitle(){
  //GAME NAME printing
  system("clear");
  cout<<'*'<<setfill('*')<<setw(101)<<'*'<<endl;
  cout<<'*'<<setfill(' ')<<setw(101)<<right<<'*'<<endl;
  cout<<'*'<<setfill(' ')<<setw(101)<<right<<'*'<<endl;
  cout<<'*'<<setfill(' ')<<std::string(40, ' ' )<<setw(60)<<left<<"Infinity Castle"<<'*'<<endl;
  cout<<'*'<<setfill(' ')<<setw(101)<<right<<'*'<<endl;
  cout<<'*'<<setfill(' ')<<setw(101)<<right<<'*'<<endl;
  cout<<'*'<<setfill('*')<<setw(101)<<'*'<<endl<<endl;
  //--------------------------------------------------------------------------------------------
  cout<<"Dare to enter the Infinity Castle ? \n";
  cout<<"Demon king Murloc and his henchmen have spread terror across the land.\n";
  cout<<"Infiltrate the castle and kill all the enemies...\n\n\n";
}

void healthStats(Player &player, Enemy *enemy)
{
  cout<<'-'<<setfill('-')<<setw(32)<<'-'<<endl;
  cout<<'|'<<setfill(' ')<<std::string(3, ' ' )<<setw(12)<<left<<" Player"<<'|';
  cout<<setfill(' ')<<std::string(4, ' ' )<<setw(11)<<left<<enemy->getName()<<'|'<<endl;
  cout<<'|'<<std::string(3, ' ' )<<setfill(' ')<<setw(4)<<right<<player.getHealth()<<"/"  
    <<setw(4)<<left<<player.getFullHealth()<<setw(4)<<right<<'|';
  cout<<std::string(3, ' ' )<<setfill(' ')<<setw(4)<<right<<enemy->getHealth()<<"/"
    <<setw(4)<<left<<enemy->getFullHealth()<<setw(4)<<right<<'|'<<endl;
  cout<<'-'<<setfill('-')<<setw(32)<<'-'<<endl;

  if(enemy->minionEnabled())
  {
    cout<<'-'<<setfill('-')<<setw(16)<<'-'<<endl;
    cout<<'|'<<setfill(' ')<<std::string(3, ' ' )<<setw(12)<<left<<" Minion"<<'|'<<endl;
    cout<<'|'<<std::string(3, ' ' )<<setfill(' ')<<setw(4)<<right<<enemy->getMinionHealth()<<"/"
    <<setw(4)<<left<<"150"<<setw(4)<<right<<'|'<<endl;
    cout<<'-'<<setfill('-')<<setw(16)<<'-'<<endl;
  }
}

PlayerState battleloop(Player &player,Enemy *enemy)
{
  char move;
  do
  {
    healthStats(player,enemy);
    Start:
    cout<<"\nPress A to attack or H to Heal\n";
    cin>>move;
    cout<<'\n';
    if (move == 'A' or move == 'a')
    {
      enemy->TakeDamage(player.GiveDamage());
    }
    else if (move == 'H' || move == 'h')
    {
      player.Healing();
      cout<<"Enemy health remaining is: "<<enemy->getHealth()<<'\n';
    }
    else 
    {
      cout<<"Invalid Input ! \n\n";
      goto Start;
    }
    //Enemy Death Condition Check
    if (enemy->getHealth()<=0) 
    {
      cout<<'-'<<setfill('-')<<setw(101)<<'-'<<endl;
      break;
    }
    //Enemy's turn
    cout<<'\n';
    player.TakeDamage(enemy->GiveDamage());
    cout<<'\n';
    cout<<'-'<<setfill('-')<<setw(101)<<'-'<<endl;
  }while(player.getHealth()>0 && enemy->getHealth()>0);
  
  //Return according to Player death condition
  if (player.getHealth() <=0)
    return dead;      //Player Dead
  else
    return alive;      //Player Alive
}

class LevelManager {
  int level;
  int gCount;
  int vCount;
  Enemy *enemy;
  Player player;
  PlayerState death = alive;
  
  public:
  PlayerState Level()
  {
    level = player.getLevel();
    gCount = (level<=3) ? level : 3;
    vCount = (level>3) ? (level-3) : 0;
    
    //output message
    cout<<'\n'<<'+'<<setfill('+')<<setw(101)<<'+'<<endl;
    switch(level)
      {
        case 1: cout<<"\nLevel 1 : Defeat the Guard !!!\n";
          break;
        case 2: cout<<"\nLevel 2 : Defeat two Guards !!!\n";
          break;
        case 3: cout<<"\nLevel 3 : Defeat three Guards !!!\n";
          break;
        case 4: cout<<"\nLevel 4 : Defeat three Guards and a Vanguard !!!\n";
          break;
        case 5: cout<<"\nLevel 5 : Defeat three Guards and two Vanguards !!!\n";
          break;
        case 6: cout<<"\nLevel 6 : Defeat Murloc the Demon King !!!\n";
      }
    cout<<'\n'<<'+'<<setfill('+')<<setw(101)<<'+'<<endl;

    if (level == 6)
    {
      enemy = new Murloc;
      death = battleloop(player, enemy);
      delete enemy;
    }
    else
    {
      for(int g=1; g<=gCount; g++)
        {
          enemy = new Guard;
          cout<<"\nGuard "<<g<<" appeared !\n";
          death = battleloop(player, enemy);
          delete enemy;
        }
      for(int v=1; v<=vCount && v>0; v++)
        {
          enemy = new Vanguard;
          cout<<"\nVanguard "<<v<<" appeared !\n";
          death = battleloop(player, enemy);
          delete enemy;
        }
    }
    player.levelUP();
    return death;
  }

};

int main() 
{
  char userInput;
  gameTitle();
  do{
    cout<<"Press S to start the Game or any other key to exit\n";
    cin>>userInput;
    cout<<"\n\n";
    if (userInput != 'S' && userInput != 's') {return 0;}
    LevelManager levelObj;
    PlayerState n;
    for (int i = 1; i<=6; i++)
      {
        n = levelObj.Level();
        if (n==dead)
        {
          cout<<"\nGAME OVER !!!\n";
          break;
        }  
      }
    if (n == alive)
    {
      cout<<"Congrats !!! You defeated Murloc and cleared the troops in Infinity Castle. Glory awaits you young warrior !!\n\n"; 
    }
  }while(userInput == 'S' || userInput == 's');
  
  return 0;
}
