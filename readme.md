# 简介
这是一个环形队列（Ring Buffer）的框架，该框架使用 C 语言实现
关于环形队列的更多信息可以参考如下连接https://zh.wikipedia.org/wiki/%E7%92%B0%E5%BD%A2%E7%B7%A9%E8%A1%9D%E5%8D%80



# 功能介绍

## 队列的声明
使用本框架的 `RingBuffer_Def` 宏定义，可以定义环形队列的结构体`RingBuffer_t `和静态存储内存。本框架支持诸如 uint8_t、uint16_t、struct类型的数据。如下声明一个结构体的环形队列
```c
struct People{	
	uint16_t heigth;
	uint8_t age;
};

// 声明 peoples 环形队列及其静态内存 peoples_data
static RingBuffer_Def(struct People, peoples, 3);
// 声明两个 People 变量
static struct People people_a, people_b;
```
## 5个功能的使用

**1、获得环形队列的剩余空间 **

```c
uint16_t RingBuffer_FreeSpace(struct RingBuffer_t* ringBuffer);
```
- 剩余空间指的是所声明类型的剩余数量；例如：上面的结构体`People`，声明环形队列的长度为3；如果已经使用了1个，则剩余空间为2，而不是 6 byte。
- ringBuffer是环形队列结构体指针，例如：&peoples

**2、添加数据到队列**

```c
int8_t RingBuffer_Push(struct RingBuffer_t* ringBuffer, void* element, bool checkFull)
```
- ringBuffer是环形队列的结构体指针，例如：&peoples
- element要添加元素的指针，必须和声明的类型相同，例如：people_a
- 此方法支持队列是否已满的检查。当形参`checkFull`为 `true` 时，检查队列是否已满，如果队列已满，数据不会添加到队列中，并且返回-1；当形参`checkFull`为 `false` 时，不检查队列是否已满，如果队列已满，将覆盖原有数据。

**3、读取队列中的数据**


```c
int8_t RingBuffer_Pop(struct RingBuffer_t* ringBuffer, void* element, bool readOnly)
```

- ringBuffer是环形队列的结构体指针，例如：&peoples
- element要读到元素的指针，必须和声明的类型相同，例如：people_b
- 此方法支持是否删除已经被读出的数据。`readOnly`为 `true` 时，只读数据不调整队列中的数据指针，再读取时，还是原来的数据。`readOnly`为 `false` 时，读取数据后队列指针被调整，再读取时，就会变为下一个数据。

**4、队列重置**

```C
void* RingBuffer_Reset(struct RingBuffer_t* ringBuffer)
```

环形队列的头指针和尾指针重置为0。

**5、队列清空**

```c
void* RingBuffer_ClearUp(struct RingBuffer_t* ringBuffer)
```

环形队列的头指针和尾指针重置为0，并将静态内存清除为0。