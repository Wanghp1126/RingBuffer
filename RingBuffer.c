/*******************************************************************************
* @FileName: RingBuffer.h
* @Author: Michael
* @Version: V1.0
* @Date: 2020/03/23
* @Brief: 环形队列
* @Others:
********************************************************************************
* @Function List:
*  1. uint16_t RingBuffer_FreeSpace(struct RingBuffer_t* buf)
*  2. int8_t RingBuffer_Push(struct RingBuffer_t* buf, void* element)
*  3. int8_t RingBuffer_Pop(struct RingBuffer_t* buf, void* element, int8_t readOnly)
*  4. void RingBuffer_Flush(struct RingBuffer_t* buf)
*
********************************************************************************
* @History:
*  1. Date:  
*  Author:
*  Modification:
*  
*  2. ...
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
          buf - 环形队列结构体指针
* @Output: None
* @Return: 
          存储元素类型的空闲空间的数量
* @Others: None
**/
uint16_t RingBuffer_FreeSpace(struct RingBuffer_t* buf)
{
	int32_t total;

	total = buf->head - buf->tail;
	if (total < 0)
	{
		total += (2 * buf->elements);
	}

	total = buf->elements - total;

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
          buf - 环形队列结构体指针
          element - 存储的元素（可以是uint8_t、int16_t或者struct等）指针
          checkFull - 非0检查队列已满；0不检查队列，直接覆盖
* @Output: None
* @Return:  
          0 - 成功
          -1 - 队列已满
* @Others: None
**/
int8_t RingBuffer_Push(struct RingBuffer_t* buf, void* element, uint8_t checkFull)
{
	uint8_t* head;

	if (checkFull)
	{
		if (RingBuffer_FreeSpace(buf) == 0)
		{
			return -1; // 队列已满
		}
	}

	head = (uint8_t*)buf->buffer
		+ ((buf->head % buf->elements) * buf->elementSize);

	memcpy(head, element, buf->elementSize);

	buf->head++;

	if (buf->head >= (2 * buf->elements)) // 2* 是为了方便空闲空间计算
	{
		buf->head = 0;
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
          buf - 环形队列结构体指针
          element - 存储的元素（可以是uint8_t、int16_t或者struct等）指针
          readOnly - 0为非只读，此时会调整队列中的指针；非0为只读，只读时不调整队列中的指针
* @Output: None
* @Return:  
          0 - 成功
          -1 - 队列为空
* @Others: None
**/
int8_t RingBuffer_Pop(struct RingBuffer_t* buf, void* element, uint8_t readOnly)
{
	uint8_t* tail;

	if (RingBuffer_FreeSpace(buf) == buf->elements)
	{
		return -1; // 队列为空
	}

	tail = (uint8_t*)buf->buffer
		+ ((buf->tail % buf->elements) * buf->elementSize);

	if (element)
	{
		memcpy(element, tail, buf->elementSize);
	}

	if (!readOnly)
	{
		// 此处可以增加清零的操作：memset(tail, 0, buf->elementSize);

		buf->tail++;
		if (buf->tail >= (2 * buf->elements)) // 2* 是为了方便空闲空间计算
		{
			buf->tail = 0;
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
          buf - 环形队列结构体指针
* @Output: None
* @Return: None
* @Others: None
**/
void RingBuffer_Flush(struct RingBuffer_t* buf)
{
	buf->tail = 0;
	buf->head = 0;
}

/************************************************************** end of file ***/
