#include "PID.h"

uint8_t pidInit(PID* pid, float* setpoint, uint32_t* measure, uint32_t* output, uint32_t* clock_register)
{
	pid->setpoint=setpoint;
	pid->measure=measure;
	pid->output=output;
	pid->clock_register=clock_register;
	pid->integral=0.0;
	pid->prev_meas=0;
	pid->next_check=clock_register+pid->delay;
}

uint8_t pidCalculate(PID* pid)
{
	if(pid->mode==PID_MODE_NO_REGULATION)
		return PID_OK;
	uint32_t measure = pid->measure;
	float p=0.0,i=0.0,d=0.0, sum;
	if(pid->mode%2)
	{
		p=1.0;
	}
	if((pid->mode>>1)%2)
	{
		pid->integral+=pid->ti*((float)(measure))*((float)pid->delay)/1000.0;
		i=pid->integral;
	}
	if((pid->mode>>2)%2)
	{
		d=pid->td*((float)(measure-pid->prev_meas))/((float)pid->delay);
		pid->prev_meas=measure;
	}
	sum=(p+i+d)*pid->k;
	pid->output=(uint32_t)sum;
	return PID_OK;
}

uint8_t pidCheckTime(PID* pid)
{
	if(pid->next_check>pid->clock_register)
		return PID_CHECK_TIME_OK;
	else
		return PID_CHECK_TIME_WAIT;
}

uint8_t pidSetMode(PID* pid, uint8_t new_mode)
{
	if(new_mode<PID_NUMBER_OF_MODES)
	{
		pid->mode=new_mode;
		return PID_OK;
	}
	else
		return PID_ERR;
}

uint8_t pidSetDelay(PID* pid, uint32_t new_delay)
{
	pid->delay=new_delay;
	return PID_OK;
}

uint8_t pidSetP(PID* pid, float new_k)
{
	pid->k=new_k;
	return PID_OK;
}

uint8_t pidSetTi(PID* pid, float new_ti)
{
	pid->ti=new_ti;
	return PID_OK;
}

uint8_t pidSetTd(PID* pid, float new_td)
{
	pid->td=new_td;
	return PID_OK;
}
