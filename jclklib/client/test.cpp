/*! \file test.cpp
    \brief Test client code

    (C) Copyright Intel Corporation 2023. All rights reserved. Intel Confidential.
    Author: Christopher Hall <christopher.s.hall@intel.com>
*/

#include "init.hpp"

#include <unistd.h>
#include <iostream>
#include <stdlib.h>
#include <common/jclklib_import.hpp>
#include <client/client_state.hpp>
#include <client/connect_msg.hpp>

using namespace JClkLibClient;
using namespace JClkLibCommon;
using namespace std;

int main()
{
    int ret = EXIT_SUCCESS;
    JClkLibCommon::jcl_subscription sub;
    std::uint32_t event2Sub1[1] = {((1<<gmPresentUUIDEvent)|(1<<gmPresentUUIDEvent)|(1<<servoLockedEvent))};

    std::cout << "[CLIENT] Before connect : Session ID : " << state.get_sessionId() << "\n";

    if (connect() == false) {
        std::cout << "[CLIENT] Failure in connecting !!!\n";
        ret = EXIT_FAILURE;
        goto do_exit;
    }
    else {
        std::cout << "[CLIENT] Connected. Session ID : " << state.get_sessionId() << "\n";
    }
    sleep(5);

    sub.get_event().writeEvent(event2Sub1, (std::size_t)sizeof(event2Sub1));
    std::cout << "[CLIENT] set subscribe event : " + sub.c_get_val_event().toString() << "\n";
    subscribe(sub);
	sleep(5);
 do_exit:
	disconnect();

    return ret;
}