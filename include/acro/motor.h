#ifndef ACRO_MOTOR_H
#define ACRO_MOTOR_H
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct acro_Motor acro_Motor;
typedef struct acro_MotorFeature acro_MotorFeature;
typedef uint64_t acro_MotorFeature_ID;

const acro_MotorFeature *acro_Motor_get_feature(const acro_Motor *, acro_MotorFeature_ID);

void acro_Motor_delete(acro_Motor *);

#endif

#ifdef __cplusplus
}
#endif
