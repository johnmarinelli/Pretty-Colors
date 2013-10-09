#ifndef _FUNCTOR_MOODSTATE_H
#define _FUNCTOR_MOODSTATE_H

#include <string>
#include <boost/thread.hpp>
#include "UserMood.h"
#include "_MessageCarrier.h"
#include "_Timer.h"
#include "_ChatBot.h"

class Ftr_MoodState
{
private:
    /*thread and mutex for console input*/
    boost::thread* m_consoleThread;
    boost::mutex m_mutex;

    /*current mood and string to parse*/
    UserMood m_mood;
    std::string m_input;

    void processInput();

    /*messaging system*/
    _MessageCarrier* m_carrierPigeon;

    /*timer system*/
    _Timer m_timer;
    bool m_moodLocked;

    /*chatbot*/
    _ChatBot m_chatBot;
    int m_timesInState;

public:
    Ftr_MoodState();
    Ftr_MoodState(const Ftr_MoodState& c);
    Ftr_MoodState& operator=(const Ftr_MoodState& c);

    void start();
    void operator()();
    void stop();

    bool addMessageCarrier(_MessageCarrier& mc);

    ~Ftr_MoodState();
};

#endif