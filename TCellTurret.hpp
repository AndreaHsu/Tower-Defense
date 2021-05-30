#ifndef TCELLTURRET_HPP
#define TCELLTURRET_HPP
#include "Turret.hpp"

class TCellTurret : public Turret {
protected:
	int flag = 0;
public:
	static const int Price;
	TCellTurret(float x, float y);
	void CreateBullet();
	void Update(float deltaTime) override;
};
#endif // TCELLTURRET_HPP
