#include "./include/Hashtable.h"
#include <fstream>

int main(int argc, char *argv[]) {
    /*Hashtable h(10);
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
    cout<<endl;*/
    string current;
    ifstream input(argv[1]);
    ofstream out("output.txt");
    while (input >> current) {
        for (int i = 0; i < current.length(); i++)
            current[i] = tolower(current[i]);
        if (current[current.size() - 1] == '.' || current[current.size() - 1] == '!' || current[current.size() - 1] == '?' || (current[current.size() - 1] == '"' && current[current.size() - 2] == '.') || (current[current.size() - 1] == '"' && current[current.size() - 2] == '?') || (current[current.size() - 1] == '"' && current[current.size() - 2] == '!'))
        {
            if (current.size() > 1 && (current[current.size() - 2] == 'r' && current[current.size()-3] == 'm')) continue;
            if (current.size() > 2 && (current[current.size() - 2] == 's' && current[current.size()-3] == 'r' && current[current.size()-4] == 'm')) continue;
                    out << current <<' ';
        }
    }


    // Looking if next word is capital. The book doesn't always capitalize...
    /*while (input >> current) {
        if (isalpha(current[0]))
            upper = isupper(current[0]);
        else
        {
            int i = 1;
            while (i < current.length() && !isalpha(current[i]))
                i++;
            upper = isupper(current[1]);
        }
        for (int i = 0; i < current.length(); i++)
            current[i] = tolower(current[i]);
        if (last[last.size() - 1] == '.' || last[current.size() - 1] == '!' || last[last.size() - 1] == '?' || (last[last.size() - 1] == '"' && last[last.size() - 2] == '.') || (last[current.size() - 1] == '"' && last[current.size() - 2] == '?') || (last[last.size() - 1] == '"' && last[last.size() - 2] == '!'))
        {
            if (upper)
            {
                if (last.size() > 1 && (last[last.size() - 2] == 'r' && last[last.size()-3] == 'm')) continue;
                if (last.size() > 2 && (last[last.size() - 2] == 's' && last[last.size()-3] == 'r' && last[last.size()-4] == 'm')) continue;
                out << last << ' ';
            }
        }
        last = current;
    }*/
    return 0;
}