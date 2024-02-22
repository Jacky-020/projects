#include <iostream>
template <typename Object>
class Two_Stack{
    private:
        Object * arr;
        int size;
        int top_of_first = 0;
        int top_of_second;
    
    public:
        Two_Stack(int s = 0) : arr(nullptr), size(s), top_of_second(s - 1){
            arr = new Object[s];
        }
        ~Two_Stack(){
            delete []arr;
        }
        void push_first(const Object & obj){
            if(full()){
                std::cerr << "full!\n";
                return;
            }
            arr[top_of_first++] = obj;            
        }
        void push_first(Object && obj){
            if(full()){
                std::cerr << "full!\n";
                return;
            }
            arr[top_of_first++] = std::move(obj);   
        }
        void push_second(const Object & obj){
            if(full()){
                std::cerr << "full!\n";
                return;
            }
            arr[top_of_second--] = obj;            
        }
        void push_second(Object && obj){
            if(full()){
                std::cerr << "full!\n";
                return;
            }
            arr[top_of_second--] = std::move(obj);            
        }
        void pop_first(){ 
            if(!first_is_empty())  
                --top_of_first; 
        }

        void pop_second(){ 
            if(!second_is_empty())
                ++top_of_second; 
        }

        const Object & top_first()const{ 
            if(first_is_empty())
                std::cerr << "First stack is empty.\n";
            return arr[top_of_first - 1]; 
        }

        const Object & top_second()const{ 
            if(second_is_empty())
                std::cerr << "Second stack is empty.\n";
            return arr[top_of_second + 1];
        }

        Object & top_first(){ 
            if(first_is_empty())
                std::cerr << "First stack is empty.\n";
            return arr[top_of_first - 1]; 
        }

        Object & top_second(){ 
            if(second_is_empty())
                std::cerr << "Second stack is empty.\n";
            return arr[top_of_second + 1];
        }

        bool first_is_empty()const
        { return top_of_first == 0; }

        bool second_is_empty()const
        { return top_of_second == size - 1; }

        bool full()const
        { return top_of_first == top_of_second + 1; }
};