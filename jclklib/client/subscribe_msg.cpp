/*
 * SPDX-License-Identifier: BSD-3-Clause
 * SPDX-FileCopyrightText: Copyright © 2024 Intel Corporation.
 */

/** @file subscribe_msg.cpp
 * @brief Client subscribe message class.
 * Implements client specific functionality.
 *
 * @author Noor Azura Ahmad Tarmizi <noor.azura.ahmad.tarmizi@intel.com>
 * @copyright © 2024 Intel Corporation.
 * @license BSD-3-Clause
 *
 */

#include <client/notification_msg.hpp>
#include <client/subscribe_msg.hpp>
#include <common/print.hpp>
#include <common/serialize.hpp>

using namespace JClkLibClient;
using namespace JClkLibCommon;
using namespace std;

/** @brief Create the ClientSubscribeMessage object
 *
 * @param msg msg structure to be fill up
 * @param LxContext client run-time transport listener context
 * @return true
 */
MAKE_RXBUFFER_TYPE(ClientSubscribeMessage::buildMessage)
{
    PrintDebug("[ClientSubscribeMessage]::buildMessage()");
    msg = new ClientSubscribeMessage();
    return true;
}

/** @brief Add client's SUBSCRIBE_MSG type and its builder to transport layer.
 *
 * This function will be called during init to add a map of SUBSCRIBE_MSG
 * type and its corresponding buildMessage function.
 *
 * @return true
 */
bool ClientSubscribeMessage::initMessage()
{
    PrintDebug("[ClientSubscribeMessage]::initMessage()");
    addMessageType(parseMsgMapElement_t(SUBSCRIBE_MSG, buildMessage));
    return true;
}

void ClientSubscribeMessage::setClientState(ClientState *newClientState)
{
    currentClientState = newClientState;
    jclCurrentState = &(newClientState->get_eventState());
}

PARSE_RXBUFFER_TYPE(ClientSubscribeMessage::parseBuffer)
{
    JClkLibCommon::ptp_event data = {};
    std::uint32_t eventSub[1];
    currentClientState->get_eventSub().get_event().readEvent(eventSub,
        (std::size_t)sizeof(eventSub));
    std::uint32_t composite_eventSub[1];
    currentClientState->get_eventSub().get_composite_event().readEvent(
        composite_eventSub,
        (std::size_t)sizeof(composite_eventSub));
    PrintDebug("[ClientSubscribeMessage]::parseBuffer ");
    if(!CommonSubscribeMessage::parseBuffer(LxContext))
        return false;
    if(!PARSE_RX(FIELD, data, LxContext))
        return false;
    /* TODO :
    1. Remove the pair if the sessionID is terminated (disconnect)
    2. to move some/all processing inside the processMessage instead of here.
    */
    JClkLibCommon::sessionId_t currentSessionID =
        currentClientState->get_sessionId();
    std::map <JClkLibCommon::sessionId_t,
        std::array<JClkLibCommon::client_ptp_event *, 2>>::iterator it;
    JClkLibCommon::client_ptp_event *client_data, *composite_client_data;
    int64_t lower_master_offset =
        currentClientState->get_eventSub().get_value().getLower(gmOffsetValue);
    int64_t upper_master_offset =
        currentClientState->get_eventSub().get_value().getUpper(gmOffsetValue);
    it = client_ptp_event_map.find(currentSessionID);
    if(it == client_ptp_event_map.end()) {
        /* Creation of a new map item for this new sessionID */
        client_data = new JClkLibCommon::client_ptp_event();
        composite_client_data = new JClkLibCommon::client_ptp_event();
        client_ptp_event_map.insert(\
            std::pair<JClkLibCommon::sessionId_t, \
            std::array<JClkLibCommon::client_ptp_event *, 2>>\
            (currentSessionID, {client_data, composite_client_data}));
    } else {
        /* Reuse the current client data */
        client_data = it->second[0];
        composite_client_data = it->second[1];
    }
    if((eventSub[0] & 1 << gmOffsetEvent) &&
        (data.master_offset != client_data->master_offset)) {
        client_data->master_offset = data.master_offset;
        if((client_data->master_offset > lower_master_offset) &&
            (client_data->master_offset < upper_master_offset))
            client_data->master_offset_in_range = true;
    }
    if((eventSub[0] & 1 << syncedToPrimaryClockEvent) &&
        (data.synced_to_primary_clock != client_data->synced_to_primary_clock))
        client_data->synced_to_primary_clock = data.synced_to_primary_clock;
    if((eventSub[0] & 1 << gmChangedEvent) &&
        (memcmp(client_data->gm_identity, data.gm_identity,
                sizeof(data.gm_identity))) != 0) {
        memcpy(client_data->gm_identity, data.gm_identity,
            sizeof(data.gm_identity));
        jclCurrentState->gm_changed = true;
    }
    if((eventSub[0] & 1 << asCapableEvent) &&
        (data.as_capable != client_data->as_capable))
        client_data->as_capable = data.as_capable;
    if(composite_eventSub[0])
        composite_client_data->composite_event = true;
    if((composite_eventSub[0] & 1 << gmOffsetEvent) &&
        (data.master_offset != composite_client_data->master_offset)) {
        composite_client_data->master_offset = data.master_offset;
        if((composite_client_data->master_offset > lower_master_offset) &&
            (composite_client_data->master_offset < upper_master_offset))
            composite_client_data->composite_event = true;
        else
            composite_client_data->composite_event = false;
    }
    if(composite_eventSub[0] & 1 << syncedToPrimaryClockEvent)
        composite_client_data->composite_event &= data.synced_to_primary_clock;
    if(composite_eventSub[0] & 1 << asCapableEvent)
        composite_client_data->composite_event &= data.as_capable;
    jclCurrentState->as_capable = client_data->as_capable;
    jclCurrentState->offset_in_range = client_data->master_offset_in_range;
    jclCurrentState->synced_to_primary_clock = client_data->synced_to_primary_clock;
    jclCurrentState->composite_event = composite_client_data->composite_event;
    memcpy(jclCurrentState->gm_identity, client_data->gm_identity,
        sizeof(client_data->gm_identity));
    return true;
}

