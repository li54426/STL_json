#ifndef JSON__h
#define JSON__h



#include <iostream>
#include<string>
#include<vector>	//存储数组
#include<map>		//存储对象
#include<sstream>	//流对象
#include<fstream>	//文件操作




/* JSON Types: */
// 1<< n 是 1 左移 n 个位置, 空出来的位置, 用 0 填充
// #define JSON_Invalid (0)
// #define JSON_False  (1 << 0)
// #define JSON_True   (1 << 1)
// #define JSON_NULL   (1 << 2)
// #define JSON_Number (1 << 3)

// #define JSON_String (1 << 4)
// #define JSON_Array  (1 << 5)
// #define JSON_Object (1 << 6)

// #define JSON_Raw    (1 << 7) /* raw json */

namespace mylib{


using namespace std;
#define JSON_Number (1 << 0)	//整形
#define JSON_double (1 << 1)	//浮点型
#define JSON_NULL   (1 << 2)    //NULL

#define JSON_String (1 << 3)	//字符串
#define JSON_bool (1 << 4)	//布尔
#define JSON_List (1 << 5)	//数组
#define JSON_Object (1 << 6)	//对象




class Json {
public:

    //表示解析的类型, 数字, 字符串还是 列表有或者对象
    int type;


    // 以下以而行只有一个会有值
	int int_val;
	double double_val;
	string string_val;
	bool bool_val;


	vector<Json>List;//用vector表示数组
	map<Json, Json>dict;//用map表示对象




	void del() {//析构掉内部的成员
		if (type == JSON_String)string_val.clear();
		if (type == JSON_List)List.clear();
		if (type == JSON_Object)dict.clear();
	}

	Json() {}
	~Json(){
		del();//析构时释放内存
	}

	// 各类构造函数
	Json(const int& x){
		del();//类型改变前需要释放之前的
		int_val = x;
		type = JSON_Number;//0
	}
	Json(const double& x) {
		del();
		double_val = x;
		type = JSON_double;
	}

	Json(const string& x) {
		del();
		string_val = x;
		type = JSON_String;
	}
	Json(const char* x) {
		del();
		type = JSON_String;
		string_val = string(x);
	}

	Json(const bool& x) {
		del();
		bool_val = x;
		type = JSON_bool;
	}

	// 添加函数，将内容放入vector
	void add(Json x) {
		if (type == JSON_List)
			List.push_back(x);
	}
	
	 // 将内容放入map{
	void put(Json key, Json val) 
		if (type == JSON_Object)
			dict[key] = val;
	}
	
	// 重载运算符
	Json& operator [](Json i) {
		if (type == JSON_List)
			return List[i.int_val];
		else
			return dict[i];
	}
	
	// 转化为为 字符串
	string str();
};


Json parser(string s){
	ss.clear();//释放内存
	ss << s;
	return parser_val();

}





Json parser_val();
Json parser_num();
Json parser_str();
Json parser_bool();
Json parser_arr();
Json parser_object();







}// end namespace





#endif
