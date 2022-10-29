/* SPDX-License-Identifier: GPL-3.0-or-later
   SPDX-FileCopyrightText: Copyright 2022 Erez Geva */

/** @file
 * @brief Verify PTP management TLV IDs unit test
 *
 * @author Erez Geva <ErezGeva2@@gmail.com>
 * @copyright 2022 Erez Geva
 *
 */

#include "msg.h"
#include "mngIds.h"

using namespace ptpmgmt;

class MngIDsTest : public ::testing::Test, public Message
{
  protected:
    BaseMngTlv b;
    MsgParams p;
    void SetUp() override {
        p = getParams();
    }
};

TEST_F(MngIDsTest, NULL_PTP_MANAGEMENT)
{
    EXPECT_TRUE(setAction(GET, NULL_PTP_MANAGEMENT));
    EXPECT_TRUE(setAction(SET, NULL_PTP_MANAGEMENT, &b));
    EXPECT_TRUE(setAction(COMMAND, NULL_PTP_MANAGEMENT));
}

TEST_F(MngIDsTest, CLOCK_DESCRIPTION)
{
    EXPECT_TRUE(setAction(GET, CLOCK_DESCRIPTION));
    CLOCK_DESCRIPTION_t t;
    EXPECT_FALSE(setAction(SET, CLOCK_DESCRIPTION, &t));
    EXPECT_FALSE(setAction(COMMAND, CLOCK_DESCRIPTION));
}

TEST_F(MngIDsTest, USER_DESCRIPTION)
{
    EXPECT_TRUE(setAction(GET, USER_DESCRIPTION));
    USER_DESCRIPTION_t t;
    EXPECT_TRUE(setAction(SET, USER_DESCRIPTION, &t));
    EXPECT_FALSE(setAction(COMMAND, USER_DESCRIPTION));
}

TEST_F(MngIDsTest, SAVE_IN_NON_VOLATILE_STORAGE)
{
    EXPECT_FALSE(setAction(GET, SAVE_IN_NON_VOLATILE_STORAGE));
    EXPECT_FALSE(setAction(SET, SAVE_IN_NON_VOLATILE_STORAGE, &b));
    EXPECT_TRUE(setAction(COMMAND, SAVE_IN_NON_VOLATILE_STORAGE));
}

TEST_F(MngIDsTest, RESET_NON_VOLATILE_STORAGE)
{
    EXPECT_FALSE(setAction(GET, RESET_NON_VOLATILE_STORAGE));
    EXPECT_FALSE(setAction(SET, RESET_NON_VOLATILE_STORAGE, &b));
    EXPECT_TRUE(setAction(COMMAND, RESET_NON_VOLATILE_STORAGE));
}

TEST_F(MngIDsTest, INITIALIZE)
{
    EXPECT_FALSE(setAction(GET, INITIALIZE));
    INITIALIZE_t t;
    EXPECT_FALSE(setAction(SET, INITIALIZE, &t));
    EXPECT_FALSE(setAction(COMMAND, INITIALIZE));
    EXPECT_TRUE(setAction(COMMAND, INITIALIZE, &t));
}

TEST_F(MngIDsTest, FAULT_LOG)
{
    EXPECT_TRUE(setAction(GET, FAULT_LOG));
    FAULT_LOG_t t;
    EXPECT_FALSE(setAction(SET, FAULT_LOG, &t));
    EXPECT_FALSE(setAction(COMMAND, FAULT_LOG));
}

TEST_F(MngIDsTest, FAULT_LOG_RESET)
{
    EXPECT_FALSE(setAction(GET, FAULT_LOG_RESET));
    EXPECT_FALSE(setAction(SET, FAULT_LOG_RESET, &b));
    EXPECT_TRUE(setAction(COMMAND, FAULT_LOG_RESET));
}

TEST_F(MngIDsTest, DEFAULT_DATA_SET)
{
    EXPECT_TRUE(setAction(GET, DEFAULT_DATA_SET));
    DEFAULT_DATA_SET_t t;
    EXPECT_FALSE(setAction(SET, DEFAULT_DATA_SET, &t));
    EXPECT_FALSE(setAction(COMMAND, DEFAULT_DATA_SET));
}

TEST_F(MngIDsTest, CURRENT_DATA_SET)
{
    EXPECT_TRUE(setAction(GET, CURRENT_DATA_SET));
    CURRENT_DATA_SET_t t;
    EXPECT_FALSE(setAction(SET, CURRENT_DATA_SET, &t));
    EXPECT_FALSE(setAction(COMMAND, CURRENT_DATA_SET));
}

