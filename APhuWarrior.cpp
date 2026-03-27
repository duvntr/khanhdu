#include <bits/stdc++.h>
using namespace std;
float maxhp=0;
float current_hp=0;
class Weapon{
public:
    float damage;
    int num_turns;
    virtual void Input(){
        cin>> damage>>num_turns;
    }
    virtual float Attack()=0;
    virtual bool isOutOfTurns(){
        return num_turns<=0;
    }
    virtual ~Weapon (){}
};
class Sword:public Weapon{
public:
    float length;
    void Input() override{
        Weapon::Input();
        cin>>length;
    }
    float Attack() override{
        num_turns-=1;
        return damage*length;
    }
};
class Bow:public Weapon{
public:
    int num_arrows;
    void Input() override{
        Weapon::Input();
        cin>>num_arrows;
    }
    float Attack() override{
        num_arrows-=2;
        return damage*num_arrows/2.0f;
    }
};
class BareHands:public Weapon{
public:
    BareHands(){
        num_turns=1;
    }
    float Attack() override{
        float self_dmg=maxhp*0.1f;
        current_hp-=self_dmg;
        return self_dmg;
    }
    bool isOutOfTurns() override{
        return false;
    }
};
class Animal{
public:
    float hp;
    float damage;
    bool is_dead=false;
    virtual void Input(){
        cin>>hp>>damage;
    }
    virtual void TakeDamage(float dmg){
        hp-=dmg;
        CheckDie();
    }
    virtual float Attack(){
        return damage;
    }
    virtual void CheckDie(){
        if(hp<=0){
            is_dead=true;
        }
    }
    virtual ~Animal(){}
};
class Bull:public Animal{
public:
    int hits_to_die;
    void Input() override{
        Animal::Input();
        cin>>hits_to_die;
    }
    void TakeDamage(float dmg) override{
        hp-=dmg;
        hits_to_die-=1;
        CheckDie();
    }
    void CheckDie() override{
        if(hp<=0||hits_to_die<=0){
            is_dead=true;
        }
    }
};
class Tiger:public Animal{
public:
    float Attack() override{
        return damage*1.5f;
    }
};
int main(){
    cin>>maxhp;
    current_hp=maxhp;
    int n;
    cin>>n;
    vector<Weapon*> weapons;
    for(int i=0;i<n;i++){
        int type;
        cin>>type;
        Weapon* w = nullptr;
        if(type==1) w = new Sword();
        if(type==2) w = new Bow();
        if(w){
            w->Input();
            weapons.push_back(w);
        }
    }
    weapons.push_back(new BareHands());
    int m;
    cin>>m;
    vector<Animal*> animals;
    for(int i=0;i<m;i++){
        int type;
        cin>>type;
        Animal* a = nullptr;
        if(type==1) a = new Bull();
        if(type==2) a = new Tiger();
        if(a){
            a->Input();
            animals.push_back(a);
        }
    }
    int w_idx=0;
    int a_idx=0;
    while(a_idx<m && current_hp>0){
        while(w_idx<weapons.size() && weapons[w_idx]->isOutOfTurns()){
            w_idx++;
        }
        float dmg_dealt=weapons[w_idx]->Attack();
        animals[a_idx]->TakeDamage(dmg_dealt);
        if(animals[a_idx]->is_dead){
            a_idx++;
        }
        else{
            if(current_hp>0){
                current_hp-=animals[a_idx]->Attack();
            }
        }
    }
    if(current_hp<=0){
        cout<<"A Phu that bai, so thu du con lai: "<<(m-a_idx)<<endl;
    }
    else{
        int weapons_left=0;
        for(int i=0;i<n;i++){
            if(!weapons[i]->isOutOfTurns()){
                weapons_left++;
            }
        }
        cout<<"A Phu chien thang, hp con lai: "<<current_hp<<", so vu khi con lai: "<<weapons_left<<endl;
    }
    for(auto a:animals) delete a;
    for(auto w:weapons) delete w;
    return 0;
}
