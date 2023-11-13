#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <iomanip>

using namespace std;

class Warrior
{
public:
    int hp;
    int atk;
    static map<string, int> init_hp;

    static void set_init_hp(vector<int> &in_init_hp)
    {
        int idx = 0;
        vector<string> warrior_type;
        warrior_type.push_back("dragon");
        warrior_type.push_back("ninja");
        warrior_type.push_back("iceman");
        warrior_type.push_back("lion");
        warrior_type.push_back("wolf");
        
        for (int i = 0; i < in_init_hp.size(); i++)
        {
            init_hp[warrior_type[i]] = in_init_hp[i];
        }
    }

    Warrior()
    {
        hp = 0;
        atk = 0;
    }
    virtual ~Warrior() {}
};

map<string, int> Warrior::init_hp;

class Dragon : public Warrior
{
public:
    Dragon(int hp, int atk = 0)
    {
        this->hp = hp;
        this->atk = atk;
    }
};

class Ninja : public Warrior
{
public:
    Ninja(int hp, int atk = 0)
    {
        this->hp = hp;
        this->atk = atk;
    }
};

class Iceman : public Warrior
{
public:
    Iceman(int hp, int atk = 0)
    {
        this->hp = hp;
        this->atk = atk;
    }
};

class Lion : public Warrior
{
public:
    Lion(int hp, int atk = 0)
    {
        this->hp = hp;
        this->atk = atk;
    }
};

class Wolf : public Warrior
{
public:
    Wolf(int hp, int atk = 0)
    {
        this->hp = hp;
        this->atk = atk;
    }
};

class Headquarter
{
    int cur_hp;
    vector<Warrior *> warriors;
    vector<string> warrior_order;
    map<string, bool> stop_produce;
    bool stop_produce_flag;

public:
    map<string, int> warrior_num;
    int cur_warrior_num;
    int cur_warrior_type_idx;

    Headquarter(int hp, vector<int> &in_init_hp, vector<string> &in_warrior_order)
    {
        cur_hp = hp;
        warrior_order = in_warrior_order;
        stop_produce_flag = false;
        cur_warrior_num = 0;
        cur_warrior_type_idx = 0;
        for (int i = 0; i < warrior_order.size(); i++)
        {
            warrior_num[warrior_order[i]] = 0;
            stop_produce[warrior_order[i]] = false;
        }
        Warrior::set_init_hp(in_init_hp);
    }

    bool get_stop_produce_flag()
    {
        return stop_produce_flag;
    }

    void set_stop_produce_flag(bool flag)
    {
        stop_produce_flag = flag;
    }

    bool get_stop_produce(string warrior_type)
    {
        return stop_produce[warrior_type];
    }

    void set_stop_produce(string warrior_type, bool flag)
    {
        stop_produce[warrior_type] = flag;
    }

    int get_hp()
    {
        return cur_hp;
    }

    void add_warrior(Warrior *warrior)
    {
        warriors.push_back(warrior);
        cur_hp -= warrior->hp;
    }

    vector<string> &get_warrior_order()
    {
        return warrior_order;
    }
};

