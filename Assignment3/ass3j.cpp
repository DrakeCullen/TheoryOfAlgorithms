#include "./include/Hashtable.h"
#include <fstream>


void readInput(string&, Hashtable &);
void getSentences(string);

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

    const int UNIQUE_WORDS = 8643;
    // 50% = 17286, 70% = 13776, 80% = 10803

    Hashtable hashTable(UNIQUE_WORDS / .5);
    string inputFile = argv[1], outputFile = argv[2];
    ofstream out(outputFile);
    readInput(inputFile, hashTable);
    Heap<Word> heMax(UNIQUE_WORDS / .5,0);
    hashTable.createHeap(heMax);
    Word* w;
    cout<<hashTable.getTotalWordCount()<<' '<<hashTable.getCollisionCount();
    for (int i = 0; i < 150; i++)
    {
        w = heMax.pop();
        out<<w->data<<' '<<w->count<<endl;
    }
    
    return 0;
}

void readInput(string &inputFile, Hashtable &hashTable)
{
    string currentWord, cleanedWord;
    ifstream input(inputFile);
    while (input >> currentWord)
    {
        cleanedWord = "";
        for (int i = 0; i < currentWord.length(); i++)
        {
            if (isalpha(currentWord[i]))
                cleanedWord += tolower(currentWord[i]);
            else if (currentWord[i] == '-')
                cleanedWord += '-';
        }
        hashTable.addWord(cleanedWord);
    }
    input.close();
}

void getSentences(string file)
{
    string current;
    ifstream input(file);
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
    input.close();


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
}