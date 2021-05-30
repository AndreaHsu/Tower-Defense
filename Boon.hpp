#ifndef BOON_HPP
#define BOON_HPP
#include "Turret.hpp"

class Boon: public Turret {
public:
	static const int Price;
	Boon(float x, float y);
	void CreateBullet();
	void Update(float deltaTime) override;
};
#endif // BOON_HPP
