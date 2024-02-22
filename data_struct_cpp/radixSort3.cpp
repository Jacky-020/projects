#include <vector>
#include <string>
using namespace std;
void radixSort(std::vector<std::string> & arr, int maxLen){
    const int BUCKETS = 256;

    std::vector<std::vector<std::string>> wordsByLength(maxLen + 1);
    std::vector<std::vector<std::string>> buckets(BUCKETS);

    for(string & s : arr){
        wordsByLength[s.length()].push_back(std::move(s));
    }

    int idx = 0;
    for(auto & wordList : wordsByLength){
        for(auto & s : wordList){
            arr[idx++] = std::move(s);
        }
    }

    int startingIndex = arr.size();
    for(int pos = maxLen - 1; pos >= 0; --pos){
        startingIndex -= wordsByLength[pos + 1].size();
        for(int i = startingIndex; i < arr.size(); ++i)
            buckets[arr[i][pos]].push_back(std::move(arr[i]));

        idx = startingIndex;
        for(auto & thisBucket : buckets){
            for(string & s : thisBucket){
                arr[idx] = std::move(s);
            }

            thisBucket.clear();
        }
    }
}