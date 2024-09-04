//
// Generated file, do not edit! Created by nedtool 5.6 from inet/routing/sixgen/heartBeat.msg.
//

// Disable warnings about unused variables, empty switch stmts, etc:
#ifdef _MSC_VER
#  pragma warning(disable:4101)
#  pragma warning(disable:4065)
#endif

#if defined(__clang__)
#  pragma clang diagnostic ignored "-Wshadow"
#  pragma clang diagnostic ignored "-Wconversion"
#  pragma clang diagnostic ignored "-Wunused-parameter"
#  pragma clang diagnostic ignored "-Wc++98-compat"
#  pragma clang diagnostic ignored "-Wunreachable-code-break"
#  pragma clang diagnostic ignored "-Wold-style-cast"
#elif defined(__GNUC__)
#  pragma GCC diagnostic ignored "-Wshadow"
#  pragma GCC diagnostic ignored "-Wconversion"
#  pragma GCC diagnostic ignored "-Wunused-parameter"
#  pragma GCC diagnostic ignored "-Wold-style-cast"
#  pragma GCC diagnostic ignored "-Wsuggest-attribute=noreturn"
#  pragma GCC diagnostic ignored "-Wfloat-conversion"
#endif

#include <iostream>
#include <sstream>
#include <memory>
#include "heartBeat_m.h"

namespace omnetpp {

// Template pack/unpack rules. They are declared *after* a1l type-specific pack functions for multiple reasons.
// They are in the omnetpp namespace, to allow them to be found by argument-dependent lookup via the cCommBuffer argument

// Packing/unpacking an std::vector
template<typename T, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::vector<T,A>& v)
{
    int n = v.size();
    doParsimPacking(buffer, n);
    for (int i = 0; i < n; i++)
        doParsimPacking(buffer, v[i]);
}

template<typename T, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::vector<T,A>& v)
{
    int n;
    doParsimUnpacking(buffer, n);
    v.resize(n);
    for (int i = 0; i < n; i++)
        doParsimUnpacking(buffer, v[i]);
}

// Packing/unpacking an std::list
template<typename T, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::list<T,A>& l)
{
    doParsimPacking(buffer, (int)l.size());
    for (typename std::list<T,A>::const_iterator it = l.begin(); it != l.end(); ++it)
        doParsimPacking(buffer, (T&)*it);
}

template<typename T, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::list<T,A>& l)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i = 0; i < n; i++) {
        l.push_back(T());
        doParsimUnpacking(buffer, l.back());
    }
}

// Packing/unpacking an std::set
template<typename T, typename Tr, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::set<T,Tr,A>& s)
{
    doParsimPacking(buffer, (int)s.size());
    for (typename std::set<T,Tr,A>::const_iterator it = s.begin(); it != s.end(); ++it)
        doParsimPacking(buffer, *it);
}

template<typename T, typename Tr, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::set<T,Tr,A>& s)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i = 0; i < n; i++) {
        T x;
        doParsimUnpacking(buffer, x);
        s.insert(x);
    }
}

// Packing/unpacking an std::map
template<typename K, typename V, typename Tr, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::map<K,V,Tr,A>& m)
{
    doParsimPacking(buffer, (int)m.size());
    for (typename std::map<K,V,Tr,A>::const_iterator it = m.begin(); it != m.end(); ++it) {
        doParsimPacking(buffer, it->first);
        doParsimPacking(buffer, it->second);
    }
}

template<typename K, typename V, typename Tr, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::map<K,V,Tr,A>& m)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i = 0; i < n; i++) {
        K k; V v;
        doParsimUnpacking(buffer, k);
        doParsimUnpacking(buffer, v);
        m[k] = v;
    }
}

// Default pack/unpack function for arrays
template<typename T>
void doParsimArrayPacking(omnetpp::cCommBuffer *b, const T *t, int n)
{
    for (int i = 0; i < n; i++)
        doParsimPacking(b, t[i]);
}

template<typename T>
void doParsimArrayUnpacking(omnetpp::cCommBuffer *b, T *t, int n)
{
    for (int i = 0; i < n; i++)
        doParsimUnpacking(b, t[i]);
}

// Default rule to prevent compiler from choosing base class' doParsimPacking() function
template<typename T>
void doParsimPacking(omnetpp::cCommBuffer *, const T& t)
{
    throw omnetpp::cRuntimeError("Parsim error: No doParsimPacking() function for type %s", omnetpp::opp_typename(typeid(t)));
}

template<typename T>
void doParsimUnpacking(omnetpp::cCommBuffer *, T& t)
{
    throw omnetpp::cRuntimeError("Parsim error: No doParsimUnpacking() function for type %s", omnetpp::opp_typename(typeid(t)));
}

}  // namespace omnetpp

namespace {
template <class T> inline
typename std::enable_if<std::is_polymorphic<T>::value && std::is_base_of<omnetpp::cObject,T>::value, void *>::type
toVoidPtr(T* t)
{
    return (void *)(static_cast<const omnetpp::cObject *>(t));
}

template <class T> inline
typename std::enable_if<std::is_polymorphic<T>::value && !std::is_base_of<omnetpp::cObject,T>::value, void *>::type
toVoidPtr(T* t)
{
    return (void *)dynamic_cast<const void *>(t);
}

template <class T> inline
typename std::enable_if<!std::is_polymorphic<T>::value, void *>::type
toVoidPtr(T* t)
{
    return (void *)static_cast<const void *>(t);
}

}

namespace inet {
namespace wirelessrouting {

// forward
template<typename T, typename A>
std::ostream& operator<<(std::ostream& out, const std::vector<T,A>& vec);

// Template rule to generate operator<< for shared_ptr<T>
template<typename T>
inline std::ostream& operator<<(std::ostream& out,const std::shared_ptr<T>& t) { return out << t.get(); }

// Template rule which fires if a struct or class doesn't have operator<<
template<typename T>
inline std::ostream& operator<<(std::ostream& out,const T&) {return out;}

// operator<< for std::vector<T>
template<typename T, typename A>
inline std::ostream& operator<<(std::ostream& out, const std::vector<T,A>& vec)
{
    out.put('{');
    for(typename std::vector<T,A>::const_iterator it = vec.begin(); it != vec.end(); ++it)
    {
        if (it != vec.begin()) {
            out.put(','); out.put(' ');
        }
        out << *it;
    }
    out.put('}');

    char buf[32];
    sprintf(buf, " (size=%u)", (unsigned int)vec.size());
    out.write(buf, strlen(buf));
    return out;
}

EXECUTE_ON_STARTUP(
    omnetpp::cEnum *e = omnetpp::cEnum::find("inet::wirelessrouting::heartBeatType");
    if (!e) omnetpp::enums.getInstance()->add(e = new omnetpp::cEnum("inet::wirelessrouting::heartBeatType"));
    e->insert(SNP, "SNP");
    e->insert(RESP, "RESP");
    e->insert(CAINREQ, "CAINREQ");
    e->insert(CAINRESP, "CAINRESP");
    e->insert(CAINFWD, "CAINFWD");
    e->insert(CAINHOP, "CAINHOP");
    e->insert(CAINERR, "CAINERR");
    e->insert(CAINACK, "CAINACK");
    e->insert(RREQ, "RREQ");
    e->insert(RREP, "RREP");
    e->insert(SCMSG, "SCMSG");
    e->insert(LAR, "LAR");
    e->insert(SPR, "SPR");
    e->insert(BRAP, "BRAP");
    e->insert(NEWFWD, "NEWFWD");
    e->insert(CAINREPLY, "CAINREPLY");
    e->insert(HOPCOUNT, "HOPCOUNT");
    e->insert(ANTN, "ANTN");
    e->insert(WGHT, "WGHT");
    e->insert(LEACH, "LEACH");
    e->insert(DRONE, "DRONE");
    e->insert(SNP_IPv6, "SNP_IPv6");
    e->insert(RESP_IPv6, "RESP_IPv6");
    e->insert(CAINREQ_IPv6, "CAINREQ_IPv6");
    e->insert(CAINRESP_IPv6, "CAINRESP_IPv6");
    e->insert(CAINFWD_IPv6, "CAINFWD_IPv6");
    e->insert(CAINHOP_IPv6, "CAINHOP_IPv6");
    e->insert(CAINERR_IPv6, "CAINERR_IPv6");
    e->insert(CAINACK_IPv6, "CAINACK_IPv6");
    e->insert(RREQ_IPv6, "RREQ_IPv6");
    e->insert(RREP_IPv6, "RREP_IPv6");
    e->insert(SCMSG_IPv6, "SCMSG_IPv6");
    e->insert(LAR_IPv6, "LAR_IPv6");
    e->insert(SPR_IPv6, "SPR_IPv6");
    e->insert(BRAP_IPv6, "BRAP_IPv6");
    e->insert(NEWFWD_IPv6, "NEWFWD_IPv6");
    e->insert(CAINREPLY_IPv6, "CAINREPLY_IPv6");
    e->insert(HOPCOUNT_IPv6, "HOPCOUNT_IPv6");
    e->insert(ANTN_IPv6, "ANTN_IPv6");
    e->insert(WGHT_IPv6, "WGHT_IPv6");
    e->insert(LEACH_IPv6, "LEACH_IPv6");
    e->insert(DRONE_IPv6, "DRONE_IPv6");
    e->insert(def, "def");
)

Register_Class(HeartBeat)

HeartBeat::HeartBeat() : ::inet::FieldsChunk()
{
}

HeartBeat::HeartBeat(const HeartBeat& other) : ::inet::FieldsChunk(other)
{
    copy(other);
}

HeartBeat::~HeartBeat()
{
}

HeartBeat& HeartBeat::operator=(const HeartBeat& other)
{
    if (this == &other) return *this;
    ::inet::FieldsChunk::operator=(other);
    copy(other);
    return *this;
}

void HeartBeat::copy(const HeartBeat& other)
{
    this->packetType = other.packetType;
}

void HeartBeat::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::FieldsChunk::parsimPack(b);
    doParsimPacking(b,this->packetType);
}

void HeartBeat::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::FieldsChunk::parsimUnpack(b);
    doParsimUnpacking(b,this->packetType);
}

inet::wirelessrouting::heartBeatType HeartBeat::getPacketType() const
{
    return this->packetType;
}

void HeartBeat::setPacketType(inet::wirelessrouting::heartBeatType packetType)
{
    handleChange();
    this->packetType = packetType;
}

class HeartBeatDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
    enum FieldConstants {
        FIELD_packetType,
    };
  public:
    HeartBeatDescriptor();
    virtual ~HeartBeatDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyname) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyname) const override;
    virtual int getFieldArraySize(void *object, int field) const override;

    virtual const char *getFieldDynamicTypeString(void *object, int field, int i) const override;
    virtual std::string getFieldValueAsString(void *object, int field, int i) const override;
    virtual bool setFieldValueAsString(void *object, int field, int i, const char *value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual void *getFieldStructValuePointer(void *object, int field, int i) const override;
};

Register_ClassDescriptor(HeartBeatDescriptor)

HeartBeatDescriptor::HeartBeatDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::wirelessrouting::HeartBeat)), "inet::FieldsChunk")
{
    propertynames = nullptr;
}

HeartBeatDescriptor::~HeartBeatDescriptor()
{
    delete[] propertynames;
}

bool HeartBeatDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<HeartBeat *>(obj)!=nullptr;
}

const char **HeartBeatDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *HeartBeatDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int HeartBeatDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 1+basedesc->getFieldCount() : 1;
}

unsigned int HeartBeatDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_packetType
    };
    return (field >= 0 && field < 1) ? fieldTypeFlags[field] : 0;
}

const char *HeartBeatDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "packetType",
    };
    return (field >= 0 && field < 1) ? fieldNames[field] : nullptr;
}

int HeartBeatDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0] == 'p' && strcmp(fieldName, "packetType") == 0) return base+0;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *HeartBeatDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "inet::wirelessrouting::heartBeatType",    // FIELD_packetType
    };
    return (field >= 0 && field < 1) ? fieldTypeStrings[field] : nullptr;
}

const char **HeartBeatDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldPropertyNames(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        case FIELD_packetType: {
            static const char *names[] = { "enum",  nullptr };
            return names;
        }
        default: return nullptr;
    }
}

const char *HeartBeatDescriptor::getFieldProperty(int field, const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldProperty(field, propertyname);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        case FIELD_packetType:
            if (!strcmp(propertyname, "enum")) return "inet::wirelessrouting::heartBeatType";
            return nullptr;
        default: return nullptr;
    }
}

int HeartBeatDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    HeartBeat *pp = (HeartBeat *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

const char *HeartBeatDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    HeartBeat *pp = (HeartBeat *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string HeartBeatDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    HeartBeat *pp = (HeartBeat *)object; (void)pp;
    switch (field) {
        case FIELD_packetType: return enum2string(pp->getPacketType(), "inet::wirelessrouting::heartBeatType");
        default: return "";
    }
}

bool HeartBeatDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    HeartBeat *pp = (HeartBeat *)object; (void)pp;
    switch (field) {
        case FIELD_packetType: pp->setPacketType((inet::wirelessrouting::heartBeatType)string2enum(value, "inet::wirelessrouting::heartBeatType")); return true;
        default: return false;
    }
}

const char *HeartBeatDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructName(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    };
}

void *HeartBeatDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    HeartBeat *pp = (HeartBeat *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

Register_Class(SNOOPHB)

SNOOPHB::SNOOPHB() : ::inet::wirelessrouting::HeartBeat()
{
}

SNOOPHB::SNOOPHB(const SNOOPHB& other) : ::inet::wirelessrouting::HeartBeat(other)
{
    copy(other);
}

SNOOPHB::~SNOOPHB()
{
}

SNOOPHB& SNOOPHB::operator=(const SNOOPHB& other)
{
    if (this == &other) return *this;
    ::inet::wirelessrouting::HeartBeat::operator=(other);
    copy(other);
    return *this;
}

void SNOOPHB::copy(const SNOOPHB& other)
{
    this->joinFlag = other.joinFlag;
    this->repairFlag = other.repairFlag;
    this->gratuitousRREPFlag = other.gratuitousRREPFlag;
    this->twoHop = other.twoHop;
    this->unknownSeqNumFlag = other.unknownSeqNumFlag;
    this->reserved = other.reserved;
    this->hopCount = other.hopCount;
    this->rreqId = other.rreqId;
    this->destAddr = other.destAddr;
    this->destSeqNum = other.destSeqNum;
    this->originatorAddr = other.originatorAddr;
    this->originatorSeqNum = other.originatorSeqNum;
    this->msgCoord = other.msgCoord;
    this->batteryPercent = other.batteryPercent;
    this->neighbAddr = other.neighbAddr;
    this->neighbMsgCoord = other.neighbMsgCoord;
    this->neighbBatteryPercent = other.neighbBatteryPercent;
    this->chDist = other.chDist;
    this->nodeName = other.nodeName;
}

void SNOOPHB::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::wirelessrouting::HeartBeat::parsimPack(b);
    doParsimPacking(b,this->joinFlag);
    doParsimPacking(b,this->repairFlag);
    doParsimPacking(b,this->gratuitousRREPFlag);
    doParsimPacking(b,this->twoHop);
    doParsimPacking(b,this->unknownSeqNumFlag);
    doParsimPacking(b,this->reserved);
    doParsimPacking(b,this->hopCount);
    doParsimPacking(b,this->rreqId);
    doParsimPacking(b,this->destAddr);
    doParsimPacking(b,this->destSeqNum);
    doParsimPacking(b,this->originatorAddr);
    doParsimPacking(b,this->originatorSeqNum);
    doParsimPacking(b,this->msgCoord);
    doParsimPacking(b,this->batteryPercent);
    doParsimPacking(b,this->neighbAddr);
    doParsimPacking(b,this->neighbMsgCoord);
    doParsimPacking(b,this->neighbBatteryPercent);
    doParsimPacking(b,this->chDist);
    doParsimPacking(b,this->nodeName);
}

void SNOOPHB::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::wirelessrouting::HeartBeat::parsimUnpack(b);
    doParsimUnpacking(b,this->joinFlag);
    doParsimUnpacking(b,this->repairFlag);
    doParsimUnpacking(b,this->gratuitousRREPFlag);
    doParsimUnpacking(b,this->twoHop);
    doParsimUnpacking(b,this->unknownSeqNumFlag);
    doParsimUnpacking(b,this->reserved);
    doParsimUnpacking(b,this->hopCount);
    doParsimUnpacking(b,this->rreqId);
    doParsimUnpacking(b,this->destAddr);
    doParsimUnpacking(b,this->destSeqNum);
    doParsimUnpacking(b,this->originatorAddr);
    doParsimUnpacking(b,this->originatorSeqNum);
    doParsimUnpacking(b,this->msgCoord);
    doParsimUnpacking(b,this->batteryPercent);
    doParsimUnpacking(b,this->neighbAddr);
    doParsimUnpacking(b,this->neighbMsgCoord);
    doParsimUnpacking(b,this->neighbBatteryPercent);
    doParsimUnpacking(b,this->chDist);
    doParsimUnpacking(b,this->nodeName);
}

bool SNOOPHB::getJoinFlag() const
{
    return this->joinFlag;
}

void SNOOPHB::setJoinFlag(bool joinFlag)
{
    handleChange();
    this->joinFlag = joinFlag;
}

bool SNOOPHB::getRepairFlag() const
{
    return this->repairFlag;
}

