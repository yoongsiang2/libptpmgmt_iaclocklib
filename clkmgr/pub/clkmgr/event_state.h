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
    eventIComposite = 31 /**< Composite event */
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
 * Event count for the events
 */
struct clkmgr_state_event_count {
    uint64_t offset_in_range_event_count; /**< Clk offset in range */
    uint64_t gm_changed_event_count; /**< Primary clk ID changed */
    uint64_t as_capable_event_count; /**< IEEE 802.1AS capable */
    uint64_t synced_to_primary_clock_event_count; /**< Synced to primary clk */
    uint64_t composite_event_count; /**< Composite event */
};

/**
 * @class ClkMgrEventCount
 * @brief Class to store the event count.
 */
class ClkMgrEventCount
{
  private:
    std::array<uint64_t, EVENT_MAX> event_count; /**< upper & lower limits */

  public:
    ClkMgrEventCount() noexcept : event_count{} {} /**< Zero-initialize */
    DECLARE_ACCESSOR(event_count); /**< vent count accessor */
};

__CLKMGR_NAMESPACE_END

#endif /* CLKMGR_EVENT_STATE_H */
