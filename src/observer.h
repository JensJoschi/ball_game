#ifndef OBSERVER_H
#define OBSERVER_H

class Observer {
public:
    Observer(){}
    virtual void onNotify() = 0;
    virtual void onDangle() = 0;
};


#endif // OBSERVER_H