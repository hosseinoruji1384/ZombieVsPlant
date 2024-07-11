#include "zombie.h"
int zombie::getHealth_z() const { return health_z; }
int zombie::getmovementdelay() const { return movement_delay; }
int zombie::getAttackPower_z() const { return attack_power; }
int zombie:: gettime_between_attack()const{return time_between_attack;}
string zombie::getDescription_z() const { return description; }

// Setter methods
void zombie::setHealth_z(int h) { health_z = h; }
void zombie::setmovement_delay(int f) { movement_delay = f; }
void zombie::setAttackPower_z(int a) { attack_power = a; }
void zombie::settime_between_attack(int t){time_between_attack=t;}
void zombie::setDescription_z(const string &d) { description = d; }