void SNOOPHB::setRepairFlag(bool repairFlag)
{
    handleChange();
    this->repairFlag = repairFlag;
}

bool SNOOPHB::getGratuitousRREPFlag() const
{
    return this->gratuitousRREPFlag;
}

void SNOOPHB::setGratuitousRREPFlag(bool gratuitousRREPFlag)
{
    handleChange();
    this->gratuitousRREPFlag = gratuitousRREPFlag;
}

bool SNOOPHB::getTwoHop() const
{
    return this->twoHop;
}

void SNOOPHB::setTwoHop(bool twoHop)
{
    handleChange();
    this->twoHop = twoHop;
}

bool SNOOPHB::getUnknownSeqNumFlag() const
{
    return this->unknownSeqNumFlag;
}

void SNOOPHB::setUnknownSeqNumFlag(bool unknownSeqNumFlag)
{
    handleChange();
    this->unknownSeqNumFlag = unknownSeqNumFlag;
}

uint16_t SNOOPHB::getReserved() const
{
    return this->reserved;
}

void SNOOPHB::setReserved(uint16_t reserved)
{
    handleChange();
    this->reserved = reserved;
}

unsigned int SNOOPHB::getHopCount() const
{
    return this->hopCount;
}

void SNOOPHB::setHopCount(unsigned int hopCount)
{
    handleChange();
    this->hopCount = hopCount;
}

uint32_t SNOOPHB::getRreqId() const
{
    return this->rreqId;
}

void SNOOPHB::setRreqId(uint32_t rreqId)
{
    handleChange();
    this->rreqId = rreqId;
}

const L3Address& SNOOPHB::getDestAddr() const
{
    return this->destAddr;
}

void SNOOPHB::setDestAddr(const L3Address& destAddr)
{
    handleChange();
    this->destAddr = destAddr;
}

uint32_t SNOOPHB::getDestSeqNum() const
{
    return this->destSeqNum;
}

void SNOOPHB::setDestSeqNum(uint32_t destSeqNum)
{
    handleChange();
    this->destSeqNum = destSeqNum;
}

const L3Address& SNOOPHB::getOriginatorAddr() const
{
    return this->originatorAddr;
}

void SNOOPHB::setOriginatorAddr(const L3Address& originatorAddr)
{
    handleChange();
    this->originatorAddr = originatorAddr;
}

uint32_t SNOOPHB::getOriginatorSeqNum() const
{
    return this->originatorSeqNum;
}

void SNOOPHB::setOriginatorSeqNum(uint32_t originatorSeqNum)
{
    handleChange();
    this->originatorSeqNum = originatorSeqNum;
}

const Coord& SNOOPHB::getMsgCoord() const
{
    return this->msgCoord;
}

void SNOOPHB::setMsgCoord(const Coord& msgCoord)
{
    handleChange();
    this->msgCoord = msgCoord;
}

uint32_t SNOOPHB::getBatteryPercent() const
{
    return this->batteryPercent;
}

void SNOOPHB::setBatteryPercent(uint32_t batteryPercent)
{
    handleChange();
    this->batteryPercent = batteryPercent;
}

const L3Address& SNOOPHB::getNeighbAddr() const
{
    return this->neighbAddr;
}

void SNOOPHB::setNeighbAddr(const L3Address& neighbAddr)
{
    handleChange();
    this->neighbAddr = neighbAddr;
}

const Coord& SNOOPHB::getNeighbMsgCoord() const
{
    return this->neighbMsgCoord;
}

void SNOOPHB::setNeighbMsgCoord(const Coord& neighbMsgCoord)
{
    handleChange();
    this->neighbMsgCoord = neighbMsgCoord;
}

uint32_t SNOOPHB::getNeighbBatteryPercent() const
{
    return this->neighbBatteryPercent;
}

void SNOOPHB::setNeighbBatteryPercent(uint32_t neighbBatteryPercent)
{
    handleChange();
    this->neighbBatteryPercent = neighbBatteryPercent;
}

double SNOOPHB::getChDist() const
{
    return this->chDist;
}

void SNOOPHB::setChDist(double chDist)
{
    handleChange();
    this->chDist = chDist;
}

const char * SNOOPHB::getNodeName() const
{
    return this->nodeName.c_str();
}

void SNOOPHB::setNodeName(const char * nodeName)
{
    handleChange();
    this->nodeName = nodeName;
}

class SNOOPHBDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
    enum FieldConstants {
        FIELD_joinFlag,
        FIELD_repairFlag,
        FIELD_gratuitousRREPFlag,
        FIELD_twoHop,
        FIELD_unknownSeqNumFlag,
        FIELD_reserved,
        FIELD_hopCount,
        FIELD_rreqId,
        FIELD_destAddr,
        FIELD_destSeqNum,
        FIELD_originatorAddr,
        FIELD_originatorSeqNum,
        FIELD_msgCoord,
        FIELD_batteryPercent,
        FIELD_neighbAddr,
        FIELD_neighbMsgCoord,
        FIELD_neighbBatteryPercent,
        FIELD_chDist,
        FIELD_nodeName,
    };
  public:
    SNOOPHBDescriptor();
    virtual ~SNOOPHBDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyname) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyname) const override;
    virtual int getFieldArraySize(void *object, int field) const override;

    virtual const char *getFieldDynamicTypeString(void *object, int field, int i) const override;
    virtual std::string getFieldValueAsString(void *object, int field, int i) const override;
    virtual bool setFieldValueAsString(void *object, int field, int i, const char *value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual void *getFieldStructValuePointer(void *object, int field, int i) const override;
};

Register_ClassDescriptor(SNOOPHBDescriptor)

SNOOPHBDescriptor::SNOOPHBDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::wirelessrouting::SNOOPHB)), "inet::wirelessrouting::HeartBeat")
{
    propertynames = nullptr;
}

SNOOPHBDescriptor::~SNOOPHBDescriptor()
{
    delete[] propertynames;
}

bool SNOOPHBDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<SNOOPHB *>(obj)!=nullptr;
}

const char **SNOOPHBDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *SNOOPHBDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int SNOOPHBDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 19+basedesc->getFieldCount() : 19;
}

unsigned int SNOOPHBDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_joinFlag
        FD_ISEDITABLE,    // FIELD_repairFlag
        FD_ISEDITABLE,    // FIELD_gratuitousRREPFlag
        FD_ISEDITABLE,    // FIELD_twoHop
        FD_ISEDITABLE,    // FIELD_unknownSeqNumFlag
        FD_ISEDITABLE,    // FIELD_reserved
        FD_ISEDITABLE,    // FIELD_hopCount
        FD_ISEDITABLE,    // FIELD_rreqId
        0,    // FIELD_destAddr
        FD_ISEDITABLE,    // FIELD_destSeqNum
        0,    // FIELD_originatorAddr
        FD_ISEDITABLE,    // FIELD_originatorSeqNum
        FD_ISCOMPOUND,    // FIELD_msgCoord
        FD_ISEDITABLE,    // FIELD_batteryPercent
        0,    // FIELD_neighbAddr
        FD_ISCOMPOUND,    // FIELD_neighbMsgCoord
        FD_ISEDITABLE,    // FIELD_neighbBatteryPercent
        FD_ISEDITABLE,    // FIELD_chDist
        FD_ISEDITABLE,    // FIELD_nodeName
    };
    return (field >= 0 && field < 19) ? fieldTypeFlags[field] : 0;
}

const char *SNOOPHBDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "joinFlag",
        "repairFlag",
        "gratuitousRREPFlag",
        "twoHop",
        "unknownSeqNumFlag",
        "reserved",
        "hopCount",
        "rreqId",
        "destAddr",
        "destSeqNum",
        "originatorAddr",
        "originatorSeqNum",
        "msgCoord",
        "batteryPercent",
        "neighbAddr",
        "neighbMsgCoord",
        "neighbBatteryPercent",
        "chDist",
        "nodeName",
    };
    return (field >= 0 && field < 19) ? fieldNames[field] : nullptr;
}

int SNOOPHBDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0] == 'j' && strcmp(fieldName, "joinFlag") == 0) return base+0;
    if (fieldName[0] == 'r' && strcmp(fieldName, "repairFlag") == 0) return base+1;
    if (fieldName[0] == 'g' && strcmp(fieldName, "gratuitousRREPFlag") == 0) return base+2;
    if (fieldName[0] == 't' && strcmp(fieldName, "twoHop") == 0) return base+3;
    if (fieldName[0] == 'u' && strcmp(fieldName, "unknownSeqNumFlag") == 0) return base+4;
    if (fieldName[0] == 'r' && strcmp(fieldName, "reserved") == 0) return base+5;
    if (fieldName[0] == 'h' && strcmp(fieldName, "hopCount") == 0) return base+6;
    if (fieldName[0] == 'r' && strcmp(fieldName, "rreqId") == 0) return base+7;
    if (fieldName[0] == 'd' && strcmp(fieldName, "destAddr") == 0) return base+8;
    if (fieldName[0] == 'd' && strcmp(fieldName, "destSeqNum") == 0) return base+9;
    if (fieldName[0] == 'o' && strcmp(fieldName, "originatorAddr") == 0) return base+10;
    if (fieldName[0] == 'o' && strcmp(fieldName, "originatorSeqNum") == 0) return base+11;
    if (fieldName[0] == 'm' && strcmp(fieldName, "msgCoord") == 0) return base+12;
    if (fieldName[0] == 'b' && strcmp(fieldName, "batteryPercent") == 0) return base+13;
    if (fieldName[0] == 'n' && strcmp(fieldName, "neighbAddr") == 0) return base+14;
    if (fieldName[0] == 'n' && strcmp(fieldName, "neighbMsgCoord") == 0) return base+15;
    if (fieldName[0] == 'n' && strcmp(fieldName, "neighbBatteryPercent") == 0) return base+16;
    if (fieldName[0] == 'c' && strcmp(fieldName, "chDist") == 0) return base+17;
    if (fieldName[0] == 'n' && strcmp(fieldName, "nodeName") == 0) return base+18;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *SNOOPHBDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "bool",    // FIELD_joinFlag
        "bool",    // FIELD_repairFlag
        "bool",    // FIELD_gratuitousRREPFlag
        "bool",    // FIELD_twoHop
        "bool",    // FIELD_unknownSeqNumFlag
        "uint16_t",    // FIELD_reserved
        "unsigned int",    // FIELD_hopCount
        "uint32_t",    // FIELD_rreqId
        "inet::L3Address",    // FIELD_destAddr
        "uint32_t",    // FIELD_destSeqNum
        "inet::L3Address",    // FIELD_originatorAddr
        "uint32_t",    // FIELD_originatorSeqNum
        "inet::Coord",    // FIELD_msgCoord
        "uint32_t",    // FIELD_batteryPercent
        "inet::L3Address",    // FIELD_neighbAddr
        "inet::Coord",    // FIELD_neighbMsgCoord
        "uint32_t",    // FIELD_neighbBatteryPercent
        "double",    // FIELD_chDist
        "string",    // FIELD_nodeName
    };
    return (field >= 0 && field < 19) ? fieldTypeStrings[field] : nullptr;
}

const char **SNOOPHBDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldPropertyNames(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *SNOOPHBDescriptor::getFieldProperty(int field, const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldProperty(field, propertyname);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int SNOOPHBDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    SNOOPHB *pp = (SNOOPHB *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

const char *SNOOPHBDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    SNOOPHB *pp = (SNOOPHB *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string SNOOPHBDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    SNOOPHB *pp = (SNOOPHB *)object; (void)pp;
    switch (field) {
        case FIELD_joinFlag: return bool2string(pp->getJoinFlag());
        case FIELD_repairFlag: return bool2string(pp->getRepairFlag());
        case FIELD_gratuitousRREPFlag: return bool2string(pp->getGratuitousRREPFlag());
        case FIELD_twoHop: return bool2string(pp->getTwoHop());
        case FIELD_unknownSeqNumFlag: return bool2string(pp->getUnknownSeqNumFlag());
        case FIELD_reserved: return ulong2string(pp->getReserved());
        case FIELD_hopCount: return ulong2string(pp->getHopCount());
        case FIELD_rreqId: return ulong2string(pp->getRreqId());
        case FIELD_destAddr: return pp->getDestAddr().str();
        case FIELD_destSeqNum: return ulong2string(pp->getDestSeqNum());
        case FIELD_originatorAddr: return pp->getOriginatorAddr().str();
        case FIELD_originatorSeqNum: return ulong2string(pp->getOriginatorSeqNum());
        case FIELD_msgCoord: {std::stringstream out; out << pp->getMsgCoord(); return out.str();}
        case FIELD_batteryPercent: return ulong2string(pp->getBatteryPercent());
        case FIELD_neighbAddr: return pp->getNeighbAddr().str();
        case FIELD_neighbMsgCoord: {std::stringstream out; out << pp->getNeighbMsgCoord(); return out.str();}
        case FIELD_neighbBatteryPercent: return ulong2string(pp->getNeighbBatteryPercent());
        case FIELD_chDist: return double2string(pp->getChDist());
        case FIELD_nodeName: return oppstring2string(pp->getNodeName());
        default: return "";
    }
}

bool SNOOPHBDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    SNOOPHB *pp = (SNOOPHB *)object; (void)pp;
    switch (field) {
        case FIELD_joinFlag: pp->setJoinFlag(string2bool(value)); return true;
        case FIELD_repairFlag: pp->setRepairFlag(string2bool(value)); return true;
        case FIELD_gratuitousRREPFlag: pp->setGratuitousRREPFlag(string2bool(value)); return true;
        case FIELD_twoHop: pp->setTwoHop(string2bool(value)); return true;
        case FIELD_unknownSeqNumFlag: pp->setUnknownSeqNumFlag(string2bool(value)); return true;
        case FIELD_reserved: pp->setReserved(string2ulong(value)); return true;
        case FIELD_hopCount: pp->setHopCount(string2ulong(value)); return true;
        case FIELD_rreqId: pp->setRreqId(string2ulong(value)); return true;
        case FIELD_destSeqNum: pp->setDestSeqNum(string2ulong(value)); return true;
        case FIELD_originatorSeqNum: pp->setOriginatorSeqNum(string2ulong(value)); return true;
        case FIELD_batteryPercent: pp->setBatteryPercent(string2ulong(value)); return true;
        case FIELD_neighbBatteryPercent: pp->setNeighbBatteryPercent(string2ulong(value)); return true;
        case FIELD_chDist: pp->setChDist(string2double(value)); return true;
        case FIELD_nodeName: pp->setNodeName((value)); return true;
        default: return false;
    }
}

const char *SNOOPHBDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructName(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        case FIELD_msgCoord: return omnetpp::opp_typename(typeid(Coord));
        case FIELD_neighbMsgCoord: return omnetpp::opp_typename(typeid(Coord));
        default: return nullptr;
    };
}

void *SNOOPHBDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    SNOOPHB *pp = (SNOOPHB *)object; (void)pp;
    switch (field) {
        case FIELD_destAddr: return toVoidPtr(&pp->getDestAddr()); break;
        case FIELD_originatorAddr: return toVoidPtr(&pp->getOriginatorAddr()); break;
        case FIELD_msgCoord: return toVoidPtr(&pp->getMsgCoord()); break;
        case FIELD_neighbAddr: return toVoidPtr(&pp->getNeighbAddr()); break;
        case FIELD_neighbMsgCoord: return toVoidPtr(&pp->getNeighbMsgCoord()); break;
        default: return nullptr;
    }
}

Register_Class(FLWEIGHT)

FLWEIGHT::FLWEIGHT() : ::inet::wirelessrouting::HeartBeat()
{
}

FLWEIGHT::FLWEIGHT(const FLWEIGHT& other) : ::inet::wirelessrouting::HeartBeat(other)
{
    copy(other);
}

FLWEIGHT::~FLWEIGHT()
{
}

FLWEIGHT& FLWEIGHT::operator=(const FLWEIGHT& other)
{
    if (this == &other) return *this;
    ::inet::wirelessrouting::HeartBeat::operator=(other);
    copy(other);
    return *this;
}

void FLWEIGHT::copy(const FLWEIGHT& other)
{
    this->destAddr = other.destAddr;
    this->sourceAddr = other.sourceAddr;
    this->w11 = other.w11;
    this->w12 = other.w12;
    this->w13 = other.w13;
    this->w21 = other.w21;
    this->w22 = other.w22;
    this->w23 = other.w23;
    this->w31 = other.w31;
    this->w32 = other.w32;
    this->w33 = other.w33;
    this->wo1 = other.wo1;
    this->wo2 = other.wo2;
    this->wo3 = other.wo3;
}

void FLWEIGHT::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::wirelessrouting::HeartBeat::parsimPack(b);
    doParsimPacking(b,this->destAddr);
    doParsimPacking(b,this->sourceAddr);
    doParsimPacking(b,this->w11);
    doParsimPacking(b,this->w12);
    doParsimPacking(b,this->w13);
    doParsimPacking(b,this->w21);
    doParsimPacking(b,this->w22);
    doParsimPacking(b,this->w23);
    doParsimPacking(b,this->w31);
    doParsimPacking(b,this->w32);
    doParsimPacking(b,this->w33);
    doParsimPacking(b,this->wo1);
    doParsimPacking(b,this->wo2);
    doParsimPacking(b,this->wo3);
}

