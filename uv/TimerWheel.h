/*
   Copyright 2017, object_he@yeah.net  All rights reserved.

   Author: object_he@yeah.net 
    
   Last modified: 2017-10-10
    
   Description: 
*/

#ifndef   UV_TIMER_WHEEL_H
#define   UV_TIMER_WHEEL_H

#include <vector>
#include <set>
#include <memory>
#include "Timer.h"
#include "TcpConnection.h"

namespace uv
{

//algorithm complexity  o(1).

class  ConnectionElement : public std::enable_shared_from_this<ConnectionElement>
{
public:
    ConnectionElement(std::shared_ptr<TcpConnection> connection)
        :connection_(connection)
    {

    }

    ~ConnectionElement()
    {
        std::shared_ptr<TcpConnection> connection = connection_.lock();
        if(connection)
        {
            connection->onSocketClose();
        }
    }

private:
    std::weak_ptr<TcpConnection> connection_;
};


class TimerWheel
{
public:
    TimerWheel(EventLoop* loop);
    TimerWheel(EventLoop* loop,unsigned int timeout);
    void setTimeout(unsigned int );
    void start();

    void insert(std::shared_ptr<TcpConnection> connnection);
    void insertNew(std::shared_ptr<TcpConnection> connection);
private:
    unsigned int index_;
    unsigned int timeoutSec_;
    Timer<void*> timer_;

    std::vector< std::set< std::shared_ptr<ConnectionElement>>> wheel;

    void wheelCallback(Timer<void*>*, void*);

};

}
#endif
