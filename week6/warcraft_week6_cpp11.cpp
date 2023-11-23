#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <iomanip>
#include <set>
#include <algorithm>
#include <fstream>

#define TIE 0
#define WIN 1
#define LOSE 2

#define USE_INPUT_FILE 1

using namespace std;
class Weapon;
class Headquarter;
class City;
int currentTime = 0;
int currentMin = 0;
int M, N, R, K, T;

class Weapon
{
    friend class Warrior;

public:
    int attack;
    // virtual void Use(Warrior *warrior){};
    virtual ~Weapon() {}
};

class Sword : public Weapon
{
    int durability;
};

class Bomb : public Weapon
{
    int durability;
};

class Arrow : public Weapon
{
    int durability;
    int left_cnt_to_use = 3;

public:
    void Decrease_left_cnt_to_use()
    {
        left_cnt_to_use--;
    }

    int Get_left_cnt_to_use()
    {
        return left_cnt_to_use;
    }
};

class Warrior
{
public:
    int hp;
    int id;
    int attack;
    int pos;
    int init_pos;
    bool dormant;
    map<int, Weapon *> weapons;

public:
    static map<string, int> INIT_HP;
    static map<string, int> ATTACK;
    static map<int, string> weapon_type;
    Headquarter *headquarter;

    Warrior(int id, int hp, int attack, Headquarter *hq, int pos) : id(id), hp(hp), attack(attack), headquarter(hq), pos(pos)
    {
        init_pos = pos;
        dormant = false;
    }

    virtual void Attack(Warrior *warrior);

    virtual void Fight_back(Warrior *warrior);

    virtual string Get_type() = 0;

    virtual void After_fight(Warrior *enemy, int win_state, int enemy_hp_before_fight);

    virtual void March(vector<City *> &cities, Headquarter &red, Headquarter &blue);

    void Report_weapon();

    bool Dormant()
    {
        return dormant;
    }

    void Set_dormant(bool dormant)
    {
        this->dormant = dormant;
    }

    int Get_hp()
    {
        return hp;
    }

    void Set_hp(int hp)
    {
        this->hp = hp;
    }

    void Set_pos(int pos)
    {
        this->pos = pos;
    }

    void Add_hp(int hp)
    {
        this->hp += hp;
    }

    int Get_id()
    {
        return id;
    }

    int Get_attack()
    {
        return attack;
    }

    int Get_pos()
    {
        return pos;
    }

    bool CantBeat(Warrior *warrior, City *city);

    virtual ~Warrior()
    {
        for (auto i : weapons)
        {
            delete i.second;
        }
    }
};

// map<string, int> Warrior::INIT_HP;
map<int, string> Warrior::weapon_type;

class Dragon : public Warrior
{
    int weapon_type_idx;
    double morale;

public:
    Dragon(int id, int hp, int attack, int weapon_type_idx, double morale, Headquarter *hq, int pos) : Warrior(id, hp, attack, hq, pos), weapon_type_idx(weapon_type_idx), morale(morale)
    {
        if (weapon_type_idx == 0)
        {
            int temp = (int)(attack * 0.2);
            if (temp > 0){
                weapons[0] = new Sword();
                weapons[0]->attack = (int)(attack * 0.2);
            }
        }
        else if (weapon_type_idx == 1)
        {
            weapons[1] = new Bomb();
        }
        else if (weapon_type_idx == 2)
        {
            weapons[2] = new Arrow();
        }
    }
    virtual void Attack(Warrior *warrior)
    {
        Warrior::Attack(warrior);
    }
    virtual void Fight_back(Warrior *warrior)
    {
        Warrior::Fight_back(warrior);
    }

    double Get_morale()
    {
        return morale;
    }

    virtual void After_fight(Warrior *enemy, int win_state, int enemy_hp_before_fight) override // 0: tie, 1: win, 2: lose
    {
        Warrior::After_fight(enemy, win_state, enemy_hp_before_fight);
        if (win_state == WIN)
        {
            morale += 0.2;
        }
        else
        {
            morale -= 0.2;
        }
    }

    void Decrease_morale(double decrease_rate)
    {
        morale -= decrease_rate;
    }

    void Increase_morale(double increase_rate)
    {
        morale += increase_rate;
    }

    void Yell();

    virtual string Get_type()
    {
        return "dragon";
    }
};

class Ninja : public Warrior
{
    int weapon_type_idx1;
    int weapon_type_idx2;

public:
    Ninja(int id, int hp, int attack, int weapon_type_idx1, int weapon_type_idx2, Headquarter *hq, int pos) : Warrior(id, hp, attack, hq, pos), weapon_type_idx1(weapon_type_idx1), weapon_type_idx2(weapon_type_idx2)
    {
        if (weapon_type_idx1 == 0)
        {
            int temp = (int)(attack * 0.2);
            if (temp > 0){
                weapons[0] = new Sword();
                weapons[0]->attack = (int)(attack * 0.2);
            }
        }
        else if (weapon_type_idx1 == 1)
        {
            weapons[1] = new Bomb();
        }
        else if (weapon_type_idx1 == 2)
        {
            weapons[2] = new Arrow();
        }

        if (weapon_type_idx2 == 0)
        {
            int temp = (int)(attack * 0.2);
            if (temp > 0){
                weapons[0] = new Sword();
                weapons[0]->attack = (int)(attack * 0.2);
            }
        }
        else if (weapon_type_idx2 == 1)
        {
            weapons[1] = new Bomb();
        }
        else if (weapon_type_idx2 == 2)
        {
            weapons[2] = new Arrow();
        }
    }
    virtual void Attack(Warrior *warrior)
    {
        Warrior::Attack(warrior);
    }
    virtual void Fight_back(Warrior *warrior)
    {
        Warrior::Fight_back(warrior);
    }
    virtual string Get_type()
    {
        return "ninja";
    }

    virtual void After_fight(Warrior *enemy, int win_state, int enemy_hp_before_fight) override
    {
        Warrior::After_fight(enemy, win_state, enemy_hp_before_fight);
    }
};

