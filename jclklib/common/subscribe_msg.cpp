/*! \file subscribe_msg.cpp
    \brief Common subscribe message implementation. Implements common functions and (de-)serialization

    (C) Copyright Intel Corporation 2023. All rights reserved. Intel Confidential.
    Author: Christopher Hall <christopher.s.hall@intel.com>
*/

#include <common/subscribe_msg.hpp>
#include <common/serialize.hpp>
#include <common/print.hpp>

using namespace JClkLibCommon;
using namespace std;

string CommonSubscribeMessage::toString()
{
	string name = ExtractClassName(string(__PRETTY_FUNCTION__),string(__FUNCTION__));
	name += "\n";
	name += Message::toString();
	//name += "Client ID: " + string((char *)clientId.data()) + "\n";

	return name;
}

PARSE_RXBUFFER_TYPE(CommonSubscribeMessage::parseBuffer) {
	PrintDebug("[CommonSubscribeMessage]::parseBuffer ");
	if(!Message::parseBuffer(LxContext))
		return false;

	if (!PARSE_RX(FIELD, get_sessionId(), LxContext))
		return false;
	
	if (!PARSE_RX(FIELD, subscription, LxContext))
		return false;

	return true;
}

BUILD_TXBUFFER_TYPE(CommonSubscribeMessage::makeBuffer) const
{
	auto ret = Message::makeBuffer(TxContext); 

	if (!ret)
		return ret;

	PrintDebug("[CommonSubscribeMessage]::makeBuffer - sessionId : " + to_string(c_get_val_sessionId()));
	if (!WRITE_TX(FIELD, c_get_val_sessionId(), TxContext))
		return false;

	PrintDebug("[CommonSubscribeMessage]::makeBuffer - subscription event : " + subscription.c_get_val_event().toString() + \
			", subscription val : " + subscription.c_get_val_value().toString());
	if (!WRITE_TX(FIELD,subscription, TxContext))
		return false;

	return true;
}

TRANSMIT_MESSAGE_TYPE(CommonSubscribeMessage::transmitMessage)
{
	PrintDebug("[CommonSubscribeMessage]::transmitMessage ");
	if (!presendMessage(&TxContext))
		return false;

	return TxContext.sendBuffer();
}

void setSubscription(jcl_subscription newsub) {
	PrintDebug("[CommonSubscribeMessage]::setSubscription ");
}