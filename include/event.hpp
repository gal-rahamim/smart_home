#ifndef EVENT_HPP
#define EVENT_HPP

#include <ctime>
#include <string>

namespace smart_home {

class Event {
public:
    typedef time_t Time;
    typedef std::string Type;
    typedef std::string Floor;
    typedef std::string Room;
    typedef std::string Payload;

public:
    Event();
    Event(const Type& a_type, const Floor& a_floor, const Room& a_room, const Payload& a_payload = "");
    std::string GetType() const;
    std::string GetFloor() const;
    std::string GetRoom() const;
    std::string GetPayload() const;

private:
    Time m_time;
    Type m_type;
    Floor m_floor;
    Room m_room;
    Payload m_payload;

};

inline Event::Event()
: m_time(time(NULL))
, m_type()
, m_floor()
, m_room()
, m_payload()
{}

inline Event::Event(const Type& a_type, const Floor& a_floor, const Room& a_room, const Payload& a_payload)
: m_time(time(NULL))
, m_type(a_type)
, m_floor(a_floor)
, m_room(a_room)
, m_payload(a_payload)
{}

inline std::string Event::GetType() const
{
    return m_type;
}
inline std::string Event::GetFloor() const
{
    return m_floor;
}
inline std::string Event::GetRoom() const
{
    return m_room;
}
inline std::string Event::GetPayload() const
{
    return m_payload;
}

} //smart_home


#endif //EVENT_HPP