class Iceman : public Warrior
{
    int weapon_type_idx;
    int step_cnt;

public:
    Iceman(int id, int hp, int attack, int weapon_type_idx, Headquarter *hq, int pos) : Warrior(id, hp, attack, hq, pos), weapon_type_idx(weapon_type_idx), step_cnt(0)
    {
        if (weapon_type_idx == 0)
        {
            int temp = (int)(attack * 0.2);
            if (temp > 0){
                weapons[0] = new Sword();
                weapons[0]->attack = (int)(attack * 0.2);
            }
        }
        else if (weapon_type_idx == 1)
        {
            weapons[1] = new Bomb();
        }
        else if (weapon_type_idx == 2)
        {
            weapons[2] = new Arrow();
        }
    }
    virtual void Attack(Warrior *warrior)
    {
        Warrior::Attack(warrior);
    }
    virtual void Fight_back(Warrior *warrior)
    {
        Warrior::Fight_back(warrior);
    }
    virtual string Get_type()
    {
        return "iceman";
    }

    virtual void March(vector<City *> &cities, Headquarter &red, Headquarter &blue) override
    {
        if (pos != init_pos && (pos == 0 || pos == N + 1))
        {
            return;
        }
        step_cnt++;
        if (step_cnt == 2)
        {
            if (hp > 9)
            {
                hp -= 9;
                attack += 20;
            }
            else
            {
                hp = 1;
                attack += 20;
            }
            step_cnt = 0;
        }
        Warrior::March(cities, red, blue);
    }

    virtual void After_fight(Warrior *enemy, int win_state, int enemy_hp_before_fight) override
    {
        Warrior::After_fight(enemy, win_state, enemy_hp_before_fight);
    }
};

class Lion : public Warrior
{
    int loyalty;

public:
    Lion(int id, int hp, int attack, int loyalty, Headquarter *hq, int pos) : Warrior(id, hp, attack, hq, pos), loyalty(loyalty) {}
    virtual void Attack(Warrior *warrior)
    {
        Warrior::Attack(warrior);
    }
    virtual void Fight_back(Warrior *warrior)
    {
        Warrior::Fight_back(warrior);
    }

    int Get_loyalty()
    {
        return loyalty;
    }

    virtual string Get_type()
    {
        return "lion";
    }

    void Decrease_loyalty(const int K)
    {
        loyalty -= K;
    }

    virtual void After_fight(Warrior *enemy, int win_state, int enemy_hp_before_fight) override; // 0: tie, 1: win, 2: lose
};

class Wolf : public Warrior
{
public:
    Wolf(int id, int hp, int attack, Headquarter *hq, int pos) : Warrior(id, hp, attack, hq, pos) {}
    virtual void Attack(Warrior *warrior)
    {
        Warrior::Attack(warrior);
    }
    virtual void Fight_back(Warrior *warrior)
    {
        Warrior::Fight_back(warrior);
    }

    virtual string Get_type()
    {
        return "wolf";
    }

    virtual void After_fight(Warrior *enemy, int win_state, int enemy_hp_before_fight) override
    {
        Warrior::After_fight(enemy, win_state, enemy_hp_before_fight);
        if (win_state == 1)
        {
            if (enemy->weapons.find(0) != enemy->weapons.end())
            {
                weapons[0] = enemy->weapons[0];
                enemy->weapons.erase(0);
            }
            if (enemy->weapons.find(1) != enemy->weapons.end())
            {
                weapons[1] = enemy->weapons[1];
                enemy->weapons.erase(1);
            }
            if (enemy->weapons.find(2) != enemy->weapons.end())
            {
                weapons[2] = enemy->weapons[2];
                enemy->weapons.erase(2);
            }
        }
    }
};

class City
{
public:
    int id;
    int hp;
    string flagColor;
    Warrior *warriors_red;
    Warrior *warriors_blue;
    vector<Weapon *> weapons;
    string last_winner;
    // int last_winner_cnt;
    // int last_winner_flag;

public:
    City(int id) : id(id), hp(0), flagColor("none"), last_winner("none")
    {
        warriors_red = NULL;
        warriors_blue = NULL;
        for (int i = 0; i < 3; i++)
        {
            weapons.push_back(NULL);
        }
    }
    int Get_hp()
    {
        return hp;
    }

    void Raise_flag(string winner)
    {
        if (winner != "none" && last_winner == winner)
        {
            if (flagColor != winner)
            {
                cout << setfill('0') << setw(3) << currentTime << ":40 " << winner << " flag raised in city " << id << endl;
            }
            flagColor = winner;
        }
        if (winner != "none")
            last_winner = winner;
    }
};

class Headquarter
{
    int cur_hp;
    vector<Warrior *> warriors;
    vector<string> warrior_order;
    string hq_name;
    vector<Warrior *> warriors_to_reward;
    vector<int> cities_to_recycle_hp;

    friend class Warrior;

public:
    map<string, int> warrior_num;
    // map<int, string> warrior_id2type;
    int total_warrior_num;
    int cur_warrior_type_idx;
    int taken_over_cnt;
    // bool win_flag;

    Headquarter(int hp, vector<string> &in_warrior_order, string hq_name) : cur_hp(hp), warrior_order(in_warrior_order), total_warrior_num(0), cur_warrior_type_idx(0), taken_over_cnt(0), hq_name(hq_name)
    {
        warriors_to_reward = {};
        for (int i = 0; i < warrior_order.size(); i++)
        {
            warrior_num[warrior_order[i]] = 0;
        }
        // Warrior::set_init_hp(in_init_hp);
    }

    void Remove(Warrior *warrior)
    {
        for (int i = 0; i < warriors.size(); i++)
        {
            if (warriors[i] == warrior)
            {
                warriors.erase(warriors.begin() + i);
                break;
            }
        }
    }

    void Reset_temp_data()
    {
        warriors_to_reward.clear();
        cities_to_recycle_hp.clear();
    }

