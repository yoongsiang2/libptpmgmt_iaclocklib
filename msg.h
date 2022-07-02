/* SPDX-License-Identifier: LGPL-3.0-or-later
   SPDX-FileCopyrightText: Copyright 2021 Erez Geva */

/** @file
 * @brief Create and parse PTP management messages
 *
 * @author Erez Geva <ErezGeva2@@gmail.com>
 * @copyright 2021 Erez Geva
 *
 * Created following @"IEEE Std 1588-2008@", PTP version 2
 * with some updates from @"IEEE Std 1588-2019@"
 */

#ifndef __PTPMGMT_MSG_H
#define __PTPMGMT_MSG_H

#include <string>
#include <cstdint>
#include <cstring>
#include <cstdio>
#include <vector>
#include <functional>
#include "cfg.h"
#include "buf.h"
#include "proc.h"
#include "sig.h"

#ifndef SWIG
namespace ptpmgmt
{
#endif

struct MsgProc;

/**
 * @brief Handle PTP management message
 * @details
 *  Handle parse and build of a PTP management massage.
 *  Handle TLV specific dataField by calling a specific call-back per TLV id
 */
class Message
{
    /** @cond internal
     * Doxygen does not know how to proccess.
     * This is a private section any way.
     */
  private:

    #ifndef SWIG
    /**
     * hold single TLV from a signaling message
     * Used internaly
     */
    struct sigTlv {
        tlvType_e tlvType;
        /**
         * As we use a vector of this structure,
         * And we do not want the vector to pass the sig-tlv pointer or copy it.
         * We do not pass the sig-tlv pointer in copy and assignment functions.
         * We pass the sig-tlv pointer directly
         *  afer we insert a new item to the vector!
         * We only copy the type value here.
         */
        sigTlv(tlvType_e type) : tlvType(type) {}
        sigTlv(const sigTlv &rhs) : tlvType(rhs.tlvType) {}
        sigTlv &operator=(const sigTlv &rhs) {
            tlvType = rhs.tlvType;
            return *this;
        }
        const BaseSigTlv *get() const { return tlv.get(); }
        void set(BaseSigTlv *t) { tlv.reset(t); }
      private:
        std::unique_ptr<BaseSigTlv> tlv;
    };
    #endif /* SWIG */

    /**< @endcond */

    /* build parameters */
    actionField_e     m_sendAction;
    size_t            m_msgLen;
    const BaseMngTlv *m_dataSend;

    /* parsing parameters */
    uint16_t          m_sequence;
    bool              m_isUnicast;
    uint8_t           m_PTPProfileSpecific;
    actionField_e     m_replyAction;
    uint32_t          m_sdoId; /* parsed message sdoId (transportSpecific) */
    msgType_e         m_type; /* parsed message type */
    tlvType_e         m_mngType; /* parsed management message type */
    uint8_t           m_domainNumber; /* parsed message domainNumber*/
    uint8_t           m_versionPTP; /* parsed message ptp version */
    uint8_t           m_minorVersionPTP; /* parsed message ptp version */
    std::vector<sigTlv> m_sigTlvs; /* hold signaling TLVs */
    std::unique_ptr<BaseMngTlv> m_dataGet;

    /* Generic */
    mng_vals_e        m_tlv_id; /* managementId */
    MsgParams         m_prms;

    /* parsing parameters */
    PortIdentity_t    m_peer; /* parsed message peer port id */
    PortIdentity_t    m_target; /* parsed message target port id */

    /* For error messages */
    managementErrorId_e m_errorId;
    PTPText_t m_errorDisplay;

    /* Map to all management IDs */
    static const ManagementId_t mng_all_vals[];

    bool allowedAction(mng_vals_e id, actionField_e action);
    /* val in network order */
    static bool findTlvId(uint16_t val, mng_vals_e &rid, implementSpecific_e spec);
    bool checkReplyAction(uint8_t actionField);
    MNG_PARSE_ERROR_e parseSig(MsgProc *); /* parse signaling message */
    /*
     * dataFieldSize() for sending SET/COMMAND
     * Get dataField of current m_tlv_id
     * For id with non fixed size
     * The size is determined by the m_dataSend content
     */
    ssize_t dataFieldSize(const BaseMngTlv *data) const;

