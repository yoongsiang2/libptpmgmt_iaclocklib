/* SPDX-License-Identifier: BSD-3-Clause
   SPDX-FileCopyrightText: Copyright © 2024 Intel Corporation. */

/** @file
 * @brief Set and get the client subscribe event state
 *
 * @author Noor Azura Ahmad Tarmizi <noor.azura.ahmad.tarmizi@intel.com>
 * @copyright © 2024 Intel Corporation.
 *
 */

#include "client/client_state.hpp"
#include "client/msgq_tport.hpp"
#include "common/clkmgrtypes.hpp"
#include "common/message.hpp"
#include "common/transport.hpp"

#include <cstring>
#include <string>

__CLKMGR_NAMESPACE_USE;

using namespace std;

ClientState::ClientState()
{
    connected = false;
    subscribed = false;
    m_sessionId = InvalidSessionId;
    fill(begin(clientID), end(clientID), 0);
    eventState = {};
    eventStateCount = {};
    eventSub = {};
    last_notification_time = {};
    ptp4ldomainNumber = 0;
    fill(begin(ptp4ludsAddr), end(ptp4ludsAddr), 0);
    fill(begin(chronyudsAddr), end(chronyudsAddr), 0);
}

ClientState::ClientState(const ClientState &newState)
{
    connected = newState.get_connected();
    subscribed = newState.get_subscribed();
    m_sessionId = newState.get_sessionId();
    strcpy((char *)clientID.data(), (char *)newState.get_clientID().data());
    eventState = newState.eventState;
    eventStateCount = newState.eventStateCount;
    eventSub = newState.eventSub;
    last_notification_time = newState.get_last_notification_time();
    ptp4ldomainNumber = newState.get_ptp4ldomainNumber();
    ptp4ludsAddr = newState.get_ptp4ludsAddr();
    chronyudsAddr = newState.get_chronyudsAddr();
}

void ClientState::set_clientState(const ClientState &newState)
{
    connected = newState.get_connected();
    subscribed = newState.get_subscribed();
    m_sessionId = newState.get_sessionId();
    strcpy((char *)clientID.data(), (char *)newState.get_clientID().data());
    eventState = newState.eventState;
    eventStateCount = newState.eventStateCount;
    eventSub = newState.eventSub;
    last_notification_time = newState.get_last_notification_time();
    ptp4ldomainNumber = newState.get_ptp4ldomainNumber();
    ptp4ludsAddr = newState.get_ptp4ludsAddr();
    chronyudsAddr = newState.get_chronyudsAddr();
}

bool ClientState::get_connected() const
{
    return connected;
}

void ClientState::set_connected(bool new_state)
{
    connected = new_state;
}

bool ClientState::get_subscribed() const
{
    return subscribed;
}

void ClientState::set_subscribed(bool subscriptionState)
{
    subscribed = subscriptionState;
}

TransportClientId ClientState::get_clientID() const
{
    return clientID;
}

void ClientState::set_clientID(const TransportClientId &new_cID)
{
    strcpy((char *)clientID.data(), (char *)new_cID.data());
}

const Event_count &ClientState::get_eventStateCount()
{
    return eventStateCount;
}

Event_state &ClientState::get_eventState()
{
    return eventState;
}

void ClientState::set_eventStateCount(const Event_count &newCount)
{
    eventStateCount = newCount;
}

void ClientState::set_eventState(const Event_state &newState)
{
    eventState = newState;
}

string ClientState::toString() const
{
    return string("[ClientState::eventState]") +
        " as_capable = " + to_string(eventState.as_capable) +
        " gm_changed = " + to_string(eventState.gm_changed) +
        " offset_in_range = " + to_string(eventState.offset_in_range) +
        " synced_to_primary_clock = " +
        to_string(eventState.synced_to_primary_clock) + "\n";
}

const ClkMgrSubscription &ClientState::get_eventSub()
{
    return eventSub;
}

void ClientState::set_eventSub(const ClkMgrSubscription &eSub)
{
    eventSub.set_ClkMgrSubscription(eSub);
}

sessionId_t ClientState::get_sessionId() const
{
    return m_sessionId;
}

void ClientState::set_sessionId(sessionId_t sessionId)
{
    m_sessionId = sessionId;
}

void ClientState::set_ptp4l_id(uint8_t ptp4l_id)
{
    m_ptp4l_id = ptp4l_id;
}

uint8_t ClientState::get_ptp4l_id() const
{
    return m_ptp4l_id;
}

void ClientState::set_last_notification_time(const timespec &newTime)
{
    last_notification_time = newTime;
}

timespec ClientState::get_last_notification_time() const
{
    return last_notification_time;
}

bool ClientState::add_chrony_instance(const UDSAddress &udsAddr)
{
    chronyudsAddr = udsAddr;
    return true;
}

bool ClientState::add_ptp4l_instance(const UDSAddress &udsAddr,
    uint8_t domainNumber)
{
    ptp4ludsAddr = udsAddr;
    ptp4ldomainNumber = domainNumber;
    return true;
}

UDSAddress ClientState::get_ptp4ludsAddr() const
{
    return ptp4ludsAddr;
}

UDSAddress ClientState::get_chronyudsAddr() const
{
    return chronyudsAddr;
}

uint8_t ClientState::get_ptp4ldomainNumber() const
{
    return ptp4ldomainNumber;
}
