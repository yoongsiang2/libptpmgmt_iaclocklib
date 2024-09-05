/*
 * SPDX-License-Identifier: BSD-3-Clause
 * SPDX-FileCopyrightText: Copyright © 2024 Intel Corporation.
 */

/** @file clockmanager_c.h
 * @brief C wrapper for the Clock Manager APIs to set up client-runtime.
 *
 * @author Song Yoong Siang <yoong.siang.song@intel.com>
 * @copyright © 2024 Intel Corporation.
 *
 */

#ifndef CLKMGR_CLOCKMANAGER_C_H
#define CLKMGR_CLOCKMANAGER_C_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

enum event_type {
    eventBGMOffset = 1 << 0, /**< Primary-secondary clock offset event */
    eventBSyncedToPrimaryClock = 1 << 1, /**< Synced to primary clock event */
    eventBASCapable = 1 << 2, /**< IEEE 802.1AS capable event */
    eventBGMChanged = 1 << 3, /**< Primary clock UUID changed event */
    eventBLast = 1 << 4 /**< Last event */
};

#define CLKMGR_EVENT_MAX (32)

/**
 * @enum EventIndex
 * @brief Index of events available for subscription. Each index corresponds to
 * a specific event. The maximum number of events is defined by EVENT_MAX.
 */
enum event_index {
    eventIGMOffset = 0, /**< Primary-secondary clock offset event */
    eventISyncedToPrimaryClock = 1, /**< Synced to primary clock event */
    eventIASCapable = 2, /**< IEEE 802.1AS capable event */
    eventIGMChanged = 3, /**< Primary clock UUID changed event */
    eventILast = 4, /**< Last single event */
    eventIComposite = (CLKMGR_EVENT_MAX - 1) /**< Composite event */
};

/** Types for struct value */
enum value_type {
    gm_offset,    /**< Primary-secondary clock offset */
    value_last    /**< Last value type */
};

/** Structure to hold upper and lower limits */
struct value {
    int32_t upper;    /**< Upper limit */
    int32_t lower;    /**< Lower limit */
};

/** Subscription structure for the events */
struct clkmgr_c_subscription {
    uint32_t event;                       /**< Events subscription */
    struct value value[value_last];       /**< Limits */
    uint32_t composite_event;             /**< Composite events subscription */
};

/** Current State for the events */
struct clkmgr_c_state {
    uint8_t gm_identity[8];               /**< Primary clock UUID */
    bool as_capable;                      /**< IEEE 802.1AS capable */
    bool offset_in_range;                 /**< Clock offset in range */
    bool synced_to_primary_clock;         /**< Synced to primary clock */
    bool gm_changed;                      /**< Primary clock UUID changed */
    bool composite_event;                 /**< Composite event */
    int64_t  clock_offset;                /**< Clock offset */
    uint64_t notification_timestamp;      /**< Timestamp for last notification */
};

/** Event count for the events */
struct clkmgr_c_event_count {
    uint64_t event_count[CLKMGR_EVENT_MAX];
};

/** Pointer to the client structure */
typedef void *clkmgr_c_client_ptr;

/**
 * Create a new client instance
 * @return Pointer to the new client instance
 */
clkmgr_c_client_ptr clkmgr_c_client_create();

/**
 * Destroy a client instance
 * @param[in, out] client_ptr Pointer to the client instance
 */
void clkmgr_c_client_destroy(clkmgr_c_client_ptr client_ptr);

/**
 * Connect the client
 * @param[in, out] client_ptr Pointer to the client instance
 * @return true on success, false on failure
 */
bool clkmgr_c_connect(clkmgr_c_client_ptr client_ptr);

/**
 * Disconnect the client
 * @param[in, out] client_ptr Pointer to the client instance
 * @return true on success, false on failure
 */
bool clkmgr_c_disconnect(clkmgr_c_client_ptr client_ptr);

/**
 * Subscribe to client events
 * @param[in, out] client_ptr Pointer to the client instance
 * @param[in] sub Subscription structure
 * @param[out] current_state Pointer to the current state structure
 * @return true on success, false on failure
 */
bool clkmgr_c_subscribe(clkmgr_c_client_ptr client_ptr,
    struct clkmgr_c_subscription sub, struct clkmgr_c_state *current_state);

/**
 * Wait for client status
 * @param[in, out] client_ptr Pointer to the client instance
 * @param[in] timeout Timeout value in seconds
 * @param[out] current_state Pointer to the current state structure
 * @param[out] event_count Pointer to the event count structure
 * @return true if there is event changes within the timeout period,
 *         and false otherwise.
 */
int clkmgr_c_status_wait(clkmgr_c_client_ptr client_ptr, int timeout,
    struct clkmgr_c_state *current_state, struct clkmgr_c_event_count *event_count);

#ifdef __cplusplus
}
#endif

#endif /* CLKMGR_CLOCKMANAGER_C_H */