TEST_F(MngIDsTest, PARENT_DATA_SET)
{
    EXPECT_TRUE(setAction(GET, PARENT_DATA_SET));
    PARENT_DATA_SET_t t;
    EXPECT_FALSE(setAction(SET, PARENT_DATA_SET, &t));
    EXPECT_FALSE(setAction(COMMAND, PARENT_DATA_SET));
}

TEST_F(MngIDsTest, TIME_PROPERTIES_DATA_SET)
{
    EXPECT_TRUE(setAction(GET, TIME_PROPERTIES_DATA_SET));
    TIME_PROPERTIES_DATA_SET_t t;
    EXPECT_FALSE(setAction(SET, TIME_PROPERTIES_DATA_SET, &t));
    EXPECT_FALSE(setAction(COMMAND, TIME_PROPERTIES_DATA_SET));
}

TEST_F(MngIDsTest, PORT_DATA_SET)
{
    EXPECT_TRUE(setAction(GET, PORT_DATA_SET));
    PORT_DATA_SET_t t;
    EXPECT_FALSE(setAction(SET, PORT_DATA_SET, &t));
    EXPECT_FALSE(setAction(COMMAND, PORT_DATA_SET));
}

TEST_F(MngIDsTest, PRIORITY1)
{
    EXPECT_TRUE(setAction(GET, PRIORITY1));
    PRIORITY1_t t;
    EXPECT_TRUE(setAction(SET, PRIORITY1, &t));
    EXPECT_FALSE(setAction(COMMAND, PRIORITY1));
}

TEST_F(MngIDsTest, PRIORITY2)
{
    EXPECT_TRUE(setAction(GET, PRIORITY2));
    PRIORITY2_t t;
    EXPECT_TRUE(setAction(SET, PRIORITY2, &t));
    EXPECT_FALSE(setAction(COMMAND, PRIORITY2));
}

TEST_F(MngIDsTest, DOMAIN)
{
    EXPECT_TRUE(setAction(GET, DOMAIN));
    DOMAIN_t t;
    EXPECT_TRUE(setAction(SET, DOMAIN, &t));
    EXPECT_FALSE(setAction(COMMAND, DOMAIN));
}

TEST_F(MngIDsTest, SLAVE_ONLY)
{
    EXPECT_TRUE(setAction(GET, SLAVE_ONLY));
    SLAVE_ONLY_t t;
    EXPECT_TRUE(setAction(SET, SLAVE_ONLY, &t));
    EXPECT_FALSE(setAction(COMMAND, SLAVE_ONLY));
}

TEST_F(MngIDsTest, LOG_ANNOUNCE_INTERVAL)
{
    EXPECT_TRUE(setAction(GET, LOG_ANNOUNCE_INTERVAL));
    LOG_ANNOUNCE_INTERVAL_t t;
    EXPECT_TRUE(setAction(SET, LOG_ANNOUNCE_INTERVAL, &t));
    EXPECT_FALSE(setAction(COMMAND, LOG_ANNOUNCE_INTERVAL));
}

TEST_F(MngIDsTest, ANNOUNCE_RECEIPT_TIMEOUT)
{
    EXPECT_TRUE(setAction(GET, ANNOUNCE_RECEIPT_TIMEOUT));
    ANNOUNCE_RECEIPT_TIMEOUT_t t;
    EXPECT_TRUE(setAction(SET, ANNOUNCE_RECEIPT_TIMEOUT, &t));
    EXPECT_FALSE(setAction(COMMAND, ANNOUNCE_RECEIPT_TIMEOUT));
}

TEST_F(MngIDsTest, LOG_SYNC_INTERVAL)
{
    EXPECT_TRUE(setAction(GET, LOG_SYNC_INTERVAL));
    LOG_SYNC_INTERVAL_t t;
    EXPECT_TRUE(setAction(SET, LOG_SYNC_INTERVAL, &t));
    EXPECT_FALSE(setAction(COMMAND, LOG_SYNC_INTERVAL));
}

TEST_F(MngIDsTest, VERSION_NUMBER)
{
    EXPECT_TRUE(setAction(GET, VERSION_NUMBER));
    VERSION_NUMBER_t t;
    EXPECT_TRUE(setAction(SET, VERSION_NUMBER, &t));
    EXPECT_FALSE(setAction(COMMAND, VERSION_NUMBER));
}

