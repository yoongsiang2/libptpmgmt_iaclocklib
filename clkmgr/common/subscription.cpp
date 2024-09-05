/*
 * SPDX-License-Identifier: BSD-3-Clause
 * SPDX-FileCopyrightText: Copyright © 2024 Intel Corporation.
 */

/** @file subscription.cpp
 * @brief PTP event subscription.
 *
 * @author Christopher Hall <christopher.s.hall@intel.com>
 * @copyright © 2024 Intel Corporation.
 * @license BSD-3-Clause
 *
 */

#include <cstring>

#include <clkmgr/subscription.h>
#include <common/print.hpp>
#include <common/serialize.hpp>

__CLKMGR_NAMESPACE_USE

using namespace std;

clkmgr_value::value_t::value_t()
{
    upper = 0;
    lower = 0;
}

clkmgr_value::value_t::value_t(uint32_t limit)
{
    upper = limit;
    lower = limit;
}

bool clkmgr_value::value_t::equal(const value_t &v)
{
    if(this->upper == v.upper && this->lower == v.lower)
        return true;
    return false;
}

uint8_t *clkmgr_value::parse(uint8_t *buf, std::size_t &length)
{
    return buf;
}

uint8_t *clkmgr_value::write(uint8_t *buf, std::size_t &length)
{
    for(size_t i = 0; i < sizeof(value) / sizeof(value[0]) && buf != nullptr; ++i)
        buf += WRITE_FIELD(value[i], buf, length);
    for(size_t i = 0; i < sizeof(reserved) / sizeof(reserved[0]) &&
        buf != nullptr; ++i)
        reserved[i].zero();
    return buf;
}

bool clkmgr_value::equal(const clkmgr_value &c)
{
    if(memcmp(this->value, c.value, sizeof(this->value)) == 0)
        return true;
    return false;
}

uint8_t *clkmgr_eventcount::parse(uint8_t *buf, std::size_t &length)
{
    return buf;
}

uint8_t *clkmgr_eventcount::write(uint8_t *buf, std::size_t &length)
{
    for(size_t i = 0; i < sizeof(count) / sizeof(count[0]) && buf != nullptr; ++i)
        buf += WRITE_FIELD(count[i], buf, length);
    memset(reserved, 0, sizeof(reserved));
    return buf;
}

void clkmgr_eventcount::zero()
{
    for(size_t i = 0; i < sizeof(count) / sizeof(count[0]); ++i)
        count[i] = 0;
    memset(reserved, 0, sizeof(reserved));
}

bool clkmgr_eventcount::equal(const clkmgr_eventcount &ec)
{
    if(memcmp(this->count, ec.count, sizeof(this->count)) == 0)
        return true;
    return false;
}

std::string clkmgr_value::toString()
{
    std::string name = "clkmgr_value : upper " + to_string(this->value->upper) +
        " lower : " +  to_string(this->value->lower) + "\n";
    return name;
}
