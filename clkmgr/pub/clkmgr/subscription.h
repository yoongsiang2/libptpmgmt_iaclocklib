/*
 * SPDX-License-Identifier: BSD-3-Clause
 * SPDX-FileCopyrightText: Copyright © 2024 Intel Corporation.
 */

/** @file subscription.h
 * @brief structure and class needed for events subsciption
 *
 * @author Christopher Hall <christopher.s.hall@intel.com>
 * @copyright © 2024 Intel Corporation.
 *
 */

#ifndef CLKMGR_SUBSCRIPTION_H
#define CLKMGR_SUBSCRIPTION_H

#include <array>
#include <cstdint>
#include <string>

#include <clkmgr/utility.h>

__CLKMGR_NAMESPACE_BEGIN

constexpr std::uint8_t EVENT_MAX = 32;

/**
 * Bitmask of events available for subscription. Each bit represents one event.
 */
typedef enum : std::uint32_t {
    eventGMOffset = 1 << 0, /**< Primary-secondary clock offset event */
    eventSyncedToPrimaryClock = 1 << 1, /**< Synced to primary clock event */
    eventASCapable = 1 << 2, /**< IEEE 802.1AS capable event */
    eventGMChanged = 1 << 3, /**< Primary clock UUID changed event */
    eventLast = 1 << 4 /**< Last event */
} EventIndex;

constexpr std::uint8_t THRESHOLD_MAX = 8;

/**
 * Index of events which require user to provide threshold. The value of index
 * should be less than THRESHOLD_MAX.
 */
typedef enum : std::uint8_t {
    thresholdGMOffset,  /**< threshold for primary-secondary clock offset */
    thresholdLast       /**< Last threshold */
} ThresholdIndex;

/**
 * Class to hold event subscriptions
 */
class ClkMgrSubscription
{
  private:
    /**
     * Structure to hold upper and lower limits
     */
    struct Threshold {
        std::int32_t upper_limit; /**< Upper limit */
        std::int32_t lower_limit; /**< Lower limit */
        Threshold() noexcept : upper_limit(0), lower_limit(0) {}
    };
    std::uint32_t event_mask; /**< Event subscription mask */
    std::uint32_t composite_event_mask; /**< Composite event mask */
    std::array<Threshold, THRESHOLD_MAX> threshold; /**< upper & lower limits */
  public:
    ClkMgrSubscription() noexcept : event_mask(0), composite_event_mask(0) {}
    DECLARE_ACCESSOR(event_mask); /**<event_mask accessor */
    DECLARE_ACCESSOR(composite_event_mask); /**< composite_event_mask accessor */
    DECLARE_ACCESSOR(threshold); /**< threshold accessor */
    /**
     * @brief Define the upper and lower limits of a specific event
     * @param index Index of the event according to ThresholdIndex enum
     * @param upper Upper limit
     * @param lower Lower limit
     * @return true on success, false on failure
     */
    bool define_threshold(std::uint8_t index, std::int32_t upper,
        std::int32_t lower);
    /**
     * @brief Check whether a given value is within predifined threshold
     * @param index Index of the event according to ThresholdIndex enum
     * @param value current value
     * @return true if in range, false otherwise
     */
    bool in_range(std::uint8_t index, std::int32_t value) const;
};

__CLKMGR_NAMESPACE_END

#endif /* CLKMGR_SUBSCRIPTION_H */
