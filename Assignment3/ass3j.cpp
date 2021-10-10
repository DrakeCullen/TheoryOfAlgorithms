#include "./include/Hashtable.h"
#include "./include/Heap.h"
#include "./src/Heap.cpp"


int main(int argc, char *argv[]) {
    Hashtable h(10);
    string hi = "hi";
    h.addWord(hi);
    string bi = "bi";
    h.addWord(bi);
    string bye = "bye";
    h.addWord(bye);
    cout<<h.getTotalWordCount()<<endl;
    cout<<h.getCollisionCount()<<endl;
    h.addWord(bi);
    cout<<h.getTotalWordCount()<<endl;
    cout<<h.getCollisionCount()<<endl;
    Word* t = h.getWord(hi);
    cout<<t->data<<' '<<t->count;

    Heap<Word> he(10);
    return 0;
}