void FLWEIGHT::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::wirelessrouting::HeartBeat::parsimUnpack(b);
    doParsimUnpacking(b,this->destAddr);
    doParsimUnpacking(b,this->sourceAddr);
    doParsimUnpacking(b,this->w11);
    doParsimUnpacking(b,this->w12);
    doParsimUnpacking(b,this->w13);
    doParsimUnpacking(b,this->w21);
    doParsimUnpacking(b,this->w22);
    doParsimUnpacking(b,this->w23);
    doParsimUnpacking(b,this->w31);
    doParsimUnpacking(b,this->w32);
    doParsimUnpacking(b,this->w33);
    doParsimUnpacking(b,this->wo1);
    doParsimUnpacking(b,this->wo2);
    doParsimUnpacking(b,this->wo3);
}

const L3Address& FLWEIGHT::getDestAddr() const
{
    return this->destAddr;
}

void FLWEIGHT::setDestAddr(const L3Address& destAddr)
{
    handleChange();
    this->destAddr = destAddr;
}

const L3Address& FLWEIGHT::getSourceAddr() const
{
    return this->sourceAddr;
}

void FLWEIGHT::setSourceAddr(const L3Address& sourceAddr)
{
    handleChange();
    this->sourceAddr = sourceAddr;
}

float FLWEIGHT::getW11() const
{
    return this->w11;
}

void FLWEIGHT::setW11(float w11)
{
    handleChange();
    this->w11 = w11;
}

float FLWEIGHT::getW12() const
{
    return this->w12;
}

void FLWEIGHT::setW12(float w12)
{
    handleChange();
    this->w12 = w12;
}

float FLWEIGHT::getW13() const
{
    return this->w13;
}

void FLWEIGHT::setW13(float w13)
{
    handleChange();
    this->w13 = w13;
}

float FLWEIGHT::getW21() const
{
    return this->w21;
}

void FLWEIGHT::setW21(float w21)
{
    handleChange();
    this->w21 = w21;
}

float FLWEIGHT::getW22() const
{
    return this->w22;
}

void FLWEIGHT::setW22(float w22)
{
    handleChange();
    this->w22 = w22;
}

float FLWEIGHT::getW23() const
{
    return this->w23;
}

void FLWEIGHT::setW23(float w23)
{
    handleChange();
    this->w23 = w23;
}

float FLWEIGHT::getW31() const
{
    return this->w31;
}

void FLWEIGHT::setW31(float w31)
{
    handleChange();
    this->w31 = w31;
}

float FLWEIGHT::getW32() const
{
    return this->w32;
}

void FLWEIGHT::setW32(float w32)
{
    handleChange();
    this->w32 = w32;
}

float FLWEIGHT::getW33() const
{
    return this->w33;
}

void FLWEIGHT::setW33(float w33)
{
    handleChange();
    this->w33 = w33;
}

float FLWEIGHT::getWo1() const
{
    return this->wo1;
}

void FLWEIGHT::setWo1(float wo1)
{
    handleChange();
    this->wo1 = wo1;
}

float FLWEIGHT::getWo2() const
{
    return this->wo2;
}

void FLWEIGHT::setWo2(float wo2)
{
    handleChange();
    this->wo2 = wo2;
}

float FLWEIGHT::getWo3() const
{
    return this->wo3;
}

void FLWEIGHT::setWo3(float wo3)
{
    handleChange();
    this->wo3 = wo3;
}

class FLWEIGHTDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
    enum FieldConstants {
        FIELD_destAddr,
        FIELD_sourceAddr,
        FIELD_w11,
        FIELD_w12,
        FIELD_w13,
        FIELD_w21,
        FIELD_w22,
        FIELD_w23,
        FIELD_w31,
        FIELD_w32,
        FIELD_w33,
        FIELD_wo1,
        FIELD_wo2,
        FIELD_wo3,
    };
  public:
    FLWEIGHTDescriptor();
    virtual ~FLWEIGHTDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyname) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyname) const override;
    virtual int getFieldArraySize(void *object, int field) const override;

    virtual const char *getFieldDynamicTypeString(void *object, int field, int i) const override;
    virtual std::string getFieldValueAsString(void *object, int field, int i) const override;
    virtual bool setFieldValueAsString(void *object, int field, int i, const char *value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual void *getFieldStructValuePointer(void *object, int field, int i) const override;
};

Register_ClassDescriptor(FLWEIGHTDescriptor)

FLWEIGHTDescriptor::FLWEIGHTDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::wirelessrouting::FLWEIGHT)), "inet::wirelessrouting::HeartBeat")
{
    propertynames = nullptr;
}

FLWEIGHTDescriptor::~FLWEIGHTDescriptor()
{
    delete[] propertynames;
}

bool FLWEIGHTDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<FLWEIGHT *>(obj)!=nullptr;
}

const char **FLWEIGHTDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *FLWEIGHTDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int FLWEIGHTDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 14+basedesc->getFieldCount() : 14;
}

unsigned int FLWEIGHTDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        0,    // FIELD_destAddr
        0,    // FIELD_sourceAddr
        FD_ISEDITABLE,    // FIELD_w11
        FD_ISEDITABLE,    // FIELD_w12
        FD_ISEDITABLE,    // FIELD_w13
        FD_ISEDITABLE,    // FIELD_w21
        FD_ISEDITABLE,    // FIELD_w22
        FD_ISEDITABLE,    // FIELD_w23
        FD_ISEDITABLE,    // FIELD_w31
        FD_ISEDITABLE,    // FIELD_w32
        FD_ISEDITABLE,    // FIELD_w33
        FD_ISEDITABLE,    // FIELD_wo1
        FD_ISEDITABLE,    // FIELD_wo2
        FD_ISEDITABLE,    // FIELD_wo3
    };
    return (field >= 0 && field < 14) ? fieldTypeFlags[field] : 0;
}

const char *FLWEIGHTDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "destAddr",
        "sourceAddr",
        "w11",
        "w12",
        "w13",
        "w21",
        "w22",
        "w23",
        "w31",
        "w32",
        "w33",
        "wo1",
        "wo2",
        "wo3",
    };
    return (field >= 0 && field < 14) ? fieldNames[field] : nullptr;
}

int FLWEIGHTDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0] == 'd' && strcmp(fieldName, "destAddr") == 0) return base+0;
    if (fieldName[0] == 's' && strcmp(fieldName, "sourceAddr") == 0) return base+1;
    if (fieldName[0] == 'w' && strcmp(fieldName, "w11") == 0) return base+2;
    if (fieldName[0] == 'w' && strcmp(fieldName, "w12") == 0) return base+3;
    if (fieldName[0] == 'w' && strcmp(fieldName, "w13") == 0) return base+4;
    if (fieldName[0] == 'w' && strcmp(fieldName, "w21") == 0) return base+5;
    if (fieldName[0] == 'w' && strcmp(fieldName, "w22") == 0) return base+6;
    if (fieldName[0] == 'w' && strcmp(fieldName, "w23") == 0) return base+7;
    if (fieldName[0] == 'w' && strcmp(fieldName, "w31") == 0) return base+8;
    if (fieldName[0] == 'w' && strcmp(fieldName, "w32") == 0) return base+9;
    if (fieldName[0] == 'w' && strcmp(fieldName, "w33") == 0) return base+10;
    if (fieldName[0] == 'w' && strcmp(fieldName, "wo1") == 0) return base+11;
    if (fieldName[0] == 'w' && strcmp(fieldName, "wo2") == 0) return base+12;
    if (fieldName[0] == 'w' && strcmp(fieldName, "wo3") == 0) return base+13;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *FLWEIGHTDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "inet::L3Address",    // FIELD_destAddr
        "inet::L3Address",    // FIELD_sourceAddr
        "float",    // FIELD_w11
        "float",    // FIELD_w12
        "float",    // FIELD_w13
        "float",    // FIELD_w21
        "float",    // FIELD_w22
        "float",    // FIELD_w23
        "float",    // FIELD_w31
        "float",    // FIELD_w32
        "float",    // FIELD_w33
        "float",    // FIELD_wo1
        "float",    // FIELD_wo2
        "float",    // FIELD_wo3
    };
    return (field >= 0 && field < 14) ? fieldTypeStrings[field] : nullptr;
}

const char **FLWEIGHTDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldPropertyNames(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *FLWEIGHTDescriptor::getFieldProperty(int field, const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldProperty(field, propertyname);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int FLWEIGHTDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    FLWEIGHT *pp = (FLWEIGHT *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

const char *FLWEIGHTDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    FLWEIGHT *pp = (FLWEIGHT *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string FLWEIGHTDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    FLWEIGHT *pp = (FLWEIGHT *)object; (void)pp;
    switch (field) {
        case FIELD_destAddr: return pp->getDestAddr().str();
        case FIELD_sourceAddr: return pp->getSourceAddr().str();
        case FIELD_w11: return double2string(pp->getW11());
        case FIELD_w12: return double2string(pp->getW12());
        case FIELD_w13: return double2string(pp->getW13());
        case FIELD_w21: return double2string(pp->getW21());
        case FIELD_w22: return double2string(pp->getW22());
        case FIELD_w23: return double2string(pp->getW23());
        case FIELD_w31: return double2string(pp->getW31());
        case FIELD_w32: return double2string(pp->getW32());
        case FIELD_w33: return double2string(pp->getW33());
        case FIELD_wo1: return double2string(pp->getWo1());
        case FIELD_wo2: return double2string(pp->getWo2());
        case FIELD_wo3: return double2string(pp->getWo3());
        default: return "";
    }
}

bool FLWEIGHTDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    FLWEIGHT *pp = (FLWEIGHT *)object; (void)pp;
    switch (field) {
        case FIELD_w11: pp->setW11(string2double(value)); return true;
        case FIELD_w12: pp->setW12(string2double(value)); return true;
        case FIELD_w13: pp->setW13(string2double(value)); return true;
        case FIELD_w21: pp->setW21(string2double(value)); return true;
        case FIELD_w22: pp->setW22(string2double(value)); return true;
        case FIELD_w23: pp->setW23(string2double(value)); return true;
        case FIELD_w31: pp->setW31(string2double(value)); return true;
        case FIELD_w32: pp->setW32(string2double(value)); return true;
        case FIELD_w33: pp->setW33(string2double(value)); return true;
        case FIELD_wo1: pp->setWo1(string2double(value)); return true;
        case FIELD_wo2: pp->setWo2(string2double(value)); return true;
        case FIELD_wo3: pp->setWo3(string2double(value)); return true;
        default: return false;
    }
}

const char *FLWEIGHTDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructName(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    };
}

void *FLWEIGHTDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    FLWEIGHT *pp = (FLWEIGHT *)object; (void)pp;
    switch (field) {
        case FIELD_destAddr: return toVoidPtr(&pp->getDestAddr()); break;
        case FIELD_sourceAddr: return toVoidPtr(&pp->getSourceAddr()); break;
        default: return nullptr;
    }
}

Register_Class(DRONEMSG)

DRONEMSG::DRONEMSG() : ::inet::wirelessrouting::HeartBeat()
{
}

DRONEMSG::DRONEMSG(const DRONEMSG& other) : ::inet::wirelessrouting::HeartBeat(other)
{
    copy(other);
}

DRONEMSG::~DRONEMSG()
{
}

DRONEMSG& DRONEMSG::operator=(const DRONEMSG& other)
{
    if (this == &other) return *this;
    ::inet::wirelessrouting::HeartBeat::operator=(other);
    copy(other);
    return *this;
}

void DRONEMSG::copy(const DRONEMSG& other)
{
    this->hopCount = other.hopCount;
    this->destAddr = other.destAddr;
    this->sourceAddr = other.sourceAddr;
    this->senderCoord = other.senderCoord;
}

void DRONEMSG::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::wirelessrouting::HeartBeat::parsimPack(b);
    doParsimPacking(b,this->hopCount);
    doParsimPacking(b,this->destAddr);
    doParsimPacking(b,this->sourceAddr);
    doParsimPacking(b,this->senderCoord);
}

void DRONEMSG::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::wirelessrouting::HeartBeat::parsimUnpack(b);
    doParsimUnpacking(b,this->hopCount);
    doParsimUnpacking(b,this->destAddr);
    doParsimUnpacking(b,this->sourceAddr);
    doParsimUnpacking(b,this->senderCoord);
}

unsigned int DRONEMSG::getHopCount() const
{
    return this->hopCount;
}

void DRONEMSG::setHopCount(unsigned int hopCount)
{
    handleChange();
    this->hopCount = hopCount;
}

const L3Address& DRONEMSG::getDestAddr() const
{
    return this->destAddr;
}

void DRONEMSG::setDestAddr(const L3Address& destAddr)
{
    handleChange();
    this->destAddr = destAddr;
}

const L3Address& DRONEMSG::getSourceAddr() const
{
    return this->sourceAddr;
}

void DRONEMSG::setSourceAddr(const L3Address& sourceAddr)
{
    handleChange();
    this->sourceAddr = sourceAddr;
}

const Coord& DRONEMSG::getSenderCoord() const
{
    return this->senderCoord;
}

void DRONEMSG::setSenderCoord(const Coord& senderCoord)
{
    handleChange();
    this->senderCoord = senderCoord;
}

class DRONEMSGDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
    enum FieldConstants {
        FIELD_hopCount,
        FIELD_destAddr,
        FIELD_sourceAddr,
        FIELD_senderCoord,
    };
  public:
    DRONEMSGDescriptor();
    virtual ~DRONEMSGDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyname) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyname) const override;
    virtual int getFieldArraySize(void *object, int field) const override;

    virtual const char *getFieldDynamicTypeString(void *object, int field, int i) const override;
    virtual std::string getFieldValueAsString(void *object, int field, int i) const override;
    virtual bool setFieldValueAsString(void *object, int field, int i, const char *value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual void *getFieldStructValuePointer(void *object, int field, int i) const override;
};

Register_ClassDescriptor(DRONEMSGDescriptor)

DRONEMSGDescriptor::DRONEMSGDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::wirelessrouting::DRONEMSG)), "inet::wirelessrouting::HeartBeat")
{
    propertynames = nullptr;
}

DRONEMSGDescriptor::~DRONEMSGDescriptor()
{
    delete[] propertynames;
}

bool DRONEMSGDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<DRONEMSG *>(obj)!=nullptr;
}

const char **DRONEMSGDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *DRONEMSGDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int DRONEMSGDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 4+basedesc->getFieldCount() : 4;
}

unsigned int DRONEMSGDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_hopCount
        0,    // FIELD_destAddr
        0,    // FIELD_sourceAddr
        FD_ISCOMPOUND,    // FIELD_senderCoord
    };
    return (field >= 0 && field < 4) ? fieldTypeFlags[field] : 0;
}

const char *DRONEMSGDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "hopCount",
        "destAddr",
        "sourceAddr",
        "senderCoord",
    };
    return (field >= 0 && field < 4) ? fieldNames[field] : nullptr;
}

int DRONEMSGDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0] == 'h' && strcmp(fieldName, "hopCount") == 0) return base+0;
    if (fieldName[0] == 'd' && strcmp(fieldName, "destAddr") == 0) return base+1;
    if (fieldName[0] == 's' && strcmp(fieldName, "sourceAddr") == 0) return base+2;
    if (fieldName[0] == 's' && strcmp(fieldName, "senderCoord") == 0) return base+3;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *DRONEMSGDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "unsigned int",    // FIELD_hopCount
        "inet::L3Address",    // FIELD_destAddr
        "inet::L3Address",    // FIELD_sourceAddr
        "inet::Coord",    // FIELD_senderCoord
    };
    return (field >= 0 && field < 4) ? fieldTypeStrings[field] : nullptr;
}

const char **DRONEMSGDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldPropertyNames(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *DRONEMSGDescriptor::getFieldProperty(int field, const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldProperty(field, propertyname);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int DRONEMSGDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    DRONEMSG *pp = (DRONEMSG *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

const char *DRONEMSGDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    DRONEMSG *pp = (DRONEMSG *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string DRONEMSGDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    DRONEMSG *pp = (DRONEMSG *)object; (void)pp;
    switch (field) {
        case FIELD_hopCount: return ulong2string(pp->getHopCount());
        case FIELD_destAddr: return pp->getDestAddr().str();
        case FIELD_sourceAddr: return pp->getSourceAddr().str();
        case FIELD_senderCoord: {std::stringstream out; out << pp->getSenderCoord(); return out.str();}
        default: return "";
    }
}

bool DRONEMSGDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    DRONEMSG *pp = (DRONEMSG *)object; (void)pp;
    switch (field) {
        case FIELD_hopCount: pp->setHopCount(string2ulong(value)); return true;
        default: return false;
    }
}

const char *DRONEMSGDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructName(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        case FIELD_senderCoord: return omnetpp::opp_typename(typeid(Coord));
        default: return nullptr;
    };
}

void *DRONEMSGDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    DRONEMSG *pp = (DRONEMSG *)object; (void)pp;
    switch (field) {
        case FIELD_destAddr: return toVoidPtr(&pp->getDestAddr()); break;
        case FIELD_sourceAddr: return toVoidPtr(&pp->getSourceAddr()); break;
        case FIELD_senderCoord: return toVoidPtr(&pp->getSenderCoord()); break;
        default: return nullptr;
    }
}

Register_Class(ANTENNA)

ANTENNA::ANTENNA() : ::inet::wirelessrouting::HeartBeat()
{
}

ANTENNA::ANTENNA(const ANTENNA& other) : ::inet::wirelessrouting::HeartBeat(other)
{
    copy(other);
}

