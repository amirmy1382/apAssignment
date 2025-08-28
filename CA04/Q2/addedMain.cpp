
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    LinkedList<string> LL;
    Stack<int> ST;
    Queue<string> QQ;

    string cmd;
    while (cin >> cmd){
        if(cmd=="LL_PUSH_FRONT"){ string s; cin>>s; LL.push_front(s); }
        else if(cmd=="LL_PUSH_BACK"){ string s; cin>>s; LL.push_back(s); }
        else if(cmd=="LL_POP_FRONT"){ LL.pop_front(); }
        else if(cmd=="LL_POP_BACK"){ LL.pop_back(); }
        else if(cmd=="LL_PRINT"){ LL.print(); }
        else if(cmd=="LL_SIZE"){ cout << LL.size() << "\n"; }
        else if(cmd=="LL_CONTAINS"){ string s; cin>>s; cout << (LL.contains(s) ? "Yes" : "No") << "\n"; }
        else if(cmd=="LL_REMOVE"){ string s; cin>>s; cout << (LL.remove(s) ? "Removed" : "NotFound") << "\n"; }
        else if(cmd=="LL_CLEAR"){ LL.clear(); }

        else if(cmd=="STACK_PUSH"){ int x; cin>>x; ST.push(x); }
        else if(cmd=="STACK_POP"){ ST.pop(); }
        else if(cmd=="STACK_TOP"){ cout << ST.top() << "\n"; }
        else if(cmd=="STACK_PRINT"){ ST.print(); }

        else if(cmd=="QUEUE_ENQ"){ string s; cin>>s; QQ.enqueue(s); }
        else if(cmd=="QUEUE_DEQ"){ QQ.dequeue(); }
        else if(cmd=="QUEUE_FRONT"){ cout << QQ.front() << "\n"; }
        else if(cmd=="QUEUE_PRINT"){ QQ.print(); }
    }
    return 0;
}