    int Get_taken_over_cnt()
    {
        return taken_over_cnt;
    }

    int Get_hp()
    {
        return cur_hp;
    }

    void Add_hp(int hp)
    {
        cur_hp += hp;
    }

    void Add_warrior(string warrior_type)
    {
        Warrior *warrior;
        total_warrior_num++;
        warrior_num[warrior_type]++;
        cur_hp -= Warrior::INIT_HP[warrior_type];
        int need_hp = Warrior::INIT_HP[warrior_type], attack = Warrior::ATTACK[warrior_type];
        cout << setfill('0') << setw(3) << currentTime << ":00 " << hq_name << " " << warrior_type << " " << total_warrior_num << " born" << endl;
        int init_pos = (hq_name == "red" ? 0 : N + 1);
        if (warrior_type == "dragon")
        {
            int weapon_type_idx = total_warrior_num % 3;
            warrior = new Dragon(total_warrior_num, need_hp, attack, weapon_type_idx, (double)cur_hp / need_hp, this, init_pos);
            cout << "Its morale is " << fixed << setprecision(2) << (double)cur_hp / need_hp << endl;
        }
        else if (warrior_type == "ninja")
        {
            int weapon_type_idx1 = total_warrior_num % 3, weapon_type_idx2 = (total_warrior_num + 1) % 3;
            warrior = new Ninja(total_warrior_num, need_hp, attack, weapon_type_idx1, weapon_type_idx2, this, init_pos);
            // cout << "It has a " << Warrior::weapon_type[weapon_type_idx1] << " and a " << Warrior::weapon_type[weapon_type_idx2] << endl;
        }
        else if (warrior_type == "iceman")
        {
            int weapon_type_idx = total_warrior_num % 3;
            warrior = new Iceman(total_warrior_num, need_hp, attack, weapon_type_idx, this, init_pos);
            // cout << "It has a " << Warrior::weapon_type[weapon_type_idx] << endl;
        }
        else if (warrior_type == "lion")
        {
            warrior = new Lion(total_warrior_num, need_hp, attack, cur_hp, this, init_pos);
            cout << "Its loyalty is " << cur_hp << endl;
        }
        else if (warrior_type == "wolf")
        {
            warrior = new Wolf(total_warrior_num, need_hp, attack, this, init_pos);
        }

        warriors.push_back(warrior);
    }

    vector<string> &Get_warrior_order()
    {
        return warrior_order;
    }

    void Reward_warriors()
    {
        if (hq_name == "red")
        {
            std::sort(warriors_to_reward.begin(), warriors_to_reward.end(), [](Warrior *a, Warrior *b)
                      { return a->Get_pos() > b->Get_pos(); });
        }
        else
        {
            std::sort(warriors_to_reward.begin(), warriors_to_reward.end(), [](Warrior *a, Warrior *b)
                      { return a->Get_pos() < b->Get_pos(); });
        }
        for (int i = 0; i < warriors_to_reward.size() && cur_hp >= 8; i++, cur_hp -= 8)
        {
            // cout << hq_name << " reward " << warriors_to_reward[i]->Get_type() << " " << warriors_to_reward[i]->Get_id() << " 8 elements" << endl;
            warriors_to_reward[i]->Add_hp(8);
        }
    }

    void Recycle_hp_from_city(vector<City *> &cities)
    {
        for (auto i : cities_to_recycle_hp)
        {
            cur_hp += cities[i]->Get_hp();
            cities[i]->hp = 0;
        }
    }

    void Lion_run_away(vector<City *> &cities)
    {
        for (int i = 0; i < warriors.size(); i++)
        {
            if (warriors[i]->Get_type() == "lion" && dynamic_cast<Lion *>(warriors[i])->Get_loyalty() <= 0)
            {
                cout << setfill('0') << setw(3) << currentTime << ":05 " << hq_name << " lion " << warriors[i]->Get_id() << " ran away" << endl;
                if (warriors[i]->headquarter->Get_hq_name() == "red")
                {
                    cities[warriors[i]->Get_pos()]->warriors_red = NULL;
                }
                else
                {
                    cities[warriors[i]->Get_pos()]->warriors_blue = NULL;
                }
                delete warriors[i];
                warriors.erase(warriors.begin() + i);
            }
        }
    }

    string Get_hq_name()
    {
        return hq_name;
    }

    void Add_warrior_to_reward(Warrior *warrior)
    {
        warriors_to_reward.push_back(warrior);
    }

    void Add_city_to_recycle_hp(int pos)
    {
        cities_to_recycle_hp.push_back(pos);
    }

    vector<Warrior *> &Get_warriors()
    {
        return warriors;
    }

    void Lion_loyalty_decrease()
    {
        for (int i = 0; i < warriors.size(); i++)
        {
            if (warriors[i]->Get_type() == "lion")
            {
                dynamic_cast<Lion *>(warriors[i])->Decrease_loyalty(K);
            }
        }
    }

    void Dragon_morale_decrease()
    {
        for (int i = 0; i < warriors.size(); i++)
        {
            if (warriors[i]->Get_type() == "dragon")
            {
                // cout << "dragon id: " << warriors[i]->Get_id() << "decrease dragon morale, original: " << dynamic_cast<Dragon *>(warriors[i])->Get_morale() << endl;
                dynamic_cast<Dragon *>(warriors[i])->Decrease_morale(0.2);
            }
        }
    }

    void Dragon_morale_increase()
    {
        for (int i = 0; i < warriors.size(); i++)
        {
            if (warriors[i]->Get_type() == "dragon")
            {
                // cout << "dragon id: " << warriors[i]->Get_id() << "increase dragon morale, original: " << dynamic_cast<Dragon *>(warriors[i])->Get_morale() << endl;
                dynamic_cast<Dragon *>(warriors[i])->Increase_morale(0.2);
            }
        }
    }

    ~Headquarter()
    {
        for (int i = 0; i < warriors.size(); i++)
        {
            delete warriors[i];
        }
    }
};

