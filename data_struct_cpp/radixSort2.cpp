#include <vector>
#include <string>
#include <cstdio>
#include <iostream>
using namespace std;
void radixSort(std::vector<std::string> & arr, int maxLen);

int main(){
    std::string input;
    std::cin >> input;
    std::vector<std::string> wordList;
    while(input != "quit"){
        wordList.push_back(input);
        std::cin >> input;
    }
    radixSort(wordList, 100);
    std::cout << "After radix sort: \n";
    for(std::string str : wordList){
        std::cout << str << std::endl;
    }
}

void radixSort(std::vector<std::string> & arr, int maxLen){
    std::vector<std::vector<std::string>> wordsByLength(maxLen + 1);
    std::vector<std::vector<std::string>> buckets(256);

    for(auto & str : arr){
        wordsByLength[str.size()].push_back(std::move(str));
    }

    int pos = maxLen + 1;
    while(wordsByLength[--pos].empty()) ;

    while(pos){
        std::cout << pos << std::endl;
        for(std::string & s : wordsByLength[pos]){
            buckets[s[pos - 1]].push_back(s);
        }
        for(int ch = 0; ch < 256; ++ch){
            for(int i = 0; i < buckets[ch].size(); ++i){
                std::cout << char(ch) << " )" << buckets[ch][i] << std::endl;
                wordsByLength[pos - 1].push_back(std::move(buckets[ch][i]));
            }
            buckets[ch].clear();
        }
        --pos;
        std::cout << std::endl;

    }
    arr.swap(wordsByLength[1]);
}