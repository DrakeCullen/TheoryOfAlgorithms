#include "./include/Hashtable.h"

int main(int argc, char *argv[]) {
    Hashtable h(10);
    string hi = "hi";
    h.addWord(hi);
    h.addWord(hi);
    string bi = "bi";
    h.addWord(bi);
    h.addWord(bi);
    h.addWord(bi);
    string bye = "bye";
    h.addWord(bye);
    cout<<h.getTotalWordCount()<<endl;
    cout<<h.getCollisionCount()<<endl;
    h.addWord(bi);
    cout<<h.getTotalWordCount()<<endl;
    cout<<h.getCollisionCount()<<endl;
    Word* t = h.getWord(hi);

    Heap<Word> he(10, 0);
    h.createHeap(he);
    while (he.getSize() > 0)
        cout<<he.pop()->data<<endl;
    cout<<endl;
    Heap<Word> heMax(10, 1);
    h.createHeap(heMax);
    while (heMax.getSize() > 0)
        cout<<heMax.pop()->data<<endl;
    cout<<endl;
    return 0;
}