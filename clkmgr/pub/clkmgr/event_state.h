/*
 * SPDX-License-Identifier: BSD-3-Clause
 * SPDX-FileCopyrightText: Copyright © 2024 Intel Corporation.
 */

/** @file event_state.h
 * @brief Structure for event state and event count
 *
 * @author Noor Azura Ahmad Tarmizi <noor.azura.ahmad.tarmizi@intel.com>
 * @copyright © 2024 Intel Corporation.
 *
 */

#ifndef CLKMGR_EVENT_STATE_H
#define CLKMGR_EVENT_STATE_H

#include <cstdint>
#include <iostream>

#include <clkmgr/utility.h>

__CLKMGR_NAMESPACE_BEGIN

constexpr std::uint8_t EVENT_MAX = 32;

/**
 * @enum EventIndex
 * @brief Index of events available for subscription. Each index corresponds to
 * a specific event. The maximum number of events is defined by EVENT_MAX.
 */
typedef enum : std::uint8_t {
    eventIGMOffset = 0, /**< Primary-secondary clock offset event */
    eventISyncedToPrimaryClock = 1, /**< Synced to primary clock event */
    eventIASCapable = 2, /**< IEEE 802.1AS capable event */
    eventIGMChanged = 3, /**< Primary clock UUID changed event */
    eventILast = 4, /**< Last single event */
    eventIComposite = (EVENT_MAX - 1) /**< Composite event */
} EventIndex;

/**
 * Current State for the events
 */
struct clkmgr_state {
    uint64_t notification_timestamp; /**< Timestamp for last notification */
    int64_t  clock_offset; /**< Clock offset */
    uint8_t  gm_identity[8]; /**< Primary clock UUID */
    bool     as_capable; /**< IEEE 802.1AS capable */
    bool     offset_in_range; /**< Clock offset in range */
    bool     synced_to_primary_clock; /**< Synced to primary clock */
    bool     gm_changed; /**< Primary clock UUID changed */
    bool     composite_event; /**< Composite event */
};

/**
 * @class ClkMgrEventCount
 * @brief Class to store the count of event state changes.
 */
class ClkMgrEventCount
{
  private:
    std::array<uint64_t, EVENT_MAX> event_count; /**< Event count */

  public:
    ClkMgrEventCount() noexcept : event_count{} {} /**< Zero-initialize */

   /**
     * @brief Get the event count for specific event.
     * @param index The index of the event to get.
     * @return The event count of event at specified index.
     */
    uint64_t get_event_count(std::uint8_t index) const {
        if (index < eventILast || index == eventIComposite) {
            return event_count[index];
        }
        std::cerr << "Index out of range" << std::endl;
        return 0;
    }

    /**
     * @brief Set the event count for specific index.
     * @param index The index of the event to set.
     * @param count The event count to set.
     * @throws std::out_of_range if the index is out of range.
     */
    void set_event_count(std::uint8_t index, uint64_t count) {
        if (index < eventILast || index == eventIComposite) {
            event_count[index] = count;
            return;
        }
        std::cerr << "Index out of range" << std::endl;
    }
};

__CLKMGR_NAMESPACE_END

#endif /* CLKMGR_EVENT_STATE_H */
