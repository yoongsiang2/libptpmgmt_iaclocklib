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

#include <cstdint>
#include <string>

#include <clkmgr/utility.h>

__CLKMGR_NAMESPACE_BEGIN

/**
 * Types for class clkmgr_value
 */
typedef enum : std::uint8_t {
    gmOffsetValue, /**< GM offset value */
    valueLast /**< Last value type */
} valueType;

#define MAX_VALUE_COUNT 12

/**
 * Class to hold upper and lower limits
 */
class clkmgr_value
{
  private:
    /**
     * Structure to hold upper and lower limits
     */
    struct value_t {
        std::int32_t upper; /**< Upper limit */
        std::int32_t lower; /**< Lower limit */
        value_t();
        value_t(uint32_t limit);
        bool equal(const value_t &v);
        bool operator== (const value_t &value) { return this->equal(value); }
        bool operator!= (const value_t &value) { return !this->equal(value); }
        void zero() { upper = 0; lower = 0; }
    };
    /**
     * Array of values
     */
    value_t value[valueLast];
    /**
     * Reserved values
     */
    value_t reserved[MAX_VALUE_COUNT - sizeof(value) / sizeof(value[0])];
  public:
    std::uint8_t *parse(std::uint8_t *buf, std::size_t &length);
    std::uint8_t *write(std::uint8_t *buf, std::size_t &length);
    bool equal(const clkmgr_value &c);
    bool operator== (const clkmgr_value &value) { return this->equal(value); }
    bool operator!= (const clkmgr_value &value) { return !this->equal(value); }
    /**
     * @brief Set the upper and lower limits of a specific index in value array
     * @param index Index of the value_t
     * @param upper Upper limit
     * @param lower Lower limit
     */
    void setValue(int index, std::int32_t upper, std::int32_t lower) {
        if(index >= 0 && index < valueLast) {
            value[index].upper = upper;
            value[index].lower = lower;
        }
    }
    /**
     * @brief Get the upper limit of a specific index in value array
     * @param index Index of the value_t
     * @return Upper limit
     */
    std::int32_t getUpper(int index) {
        if(index >= 0 && index < valueLast)
            return value[index].upper;
        return 0;
    }
    /**
     * @brief Get the lower limit of a specific index in value array
     * @param index Index of the value_t
     * @return Lower limit
     */
    std::int32_t getLower(int index) {
        if(index >= 0 && index < valueLast)
            return value[index].lower;
        return 0;
    }
    std::string toString();
};

#define BITS_PER_BYTE (8)
#define MAX_EVENT_COUNT (32)

/**
 * Types of PTP events subscription
 */
typedef enum : std::uint8_t {
    gmOffsetEvent, /**< Primary-secondary clock offset event */
    syncedToPrimaryClockEvent, /**< Synced to primary clock event */
    asCapableEvent, /**< IEEE 802.1AS capable event */
    gmChangedEvent, /**< Primary clock UUID changed event */
    eventLast /**< Last event type */
} eventType;

/**
 * Class to hold event counts
 */
class clkmgr_eventcount
{
    std::uint32_t count[eventLast]; /**< Event counts */
    /**
     * Reserved event counts
     */
    std::uint32_t reserved[MAX_EVENT_COUNT - eventLast];
  public:
    std::uint8_t *parse(std::uint8_t *buf, std::size_t &length);
    std::uint8_t *write(std::uint8_t *buf, std::size_t &length);
    void zero();
    bool equal(const clkmgr_eventcount &ec);
    bool operator== (const clkmgr_eventcount &ec) { return this->equal(ec); }
    bool operator!= (const clkmgr_eventcount &ec) { return !this->equal(ec); }
};

/**
 * Class to hold event subscriptions
 */
class clkmgr_subscription
{
  private:
    std::uint32_t event_mask; /**< Event subscription mask */
    clkmgr_value value; /**< value of upper and lower limits */
    std::uint32_t composite_event_mask; /**< Composite event mask */
  public:
    DECLARE_ACCESSOR(event_mask); /**< Declare accessor for event */
    DECLARE_ACCESSOR(value); /**< Declare accessor for value */
    DECLARE_ACCESSOR(composite_event_mask); /**< Declare accessor for composite event */
};

__CLKMGR_NAMESPACE_END

#endif /* CLKMGR_SUBSCRIPTION_H */