void Lion::After_fight(Warrior *enemy, int win_state, int enemy_hp_before_fight)
{
    Warrior::After_fight(enemy, win_state, enemy_hp_before_fight);
    if (win_state != WIN)
    {
        // cout << headquarter->Get_hq_name() << " lion " << id << " loyalty decrease by " << K << ", original: " << loyalty << endl;
        loyalty -= K;
    }
}

bool Warrior::CantBeat(Warrior *enemy, City *city)
{
    // if (enemy->Get_type() == "ninja" || enemy->hp <= 0)
    bool enemy_attack_first = ((enemy->headquarter->Get_hq_name() == "red") && (city->flagColor == "red" || (city->flagColor == "none" && pos % 2 == 1))) ||
                              ((enemy->headquarter->Get_hq_name() == "blue") && (city->flagColor == "blue" || (city->flagColor == "none" && pos % 2 == 0)));
    if (enemy->hp <= 0)
        return false;
    // bool can_survive_active_attack = false, can_survive_pass_attack = false;
    int self_active_attack = attack, self_passive_attack = attack / 2;
    self_active_attack += (weapons.find(0) != weapons.end() ? weapons[0]->attack : 0);
    self_passive_attack += (weapons.find(0) != weapons.end() ? weapons[0]->attack : 0);

    int enemy_active_attack = enemy->attack, enemy_passive_attack = enemy->attack / 2;
    enemy_active_attack += (enemy->weapons.find(0) != enemy->weapons.end() ? enemy->weapons[0]->attack : 0);
    enemy_passive_attack += (enemy->weapons.find(0) != enemy->weapons.end() ? enemy->weapons[0]->attack : 0);

    // if (enemy->weapons.find(2) != enemy->weapons.end())
    // {
    //     enemy_active_attack += R;
    //     enemy_passive_attack += R;
    // }
    // !!!! TODO, check if enemy will be killed
    if (!enemy_attack_first)
    {
        if (self_active_attack >= enemy->hp || hp > enemy_passive_attack || enemy->Get_type() == "ninja")
            return false;
    }
    else
    {
        if (hp > enemy_active_attack)
            return false;
    }
    // if (enemy_passive_attack < hp || enemy_active_attack < hp)
    // {
    //     return false;
    // }

    return true;
}

void Warrior::Report_weapon()
{
    cout << setfill('0') << setw(3) << currentTime << ":55 " << headquarter->Get_hq_name() << " " << Get_type() << " " << id << " has ";
    if (weapons.size() == 0)
    {
        cout << "no weapon" << endl;
    }
    else
    {
        int total_weapon_cnt = weapons.size();
        vector<int> idxs = {2, 1, 0};
        for (auto i : idxs)
        {
            if (weapons.find(i) == weapons.end())
            {
                continue;
            }
            Weapon *weapon = weapons[i];
            if (i == 2)
            {
                cout << "arrow(" << dynamic_cast<Arrow *>(weapon)->Get_left_cnt_to_use() << ")";
            }
            else if (i == 1)
            {
                cout << "bomb";
            }
            else if (i == 0)
            {
                cout << "sword(" << weapon->attack << ")";
            }
            total_weapon_cnt--;
            if (total_weapon_cnt != 0)
                cout << ",";
        }
        cout << endl;
    }
}

void Warrior::After_fight(Warrior *enemy, int win_state, int enemy_hp_before_fight)
{
    // if (win_state != WIN)
    // {
    //     headquarter->Lion_loyalty_decrease();
    //     // headquarter->Dragon_morale_decrease();
    // }
    // else{
    //     headquarter->Dragon_morale_increase();
    // }

    if (enemy->Get_type() == "lion" && win_state == WIN)
    {
        hp += enemy_hp_before_fight;
    }
};

void Warrior::Attack(Warrior *warrior)
{
    warrior->hp -= attack;
    // if warrior has sword, use it and decrease its attack to 80%
    if (weapons.find(0) != weapons.end())
    {
        warrior->hp -= weapons[0]->attack;
        weapons[0]->attack = (int)(weapons[0]->attack * 0.8);
        if (weapons[0]->attack == 0)
        {
            delete weapons[0];
            weapons.erase(0);
        }
    }
}

void Warrior::Fight_back(Warrior *warrior)
{
    if (this->hp <= 0)
    {
        return;
    }
    warrior->hp -= (int)(attack / 2);
    // if warrior has sword, use it and decrease its attack to 80%
    if (weapons.find(0) != weapons.end())
    {
        warrior->hp -= weapons[0]->attack;
        weapons[0]->attack = (int)(weapons[0]->attack * 0.8);
        if (weapons[0]->attack == 0)
        {
            delete weapons[0];
            weapons.erase(0);
        }
    }
}

void Warrior::March(vector<City *> &cities, Headquarter &red, Headquarter &blue)
{
    // cout << headquarter->Get_hq_name() << "  " << Get_type() << " " << id << "!!!!!" << endl;
    if (headquarter->Get_hq_name() == "red")
    {
        if (pos == N + 1)
        {

            return;
        }
        else if (pos == 0)
        {
            pos = 1;
            cities[pos]->warriors_red = this;
        }
        else
        {
            if (cities[pos]->warriors_red == this)
            {
                cities[pos]->warriors_red = NULL;
            }
            pos++;
            cities[pos]->warriors_red = this;
        }
        // if (pos == N + 1)
        // {
        //     cout << setfill('0') << setw(3) << currentTime << ":10 red " << Get_type() << " " << id << " reached blue headquarter with " << hp << " elements and force " << attack << endl;
        //     blue.taken_over_cnt++;
        //     if (blue.taken_over_cnt == 2)
        //     {
        //         cout << setfill('0') << setw(3) << currentTime << ":10 blue headquarter was taken" << endl;
        //     }
        // }
    }
    else
    {
        if (pos == 0)
        {
            return;
        }
        else if (pos == N + 1)
        {
            pos = N;
            cities[pos]->warriors_blue = this;
        }
        else
        {
            if (cities[pos]->warriors_blue == this)
            {
                cities[pos]->warriors_blue = NULL;
            }
            pos--;
            cities[pos]->warriors_blue = this;
        }
        // if (pos == 0)
        // {
        //     cout << setfill('0') << setw(3) << currentTime << ":10 blue " << Get_type() << " " << id << " reached red headquarter with " << hp << " elements and force " << attack << endl;
        //     red.taken_over_cnt++;
        //     if (red.taken_over_cnt == 2)
        //     {
        //         cout << setfill('0') << setw(3) << currentTime << ":10 red headquarter was taken" << endl;
        //     }
        // }
    }
}

