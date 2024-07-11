#include "plants.h"
int plants::getHealth() const { return health_p; }
int plants::getFiringRate() const { return firing_rate; }
int plants::getAttackPower() const { return attack_power; }
string plants::getDescription() const { return description; }

// Setter methods
void plants::setHealth(int h) { health_p = h; }
void plants::setFiringRate(int f) { firing_rate = f; }
void plants::setAttackPower(int a) { attack_power = a; }
void plants::setDescription(const string &d) { description = d; }
