#ifndef EVENT_H
#define EVENT_H

class Event
{

public:
    enum Type{PAGE_ACCESS, TLB_MISS, PAGE_FAULT, MEMORY_WRITE };


public:
    Event(int id, double timestamp, Type t,unsigned int virtualAddress);

    bool operator<(const Event& other) const{
        return this->timestamp > other.timestamp;
    }

    double getTimestamp() const {return timestamp; }
    int getID() const {return ID; }
    Type getType() const {return type; }



    unsigned int getVirtualAddress() const;

private:
    double timestamp;
    int ID;
    Type type;
    unsigned int virtualAddress;
};





#endif // EVENT_H