void Dragon::Yell()
{
    // cout << "dragon morale: " << morale << endl;
    cout << setfill('0') << setw(3) << currentTime << ":40 " << headquarter->Get_hq_name() << " dragon " << id << " yelled in city " << pos << endl;
}

void Produce_warrior(Headquarter &hq)
{
    string warrior_type = hq.Get_warrior_order()[hq.cur_warrior_type_idx];
    // string next_type = hq.Get_warrior_order()[(hq.cur_warrior_type_idx + 1) % 5];
    if (hq.Get_hp() >= Warrior::INIT_HP[warrior_type]) // hq can produce next_type
    {
        hq.Add_warrior(warrior_type);
        hq.cur_warrior_type_idx = (hq.cur_warrior_type_idx + 1) % 5;
    }
    // else
    // {
    //     cout << setfill('0') << setw(3) << currentTime << " " << hq.Get_hq_name() << " does not have enough hp to produce warrior "
    //          << warrior_type << " waiting for next turn" << endl;
    // }
}

void Lion_run_away(Headquarter &red, Headquarter &blue, vector<City *> &cities)
{
    red.Lion_run_away(cities);
    blue.Lion_run_away(cities);
}

void March(Headquarter &red, Headquarter &blue, vector<City *> &cities)
{
    vector<Warrior *> &red_warriors = red.Get_warriors();
    vector<Warrior *> &blue_warriors = blue.Get_warriors();
    for (int i = 0; i < red_warriors.size(); i++)
    {
        if (!red_warriors[i]->Dormant())
        {
            red_warriors[i]->March(cities, red, blue);
        }
    }

    for (int i = 0; i < blue_warriors.size(); i++)
    {
        if (!blue_warriors[i]->Dormant())
        {
            blue_warriors[i]->March(cities, red, blue);
        }
    }

    for (int i = 0; i < N + 2; i++)
    {
        City *city = cities[i];
        if (i != 0 && city->warriors_red && !city->warriors_red->Dormant())
        {
            Warrior *warrior = city->warriors_red;
            if (i != N + 1)
                cout << setfill('0') << setw(3) << currentTime << ":10 red " << warrior->Get_type() << " " << warrior->Get_id() << " marched to city " << i << " with " << warrior->Get_hp() << " elements and force " << warrior->Get_attack() << endl;
            else
            {
                cout << setfill('0') << setw(3) << currentTime << ":10 red " << warrior->Get_type() << " " << warrior->Get_id() << " reached blue headquarter with " << warrior->Get_hp() << " elements and force " << warrior->Get_attack() << endl;
                blue.taken_over_cnt++;
                warrior->Set_dormant(true);
                if (blue.taken_over_cnt == 2)
                {
                    cout << setfill('0') << setw(3) << currentTime << ":10 blue headquarter was taken" << endl;
                }
            }
        }

        if (i != N + 1 && city->warriors_blue && !city->warriors_blue->Dormant())
        {
            // if (currentTime == 20 && i == 11)
            // {
            //     cout << "debug" << endl;
            // }
            Warrior *warrior = city->warriors_blue;
            if (i != 0)
                cout << setfill('0') << setw(3) << currentTime << ":10 blue " << warrior->Get_type() << " " << warrior->Get_id() << " marched to city " << i << " with " << warrior->Get_hp() << " elements and force " << warrior->Get_attack() << endl;
            else
            {
                cout << setfill('0') << setw(3) << currentTime << ":10 blue " << warrior->Get_type() << " " << warrior->Get_id() << " reached red headquarter with " << warrior->Get_hp() << " elements and force " << warrior->Get_attack() << endl;
                red.taken_over_cnt++;
                warrior->Set_dormant(true);
                if (red.taken_over_cnt == 2)
                {
                    cout << setfill('0') << setw(3) << currentTime << ":10 red headquarter was taken" << endl;
                }
            }
        }
    }
}

void Produce_hp(vector<City *> &cities)
{
    for (int i = 0; i < cities.size(); i++)
    {
        cities[i]->hp += 10;
    }
}

void Take_city_hp(vector<City *> &cities, Headquarter &red, Headquarter &blue)
{
    for (int i = 1; i < N + 1; i++)
    {
        if (cities[i]->warriors_blue && cities[i]->warriors_red == NULL)
        {
            Warrior *warrior = cities[i]->warriors_blue;
            warrior->headquarter->Add_hp(cities[i]->hp);
            cout << setfill('0') << setw(3) << currentTime << ":30 blue " << warrior->Get_type() << " " << warrior->Get_id() << " earned " << cities[i]->hp << " elements for his headquarter" << endl;
            cities[i]->hp = 0;
        }

        else if (cities[i]->warriors_blue == NULL && cities[i]->warriors_red)
        {
            Warrior *warrior = cities[i]->warriors_red;
            warrior->headquarter->Add_hp(cities[i]->hp);
            cout << setfill('0') << setw(3) << currentTime << ":30 red " << warrior->Get_type() << " " << warrior->Get_id() << " earned " << cities[i]->hp << " elements for his headquarter" << endl;
            cities[i]->hp = 0;
        }
    }
}

