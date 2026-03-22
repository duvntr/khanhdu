#include <bits/stdc++.h>
using namespace std;
class Beverage{
public:
    string name;
    float price;
    Beverage(){
        name="";
        price=0.0;
    }
    virtual ~Beverage()=default;
    virtual void Input(){
        cin>>name;
        cin>>price;
    }
};
class Coffee : public Beverage{
public:
    int isHasIce;
    void Input() override{
        Beverage::Input();
        cin>>isHasIce;
    }
};
class Tea : public Beverage{
public:
    int isManySugar;
    void Input() override{
        Beverage::Input();
        cin>>isManySugar;
    }
};
class OtherBeverage : public Beverage{

};
string toLowerCase(string s){
    for(int i=0;i<s.length();i++){
        s[i]=tolower(s[i]);
    }
    return s;
}
bool coChuaSua(string tenMon){
    if(tenMon.find("sua")!=string::npos){
        return true;
    }
    else{
        return false;
    }
}
int main(){
    vector<unique_ptr<Beverage>> beverages;
    int n;
    float totalPrice=0;
    int numberOfMilk=0;
    cin>>n;
    for(int i=0;i<n;i++){
        int type;
        cin>>type;
        unique_ptr<Beverage> drink;
        if(type==1){
            drink = make_unique<Coffee>();
        }
        else if(type==2){
            drink = make_unique<Tea>();
        }
        else if(type==3){
            drink = make_unique<OtherBeverage>();
        }
        else{
            continue;
        }
        drink->Input();
        totalPrice+=drink->price;
        string lowername = toLowerCase(drink->name);
        if(coChuaSua(lowername)==true){
            numberOfMilk++;
        }
        beverages.push_back(move(drink));
    }
    string customerName;
    int day,month,year;
    cin>>customerName>>day>>month>>year;
    if(month==7){
        totalPrice*=0.9;
    }
    cout<<"Tong gia tri hoa don: "<<totalPrice<<endl;
    cout<<"Tong so mon co sua: "<<numberOfMilk<<endl;
    return 0;
}