ANTENNA::~ANTENNA()
{
}

ANTENNA& ANTENNA::operator=(const ANTENNA& other)
{
    if (this == &other) return *this;
    ::inet::wirelessrouting::HeartBeat::operator=(other);
    copy(other);
    return *this;
}

void ANTENNA::copy(const ANTENNA& other)
{
    this->hopCount = other.hopCount;
    this->destAddr = other.destAddr;
    this->sourceAddr = other.sourceAddr;
}

void ANTENNA::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::wirelessrouting::HeartBeat::parsimPack(b);
    doParsimPacking(b,this->hopCount);
    doParsimPacking(b,this->destAddr);
    doParsimPacking(b,this->sourceAddr);
}

void ANTENNA::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::wirelessrouting::HeartBeat::parsimUnpack(b);
    doParsimUnpacking(b,this->hopCount);
    doParsimUnpacking(b,this->destAddr);
    doParsimUnpacking(b,this->sourceAddr);
}

unsigned int ANTENNA::getHopCount() const
{
    return this->hopCount;
}

void ANTENNA::setHopCount(unsigned int hopCount)
{
    handleChange();
    this->hopCount = hopCount;
}

const L3Address& ANTENNA::getDestAddr() const
{
    return this->destAddr;
}

void ANTENNA::setDestAddr(const L3Address& destAddr)
{
    handleChange();
    this->destAddr = destAddr;
}

const L3Address& ANTENNA::getSourceAddr() const
{
    return this->sourceAddr;
}

void ANTENNA::setSourceAddr(const L3Address& sourceAddr)
{
    handleChange();
    this->sourceAddr = sourceAddr;
}

class ANTENNADescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
    enum FieldConstants {
        FIELD_hopCount,
        FIELD_destAddr,
        FIELD_sourceAddr,
    };
  public:
    ANTENNADescriptor();
    virtual ~ANTENNADescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyname) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyname) const override;
    virtual int getFieldArraySize(void *object, int field) const override;

    virtual const char *getFieldDynamicTypeString(void *object, int field, int i) const override;
    virtual std::string getFieldValueAsString(void *object, int field, int i) const override;
    virtual bool setFieldValueAsString(void *object, int field, int i, const char *value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual void *getFieldStructValuePointer(void *object, int field, int i) const override;
};

Register_ClassDescriptor(ANTENNADescriptor)

ANTENNADescriptor::ANTENNADescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::wirelessrouting::ANTENNA)), "inet::wirelessrouting::HeartBeat")
{
    propertynames = nullptr;
}

ANTENNADescriptor::~ANTENNADescriptor()
{
    delete[] propertynames;
}

bool ANTENNADescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<ANTENNA *>(obj)!=nullptr;
}

const char **ANTENNADescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *ANTENNADescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int ANTENNADescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 3+basedesc->getFieldCount() : 3;
}

unsigned int ANTENNADescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_hopCount
        0,    // FIELD_destAddr
        0,    // FIELD_sourceAddr
    };
    return (field >= 0 && field < 3) ? fieldTypeFlags[field] : 0;
}

const char *ANTENNADescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "hopCount",
        "destAddr",
        "sourceAddr",
    };
    return (field >= 0 && field < 3) ? fieldNames[field] : nullptr;
}

int ANTENNADescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0] == 'h' && strcmp(fieldName, "hopCount") == 0) return base+0;
    if (fieldName[0] == 'd' && strcmp(fieldName, "destAddr") == 0) return base+1;
    if (fieldName[0] == 's' && strcmp(fieldName, "sourceAddr") == 0) return base+2;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *ANTENNADescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "unsigned int",    // FIELD_hopCount
        "inet::L3Address",    // FIELD_destAddr
        "inet::L3Address",    // FIELD_sourceAddr
    };
    return (field >= 0 && field < 3) ? fieldTypeStrings[field] : nullptr;
}

const char **ANTENNADescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldPropertyNames(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *ANTENNADescriptor::getFieldProperty(int field, const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldProperty(field, propertyname);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int ANTENNADescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    ANTENNA *pp = (ANTENNA *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

const char *ANTENNADescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    ANTENNA *pp = (ANTENNA *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string ANTENNADescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    ANTENNA *pp = (ANTENNA *)object; (void)pp;
    switch (field) {
        case FIELD_hopCount: return ulong2string(pp->getHopCount());
        case FIELD_destAddr: return pp->getDestAddr().str();
        case FIELD_sourceAddr: return pp->getSourceAddr().str();
        default: return "";
    }
}

bool ANTENNADescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    ANTENNA *pp = (ANTENNA *)object; (void)pp;
    switch (field) {
        case FIELD_hopCount: pp->setHopCount(string2ulong(value)); return true;
        default: return false;
    }
}

const char *ANTENNADescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructName(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    };
}

void *ANTENNADescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    ANTENNA *pp = (ANTENNA *)object; (void)pp;
    switch (field) {
        case FIELD_destAddr: return toVoidPtr(&pp->getDestAddr()); break;
        case FIELD_sourceAddr: return toVoidPtr(&pp->getSourceAddr()); break;
        default: return nullptr;
    }
}

Register_Class(CHDEF)

CHDEF::CHDEF() : ::inet::wirelessrouting::HeartBeat()
{
}

CHDEF::CHDEF(const CHDEF& other) : ::inet::wirelessrouting::HeartBeat(other)
{
    copy(other);
}

CHDEF::~CHDEF()
{
}

CHDEF& CHDEF::operator=(const CHDEF& other)
{
    if (this == &other) return *this;
    ::inet::wirelessrouting::HeartBeat::operator=(other);
    copy(other);
    return *this;
}

void CHDEF::copy(const CHDEF& other)
{
    this->sourceAddr = other.sourceAddr;
    this->senderCoord = other.senderCoord;
}

void CHDEF::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::wirelessrouting::HeartBeat::parsimPack(b);
    doParsimPacking(b,this->sourceAddr);
    doParsimPacking(b,this->senderCoord);
}

void CHDEF::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::wirelessrouting::HeartBeat::parsimUnpack(b);
    doParsimUnpacking(b,this->sourceAddr);
    doParsimUnpacking(b,this->senderCoord);
}

const L3Address& CHDEF::getSourceAddr() const
{
    return this->sourceAddr;
}

void CHDEF::setSourceAddr(const L3Address& sourceAddr)
{
    handleChange();
    this->sourceAddr = sourceAddr;
}

const Coord& CHDEF::getSenderCoord() const
{
    return this->senderCoord;
}

void CHDEF::setSenderCoord(const Coord& senderCoord)
{
    handleChange();
    this->senderCoord = senderCoord;
}

class CHDEFDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
    enum FieldConstants {
        FIELD_sourceAddr,
        FIELD_senderCoord,
    };
  public:
    CHDEFDescriptor();
    virtual ~CHDEFDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyname) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyname) const override;
    virtual int getFieldArraySize(void *object, int field) const override;

    virtual const char *getFieldDynamicTypeString(void *object, int field, int i) const override;
    virtual std::string getFieldValueAsString(void *object, int field, int i) const override;
    virtual bool setFieldValueAsString(void *object, int field, int i, const char *value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual void *getFieldStructValuePointer(void *object, int field, int i) const override;
};

Register_ClassDescriptor(CHDEFDescriptor)

CHDEFDescriptor::CHDEFDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::wirelessrouting::CHDEF)), "inet::wirelessrouting::HeartBeat")
{
    propertynames = nullptr;
}

CHDEFDescriptor::~CHDEFDescriptor()
{
    delete[] propertynames;
}

bool CHDEFDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<CHDEF *>(obj)!=nullptr;
}

const char **CHDEFDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *CHDEFDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int CHDEFDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 2+basedesc->getFieldCount() : 2;
}

unsigned int CHDEFDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        0,    // FIELD_sourceAddr
        FD_ISCOMPOUND,    // FIELD_senderCoord
    };
    return (field >= 0 && field < 2) ? fieldTypeFlags[field] : 0;
}

const char *CHDEFDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "sourceAddr",
        "senderCoord",
    };
    return (field >= 0 && field < 2) ? fieldNames[field] : nullptr;
}

int CHDEFDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0] == 's' && strcmp(fieldName, "sourceAddr") == 0) return base+0;
    if (fieldName[0] == 's' && strcmp(fieldName, "senderCoord") == 0) return base+1;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *CHDEFDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "inet::L3Address",    // FIELD_sourceAddr
        "inet::Coord",    // FIELD_senderCoord
    };
    return (field >= 0 && field < 2) ? fieldTypeStrings[field] : nullptr;
}

const char **CHDEFDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldPropertyNames(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *CHDEFDescriptor::getFieldProperty(int field, const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldProperty(field, propertyname);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int CHDEFDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    CHDEF *pp = (CHDEF *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

const char *CHDEFDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    CHDEF *pp = (CHDEF *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string CHDEFDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    CHDEF *pp = (CHDEF *)object; (void)pp;
    switch (field) {
        case FIELD_sourceAddr: return pp->getSourceAddr().str();
        case FIELD_senderCoord: {std::stringstream out; out << pp->getSenderCoord(); return out.str();}
        default: return "";
    }
}

bool CHDEFDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    CHDEF *pp = (CHDEF *)object; (void)pp;
    switch (field) {
        default: return false;
    }
}

const char *CHDEFDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructName(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        case FIELD_senderCoord: return omnetpp::opp_typename(typeid(Coord));
        default: return nullptr;
    };
}

void *CHDEFDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    CHDEF *pp = (CHDEF *)object; (void)pp;
    switch (field) {
        case FIELD_sourceAddr: return toVoidPtr(&pp->getSourceAddr()); break;
        case FIELD_senderCoord: return toVoidPtr(&pp->getSenderCoord()); break;
        default: return nullptr;
    }
}

Register_Class(RESPHB)

RESPHB::RESPHB() : ::inet::wirelessrouting::HeartBeat()
{
}

RESPHB::RESPHB(const RESPHB& other) : ::inet::wirelessrouting::HeartBeat(other)
{
    copy(other);
}

RESPHB::~RESPHB()
{
}

RESPHB& RESPHB::operator=(const RESPHB& other)
{
    if (this == &other) return *this;
    ::inet::wirelessrouting::HeartBeat::operator=(other);
    copy(other);
    return *this;
}

void RESPHB::copy(const RESPHB& other)
{
    this->hopCount = other.hopCount;
    this->destAddr = other.destAddr;
    this->sourceAddr = other.sourceAddr;
    this->chAddr = other.chAddr;
    this->originatorAddr = other.originatorAddr;
    this->batteryPercent = other.batteryPercent;
    this->senderCoord = other.senderCoord;
}

void RESPHB::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::wirelessrouting::HeartBeat::parsimPack(b);
    doParsimPacking(b,this->hopCount);
    doParsimPacking(b,this->destAddr);
    doParsimPacking(b,this->sourceAddr);
    doParsimPacking(b,this->chAddr);
    doParsimPacking(b,this->originatorAddr);
    doParsimPacking(b,this->batteryPercent);
    doParsimPacking(b,this->senderCoord);
}

void RESPHB::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::wirelessrouting::HeartBeat::parsimUnpack(b);
    doParsimUnpacking(b,this->hopCount);
    doParsimUnpacking(b,this->destAddr);
    doParsimUnpacking(b,this->sourceAddr);
    doParsimUnpacking(b,this->chAddr);
    doParsimUnpacking(b,this->originatorAddr);
    doParsimUnpacking(b,this->batteryPercent);
    doParsimUnpacking(b,this->senderCoord);
}

unsigned int RESPHB::getHopCount() const
{
    return this->hopCount;
}

void RESPHB::setHopCount(unsigned int hopCount)
{
    handleChange();
    this->hopCount = hopCount;
}

const L3Address& RESPHB::getDestAddr() const
{
    return this->destAddr;
}

void RESPHB::setDestAddr(const L3Address& destAddr)
{
    handleChange();
    this->destAddr = destAddr;
}

const L3Address& RESPHB::getSourceAddr() const
{
    return this->sourceAddr;
}

void RESPHB::setSourceAddr(const L3Address& sourceAddr)
{
    handleChange();
    this->sourceAddr = sourceAddr;
}

const L3Address& RESPHB::getChAddr() const
{
    return this->chAddr;
}

void RESPHB::setChAddr(const L3Address& chAddr)
{
    handleChange();
    this->chAddr = chAddr;
}

const L3Address& RESPHB::getOriginatorAddr() const
{
    return this->originatorAddr;
}

void RESPHB::setOriginatorAddr(const L3Address& originatorAddr)
{
    handleChange();
    this->originatorAddr = originatorAddr;
}

uint32_t RESPHB::getBatteryPercent() const
{
    return this->batteryPercent;
}

void RESPHB::setBatteryPercent(uint32_t batteryPercent)
{
    handleChange();
    this->batteryPercent = batteryPercent;
}

const Coord& RESPHB::getSenderCoord() const
{
    return this->senderCoord;
}

void RESPHB::setSenderCoord(const Coord& senderCoord)
{
    handleChange();
    this->senderCoord = senderCoord;
}

class RESPHBDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
    enum FieldConstants {
        FIELD_hopCount,
        FIELD_destAddr,
        FIELD_sourceAddr,
        FIELD_chAddr,
        FIELD_originatorAddr,
        FIELD_batteryPercent,
        FIELD_senderCoord,
    };
  public:
    RESPHBDescriptor();
    virtual ~RESPHBDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyname) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyname) const override;
    virtual int getFieldArraySize(void *object, int field) const override;

    virtual const char *getFieldDynamicTypeString(void *object, int field, int i) const override;
    virtual std::string getFieldValueAsString(void *object, int field, int i) const override;
    virtual bool setFieldValueAsString(void *object, int field, int i, const char *value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual void *getFieldStructValuePointer(void *object, int field, int i) const override;
};

Register_ClassDescriptor(RESPHBDescriptor)

RESPHBDescriptor::RESPHBDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::wirelessrouting::RESPHB)), "inet::wirelessrouting::HeartBeat")
{
    propertynames = nullptr;
}

RESPHBDescriptor::~RESPHBDescriptor()
{
    delete[] propertynames;
}

bool RESPHBDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<RESPHB *>(obj)!=nullptr;
}

const char **RESPHBDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *RESPHBDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int RESPHBDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 7+basedesc->getFieldCount() : 7;
}

unsigned int RESPHBDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_hopCount
        0,    // FIELD_destAddr
        0,    // FIELD_sourceAddr
        0,    // FIELD_chAddr
        0,    // FIELD_originatorAddr
        FD_ISEDITABLE,    // FIELD_batteryPercent
        FD_ISCOMPOUND,    // FIELD_senderCoord
    };
    return (field >= 0 && field < 7) ? fieldTypeFlags[field] : 0;
}

const char *RESPHBDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "hopCount",
        "destAddr",
        "sourceAddr",
        "chAddr",
        "originatorAddr",
        "batteryPercent",
        "senderCoord",
    };
    return (field >= 0 && field < 7) ? fieldNames[field] : nullptr;
}

int RESPHBDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0] == 'h' && strcmp(fieldName, "hopCount") == 0) return base+0;
    if (fieldName[0] == 'd' && strcmp(fieldName, "destAddr") == 0) return base+1;
    if (fieldName[0] == 's' && strcmp(fieldName, "sourceAddr") == 0) return base+2;
    if (fieldName[0] == 'c' && strcmp(fieldName, "chAddr") == 0) return base+3;
    if (fieldName[0] == 'o' && strcmp(fieldName, "originatorAddr") == 0) return base+4;
    if (fieldName[0] == 'b' && strcmp(fieldName, "batteryPercent") == 0) return base+5;
    if (fieldName[0] == 's' && strcmp(fieldName, "senderCoord") == 0) return base+6;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *RESPHBDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "unsigned int",    // FIELD_hopCount
        "inet::L3Address",    // FIELD_destAddr
        "inet::L3Address",    // FIELD_sourceAddr
        "inet::L3Address",    // FIELD_chAddr
        "inet::L3Address",    // FIELD_originatorAddr
        "uint32_t",    // FIELD_batteryPercent
        "inet::Coord",    // FIELD_senderCoord
    };
    return (field >= 0 && field < 7) ? fieldTypeStrings[field] : nullptr;
}

const char **RESPHBDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldPropertyNames(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *RESPHBDescriptor::getFieldProperty(int field, const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldProperty(field, propertyname);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int RESPHBDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    RESPHB *pp = (RESPHB *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

const char *RESPHBDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    RESPHB *pp = (RESPHB *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string RESPHBDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    RESPHB *pp = (RESPHB *)object; (void)pp;
    switch (field) {
        case FIELD_hopCount: return ulong2string(pp->getHopCount());
        case FIELD_destAddr: return pp->getDestAddr().str();
        case FIELD_sourceAddr: return pp->getSourceAddr().str();
        case FIELD_chAddr: return pp->getChAddr().str();
        case FIELD_originatorAddr: return pp->getOriginatorAddr().str();
        case FIELD_batteryPercent: return ulong2string(pp->getBatteryPercent());
        case FIELD_senderCoord: {std::stringstream out; out << pp->getSenderCoord(); return out.str();}
        default: return "";
    }
}

bool RESPHBDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    RESPHB *pp = (RESPHB *)object; (void)pp;
    switch (field) {
        case FIELD_hopCount: pp->setHopCount(string2ulong(value)); return true;
        case FIELD_batteryPercent: pp->setBatteryPercent(string2ulong(value)); return true;
        default: return false;
    }
}

const char *RESPHBDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructName(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        case FIELD_senderCoord: return omnetpp::opp_typename(typeid(Coord));
        default: return nullptr;
    };
}

void *RESPHBDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    RESPHB *pp = (RESPHB *)object; (void)pp;
    switch (field) {
        case FIELD_destAddr: return toVoidPtr(&pp->getDestAddr()); break;
        case FIELD_sourceAddr: return toVoidPtr(&pp->getSourceAddr()); break;
        case FIELD_chAddr: return toVoidPtr(&pp->getChAddr()); break;
        case FIELD_originatorAddr: return toVoidPtr(&pp->getOriginatorAddr()); break;
        case FIELD_senderCoord: return toVoidPtr(&pp->getSenderCoord()); break;
        default: return nullptr;
    }
}

