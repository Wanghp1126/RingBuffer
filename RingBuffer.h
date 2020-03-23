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

#ifndef __RINGBUFFER_H__
#define __RINGBUFFER_H__

#include "stm32f10x.h"

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

	/**
	���ζ��нṹ�壬���Ƽ�ֱ��ʹ�ã��Ƽ�ʹ������ĺ궨�� RingBuffer_Def
	*/
	struct RingBuffer_t {
		void* const buffer; // �洢�ռ����ָ��
		uint16_t tail;      // β��
		uint16_t head;      // �ײ�
		uint16_t const elements;    // Ԫ�ص�����
		uint16_t const elementSize; // Ԫ�ص��ֽڳ���
	};

	/**
	ͨ���궨�廷�ζ��У�ͬʱ�����˴洢�ռ�ͻ��ζ��нṹ�壩
	type - Ԫ�����ͣ��磺uint8_t��int32_t��struct myStruct
	bufName - Ҫ���廷�ζ��е�����
	size - ��Ҫ�洢��Ԫ������
	*/
#define RingBuffer_Def(type, bufName, size)     \
    type bufName##_data[size];                  \
    struct RingBuffer_t bufName = {             \
                 .buffer = bufName##_data,      \
                 .tail = 0,                     \
                 .head = 0,                     \
                 .elements = size,              \
                 .elementSize = sizeof(type)    \
    };


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
	uint16_t RingBuffer_FreeSpace(struct RingBuffer_t* buf);

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
	int8_t RingBuffer_Push(struct RingBuffer_t* buf, void* element, uint8_t checkFull);

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
	int8_t RingBuffer_Pop(struct RingBuffer_t* buf, void* element, uint8_t readOnly);

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
	void RingBuffer_Flush(struct RingBuffer_t* buf);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // !__RINGBUFFER_H__

/************************************************************** end of file ***/
