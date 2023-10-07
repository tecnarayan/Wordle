#include<bits/stdc++.h>

using namespace std;

vector<string> global_memory;
string char_present;
string char_not_present = "";
int count_ = 0;


bool isCharNotPresent(char targetChar, const std::string& word) {
    for (char ch : word) {
        if (ch == targetChar) {
            return false; // Character found in the word, return false
        }
    }
    return true; // Character not found in the word, return true
}


std::string removeCharacter(const std::string& word, char characterToRemove) {
    std::string result = "";
    bool b = false;

    for (char ch : word) {
        if(b){
            result += ch;
            continue;
        }
        if (ch != characterToRemove) {
            result += ch;
            b = true;
        }
    }

    return result;
}


bool areAllCharactersDifferent(const std::string& word) {
    // Create an array to keep track of characters encountered
    bool encountered[256] = {false}; // Assuming ASCII characters

    for (char ch : word) {
        // Check if the character has been encountered before
        if (encountered[static_cast<unsigned char>(ch)]) {
            return false; // Character is not unique
        }

        // Mark the character as encountered
        encountered[static_cast<unsigned char>(ch)] = true;
    }

    return true; // All characters are unique
}


string max_probable(string done){
    
    vector<string> load;
    
    std::vector<std::unordered_map<char, int>> number(5);

    for (int i = 0; i < 5; i++) {
        for (char ch = 'a'; ch <= 'z'; ch++) {
            number[i][ch] = 0;
            if(! isCharNotPresent(ch , "ETAOIN")) number[i][ch] = 10;
        }
    }

    ifstream inputFile("wordlist2.csv");
    string word;
    while(getline(inputFile , word)){
        for(int i = 0 ; i < 5 ; i++){
            if(done[i] != '_'){
                if(done[i] != word[i]) break;
            }
            if(done[i] == '_'){
                bool broken = false;
                for(int ii = 0 ; ii < count_ ; ii++){
                    string word_vec = global_memory[ii];
                    if(word[i] == word_vec[i]){
                        broken = true;
                        break;
                    }
                }
                if(broken) break;
            }
            if( i == 4){
                bool broken = false;
                string dumb = word;
                for(int z = 0 ; z < char_present.length() ; z++){
                    if(isCharNotPresent(char_present[z],dumb)){
                        broken = true;
                        break;
                    }
                    dumb = removeCharacter(dumb , char_present[z]);
                }
                if(broken) break;

                broken = false;
                for(int z = 0 ; z < char_not_present.length() ; z++){
                    if(! isCharNotPresent(char_not_present[z],word)){
                        broken = true;
                        break;
                    }
                }
                if(broken) break;

                load.push_back(word);
                for(int j = 0 ; j < 5 ; j++){
                    number[j][word[j]] += 1;
                }
            }
        }
        
    }

    int max_score = 0;
    string p = "";
    vector<string> curr;
    for(auto i : load){
        int score = 0;
        for(int j = 0 ; j < 5 ; j++){
            score += number[j][i[j]];
        }
        if(areAllCharactersDifferent(i))score += 50;
        if(score == max_score){
            curr.push_back(i);
        }
        if(score > max_score){
            max_score = score;
            p = i;
            curr.assign({});
            curr.push_back(i);
        }
    }

    std::random_device rd;
    std::mt19937 gen(rd()); // Mersenne Twister engine

    // Generate random integers in a specific range
    std::uniform_int_distribution<int> intDistribution(1, curr.size()); // Generate integers between 1 and 100
    int randomInt = intDistribution(gen);

    return curr[randomInt-1];

}

int main() {

    string s = "stone";
    global_memory.push_back(s);
    count_ +=1;
    cout<<s<<endl;

    for(int i = 0 ; i < 5 ; i++){
        cout<<"STRING MATCHED :: ";
        cin>>s;
        cout<<"CHAR MATCHED :: ";  // ENTER "$" IF NONE HAS MATCHED
        cin>>char_present;
        if(char_present == "$")char_present = "";
        cout<<"CHAR DID'T MATCHED :: ";
        string tt;
        cin>>tt;
        char_not_present += tt;
        cout<<endl;
        s = max_probable(s);
        cout<<s<<endl;
        global_memory.push_back(s);
        count_ +=1;
    }

}