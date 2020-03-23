/*******************************************************************************
* @FileName: RingBuffer.h
* @Author: Michael
* @Version: V1.0
* @Date: 2020/03/23
* @Brief: ���ζ���
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
          ��ö����еĿ��пռ�
* @Brief: 
* @Calls: None
* @Called By: None
* @Input: 
          buf - ���ζ��нṹ��ָ��
* @Output: None
* @Return: 
          �洢Ԫ�����͵Ŀ��пռ������
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
          ��������ӵ����ζ�����
* @Brief: 
* @Calls:  
          RingBuffer_FreeSpace()��memcpy()
* @Called By: None
* @Input:  
          buf - ���ζ��нṹ��ָ��
          element - �洢��Ԫ�أ�������uint8_t��int16_t����struct�ȣ�ָ��
          checkFull - ��0������������0�������У�ֱ�Ӹ���
* @Output: None
* @Return:  
          0 - �ɹ�
          -1 - ��������
* @Others: None
**/
int8_t RingBuffer_Push(struct RingBuffer_t* buf, void* element, uint8_t checkFull)
{
	uint8_t* head;

	if (checkFull)
	{
		if (RingBuffer_FreeSpace(buf) == 0)
		{
			return -1; // ��������
		}
	}

	head = (uint8_t*)buf->buffer
		+ ((buf->head % buf->elements) * buf->elementSize);

	memcpy(head, element, buf->elementSize);

	buf->head++;

	if (buf->head >= (2 * buf->elements)) // 2* ��Ϊ�˷�����пռ����
	{
		buf->head = 0;
	}

	return 0;
}

/**
* @Function:  
          ��ȡ���ζ����е�����
* @Brief: 
* @Calls:  
          RingBuffer_FreeSpace()��memcpy()
* @Called By: None
* @Input:  
          buf - ���ζ��нṹ��ָ��
          element - �洢��Ԫ�أ�������uint8_t��int16_t����struct�ȣ�ָ��
          readOnly - 0Ϊ��ֻ������ʱ����������е�ָ�룻��0Ϊֻ����ֻ��ʱ�����������е�ָ��
* @Output: None
* @Return:  
          0 - �ɹ�
          -1 - ����Ϊ��
* @Others: None
**/
int8_t RingBuffer_Pop(struct RingBuffer_t* buf, void* element, uint8_t readOnly)
{
	uint8_t* tail;

	if (RingBuffer_FreeSpace(buf) == buf->elements)
	{
		return -1; // ����Ϊ��
	}

	tail = (uint8_t*)buf->buffer
		+ ((buf->tail % buf->elements) * buf->elementSize);

	if (element)
	{
		memcpy(element, tail, buf->elementSize);
	}

	if (!readOnly)
	{
		// �˴�������������Ĳ�����memset(tail, 0, buf->elementSize);

		buf->tail++;
		if (buf->tail >= (2 * buf->elements)) // 2* ��Ϊ�˷�����пռ����
		{
			buf->tail = 0;
		}
	}
	return 0;
}

/**
* @Function:  
          ���ö��е�ͷָ���β��ָ��Ϊ0���������������
* @Brief: None
* @Calls: None
* @Called By: None
* @Input:  
          buf - ���ζ��нṹ��ָ��
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
