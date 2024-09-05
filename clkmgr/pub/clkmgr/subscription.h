/*
 * SPDX-License-Identifier: BSD-3-Clause
 * SPDX-FileCopyrightText: Copyright © 2024 Intel Corporation.
 */

/** @file subscription.h
 * @brief class, structures and enums used for events subsciption
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

#include <clkmgr/event_state.h>
#include <clkmgr/utility.h>

__CLKMGR_NAMESPACE_BEGIN

/**
 * @enum EventBitmask
 * @brief Bitmask of events available for subscription. Each bit represents one
 * event.
 */
typedef enum : std::uint32_t {
    eventBGMOffset = 1 << eventIGMOffset, /**< Bitmask for offset */
    eventBSyncedToPrimaryClock = 1 << eventISyncedToPrimaryClock, /**< Synced */
    eventBASCapable = 1 << eventIASCapable, /**< Bitmask for AS capable */
    eventBGMChanged = 1 << eventIGMChanged, /**< Bitmask for UUID */
} EventBitmask;

constexpr std::uint8_t THRESHOLD_MAX = 8;

/**
 * @enum ThresholdIndex
 * @brief Index of events which require user to provide threshold.
 * @note The thresholdLast is reserved for future use. The maximum number of
 * events which can have threshold is THRESHOLD_MAX.
 */
typedef enum : std::uint8_t {
    thresholdGMOffset,  /**< threshold for primary-secondary clock offset */
    thresholdLast       /**< Last threshold */
} ThresholdIndex;

/**
 * @class ClkMgrSubscription
 * @brief Class to hold the event subscription mask, composite event mask, and
 * thresholds for events that require user-defined limits.
 */
class ClkMgrSubscription
{
  private:
    /**
     * @struct Threshold
     * @brief Structure to hold upper and lower limits
     */
    struct Threshold {
        std::int32_t upper_limit; /**< Upper limit */
        std::int32_t lower_limit; /**< Lower limit */
        Threshold() noexcept : upper_limit(0), lower_limit(0) {}
    };

    std::uint32_t event_mask; /**< Event subscription mask */
    std::uint32_t composite_event_mask; /**< Composite event mask */
    std::array<Threshold, THRESHOLD_MAX> threshold; /**< Upper & lower limits */

  public:
    ClkMgrSubscription() noexcept : event_mask(0), composite_event_mask(0) {}
    DECLARE_ACCESSOR(event_mask); /**< Event mask accessor */
    DECLARE_ACCESSOR(composite_event_mask); /**< Composite event accessor */
    DECLARE_ACCESSOR(threshold); /**< Threshold accessor */

    /**
     * @brief Define the upper and lower limits of a specific event
     * @param[in] index Index of the event according to ThresholdIndex enum
     * @param[in] upper Upper limit
     * @param[in] lower Lower limit
     * @return true on success, false on failure
     */
    bool define_threshold(std::uint8_t index, std::int32_t upper,
        std::int32_t lower);

    /**
     * @brief Check whether a given value is within predefined threshold
     * @param[in] index Index of the event according to ThresholdIndex enum
     * @param[in] value Current value
     * @return Return true if value is within the threshold, and false otherwise
     */
    bool in_range(std::uint8_t index, std::int32_t value) const;
};

__CLKMGR_NAMESPACE_END

#endif /* CLKMGR_SUBSCRIPTION_H */
