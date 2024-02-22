#include <string>
#include <vector>
#include <iostream>
using namespace std;
void radixSort(std::vector<std::string> & arr);

int main(){
    cout << "Enter the number of string to input: ";
    int numString;
    cin >> numString;
    vector<string> stringList(numString);
    for(int i = 0; i < numString; ++i){
        cout << "Enter the string: ";
        cin >> stringList[i];
    }
    radixSort(stringList);
    for(const auto & entry : stringList){
        cout << entry << endl;
    }
}
void radixSort(std::vector<std::string> & arr){
    const int BUCKETS = 256;
    std::vector<std::string> out(arr.size());
    for(int p = arr[0].size() - 1; p >= 0; --p){
        std::vector<int> count(BUCKETS + 1);
        for(const std::string & s : arr){
            ++count[s[p] + 1];
        }

        for(int i = 1; i <= BUCKETS; ++i){
            count[i] += count[i - 1];
        }
 
        for(std::string & s : arr){
            out[count[s[p]]++] = std::move(s);
        }

        arr.swap(out);
    }

    if(arr.size() & 1){
        arr.swap(out);
    }
}