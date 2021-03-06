#include "./include/Hashtable.h"
#include <fstream>
#include <time.h>
#include <chrono>

/**
    I declare that all material in this assessment task is my work except where there is clear acknowledgement or reference to the work of others. 
    I further declare that I have complied and agreed to the CMU Academic Integrity Policy at the University website.
    http://www.coloradomesa.edu/student-services/documents
    Author’s Name: Drake Cullen 
    UID(700#): 700480375
    Date: 10/20/2021
*/

void readInput(string&, Hashtable &);
void showMenu(Hashtable &hashTable, string &inputFile, string &outputFile, bool &displayMenu);
void heapForTopOneFifty(Hashtable &, string &, bool);
void heapForAllWords(Hashtable &, string &, bool);
void calculateTimeOccupancy(string &, ofstream &, double, string[]);
void compareTimeOccupancy(string &, string &);
void getSentences(string&, string&);

int main(int argc, char *argv[]) {
    // 50% = 17286, 70% = 13776, 80% = 10803
    const int UNIQUE_WORDS = 8642;
    bool displayMenu = false;
    Hashtable hashTable(UNIQUE_WORDS / .5);
    string inputFile = argv[1], outputFile = argv[2], temp = "";
    readInput(inputFile, hashTable);

    if (argc > 3)
    {
        temp = argv[3];
        displayMenu = temp == "menu";
    }
    
    if (displayMenu)
    {
        while (displayMenu)
        {
            showMenu(hashTable, inputFile, outputFile, displayMenu);
        }
    } else {
        if (argc > 3)
            temp = argv[3];
        if (temp == "ascending")
            heapForAllWords(hashTable, outputFile, 0);
        else
            heapForAllWords(hashTable, outputFile, 1);
    }
    return 0;
}


/**
 * Read in word by word from the input file. 
 * Convert all words to lowercase and clean up data before adding to the hashtable.
 * @param string& -> The name of the input file.
 * @param Hashtable -> The hashtable that the words will be added to
 * O(n) Where n is the total number of characters in the file. For each word, every letter
 * is checked and if need, it is converted to lowercase.
 * Adding to the hashtable takes constant time.
 */
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
            else if (currentWord[i] == '-' && i + 1 < currentWord.length() && currentWord[i+1] != '-')
                cleanedWord += '-';
        }
        hashTable.addWord(cleanedWord);
    }
    input.close();
}

/**
 * Display the user with a menu.
 * Based on their choice, call the appropriate function.
 * Convert all words to lowercase and clean up data before adding to the hashtable.
 * @param Hashtable -> The hashtable that the words will be added to
 * @param string& -> The name of the input file.
 * @param string& -> The hashtable that the words will be added to
 * @param bool -> Determines when the user would like to quit the program.
 */
void showMenu(Hashtable &hashTable, string &inputFile, string &outputFile, bool &displayMenu)
{
    int userInput;
    string searchWord;

    cout<<"\n Choose an option by typing the associated number (all output is printed to the output file): \n 1) Find the number of occurences of a word. \n 2) Print the 150 least frequently occuring words. \n 3) Print the 150 most frequently occuring words. \n";
    cout<<" 4) All words in ascending order by frequency. \n 5) All words in descending order by frequency. \n 6) Print the number of sentences. \n 7) To test occupancy ratios affect on speed. \n 0) Terminates the program. \n > ";
    cin>>userInput;

    if (userInput == 0)
        displayMenu = false;
    else if (userInput == 1)
    {
        cout<<"Enter a word: ";
        cin>>searchWord;
        Word* result = hashTable.getWord(searchWord);
        if (result != nullptr)
        {
            cout<<"\""<<searchWord<<"\" appears "<<result->count<<" time(s)"<<endl;
        }
        else 
        {
            cout<<"\""<<searchWord<<"\" was not found in the word list \n";
        }
    }
    else if (userInput == 2)
        heapForTopOneFifty(hashTable, outputFile, 0);
    else if (userInput == 3)
        heapForTopOneFifty(hashTable, outputFile, 1);
    else if (userInput == 4)
        heapForAllWords(hashTable, outputFile, 0);
    else if (userInput == 5)
        heapForAllWords(hashTable, outputFile, 1);
    else if (userInput == 6)
        getSentences(inputFile, outputFile);
    else if (userInput == 7)
        compareTimeOccupancy(inputFile, outputFile);
}


