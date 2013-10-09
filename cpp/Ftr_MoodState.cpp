#include "Ftr_MoodState.h"

#include <iostream>

Ftr_MoodState::Ftr_MoodState()
{
    m_mood = DEFAULT;
    m_consoleThread = NULL;
    m_carrierPigeon = NULL;

    m_chatBot.setNextState(DEFAULT, 0);
    m_timesInState = 0;

    m_moodLocked = false;
}

Ftr_MoodState::Ftr_MoodState(const Ftr_MoodState& c)
{
    m_mood = DEFAULT;
    m_consoleThread = NULL;
    m_carrierPigeon = NULL;
    
    m_chatBot.setNextState(DEFAULT, 0);
    m_timesInState = 0;

    m_moodLocked = false;
}

Ftr_MoodState& Ftr_MoodState::operator=(const Ftr_MoodState& c)
{
    m_mood = DEFAULT;
    m_consoleThread = NULL;
    m_carrierPigeon = NULL;
    
    m_chatBot.setNextState(DEFAULT, 0);
    m_timesInState = 0;

    m_moodLocked = false;

    return *this;
}

void Ftr_MoodState::start()
{
    m_consoleThread = new boost::thread(boost::ref(*this));
}

void Ftr_MoodState::stop()
{
    if(m_consoleThread != NULL){
        m_consoleThread->join();
    }
}

void Ftr_MoodState::operator()()
{
    while(true)
	{
        m_mutex.lock();

        /*
        1: chat
        2: get input. 
        3: process input & set state 
        4: change state        
        */
        if(!m_chatBot.m_sessionOver)
        {
            m_chatBot.chat();
		    std::getline(std::cin, m_input);        
            processInput();       
            m_chatBot.changeState();
        }

        m_mutex.unlock();
	}
}

void Ftr_MoodState::processInput()
{
    //input manipulation
    m_mood = m_chatBot.find(m_input);
    m_input.erase();
    m_chatBot.setNextState(m_mood, ++m_timesInState);

    if(m_timesInState > 3)
        m_timesInState = 0;
    
    m_carrierPigeon->setMessage(m_mood);
}

bool Ftr_MoodState::addMessageCarrier(_MessageCarrier& mc)
{
    m_carrierPigeon = &mc;
    return true;
}

Ftr_MoodState::~Ftr_MoodState()
{
    stop();

    if(m_consoleThread != NULL){
        delete m_consoleThread;
        m_consoleThread = NULL;
    }
}