Register_Class(CAINMSG)

CAINMSG::CAINMSG() : ::inet::wirelessrouting::HeartBeat()
{
}

CAINMSG::CAINMSG(const CAINMSG& other) : ::inet::wirelessrouting::HeartBeat(other)
{
    copy(other);
}

CAINMSG::~CAINMSG()
{
}

CAINMSG& CAINMSG::operator=(const CAINMSG& other)
{
    if (this == &other) return *this;
    ::inet::wirelessrouting::HeartBeat::operator=(other);
    copy(other);
    return *this;
}

void CAINMSG::copy(const CAINMSG& other)
{
    this->hopCount = other.hopCount;
    this->destAddr = other.destAddr;
    this->cainDestAddr = other.cainDestAddr;
    this->originatorAddr = other.originatorAddr;
    this->sourceAddr = other.sourceAddr;
    this->chAddr = other.chAddr;
    this->lastAddr = other.lastAddr;
    this->rrepSource = other.rrepSource;
    this->ackType = other.ackType;
    this->ackSeqNum = other.ackSeqNum;
    this->seqNum = other.seqNum;
    this->batteryPercent = other.batteryPercent;
    this->chBattery = other.chBattery;
    this->senderCoord = other.senderCoord;
    this->sprayQtdNeigh = other.sprayQtdNeigh;
    this->centrality = other.centrality;
    this->hops = other.hops;
    this->msgId = other.msgId;
    this->distance = other.distance;
    this->timeInit = other.timeInit;
}

void CAINMSG::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::wirelessrouting::HeartBeat::parsimPack(b);
    doParsimPacking(b,this->hopCount);
    doParsimPacking(b,this->destAddr);
    doParsimPacking(b,this->cainDestAddr);
    doParsimPacking(b,this->originatorAddr);
    doParsimPacking(b,this->sourceAddr);
    doParsimPacking(b,this->chAddr);
    doParsimPacking(b,this->lastAddr);
    doParsimPacking(b,this->rrepSource);
    doParsimPacking(b,this->ackType);
    doParsimPacking(b,this->ackSeqNum);
    doParsimPacking(b,this->seqNum);
    doParsimPacking(b,this->batteryPercent);
    doParsimPacking(b,this->chBattery);
    doParsimPacking(b,this->senderCoord);
    doParsimPacking(b,this->sprayQtdNeigh);
    doParsimPacking(b,this->centrality);
    doParsimPacking(b,this->hops);
    doParsimPacking(b,this->msgId);
    doParsimPacking(b,this->distance);
    doParsimPacking(b,this->timeInit);
}

void CAINMSG::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::wirelessrouting::HeartBeat::parsimUnpack(b);
    doParsimUnpacking(b,this->hopCount);
    doParsimUnpacking(b,this->destAddr);
    doParsimUnpacking(b,this->cainDestAddr);
    doParsimUnpacking(b,this->originatorAddr);
    doParsimUnpacking(b,this->sourceAddr);
    doParsimUnpacking(b,this->chAddr);
    doParsimUnpacking(b,this->lastAddr);
    doParsimUnpacking(b,this->rrepSource);
    doParsimUnpacking(b,this->ackType);
    doParsimUnpacking(b,this->ackSeqNum);
    doParsimUnpacking(b,this->seqNum);
    doParsimUnpacking(b,this->batteryPercent);
    doParsimUnpacking(b,this->chBattery);
    doParsimUnpacking(b,this->senderCoord);
    doParsimUnpacking(b,this->sprayQtdNeigh);
    doParsimUnpacking(b,this->centrality);
    doParsimUnpacking(b,this->hops);
    doParsimUnpacking(b,this->msgId);
    doParsimUnpacking(b,this->distance);
    doParsimUnpacking(b,this->timeInit);
}

unsigned int CAINMSG::getHopCount() const
{
    return this->hopCount;
}

void CAINMSG::setHopCount(unsigned int hopCount)
{
    handleChange();
    this->hopCount = hopCount;
}

const L3Address& CAINMSG::getDestAddr() const
{
    return this->destAddr;
}

void CAINMSG::setDestAddr(const L3Address& destAddr)
{
    handleChange();
    this->destAddr = destAddr;
}

const L3Address& CAINMSG::getCainDestAddr() const
{
    return this->cainDestAddr;
}

void CAINMSG::setCainDestAddr(const L3Address& cainDestAddr)
{
    handleChange();
    this->cainDestAddr = cainDestAddr;
}

const L3Address& CAINMSG::getOriginatorAddr() const
{
    return this->originatorAddr;
}

void CAINMSG::setOriginatorAddr(const L3Address& originatorAddr)
{
    handleChange();
    this->originatorAddr = originatorAddr;
}

const L3Address& CAINMSG::getSourceAddr() const
{
    return this->sourceAddr;
}

void CAINMSG::setSourceAddr(const L3Address& sourceAddr)
{
    handleChange();
    this->sourceAddr = sourceAddr;
}

const L3Address& CAINMSG::getChAddr() const
{
    return this->chAddr;
}

void CAINMSG::setChAddr(const L3Address& chAddr)
{
    handleChange();
    this->chAddr = chAddr;
}

const L3Address& CAINMSG::getLastAddr() const
{
    return this->lastAddr;
}

void CAINMSG::setLastAddr(const L3Address& lastAddr)
{
    handleChange();
    this->lastAddr = lastAddr;
}

const L3Address& CAINMSG::getRrepSource() const
{
    return this->rrepSource;
}

void CAINMSG::setRrepSource(const L3Address& rrepSource)
{
    handleChange();
    this->rrepSource = rrepSource;
}

inet::wirelessrouting::heartBeatType CAINMSG::getAckType() const
{
    return this->ackType;
}

void CAINMSG::setAckType(inet::wirelessrouting::heartBeatType ackType)
{
    handleChange();
    this->ackType = ackType;
}

uint32_t CAINMSG::getAckSeqNum() const
{
    return this->ackSeqNum;
}

void CAINMSG::setAckSeqNum(uint32_t ackSeqNum)
{
    handleChange();
    this->ackSeqNum = ackSeqNum;
}

uint32_t CAINMSG::getSeqNum() const
{
    return this->seqNum;
}

void CAINMSG::setSeqNum(uint32_t seqNum)
{
    handleChange();
    this->seqNum = seqNum;
}

uint32_t CAINMSG::getBatteryPercent() const
{
    return this->batteryPercent;
}

void CAINMSG::setBatteryPercent(uint32_t batteryPercent)
{
    handleChange();
    this->batteryPercent = batteryPercent;
}

uint32_t CAINMSG::getChBattery() const
{
    return this->chBattery;
}

void CAINMSG::setChBattery(uint32_t chBattery)
{
    handleChange();
    this->chBattery = chBattery;
}

const Coord& CAINMSG::getSenderCoord() const
{
    return this->senderCoord;
}

void CAINMSG::setSenderCoord(const Coord& senderCoord)
{
    handleChange();
    this->senderCoord = senderCoord;
}

uint32_t CAINMSG::getSprayQtdNeigh() const
{
    return this->sprayQtdNeigh;
}

void CAINMSG::setSprayQtdNeigh(uint32_t sprayQtdNeigh)
{
    handleChange();
    this->sprayQtdNeigh = sprayQtdNeigh;
}

uint32_t CAINMSG::getCentrality() const
{
    return this->centrality;
}

void CAINMSG::setCentrality(uint32_t centrality)
{
    handleChange();
    this->centrality = centrality;
}

unsigned int CAINMSG::getHops() const
{
    return this->hops;
}

void CAINMSG::setHops(unsigned int hops)
{
    handleChange();
    this->hops = hops;
}

const char * CAINMSG::getMsgId() const
{
    return this->msgId.c_str();
}

void CAINMSG::setMsgId(const char * msgId)
{
    handleChange();
    this->msgId = msgId;
}

double CAINMSG::getDistance() const
{
    return this->distance;
}

void CAINMSG::setDistance(double distance)
{
    handleChange();
    this->distance = distance;
}

omnetpp::simtime_t CAINMSG::getTimeInit() const
{
    return this->timeInit;
}

void CAINMSG::setTimeInit(omnetpp::simtime_t timeInit)
{
    handleChange();
    this->timeInit = timeInit;
}

class CAINMSGDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
    enum FieldConstants {
        FIELD_hopCount,
        FIELD_destAddr,
        FIELD_cainDestAddr,
        FIELD_originatorAddr,
        FIELD_sourceAddr,
        FIELD_chAddr,
        FIELD_lastAddr,
        FIELD_rrepSource,
        FIELD_ackType,
        FIELD_ackSeqNum,
        FIELD_seqNum,
        FIELD_batteryPercent,
        FIELD_chBattery,
        FIELD_senderCoord,
        FIELD_sprayQtdNeigh,
        FIELD_centrality,
        FIELD_hops,
        FIELD_msgId,
        FIELD_distance,
        FIELD_timeInit,
    };
  public:
    CAINMSGDescriptor();
    virtual ~CAINMSGDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyname) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyname) const override;
    virtual int getFieldArraySize(void *object, int field) const override;

    virtual const char *getFieldDynamicTypeString(void *object, int field, int i) const override;
    virtual std::string getFieldValueAsString(void *object, int field, int i) const override;
    virtual bool setFieldValueAsString(void *object, int field, int i, const char *value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual void *getFieldStructValuePointer(void *object, int field, int i) const override;
};

Register_ClassDescriptor(CAINMSGDescriptor)

CAINMSGDescriptor::CAINMSGDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::wirelessrouting::CAINMSG)), "inet::wirelessrouting::HeartBeat")
{
    propertynames = nullptr;
}

CAINMSGDescriptor::~CAINMSGDescriptor()
{
    delete[] propertynames;
}

bool CAINMSGDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<CAINMSG *>(obj)!=nullptr;
}

const char **CAINMSGDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *CAINMSGDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int CAINMSGDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 20+basedesc->getFieldCount() : 20;
}

unsigned int CAINMSGDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_hopCount
        0,    // FIELD_destAddr
        0,    // FIELD_cainDestAddr
        0,    // FIELD_originatorAddr
        0,    // FIELD_sourceAddr
        0,    // FIELD_chAddr
        0,    // FIELD_lastAddr
        0,    // FIELD_rrepSource
        FD_ISEDITABLE,    // FIELD_ackType
        FD_ISEDITABLE,    // FIELD_ackSeqNum
        FD_ISEDITABLE,    // FIELD_seqNum
        FD_ISEDITABLE,    // FIELD_batteryPercent
        FD_ISEDITABLE,    // FIELD_chBattery
        FD_ISCOMPOUND,    // FIELD_senderCoord
        FD_ISEDITABLE,    // FIELD_sprayQtdNeigh
        FD_ISEDITABLE,    // FIELD_centrality
        FD_ISEDITABLE,    // FIELD_hops
        FD_ISEDITABLE,    // FIELD_msgId
        FD_ISEDITABLE,    // FIELD_distance
        0,    // FIELD_timeInit
    };
    return (field >= 0 && field < 20) ? fieldTypeFlags[field] : 0;
}

const char *CAINMSGDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "hopCount",
        "destAddr",
        "cainDestAddr",
        "originatorAddr",
        "sourceAddr",
        "chAddr",
        "lastAddr",
        "rrepSource",
        "ackType",
        "ackSeqNum",
        "seqNum",
        "batteryPercent",
        "chBattery",
        "senderCoord",
        "sprayQtdNeigh",
        "centrality",
        "hops",
        "msgId",
        "distance",
        "timeInit",
    };
    return (field >= 0 && field < 20) ? fieldNames[field] : nullptr;
}

int CAINMSGDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0] == 'h' && strcmp(fieldName, "hopCount") == 0) return base+0;
    if (fieldName[0] == 'd' && strcmp(fieldName, "destAddr") == 0) return base+1;
    if (fieldName[0] == 'c' && strcmp(fieldName, "cainDestAddr") == 0) return base+2;
    if (fieldName[0] == 'o' && strcmp(fieldName, "originatorAddr") == 0) return base+3;
    if (fieldName[0] == 's' && strcmp(fieldName, "sourceAddr") == 0) return base+4;
    if (fieldName[0] == 'c' && strcmp(fieldName, "chAddr") == 0) return base+5;
    if (fieldName[0] == 'l' && strcmp(fieldName, "lastAddr") == 0) return base+6;
    if (fieldName[0] == 'r' && strcmp(fieldName, "rrepSource") == 0) return base+7;
    if (fieldName[0] == 'a' && strcmp(fieldName, "ackType") == 0) return base+8;
    if (fieldName[0] == 'a' && strcmp(fieldName, "ackSeqNum") == 0) return base+9;
    if (fieldName[0] == 's' && strcmp(fieldName, "seqNum") == 0) return base+10;
    if (fieldName[0] == 'b' && strcmp(fieldName, "batteryPercent") == 0) return base+11;
    if (fieldName[0] == 'c' && strcmp(fieldName, "chBattery") == 0) return base+12;
    if (fieldName[0] == 's' && strcmp(fieldName, "senderCoord") == 0) return base+13;
    if (fieldName[0] == 's' && strcmp(fieldName, "sprayQtdNeigh") == 0) return base+14;
    if (fieldName[0] == 'c' && strcmp(fieldName, "centrality") == 0) return base+15;
    if (fieldName[0] == 'h' && strcmp(fieldName, "hops") == 0) return base+16;
    if (fieldName[0] == 'm' && strcmp(fieldName, "msgId") == 0) return base+17;
    if (fieldName[0] == 'd' && strcmp(fieldName, "distance") == 0) return base+18;
    if (fieldName[0] == 't' && strcmp(fieldName, "timeInit") == 0) return base+19;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *CAINMSGDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "unsigned int",    // FIELD_hopCount
        "inet::L3Address",    // FIELD_destAddr
        "inet::L3Address",    // FIELD_cainDestAddr
        "inet::L3Address",    // FIELD_originatorAddr
        "inet::L3Address",    // FIELD_sourceAddr
        "inet::L3Address",    // FIELD_chAddr
        "inet::L3Address",    // FIELD_lastAddr
        "inet::L3Address",    // FIELD_rrepSource
        "inet::wirelessrouting::heartBeatType",    // FIELD_ackType
        "uint32_t",    // FIELD_ackSeqNum
        "uint32_t",    // FIELD_seqNum
        "uint32_t",    // FIELD_batteryPercent
        "uint32_t",    // FIELD_chBattery
        "inet::Coord",    // FIELD_senderCoord
        "uint32_t",    // FIELD_sprayQtdNeigh
        "uint32_t",    // FIELD_centrality
        "unsigned int",    // FIELD_hops
        "string",    // FIELD_msgId
        "double",    // FIELD_distance
        "omnetpp::simtime_t",    // FIELD_timeInit
    };
    return (field >= 0 && field < 20) ? fieldTypeStrings[field] : nullptr;
}

const char **CAINMSGDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldPropertyNames(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        case FIELD_ackType: {
            static const char *names[] = { "enum",  nullptr };
            return names;
        }
        default: return nullptr;
    }
}

const char *CAINMSGDescriptor::getFieldProperty(int field, const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldProperty(field, propertyname);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        case FIELD_ackType:
            if (!strcmp(propertyname, "enum")) return "inet::wirelessrouting::heartBeatType";
            return nullptr;
        default: return nullptr;
    }
}

int CAINMSGDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    CAINMSG *pp = (CAINMSG *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

const char *CAINMSGDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    CAINMSG *pp = (CAINMSG *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string CAINMSGDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    CAINMSG *pp = (CAINMSG *)object; (void)pp;
    switch (field) {
        case FIELD_hopCount: return ulong2string(pp->getHopCount());
        case FIELD_destAddr: return pp->getDestAddr().str();
        case FIELD_cainDestAddr: return pp->getCainDestAddr().str();
        case FIELD_originatorAddr: return pp->getOriginatorAddr().str();
        case FIELD_sourceAddr: return pp->getSourceAddr().str();
        case FIELD_chAddr: return pp->getChAddr().str();
        case FIELD_lastAddr: return pp->getLastAddr().str();
        case FIELD_rrepSource: return pp->getRrepSource().str();
        case FIELD_ackType: return enum2string(pp->getAckType(), "inet::wirelessrouting::heartBeatType");
        case FIELD_ackSeqNum: return ulong2string(pp->getAckSeqNum());
        case FIELD_seqNum: return ulong2string(pp->getSeqNum());
        case FIELD_batteryPercent: return ulong2string(pp->getBatteryPercent());
        case FIELD_chBattery: return ulong2string(pp->getChBattery());
        case FIELD_senderCoord: {std::stringstream out; out << pp->getSenderCoord(); return out.str();}
        case FIELD_sprayQtdNeigh: return ulong2string(pp->getSprayQtdNeigh());
        case FIELD_centrality: return ulong2string(pp->getCentrality());
        case FIELD_hops: return ulong2string(pp->getHops());
        case FIELD_msgId: return oppstring2string(pp->getMsgId());
        case FIELD_distance: return double2string(pp->getDistance());
        case FIELD_timeInit: return simtime2string(pp->getTimeInit());
        default: return "";
    }
}

bool CAINMSGDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    CAINMSG *pp = (CAINMSG *)object; (void)pp;
    switch (field) {
        case FIELD_hopCount: pp->setHopCount(string2ulong(value)); return true;
        case FIELD_ackType: pp->setAckType((inet::wirelessrouting::heartBeatType)string2enum(value, "inet::wirelessrouting::heartBeatType")); return true;
        case FIELD_ackSeqNum: pp->setAckSeqNum(string2ulong(value)); return true;
        case FIELD_seqNum: pp->setSeqNum(string2ulong(value)); return true;
        case FIELD_batteryPercent: pp->setBatteryPercent(string2ulong(value)); return true;
        case FIELD_chBattery: pp->setChBattery(string2ulong(value)); return true;
        case FIELD_sprayQtdNeigh: pp->setSprayQtdNeigh(string2ulong(value)); return true;
        case FIELD_centrality: pp->setCentrality(string2ulong(value)); return true;
        case FIELD_hops: pp->setHops(string2ulong(value)); return true;
        case FIELD_msgId: pp->setMsgId((value)); return true;
        case FIELD_distance: pp->setDistance(string2double(value)); return true;
        default: return false;
    }
}

const char *CAINMSGDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructName(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        case FIELD_senderCoord: return omnetpp::opp_typename(typeid(Coord));
        default: return nullptr;
    };
}

void *CAINMSGDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    CAINMSG *pp = (CAINMSG *)object; (void)pp;
    switch (field) {
        case FIELD_destAddr: return toVoidPtr(&pp->getDestAddr()); break;
        case FIELD_cainDestAddr: return toVoidPtr(&pp->getCainDestAddr()); break;
        case FIELD_originatorAddr: return toVoidPtr(&pp->getOriginatorAddr()); break;
        case FIELD_sourceAddr: return toVoidPtr(&pp->getSourceAddr()); break;
        case FIELD_chAddr: return toVoidPtr(&pp->getChAddr()); break;
        case FIELD_lastAddr: return toVoidPtr(&pp->getLastAddr()); break;
        case FIELD_rrepSource: return toVoidPtr(&pp->getRrepSource()); break;
        case FIELD_senderCoord: return toVoidPtr(&pp->getSenderCoord()); break;
        default: return nullptr;
    }
}

Register_Class(Rrep)

Rrep::Rrep() : ::inet::wirelessrouting::HeartBeat()
{
}

Rrep::Rrep(const Rrep& other) : ::inet::wirelessrouting::HeartBeat(other)
{
    copy(other);
}

Rrep::~Rrep()
{
}

Rrep& Rrep::operator=(const Rrep& other)
{
    if (this == &other) return *this;
    ::inet::wirelessrouting::HeartBeat::operator=(other);
    copy(other);
    return *this;
}

void Rrep::copy(const Rrep& other)
{
    this->heartBeatType = other.heartBeatType;
    this->hopCount = other.hopCount;
    this->rreqId = other.rreqId;
    this->destAddr = other.destAddr;
    this->destSeqNum = other.destSeqNum;
    this->originatorAddr = other.originatorAddr;
    this->originatorSeqNum = other.originatorSeqNum;
}

void Rrep::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::wirelessrouting::HeartBeat::parsimPack(b);
    doParsimPacking(b,this->heartBeatType);
    doParsimPacking(b,this->hopCount);
    doParsimPacking(b,this->rreqId);
    doParsimPacking(b,this->destAddr);
    doParsimPacking(b,this->destSeqNum);
    doParsimPacking(b,this->originatorAddr);
    doParsimPacking(b,this->originatorSeqNum);
}

void Rrep::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::wirelessrouting::HeartBeat::parsimUnpack(b);
    doParsimUnpacking(b,this->heartBeatType);
    doParsimUnpacking(b,this->hopCount);
    doParsimUnpacking(b,this->rreqId);
    doParsimUnpacking(b,this->destAddr);
    doParsimUnpacking(b,this->destSeqNum);
    doParsimUnpacking(b,this->originatorAddr);
    doParsimUnpacking(b,this->originatorSeqNum);
}

unsigned int Rrep::getHeartBeatType() const
{
    return this->heartBeatType;
}

void Rrep::setHeartBeatType(unsigned int heartBeatType)
{
    handleChange();
    this->heartBeatType = heartBeatType;
}

unsigned int Rrep::getHopCount() const
{
    return this->hopCount;
}

void Rrep::setHopCount(unsigned int hopCount)
{
    handleChange();
    this->hopCount = hopCount;
}

unsigned int Rrep::getRreqId() const
{
    return this->rreqId;
}

void Rrep::setRreqId(unsigned int rreqId)
{
    handleChange();
    this->rreqId = rreqId;
}

const L3Address& Rrep::getDestAddr() const
{
    return this->destAddr;
}

void Rrep::setDestAddr(const L3Address& destAddr)
{
    handleChange();
    this->destAddr = destAddr;
}

unsigned int Rrep::getDestSeqNum() const
{
    return this->destSeqNum;
}

void Rrep::setDestSeqNum(unsigned int destSeqNum)
{
    handleChange();
    this->destSeqNum = destSeqNum;
}

const L3Address& Rrep::getOriginatorAddr() const
{
    return this->originatorAddr;
}

void Rrep::setOriginatorAddr(const L3Address& originatorAddr)
{
    handleChange();
    this->originatorAddr = originatorAddr;
}

unsigned int Rrep::getOriginatorSeqNum() const
{
    return this->originatorSeqNum;
}

void Rrep::setOriginatorSeqNum(unsigned int originatorSeqNum)
{
    handleChange();
    this->originatorSeqNum = originatorSeqNum;
}

class RrepDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
    enum FieldConstants {
        FIELD_heartBeatType,
        FIELD_hopCount,
        FIELD_rreqId,
        FIELD_destAddr,
        FIELD_destSeqNum,
        FIELD_originatorAddr,
        FIELD_originatorSeqNum,
    };
  public:
    RrepDescriptor();
    virtual ~RrepDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyname) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyname) const override;
    virtual int getFieldArraySize(void *object, int field) const override;

    virtual const char *getFieldDynamicTypeString(void *object, int field, int i) const override;
    virtual std::string getFieldValueAsString(void *object, int field, int i) const override;
    virtual bool setFieldValueAsString(void *object, int field, int i, const char *value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual void *getFieldStructValuePointer(void *object, int field, int i) const override;
};

Register_ClassDescriptor(RrepDescriptor)

RrepDescriptor::RrepDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::wirelessrouting::Rrep)), "inet::wirelessrouting::HeartBeat")
{
    propertynames = nullptr;
}

RrepDescriptor::~RrepDescriptor()
{
    delete[] propertynames;
}

bool RrepDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<Rrep *>(obj)!=nullptr;
}

const char **RrepDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *RrepDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int RrepDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 7+basedesc->getFieldCount() : 7;
}

unsigned int RrepDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_heartBeatType
        FD_ISEDITABLE,    // FIELD_hopCount
        FD_ISEDITABLE,    // FIELD_rreqId
        0,    // FIELD_destAddr
        FD_ISEDITABLE,    // FIELD_destSeqNum
        0,    // FIELD_originatorAddr
        FD_ISEDITABLE,    // FIELD_originatorSeqNum
    };
    return (field >= 0 && field < 7) ? fieldTypeFlags[field] : 0;
}

const char *RrepDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "heartBeatType",
        "hopCount",
        "rreqId",
        "destAddr",
        "destSeqNum",
        "originatorAddr",
        "originatorSeqNum",
    };
    return (field >= 0 && field < 7) ? fieldNames[field] : nullptr;
}

int RrepDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0] == 'h' && strcmp(fieldName, "heartBeatType") == 0) return base+0;
    if (fieldName[0] == 'h' && strcmp(fieldName, "hopCount") == 0) return base+1;
    if (fieldName[0] == 'r' && strcmp(fieldName, "rreqId") == 0) return base+2;
    if (fieldName[0] == 'd' && strcmp(fieldName, "destAddr") == 0) return base+3;
    if (fieldName[0] == 'd' && strcmp(fieldName, "destSeqNum") == 0) return base+4;
    if (fieldName[0] == 'o' && strcmp(fieldName, "originatorAddr") == 0) return base+5;
    if (fieldName[0] == 'o' && strcmp(fieldName, "originatorSeqNum") == 0) return base+6;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *RrepDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "unsigned int",    // FIELD_heartBeatType
        "unsigned int",    // FIELD_hopCount
        "unsigned int",    // FIELD_rreqId
        "inet::L3Address",    // FIELD_destAddr
        "unsigned int",    // FIELD_destSeqNum
        "inet::L3Address",    // FIELD_originatorAddr
        "unsigned int",    // FIELD_originatorSeqNum
    };
    return (field >= 0 && field < 7) ? fieldTypeStrings[field] : nullptr;
}

const char **RrepDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldPropertyNames(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *RrepDescriptor::getFieldProperty(int field, const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldProperty(field, propertyname);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int RrepDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    Rrep *pp = (Rrep *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

const char *RrepDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    Rrep *pp = (Rrep *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string RrepDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    Rrep *pp = (Rrep *)object; (void)pp;
    switch (field) {
        case FIELD_heartBeatType: return ulong2string(pp->getHeartBeatType());
        case FIELD_hopCount: return ulong2string(pp->getHopCount());
        case FIELD_rreqId: return ulong2string(pp->getRreqId());
        case FIELD_destAddr: return pp->getDestAddr().str();
        case FIELD_destSeqNum: return ulong2string(pp->getDestSeqNum());
        case FIELD_originatorAddr: return pp->getOriginatorAddr().str();
        case FIELD_originatorSeqNum: return ulong2string(pp->getOriginatorSeqNum());
        default: return "";
    }
}

bool RrepDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    Rrep *pp = (Rrep *)object; (void)pp;
    switch (field) {
        case FIELD_heartBeatType: pp->setHeartBeatType(string2ulong(value)); return true;
        case FIELD_hopCount: pp->setHopCount(string2ulong(value)); return true;
        case FIELD_rreqId: pp->setRreqId(string2ulong(value)); return true;
        case FIELD_destSeqNum: pp->setDestSeqNum(string2ulong(value)); return true;
        case FIELD_originatorSeqNum: pp->setOriginatorSeqNum(string2ulong(value)); return true;
        default: return false;
    }
}

const char *RrepDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructName(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    };
}

void *RrepDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    Rrep *pp = (Rrep *)object; (void)pp;
    switch (field) {
        case FIELD_destAddr: return toVoidPtr(&pp->getDestAddr()); break;
        case FIELD_originatorAddr: return toVoidPtr(&pp->getOriginatorAddr()); break;
        default: return nullptr;
    }
}

Register_Class(Rreq)

Rreq::Rreq() : ::inet::wirelessrouting::HeartBeat()
{
}

Rreq::Rreq(const Rreq& other) : ::inet::wirelessrouting::HeartBeat(other)
{
    copy(other);
}

Rreq::~Rreq()
{
}

Rreq& Rreq::operator=(const Rreq& other)
{
    if (this == &other) return *this;
    ::inet::wirelessrouting::HeartBeat::operator=(other);
    copy(other);
    return *this;
}

void Rreq::copy(const Rreq& other)
{
    this->heartBeatType = other.heartBeatType;
    this->hopCount = other.hopCount;
    this->rreqId = other.rreqId;
    this->destAddr = other.destAddr;
    this->destSeqNum = other.destSeqNum;
    this->originatorAddr = other.originatorAddr;
    this->originatorSeqNum = other.originatorSeqNum;
}

void Rreq::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::wirelessrouting::HeartBeat::parsimPack(b);
    doParsimPacking(b,this->heartBeatType);
    doParsimPacking(b,this->hopCount);
    doParsimPacking(b,this->rreqId);
    doParsimPacking(b,this->destAddr);
    doParsimPacking(b,this->destSeqNum);
    doParsimPacking(b,this->originatorAddr);
    doParsimPacking(b,this->originatorSeqNum);
}

void Rreq::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::wirelessrouting::HeartBeat::parsimUnpack(b);
    doParsimUnpacking(b,this->heartBeatType);
    doParsimUnpacking(b,this->hopCount);
    doParsimUnpacking(b,this->rreqId);
    doParsimUnpacking(b,this->destAddr);
    doParsimUnpacking(b,this->destSeqNum);
    doParsimUnpacking(b,this->originatorAddr);
    doParsimUnpacking(b,this->originatorSeqNum);
}

unsigned int Rreq::getHeartBeatType() const
{
    return this->heartBeatType;
}

void Rreq::setHeartBeatType(unsigned int heartBeatType)
{
    handleChange();
    this->heartBeatType = heartBeatType;
}

unsigned int Rreq::getHopCount() const
{
    return this->hopCount;
}

void Rreq::setHopCount(unsigned int hopCount)
{
    handleChange();
    this->hopCount = hopCount;
}

unsigned int Rreq::getRreqId() const
{
    return this->rreqId;
}

void Rreq::setRreqId(unsigned int rreqId)
{
    handleChange();
    this->rreqId = rreqId;
}

const L3Address& Rreq::getDestAddr() const
{
    return this->destAddr;
}

void Rreq::setDestAddr(const L3Address& destAddr)
{
    handleChange();
    this->destAddr = destAddr;
}

unsigned int Rreq::getDestSeqNum() const
{
    return this->destSeqNum;
}

void Rreq::setDestSeqNum(unsigned int destSeqNum)
{
    handleChange();
    this->destSeqNum = destSeqNum;
}

const L3Address& Rreq::getOriginatorAddr() const
{
    return this->originatorAddr;
}

void Rreq::setOriginatorAddr(const L3Address& originatorAddr)
{
    handleChange();
    this->originatorAddr = originatorAddr;
}

unsigned int Rreq::getOriginatorSeqNum() const
{
    return this->originatorSeqNum;
}

void Rreq::setOriginatorSeqNum(unsigned int originatorSeqNum)
{
    handleChange();
    this->originatorSeqNum = originatorSeqNum;
}

class RreqDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
    enum FieldConstants {
        FIELD_heartBeatType,
        FIELD_hopCount,
        FIELD_rreqId,
        FIELD_destAddr,
        FIELD_destSeqNum,
        FIELD_originatorAddr,
        FIELD_originatorSeqNum,
    };
  public:
    RreqDescriptor();
    virtual ~RreqDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyname) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyname) const override;
    virtual int getFieldArraySize(void *object, int field) const override;

    virtual const char *getFieldDynamicTypeString(void *object, int field, int i) const override;
    virtual std::string getFieldValueAsString(void *object, int field, int i) const override;
    virtual bool setFieldValueAsString(void *object, int field, int i, const char *value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual void *getFieldStructValuePointer(void *object, int field, int i) const override;
};

Register_ClassDescriptor(RreqDescriptor)

RreqDescriptor::RreqDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::wirelessrouting::Rreq)), "inet::wirelessrouting::HeartBeat")
{
    propertynames = nullptr;
}

RreqDescriptor::~RreqDescriptor()
{
    delete[] propertynames;
}

bool RreqDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<Rreq *>(obj)!=nullptr;
}

const char **RreqDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *RreqDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int RreqDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 7+basedesc->getFieldCount() : 7;
}

unsigned int RreqDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_heartBeatType
        FD_ISEDITABLE,    // FIELD_hopCount
        FD_ISEDITABLE,    // FIELD_rreqId
        0,    // FIELD_destAddr
        FD_ISEDITABLE,    // FIELD_destSeqNum
        0,    // FIELD_originatorAddr
        FD_ISEDITABLE,    // FIELD_originatorSeqNum
    };
    return (field >= 0 && field < 7) ? fieldTypeFlags[field] : 0;
}

const char *RreqDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "heartBeatType",
        "hopCount",
        "rreqId",
        "destAddr",
        "destSeqNum",
        "originatorAddr",
        "originatorSeqNum",
    };
    return (field >= 0 && field < 7) ? fieldNames[field] : nullptr;
}

int RreqDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0] == 'h' && strcmp(fieldName, "heartBeatType") == 0) return base+0;
    if (fieldName[0] == 'h' && strcmp(fieldName, "hopCount") == 0) return base+1;
    if (fieldName[0] == 'r' && strcmp(fieldName, "rreqId") == 0) return base+2;
    if (fieldName[0] == 'd' && strcmp(fieldName, "destAddr") == 0) return base+3;
    if (fieldName[0] == 'd' && strcmp(fieldName, "destSeqNum") == 0) return base+4;
    if (fieldName[0] == 'o' && strcmp(fieldName, "originatorAddr") == 0) return base+5;
    if (fieldName[0] == 'o' && strcmp(fieldName, "originatorSeqNum") == 0) return base+6;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *RreqDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "unsigned int",    // FIELD_heartBeatType
        "unsigned int",    // FIELD_hopCount
        "unsigned int",    // FIELD_rreqId
        "inet::L3Address",    // FIELD_destAddr
        "unsigned int",    // FIELD_destSeqNum
        "inet::L3Address",    // FIELD_originatorAddr
        "unsigned int",    // FIELD_originatorSeqNum
    };
    return (field >= 0 && field < 7) ? fieldTypeStrings[field] : nullptr;
}