TEST_F(MngIDsTest, ENABLE_PORT)
{
    EXPECT_FALSE(setAction(GET, ENABLE_PORT));
    EXPECT_FALSE(setAction(SET, ENABLE_PORT, &b));
    EXPECT_TRUE(setAction(COMMAND, ENABLE_PORT));
}

TEST_F(MngIDsTest, DISABLE_PORT)
{
    EXPECT_FALSE(setAction(GET, DISABLE_PORT));
    EXPECT_FALSE(setAction(SET, DISABLE_PORT, &b));
    EXPECT_TRUE(setAction(COMMAND, DISABLE_PORT));
}

TEST_F(MngIDsTest, TIME)
{
    EXPECT_TRUE(setAction(GET, TIME));
    TIME_t t;
    EXPECT_TRUE(setAction(SET, TIME, &t));
    EXPECT_FALSE(setAction(COMMAND, TIME));
}

TEST_F(MngIDsTest, CLOCK_ACCURACY)
{
    EXPECT_TRUE(setAction(GET, CLOCK_ACCURACY));
    CLOCK_ACCURACY_t t;
    EXPECT_TRUE(setAction(SET, CLOCK_ACCURACY, &t));
    EXPECT_FALSE(setAction(COMMAND, CLOCK_ACCURACY));
}

TEST_F(MngIDsTest, UTC_PROPERTIES)
{
    EXPECT_TRUE(setAction(GET, UTC_PROPERTIES));
    UTC_PROPERTIES_t t;
    EXPECT_TRUE(setAction(SET, UTC_PROPERTIES, &t));
    EXPECT_FALSE(setAction(COMMAND, UTC_PROPERTIES));
}

TEST_F(MngIDsTest, TRACEABILITY_PROPERTIES)
{
    EXPECT_TRUE(setAction(GET, TRACEABILITY_PROPERTIES));
    TRACEABILITY_PROPERTIES_t t;
    EXPECT_TRUE(setAction(SET, TRACEABILITY_PROPERTIES, &t));
    EXPECT_FALSE(setAction(COMMAND, TRACEABILITY_PROPERTIES));
}

TEST_F(MngIDsTest, TIMESCALE_PROPERTIES)
{
    EXPECT_TRUE(setAction(GET, TIMESCALE_PROPERTIES));
    TIMESCALE_PROPERTIES_t t;
    EXPECT_TRUE(setAction(SET, TIMESCALE_PROPERTIES, &t));
    EXPECT_FALSE(setAction(COMMAND, TIMESCALE_PROPERTIES));
}

TEST_F(MngIDsTest, UNICAST_NEGOTIATION_ENABLE)
{
    EXPECT_TRUE(setAction(GET, UNICAST_NEGOTIATION_ENABLE));
    UNICAST_NEGOTIATION_ENABLE_t t;
    EXPECT_TRUE(setAction(SET, UNICAST_NEGOTIATION_ENABLE, &t));
    EXPECT_FALSE(setAction(COMMAND, UNICAST_NEGOTIATION_ENABLE));
}

TEST_F(MngIDsTest, PATH_TRACE_LIST)
{
    EXPECT_TRUE(setAction(GET, PATH_TRACE_LIST));
    PATH_TRACE_LIST_t t;
    EXPECT_FALSE(setAction(SET, PATH_TRACE_LIST, &t));
    EXPECT_FALSE(setAction(COMMAND, PATH_TRACE_LIST));
}

TEST_F(MngIDsTest, PATH_TRACE_ENABLE)
{
    EXPECT_TRUE(setAction(GET, PATH_TRACE_ENABLE));
    PATH_TRACE_ENABLE_t t;
    EXPECT_TRUE(setAction(SET, PATH_TRACE_ENABLE, &t));
    EXPECT_FALSE(setAction(COMMAND, PATH_TRACE_ENABLE));
}

TEST_F(MngIDsTest, GRANDMASTER_CLUSTER_TABLE)
{
    EXPECT_TRUE(setAction(GET, GRANDMASTER_CLUSTER_TABLE));
    GRANDMASTER_CLUSTER_TABLE_t t;
    EXPECT_TRUE(setAction(SET, GRANDMASTER_CLUSTER_TABLE, &t));
    EXPECT_FALSE(setAction(COMMAND, GRANDMASTER_CLUSTER_TABLE));
}

