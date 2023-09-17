#inlcude<iostream>




int main()
{
	ifstream fin("test.txt");
	stringstream ss; 
	ss << fin.rdbuf();
	Json x = parser(ss.str());
 
	cout << "test 1.1------------------------------" << endl;
	cout << x << endl;
 
	cout << "\n\ntest 1.2------------------------------" << endl;
	cout << x["person"] << endl;
 
	cout << "\n\ntest 1.3------------------------------" << endl;
	cout << x["person"]["name"] << endl;
	cout << x["person"]["age"] << endl;
	cout << x["person"]["hobby"][0] << endl;
	cout << x["person"]["hobby"][1] << endl;
	cout << x["person"]["hobby"][2] << endl;
	cout << x["person"]["hobby"][3] << endl;
	
 
	//修改内容
	Json y = parser(x.str());
	y["person"]["name"] = "july";
	y["person"]["age"] = 28;
	y["person"]["hobby"][0] = "6.78";
	y["person"]["hobby"][1] = "play GAMES";
	y["person"]["hobby"][2] = "sing and dance";
	x = parser(y.str());
	
	cout << "\n\ntest 2.1------------------------------" << endl;
	cout << x << endl;
 
	cout << "\n\ntest 2.2------------------------------" << endl;
	cout << x["person"]["name"] << endl;
	cout << x["person"]["age"] << endl;
	cout << x["person"]["hobby"][0] << endl;
	cout << x["person"]["hobby"][1] << endl;
	cout << x["person"]["hobby"][2] << endl;
	cout << x["person"]["hobby"][3] << endl;
 
	return 0;
}