const char **RreqDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldPropertyNames(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *RreqDescriptor::getFieldProperty(int field, const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldProperty(field, propertyname);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int RreqDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    Rreq *pp = (Rreq *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

const char *RreqDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    Rreq *pp = (Rreq *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string RreqDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    Rreq *pp = (Rreq *)object; (void)pp;
    switch (field) {
        case FIELD_heartBeatType: return ulong2string(pp->getHeartBeatType());
        case FIELD_hopCount: return ulong2string(pp->getHopCount());
        case FIELD_rreqId: return ulong2string(pp->getRreqId());
        case FIELD_destAddr: return pp->getDestAddr().str();
        case FIELD_destSeqNum: return ulong2string(pp->getDestSeqNum());
        case FIELD_originatorAddr: return pp->getOriginatorAddr().str();
        case FIELD_originatorSeqNum: return ulong2string(pp->getOriginatorSeqNum());
        default: return "";
    }
}

bool RreqDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    Rreq *pp = (Rreq *)object; (void)pp;
    switch (field) {
        case FIELD_heartBeatType: pp->setHeartBeatType(string2ulong(value)); return true;
        case FIELD_hopCount: pp->setHopCount(string2ulong(value)); return true;
        case FIELD_rreqId: pp->setRreqId(string2ulong(value)); return true;
        case FIELD_destSeqNum: pp->setDestSeqNum(string2ulong(value)); return true;
        case FIELD_originatorSeqNum: pp->setOriginatorSeqNum(string2ulong(value)); return true;
        default: return false;
    }
}

const char *RreqDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructName(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    };
}

void *RreqDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    Rreq *pp = (Rreq *)object; (void)pp;
    switch (field) {
        case FIELD_destAddr: return toVoidPtr(&pp->getDestAddr()); break;
        case FIELD_originatorAddr: return toVoidPtr(&pp->getOriginatorAddr()); break;
        default: return nullptr;
    }
}

Register_Class(Rerr)

Rerr::Rerr() : ::inet::wirelessrouting::HeartBeat()
{
}

Rerr::Rerr(const Rerr& other) : ::inet::wirelessrouting::HeartBeat(other)
{
    copy(other);
}

Rerr::~Rerr()
{
    delete [] this->unreachableNodes;
}

Rerr& Rerr::operator=(const Rerr& other)
{
    if (this == &other) return *this;
    ::inet::wirelessrouting::HeartBeat::operator=(other);
    copy(other);
    return *this;
}

void Rerr::copy(const Rerr& other)
{
    this->noDeleteFlag = other.noDeleteFlag;
    this->reserved = other.reserved;
    delete [] this->unreachableNodes;
    this->unreachableNodes = (other.unreachableNodes_arraysize==0) ? nullptr : new UnreachableNode[other.unreachableNodes_arraysize];
    unreachableNodes_arraysize = other.unreachableNodes_arraysize;
    for (size_t i = 0; i < unreachableNodes_arraysize; i++) {
        this->unreachableNodes[i] = other.unreachableNodes[i];
    }
}

void Rerr::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::wirelessrouting::HeartBeat::parsimPack(b);
    doParsimPacking(b,this->noDeleteFlag);
    doParsimPacking(b,this->reserved);
    b->pack(unreachableNodes_arraysize);
    doParsimArrayPacking(b,this->unreachableNodes,unreachableNodes_arraysize);
}

void Rerr::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::wirelessrouting::HeartBeat::parsimUnpack(b);
    doParsimUnpacking(b,this->noDeleteFlag);
    doParsimUnpacking(b,this->reserved);
    delete [] this->unreachableNodes;
    b->unpack(unreachableNodes_arraysize);
    if (unreachableNodes_arraysize == 0) {
        this->unreachableNodes = nullptr;
    } else {
        this->unreachableNodes = new UnreachableNode[unreachableNodes_arraysize];
        doParsimArrayUnpacking(b,this->unreachableNodes,unreachableNodes_arraysize);
    }
}

bool Rerr::getNoDeleteFlag() const
{
    return this->noDeleteFlag;
}

void Rerr::setNoDeleteFlag(bool noDeleteFlag)
{
    handleChange();
    this->noDeleteFlag = noDeleteFlag;
}

uint16_t Rerr::getReserved() const
{
    return this->reserved;
}

void Rerr::setReserved(uint16_t reserved)
{
    handleChange();
    this->reserved = reserved;
}

size_t Rerr::getUnreachableNodesArraySize() const
{
    return unreachableNodes_arraysize;
}

const UnreachableNode& Rerr::getUnreachableNodes(size_t k) const
{
    if (k >= unreachableNodes_arraysize) throw omnetpp::cRuntimeError("Array of size unreachableNodes_arraysize indexed by %lu", (unsigned long)k);
    return this->unreachableNodes[k];
}

void Rerr::setUnreachableNodesArraySize(size_t newSize)
{
    handleChange();
    UnreachableNode *unreachableNodes2 = (newSize==0) ? nullptr : new UnreachableNode[newSize];
    size_t minSize = unreachableNodes_arraysize < newSize ? unreachableNodes_arraysize : newSize;
    for (size_t i = 0; i < minSize; i++)
        unreachableNodes2[i] = this->unreachableNodes[i];
    delete [] this->unreachableNodes;
    this->unreachableNodes = unreachableNodes2;
    unreachableNodes_arraysize = newSize;
}

void Rerr::setUnreachableNodes(size_t k, const UnreachableNode& unreachableNodes)
{
    if (k >= unreachableNodes_arraysize) throw omnetpp::cRuntimeError("Array of size  indexed by %lu", (unsigned long)k);
    handleChange();
    this->unreachableNodes[k] = unreachableNodes;
}

void Rerr::insertUnreachableNodes(size_t k, const UnreachableNode& unreachableNodes)
{
    handleChange();
    if (k > unreachableNodes_arraysize) throw omnetpp::cRuntimeError("Array of size  indexed by %lu", (unsigned long)k);
    size_t newSize = unreachableNodes_arraysize + 1;
    UnreachableNode *unreachableNodes2 = new UnreachableNode[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        unreachableNodes2[i] = this->unreachableNodes[i];
    unreachableNodes2[k] = unreachableNodes;
    for (i = k + 1; i < newSize; i++)
        unreachableNodes2[i] = this->unreachableNodes[i-1];
    delete [] this->unreachableNodes;
    this->unreachableNodes = unreachableNodes2;
    unreachableNodes_arraysize = newSize;
}

void Rerr::insertUnreachableNodes(const UnreachableNode& unreachableNodes)
{
    insertUnreachableNodes(unreachableNodes_arraysize, unreachableNodes);
}

void Rerr::eraseUnreachableNodes(size_t k)
{
    if (k >= unreachableNodes_arraysize) throw omnetpp::cRuntimeError("Array of size  indexed by %lu", (unsigned long)k);
    handleChange();
    size_t newSize = unreachableNodes_arraysize - 1;
    UnreachableNode *unreachableNodes2 = (newSize == 0) ? nullptr : new UnreachableNode[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        unreachableNodes2[i] = this->unreachableNodes[i];
    for (i = k; i < newSize; i++)
        unreachableNodes2[i] = this->unreachableNodes[i+1];
    delete [] this->unreachableNodes;
    this->unreachableNodes = unreachableNodes2;
    unreachableNodes_arraysize = newSize;
}

class RerrDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
    enum FieldConstants {
        FIELD_noDeleteFlag,
        FIELD_reserved,
        FIELD_unreachableNodes,
    };
  public:
    RerrDescriptor();
    virtual ~RerrDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyname) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyname) const override;
    virtual int getFieldArraySize(void *object, int field) const override;

    virtual const char *getFieldDynamicTypeString(void *object, int field, int i) const override;
    virtual std::string getFieldValueAsString(void *object, int field, int i) const override;
    virtual bool setFieldValueAsString(void *object, int field, int i, const char *value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual void *getFieldStructValuePointer(void *object, int field, int i) const override;
};

Register_ClassDescriptor(RerrDescriptor)

RerrDescriptor::RerrDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::wirelessrouting::Rerr)), "inet::wirelessrouting::HeartBeat")
{
    propertynames = nullptr;
}

RerrDescriptor::~RerrDescriptor()
{
    delete[] propertynames;
}

bool RerrDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<Rerr *>(obj)!=nullptr;
}

const char **RerrDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *RerrDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int RerrDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 3+basedesc->getFieldCount() : 3;
}

unsigned int RerrDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_noDeleteFlag
        FD_ISEDITABLE,    // FIELD_reserved
        FD_ISARRAY | FD_ISCOMPOUND,    // FIELD_unreachableNodes
    };
    return (field >= 0 && field < 3) ? fieldTypeFlags[field] : 0;
}

const char *RerrDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "noDeleteFlag",
        "reserved",
        "unreachableNodes",
    };
    return (field >= 0 && field < 3) ? fieldNames[field] : nullptr;
}

int RerrDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0] == 'n' && strcmp(fieldName, "noDeleteFlag") == 0) return base+0;
    if (fieldName[0] == 'r' && strcmp(fieldName, "reserved") == 0) return base+1;
    if (fieldName[0] == 'u' && strcmp(fieldName, "unreachableNodes") == 0) return base+2;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *RerrDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "bool",    // FIELD_noDeleteFlag
        "uint16_t",    // FIELD_reserved
        "inet::wirelessrouting::UnreachableNode",    // FIELD_unreachableNodes
    };
    return (field >= 0 && field < 3) ? fieldTypeStrings[field] : nullptr;
}

const char **RerrDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldPropertyNames(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *RerrDescriptor::getFieldProperty(int field, const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldProperty(field, propertyname);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int RerrDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    Rerr *pp = (Rerr *)object; (void)pp;
    switch (field) {
        case FIELD_unreachableNodes: return pp->getUnreachableNodesArraySize();
        default: return 0;
    }
}

const char *RerrDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    Rerr *pp = (Rerr *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string RerrDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    Rerr *pp = (Rerr *)object; (void)pp;
    switch (field) {
        case FIELD_noDeleteFlag: return bool2string(pp->getNoDeleteFlag());
        case FIELD_reserved: return ulong2string(pp->getReserved());
        case FIELD_unreachableNodes: {std::stringstream out; out << pp->getUnreachableNodes(i); return out.str();}
        default: return "";
    }
}

bool RerrDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    Rerr *pp = (Rerr *)object; (void)pp;
    switch (field) {
        case FIELD_noDeleteFlag: pp->setNoDeleteFlag(string2bool(value)); return true;
        case FIELD_reserved: pp->setReserved(string2ulong(value)); return true;
        default: return false;
    }
}

const char *RerrDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructName(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        case FIELD_unreachableNodes: return omnetpp::opp_typename(typeid(UnreachableNode));
        default: return nullptr;
    };
}

void *RerrDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    Rerr *pp = (Rerr *)object; (void)pp;
    switch (field) {
        case FIELD_unreachableNodes: return toVoidPtr(&pp->getUnreachableNodes(i)); break;
        default: return nullptr;
    }
}

Register_Class(RrepAck)

RrepAck::RrepAck() : ::inet::wirelessrouting::HeartBeat()
{
}

RrepAck::RrepAck(const RrepAck& other) : ::inet::wirelessrouting::HeartBeat(other)
{
    copy(other);
}

RrepAck::~RrepAck()
{
}

RrepAck& RrepAck::operator=(const RrepAck& other)
{
    if (this == &other) return *this;
    ::inet::wirelessrouting::HeartBeat::operator=(other);
    copy(other);
    return *this;
}

void RrepAck::copy(const RrepAck& other)
{
    this->heartBeatType = other.heartBeatType;
    this->hopCount = other.hopCount;
    this->rreqId = other.rreqId;
    this->destAddr = other.destAddr;
    this->destSeqNum = other.destSeqNum;
    this->originatorAddr = other.originatorAddr;
    this->originatorSeqNum = other.originatorSeqNum;
}

void RrepAck::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::wirelessrouting::HeartBeat::parsimPack(b);
    doParsimPacking(b,this->heartBeatType);
    doParsimPacking(b,this->hopCount);
    doParsimPacking(b,this->rreqId);
    doParsimPacking(b,this->destAddr);
    doParsimPacking(b,this->destSeqNum);
    doParsimPacking(b,this->originatorAddr);
    doParsimPacking(b,this->originatorSeqNum);
}

void RrepAck::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::wirelessrouting::HeartBeat::parsimUnpack(b);
    doParsimUnpacking(b,this->heartBeatType);
    doParsimUnpacking(b,this->hopCount);
    doParsimUnpacking(b,this->rreqId);
    doParsimUnpacking(b,this->destAddr);
    doParsimUnpacking(b,this->destSeqNum);
    doParsimUnpacking(b,this->originatorAddr);
    doParsimUnpacking(b,this->originatorSeqNum);
}

unsigned int RrepAck::getHeartBeatType() const
{
    return this->heartBeatType;
}

void RrepAck::setHeartBeatType(unsigned int heartBeatType)
{
    handleChange();
    this->heartBeatType = heartBeatType;
}

unsigned int RrepAck::getHopCount() const
{
    return this->hopCount;
}

void RrepAck::setHopCount(unsigned int hopCount)
{
    handleChange();
    this->hopCount = hopCount;
}

unsigned int RrepAck::getRreqId() const
{
    return this->rreqId;
}

void RrepAck::setRreqId(unsigned int rreqId)
{
    handleChange();
    this->rreqId = rreqId;
}

const L3Address& RrepAck::getDestAddr() const
{
    return this->destAddr;
}

void RrepAck::setDestAddr(const L3Address& destAddr)
{
    handleChange();
    this->destAddr = destAddr;
}

unsigned int RrepAck::getDestSeqNum() const
{
    return this->destSeqNum;
}

void RrepAck::setDestSeqNum(unsigned int destSeqNum)
{
    handleChange();
    this->destSeqNum = destSeqNum;
}

const L3Address& RrepAck::getOriginatorAddr() const
{
    return this->originatorAddr;
}

void RrepAck::setOriginatorAddr(const L3Address& originatorAddr)
{
    handleChange();
    this->originatorAddr = originatorAddr;
}

unsigned int RrepAck::getOriginatorSeqNum() const
{
    return this->originatorSeqNum;
}

void RrepAck::setOriginatorSeqNum(unsigned int originatorSeqNum)
{
    handleChange();
    this->originatorSeqNum = originatorSeqNum;
}

class RrepAckDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
    enum FieldConstants {
        FIELD_heartBeatType,
        FIELD_hopCount,
        FIELD_rreqId,
        FIELD_destAddr,
        FIELD_destSeqNum,
        FIELD_originatorAddr,
        FIELD_originatorSeqNum,
    };
  public:
    RrepAckDescriptor();
    virtual ~RrepAckDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyname) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyname) const override;
    virtual int getFieldArraySize(void *object, int field) const override;

    virtual const char *getFieldDynamicTypeString(void *object, int field, int i) const override;
    virtual std::string getFieldValueAsString(void *object, int field, int i) const override;
    virtual bool setFieldValueAsString(void *object, int field, int i, const char *value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual void *getFieldStructValuePointer(void *object, int field, int i) const override;
};

Register_ClassDescriptor(RrepAckDescriptor)

RrepAckDescriptor::RrepAckDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::wirelessrouting::RrepAck)), "inet::wirelessrouting::HeartBeat")
{
    propertynames = nullptr;
}

RrepAckDescriptor::~RrepAckDescriptor()
{
    delete[] propertynames;
}

bool RrepAckDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<RrepAck *>(obj)!=nullptr;
}

const char **RrepAckDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *RrepAckDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int RrepAckDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 7+basedesc->getFieldCount() : 7;
}

unsigned int RrepAckDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_heartBeatType
        FD_ISEDITABLE,    // FIELD_hopCount
        FD_ISEDITABLE,    // FIELD_rreqId
        0,    // FIELD_destAddr
        FD_ISEDITABLE,    // FIELD_destSeqNum
        0,    // FIELD_originatorAddr
        FD_ISEDITABLE,    // FIELD_originatorSeqNum
    };
    return (field >= 0 && field < 7) ? fieldTypeFlags[field] : 0;
}

const char *RrepAckDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "heartBeatType",
        "hopCount",
        "rreqId",
        "destAddr",
        "destSeqNum",
        "originatorAddr",
        "originatorSeqNum",
    };
    return (field >= 0 && field < 7) ? fieldNames[field] : nullptr;
}

int RrepAckDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0] == 'h' && strcmp(fieldName, "heartBeatType") == 0) return base+0;
    if (fieldName[0] == 'h' && strcmp(fieldName, "hopCount") == 0) return base+1;
    if (fieldName[0] == 'r' && strcmp(fieldName, "rreqId") == 0) return base+2;
    if (fieldName[0] == 'd' && strcmp(fieldName, "destAddr") == 0) return base+3;
    if (fieldName[0] == 'd' && strcmp(fieldName, "destSeqNum") == 0) return base+4;
    if (fieldName[0] == 'o' && strcmp(fieldName, "originatorAddr") == 0) return base+5;
    if (fieldName[0] == 'o' && strcmp(fieldName, "originatorSeqNum") == 0) return base+6;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *RrepAckDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "unsigned int",    // FIELD_heartBeatType
        "unsigned int",    // FIELD_hopCount
        "unsigned int",    // FIELD_rreqId
        "inet::L3Address",    // FIELD_destAddr
        "unsigned int",    // FIELD_destSeqNum
        "inet::L3Address",    // FIELD_originatorAddr
        "unsigned int",    // FIELD_originatorSeqNum
    };
    return (field >= 0 && field < 7) ? fieldTypeStrings[field] : nullptr;
}

