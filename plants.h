#ifndef PLANTS_H
#define PLANTS_H


#include <iostream>
using namespace std;
class plants{
    int health_p;
    int firing_rate;
    int attack_power;
    string description;
public:
    plants(int h, int f, int a, string d):health_p(h),firing_rate(f),attack_power(a),description(d){}
    int getHealth() const ;
    int getFiringRate() const ;
    int getAttackPower() const ;
    string getDescription() const ;

    // Setter methods
    void setHealth(int h) ;
    void setFiringRate(int f) ;
    void setAttackPower(int a);
    void setDescription(const string &d) ;
     virtual ~plants() {}
};
class peashooter : public plants {
public:
    peashooter(int h, int f, int a, string d)
        : plants(h, f, a, d) {}
};
#endif // PLANTS_H
