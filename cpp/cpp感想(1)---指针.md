## cpp感想(1)---指针

版本号: V1.0

### 1 第一版本感想

一开始认为只是一个存储地址的变量, 但是发现有些片面了

### 2 第二版感想

想了很久发现, 没有一个词能够很好的形容指针, 感觉协议还靠边一点

协议, 协议就是一些特殊的规则集合

指针 是我们自己定义的操纵内存的接口

我现在的理解就是 **指针 = 地址 + 协议**

地址是指在内存中的位置, 协议是指如何管理指向的内存, 



#### 2.1 链表---来自数据结构

```c++
typedef struct Listnode{
    datatype data;
    struct Listnode *next;
}listnode;
```

为什么可以做到嵌套定义 : 

- Listnode 类型的变量可以有两个元素, 一个是数据域, 另一个是指针.这两个的大小和组织形式都是固定的, 例如, datatype为int时, 占据8个字节, 指针一般占据8个字节. 这就占据16个字节. 
- Listnode 指针的协议就可以这么来描述: 大小为16个字节, 类内元素排列是 int ( 8 )+ 指针 ( 8 )



#### 2.2 obj---来自SGIGCC2.9

```c++
  union obj {
        union obj * free_list_link;
        char client_data[1];    /* The client sees this.        */
  };
```

其实就是告诉指针, 这块内存中存储的是个地址, 并且占用8个字节的内存

```c++
struct listnode{
    listnode *next;
};
typedef struct listnode listnode;

int main() {
	// your code goes here
	listnode a,b;
	a.next = &b;
	cout<< "sizeof  listnode = "<< sizeof(listnode)<< endl;
	cout<< "the address of a ="<< &a<< "the address of b ="<< &b<< endl;
	cout<< "the a.next = "<< a.next <<endl;
	return 0;
}
/*
sizeof  listnode = 8
the address of a =0x7ffc8f28fcf8
the address of b =0x7ffc8f28fd00
the a.next = 0x7ffc8f28fd00
*/


```



#### 2.3 short和int---来自编程范式(视频)

```c++
int arr[5];
 
arr[3]= 128;
 
((short*)arr)[6]= 2;
//arr被重新解释成2bytes的short型，此时，之前赋值128的地方变为arr[7]

//因为short占用的字节小, 因此你可以通过short指针的方式来进行操控一部分内存
```

