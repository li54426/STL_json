class LRUCache {
public:
    // list中需要有两个值, 一个key, 一个val, 需要使用 pair 打包起来
    list< pair<int,int> > l;
    // map int-> 地址, 所以第二个元素是 iterator
    unordered_map<int, list<pair<int,int>>::iterator > mp;
    int size;

    LRUCache(int capacity) {
        // init
        size = capacity;
    }
    
    int get(int key) {
        // return value and **updata**
        // only hash is O(1)
        // 表示时间 要用 表
        if(!mp.count(key)){
            return -1;
        }
        else{
            // exist
            auto it = mp[key];
            l.splice(l.begin(), l, it);
            return mp[key]-> second;
        }

    }
    
    void put(int key, int value) {
        // change and 
        if(!mp.count(key) ){
            // dont exist
            // insert = not full
            if(mp.size()< size){
                l.push_front({key, value});
                mp[key] = l.begin();
            }

            else{
                // sort  = full
                // find the last and delete
                auto it = l.end();
                it--;
                int de= it-> first;
				
                // change list
                it ->first = key;
                it ->second = value;
				
                //change mp
                mp.erase(de);
                mp[key] = it;
                // sort
                l.splice(l.begin(), l, it);
            }
            
        }


        else{
            // exist and sort
            auto it = mp[key];
            it->second = value;
            l.splice(l.begin(), l, it);

        }
        // cout<< "mp.size = "<< mp.size()<< endl;
        // cout<< "l.size="<< l.size()<< endl;
    }
};