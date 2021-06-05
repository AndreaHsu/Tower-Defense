#ifndef ACIDCELLTURRET_HPP
#define ACIDCELLTURRET_HPP
#include "Turret.hpp"

class AcidCellTurret : public Turret {
public:
	static const int Price;
	AcidCellTurret(float x, float y);
	void CreateBullet() override;
};
#endif // ACIDCELLTURRET_HPP