/** @brief process the reply for notification msg from proxy.
 *
 * This function will be called when the transport layer
 * in client runtime received a SUBSCRIBE_MSG type (an echo reply from
 * proxy)
 * In this case, transport layer will rx a buffer in the client associated
 * listening message queue (listening to proxy) and call this function when
 * the enum ID corresponding to the SUBSCRIBE_MSG is received.
 *
 * @param LxContext client run-time transport listener context
 * @param TxContext client run-time transport transmitter context
 * @return true
 */
PROCESS_MESSAGE_TYPE(ClientSubscribeMessage::processMessage)
{
    PrintDebug("[ClientSubscribeMessage]::processMessage (reply)");
    std::unique_lock<rtpi::mutex> lock(cv_mtx);
    currentClientState->set_subscribed(true);
    /* Add the current ClientState to the notification class */
    ClientNotificationMessage::addClientState(currentClientState);
    this->set_msgAck(ACK_NONE);
    jcl_state jclCurrentState = currentClientState->get_eventState();
    lock.unlock();
    cv.notify_one(lock);
    return true;
}

/* delete the client ptp event based on session ID given */
void ClientSubscribeMessage::deleteClientPtpEventStruct(
    JClkLibCommon::sessionId_t sID)
{
    std::map <JClkLibCommon::sessionId_t,
        std::array<JClkLibCommon::client_ptp_event *, 2>>::iterator it;
    JClkLibCommon::client_ptp_event *client_data, *composite_data;
    it = client_ptp_event_map.find(sID);
    if(it != client_ptp_event_map.end()) {
        client_data = it->second[0];
        composite_data = it->second[1];
        delete client_data;
        delete composite_data;
        client_ptp_event_map.erase(it);
    } else
        PrintDebug("The item is not found in client_ptp_event_map");
}

/* get the corresponding ClientPtpEvent */
JClkLibCommon::client_ptp_event
*ClientSubscribeMessage::getClientPtpEventStruct(JClkLibCommon::sessionId_t sID)
{
    std::map <JClkLibCommon::sessionId_t,
        std::array<JClkLibCommon::client_ptp_event *, 2>>::iterator it;
    JClkLibCommon::client_ptp_event *client_data = nullptr;
    it = client_ptp_event_map.find(sID);
    if(it != client_ptp_event_map.end())
        client_data = it->second[0];
    return client_data;
}

/* get the corresponding ClientPtpEvent for composite  */
JClkLibCommon::client_ptp_event
*ClientSubscribeMessage::getClientPtpEventCompositeStruct(
    JClkLibCommon::sessionId_t sID)
{
    std::map <JClkLibCommon::sessionId_t,
        std::array<JClkLibCommon::client_ptp_event *, 2>>::iterator it;
    JClkLibCommon::client_ptp_event *client_data = nullptr;
    it = client_ptp_event_map.find(sID);
    if(it != client_ptp_event_map.end())
        client_data = it->second[1];
    return client_data;
}

/* reduce the corresponding eventCount */
void ClientSubscribeMessage::resetClientPtpEventStruct(
    JClkLibCommon::sessionId_t sID,
    jcl_state_event_count &eventCount)
{
    std::map <JClkLibCommon::sessionId_t,
        std::array<JClkLibCommon::client_ptp_event *, 2>>::iterator it;
    JClkLibCommon::client_ptp_event *client_ptp_data = nullptr;
    it = client_ptp_event_map.find(sID);
    if(it != client_ptp_event_map.end())
        client_ptp_data = it->second[0];
    else {
        PrintError("resetClientPtpEventStruct Failed.");
        return;
    }
    client_ptp_data->offset_in_range_event_count.fetch_sub(
        eventCount.offset_in_range_event_count,
        std::memory_order_relaxed);
    client_ptp_data->as_capable_event_count.fetch_sub(
        eventCount.as_capable_event_count,
        std::memory_order_relaxed);
    client_ptp_data->synced_to_primary_clock_event_count.fetch_sub(
        eventCount.synced_to_primary_clock_event_count,
        std::memory_order_relaxed);
    client_ptp_data->gm_changed_event_count.fetch_sub(
        eventCount.gm_changed_event_count,
        std::memory_order_relaxed);
    client_ptp_data->composite_event_count.fetch_sub(
        eventCount.composite_event_count,
        std::memory_order_relaxed);
    eventCount.offset_in_range_event_count =
        client_ptp_data->offset_in_range_event_count;
    eventCount.as_capable_event_count = client_ptp_data->as_capable_event_count;
    eventCount.synced_to_primary_clock_event_count =
        client_ptp_data->synced_to_primary_clock_event_count;
    eventCount.gm_changed_event_count = client_ptp_data->gm_changed_event_count;
    eventCount.composite_event_count = client_ptp_data->composite_event_count;
}
