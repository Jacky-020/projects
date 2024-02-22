#include <iostream>
template <typename Object>
class Three_Stack{
    private:
        Object * arr;
        int size;
        int top_of_first = 0;
        int top_of_second;
        int bottom_of_third;
        int top_of_third;

        void renew_third_to_left(int movement){
            for(int i = bottom_of_third; i < top_of_third; ++i){
                arr[i - movement] = arr[i];
            }
        }
        void renew_third_to_right(int movement){
            for(int i = top_of_third - 1; i >= bottom_of_third; --i){
                arr[i + movement] = arr[i];
            }
        }
    public:
        Three_Stack(int s = 0) : arr(nullptr), size(s), top_of_second(s - 1), bottom_of_third(s / 3), top_of_third(s / 3){
            arr = new Object[s];
        }
        ~Three_Stack(){
            delete []arr;
        }
        void push_first(const Object & obj){
            if(full()){
                std::cerr << "full!\n";
                return;
            }
            if(touch_bottom_of_third())
                move_third_to_right();
            arr[top_of_first++] = obj;            
        }
        void push_first(Object && obj){
            if(full()){
                std::cerr << "full!\n";
                return;
            }
            if(touch_bottom_of_third())
                move_third_to_right();
            arr[top_of_first++] = std::move(obj);   
        }
        void push_second(const Object & obj){
            if(full()){
                std::cerr << "full!\n";
                return;
            }
            if(touch_top_of_third())
                move_third_to_left();

            arr[top_of_second--] = obj;            
        }
        void push_second(Object && obj){
            if(full()){
                std::cerr << "full!\n";
                return;
            }
            if(touch_top_of_third())
                move_third_to_left();
            arr[top_of_second--] = std::move(obj);            
        }
        void push_third(const Object & obj){
            if(full()){
                std::cerr << "full!\n";
                return;
            }
            if(touch_top_of_third()){
                move_third_to_left();
            }
            arr[top_of_third++] = obj;   
        }
        void push_third(Object && obj){
            if(full()){
                std::cerr << "full!\n";
                return;
            }
            if(touch_top_of_third())
                move_third_to_left();
            arr[top_of_third++] = std::move(obj);   
        }
        void pop_first(){ 
            if(!first_is_empty())  
                --top_of_first; 
        }

        void pop_second(){ 
            if(!second_is_empty())
                ++top_of_second; 
        }

        void pop_third(){
            if(!third_is_empty())
                --top_of_third; 
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

        const Object & top_third()const{ 
            if(third_is_empty())
                std::cerr << "Third stack is empty.\n";
            return arr[top_of_third - 1];
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
        Object & top_third(){ 
            if(third_is_empty())
                std::cerr << "Third stack is empty.\n";
            return arr[top_of_third - 1];
        }

        bool first_is_empty()const
        { return top_of_first == 0; }

        bool second_is_empty()const
        { return top_of_second == size - 1; }
        
        bool third_is_empty()const
        { return top_of_third == bottom_of_third; }

        bool full()const
        { return touch_bottom_of_third() && touch_top_of_third(); }

        bool touch_bottom_of_third()const
        { return top_of_first == bottom_of_third; }
        
        bool touch_top_of_third()const
        { return top_of_third - top_of_second == 1; }

        void move_third_to_right(){
            int empty_space = bottom_of_third - top_of_first + top_of_second - top_of_third + 1;
            int movement = empty_space / 3 + 1;
            movement = empty_space / 3 + 1;
            renew_third_to_right(movement);
            bottom_of_third += movement;
            top_of_third += movement;
        }

        void move_third_to_left(){
            int empty_space = bottom_of_third - top_of_first + top_of_second - top_of_third + 1;
            int movement = empty_space / 3 + 1;
            renew_third_to_left(movement);
            bottom_of_third -= movement;
            top_of_third -= movement;
        }
        
};