TEST_F(MngIDsTest, UNICAST_MASTER_TABLE)
{
    EXPECT_TRUE(setAction(GET, UNICAST_MASTER_TABLE));
    UNICAST_MASTER_TABLE_t t;
    EXPECT_TRUE(setAction(SET, UNICAST_MASTER_TABLE, &t));
    EXPECT_FALSE(setAction(COMMAND, UNICAST_MASTER_TABLE));
}

TEST_F(MngIDsTest, UNICAST_MASTER_MAX_TABLE_SIZE)
{
    EXPECT_TRUE(setAction(GET, UNICAST_MASTER_MAX_TABLE_SIZE));
    UNICAST_MASTER_MAX_TABLE_SIZE_t t;
    EXPECT_FALSE(setAction(SET, UNICAST_MASTER_MAX_TABLE_SIZE, &t));
    EXPECT_FALSE(setAction(COMMAND, UNICAST_MASTER_MAX_TABLE_SIZE));
}

TEST_F(MngIDsTest, ACCEPTABLE_MASTER_TABLE)
{
    EXPECT_TRUE(setAction(GET, ACCEPTABLE_MASTER_TABLE));
    ACCEPTABLE_MASTER_TABLE_t t;
    EXPECT_TRUE(setAction(SET, ACCEPTABLE_MASTER_TABLE, &t));
    EXPECT_FALSE(setAction(COMMAND, ACCEPTABLE_MASTER_TABLE));
}

TEST_F(MngIDsTest, ACCEPTABLE_MASTER_TABLE_ENABLED)
{
    EXPECT_TRUE(setAction(GET, ACCEPTABLE_MASTER_TABLE_ENABLED));
    ACCEPTABLE_MASTER_TABLE_ENABLED_t t;
    EXPECT_TRUE(setAction(SET, ACCEPTABLE_MASTER_TABLE_ENABLED, &t));
    EXPECT_FALSE(setAction(COMMAND, ACCEPTABLE_MASTER_TABLE_ENABLED));
}

TEST_F(MngIDsTest, ACCEPTABLE_MASTER_MAX_TABLE_SIZE)
{
    EXPECT_TRUE(setAction(GET, ACCEPTABLE_MASTER_MAX_TABLE_SIZE));
    ACCEPTABLE_MASTER_MAX_TABLE_SIZE_t t;
    EXPECT_FALSE(setAction(SET, ACCEPTABLE_MASTER_MAX_TABLE_SIZE, &t));
    EXPECT_FALSE(setAction(COMMAND, ACCEPTABLE_MASTER_MAX_TABLE_SIZE));
}

TEST_F(MngIDsTest, ALTERNATE_MASTER)
{
    EXPECT_TRUE(setAction(GET, ALTERNATE_MASTER));
    ALTERNATE_MASTER_t t;
    EXPECT_TRUE(setAction(SET, ALTERNATE_MASTER, &t));
    EXPECT_FALSE(setAction(COMMAND, ALTERNATE_MASTER));
}

TEST_F(MngIDsTest, ALTERNATE_TIME_OFFSET_ENABLE)
{
    EXPECT_TRUE(setAction(GET, ALTERNATE_TIME_OFFSET_ENABLE));
    ALTERNATE_TIME_OFFSET_ENABLE_t t;
    EXPECT_TRUE(setAction(SET, ALTERNATE_TIME_OFFSET_ENABLE, &t));
    EXPECT_FALSE(setAction(COMMAND, ALTERNATE_TIME_OFFSET_ENABLE));
}

TEST_F(MngIDsTest, ALTERNATE_TIME_OFFSET_NAME)
{
    EXPECT_TRUE(setAction(GET, ALTERNATE_TIME_OFFSET_NAME));
    ALTERNATE_TIME_OFFSET_NAME_t t;
    EXPECT_TRUE(setAction(SET, ALTERNATE_TIME_OFFSET_NAME, &t));
    EXPECT_FALSE(setAction(COMMAND, ALTERNATE_TIME_OFFSET_NAME));
}

TEST_F(MngIDsTest, ALTERNATE_TIME_OFFSET_MAX_KEY)
{
    EXPECT_TRUE(setAction(GET, ALTERNATE_TIME_OFFSET_MAX_KEY));
    ALTERNATE_TIME_OFFSET_MAX_KEY_t t;
    EXPECT_FALSE(setAction(SET, ALTERNATE_TIME_OFFSET_MAX_KEY, &t));
    EXPECT_FALSE(setAction(COMMAND, ALTERNATE_TIME_OFFSET_MAX_KEY));
}

