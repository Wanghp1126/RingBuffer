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

#ifndef __RINGBUFFER_H__
#define __RINGBUFFER_H__

// 硬件支持
#include "stm32f10x.h"

#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

	/**
	环形队列结构体，不推荐直接使用，推荐使用下面的宏定义 RingBuffer_Def
	*/
	struct RingBuffer_t {
		void* const buffer; // 存储空间的首指针
		uint16_t tail;      // 尾部
		uint16_t head;      // 首部
		uint16_t const element_count;  // 元素的数量
		uint16_t const element_size;   // 元素的字节长度
	};

	/**
	通过宏定义环形队列（同时定义了存储空间和环形队列结构体）
	type - 元素类型，如：uint8_t、int32_t、struct myStruct
	bufName - 要定义环形队列的名称
	size - 需要存储的元素数量
	*/
#define RingBuffer_Def(type, bufName, size)     \
    type bufName##_data[size];                  \
    struct RingBuffer_t bufName = {             \
                 .buffer = bufName##_data,      \
                 .tail = 0,                     \
                 .head = 0,                     \
                 .element_count = size,         \
                 .element_size = sizeof(type)   \
    }


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
			  存储元素类型的空闲空间的数量
	* @Others: None
	**/
	uint16_t RingBuffer_FreeSpace(struct RingBuffer_t* ringBuffer);

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
	int8_t RingBuffer_Push(struct RingBuffer_t* ringBuffer, void* element, bool checkFull);

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
	int8_t RingBuffer_Pop(struct RingBuffer_t* ringBuffer, void* element, bool readOnly);

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
	void* RingBuffer_Reset(struct RingBuffer_t* ringBuffer);
	
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
	void* RingBuffer_ClearUp(struct RingBuffer_t* ringBuffer);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // !__RINGBUFFER_H__

/************************************************************** end of file ***/
