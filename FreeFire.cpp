#include <bits/stdc++.h>
using namespace std;

class Gun {
protected:
    string name;
    int mag_size;
    double base_dmg;
    double base_rate;
    int mags;
    double wear;
public:
    Gun(string n, int ms, double bd, double br, int m, double w)
        : name(n), mag_size(ms), base_dmg(bd), base_rate(br), mags(m), wear(w) {}

    virtual ~Gun() {}

    string getName() { return name; }

    virtual double getDamage() {
        if (wear < 1.0) return base_dmg * wear;
        return base_dmg;
    }

    virtual double getTimePerShot() {
        double rate = base_rate;
        if (wear < 1.0) rate = rate / 2.0;
        return 1.0 / rate;
    }

    double calculateTotalDamage(double t) {
        double dmg = getDamage();
        double t_shot = getTimePerShot();
        double current_time = 0.0;
        double total_dmg = 0.0;
        int current_bullets =(mags>0)?mag_size:0;
        int remaining_mags =(mags>0)? mags - 1:0;

        while (current_time <= t - 1e-6) {
            if (current_bullets == 0) {
                if (remaining_mags > 0) {
                    current_time += 2.0;
                    remaining_mags--;
                    current_bullets = mag_size;
                    continue;
                } else {
                    break;
                }
            }
            if(current_time<t -1e-6){  
                total_dmg += dmg;
               current_bullets--;
               current_time += t_shot;
            }
        }
        return total_dmg;
    }
};

class Pistol : public Gun {
public:
    Pistol(string n, int ms, double bd, double br, int m, double w)
        : Gun(n, ms, bd, br, m, w) {}
};

class AssaultRifle : public Gun {
private:
    double bonus_dmg;
public:
    AssaultRifle(string n, int ms, double bd, double br, int m, double w, double bonus)
        : Gun(n, ms, bd, br, m, w), bonus_dmg(bonus) {}

    double getDamage() override {
        return Gun::getDamage() + bonus_dmg;
    }
};

class Sniper : public Gun {
public:
    Sniper(string n, int ms, double bd, double br, int m, double w)
        : Gun(n, ms, bd, br, m, w) {}

    double getTimePerShot() override {
        return Gun::getTimePerShot() + 1.0;
    }
};

int main() {
    int n;
    if (!(cin >> n)) return 0;
    vector<Gun*> inventory;

    for (int i = 0; i < n; i++) {
        int type, mags;
        double wear;
        cin >> type >> mags >> wear;

        if (type == 1) {
            inventory.push_back(new Pistol("G18", 12, 2, 1, mags, wear));
        } else if (type == 2) {
            inventory.push_back(new Pistol("M500", 5, 4, 0.5, mags, wear));
        } else if (type == 3) {
            double bonus; cin >> bonus;
            inventory.push_back(new AssaultRifle("MP40", 20, 3, 5, mags, wear, bonus));
        } else if (type == 4) {
            double bonus; cin >> bonus;
            inventory.push_back(new AssaultRifle("AK", 30, 5, 1, mags, wear, bonus));
        } else if (type == 5) {
            inventory.push_back(new Sniper("SVD", 10, 5, 0.5, mags, wear));
        } else if (type == 6) {
            inventory.push_back(new Sniper("AWM", 5, 10, 0.5, mags, wear));
        }
    }

    double t;
    cin >> t;

    for (Gun* gun : inventory) {
        cout << gun->getName() << ": " << gun->calculateTotalDamage(t) << endl;
    }

    for (Gun* gun : inventory) {
        delete gun;
    }
    inventory.clear();

    return 0;
}
