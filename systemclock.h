#ifndef SYSTEMCLOCK_H
#define SYSTEMCLOCK_H

class SystemClock {

private:
    unsigned long currentTime = 0;

public:
    SystemClock();

    void addTime(unsigned int t) {
        this->currentTime += t;
    }

    unsigned long getTime() const {
        return this->currentTime;
    }
};

#endif // SYSTEMCLOCK_H
