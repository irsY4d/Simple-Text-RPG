#include <iostream>
#include <vector>
#include <ctime>

using namespace std;

//class konstanta
const int MAX_HEALTH = 15;

//Class player
class Player {
protected:
	int m_attack = 0;
	int m_armor = 0;
	int m_magic = 0;
	int m_health = 0;
	string m_gender = "";
public:
	Player(string gender, int health, int attack, int armor, int magic);//konstruktor
	vector<string> inventory;
	void createPlayer();
	void showPlayerInfo();
	void randStat(int& health, int& atk, int& armor, int& magic);
	void setInit(int health, int attack, int armor, int magic);
	void Attack(int damage, int health);
};

Player::Player(string gender, int health, int attack, int armor, int magic):m_gender(gender), m_health(health), m_attack(attack), m_armor(armor), m_magic(magic) {}

void Player::createPlayer() {
	vector<string> inv {"Sword",  "Bow",  "Axe", "Magic Book"};
	int choose_gender =0;
	int choose_weapon =0;

	//Create Player
	cout << "Create Player: " << endl;

	do {
		cout << "1. Male, 2. Female" << endl;
		cout << "Choose your gender: ";
		cin >> choose_gender;

		if (choose_gender == 1) {
			m_gender = "Male";
		} else if (choose_gender == 2) {
			m_gender = "Female";
		} else {
			cout << "invalid" << endl;
			//continue;
		}
	} while (choose_gender != 1 && choose_gender != 2);


	//Choose Weapon
	do {
		cout << "1. Sword, 2. Bow, 3. Axe, 4. Magic Book" << endl;
		cout << "Choose your weapon : ";
		cin >> choose_weapon;

		switch (choose_weapon) {
		case 1: {
			inventory.push_back(inv[0]);
			break;
		}

		case 2: {
			inventory.push_back(inv[1]);
			break;
		}

		case 3: {
			inventory.push_back(inv[2]);
			break;
		}

		case 4: {
			inventory.push_back(inv[3]);
			break;
		}

		default: {
			cout << "invalid" << endl;
			break;
			//continue;
		}
		}
	} while (choose_weapon < 1 || choose_weapon > 4);

	cout << "your character is " << m_gender << " and your weapon is " << inventory.back() << endl;
}

void Player::showPlayerInfo() {
	char q1 = 'y';
	vector<string>::iterator penunjuk;
	cout << "do you wanna see your character info? [y/n]: ";
	cin >> q1;

	if (q1 == 'y') {
		// Showing character information
		cout << "Player Info:" << endl;
		cout << "Gender: " << m_gender << endl;
		cout << "Inventory: "<< endl;
		for (penunjuk=inventory.begin(); penunjuk!=inventory.end(); ++penunjuk) {
			cout << *penunjuk << endl;
		}
		cout << "Stat: " << endl;
		cout << "HP : " << m_health << endl;
		cout << "Attack : " << m_attack << endl;
		cout << "Armor : " << m_armor << endl;
		cout << "Magic : " << m_magic << endl;
	}
}

void Player::randStat(int& health, int& atk, int& armor, int& magic) {
	health = MAX_HEALTH;
	do {
		atk = rand() % 10;
	} while (atk <= 5);
	do {
		armor = rand() % 9;
	} while (armor <= 2);
	magic = rand() % 5;
}

void Player::Attack(int damage, int health) {
	damage = m_attack;
	health = max(0, health-damage);

	cout << "You attack!! Damage: " << damage << endl;
	cout << "Enemy HP: " << health << endl;
}

void Player::setInit(int health, int attack, int armor, int magic) {
	m_health = health;
	m_attack = attack;
	m_armor = armor;
	m_magic= magic;
}


//class Enemy
class Enemy {
public :
	string m_name="";
	int m_health=0;
	int m_attack=0;
	int m_armor=0;
	virtual void EnemyAttack(int health);
	virtual void ShowEnemyInfo();
	Enemy(string name, int health, int attack, int armor);
};

Enemy::Enemy(string name, int health, int attack, int armor):m_health(health), m_name(name), m_attack(attack), m_armor(armor) {

}

void Enemy::EnemyAttack(int health) {
	int damage = m_attack;
	health = min(MAX_HEALTH, health-damage);

	cout << "Enemy Attack you! Damage: " << damage << endl;
	cout << "Your HP: " << health << endl;
}

void Enemy::ShowEnemyInfo() {
	cout << "Enemy Info: " << endl;
	cout << "Name  : " << m_name << endl;
	cout << "Health: " << m_health << endl;
	cout << "Attack: " << m_attack << endl;
	cout << "Armor : " << m_armor << endl;
}

//child class
class Zombie : public Enemy {
public:
	Zombie();
};

Zombie::Zombie(): Enemy("Zombie", 8, 2, 0) {}

class Skeleton : public Enemy {
public:
	Skeleton();
};

Skeleton::Skeleton(): Enemy("Skeleton", 3, 8, 5) {}

