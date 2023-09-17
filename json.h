#ifndef JSON__h
#define JSON__h



#include <iostream>
#include<string>
#include<vector>	//�洢����
#include<map>		//�洢����
#include<sstream>	//������
#include<fstream>	//�ļ�����




/* JSON Types: */
// 1<< n �� 1 ���� n ��λ��, �ճ�����λ��, �� 0 ���
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
#define JSON_Number (1 << 0)	//����
#define JSON_double (1 << 1)	//������
#define JSON_NULL   (1 << 2)    //NULL

#define JSON_String (1 << 3)	//�ַ���
#define JSON_bool (1 << 4)	//����
#define JSON_List (1 << 5)	//����
#define JSON_Object (1 << 6)	//����




class Json {
public:

    //��ʾ����������, ����, �ַ������� �б��л��߶���
    int type;


    // �����Զ���ֻ��һ������ֵ
	int int_val;
	double double_val;
	string string_val;
	bool bool_val;


	vector<Json>List;//��vector��ʾ����
	map<Json, Json>dict;//��map��ʾ����




	void del() {//�������ڲ��ĳ�Ա
		if (type == JSON_String)string_val.clear();
		if (type == JSON_List)List.clear();
		if (type == JSON_Object)dict.clear();
	}

	Json() {}
	~Json(){
		del();//����ʱ�ͷ��ڴ�
	}

	// ���๹�캯��
	Json(const int& x){
		del();//���͸ı�ǰ��Ҫ�ͷ�֮ǰ��
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

	// ��Ӻ����������ݷ���vector
	void add(Json x) {
		if (type == JSON_List)
			List.push_back(x);
	}
	
	 // �����ݷ���map{
	void put(Json key, Json val) 
		if (type == JSON_Object)
			dict[key] = val;
	}
	
	// ���������
	Json& operator [](Json i) {
		if (type == JSON_List)
			return List[i.int_val];
		else
			return dict[i];
	}
	
	// ת��ΪΪ �ַ���
	string str();
};


Json parser(string s){
	ss.clear();//�ͷ��ڴ�
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