TEST_F(MngIDsTest, ALTERNATE_TIME_OFFSET_PROPERTIES)
{
    EXPECT_TRUE(setAction(GET, ALTERNATE_TIME_OFFSET_PROPERTIES));
    ALTERNATE_TIME_OFFSET_PROPERTIES_t t;
    EXPECT_TRUE(setAction(SET, ALTERNATE_TIME_OFFSET_PROPERTIES, &t));
    EXPECT_FALSE(setAction(COMMAND, ALTERNATE_TIME_OFFSET_PROPERTIES));
}

TEST_F(MngIDsTest, TRANSPARENT_CLOCK_PORT_DATA_SET)
{
    EXPECT_TRUE(setAction(GET, TRANSPARENT_CLOCK_PORT_DATA_SET));
    TRANSPARENT_CLOCK_PORT_DATA_SET_t t;
    EXPECT_FALSE(setAction(SET, TRANSPARENT_CLOCK_PORT_DATA_SET, &t));
    EXPECT_FALSE(setAction(COMMAND, TRANSPARENT_CLOCK_PORT_DATA_SET));
}

TEST_F(MngIDsTest, LOG_MIN_PDELAY_REQ_INTERVAL)
{
    EXPECT_TRUE(setAction(GET, LOG_MIN_PDELAY_REQ_INTERVAL));
    LOG_MIN_PDELAY_REQ_INTERVAL_t t;
    EXPECT_TRUE(setAction(SET, LOG_MIN_PDELAY_REQ_INTERVAL, &t));
    EXPECT_FALSE(setAction(COMMAND, LOG_MIN_PDELAY_REQ_INTERVAL));
}

TEST_F(MngIDsTest, TRANSPARENT_CLOCK_DEFAULT_DATA_SET)
{
    EXPECT_TRUE(setAction(GET, TRANSPARENT_CLOCK_DEFAULT_DATA_SET));
    TRANSPARENT_CLOCK_DEFAULT_DATA_SET_t t;
    EXPECT_FALSE(setAction(SET, TRANSPARENT_CLOCK_DEFAULT_DATA_SET, &t));
    EXPECT_FALSE(setAction(COMMAND, TRANSPARENT_CLOCK_DEFAULT_DATA_SET));
}

TEST_F(MngIDsTest, PRIMARY_DOMAIN)
{
    EXPECT_TRUE(setAction(GET, PRIMARY_DOMAIN));
    PRIMARY_DOMAIN_t t;
    EXPECT_TRUE(setAction(SET, PRIMARY_DOMAIN, &t));
    EXPECT_FALSE(setAction(COMMAND, PRIMARY_DOMAIN));
}

TEST_F(MngIDsTest, DELAY_MECHANISM)
{
    EXPECT_TRUE(setAction(GET, DELAY_MECHANISM));
    DELAY_MECHANISM_t t;
    EXPECT_TRUE(setAction(SET, DELAY_MECHANISM, &t));
    EXPECT_FALSE(setAction(COMMAND, DELAY_MECHANISM));
}

TEST_F(MngIDsTest, EXTERNAL_PORT_CONFIGURATION_ENABLED)
{
    EXPECT_TRUE(setAction(GET, EXTERNAL_PORT_CONFIGURATION_ENABLED));
    EXTERNAL_PORT_CONFIGURATION_ENABLED_t t;
    EXPECT_TRUE(setAction(SET, EXTERNAL_PORT_CONFIGURATION_ENABLED, &t));
    EXPECT_FALSE(setAction(COMMAND, EXTERNAL_PORT_CONFIGURATION_ENABLED));
}

TEST_F(MngIDsTest, MASTER_ONLY)
{
    EXPECT_TRUE(setAction(GET, MASTER_ONLY));
    MASTER_ONLY_t t;
    EXPECT_TRUE(setAction(SET, MASTER_ONLY, &t));
    EXPECT_FALSE(setAction(COMMAND, MASTER_ONLY));
}

