
#include "stm32f4xx_hal.h"

/*
 * status
 */
enum
{
	PID_OK,
	PID_ERR
};

typedef struct
{
	float k;
	float ti;
	float td;

	float integral;
	float prev_meas;

	uint8_t mode;

	uint32_t delay;
	uint32_t next_check;

	uint32_t* clock_register;
	float* setpoint;
	uint32_t* output;
	uint32_t* measure;
}PID;

uint8_t pidInit(PID* pid, float* setpoint, uint32_t* measure, uint32_t* output, uint32_t* clock_register);

uint8_t pidCalculate(PID* pid);

#define PID_CHECK_TIME_OK		0
#define PID_CHECK_TIME_WAIT		1
uint8_t pidCheckTime(PID* pid);

enum
{
	PID_MODE_NO_REGULATION,
	PID_MODE_P_REGULATOR,
	PID_MODE_I_REGULATOR,
	PID_MODE_PI_REGULATOR,
	PID_MODE_D_REGULATOR,
	PID_MODE_PD_REGULATOR,
	PID_MODE_ID_REGULATOR,
	PID_MODE_PID_REGULATOR,
	PID_NUMBER_OF_MODES
};
uint8_t pidSetMode(PID* pid, uint8_t new_mode);

uint8_t pidSetDelay(PID* pid, uint32_t new_delay);

uint8_t pidSetP(PID* pid, float new_k);

uint8_t pidSetTi(PID* pid, float new_ti);

uint8_t pidSetTd(PID* pid, float new_td);
