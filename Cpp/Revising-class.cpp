// ===========================================================================
// Character, Warrior, Wizard, and Team --> revising to generic and vector
// ===========================================================================
#include <iostream>
#include <string>
#include <cmath>
#include <vector>
using namespace std;

template<typename KeyType>
class Character
{
protected:
    static const int EXP_LV = 100;
    KeyType name;
    int level;
    int exp;
    int power;
    int knowledge;
    int luck;
    void levelUp(int pInc, int kInc, int lInc);

public:
    Character(KeyType n, int lv, int po, int kn, int lu);
    virtual void beatMonster(int exp) = 0; // pure vitural function -> this class will become abstract class.
    virtual void print();
    KeyType getName();
};

template<typename KeyType>
Character<KeyType>::Character(KeyType n, int lv, int po, int kn, int lu)
    : name(n), level(lv), exp(pow(lv - 1, 2) * EXP_LV), power(po), knowledge(kn), luck(lu)
{
}

template<typename KeyType>
void Character<KeyType>::print()
{
    cout << this->name
         << ": Level " << this->level << " (" << this->exp << "/" << pow(this->level, 2) * EXP_LV
         << "), " << this->power << "-" << this->knowledge << "-" << this->luck << "\n";
}

template<typename KeyType>
void Character<KeyType>::levelUp(int pInc, int kInc, int lInc)
{
    this->level++;
    this->power += pInc;
    this->knowledge += kInc;
    this->luck += lInc;
}

template<typename KeyType>
KeyType Character<KeyType>::getName()
{
    return this->name;
}

template<typename KeyType>
class Warrior : public Character<KeyType>
{
private:
    static const int PO_LV = 10;
    static const int KN_LV = 5;
    static const int LU_LV = 5;

public:
    Warrior(KeyType n) : Character<KeyType>(n, 1, PO_LV, KN_LV, LU_LV) {}
    Warrior(KeyType n, int lv) : Character<KeyType>(n, lv, lv * PO_LV, lv * KN_LV, lv * LU_LV) {}
    void print()
    {
        cout << "Warrior ";
        Character<KeyType>::print();
    }
    void beatMonster(int exp)
    {
        this->exp += exp;
        while (this->exp >= pow(this->level, 2) * Character<KeyType>::EXP_LV)
            this->levelUp(PO_LV, KN_LV, LU_LV);
    }
};

template<typename KeyType>
class Wizard : public Character<KeyType>
{
private:
    static const int PO_LV = 4;
    static const int KN_LV = 9;
    static const int LU_LV = 7;

public:
    Wizard(KeyType n) : Character<KeyType>(n, 1, PO_LV, KN_LV, LU_LV) {}
    Wizard(KeyType n, int lv) : Character<KeyType>(n, lv, lv * PO_LV, lv * KN_LV, lv * LU_LV) {}
    void print()
    {
        cout << "Wizard ";
        Character<KeyType>::print();
    }
    void beatMonster(int exp)
    {
        this->exp += exp;
        while (this->exp >= pow(this->level, 2) * Character<KeyType>::EXP_LV)
            this->levelUp(PO_LV, KN_LV, LU_LV);
    }
};

template<typename KeyType>
class Team
{
private:
    //int memberCount;
    //Character<KeyType>* member[10];
    vector<Character<KeyType>*> member;

public:
    Team();
    ~Team();
    void addWarrior(KeyType name, int lv);
    void addWizard(KeyType name, int lv);
    void memberBeatMonster(KeyType name, int exp);
    void printMember(KeyType name);
};

template<typename KeyType>
Team<KeyType>::Team()
{
    // this->memberCount = 0;
    // for (int i = 0; i < 10; i++)
    //     member[i] = nullptr;
}

template<typename KeyType>
Team<KeyType>::~Team()
{
    // for (int i = 0; i < this->memberCount; i++)
    //     delete this->member[i];
    while (this->member.size() > 0)
    {
        delete this->member.back();
        this->member.pop_back();
    }   
}

template<typename KeyType>
void Team<KeyType>::addWarrior(KeyType name, int lv)
{
    // if (memberCount < 10)
    // {
    //     member[memberCount] = new Warrior<KeyType>(name, lv);
    //     memberCount++;
    // }

    Warrior<KeyType>* wptr = new Warrior<KeyType>(name, lv);
    this->member.push_back(wptr);
}

template<typename KeyType>
void Team<KeyType>::addWizard(KeyType name, int lv)
{
    // if (memberCount < 10)
    // {
    //     member[memberCount] = new Wizard<KeyType>(name, lv);
    //     memberCount++;
    // }

    Wizard<KeyType>* wptr = new Wizard<KeyType>(name, lv);
    this->member.push_back(wptr);
}

template<typename KeyType>
void Team<KeyType>::memberBeatMonster(KeyType name, int exp)
{
    for (int i = 0; i < this->member.size(); i++)
    {
        if (this->member[i]->getName() == name)
        {
            this->member[i]->beatMonster(exp);
            break;
        }
    }
}

template<typename KeyType>
void Team<KeyType>::printMember(KeyType name)
{
    for (int i = 0; i < this->member.size(); i++)
    {
        if (this->member[i]->getName() == name)
        {
            this->member[i]->print();
            break;
        }
    }
}
// ===========================================================================
// End of Character, Warrior, Wizard, and Team
// ===========================================================================

int main()
{
    Character<string> *c[3];
    c[0] = new Warrior<string>("Alice", 10);
    c[1] = new Wizard<string>("Sophie", 8);
    c[2] = new Warrior<string>("Amy", 12);
    c[0]->beatMonster(10000);
    for (int i = 0; i < 3; i++)
        c[i]->print();
    for (int i = 0; i < 3; i++)
        delete c[i];

    //Character test("test", 1, 2, 3, 4); cannot declare abstract type
    
    Team<string> stringTeam;
    stringTeam.addWarrior("Kate", 2);
    stringTeam.memberBeatMonster("Kate", 10000);
    stringTeam.addWarrior("Eric", 2);
    stringTeam.printMember("Kate");
    stringTeam.printMember("Eric");

    Team<int> intTeam;
    intTeam.addWarrior(1, 2);
    intTeam.memberBeatMonster(1, 10000);
    intTeam.addWarrior(5, 2);
    intTeam.printMember(1);
    intTeam.printMember(5);




    return 0;
}
