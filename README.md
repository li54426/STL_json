







### LRU 和 LFU

#### LRU



#### LFU

![image-20221224113921988](https://i0.hdslb.com/bfs/album/958d44c8c8d937085a3a68f2c9a0120521b164dc.png)

以下是LFU的存储结构:

- minf: 用来记录最小的频率
- cap: 用来表示容量
- hashmap<int, int> kv: key-> value
- hashmap<int, int> kf: key-> frequency
- hashmap<int, intfindlist>: frequency-> keys( 一个具有查找功能的list )



intfindlist: 通过映射来查找

- hashmap<int, iterator> mp: key-> iterator
- list







### JSON

#### 1.1 值(value)类型

- **字符串：**必须用双引号括起来
- **数 值：**十进制整数或浮点数
- **对 象：**键 / 值对的集合
- **数 组：**值的集合
- **布尔值：**true 或 false
- **null**





#### 1.2 json 的键必须是 string 类型么

在 JSON（JavaScript Object Notation）中，键（key）可以是任何有效的 JSON 值，包括字符串、数字、对象、数组等。

因此，JSON 的键并不必须是字符串类型。实际上，在实际应用中，我们通常使用字符串类型作为键，因为它们易于人类阅读和理解，并且与 JavaScript 中的对象属性一致。

但是，如果您需要使用非字符串类型的键，那么您需要在解析和序列化 JSON 数据时进行适当的处理，以确保键能够正确地解析和存储。

总之，JSON 中的键可以是任何有效的 JSON 值，但在实际应用中，我们通常使用字符串类型作为键。





#### JSON解析过程

-  每次遇到一个 {} [] 都会加一层

```json
{
   "person":
	{
   		"name": "peter",
   		"age": 20, 
   		"fruits": "apple",
   		"color": "RED",
   		"hobby": [666 , "EAT" , "dadooudou" , "睡觉"]
	}
 }
```





实例解析

- 首先遇到 `{`, 这是一个json对象, 有层次性,
- 继续解析, `"person"`是一个字符串, 返回一个 json对象
- 
