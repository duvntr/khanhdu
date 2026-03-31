#include <bits/stdc++.h>
using namespace std;

class DaThuc{
private:
    int n;
    vector<int> a;
public:
    DaThuc(){
        n=0;
        a.resize(1, 0); 
    }
    
    friend istream& operator>>(istream& is,DaThuc & dt){
        is>>dt.n;
        dt.a.resize(dt.n + 1); 
        for(int i=0;i<=dt.n;i++){
            is>>dt.a[i];
        }
        return is; 
    }
    
    friend ostream& operator<<(ostream& os,DaThuc dt){
        bool first = true;
        for(int i=0;i<=dt.n;i++){
            if(dt.a[i] != 0){
                if(first == false && dt.a[i] > 0){
                    os << "+";
                }
                os << dt.a[i] << "x^" << i;
                first = false;
            }
        }
        if(first == true) os << "0"; 
        return os;
    }
    
    friend DaThuc operator+(DaThuc dt1,DaThuc dt2){
        DaThuc tong;
        tong.n=max(dt1.n,dt2.n);
        
        tong.a.resize(tong.n + 1, 0); 
        dt1.a.resize(tong.n + 1, 0);
        dt2.a.resize(tong.n + 1, 0);
        
        for(int i=0;i<=tong.n;i++){
            tong.a[i]=dt1.a[i]+dt2.a[i];
        }
        return tong;
    }
    
    friend DaThuc operator-(DaThuc dt1,DaThuc dt2){
        DaThuc hieu;
        hieu.n=max(dt1.n,dt2.n);
        
        hieu.a.resize(hieu.n + 1, 0);
        dt1.a.resize(hieu.n + 1, 0);
        dt2.a.resize(hieu.n + 1, 0);
        
        for(int i=0;i<=hieu.n;i++){
            hieu.a[i]=dt1.a[i]-dt2.a[i];
        }
        return hieu;
    }
    
    friend DaThuc operator*(DaThuc dt1,DaThuc dt2){
        DaThuc tich;
        tich.n=dt1.n+dt2.n;
        
        tich.a.resize(tich.n + 1, 0); 
        
        for(int i=0;i<=dt1.n;i++){
            for(int j=0;j<=dt2.n;j++){
                tich.a[i+j]+=dt1.a[i]*dt2.a[j];
            }
        }
        return tich;
    }
};

int main(){
    DaThuc P,Q;
    string dau;
    cin>>P;
    cin>>Q;
    cin>>dau;
    DaThuc Tong=P+Q;
    DaThuc Hieu=P-Q;
    DaThuc Tich=P*Q;
    if(dau=="+"){
        cout<<Tong;
    }
    else if(dau=="-"){
        cout<<Hieu;
    }
    else if(dau=="*"){
        cout<<Tich;
    }
    return 0;
}
