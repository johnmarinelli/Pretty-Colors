#ifndef _MESSAGECARRIER_H
#define _MESSAGECARRIER_H

#include "UserMood.h"
class _MessageCarrier
{
private:
    UserMood message;

public:
    _MessageCarrier(){
        message = DEFAULT;
    };

    _MessageCarrier(const _MessageCarrier& c){
        message = c.message;
    };

    _MessageCarrier& operator=(const _MessageCarrier& c){
        message = c.message;
        return *this;
    };

    void setMessage(UserMood msg){
        message = msg;
    };

    UserMood getMessage(){
        return message;
    };

    ~_MessageCarrier(){
    };
};

#endif