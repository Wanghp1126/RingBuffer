/*******************************************************************************
* @FileName: RingBuffer.h
* @Author: Michael
* @Version: V1.1
* @Date: 2021/02/16
* @Brief: 环形队列
* @Others:
********************************************************************************
* @Function List:
*  1. uint16_t RingBuffer_FreeSpace(struct RingBuffer_t* ringBuffer)
*  2. int8_t RingBuffer_Push(struct RingBuffer_t* ringBuffer, void* element, bool checkFull)
*  3. int8_t int8_t RingBuffer_Pop(struct RingBuffer_t* ringBuffer, void* element, bool readOnly)
*  4. void* RingBuffer_Reset(struct RingBuffer_t* ringBuffer)
*  5. void* RingBuffer_ClearUp(struct RingBuffer_t* ringBuffer)
*
********************************************************************************
* @History:
*  1. V1.0
*  Date: 2020/03/23
*  Author: Michael
*  1. uint16_t RingBuffer_FreeSpace(struct RingBuffer_t* ringBuffer)
*  2. int8_t RingBuffer_Push(struct RingBuffer_t* ringBuffer, void* element)
*  3. int8_t RingBuffer_Pop(struct RingBuffer_t* ringBuffer, void* element, int8_t readOnly)
*  4. void RingBuffer_Flush(struct RingBuffer_t* ringBuffer)

*  2. V1.1
*  Date: 2021/02/16
*  Author: Michael
*  Modification:
*  增加 void* RingBuffer_ClearUp(struct RingBuffer_t* ringBuffer)
*  修改 int8_t RingBuffer_Push(struct RingBuffer_t* ringBuffer, void* element, bool checkFull)
*  修改 int8_t RingBuffer_Pop(struct RingBuffer_t* ringBuffer, void* element, bool readOnly)
*  修改 void* RingBuffer_Reset(struct RingBuffer_t* ringBuffer)
*
*  3. ...
*
*******************************************************************************/

#include "RingBuffer.h"
#include <string.h>

/**
* @Function: 
          获得队列中的空闲空间
* @Brief: 
* @Calls: None
* @Called By: None
* @Input: 
          ringBuffer - 环形队列结构体指针
* @Output: None
* @Return: 
          能够存储元素类型的空闲空间的数量
* @Others: None
**/
uint16_t RingBuffer_FreeSpace(struct RingBuffer_t* ringBuffer)
{
	int32_t total;

	total = ringBuffer->head - ringBuffer->tail;
	if (total < 0)
	{
		total += (2 * ringBuffer->element_count);
	}

	total = ringBuffer->element_count - total;

	return (uint16_t)total;
}

/**
* @Function:  
          把数据添加到环形队列中
* @Brief: 
* @Calls:  
          RingBuffer_FreeSpace()、memcpy()
* @Called By: None
* @Input:  
          ringBuffer - 环形队列结构体指针
          element - 存储的元素（可以是uint8_t、int16_t或者struct等）指针
          checkFull - true 检查队列是否已满；
                      fasle不检查队列是否已满，队列已满时直接覆盖原数据
* @Output: None
* @Return:  
          0 - 成功
          -1 - 队列已满
* @Others: None
**/
int8_t RingBuffer_Push(struct RingBuffer_t* ringBuffer, void* element, bool checkFull)
{
	uint8_t* head;

	if (checkFull == true)
	{
		if (RingBuffer_FreeSpace(ringBuffer) == 0)
		{
			return -1; // 队列已满
		}
	}

	head = (uint8_t*)ringBuffer->buffer
		+ ((ringBuffer->head % ringBuffer->element_count) * ringBuffer->element_size);

	memcpy(head, element, ringBuffer->element_size);

	ringBuffer->head++;

	if (ringBuffer->head >= (2 * ringBuffer->element_count)) // 2* 是为了方便空闲空间计算
	{
		ringBuffer->head = 0;
	}

	return 0;
}

/**
* @Function:  
          获取环形队列中的数据
* @Brief: 
* @Calls:  
          RingBuffer_FreeSpace()、memcpy()
* @Called By: None
* @Input:  
          ringBuffer - 环形队列结构体指针
          element - 存储的元素（可以是uint8_t、int16_t或者struct等）指针
          readOnly - true 只读但不调整队列中的指针; false读取数据并调整队列中的指针；
* @Output: None
* @Return:  
          0 - 成功
          -1 - 队列为空
* @Others: None
**/
int8_t RingBuffer_Pop(struct RingBuffer_t* ringBuffer, void* element, bool readOnly)
{
	uint8_t* tail;

	if (RingBuffer_FreeSpace(ringBuffer) == ringBuffer->element_count)
	{
		return -1; // 队列为空
	}

	tail = (uint8_t*)ringBuffer->buffer
		+ ((ringBuffer->tail % ringBuffer->element_count) * ringBuffer->element_size);

	if (element)
	{
		memcpy(element, tail, ringBuffer->element_size);
	}

	if (readOnly == false )
	{
		// 此处可以增加清零的操作：memset(tail, 0, ringBuffer->elementSize);

		ringBuffer->tail++;
		if (ringBuffer->tail >= (2 * ringBuffer->element_count)) // 2* 是为了方便空闲空间计算
		{
			ringBuffer->tail = 0;
		}
	}
	return 0;
}

/**
* @Function:  
          重置队列的头指针和尾部指针为0，不清除其他内容
* @Brief: None
* @Calls: None
* @Called By: None
* @Input:  
          ringBuffer - 环形队列结构体指针
* @Output: None
* @Return: 环形队列结构体指针
* @Others: None
**/
void* RingBuffer_Reset(struct RingBuffer_t* ringBuffer)
{
	ringBuffer->tail = 0;
	ringBuffer->head = 0;
	return ringBuffer;
}

/**
* @Function:  
          清空队列
* @Brief: None
* @Calls: RingBuffer_Reset()、memset()
* @Called By: None
* @Input:  
          ringBuffer - 环形队列结构体指针
* @Output: None
* @Return: 环形队列结构体指针
* @Others: None
**/
void* RingBuffer_ClearUp(struct RingBuffer_t* ringBuffer)
{
	RingBuffer_Reset(ringBuffer);	
	memset(ringBuffer->buffer, 0, (ringBuffer->element_count * ringBuffer->element_size));	
	return ringBuffer;
}



/************************************************************** end of file ***/