int main()
{
    int case_num;
    cin >> case_num;
    for (int i = 0; i < case_num; i++)
    {
        int hp;
        cin >> hp;
        vector<int> init_hp(5);
        for (int j = 0; j < 5; j++)
        {
            cin >> init_hp[j];
        }
        vector<string> warrior_order_red;
        warrior_order_red.push_back("iceman");
        warrior_order_red.push_back("lion");
        warrior_order_red.push_back("wolf");
        warrior_order_red.push_back("ninja");
        warrior_order_red.push_back("dragon");
        vector<string> warrior_order_blue;
        warrior_order_blue.push_back("lion");
        warrior_order_blue.push_back("dragon");
        warrior_order_blue.push_back("ninja");
        warrior_order_blue.push_back("iceman");
        warrior_order_blue.push_back("wolf");

        Headquarter red(hp, init_hp, warrior_order_red);
        Headquarter blue(hp, init_hp, warrior_order_blue);

        cout << "Case:" << i + 1 << endl;
        int time = 0;

        while (!red.get_stop_produce_flag() || !blue.get_stop_produce_flag())
        {
            if (!red.get_stop_produce_flag())
            {
                string warrior_type = red.get_warrior_order()[red.cur_warrior_type_idx];
                bool found_next_type = false;
                for (int k = 0; k < 5; k++)
                {
                    string next_type = red.get_warrior_order()[(red.cur_warrior_type_idx + k) % 5];
                    if (!red.get_stop_produce(next_type) && red.get_hp() >= Warrior::init_hp[next_type])
                    {
                        red.set_stop_produce(next_type, false);
                        red.set_stop_produce_flag(false);
                        red.cur_warrior_type_idx = (red.cur_warrior_type_idx + k) % 5;
                        found_next_type = true;
                        if (next_type == "dragon")
                        {
                            red.add_warrior(new Dragon(Warrior::init_hp[next_type]));
                        }
                        else if (next_type == "ninja")
                        {
                            red.add_warrior(new Ninja(Warrior::init_hp[next_type]));
                        }
                        else if (next_type == "iceman")
                        {
                            red.add_warrior(new Iceman(Warrior::init_hp[next_type]));
                        }
                        else if (next_type == "lion")
                        {
                            red.add_warrior(new Lion(Warrior::init_hp[next_type]));
                        }
                        else if (next_type == "wolf")
                        {
                            red.add_warrior(new Wolf(Warrior::init_hp[next_type]));
                        }
                        red.warrior_num[next_type]++;
                        red.cur_warrior_num++;
                        cout << setfill('0') << setw(3) << time << " red " << next_type << " " << red.cur_warrior_num << " born with strength " << Warrior::init_hp[next_type] << ","
                             << red.warrior_num[next_type] << " " << next_type << " in " << "red headquarter" << endl;
                        red.cur_warrior_type_idx = (red.cur_warrior_type_idx + 1) % 5;
                        break;
                    }
                }
                if (!found_next_type)
                {
                    red.set_stop_produce_flag(true);
                    cout << setfill('0') << setw(3) << time << " red headquarter stops making warriors" << endl;
                }
            }

            if (!blue.get_stop_produce_flag())
            {
                string warrior_type = blue.get_warrior_order()[blue.cur_warrior_type_idx];
                bool found_next_type = false;
                for (int k = 0; k < 5; k++)
                {
                    string next_type = blue.get_warrior_order()[(blue.cur_warrior_type_idx + k) % 5];
                    if (!blue.get_stop_produce(next_type) && blue.get_hp() >= Warrior::init_hp[next_type])
                    {
                        blue.set_stop_produce(next_type, false);
                        blue.set_stop_produce_flag(false);
                        blue.cur_warrior_type_idx = (blue.cur_warrior_type_idx + k) % 5;
                        found_next_type = true;
                        if (next_type == "dragon")
                        {
                            blue.add_warrior(new Dragon(Warrior::init_hp[next_type]));
                        }
                        else if (next_type == "ninja")
                        {
                            blue.add_warrior(new Ninja(Warrior::init_hp[next_type]));
                        }
                        else if (next_type == "iceman")
                        {
                            blue.add_warrior(new Iceman(Warrior::init_hp[next_type]));
                        }
                        else if (next_type == "lion")
                        {
                            blue.add_warrior(new Lion(Warrior::init_hp[next_type]));
                        }
                        else if (next_type == "wolf")
                        {
                            blue.add_warrior(new Wolf(Warrior::init_hp[next_type]));
                        }
                        blue.warrior_num[next_type]++;
                        blue.cur_warrior_num++;
                        cout << setfill('0') << setw(3) << time << " blue " << next_type << " " << blue.cur_warrior_num << " born with strength " << Warrior::init_hp[next_type] << ","
                             << blue.warrior_num[next_type] << " " << next_type << " in " << "blue headquarter" << endl;
                        blue.cur_warrior_type_idx = (blue.cur_warrior_type_idx + 1) % 5;
                        break;
                    }
                }
                if (!found_next_type)
                {
                    blue.set_stop_produce_flag(true);
                    cout << setfill('0') << setw(3) << time << " blue headquarter stops making warriors" << endl;
                }
            }
            time++;
        }
    }
    return 0;
}