/**
 * Create a heap to print out the top 150 most occurring words, or the 150 least occuring words.
 * @param Hashtable -> The hashtable with all of the words
 * @param string& -> The name of the output file.
 * @param bool -> A 0 is a min heap and a 1 is a max heap.
 * O(log(n)) We will always loop 150 times. Popping from a heap takes log(n).
 */
void heapForTopOneFifty(Hashtable &hashTable, string &outFile, bool heapType)
{
    ofstream out(outFile);
    Heap<Word> heap(hashTable.getTotalWordCount() / .5, heapType);
    hashTable.createHeap(heap);
    Word* w;
    for (int i = 0; i < 150 ; i++)
    {
        w = heap.pop();
        out<<w->data<<' '<<w->count<<endl;
    }
    out.close();
    cout<<"Check the output file for results. \n";
}

/**
 * Create a heap to print out every word in ascending or descending order based
 * on the number of times they appear in the input file.
 * @param Hashtable -> The hashtable with all of the words
 * @param string& -> The name of the output file.
 * @param bool -> A 0 is a min heap and a 1 is a max heap.
 * O(n*log(n)) We will have to loop through every word, giving us time n. For each word,
 * popping from a heap takes log(n). Thus we have n*log(n)
 */
void heapForAllWords(Hashtable &hashTable, string &outFile, bool heapType)
{
    ofstream out(outFile);
    Heap<Word> heap(hashTable.getTotalWordCount() / .5, heapType);
    hashTable.createHeap(heap);
    Word* w;
    for (int i = 0; i <= hashTable.getTotalWordCount() - 1 ; i++)
    {
        w = heap.pop();
        out<<w->data<<' '<<w->count<<endl;
    }
    out.close();
    cout<<"Check the output file for results. \n";
}


/**
 * This function prints out the total number of sentences.
 * To start, it looks for periods, question marks, and exclamation points. 
 * 
 * Next, it searches for quotation marks. If a quotation mark is at the end of a word,
 * the value before the quotation mark is read. I search for this because you make have a sentence 
 * such as: Mark said: "Hello."
 * 
 * If either of the cases above are true, we look at the next word. If the next word doesn't start with a 
 * capital letter, than we probably have an abbreviation like St.
 * 
 * Finally, don't add one to the counter if the word is part of the special cases such as Mr. and Mrs.
 * 
 * @param string* -> The name of the input file.
 * @param string* -> The name of the output file.
 * O(n) Where n is the number of words in the file.
 */
