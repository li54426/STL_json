namespace mylib{

/*
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
*/


// 流类，将字符串转换为数字、将数字转换为字符串等
// peek() 返回当前下标所指向的字符
// get() 返回当前下标所指向的字符, 并令**下标加1**，返回值为 -1 说明遍历完了
stringstream ss;


// 进行任务派发
Json parser_val(){
	while (ss.peek() != -1){
		// 开头一定是这几类中的一类 
		if (ss.peek() == ' ' || ss.peek() == '\n' || ss.peek() == '\t')
			ss.get();
		else if (ss.peek() == '"')//字符串{
			return parser_str();
		}
		else if (ss.peek() == 'f' || ss.peek() == 't'){
			return parser_bool();
		}
		else if (ss.peek() == '['){
			return  parser_arr();
		}
		else if (ss.peek() == '{'){
			return parser_object();
		}
		else{
			return parser_num();//数字
		}
	}
	return 0;
}

// 最重要的一个函数, 注意他的逻辑
// 如何处理 : , { }
// 解析json对象
Json parser_object(){
	// 去掉 {
	ss.get();
	Json dict;
	dict.type = JSON_Object;
	while (ss.peek() != '}') {
		Json key = parser_val();
		while (ss.peek() == ' ' || ss.peek() == ':') //键与值的分割
			ss.get();
		Json val = parser_val();
		dict.put(key, val);
		while (ss.peek() != '}' && (ss.peek() == ' ' || ss.peek() == '\t' || ss.peek() == '\n' || ss.peek() == ','))
			ss.get();//切换到下一个对象
	}
	ss.get();
	return dict;
}


// 解析数组
Json parser_arr(){
	ss.get();
	Json vec;
	vec.type = JSON_List;
	while (ss.peek() != ']'){
		vec.add(parser_val());//不确定每个数组元素的类型
		while (ss.peek() != ']' && (ss.peek() == ' ' || ss.peek() == '\t' || ss.peek() == '\n' || ss.peek() == ','))
			ss.get();//切换到下一个元素
	}
	ss.get();
	return vec;
}

Json parser_num()//解析数字{
	string s;
	//isdigit 判断一个字符是否为数字
	while (isdigit(ss.peek()) || ss.peek() == 'e' || ss.peek() == '-' || ss.peek() == '+')//判断数字
		s.push_back(ss.get());//std::string::pushi_back()
	if (count(s.begin(), s.end(), '.') || count(s.begin(), s.end(), 'e'))//是否是浮点数{
		return stof(s);//string转float
	}
	else{
		return stoi(s);//string转JSON_Number
	}
}

// 解析字符串
Json parser_str(){
	ss.get();
	// 首先申请16 byte 的空间
	string s(16, ' ');
	s.clear();
	while (ss.peek() != '"')
		s.push_back(ss.get());
	ss.get();//去掉引号
	return Json(s);
}

Json parser_bool()//解析布尔{
	if (ss.peek() == 'f'){
	    for(int i = 0; i< 5; i++){
            // 去除五个字符
            ss.get();
	    }

		return Json(false);
	}
	else{
        for(int i = 0; i< 4; i++){
            // 去除4个字符
            ss.get();
	    }
		return Json(true);
	}
}







// ###############输出部分###############
// 重载运算符，方便输出
ostream& operator << (ostream& out, const Json& v)
{
	if (v.type == JSON_Number)
		out << v.int_val;
	if (v.type == JSON_double)
		out << v.double_val;
	if (v.type == JSON_String)
		out << "\"" << v.string_val << "\"";
	if (v.type == JSON_bool)
	{
		if (v.bool_val)
			out << "true";
		else
			out << "false";
	}
	if (v.type == JSON_List) //重载输出，格式要尽可能符合JSON的语法
	{
		out << "[";
		for (JSON_Number i = 0; i < v.List.size(); i++)
		{
			if (i)//第一个元素前面不用逗号
				out << ",";
			out << v.List[i];
		}
		out << "]";
	}
	if (v.type == JSON_Object)
	{
		out << "{";
		for (auto it = v.dict.begin(); it != v.dict.end(); it++)
		{
			if (it != v.dict.begin())//第一个元素前面不用逗号
				out << ",";
			out << it->first << ":" << it->second;//map以first和second表示键值对
		}
		out << "}";
	}
	return out;
}

string Json::str(){
	stringstream ss;
	ss << (*this);//使用重载过后的<<
	return ss.str();
}

// 重载 < 运算符，C++里的vector和map都已经重载了小于号
bool operator < (const Json& a, const Json& b)  {
	if (a.type != b.type)
		return a.type < b.type;
	else{
		if (a.type == JSON_Number)
			return a.int_val < b.int_val;
		if (a.type == JSON_double)
			return a.double_val < b.double_val;
		if (a.type == JSON_String)
			return a.string_val < b.string_val;
		if (a.type == JSON_List)
			return a.List < b.List;
		if (a.type == JSON_Object)
			return a.dict < b.dict;
		return true;
	}
}

}// end name space