void Use_arrow(vector<City *> &cities)
{
    for (int i = 0; i < N + 2; i++)
    {
        if (cities[i]->warriors_red && i < N && cities[i + 1]->warriors_blue)
        {
            Warrior *red_warrior = cities[i]->warriors_red;
            Warrior *blue_warrior = cities[i + 1]->warriors_blue;
            if (red_warrior->weapons.find(2) != red_warrior->weapons.end())
            {
                cities[i + 1]->warriors_blue->hp -= R;
                dynamic_cast<Arrow *>(red_warrior->weapons[2])->Decrease_left_cnt_to_use();
                if (dynamic_cast<Arrow *>(red_warrior->weapons[2])->Get_left_cnt_to_use() == 0)
                {
                    delete red_warrior->weapons[2];
                    red_warrior->weapons.erase(2);
                }
                if (blue_warrior->hp <= 0)
                {
                    // delete blue_warrior;
                    // cities[i + 1]->warriors_blue = NULL;
                    cout << setfill('0') << setw(3) << currentTime << ":35 red " << red_warrior->Get_type() << " " << red_warrior->Get_id() << " shot and killed blue " << blue_warrior->Get_type() << " " << blue_warrior->Get_id() << endl;
                }
                else
                {
                    cout << setfill('0') << setw(3) << currentTime << ":35 red " << red_warrior->Get_type() << " " << red_warrior->Get_id() << " shot" << endl;
                }
            }
        }

        if (cities[i]->warriors_blue && i > 1 && cities[i - 1]->warriors_red)
        {
            Warrior *red_warrior = cities[i - 1]->warriors_red;
            Warrior *blue_warrior = cities[i]->warriors_blue;
            if (blue_warrior->weapons.find(2) != blue_warrior->weapons.end())
            {
                cities[i - 1]->warriors_red->hp -= R;
                dynamic_cast<Arrow *>(blue_warrior->weapons[2])->Decrease_left_cnt_to_use();
                if (dynamic_cast<Arrow *>(blue_warrior->weapons[2])->Get_left_cnt_to_use() == 0)
                {
                    delete blue_warrior->weapons[2];
                    blue_warrior->weapons.erase(2);
                }
                if (red_warrior->hp <= 0)
                {
                    // delete red_warrior;
                    // cities[i - 1]->warriors_red = NULL;
                    cout << setfill('0') << setw(3) << currentTime << ":35 blue " << blue_warrior->Get_type() << " " << blue_warrior->Get_id() << " shot and killed red " << red_warrior->Get_type() << " " << red_warrior->Get_id() << endl;
                }
                else
                {
                    cout << setfill('0') << setw(3) << currentTime << ":35 blue " << blue_warrior->Get_type() << " " << blue_warrior->Get_id() << " shot" << endl;
                }
            }
        }
    }
}

void Use_bomb(vector<City *> &cities, Headquarter &red, Headquarter &blue)
{
    for (int i = 1; i < N + 1; i++)
    {

        // if (currentTime == 23 && i == 15)
        // {
        //     cout << "Debug" << endl;
        // }
        // if (currentTime == 11)
        // {
        //     cout << "Debug" << endl;
        // }
        if (cities[i]->warriors_blue && cities[i]->warriors_red)
        {
            Warrior *red_warrior = cities[i]->warriors_red;
            Warrior *blue_warrior = cities[i]->warriors_blue;
            if (red_warrior->hp > 0 && red_warrior->weapons.find(1) != red_warrior->weapons.end())
            {
                if (red_warrior->CantBeat(blue_warrior, cities[i]))
                {
                    // cout << "At city " << i << " city flag is " << cities[i]->flagColor << endl;
                    cout << setfill('0') << setw(3) << currentTime << ":38 red " << red_warrior->Get_type() << " " << red_warrior->Get_id() << " used a bomb and killed blue " << blue_warrior->Get_type() << " " << blue_warrior->Get_id() << endl;
                    cities[i]->warriors_red = NULL;
                    red.Remove(red_warrior);
                    delete red_warrior;
                    cities[i]->warriors_blue = NULL;
                    blue.Remove(blue_warrior);
                    delete blue_warrior;
                }
            }
            if (cities[i]->warriors_blue && blue_warrior->hp > 0 && blue_warrior->weapons.find(1) != blue_warrior->weapons.end())
            {
                if (blue_warrior->CantBeat(red_warrior, cities[i]))
                {
                    // cout << "At city " << i << " city flag is " << cities[i]->flagColor << endl;
                    cout << setfill('0') << setw(3) << currentTime << ":38 blue " << blue_warrior->Get_type() << " " << blue_warrior->Get_id() << " used a bomb and killed red " << red_warrior->Get_type() << " " << red_warrior->Get_id() << endl;
                    cities[i]->warriors_red = NULL;
                    red.Remove(red_warrior);
                    delete red_warrior;
                    cities[i]->warriors_blue = NULL;
                    blue.Remove(blue_warrior);
                    delete blue_warrior;
                }
            }
        }
    }
}

void Arrow_killed_warrior_handler(City *city, Warrior *active, Warrior *passive)
{
    Warrior *winner = NULL, *loser = NULL;
    if (active->Get_hp() <= 0 && passive->Get_hp() <= 0)
    {
        city->warriors_red = NULL;
        city->warriors_blue = NULL;
        active->headquarter->Remove(active);
        passive->headquarter->Remove(passive);
        active->After_fight(passive, TIE, 0);
        passive->After_fight(active, TIE, 0);
        city->Raise_flag("none");
        delete active;
        delete passive;
    }
    else if (active->Get_hp() <= 0)
    {
        winner = passive;
        loser = active;
    }
    else if (passive->Get_hp() <= 0)
    {
        winner = active;
        loser = passive;
    }

    if (winner && loser)
    {   
        if (winner->Get_type() == "dragon" && dynamic_cast<Dragon*> (winner)->Get_morale() > 0.8 && winner->headquarter->Get_hq_name() == active->headquarter->Get_hq_name())
        {
            dynamic_cast<Dragon*> (winner)->Yell();
        }
        cout << setfill('0') << setw(3) << currentTime << ":40 " << winner->headquarter->Get_hq_name() << " " << winner->Get_type() << " " << winner->Get_id() << " earned " << city->hp << " elements for his headquarter" << endl;
        winner->headquarter->Add_warrior_to_reward(winner);
        winner->headquarter->Add_city_to_recycle_hp(winner->pos);
        loser->headquarter->Remove(loser);
        winner->After_fight(loser, WIN, 0);
        loser->After_fight(winner, LOSE, winner->Get_hp());
        city->Raise_flag(winner->headquarter->Get_hq_name());

        if (loser == city->warriors_red)
            city->warriors_red = NULL;
        else
            city->warriors_blue = NULL;
        delete loser;
    }
}

