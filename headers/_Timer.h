#ifndef _TIMER_H
#define _TIMER_H

#include <time.h>

struct _Timer
{
private:
    clock_t m_timeStarted;
    clock_t m_timePaused;

    bool m_isStarted;
    bool m_isPaused;

public:
    _Timer()
    {
        m_timeStarted = 0;
        m_timePaused = 0;
        m_isStarted = false;
        m_isPaused = false;
    };

    bool isStarted()
    {
        return m_isStarted;
    };

    bool isStopped()
    {
        return !m_isStarted;
    };

    void pause()
    {
        if(m_isPaused || !m_isStarted){
            return;
        }

        else{
            m_isPaused = true;
            m_timePaused = clock();
        }
    };
    
    void resume()
    {
        if(!m_isPaused){
            return;
        }

        else{
            m_isPaused = false;
            m_timeStarted = clock() + m_timePaused;
        }
    };

    void start()
    {
        m_isStarted = true;
        m_isPaused = false;
        m_timeStarted = clock();
    };

    void stop()
    {
        m_isStarted = false;
    };

    void reset()
    {
        m_isPaused = false;
        m_timeStarted = clock();
    };

    clock_t getTicks()
    {
        if(!m_isStarted)
            return 0;
        if(m_isPaused)
            return m_timePaused - m_timeStarted;

        return clock() - m_timeStarted;
    };

};

#endif