  public:
    Message();
    /**
     * Construct a new object using the user MsgParams parameters
     * @param[in] prms MsgParams parameters
     * @note you may use the parameters from a different message object
     */
    Message(const MsgParams &prms);
    /**
     * Get the current msgparams parameters
     * @return msgparams parameters
     */
    const MsgParams &getParams() const { return m_prms; }
    /**
     * Set and use a user MsgParams parameters
     * @param[in] prms MsgParams parameters
     * @return true if parameters are valid and updated
     */
    bool updateParams(const MsgParams &prms);
    /**
     * Get the current TLV id
     * @return current TLV id
     * @note the message object holds a single value from the last setting or
     *  reply parsing.
     */
    mng_vals_e getTlvId() const { return m_tlv_id; }
    /**
     * Set target clock ID to use all clocks.
     */
    void setAllClocks();
    /**
     * Query if target clock ID is using all clocks.
     * @return true if target use all clocks
     */
    bool isAllClocks() const;
    /**
     * Fetch MsgParams parameters from configuration file
     * @param[in] cfg reference to configuration file object
     * @param[in] section in configuration file
     * @return true on success
     * @note calling without section will fetch value from @"global@" section
     */
    bool useConfig(const ConfigFile &cfg, const std::string &section = "");
    /**
     * Convert parse error code to string
     * @param[in] err parse code
     * @return string with the error message
     */
    static const char *err2str_c(MNG_PARSE_ERROR_e err);