class Ogre : public Enemy {
public:
	Ogre();
};

Ogre::Ogre(): Enemy("Ogre", 10, 5, 7) {}

class Dragon : public Enemy {
public:
	Dragon();
};

Dragon::Dragon(): Enemy("Dragon", 15, 9, 10) {}


void startBattle(bool& gameAction, int& stat_health, int& stat_atk_rand, int& stat_armor_rand, int& stat_magic_rand, int& enemy_health, int& enemy_attack, int& enemy_armor);

int main() {
	//initialization
	int menu_select=0; //main menu
	int playermove = 0; //choosing menu action
	srand(static_cast<unsigned int>(time(0)));
	char again = 'y';
	//stat Player
	int stat_health=0;
	int stat_atk_rand = 0;
	int stat_armor_rand = 0;
	int stat_magic_rand = 0;


	//gameloop
	while (again == 'y') {
		//Game Menu
		cout << "Welcome to the game!!" << endl;
		cout << "1. Play" << endl;
		cout << "2. Exit" << endl;
		cout << "Select: ";
		cin >> menu_select;


		switch(menu_select) {
		case 1: { // Play
			bool gameAction = true;
			//Create Object Player
			Player p1( "", 0, 0, 0, 0);
			p1.randStat(stat_health,stat_atk_rand, stat_armor_rand, stat_magic_rand);
			p1.setInit(stat_health, stat_atk_rand, stat_armor_rand, stat_magic_rand);
			p1.createPlayer();
			p1.showPlayerInfo();

			cout << "Game Starting!" << endl;
			while(gameAction) {
				//menu action
				cout << "\nMain Menu Action: " << endl;
				cout << "1. Move" << endl;
				cout << "2. Break" << endl;
				cout << "3. Player info" << endl;
				cout << "4. Exit to Menu" << endl;
				cout << "Select an action: ";
				cin >>  playermove;
				switch(playermove) {
				case 1: {
					cout << "your character is moving...." << endl;

					//chance to meet the enemy
					//srand(static_cast<unsigned int>(time(0)));
					int chance = rand() % 2;

					if (chance == 0) {
						// Enemy pool
						vector<Enemy*> enemies = {new Zombie(), new Skeleton(), new Ogre(), new Dragon()};

						// Randomly select enemy
						int enemyEncounterIndex = rand() % enemies.size();
						Enemy* currentEnemy = enemies[enemyEncounterIndex];
						cout << "\nyou encountered enemy... " << endl;
						currentEnemy->ShowEnemyInfo();

						//save information about hp, atk, armor
						int enemy_health = currentEnemy->m_health;
						int enemy_attack = currentEnemy->m_attack;
						int enemy_armor = currentEnemy->m_armor;

						//escape option
						int chance_escape = rand() % 3;
						char q2;

						cout <<"\nare you trying to escape?[y/n]: ";
						cin >>  q2;

						do {
							if (q2 == 'y') {
								if (chance_escape == 0) {
									cout << "You successfully escaped!" << endl;
								} else if (chance_escape == 1) {
									cout << "You failed to escape!" << endl;
									startBattle(gameAction, stat_health, stat_atk_rand, stat_armor_rand, stat_magic_rand, enemy_health, enemy_attack, enemy_armor);
									enemies.erase(enemies.begin() + enemyEncounterIndex);
									cout << "Remaining enemies: " << enemies.size() << endl;

									if (stat_health <= 0) {
										//promptPlayAgain(again, gameAction, health, attack, armor, magic, inventory, gender);
									}
								}
								break;

							} else if (q2 == 'n') {
								cout << "You chose to fight!" << endl;
								startBattle(gameAction, stat_health, stat_atk_rand, stat_armor_rand, stat_magic_rand, enemy_health, enemy_attack, enemy_armor);
								enemies.erase(enemies.begin() + enemyEncounterIndex);
								cout << "Remaining enemies: " << enemies.size() << endl;

								if (stat_health <= 0) {
									//promptPlayAgain(again, gameAction, health, attack, armor, magic, inventory, gender);
								}
								break; // Keluar dari loop jika input valid dan ditangani
							} else {
								cout << "Invalid input. Please enter 'y' or 'n'." << endl;
							}
						} while (true);

						if (enemies.empty()) {
							cout << "\nCongratulations! You have defeated all the enemies!\n";
							gameAction = false;
							cout << "Returning to main menu...." << endl;
						}




					} else {
						cout << "you did not encountered any enemy.." << endl;
					}

					break;
				}

				case 2: {
					cout << "your character break for a moment...." << endl;
					break;
				}

				case 3: {
					p1.showPlayerInfo();
					break;
				}

				case 4: {
					cout << "Are you sure you wanna exit to main menu?[y/n] ";
					cin >> again;
					if (again == 'y') {
						gameAction = false;
						cout << "Returning to Main Menu.... " << endl;
					}
					break;
				}

				default : {
					cout << "invalid" << endl;
					break;
				}
				}
			}

			break;
		}

		case 2: { // Exit
			again = 'n';
			break;
		}

		default: { // invalid
			cout << "invalid" << endl;
			break;
		}
		}

	}

	cout << "Thanks for Playing!" << endl;

	// Pokemon poke1("Feli", 8, 10, 11);
	// poke1.Speak();

	return 0;
}


