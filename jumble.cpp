#include <sstream>
#include <fstream>
#include <string>
#include <iostream>
#include <unordered_map>
#include <algorithm>
#include <vector>
using namespace std;

//sort the string(s)
void ssort(string &s) {
  sort(s.begin(), s.end());
}

int main(int argc, char *argv[]){

  unordered_map<string, vector<string> *> freqlist;
  vector<string> *wordlist;
  unordered_map<string, vector<string> *>::iterator wordId;
  ifstream file;
  string word;
  string input;
  string sortedString;
  string hashkey;
  int countSize = 0;
  int numWords = 0;
  int numClasses = 0;

  if(argc != 2) {
    cout << "usage:  ./jumble <filename>\n";
    cout << "goodbye\n";
    return 1;
  }

  file.open(argv[1], ios::in);

  if(!file.is_open()){
    cout << "Error: could not open file '" << argv[1] << "'\n";
    cout << "goodbye\n";
    return 1;
  }

  cout << "reading input file...\n";

  while(!file.eof()){
    if (file >> input){
        numWords++;
        sortedString = input;
        ssort(sortedString);

        wordId = freqlist.find(sortedString);

        if (wordId == freqlist.end()){
            wordlist = new vector<string> ();
            freqlist.insert(pair<string, vector<string> *> (sortedString,wordlist));
            numClasses++;
        }
        else{
            wordlist = wordId->second;
        }

        wordlist->push_back(string(input));

        if (wordlist->size() >= countSize){
            countSize = wordlist->size();
            hashkey = sortedString;
        }
    }
  }

  cout << "start entering jumbled words (ctrl-d to terminate)" << endl;
  cout << " " << endl;
  file.close();

  //Finding jumble from here onwards
  cout << "> ";
  while (cin >> input){
      ssort(input);

      wordId = freqlist.find(input);
      if (wordId == freqlist.end()){
          cout << "no anagrams found...try again" << endl;
          cout << "> ";
      }
      else{
          wordlist = wordId->second;
          cout << "English Anagrams Found:" << endl;
          for (vector<string>::iterator wordlist1 = wordlist->begin(); wordlist1 != wordlist->end(); wordlist1++){
              cout << "    " << *wordlist1 << endl;
          }
          cout << "\b\b" << endl;
          cout << "> ";
      }
  }

  //display outputs
  cout << "REPORT" << endl;
  cout << " " << endl;
  cout << "  numWords" << "             " << ":" << "  " << numWords << endl;
  cout << "  numClasses" << "           " << ":" << "  " << numClasses << endl;
  cout << "  size-of-larget-class" << "  " << ":" << "  " << countSize << endl;
  cout << "  largest-class key" << "     " << ":" << "  " << "'" << hashkey << "'" << endl;
  cout << "  members of largest class:" << endl;
  cout << " " << endl;

  wordId = freqlist.find(hashkey);
      if (wordId == freqlist.end()){
          cout << "no anagrams found...try again" << endl;
          cout << "> ";
      }
      else{
          wordlist = wordId->second;
          for(vector<string>::iterator wordlist1 = wordlist->begin(); wordlist1 != wordlist->end(); wordlist1++){
              cout << "    " << "'" << *wordlist1 << "'" << endl;
          }
          cout << "\b\b" << endl;
      }

  for (unordered_map<string, vector<string> *>::iterator wordlist1 = freqlist.begin(); wordlist1 != freqlist.end(); wordlist1++){
      delete wordlist1->second;
  }

  return 0;
}
