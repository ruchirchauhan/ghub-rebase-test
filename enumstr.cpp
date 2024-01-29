/******************************************************************************

                              Online C++ Compiler.
               Code, Compile, Run and Debug C++ program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include <iostream>
#include <stdio.h>
#include <string_view>
#include <vector>

#define ENUM_STRING(x) (x,#x)

enum eSMState {
    SM_STATE_IDLE,
    SM_STATE_INITIALIZED,
    SM_STATE_DMS_PENDING,
    SM_STATE_DPS_PENDING,
    SM_STATE_CONNECT_TO_BROKER_PENDING,
    SM_STATE_CONNECTED
};

std::string eSMStateString(eSMState e) {
    static std::vector<std::pair<int, std::string>> en = {std::make_pair(SM_STATE_IDLE, #SM_STATE_IDLE),
                                                       std::make_pair(SM_STATE_INITIALIZED, #SM_STATE_INITIALIZED),
                                                       std::make_pair(SM_STATE_DMS_PENDING, #SM_STATE_DMS_PENDING),
                                                       std::make_pair(SM_STATE_DPS_PENDING, #SM_STATE_DPS_PENDING),
                                                       std::make_pair(SM_STATE_CONNECT_TO_BROKER_PENDING, #SM_STATE_CONNECT_TO_BROKER_PENDING),
                                                       std::make_pair(SM_STATE_CONNECTED, #SM_STATE_CONNECTED)};
    return en[e];
}

int main()
{
    cout<<"Hello World";
    printf("SM_STATE_IDLE[%d][%s]\n", SM_STATE_IDLE, eSMStateString(SM_STATE_IDLE).c_str());
    printf("SM_STATE_IDLE[%d][%s]\n", SM_STATE_IDLE, eSMStateString(SM_STATE_IDLE).c_str());

    return 0;
}