const char **RrepAckDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldPropertyNames(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *RrepAckDescriptor::getFieldProperty(int field, const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldProperty(field, propertyname);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int RrepAckDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    RrepAck *pp = (RrepAck *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

const char *RrepAckDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    RrepAck *pp = (RrepAck *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string RrepAckDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    RrepAck *pp = (RrepAck *)object; (void)pp;
    switch (field) {
        case FIELD_heartBeatType: return ulong2string(pp->getHeartBeatType());
        case FIELD_hopCount: return ulong2string(pp->getHopCount());
        case FIELD_rreqId: return ulong2string(pp->getRreqId());
        case FIELD_destAddr: return pp->getDestAddr().str();
        case FIELD_destSeqNum: return ulong2string(pp->getDestSeqNum());
        case FIELD_originatorAddr: return pp->getOriginatorAddr().str();
        case FIELD_originatorSeqNum: return ulong2string(pp->getOriginatorSeqNum());
        default: return "";
    }
}

bool RrepAckDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    RrepAck *pp = (RrepAck *)object; (void)pp;
    switch (field) {
        case FIELD_heartBeatType: pp->setHeartBeatType(string2ulong(value)); return true;
        case FIELD_hopCount: pp->setHopCount(string2ulong(value)); return true;
        case FIELD_rreqId: pp->setRreqId(string2ulong(value)); return true;
        case FIELD_destSeqNum: pp->setDestSeqNum(string2ulong(value)); return true;
        case FIELD_originatorSeqNum: pp->setOriginatorSeqNum(string2ulong(value)); return true;
        default: return false;
    }
}

const char *RrepAckDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructName(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    };
}

void *RrepAckDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    RrepAck *pp = (RrepAck *)object; (void)pp;
    switch (field) {
        case FIELD_destAddr: return toVoidPtr(&pp->getDestAddr()); break;
        case FIELD_originatorAddr: return toVoidPtr(&pp->getOriginatorAddr()); break;
        default: return nullptr;
    }
}

Register_Class(WaitForRrep)

WaitForRrep::WaitForRrep(const char *name, short kind) : ::omnetpp::cMessage(name, kind)
{
}

WaitForRrep::WaitForRrep(const WaitForRrep& other) : ::omnetpp::cMessage(other)
{
    copy(other);
}

WaitForRrep::~WaitForRrep()
{
}

WaitForRrep& WaitForRrep::operator=(const WaitForRrep& other)
{
    if (this == &other) return *this;
    ::omnetpp::cMessage::operator=(other);
    copy(other);
    return *this;
}

void WaitForRrep::copy(const WaitForRrep& other)
{
    this->destAddr = other.destAddr;
    this->lastTTL = other.lastTTL;
    this->fromInvalidEntry = other.fromInvalidEntry;
}

void WaitForRrep::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::omnetpp::cMessage::parsimPack(b);
    doParsimPacking(b,this->destAddr);
    doParsimPacking(b,this->lastTTL);
    doParsimPacking(b,this->fromInvalidEntry);
}

void WaitForRrep::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::omnetpp::cMessage::parsimUnpack(b);
    doParsimUnpacking(b,this->destAddr);
    doParsimUnpacking(b,this->lastTTL);
    doParsimUnpacking(b,this->fromInvalidEntry);
}

const L3Address& WaitForRrep::getDestAddr() const
{
    return this->destAddr;
}

void WaitForRrep::setDestAddr(const L3Address& destAddr)
{
    this->destAddr = destAddr;
}

unsigned int WaitForRrep::getLastTTL() const
{
    return this->lastTTL;
}

void WaitForRrep::setLastTTL(unsigned int lastTTL)
{
    this->lastTTL = lastTTL;
}

bool WaitForRrep::getFromInvalidEntry() const
{
    return this->fromInvalidEntry;
}

void WaitForRrep::setFromInvalidEntry(bool fromInvalidEntry)
{
    this->fromInvalidEntry = fromInvalidEntry;
}

class WaitForRrepDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
    enum FieldConstants {
        FIELD_destAddr,
        FIELD_lastTTL,
        FIELD_fromInvalidEntry,
    };
  public:
    WaitForRrepDescriptor();
    virtual ~WaitForRrepDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyname) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyname) const override;
    virtual int getFieldArraySize(void *object, int field) const override;

    virtual const char *getFieldDynamicTypeString(void *object, int field, int i) const override;
    virtual std::string getFieldValueAsString(void *object, int field, int i) const override;
    virtual bool setFieldValueAsString(void *object, int field, int i, const char *value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual void *getFieldStructValuePointer(void *object, int field, int i) const override;
};

Register_ClassDescriptor(WaitForRrepDescriptor)

WaitForRrepDescriptor::WaitForRrepDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::wirelessrouting::WaitForRrep)), "omnetpp::cMessage")
{
    propertynames = nullptr;
}

WaitForRrepDescriptor::~WaitForRrepDescriptor()
{
    delete[] propertynames;
}

bool WaitForRrepDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<WaitForRrep *>(obj)!=nullptr;
}

const char **WaitForRrepDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *WaitForRrepDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int WaitForRrepDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 3+basedesc->getFieldCount() : 3;
}

unsigned int WaitForRrepDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        0,    // FIELD_destAddr
        FD_ISEDITABLE,    // FIELD_lastTTL
        FD_ISEDITABLE,    // FIELD_fromInvalidEntry
    };
    return (field >= 0 && field < 3) ? fieldTypeFlags[field] : 0;
}

const char *WaitForRrepDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "destAddr",
        "lastTTL",
        "fromInvalidEntry",
    };
    return (field >= 0 && field < 3) ? fieldNames[field] : nullptr;
}

int WaitForRrepDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0] == 'd' && strcmp(fieldName, "destAddr") == 0) return base+0;
    if (fieldName[0] == 'l' && strcmp(fieldName, "lastTTL") == 0) return base+1;
    if (fieldName[0] == 'f' && strcmp(fieldName, "fromInvalidEntry") == 0) return base+2;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *WaitForRrepDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "inet::L3Address",    // FIELD_destAddr
        "unsigned int",    // FIELD_lastTTL
        "bool",    // FIELD_fromInvalidEntry
    };
    return (field >= 0 && field < 3) ? fieldTypeStrings[field] : nullptr;
}

const char **WaitForRrepDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldPropertyNames(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *WaitForRrepDescriptor::getFieldProperty(int field, const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldProperty(field, propertyname);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int WaitForRrepDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    WaitForRrep *pp = (WaitForRrep *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

const char *WaitForRrepDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    WaitForRrep *pp = (WaitForRrep *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string WaitForRrepDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    WaitForRrep *pp = (WaitForRrep *)object; (void)pp;
    switch (field) {
        case FIELD_destAddr: return pp->getDestAddr().str();
        case FIELD_lastTTL: return ulong2string(pp->getLastTTL());
        case FIELD_fromInvalidEntry: return bool2string(pp->getFromInvalidEntry());
        default: return "";
    }
}

bool WaitForRrepDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    WaitForRrep *pp = (WaitForRrep *)object; (void)pp;
    switch (field) {
        case FIELD_lastTTL: pp->setLastTTL(string2ulong(value)); return true;
        case FIELD_fromInvalidEntry: pp->setFromInvalidEntry(string2bool(value)); return true;
        default: return false;
    }
}

const char *WaitForRrepDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructName(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    };
}

void *WaitForRrepDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    WaitForRrep *pp = (WaitForRrep *)object; (void)pp;
    switch (field) {
        case FIELD_destAddr: return toVoidPtr(&pp->getDestAddr()); break;
        default: return nullptr;
    }
}

Register_Class(PacketHolderMessage)

PacketHolderMessage::PacketHolderMessage(const char *name, short kind) : ::omnetpp::cMessage(name, kind)
{
    if (this->ownedPacket != nullptr) take(this->ownedPacket);
}

PacketHolderMessage::PacketHolderMessage(const PacketHolderMessage& other) : ::omnetpp::cMessage(other)
{
    copy(other);
}

PacketHolderMessage::~PacketHolderMessage()
{
    dropAndDelete(this->ownedPacket);
}

PacketHolderMessage& PacketHolderMessage::operator=(const PacketHolderMessage& other)
{
    if (this == &other) return *this;
    ::omnetpp::cMessage::operator=(other);
    copy(other);
    return *this;
}

void PacketHolderMessage::copy(const PacketHolderMessage& other)
{
    dropAndDelete(this->ownedPacket);
    this->ownedPacket = other.ownedPacket;
    if (this->ownedPacket != nullptr) {
        this->ownedPacket = this->ownedPacket->dup();
        take(this->ownedPacket);
        this->ownedPacket->setName(other.ownedPacket->getName());
    }
}

void PacketHolderMessage::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::omnetpp::cMessage::parsimPack(b);
    doParsimPacking(b,this->ownedPacket);
}

void PacketHolderMessage::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::omnetpp::cMessage::parsimUnpack(b);
    doParsimUnpacking(b,this->ownedPacket);
}

const Packet * PacketHolderMessage::getOwnedPacket() const
{
    return this->ownedPacket;
}

void PacketHolderMessage::setOwnedPacket(Packet * ownedPacket)
{
    if (this->ownedPacket != nullptr) throw omnetpp::cRuntimeError("setOwnedPacket(): a value is already set, remove it first with dropOwnedPacket()");
    this->ownedPacket = ownedPacket;
    if (this->ownedPacket != nullptr)
        take(this->ownedPacket);
}

Packet * PacketHolderMessage::dropOwnedPacket()
{
    Packet * retval = this->ownedPacket;
    if (retval != nullptr)
        drop(retval);
    this->ownedPacket = nullptr;
    return retval;
}

class PacketHolderMessageDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
    enum FieldConstants {
        FIELD_ownedPacket,
    };
  public:
    PacketHolderMessageDescriptor();
    virtual ~PacketHolderMessageDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyname) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyname) const override;
    virtual int getFieldArraySize(void *object, int field) const override;

    virtual const char *getFieldDynamicTypeString(void *object, int field, int i) const override;
    virtual std::string getFieldValueAsString(void *object, int field, int i) const override;
    virtual bool setFieldValueAsString(void *object, int field, int i, const char *value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual void *getFieldStructValuePointer(void *object, int field, int i) const override;
};

Register_ClassDescriptor(PacketHolderMessageDescriptor)

PacketHolderMessageDescriptor::PacketHolderMessageDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::wirelessrouting::PacketHolderMessage)), "omnetpp::cMessage")
{
    propertynames = nullptr;
}

PacketHolderMessageDescriptor::~PacketHolderMessageDescriptor()
{
    delete[] propertynames;
}

bool PacketHolderMessageDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<PacketHolderMessage *>(obj)!=nullptr;
}

const char **PacketHolderMessageDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *PacketHolderMessageDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int PacketHolderMessageDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 1+basedesc->getFieldCount() : 1;
}

unsigned int PacketHolderMessageDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISCOMPOUND | FD_ISPOINTER | FD_ISCOBJECT | FD_ISCOWNEDOBJECT,    // FIELD_ownedPacket
    };
    return (field >= 0 && field < 1) ? fieldTypeFlags[field] : 0;
}

const char *PacketHolderMessageDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "ownedPacket",
    };
    return (field >= 0 && field < 1) ? fieldNames[field] : nullptr;
}

int PacketHolderMessageDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0] == 'o' && strcmp(fieldName, "ownedPacket") == 0) return base+0;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *PacketHolderMessageDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "inet::Packet",    // FIELD_ownedPacket
    };
    return (field >= 0 && field < 1) ? fieldTypeStrings[field] : nullptr;
}

const char **PacketHolderMessageDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldPropertyNames(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        case FIELD_ownedPacket: {
            static const char *names[] = { "owned",  nullptr };
            return names;
        }
        default: return nullptr;
    }
}

const char *PacketHolderMessageDescriptor::getFieldProperty(int field, const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldProperty(field, propertyname);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        case FIELD_ownedPacket:
            if (!strcmp(propertyname, "owned")) return "";
            return nullptr;
        default: return nullptr;
    }
}

int PacketHolderMessageDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    PacketHolderMessage *pp = (PacketHolderMessage *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

const char *PacketHolderMessageDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    PacketHolderMessage *pp = (PacketHolderMessage *)object; (void)pp;
    switch (field) {
        case FIELD_ownedPacket: { const Packet * value = pp->getOwnedPacket(); return omnetpp::opp_typename(typeid(*value)); }
        default: return nullptr;
    }
}

std::string PacketHolderMessageDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    PacketHolderMessage *pp = (PacketHolderMessage *)object; (void)pp;
    switch (field) {
        case FIELD_ownedPacket: {std::stringstream out; out << pp->getOwnedPacket(); return out.str();}
        default: return "";
    }
}

bool PacketHolderMessageDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    PacketHolderMessage *pp = (PacketHolderMessage *)object; (void)pp;
    switch (field) {
        default: return false;
    }
}

const char *PacketHolderMessageDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructName(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        case FIELD_ownedPacket: return omnetpp::opp_typename(typeid(Packet));
        default: return nullptr;
    };
}

void *PacketHolderMessageDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    PacketHolderMessage *pp = (PacketHolderMessage *)object; (void)pp;
    switch (field) {
        case FIELD_ownedPacket: return toVoidPtr(pp->getOwnedPacket()); break;
        default: return nullptr;
    }
}

UnreachableNode::UnreachableNode()
{
    this->seqNum = 0;
}

void __doPacking(omnetpp::cCommBuffer *b, const UnreachableNode& a)
{
    doParsimPacking(b,a.addr);
    doParsimPacking(b,a.seqNum);
}

void __doUnpacking(omnetpp::cCommBuffer *b, UnreachableNode& a)
{
    doParsimUnpacking(b,a.addr);
    doParsimUnpacking(b,a.seqNum);
}

class UnreachableNodeDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
    enum FieldConstants {
        FIELD_addr,
        FIELD_seqNum,
    };
  public:
    UnreachableNodeDescriptor();
    virtual ~UnreachableNodeDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyname) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyname) const override;
    virtual int getFieldArraySize(void *object, int field) const override;

    virtual const char *getFieldDynamicTypeString(void *object, int field, int i) const override;
    virtual std::string getFieldValueAsString(void *object, int field, int i) const override;
    virtual bool setFieldValueAsString(void *object, int field, int i, const char *value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual void *getFieldStructValuePointer(void *object, int field, int i) const override;
};

Register_ClassDescriptor(UnreachableNodeDescriptor)

UnreachableNodeDescriptor::UnreachableNodeDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::wirelessrouting::UnreachableNode)), "")
{
    propertynames = nullptr;
}

UnreachableNodeDescriptor::~UnreachableNodeDescriptor()
{
    delete[] propertynames;
}

bool UnreachableNodeDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<UnreachableNode *>(obj)!=nullptr;
}

const char **UnreachableNodeDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *UnreachableNodeDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int UnreachableNodeDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 2+basedesc->getFieldCount() : 2;
}

unsigned int UnreachableNodeDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        0,    // FIELD_addr
        FD_ISEDITABLE,    // FIELD_seqNum
    };
    return (field >= 0 && field < 2) ? fieldTypeFlags[field] : 0;
}

const char *UnreachableNodeDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "addr",
        "seqNum",
    };
    return (field >= 0 && field < 2) ? fieldNames[field] : nullptr;
}

int UnreachableNodeDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0] == 'a' && strcmp(fieldName, "addr") == 0) return base+0;
    if (fieldName[0] == 's' && strcmp(fieldName, "seqNum") == 0) return base+1;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *UnreachableNodeDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "inet::L3Address",    // FIELD_addr
        "uint32_t",    // FIELD_seqNum
    };
    return (field >= 0 && field < 2) ? fieldTypeStrings[field] : nullptr;
}

const char **UnreachableNodeDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldPropertyNames(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *UnreachableNodeDescriptor::getFieldProperty(int field, const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldProperty(field, propertyname);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int UnreachableNodeDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    UnreachableNode *pp = (UnreachableNode *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

const char *UnreachableNodeDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    UnreachableNode *pp = (UnreachableNode *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string UnreachableNodeDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    UnreachableNode *pp = (UnreachableNode *)object; (void)pp;
    switch (field) {
        case FIELD_addr: return pp->addr.str();
        case FIELD_seqNum: return ulong2string(pp->seqNum);
        default: return "";
    }
}

bool UnreachableNodeDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    UnreachableNode *pp = (UnreachableNode *)object; (void)pp;
    switch (field) {
        case FIELD_seqNum: pp->seqNum = string2ulong(value); return true;
        default: return false;
    }
}

const char *UnreachableNodeDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructName(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    };
}

void *UnreachableNodeDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    UnreachableNode *pp = (UnreachableNode *)object; (void)pp;
    switch (field) {
        case FIELD_addr: return toVoidPtr(&pp->addr); break;
        default: return nullptr;
    }
}

} // namespace wirelessrouting
} // namespace inet

