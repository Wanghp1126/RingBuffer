/**
* 示例如下：


#include "RingBuffer.h"

struct people{
	uint8_t age;
	uint16_t heigth;
};

RingBuffer_Def(uint8_t, sample, 3);
RingBuffer_Def(struct people, peoples, 3);

void RingBufferSample()
{
	uint8_t abc;
	uint8_t abc_result;
	struct people pp;
	struct people pp_result;
	
	
	pp.age = 10;
	pp.heigth = 600;
	RingBuffer_Push(&peoples, &pp, 1);
	
	pp.age = 21;
	pp.heigth = 1600;
	RingBuffer_Push(&peoples, &pp, 1);
	
	pp.age = 30;
	pp.heigth = 2000;
	RingBuffer_Push(&peoples, &pp, 1);
	
	RingBuffer_Pop(&peoples, &pp_result, 0);
	RingBuffer_Pop(&peoples, &pp_result, 0);
	
	pp.age = 25;
	pp.heigth = 1800;
	RingBuffer_Push(&peoples, &pp);
	
	
	abc=1;
	RingBuffer_Push(&sample, &abc, 1);
	abc=2;
	RingBuffer_Push(&sample, &abc, 1);
	abc=3;
	RingBuffer_Push(&sample, &abc, 1);
	
	RingBuffer_Pop(&sample, &abc_result, 0);
	RingBuffer_Pop(&sample, &abc_result, 0);
}

*/
