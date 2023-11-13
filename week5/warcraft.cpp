#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <iomanip>

using namespace std;

class Warrior
{
    int hp;
    int id;

public:
    static map<string, int> init_hp;
    static map<int, string> weapon_type;

    static void set_init_hp(vector<int> &in_init_hp)
    {
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

    Warrior(int id, int hp) : id(id), hp(hp) {}
    virtual ~Warrior() {}
};

map<string, int> Warrior::init_hp;
map<int, string> Warrior::weapon_type;


class Dragon : public Warrior
{
    int weapon_type_idx;
    double morale;

public:
    Dragon(int id, int hp, int weapon_type_idx, double morale) : Warrior(id, hp), weapon_type_idx(weapon_type_idx), morale(morale) {}
};

class Ninja : public Warrior
{
    int weapon_type_idx1;
    int weapon_type_idx2;

public:
    Ninja(int id, int hp, int weapon_type_idx1, int weapon_type_idx2) : Warrior(id, hp), weapon_type_idx1(weapon_type_idx1), weapon_type_idx2(weapon_type_idx2) {}
};

class Iceman : public Warrior
{
    int weapon_type_idx;

public:
    Iceman(int id, int hp, int weapon_type_idx) : Warrior(id, hp), weapon_type_idx(weapon_type_idx) {}
};

class Lion : public Warrior
{
    int loyalty;

public:
    Lion(int id, int hp, int loyalty) : Warrior(id, hp), loyalty(loyalty) {}
};

class Wolf : public Warrior
{
public:
    Wolf(int id, int hp) : Warrior(id, hp) {}
};

class Headquarter
{
    int cur_hp;
    vector<Warrior *> warriors;
    vector<string> warrior_order;
    map<string, bool> stop_produce;
    bool stop_produce_flag;
    string hq_name;

public:
    map<string, int> warrior_num;
    int total_warrior_num;
    int cur_warrior_type_idx;

    Headquarter(int hp, vector<int> &in_init_hp, vector<string> &in_warrior_order, string hq_name) : hq_name(hq_name)
    {
        cur_hp = hp;
        warrior_order = in_warrior_order;
        stop_produce_flag = false;
        total_warrior_num = 0;
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

    void add_warrior(string warrior_type, int time = 0)
    {
        Warrior *warrior;
        total_warrior_num++;
        warrior_num[warrior_type]++;
        cur_hp -= Warrior::init_hp[warrior_type];
        int need_hp = Warrior::init_hp[warrior_type];
        cout << setfill('0') << setw(3) << time << " " << hq_name << " " << warrior_type << " " << total_warrior_num << " born with strength " << need_hp << ","
             << warrior_num[warrior_type] << " " << warrior_type << " in " << hq_name << " headquarter" << endl;
        if (warrior_type == "dragon")
        {
            int weapon_type_idx = total_warrior_num % 3;
            warrior = new Dragon(total_warrior_num, need_hp, weapon_type_idx, (double)cur_hp / need_hp);
            cout << "It has a " << Warrior::weapon_type[weapon_type_idx] << ",and it's morale is " << fixed << setprecision(2) << (double)cur_hp / need_hp << endl;
        }
        else if (warrior_type == "ninja")
        {
            int weapon_type_idx1 = total_warrior_num % 3, weapon_type_idx2 = (total_warrior_num + 1) % 3;
            warrior = new Ninja(total_warrior_num, need_hp, weapon_type_idx1, weapon_type_idx2);
            cout << "It has a " << Warrior::weapon_type[weapon_type_idx1] << " and a " << Warrior::weapon_type[weapon_type_idx2] << endl;
        }
        else if (warrior_type == "iceman")
        {
            int weapon_type_idx = total_warrior_num % 3;
            warrior = new Iceman(total_warrior_num, need_hp, weapon_type_idx);
            cout << "It has a " << Warrior::weapon_type[weapon_type_idx] << endl;
        }
        else if (warrior_type == "lion")
        {
            warrior = new Lion(total_warrior_num, need_hp, cur_hp);
            cout << "It's loyalty is " << cur_hp << endl;
        }
        else if (warrior_type == "wolf")
        {
            warrior = new Wolf(total_warrior_num, need_hp);
        }

        warriors.push_back(warrior);
    }

    vector<string> &get_warrior_order()
    {
        return warrior_order;
    }

    ~Headquarter()
    {
        for (int i = 0; i < warriors.size(); i++)
        {
            delete warriors[i];
        }
    }
};

int main()
{
    int case_num;
    cin >> case_num;
    Warrior::weapon_type[0] = "sword";
    Warrior::weapon_type[1] = "bomb";
    Warrior::weapon_type[2] = "arrow";
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

        Headquarter red(hp, init_hp, warrior_order_red, "red");
        Headquarter blue(hp, init_hp, warrior_order_blue, "blue");

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
                    if (!red.get_stop_produce(next_type) && red.get_hp() >= Warrior::init_hp[next_type]) // red can produce next_type
                    {
                        red.set_stop_produce(next_type, false);
                        red.set_stop_produce_flag(false);
                        red.cur_warrior_type_idx = (red.cur_warrior_type_idx + k) % 5;
                        found_next_type = true;
                        red.add_warrior(next_type, time);
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
                        blue.add_warrior(next_type, time);
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