void Fight_between_warriors(City *city, Warrior *active, Warrior *passive)
{
    if (active->Get_hp() <= 0 || passive->Get_hp() <= 0) // at least one dead due to arrow
    {
        Arrow_killed_warrior_handler(city, active, passive);
        return;
    }

    int active_hp = active->Get_hp(), passive_hp = passive->Get_hp();
    cout << setfill('0') << setw(3) << currentTime << ":40 " << active->headquarter->Get_hq_name() << " " << active->Get_type() << " " << active->Get_id() << " attacked " << passive->headquarter->Get_hq_name() << " " << passive->Get_type() << " " << passive->Get_id() << " in city " << city->id << " with " << active->hp << " elements and force " << active->attack << endl;
    active->Attack(passive);
    if (passive->hp <= 0)
    {
        cout << setfill('0') << setw(3) << currentTime << ":40 " << passive->headquarter->Get_hq_name() << " " << passive->Get_type() << " " << passive->Get_id() << " was killed in city " << city->id << endl;
        if (active->Get_type() == "dragon" && dynamic_cast<Dragon*> (active)->Get_morale() > 0.8)
        {
            dynamic_cast<Dragon*> (active)->Yell();
        }
        cout << setfill('0') << setw(3) << currentTime << ":40 " << active->headquarter->Get_hq_name() << " " << active->Get_type() << " " << active->Get_id() << " earned " << city->hp << " elements for his headquarter" << endl;
        if (city->warriors_red == passive)
            city->warriors_red = NULL;
        else
            city->warriors_blue = NULL;
        passive->headquarter->Remove(passive);
        // request headquarter for reward
        active->headquarter->Add_warrior_to_reward(active);
        active->headquarter->Add_city_to_recycle_hp(active->pos);
        active->After_fight(passive, WIN, passive_hp);
        passive->After_fight(active, LOSE, active_hp);
        city->Raise_flag(active->headquarter->Get_hq_name());
        delete passive;
    }
    else
    {
        if (passive->Get_type() != "ninja")
        {
            cout << setfill('0') << setw(3) << currentTime << ":40 " << passive->headquarter->Get_hq_name() << " " << passive->Get_type() << " " << passive->Get_id() << " fought back against " << active->headquarter->Get_hq_name() << " " << active->Get_type() << " " << active->Get_id() << " in city " << city->id << endl;
            passive->Fight_back(active);
        }
        if (active->hp <= 0)
        {
            cout << setfill('0') << setw(3) << currentTime << ":40 " << active->headquarter->Get_hq_name() << " " << active->Get_type() << " " << active->Get_id() << " was killed in city " << city->id << endl;
            cout << setfill('0') << setw(3) << currentTime << ":40 " << passive->headquarter->Get_hq_name() << " " << passive->Get_type() << " " << passive->Get_id() << " earned " << city->hp << " elements for his headquarter" << endl;
            if (city->warriors_blue == active)
                city->warriors_blue = NULL;
            else
                city->warriors_red = NULL;
            active->headquarter->Remove(active);
            // request headquarter for reward
            passive->headquarter->Add_warrior_to_reward(passive);
            passive->headquarter->Add_city_to_recycle_hp(passive->pos);

            active->After_fight(passive, LOSE, passive_hp);
            passive->After_fight(active, WIN, active_hp);
            city->Raise_flag(passive->headquarter->Get_hq_name());
            delete active;
        }
        else
        { // both alive
            if (active->Get_type() == "dragon" && dynamic_cast<Dragon*> (active)->Get_morale() > 0.8)
            {
                dynamic_cast<Dragon*> (active)->Yell();
            }
            active->After_fight(passive, TIE, passive_hp);
            passive->After_fight(active, TIE, active_hp);
            city->last_winner = "none";
        }
    }
}

void Clean_dead_warriors(vector<City *> &cities)
{
    for (int i = 0; i < N + 2; i++)
    {
        if (cities[i]->warriors_red && cities[i]->warriors_red->Get_hp() <= 0)
        {
            cities[i]->warriors_red->headquarter->Remove(cities[i]->warriors_red);
            cities[i]->warriors_red = NULL;
            delete cities[i]->warriors_red;
        }

        if (cities[i]->warriors_blue && cities[i]->warriors_blue->Get_hp() <= 0)
        {
            cities[i]->warriors_blue->headquarter->Remove(cities[i]->warriors_blue);
            cities[i]->warriors_blue = NULL;
            delete cities[i]->warriors_blue;
        }
    }
}

void Fight(vector<City *> cities, Headquarter &red, Headquarter &blue)
{
    for (int i = 1; i < N + 1; i++)
    {
        City *city = cities[i];
        if (city->warriors_blue && city->warriors_red)
        {
            Warrior *red_warrior = city->warriors_red;
            Warrior *blue_warrior = city->warriors_blue;
            if (city->flagColor == "red" || (city->flagColor == "none" && i % 2 == 1)) // red attack first
            {
                Fight_between_warriors(city, red_warrior, blue_warrior);
            }
            else if (city->flagColor == "blue" || (city->flagColor == "none" && i % 2 == 0)) // blue attack first
            {
                Fight_between_warriors(city, blue_warrior, red_warrior);
            }
        }
    }
    red.Reward_warriors();
    blue.Reward_warriors();
    red.Recycle_hp_from_city(cities);
    blue.Recycle_hp_from_city(cities);
    Clean_dead_warriors(cities);
}