TEST_F(MngIDsTest, HOLDOVER_UPGRADE_ENABLE)
{
    EXPECT_TRUE(setAction(GET, HOLDOVER_UPGRADE_ENABLE));
    HOLDOVER_UPGRADE_ENABLE_t t;
    EXPECT_TRUE(setAction(SET, HOLDOVER_UPGRADE_ENABLE, &t));
    EXPECT_FALSE(setAction(COMMAND, HOLDOVER_UPGRADE_ENABLE));
}

TEST_F(MngIDsTest, EXT_PORT_CONFIG_PORT_DATA_SET)
{
    EXPECT_TRUE(setAction(GET, EXT_PORT_CONFIG_PORT_DATA_SET));
    EXT_PORT_CONFIG_PORT_DATA_SET_t t;
    EXPECT_TRUE(setAction(SET, EXT_PORT_CONFIG_PORT_DATA_SET, &t));
    EXPECT_FALSE(setAction(COMMAND, EXT_PORT_CONFIG_PORT_DATA_SET));
}

TEST_F(MngIDsTest, TIME_STATUS_NP)
{
    EXPECT_TRUE(setAction(GET, TIME_STATUS_NP));
    TIME_STATUS_NP_t t;
    EXPECT_FALSE(setAction(SET, TIME_STATUS_NP, &t));
    EXPECT_FALSE(setAction(COMMAND, TIME_STATUS_NP));
    p.implementSpecific = noImplementSpecific;
    updateParams(p);
    EXPECT_FALSE(setAction(GET, TIME_STATUS_NP));
    EXPECT_FALSE(setAction(SET, TIME_STATUS_NP, &t));
    EXPECT_FALSE(setAction(COMMAND, TIME_STATUS_NP));
}

TEST_F(MngIDsTest, GRANDMASTER_SETTINGS_NP)
{
    EXPECT_TRUE(setAction(GET, GRANDMASTER_SETTINGS_NP));
    GRANDMASTER_SETTINGS_NP_t t;
    EXPECT_TRUE(setAction(SET, GRANDMASTER_SETTINGS_NP, &t));
    EXPECT_FALSE(setAction(COMMAND, GRANDMASTER_SETTINGS_NP));
    p.implementSpecific = noImplementSpecific;
    updateParams(p);
    EXPECT_FALSE(setAction(GET, GRANDMASTER_SETTINGS_NP));
    EXPECT_FALSE(setAction(SET, GRANDMASTER_SETTINGS_NP, &t));
    EXPECT_FALSE(setAction(COMMAND, GRANDMASTER_SETTINGS_NP));
}

TEST_F(MngIDsTest, PORT_DATA_SET_NP)
{
    EXPECT_TRUE(setAction(GET, PORT_DATA_SET_NP));
    PORT_DATA_SET_NP_t t;
    EXPECT_TRUE(setAction(SET, PORT_DATA_SET_NP, &t));
    EXPECT_FALSE(setAction(COMMAND, PORT_DATA_SET_NP));
    p.implementSpecific = noImplementSpecific;
    updateParams(p);
    EXPECT_FALSE(setAction(GET, PORT_DATA_SET_NP));
    EXPECT_FALSE(setAction(SET, PORT_DATA_SET_NP, &t));
    EXPECT_FALSE(setAction(COMMAND, PORT_DATA_SET_NP));
}

TEST_F(MngIDsTest, SUBSCRIBE_EVENTS_NP)
{
    EXPECT_TRUE(setAction(GET, SUBSCRIBE_EVENTS_NP));
    SUBSCRIBE_EVENTS_NP_t t;
    EXPECT_TRUE(setAction(SET, SUBSCRIBE_EVENTS_NP, &t));
    EXPECT_FALSE(setAction(COMMAND, SUBSCRIBE_EVENTS_NP));
    p.implementSpecific = noImplementSpecific;
    updateParams(p);
    EXPECT_FALSE(setAction(GET, SUBSCRIBE_EVENTS_NP));
    EXPECT_FALSE(setAction(SET, SUBSCRIBE_EVENTS_NP, &t));
    EXPECT_FALSE(setAction(COMMAND, SUBSCRIBE_EVENTS_NP));
}

TEST_F(MngIDsTest, PORT_PROPERTIES_NP)
{
    EXPECT_TRUE(setAction(GET, PORT_PROPERTIES_NP));
    PORT_PROPERTIES_NP_t t;
    EXPECT_FALSE(setAction(SET, PORT_PROPERTIES_NP, &t));
    EXPECT_FALSE(setAction(COMMAND, PORT_PROPERTIES_NP));
    p.implementSpecific = noImplementSpecific;
    updateParams(p);
    EXPECT_FALSE(setAction(GET, PORT_PROPERTIES_NP));
    EXPECT_FALSE(setAction(SET, PORT_PROPERTIES_NP, &t));
    EXPECT_FALSE(setAction(COMMAND, PORT_PROPERTIES_NP));
}

