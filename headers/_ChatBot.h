#ifndef _CHATBOT_H
#define _CHATBOT_H

#include <string>
#include "UserMood.h"

const int MOOD_INDICATORS = 5;
const int NUM_OF_REPLIES = 4;

enum ChatBotState
{
    QUESTIONING,
    LISTENING,
    CONFUSED,
    FINISHED,
};

class _ChatBot
{
private:
    ChatBotState m_nextState;
    ChatBotState m_currentState;

    std::string getReply();

    std::string m_angryStrings[MOOD_INDICATORS];
    std::string m_sadStrings[MOOD_INDICATORS];
    std::string m_happyStrings[MOOD_INDICATORS];
    std::string m_finishedStrings[MOOD_INDICATORS];

    std::string m_questioningStrings[NUM_OF_REPLIES];
    std::string m_listeningStrings[NUM_OF_REPLIES];
    std::string m_confusedStrings[NUM_OF_REPLIES];
    std::string m_doneString;
    
public:
    bool m_sessionOver;

    _ChatBot(void);

    void chat();

    UserMood find(std::string input);

    void setNextState(UserMood mood, int numTimesInState, ChatBotState directState = QUESTIONING);
    void changeState();

    ~_ChatBot(void);
};

#endif