void getSentences(string& inputFile, string& outFile)
{
    string current, last;
    ifstream input(inputFile);
    ofstream out(outFile);
    int numOfSentences = 0;
    /*
    while (input >> current) {
        for (int i = 0; i < current.length(); i++)
            current[i] = tolower(current[i]);
        if (current[current.size() - 1] == '.' || current[current.size() - 1] == '!' || current[current.size() - 1] == '?' || (current[current.size() - 1] == '"' && current[current.size() - 2] == '.') || (current[current.size() - 1] == '"' && current[current.size() - 2] == '?') || (current[current.size() - 1] == '"' && current[current.size() - 2] == '!'))
        {
            if (current.size() > 1 && (current[current.size() - 2] == 'r' && current[current.size()-3] == 'm')) continue;
            if (current.size() > 2 && (current[current.size() - 2] == 's' && current[current.size()-3] == 'r' && current[current.size()-4] == 'm')) continue;
            numOfSentences++;
        }
    }
    out<<"There are a total of "<<numOfSentences<<" sentences.";
    input.close();
    out.close();
    cout<<"Check the output file for results. \n";*/

    bool upper;
    input >> last;
    while (input >> current) {
        upper = false;
        // If the first letter is capitalized
        if (isalpha(current[0]))
            upper = isupper(current[0]);
        // Maybe the word started with a symbol, so check the next letter(s) for a capital
        else
        {
            int i = 1;
            while (i < current.length() && !isalpha(current[i]))
                i++;
            if (i < current.length())
                upper = isupper(current[i]);
        }

        // Make all the letters lowercase
        for (int i = 0; i < current.length(); i++)
            current[i] = tolower(current[i]);
        
        // Check the previous word for puncutation
        if (last[last.length() - 1] == '.' || last[last.length() - 1] == '!' || last[last.length() - 1] == '?' 
            || (last.length() > 1 && last[last.length() - 1] == '"' && last[last.length() - 2] == '.') 
            || (last.length() > 1 && last[last.length() - 1] == '"' && last[last.length() - 2] == '?') 
            || (last.length() > 1 && last[last.length() - 1] == '"' && last[last.length() - 2] == '!'))
        {
            // If the previous word has punctuation and this word is uppercase
            if (upper)
            {
                if (last.length() > 1 && (last[last.length() - 2] == 'r' && last[last.length()-3] == 'm')) continue;
                if (last.length() > 2 && (last[last.length() - 2] == 's' && last[last.length()-3] == 'r' && last[last.length()-4] == 'm')) continue;
                numOfSentences++;
            }
        }
        last = current;
    }
    out<<"There are a total of "<<numOfSentences<<" sentences.";
    input.close();
    out.close();
    cout<<"Check the output file for results. \n";
}

/**
 * Create a hashtable for a given occupancyRatio. Test the retrieval speed of  7,650,000 lookups.
 * @param string& -> The name of the input file.
 * @param string& -> The name of the output file.
 * @param double -> The occupancy ratio
 * @param string[] -> Random words to test on
 * O(n) because each word must be looped through to create the hashTable.
 */
void calculateTimeOccupancy(string &inputFile, ofstream &out, double occupancyRatio, string randomWords[])
{
    const int UNIQUE_WORDS = 8642;
    Hashtable hashTable(UNIQUE_WORDS / occupancyRatio);
    readInput(inputFile, hashTable);
    clock_t startTicks = clock();
    auto startTime = chrono::steady_clock::now();
    for (int j = 0; j < 5000; j++)
    {
        for (int i = 0; i < 1530; i++)
            hashTable.getWord(randomWords[i]);
    }
    clock_t endTicks = clock();
    auto endTime = chrono::steady_clock::now();
    out<<"An occupancy rate of " << occupancyRatio<<" took "<< endTicks - startTicks << " clock ticks and " << double(chrono::duration_cast<chrono::microseconds>(endTime - startTime).count()) / 1000000 << " seconds for 7,650,000 lookups. \n";
    hashTable.calculateCollisions();
    out<<"There are "<<hashTable.getCollisionCount()<<" collisions.\n\n";
}


/**
 * Compare the number of clock ticks and time for hash tables 
 * with varying occupancy metrics.
 * @param string& -> The name of the input file.
 * @param string& -> The name of the output file.
 * O(n) because each word must be looped through to create the hashTable for each test.
 */
