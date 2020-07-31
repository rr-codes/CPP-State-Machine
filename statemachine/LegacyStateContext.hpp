//
//  LegacyStateContext.hpp
//  statemachine
//
//  Created by Richard Robinson on 2020-07-22.
//

#ifndef LegacyStateContext_hpp
#define LegacyStateContext_hpp

#include <stdio.h>
#include <thread>

namespace Legacy {

constexpr auto GO_N = 0;
constexpr auto WAIT_N = 1;
constexpr auto GO_E = 2;
constexpr auto WAIT_E = 3;

class StateContext {
public:
    int light = 0;
    
    StateContext(int initialState) : currentState(initialState) {
        light = FSM[currentState].Out;
    }
    
    void update(int input) {
        std::this_thread::sleep_for(std::chrono::milliseconds(FSM[currentState].Time));
        currentState = FSM[currentState].Next[input];
        light = FSM[currentState].Out;  // set lights
    }
    
private:
    int currentState = GO_N;
    
    struct State {
        int Out;
        int Time;
        int Next[4];
    };
    
    State FSM[4] = {
        { 0x21, 300, { GO_N, WAIT_N, GO_N, WAIT_N } },
        { 0x22,  50, { GO_E, GO_E, GO_E, GO_E } },
        { 0x0C, 300, { GO_E, GO_E, WAIT_E, WAIT_E } },
        { 0x14,  50, { GO_N, GO_N, GO_N, GO_N } }
    };
};

}

#endif /* LegacyStateContext_hpp */
