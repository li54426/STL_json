class MyLinkedList {
    int size_{0};
    class Node{
        public:
        int val{0};
        Node *prev{nullptr};
        Node *next{nullptr};

        Node(int v):val(v){}
    };
    Node *dump{nullptr};
public:
    MyLinkedList() {
        dump = new Node(-10086);
        dump-> next = dump;
        dump-> prev = dump;


    }
    
    int get(int index) {
        // 所有节点下标从 0 开始
        if(index>= size_){
            return -1;
        }

        Node *cur = dump->next;
        for(int i = 0; i<index; ++i){
            cur = cur->next;
        }
        return cur->val;
    }
    
    void addAtHead(int val) {
        // 插入到链表中第一个元素之前
        Node *cur = new Node(val);
        Node *head = dump->next;
        cur-> next = dump->next;
        cur-> prev = dump;
        dump->next->prev = cur;
        dump-> next = cur;

        ++size_;


    }
    
    // val作为链表的最后一个元素
    void addAtTail(int val) {
        // 在尾部的dump 元素 以及dump 元素之前 插入一个元素.
        Node *tail = dump-> prev;
        Node *cur = new Node(val);
        cur -> next = dump;
        cur-> prev = tail;

        tail-> next = cur;
        dump-> prev = cur;

        ++size_;

    }
    
    // 插入到链表中下标为 index 的节点之前
    // 也就是成为 index
    // 如果 index 比长度更大，该节点将 不会插入 到链表中。
    void addAtIndex(int index, int val) {
        if(index == size_){
            addAtTail(val);
            return;
        }

        if(index == 0){
            addAtHead(val);
            return;
        }

        if(index > size_){
            return;
        }

        
        Node *pos = dump->next;
        for(int i =0; i< index; ++i){
            pos = pos->next;
        }
        Node *cur = new Node(val); 
        cur -> next = pos;
        cur-> prev = pos-> prev;

        pos->prev->next = cur;
        pos-> prev = cur;

        ++size_;

        // cout<< "insert the index "<< index << "\tthe val ="<<val<< endl;

    }
    
    // 如果下标有效，则删除链表中下标为 index 的节点。
    void deleteAtIndex(int index) {
        if(index >= size_){
            return;
        }
        
        Node *pos = dump->next;
        for(int i = 0; i<index; ++i){
            pos = pos->next;
        }

        pos->prev -> next = pos->next;
        pos->next -> prev = pos->prev;
        delete pos;
        --size_;

        // cout<< "delete the index "<< index<< endl;
    }
};