void compareTimeOccupancy(string &inputFile, string &outFile)
{
    ofstream out(outFile);
    chrono::duration<double> timeTaken;
    clock_t clockTicks;
    string randomWords[] = {"anywhere", "under", "sherlockholmes", "start", "jose", "league", "the", "of", "adventure", "i", "that", "perfect", "a", "things", "such", "doubt", "lenses", "but", "seen", "home-centred", "absorb", "lodgings", "drowsiness", "by", "and", "heard", "his", "had", "one", "now", "must", "powers", "in", "chest", "told", "upon", "formerly", "to", "across", "you", "thought", "tell", "how", "mary", "he", "leather", "round", "slavey", "nitrate", "member", "deduction", "simple", "lighting", "clear", "often", "not", "because", "good", "said", "to-night", "it", "begins", "deduce", "is", "e", "rather", "at", "precisely", "account", "german", "sound", "this", "may", "your", "immediately", "could", "bands", "was", "rich", "hat", "black", "thick", "note", "call", "cases", "matter", "go", "shoulders", "will", "exactly", "has", "reigning", "with", "as", "advise", "hereditary", "over", "person", "made", "up", "docketing", "which", "warsaw-yes", "wrote", "writing", "photograph", "yourself", "we", "attempts", "twice", "quite", "married", "she", "soul", "are", "would", "have", "money", "holmes", "news", "landlady", "two", "gave", "hand", "pleasure", "ceased", "amazing", "indeed", "heartily", "lie", "never", "unusual", "preposterous", "be", "view", "there", "dozen", "compelled", "man", "seldom", "him", "mr", "home", "campaign", "likely", "attention", "inquiry", "if", "remarkably", "great", "catch", "shouted", "road", "caught", "might", "twenty", "or", "half", "door", "three", "who", "godfrey", "then", "altar", "vouching", "me", "sally", "an", "separated", "answered", "still", "for", "meet", "formidable", "cap", "fire", "new", "part", "minutes", "being", "animated", "cigars", "marriage", "princess", "carries", "lawyer", "remember", "hands", "know", "show", "flushed", "lights", "cried", "hadnt", "felt", "conspiring", "blackest", "heart", "ill-gentlemen", "within", "corner", "away", "down", "nothing", "did", "do", "everyone", "fell", "open", "grabs", "rush", "attempt", "shown", "neither", "habits", "on", "toast", "wish", "silence", "her", "all", "my", "kind", "sherlock", "when", "wronged", "steps", "remain", "king", "am", "honour", "stretched", "threatened", "womans", "gentleman", "abruptly", "putting", "so", "doubting", "smaller", "dr", "course", "memory", "unique", "wrinkled", "forward", "obese", "front", "beside", "shook", "some", "manual", "right", "developed", "especially", "staining", "coin", "after", "planted", "sir", "does", "chair", "effect", "date", "earn", "ideas", "price", "photography", "cellar", "hes", "us", "thing", "its", "than", "glad", "what", "see", "peculiar", "apply", "hear", "old", "light", "wilson", "from", "orange", "were", "given", "coming", "experience", "pinch", "chairs", "fault", "anything", "water", "through", "below", "serious", "face", "another", "vincent", "knew", "suit", "day", "nor", "out", "pens", "say", "belief", "every", "like", "pretty", "end", "about", "into", "most", "pray", "any", "william", "ready", "address", "morris", "far", "knowledge", "no", "playing", "yes", "though", "earrings", "gesture", "italian", "listened", "looked", "stopped", "brightly", "keenly", "young", "daring", "before", "knees", "found", "traffic", "difficult", "standing", "here", "little", "while", "relentless", "itself", "mood", "suddenly", "other", "saturday", "put", "among", "only", "grotesque", "set", "agent", "our", "friend", "observed", "eton", "turn", "raising", "first", "endless", "fellow", "virtue", "anyone", "ended", "earth-smelling", "why", "stones", "work", "considerable", "present", "disadvantage", "conceal", "darkness", "vault", "heavier", "look", "line", "womanly", "very", "blood", "cab", "merryweather", "determined", "watson", "really", "house", "doing", "more", "bank", "concert", "days", "exclaimed", "ennui", "effort", "benefactor", "street", "hover", "outr", "bald", "result", "platitudes", "depend", "understand", "absolutely", "reading", "push", "connection", "story-teller", "bohemia", "asked", "without", "crimes", "motive", "communication", "longer", "love", "entered", "behind", "closed", "trying", "fear", "again", "father-took", "last", "since", "well", "tidy", "goodwill", "expected", "stock", "interest", "believe", "staying", "pays", "speak", "stole", "time", "folk", "safe", "used", "where", "leadenhall", "long", "against", "marrying", "just", "hotel", "eyes", "later", "happened", "mother", "oh", "let", "place", "way", "beads", "colour", "word", "missed", "trust", "similar", "surprise", "lower", "fully", "both", "deep", "amusing", "gaiters", "angel", "instituted", "friends", "fathom", "irene", "circumstances", "sufferer", "deserting", "reply", "stepfather", "come", "each", "mind", "hosmer", "handwriting", "case", "think", "waste", "lips", "bad", "between", "wrong", "utterly", "older", "advantages", "obvious", "covered", "france", "permanent", "happening", "ought", "client", "once", "gallows", "profited", "spectacles", "confirmed", "minor", "eliminated", "same", "much", "change", "makes", "either", "rummaged", "full", "paradoxical", "shall", "valley", "settle", "became", "lives", "kept", "pool", "alive", "crowder", "game-keeper", "mccarthy", "actually", "grass", "they", "son", "father", "following", "inflicted", "straight", "gentlemen", "clearly", "sunlight", "side", "investigation", "jury", "top", "highly", "even", "yard", "direction", "thinking", "seeing", "becoming", "instantly", "saw", "went", "give", "seat", "too", "severn", "rustic", "question", "probable", "plainer", "hardly", "natural", "hope", "back", "afraid", "disagreements", "always", "life", "passed", "broken", "miss", "lestrade", "james", "possible", "lestrades", "returned", "nice", "five", "maddening", "accounts", "barmaid", "written", "suffered", "those", "please", "morning", "hatherley", "sixty", "manner", "strange", "find", "demurely", "brighter", "weight", "showed", "sons", "points", "boscombe", "known", "glitter", "track", "marshy", "towards", "situated", "belt", "companion", "foot", "vanishes", "ran", "ha", "leaves", "lens", "stone", "lodge", "having", "carrying", "holding", "smokes", "these", "sceptic", "leg", "should", "paper", "method", "length", "lameness", "recorded", "cigarette", "tossed", "off", "human", "bowed", "combined", "official", "interests", "didnt", "blasted", "s", "lay", "close", "wicked", "wealthy", "market", "alice", "town", "boot", "land", "cunning", "whole", "talk", "mad", "girl", "struck", "fetch", "been", "solemnly", "live", "object", "probably", "future", "taken", "bars", "sea-stories", "rain", "mothers", "perhaps", "sit", "glare", "pince-nez", "court", "mysterious", "details", "feet", "plantation", "retiring", "brother", "draughts", "privacy", "trunks", "foreign", "jumped", "laugh", "k", "letter", "cashbox", "less", "society", "garden", "times", "winced", "uncle", "horsham", "label", "states", "colonel", "earth", "above", "pooh", "joke", "hill", "received", "twilight", "unable", "robbery", "january", "however", "dried", "done", "relations", "clenched", "suggestive", "drawing", "amid", "helps", "uncles", "notices", "th", "secret", "glow", "finger-tips", "bearings", "results", "bone", "state", "can", "reasoner", "precise", "unsystematic", "need", "climate", "east", "ship", "elapsed", "mission", "pondicherry", "seven", "carried", "individual", "fanciful", "notably", "sprig", "openly", "impunity", "south", "sort", "seen-", "c-that", "miserable", "foresee", "bell", "h", "recovered", "exhibited", "unfortunate", "landing-stages", "hurts", "bridge", "police", "clue", "took", "o", "sure", "sheet", "searched", "learned", "reaches", "best", "reached", "lip", "addicted", "attain", "drooping", "lap", "quick", "whitney", "came", "opium", "second", "send", "upper", "search", "lack-lustre", "stool", "stay", "june", "pipes-i", "narrow", "drug", "cry", "excellent", "practically", "enemies", "vengeance", "bodies", "neville", "shortly", "dashed", "broad", "party", "current", "seems", "definite", "rule", "popular", "offices", "office", "mrs", "packet", "followed", "clair", "seemed", "attempted", "assistant", "lane", "proprietor", "sign", "inspector", "examined", "bedroom", "least", "examination", "floor", "st", "bloodstains", "clairs", "powerful", "careful", "ring-finger", "dreaming", "tide", "lascar", "windows", "short", "trees", "rooms", "eagerness", "dear", "plain", "feelings", "point", "none", "pause", "yet", "octavo", "to-day", "respond", "monday", "placed", "large", "armchairs", "shag", "wake", "smoke", "certainly", "fools", "stout", "quiet", "concerned", "inquiries", "regular", "bag", "quietly", "hair", "wash", "seamed", "rubbing", "cake", "therefore", "help", "ay", "supply", "amateur", "scar", "plaster", "d", "filling", "entreated", "reopening", "seized", "few", "moment", "further", "vii", "christmas", "purple", "near", "seedy", "lying", "frost", "humanity", "remarked", "peterson", "mans", "window", "also", "surely", "baker", "bakers", "continue", "methods", "timid", "picked", "although", "moral", "leads", "laid", "forehead", "years", "quality", "expensive", "world", "sold", "observe", "positive", "brought", "candle", "save", "eh", "wife", "scintillating", "sentimental", "recover", "nd", "evidence", "gem", "forced", "countess", "assizes", "advertisement", "eye", "introduction", "gone", "red", "suicide", "strong", "crop", "fanlight", "brown", "fashion", "naturally", "strode", "outside", "bloomsbury", "ruddy-faced", "follow", "endell", "name", "questioning", "ah", "couple", "provoked", "akimbo", "trifle", "fiver", "bred", "hanging", "finish", "list", "daresay", "yellow", "knots", "passing", "cosmopolitan", "wonder", "blue", "clutched", "voice", "break", "bible", "policeman", "pale", "safety", "carry", "fluttered", "youd", "aside", "kill", "opened", "jem", "thief", "burst", "heavy", "rose", "problem", "band", "studied", "terrible", "knock", "retorted", "lady", "sitting-room", "deductions", "associate", "shiver", "pitiable", "violent", "left", "recall", "whatever", "fancies", "averted", "oldest", "gambler", "obtained", 
                            "caused", "escaped", "morose", "major-general", "establish", "moran", "obstacle", "exchanging", "quarrels", "terror", "hospitality", "animals", "baboon", "mine", "honoria", "fortnight", "seared", "inhabited", "buildings", "room", "sleep", "from-perhaps", "proceed", "splashing", "terrified", "sister", "finger", "words", "medical", "consciousness", "secured", "shock", "handkerchiefs", "ever", "leatherhead", "housekeeper", "chimney", "combine", "clang", "whether", "breadth", "deep-set", "prey", "saying", "imperturbably", "bent", "snarled", "detective", "suffer", "aware", "drive", "quest", "pulled", "started", "paid", "business", "turned", "returns", "curving", "portion", "erected", "centre", "seem", "bar", "masonry", "small", "chamber", "fireplace", "examining", "panelled", "several", "ventilators", "wooden", "slowly", "big", "lash", "make", "village", "spend", "sleeve", "prefer", "enough", "palmer", "goodness", "middle", "lawn", "darted", "broke", "moved", "fatal", "pistol", "matches", "nervous", "absolute", "catlike", "momentary", "gentle", "jet", "sudden", "yell", "roylotts", "headgear", "seconds", "dog-whip", "horrid", "bell-rope", "coupled", "discovered", "use", "sooner", "weigh", "submitted", "narratives", "step", "practice", "men", "railway", "dooties", "sorry", "night", "doctor", "victoria", "caraffe", "considerably", "surgeon", "brandy", "rushed", "agony", "stop", "pounds", "until", "size", "outstanding", "bright", "excuse", "essential-absolute", "beg", "opinion", "suppose", "paying", "bought", "comparatively", "deposit", "engineers", "bricks", "cold", "interesting", "lurched", "smoothness", "woman", "dark", "lamp", "wonderfully", "living", "possibly", "humming", "fee", "affair", "slink", "cared", "together", "piston", "regurgitation", "fullers-earth", "clank", "levers", "so-precious", "myself", "dull", "fall", "understood", "sickness", "tie", "recalled", "hour", "wait", "bring", "sat", "shelf", "inst", "train", "scotland", "circle", "notice", "boxed", "lucky", "ostrich", "met", "whereabouts", "machinery", "gained", "noble", "episode", "autumnal", "surrounded", "letters", "variety", "summonses", "quill", "mantelpiece", "born", "late", "descent", "aloysius", "invaders", "definitely", "figure", "reported", "honeymoon", "warn", "headed", "consternation", "announced", "lancaster", "absence", "doran", "bridegroom", "own", "high", "lord", "draw", "already", "invested", "wifes", "london", "fair", "accustomed", "arm", "ulster", "company", "dorans", "flora", "seek", "fortunate", "head", "year", "pea-jacket", "simon", "square", "pile", "bitterness", "pocket", "slapped", "their", "satisfaction", "contrary", "good-day", "garments", "arrived", "pt", "features", "surprised", "stairs", "confess", "cannot", "moulton", "frock-coat", "pleading", "wiry", "pa", "service", "scribble", "pew", "get", "run", "slipped", "ladies", "talking", "sweeping", "prevent", "quartering", "allowed", "prior", "sherry", "particular", "evenings", "dressing-gown", "ploughed", "foot-paths", "fifty", "sombre", "chatted", "ears", "pass", "depends", "number", "plate", "trifling", "ones", "founded", "refrain", "match", "alone", "locked", "disappointment", "charming", "brilliant", "story", "cupboard", "cast", "generous", "else", "farthing", "someone", "wide", "listening", "next", "arthur", "stolen", "missing", "anger", "got", "affected", "consider", "risk", "danger", "banker", "task", "residence", "entrance", "stretching", "led", "path", "knows", "hushing", "truth", "maid", "remarks", "impatiently", "holder", "brings", "thin", "hard", "taking", "edge", "perplexity", "trousers", "entirely", "gems", "imagine", "dressed", "boots", "glass", "soon", "complain", "hot", "ring", "dishonoured", "troubles", "thousand", "pen", "walked", "hugged", "sternly", "understanding", "admitted", "desperate", "coronet", "wooden-legged", "slept", "soft", "along", "action", "something", "ascended", "explain", "scene", "preserve", "snow", "struggle", "hurt", "framework", "beginning", "retain", "six", "hundred", "england", "important", "charge", "cinder", "cause", "selfishness", "justice", "rare", "spring", "metal", "pshaw", "tooth", "criminal", "touched", "yours", "spence", "wits",
                            "westaways", "chin", "better", "nutshell", "lovely", "killing", "take","madam", "page", "inquire", "shade", "philadelphia", "duties", "refuse", "keep", "accepted", "turning", "threw", "studies", "to-morrow", "postpone", "oclock", "began", "clouds", "around", "fogs", "them", "vilest", "wickedness", "appeals", "cathedral", "repute", "easy", "dog-cart", "southampton", "rucastle", "lost", "amusement", "appearance", "arrival", "handkerchief", "blind", "relation", "beeches", "conscious", "employer", "almost", "huge", "sentinel", "tresses", "drawer", "suite", "grounds", "instinct", "downstairs", "cord", "waiting", "caressing", "frightened", "curiosity", "lest", "evening", "creature", "gravity", "ask", "matters", "wore", "afterwards", "merely", "public-house", "tried", "basketful", "hunter", "whose", "wheres", "tall", "rights", "worn", "metallic", "free-handed", "mauritius", "ebook", "various", "replace", "trademark", "receive", "works", "terms", "possession", "registered", "agree", "agreement", "literary", "claim", "copying", "copied", "providing", "project", "posted", "unlink", "form", "copy", "paragraph", "gutenberg-tm", "forth", "damages", "disclaim", "indirect", "medium", "merchantibility", "provisions", "distribution", "foundation", "archive", "tax", "permitted", "fairbanks", "north", "information", "b", "widest", "status", "many", "httppglaforg", "international", "united", "originator", "thirty", "copyright"};
    out<<"The following hash tables are created with variable occupancy rates. They are than used to look up 1,530 random words 5,000 times. \nTherefore, there are a total of 7,650,000 lookups. The number of clock ticks and time in seconds are reported. \n\n";

    calculateTimeOccupancy(inputFile, out, .5, randomWords);
    calculateTimeOccupancy(inputFile, out, .7, randomWords);
    calculateTimeOccupancy(inputFile, out, .8, randomWords);

    out.close();
    cout<<"Check the output file for results. \n";
}