    /**
     * Convert message type to string
     * @param[in] type
     * @return string with the TLV type
     */
    static const char *type2str_c(msgType_e type);
    /**
     * Convert TLV type to string
     * @param[in] type
     * @return string with the TLV type
     */
    static const char *tlv2str_c(tlvType_e type);
    /**
     * Convert action to string
     * @param[in] action
     * @return string with the action in a string
     */
    static const char *act2str_c(actionField_e action);
    /**
     * Convert management id to string
     * @param[in] id parse code
     * @return string with ID name
     */
    static const char *mng2str_c(mng_vals_e id);
    /**
     * Convert string to management id
     * @param[in] str string to search
     * @param[out] id parse code
     * @param[in] exact perform an exact match
     * @return true if found
     */
    static const bool findMngID(const std::string &str, mng_vals_e &id,
        bool exact = true);
    /**
     * Convert management error to string
     * @param[in] err ID
     * @return string with the error message
     */
    static const char *errId2str_c(managementErrorId_e err);
    /**
     * Convert clock type to string
     * @param[in] type clock type
     * @return string with the clock type
     */
    static const char *clkType2str_c(clockType_e type);
    /**
     * Convert network protocol to string
     * @param[in] protocol network protocol
     * @return string with the network protocol
     */
    static const char *netProt2str_c(networkProtocol_e protocol);
    /**
     * Convert clock accuracy to string
     * @param[in] value clock accuracy
     * @return string with the clock accuracy
     */
    static const char *clockAcc2str_c(clockAccuracy_e value);
    /**
     * Convert fault record severity code to string
     * @param[in] code severity code
     * @return string with the severity code
     */
    static const char *faultRec2str_c(faultRecord_e code);
    /**
     * Convert time source to string
     * @param[in] type time source
     * @return string with the time source
     */
    static const char *timeSrc2str_c(timeSource_e type);
    /**
     * Convert string to time source type
     * @param[in] str string to search
     * @param[out] type time source
     * @param[in] exact perform an exact match
     * @return true if found
     */
    static const bool findTimeSrc(const std::string &str, timeSource_e &type,
        bool exact = true);
    /**
     * Convert port state to string
     * @param[in] state port state
     * @return string with the port state
     */
    static const char *portState2str_c(portState_e state);
    /**
     * Convert string to port state
     * @param[in] str string to search
     * @param[out] state port state
     * @param[in] caseSens perform case sensetive match
     * @return true if found
     */
    static const bool findPortState(const std::string &str, portState_e &state,
        bool caseSens = true);
    /**
     * Convert linuxptp time stamp type to string
     * @param[in] type time stamp type
     * @return string with the Linux time stamp type
     */
    static const char *ts2str_c(linuxptpTimeStamp_e type);
    /**
     * Convert linuxptp power profile version to string
     * @param[in] ver version
     * @return string with the Linux power profile version
     */
    static const char *pwr2str_c(linuxptpPowerProfileVersion_e ver);
    /**
     * Convert linuxptp master unicasy state to string
     * @param[in] state
     * @return string with the master state in the unicast master table
     */
    static const char *us2str_c(linuxptpUnicastState_e state);
    /**
     * Check if leap 61 seconds flag is enabled
     * @param[in] flags
     * @return 1 if flag on or 0 if not
     */
    static uint8_t is_LI_61(uint8_t flags) { return flags & F_LI_61 ? 1 : 0; }
    /**
     * Check if leap 59 seconds flag is enabled
     * @param[in] flags
     * @return 1 if flag on or 0 if not
     */
    static uint8_t is_LI_59(uint8_t flags) { return flags & F_LI_59 ? 1 : 0; }
    /**
     * Check if UTC offset is valid flag is enabled
     * @param[in] flags
     * @return 1 if flag on or 0 if not
     */
    static uint8_t is_UTCV(uint8_t flags)  { return flags & F_UTCV  ? 1 : 0; }
    /**
     * Check if is PTP instance flag is enabled
     * @param[in] flags
     * @return 1 if flag on or 0 if not
     */
    static uint8_t is_PTP(uint8_t flags)   { return flags & F_PTP   ? 1 : 0; }
    /**
     * Check if timescale is traceable flag is enabled
     * @param[in] flags
     * @return 1 if flag on or 0 if not
     */
    static uint8_t is_TTRA(uint8_t flags)  { return flags & F_TTRA  ? 1 : 0; }
    /**
     * Check if frequency is traceable flag is enabled
     * @param[in] flags
     * @return 1 if flag on or 0 if not
     */
    static uint8_t is_FTRA(uint8_t flags)  { return flags & F_FTRA  ? 1 : 0; }
    /**
     * Check management TLV id uses empty dataField
     * @param[in] id management TLV id
     * @return true if dataField is empty
     */
    static bool isEmpty(mng_vals_e id);
    /**
     * Check if management TLV is valid for use
     * @param[in] id management TLV id
     * @return true if management TLV is valid
     * @note function also check implement specific TLVs!
     */
    bool isValidId(mng_vals_e id);
    /**
     * Set message object management TLV id, action and data for dataField
     * @param[in] actionField for sending
     * @param[in] tlv_id management TLV id
     * @param[in] dataSend pointer to TLV object
     * @return true if setting is correct
     * @note the setting is valid for send only
     * @attention
     *  The caller must use the proper structure with the TLV id!
     *  Mismatch will probably cause a crash to your application.
     *  The library does @b NOT perform any error catchig of any kind!
     */
    bool setAction(actionField_e actionField, mng_vals_e tlv_id,
        const BaseMngTlv *dataSend = nullptr);
    /**
     * Clear data for send, prevent accidentally use, in case it is freed
     */
    void clearData();
    /**
     * Build a raw message for send using setAction setting
     * @param[in, out] buf memory buffer to fill with raw PTP Message
     * @param[in] bufSize buffer size
     * @param[in] sequence message sequence
     * @return parse error state
     * @note build before setting with setAction will create a GET raw message
     *  with NULL_PTP_MANAGEMENT management TLV
     * @note usually the user increases the sequence so it can be compared
     *  with replied message
     * @note if raw message is larger than buffer size the function
     *   return MNG_PARSE_ERROR_TOO_SMALL
     */
    MNG_PARSE_ERROR_e build(void *buf, size_t bufSize, uint16_t sequence);
    /**
     * Build a raw message for send based on last setAction call
     * @param[in, out] buf object with memory buffer to fill with raw PTP Message
     * @param[in] sequence message sequence
     * @return parse error state
     * @note build before setting with setAction will create a GET raw message
     *  with NULL_PTP_MANAGEMENT management TLV
     * @note usually the user increases the sequence so it can be compared
     *  with replied message
     * @note if raw message is larger than buffer size the function
     *   return MNG_PARSE_ERROR_TOO_SMALL
     */
    MNG_PARSE_ERROR_e build(Buf &buf, uint16_t sequence)
    { return build(buf.get(), buf.size(), sequence); }
    /**
     * Get build management action
     * @return build management action
     */
    actionField_e getSendAction() const { return m_sendAction; }
    /**
     * Get last build message size
     * @return message size
     */
    size_t getMsgLen() const { return m_msgLen; }
    /**
     * Get planned message to build size
     * @return planned message size or negative for error
     * @note the planned message size is based on the management TLV id,
     *  action and the dataSend set by the user.
     * User can use the size to allocate proper buffer for sending
     */
    ssize_t getMsgPlanedLen() const;
    /* Parsed message functions */
    /**
     * Parse a received raw socket
     * @param[in] buf memory buffer containing the raw PTP Message
     * @param[in] msgSize received size of PTP Message
     * @return parse error state
     */
    MNG_PARSE_ERROR_e parse(const void *buf, ssize_t msgSize);
    /**
     * Parse a received raw socket
     * @param[in] buf object with memory buffer containing the raw PTP Message
     * @param[in] msgSize received size of PTP Message
     * @return parse error state
     */
    MNG_PARSE_ERROR_e parse(const Buf &buf, ssize_t msgSize);
    /**
     * Get last reply management action
     * @return reply management action
     * @note set on parse
     */
    actionField_e getReplyAction() const { return m_replyAction; }
    /**
     * Is last parsed message a unicast or not
     * @return true if parsed message is unicast
     */
    bool isUnicast() const { return m_isUnicast; }
    /**
     * Get last reply PTP Profile Specific
     * @return reply management action
     * @note set on parse
     */
    uint8_t getPTPProfileSpecific() const { return m_PTPProfileSpecific; }
    /**
     * Get last parsed message sequence number
     * @return parsed sequence number
     */
    uint16_t getSequence() const { return m_sequence; }
    /**
     * Get last parsed message peer port ID
     * @return parsed message peer port ID
     */
    const PortIdentity_t &getPeer() const { return m_peer; }
    /**
     * Get last parsed message target port ID
     * @return parsed message target port ID
     */
    const PortIdentity_t &getTarget() const { return m_target; }
    /**
     * Get last parsed message sdoId
     * @return parsed message sdoId
     * @note upper byte is was transportSpecific
     */
    uint32_t getSdoId() const { return m_sdoId; }
    /**
     * Get last parsed message domainNumber
     * @return parsed message domainNumber
     */
    uint8_t getDomainNumber() const { return m_domainNumber; }
    /**
     * Get last parsed message PTP version
     * @return parsed message versionPTP
     */
    uint8_t getVersionPTP() const { return m_versionPTP; }
    /**
     * Get last parsed message minor PTP version
     * @return parsed message versionPTP
     */
    uint8_t getMinorVersionPTP() const { return m_minorVersionPTP; }
    /**
     * Get last parsed message dataField
     * @return pointer to last parsed message dataField or null
     * @note User need to cast to proper structure depends on
     *  management TLV ID.
     * @note User @b should not try to free this TLV object
     */
    const BaseMngTlv *getData() const { return m_dataGet.get(); }
    /**
     * Get management error code ID
     * Relevant only when parsed message return MNG_PARSE_ERROR_MSG
     * @return error code
     */
    managementErrorId_e getErrId() const { return m_errorId; }
    /**
     * Get management error message
     * Relevant only when parsed message return MNG_PARSE_ERROR_MSG
     * @return error message
     */
    const std::string &getErrDisplay() const { return m_errorDisplay.textField; }
    /**
     * Get management error message
     * Relevant only when parsed message return MNG_PARSE_ERROR_MSG
     * @return error message
     */
    const char *getErrDisplay_c() const { return m_errorDisplay.string(); }
    /**
     * query if last message is a signaling message
     * @return true if last message is a signaling message
     */
    bool isLastMsgSig() const { return m_type == Signaling; }
    /**
     * Get message type
     * @return message type
     */
    msgType_e getType() const { return m_type; }
    /**
     * Get management message type
     * @return management message type
     * @note return MANAGEMENT or MANAGEMENT_ERROR_STATUS
     */
    tlvType_e getMngType() const { return m_mngType; }
    /**
     * Traverse all last signaling message TLVs
     * @param[in] callback function to call with each TLV
     * @return true if any of the calling to call-back return true
     * @note stop if any of the calling to call-back return true
     * @note if scripting can not provide C++ call-back
     *  it may use the function bellow
     */
    bool traversSigTlvs(const std::function<bool (const Message &msg,
            tlvType_e tlvType, const BaseSigTlv *tlv)> callback) const;
    /**
     * Get number of the last signaling message TLVs
     * @return number of TLVs or zero
     * @note this function is for scripting, normal C++ can use traversSigTlvs
     */
    size_t getSigTlvsCount() const;
    /**
     * Get a TLV from the last signaling message TLVs by position
     * @param[in] position of TLV
     * @return TLV or null
     * @note this function is for scripting, normal C++ can use traversSigTlvs
     */
    const BaseSigTlv *getSigTlv(size_t position) const;
    /**
     * Get a type of TLV from the last signaling message TLVs by position
     * @param[in] position of TLV
     * @return type of TLV or unknown
     * @note this function is for scripting, normal C++ can use traversSigTlvs
     */
    tlvType_e getSigTlvType(size_t position) const;
    /**
     * Get the management TLV ID of a management TLV
     * from the last signaling message TLVs by position
     * @param[in] position of TLV
     * @return management TLV ID or NULL_PTP_MANAGEMENT
     * @note return NULL_PTP_MANAGEMENT if TLV is not management
     * @note this function is for scripting, normal C++ can just cast
     */
    mng_vals_e getSigMngTlvType(size_t position) const;
    /**
     * Get a management TLV from the last signaling message TLVs by position
     * @param[in] position of TLV
     * @return management TLV or null
     * @note return null if TLV is not management
     * @note this function is for scripting, normal C++ can just cast
     * @note User @b should not try to free this TLV object
     */
    const BaseMngTlv *getSigMngTlv(size_t position) const;
};

/* For SWIG */
#undef A
#undef _ptpmCaseUF

#ifndef SWIG
}; /* namespace ptpmgmt */
#endif

#endif /* __PTPMGMT_MSG_H */
