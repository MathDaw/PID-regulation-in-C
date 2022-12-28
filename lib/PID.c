#include "PID.h"

enum PID_RETURN_STATUS pidInit(PID* pid, PID_DATA_INPUT_TYPE* setpoint, PID_DATA_INPUT_TYPE* measure, PID_DATA_INPUT_TYPE* output, PID_DATA_INPUT_TYPE* clock_register)
{
	pid->setpoint=setpoint;
	pid->measure=measure;
	pid->output=output;
	pid->clock_register=clock_register;
	pid->integral=0.0;
	pid->prev_diff=0;
	pid->next_check=*clock_register+pid->delay;
	return PID_OK;
}

enum PID_RETURN_STATUS pidCalculate(PID* pid)
{
	if(pid->mode==PID_MODE_NO_REGULATION)
		return PID_OK;
	pid->next_check = *pid->clock_register + pid->delay;
	PID_CALC_TYPE diff = (PID_CALC_TYPE)(*pid->setpoint - *pid->measure);
	PID_CALC_TYPE p=0.0,i=0.0,d=0.0, sum;
	if(pid->mode%2)
	{
		p=diff;
	}
	if((pid->mode>>1)%2)
	{
		pid->integral+=pid->ti * diff * ( (PID_CALC_TYPE)pid->delay ) / 1000.0;
		i=pid->integral;
	}
	if((pid->mode>>2)%2)
	{
		d=pid->td*( diff-pid->prev_diff )/((PID_CALC_TYPE)pid->delay);
		pid->prev_diff=diff;
	}
	sum=(p+i+d)*pid->k;
	*pid->output=(PID_DATA_INPUT_TYPE)sum;
	return PID_OK;
}

enum PID_CHECK_TIME pidCheckTime(PID* pid)
{
	if(*pid->clock_register >= pid->next_check)
		return PID_CHECK_TIME_OK;
	else
		return PID_CHECK_TIME_WAIT;
}

enum PID_RETURN_STATUS pidSetMode(PID* pid, enum PID_MODE_TYPE new_mode)
{
	if(new_mode<PID_NUMBER_OF_MODES)
	{
		pid->mode=new_mode;
		return PID_OK;
	}
	else
		return PID_ERR;
}

enum PID_RETURN_STATUS pidSetDelay(PID* pid, PID_DATA_INPUT_TYPE new_delay_ms)
{
	pid->delay=new_delay_ms;
	return PID_OK;
}

enum PID_RETURN_STATUS pidSetP(PID* pid, PID_CALC_TYPE new_k)
{
	pid->k=new_k;
	return PID_OK;
}

enum PID_RETURN_STATUS pidSetTi(PID* pid, PID_CALC_TYPE new_ti)
{
	pid->ti=new_ti;
	return PID_OK;
}

enum PID_RETURN_STATUS pidSetTd(PID* pid, PID_CALC_TYPE new_td)
{
	pid->td=new_td;
	return PID_OK;
}
