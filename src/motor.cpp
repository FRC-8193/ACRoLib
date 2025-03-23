#include <acro/motor.h>
#include <acro/motor.hpp>

const acro_MotorFeature *acro_Motor_get_feature(const acro_Motor *self, acro_MotorFeature_ID id) {
	return (acro_MotorFeature *)&(((acro::Motor *)self)->get_feature(id));
}

void acro_Motor_delete(acro_Motor *self) {
	delete (acro::Motor *)self;
}