void Report_hp(Headquarter &red, Headquarter &blue)
{
    cout << setfill('0') << setw(3) << currentTime << ":50 " << red.Get_hp() << " elements in red headquarter" << endl;
    cout << setfill('0') << setw(3) << currentTime << ":50 " << blue.Get_hp() << " elements in blue headquarter" << endl;
}

void Report_weapon(Headquarter &red, Headquarter &blue)
{
    vector<Warrior *> &red_warriors = red.Get_warriors();
    std::sort(red_warriors.begin(), red_warriors.end(), [](Warrior *a, Warrior *b)
              { return a->Get_pos() < b->Get_pos(); });
    vector<Warrior *> &blue_warriors = blue.Get_warriors();
    std::sort(blue_warriors.begin(), blue_warriors.end(), [](Warrior *a, Warrior *b)
              { return a->Get_pos() < b->Get_pos(); });

    for (int i = 0; i < red_warriors.size(); i++)
    {
        Warrior *warrior = red_warriors[i];
        warrior->Report_weapon();
    }

    for (int i = 0; i < blue_warriors.size(); i++)
    {
        Warrior *warrior = blue_warriors[i];
        warrior->Report_weapon();
    }
}

void run(Headquarter &red, Headquarter &blue, vector<City *> &cities)
{
    while (red.Get_taken_over_cnt() < 2 && blue.Get_taken_over_cnt() < 2 && currentMin <= T)
    {
        red.Reset_temp_data();
        blue.Reset_temp_data();
        // 0 min, produce warrior
        Produce_warrior(red);
        Produce_warrior(blue);
        currentMin += 5;

        if (currentMin > T)
        {
            break;
        }
        // 5 min, lions run away
        Lion_run_away(red, blue, cities);
        currentMin += 5;

        if (currentMin > T)
        {
            break;
        }

        // 10 min, march
        March(red, blue, cities);
        currentMin += 10;

        if (currentMin > T || red.Get_taken_over_cnt() >= 2 || blue.Get_taken_over_cnt() >= 2)
        {
            break;
        }

        // 20 min, produce hp
        Produce_hp(cities);
        currentMin += 10;

        if (currentMin > T)
        {
            break;
        }

        // 30 min, take city hp
        Take_city_hp(cities, red, blue);
        currentMin += 5;

        if (currentMin > T)
        {
            break;
        }

        // 35 min, use arrow
        Use_arrow(cities);
        currentMin += 3;

        if (currentMin > T)
        {
            break;
        }

        // 38 min, use bomb
        Use_bomb(cities, red, blue);
        currentMin += 2;

        if (currentMin > T)
        {
            break;
        }

        // 40 min, fight
        Fight(cities, red, blue);
        currentMin += 10;

        if (currentMin > T)
        {
            break;
        }

        // 50 min, report hp
        Report_hp(red, blue);
        currentMin += 5;

        if (currentMin > T)
        {
            break;
        }

        // 55 min, report weapon
        Report_weapon(red, blue);
        currentMin += 5;
        currentTime++;
    }
}

map<string, int> Warrior::INIT_HP;
map<string, int> Warrior::ATTACK;

int main()
{
    #if USE_INPUT_FILE
    ifstream inputFile("in.txt"); // Open the input file
    if (!inputFile.is_open())
    {
        cout << "Error opening the file!" << endl;
        return 1;
    }

    int case_num;
    // cin >> case_num;
    inputFile >> case_num;
    #else
    int case_num;
    cin >> case_num;
    #endif

    Warrior::weapon_type[0] = "sword";
    Warrior::weapon_type[1] = "bomb";
    Warrior::weapon_type[2] = "arrow";

    static vector<string> warrior_order_red;
    warrior_order_red.push_back("iceman");
    warrior_order_red.push_back("lion");
    warrior_order_red.push_back("wolf");
    warrior_order_red.push_back("ninja");
    warrior_order_red.push_back("dragon");
    static vector<string> warrior_order_blue;
    warrior_order_blue.push_back("lion");
    warrior_order_blue.push_back("dragon");
    warrior_order_blue.push_back("ninja");
    warrior_order_blue.push_back("iceman");
    warrior_order_blue.push_back("wolf");

    static vector<string> input_order;
    input_order.push_back("dragon");
    input_order.push_back("ninja");
    input_order.push_back("iceman");
    input_order.push_back("lion");
    input_order.push_back("wolf");
    for (int i = 0; i < case_num; i++)
    {
        #if USE_INPUT_FILE
        // cin >> M >> N >> R >> K >> T;
        inputFile >> M >> N >> R >> K >> T;
        for (int j = 0; j < 5; j++)
        {
            int temp;
            // cin >> temp;
            inputFile >> temp;
            Warrior::INIT_HP[input_order[j]] = temp;
        }

        for (int j = 0; j < 5; j++)
        {
            int temp;
            // cin >> temp;
            inputFile >> temp;
            Warrior::ATTACK[input_order[j]] = temp;
        }
        #else
        cin >> M >> N >> R >> K >> T;
        for (int j = 0; j < 5; j++)
        {
            int temp;
            cin >> temp;
            Warrior::INIT_HP[input_order[j]] = temp;
        }

        for (int j = 0; j < 5; j++)
        {
            int temp;
            cin >> temp;
            Warrior::ATTACK[input_order[j]] = temp;
        }
        #endif

        Headquarter red(M, warrior_order_red, "red");
        Headquarter blue(M, warrior_order_blue, "blue");
        vector<City *> cities;
        for (int j = 0; j < N + 2; j++)
        {
            City *city = new City(j);
            cities.push_back(city);
        }

        cout << "Case " << i + 1 << ":" << endl;
        currentMin = 0;
        currentTime = 0;
        run(red, blue, cities);

        for (int j = 0; j < N + 2; j++)
        {
            delete cities[j];
        }
    }
    return 0;
}