#include "RingBuffer.h"

struct people{	
	uint16_t heigth;
	uint8_t age;
};

static RingBuffer_Def(uint8_t, sample, 3);
static RingBuffer_Def(struct people, peoples, 3);

static void Demo()
{
	int8_t result;
	uint8_t abc;
	uint8_t abc_result;
	struct people pp;
	struct people pp_result;
	
	
	pp.age = 10;
	pp.heigth = 600;
	result= RingBuffer_Push(&peoples, &pp, 1);
	
	pp.age = 20;
	pp.heigth = 1600;
	result = RingBuffer_Push(&peoples, &pp, 1);
	
	pp.age = 30;
	pp.heigth = 2000;
	RingBuffer_Push(&peoples, &pp, 1);
	
	result = RingBuffer_Pop(&peoples, &pp_result, 0);
	result = RingBuffer_Pop(&peoples, &pp_result, 0);
	
	pp.age = 40;
	pp.heigth = 1800;
	result = RingBuffer_Push(&peoples, &pp, 1);
	
	pp.age = 50;
	pp.heigth = 1800;
	result = RingBuffer_Push(&peoples, &pp, 1);
	
	
	abc=1;
	result = RingBuffer_Push(&sample, &abc, 1);
	abc=2;
	result = RingBuffer_Push(&sample, &abc, 1);
	abc=3;
	result = RingBuffer_Push(&sample, &abc, 1);
	
	result = RingBuffer_Pop(&sample, &abc_result, 0);
	result = RingBuffer_Pop(&sample, &abc_result, 0);
	
	RingBuffer_ClearUp(&sample);
	RingBuffer_ClearUp(&peoples);
}
