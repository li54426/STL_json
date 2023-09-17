class LFUCache {
private:
    int cap;
    int minf;
    //typedef pair<int, int> intpair;
    unordered_map<int, int> kv, kf;
    typedef list<int> intlist;

    
    template <class T>
    class findlist{
        // 有查找功能的链表
        // 开头是时间最久的
    private:
        // 注意 使用typename来表示这是一个类型
        typedef typename list<T>::iterator iterator;
        // 主要成员: 一个list 以及一个哈希表 key-> iterator 
        intlist l;
        unordered_map<T, typename list<int>::iterator> mp;
    public:
        void push(T key){
            // 头部是最久没用的
            l.push_back(key);
            iterator ite = l.end();
            ite--;
            // cout<< "push"<< *ite<< endl;
            mp[key] = ite;
        }
        void erase(int key){
            iterator it = mp[key];
            // 删除列表中的元素
            l.erase(it);
            mp.erase(key);
        }
        int deletelast(){
            T a = l.front();
            //cout<< "deletelast = "<< a<< endl;
            l.pop_front();
            return a;
        }
        int size(){
            return l.size();
        }
    };

    // 频率相同的 key 的list
    typedef findlist<int> intfindlist;
    unordered_map<int, intfindlist> fklist;

 
public:
    LFUCache(int capacity) {
        cap = capacity;
        minf = 0;
    }

    void addf(int key){
        // 将原来的intlist删除, 并且重新插入一个新的list中

        int f= kf[key];
        intfindlist &l = fklist[f];
        l.erase(key);

        intfindlist &a = fklist[f+1];
        a.push(key);
        
        // 更新 minf, 当改变的正好是 minf 并且对应list 中的没有元素时, minf++
        // 
        if(!l.size() && f == minf){
            minf++;
        }
        
        kf[key]++;

    }

    int deleteminf(){
        intfindlist &l = fklist[ minf];
        return l.deletelast();
    }
    
    int get(int key) {
        // 查找 O(1)只有哈希表
        // put o(1)-> 有序的表
        if(!kv.count(key)){
            return -1;
        }
        else{
            // fre++
            addf(key);
            return kv[key];
        }

    }
    
    void put(int key, int value) {
        if(0 == cap) return;
        if(!kv.count(key)){
            //不存在
            if(kv.size() >= cap){
                // 删除并插入
                // cout<< "the cap is full"<<endl;
                // cout<< "size = "<< kv.size()<< endl;
                // cout<< "key="<< key<< endl;
                int delkey = deleteminf();
                kv.erase(delkey);
                kf.erase(delkey);

                minf = 1;
                kv[key] = value;
                kf[key] = 1;
                intfindlist &l= fklist[1];
                l.push(key);

            }
            else{
                // 直接插入
                //cout<< "insert"<< endl;
                minf =1;
                kv[key] = value;
                kf[key] = 1;
                intfindlist &l= fklist[1];
                l.push(key);
            }
        }
        else{
            // 存在
            addf(key);
            kv[key] = value;
        }
    }
};
