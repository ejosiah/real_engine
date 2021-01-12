#include <string_view>
#include "Scene.h"

namespace real{

    struct Action{
        enum class Behavior{
            NORMAL, DETECT_INITIAL_PRESS_ONLY
        };

        enum class State{
            RELEASED,
            PRESSED,
            HELD
        };

        std::string_view name;
        Behavior behavior;
        State state;
        int amount;

        inline void reset(){
            state = State::RELEASED;
            amount = 0;
        }

        inline void press(){
            press(1);
        }

        inline void press(int amount){
            if(state != State::HELD){
                this->amount += amount;
                state = State::PRESSED;
            }
        }

        inline void release(){
            state = State::RELEASED;
        }

        inline bool isPressed(){
            return getAmount() != 0;
        }

        inline int getAmount(){
            int res = amount;
            if(res != 0){
                if(state == State::RELEASED){
                    amount = 0;
                }else if(behavior == Behavior::DETECT_INITIAL_PRESS_ONLY){
                    state = State::HELD;
                    amount = 0;
                }
            }
            return res;
        }
    };

    class InputManager{

    public:
        void processEvents();

        Result init(const Scene& scene);
    };
}