void startBattle(bool& gameAction, int& stat_health, int& stat_atk_rand, int& stat_armor_rand, int& stat_magic_rand, int& enemy_health, int& enemy_attack, int& enemy_armor) {
	int action = 0;
	int defendArmor = 0;
	int tempArmor = 0;
	int tempEnemyArmor = 0;
	bool isDefending = false;
	bool enemyDefending = false;

	cout << "\nBattle Started !!" << endl;
	srand(static_cast<unsigned int>(time(0)));
	int turn = rand() % 2;

	while (stat_health > 0 && enemy_health > 0) {

		if (turn == 0) {
			//player turn
			cout << "\nYour Turn's!" << endl;
			cout << "Choose your action: " << endl;
			cout << "1. Attack" << endl;
			cout << "2. Defend" << endl;
			cout << "3. Throw  Magic" << endl;
			cout << "your action: ";
			cin >> action;

			switch(action) {
			case 1: { // Attack
				cout<< "you attack enemy! " << endl;

				int damage = stat_atk_rand;
				tempEnemyArmor = enemy_armor;

				if(enemyDefending) {
					tempEnemyArmor += 2;
					if (tempEnemyArmor >= damage) {
						enemy_health = max(0, enemy_health - damage/2);
						cout << "\nyour damage less than enemy armor the damage has half" << endl;
					} else {
						enemy_health = max(0, enemy_health - damage);
						cout << "Your damage exceeds enemy armor, damage applied!" << endl;
					}
				} else {
					if (enemy_armor >= damage) {
						enemy_health = max(0, enemy_health - damage/2);
						cout << "\nyour damage less than enemy armor the damage has half" << endl;
					} else {
						enemy_health = max(0, enemy_health - damage);
						cout << "Your damage exceeds enemy armor, damage applied!" << endl;
					}
				}


				cout << "you dealt " << damage << " attack damage to enemy" << endl;
				cout << "enemy health: " << enemy_health << endl;
				isDefending = false;
				break;
			}

			case 2: { // Defend
				cout << "you defend yourself!" << endl;
				cout << "your armor +1 until the end of the turn" << endl;
				defendArmor = 1;
				isDefending = true;
				break;
			}

			case 3: { //Throw Magic
				cout << "you throw a magic!" << endl;

				if (stat_magic_rand > 0) {
					int magic_damage = stat_atk_rand * 2;
					enemy_health = max(0, enemy_health - magic_damage);
					stat_magic_rand--;

					cout << "you dealt " << magic_damage << " magic damage to enemy" << endl;
					cout << "your have " << stat_magic_rand<< " magic energy point left" << endl;
				} else {
					cout << "you dont have enough magic energy!" << endl;
				}

				cout << "enemy health: " << enemy_health << endl;
				isDefending = false;
				break;
			}

			default: {
				cout << "your action invalid!!" << endl;
				break;
			}
			}

		} else {
			//enemies turn
			cout << "\nEnemies Turn's" << endl;
			int enemy_action = rand() % 2;

			if(enemy_action == 0) {
				cout << "Enemy Attack you!" << endl;

				int enemy_dmg = enemy_attack;
				tempArmor = stat_armor_rand + defendArmor;

				if (isDefending) {
					cout << "your Armor: " << tempArmor << endl;
					if (enemy_dmg <= tempArmor) {
						stat_health = max(0, stat_health - enemy_dmg/2);
						cout << "enemy damage less than your armor the damage taken has half" << endl;
					}   else {
						stat_health = max(0, stat_health - enemy_dmg);
						cout << "Enemy damage exceeds your armor, full damage applied." << endl;
					}
				} else {
					if (enemy_dmg <= stat_armor_rand) {
						stat_health = max(0, stat_health - enemy_dmg/2);
						cout << "enemy damage less than your armor, the damage taken has half" << endl;
					} else {
						stat_health = max(0, stat_health - enemy_dmg);
						cout << "Enemy damage exceeds your armor, full damage applied." << endl;
					}
				}

				isDefending = false;// reset to default

				cout << "the Enemy dealt " << enemy_dmg << " to you!" << endl;
				cout << "your health: " << stat_health << endl;
				enemyDefending = false;
			} else {
				cout << "Enemy choose to Defend" << endl;
				cout << "Enemy armor +2 until the end of turn" << endl;
				enemyDefending = true;
			}

		}


		//check who lose the fight
		if (stat_health <= 0) {
			cout << "you have been defeated!" << endl;
			gameAction = false;
		} else if (enemy_health <= 0) {
			cout << "you defeated the enemy!" << endl;
			//dropItem(inventory);
			//showPlayerInfo();
		}

		turn = !turn; //change turn
	}
}
