// Copyright (c) 2015
// Author: Chrono Law
#ifndef _NGX_CLOCK_HPP
#define _NGX_CLOCK_HPP

#include "Nginx.hpp"

class NgxClock final
{
public:
    NgxClock() = default;
    ~NgxClock() = default;
public:
    static const ngx_time_t& now()
    {
        ngx_time_update();

        return *ngx_timeofday();
    }

public:
    void reset()
    {
        m_time = now();
    }

    ngx_time_t delta() const
    {
        auto t = now();

        t.sec -= m_time.sec;
        t.msec -= m_time.msec;

        return t;
    }

    double elapsed() const
    {
        auto t = delta();

        return t.sec + t.msec * 1.0 / 1000;
    }
public:
    void sleep(ngx_uint_t sec) const
    {
        ngx_sleep(sec);
    }

    void msleep(ngx_uint_t msec) const
    {
        ngx_msleep(msec);
    }
private:
    ngx_time_t m_time = now();
};

#endif  //_NGX_CLOCK_HPP