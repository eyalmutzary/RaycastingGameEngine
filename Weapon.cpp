#include "Weapon.h"

Weapon::Weapon(Texture_state& texture_state, Weapon_state weapon_state, int ammo, int damage, int fire_rate, int reload_time, float bullet_speed)
    : texture_state(texture_state), weapon_state(weapon_state), ammo(ammo), damage(damage), fire_rate(fire_rate), reload_time(reload_time), bullet_speed(bullet_speed) {}