TEST_F(MngIDsTest, PORT_STATS_NP)
{
    EXPECT_TRUE(setAction(GET, PORT_STATS_NP));
    PORT_STATS_NP_t t;
    EXPECT_FALSE(setAction(SET, PORT_STATS_NP, &t));
    EXPECT_FALSE(setAction(COMMAND, PORT_STATS_NP));
    p.implementSpecific = noImplementSpecific;
    updateParams(p);
    EXPECT_FALSE(setAction(GET, PORT_STATS_NP));
    EXPECT_FALSE(setAction(SET, PORT_STATS_NP, &t));
    EXPECT_FALSE(setAction(COMMAND, PORT_STATS_NP));
}

TEST_F(MngIDsTest, SYNCHRONIZATION_UNCERTAIN_NP)
{
    EXPECT_TRUE(setAction(GET, SYNCHRONIZATION_UNCERTAIN_NP));
    SYNCHRONIZATION_UNCERTAIN_NP_t t;
    EXPECT_TRUE(setAction(SET, SYNCHRONIZATION_UNCERTAIN_NP, &t));
    EXPECT_FALSE(setAction(COMMAND, SYNCHRONIZATION_UNCERTAIN_NP));
    p.implementSpecific = noImplementSpecific;
    updateParams(p);
    EXPECT_FALSE(setAction(GET, SYNCHRONIZATION_UNCERTAIN_NP));
    EXPECT_FALSE(setAction(SET, SYNCHRONIZATION_UNCERTAIN_NP, &t));
    EXPECT_FALSE(setAction(COMMAND, SYNCHRONIZATION_UNCERTAIN_NP));
}

TEST_F(MngIDsTest, PORT_SERVICE_STATS_NP)
{
    EXPECT_TRUE(setAction(GET, PORT_SERVICE_STATS_NP));
    PORT_SERVICE_STATS_NP_t t;
    EXPECT_FALSE(setAction(SET, PORT_SERVICE_STATS_NP, &t));
    EXPECT_FALSE(setAction(COMMAND, PORT_SERVICE_STATS_NP));
    p.implementSpecific = noImplementSpecific;
    updateParams(p);
    EXPECT_FALSE(setAction(GET, PORT_SERVICE_STATS_NP));
    EXPECT_FALSE(setAction(SET, PORT_SERVICE_STATS_NP, &t));
    EXPECT_FALSE(setAction(COMMAND, PORT_SERVICE_STATS_NP));
}

TEST_F(MngIDsTest, UNICAST_MASTER_TABLE_NP)
{
    EXPECT_TRUE(setAction(GET, UNICAST_MASTER_TABLE_NP));
    UNICAST_MASTER_TABLE_NP_t t;
    EXPECT_FALSE(setAction(SET, UNICAST_MASTER_TABLE_NP, &t));
    EXPECT_FALSE(setAction(COMMAND, UNICAST_MASTER_TABLE_NP));
    p.implementSpecific = noImplementSpecific;
    updateParams(p);
    EXPECT_FALSE(setAction(GET, UNICAST_MASTER_TABLE_NP));
    EXPECT_FALSE(setAction(SET, UNICAST_MASTER_TABLE_NP, &t));
    EXPECT_FALSE(setAction(COMMAND, UNICAST_MASTER_TABLE_NP));
}

TEST_F(MngIDsTest, PORT_HWCLOCK_NP)
{
    EXPECT_TRUE(setAction(GET, PORT_HWCLOCK_NP));
    PORT_HWCLOCK_NP_t t;
    EXPECT_FALSE(setAction(SET, PORT_HWCLOCK_NP, &t));
    EXPECT_FALSE(setAction(COMMAND, PORT_HWCLOCK_NP));
    p.implementSpecific = noImplementSpecific;
    updateParams(p);
    EXPECT_FALSE(setAction(GET, PORT_HWCLOCK_NP));
    EXPECT_FALSE(setAction(SET, PORT_HWCLOCK_NP, &t));
    EXPECT_FALSE(setAction(COMMAND, PORT_HWCLOCK_NP));
}
