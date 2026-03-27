#include <bits/stdc++.h>
using namespace std;

class DaThuc {
private:
    int n;
    vector<int> a;
public:
    DaThuc() {
        n = 0;
        a.resize(1, 0);
    }
    friend istream& operator>>(istream& is, DaThuc & dt) {
        is >> dt.n;
        dt.a.resize(dt.n + 1);
        for(int i = 0; i <= dt.n; i++){
            is >> dt.a[i];
        }
        return is;
    }

    friend ostream& operator<<(ostream& os, const DaThuc & dt) {
        bool isZero = true;
        for(int i = 0; i <= dt.n; i++){
            if(dt.a[i] != 0) {
                isZero = false;
                if(dt.a[i] > 0 && i > 0) os << "+";
                os << dt.a[i];
                if (i > 0) os << "x^" << i;
            }
        }
        if (isZero) os << "0";
        return os;
    }
    friend DaThuc operator+(const DaThuc& dt1, const DaThuc& dt2){
        DaThuc tong;
        tong.n = max(dt1.n, dt2.n);
        tong.a.resize(tong.n + 1, 0);
        for(int i = 0; i <= tong.n; i++){
            int heso1 = (i <= dt1.n) ? dt1.a[i] : 0;
            int heso2 = (i <= dt2.n) ? dt2.a[i] : 0;
            tong.a[i] = heso1 + heso2;
        }
        return tong;
    }
    friend DaThuc operator-(const DaThuc& dt1, const DaThuc& dt2){
        DaThuc hieu;
        hieu.n = max(dt1.n, dt2.n);
        hieu.a.resize(hieu.n + 1, 0);
        for(int i = 0; i <= hieu.n; i++){
            int heso1 = (i <= dt1.n) ? dt1.a[i] : 0;
            int heso2 = (i <= dt2.n) ? dt2.a[i] : 0;
            hieu.a[i] = heso1 - heso2;
        }
        return hieu;
    }

    friend DaThuc operator*(const DaThuc& dt1, const DaThuc& dt2){
        DaThuc tich;
        tich.n = dt1.n + dt2.n;
        tich.a.resize(tich.n + 1, 0);
        for(int i = 0; i <= dt1.n; i++){
            for(int j = 0; j <= dt2.n; j++){
                tich.a[i+j] += dt1.a[i] * dt2.a[j];
            }
        }
        return tich;
    }
};

int main(){
    DaThuc P, Q;
    string dau;
    cin >> P;
    cin >> Q;
    cin >> dau;
    if(dau == "+"){
        cout << P + Q;
    }
    else if(dau == "-"){
        cout << P - Q;
    }
    else if(dau == "*"){
        cout << P * Q;
    }
    return 0;
}
