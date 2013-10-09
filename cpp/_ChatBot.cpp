#include "_ChatBot.h"
#include <cmath>
#include <ctime>
#include <iostream>

_ChatBot::_ChatBot(void)
{
    m_sessionOver = false;
    m_currentState = QUESTIONING; 

    m_questioningStrings[0] = "Tell me, how do you feel?\n";
    m_questioningStrings[1] = "Feel free to tell me how you are doing.\n";
    m_questioningStrings[2] = "How are you?\n";
    m_questioningStrings[3] = "Tell me about what's going on.\n";

    m_listeningStrings[0] = "Mhm.\n";
    m_listeningStrings[1] = "I'm listening.\n";
    m_listeningStrings[2] = "Go on.\n";
    m_listeningStrings[3] = "Tell me more.\n";

    m_confusedStrings[0] = "I'm sorry, could you explain in detail?\n";
    m_confusedStrings[1] = "Could you tell me in a different manner?\n";
    m_confusedStrings[2] = "Please explain yourself better.\n";
    m_confusedStrings[3] = "I'm sorry, I don't understand.\n";

    m_angryStrings[0] = "angry";
    m_angryStrings[1] = "upset";
    m_angryStrings[2] = "mad";
    m_angryStrings[3] = "furious";
    m_angryStrings[4] = "pissed";

    m_sadStrings[0] = "sad";
    m_sadStrings[1] = "depress";
    m_sadStrings[2] = "bummed";
    m_sadStrings[3] = "scared";
    m_sadStrings[4] = "cry";

    m_happyStrings[0] = "happy";
    m_happyStrings[1] = "content";
    m_happyStrings[2] = "excite";
    m_happyStrings[3] = "joy";
    m_happyStrings[4] = "fun";

    m_finishedStrings[1] = "im done";
    m_finishedStrings[2] = "i'm done";
    m_finishedStrings[0] = "I'm done";
    m_finishedStrings[3] = "i am done";
    m_finishedStrings[4] = "done here";

    m_doneString = "I think that concludes our session.  That will be four hundred-thousand dollars.\n";

    std::srand(std::time(NULL));
}

std::string _ChatBot::getReply()
{
    int index = std::rand() % NUM_OF_REPLIES;

    switch(m_currentState)
    {
    case QUESTIONING: return m_questioningStrings[index];  break;
    case LISTENING: return m_listeningStrings[index]; break;
    case CONFUSED: return m_confusedStrings[index]; break;
    case FINISHED: return m_doneString; break;
    default: return m_confusedStrings[index]; break;
    }
}

void _ChatBot::chat()
{
    std::cout << getReply();
}

//THIS COULD TOTALLY BE WRITTEN BETTER.
//BUT I DON'T HAVE TIME & THIS PROJECT ISN'T VERY HIGH PRIORITY
//IM SORRY FOR UGLINESS :(
UserMood _ChatBot::find(std::string input)
{
    std::size_t isFound;
    
    setNextState(DEFAULT, 0, CONFUSED);
   // return DEFAULT;

    for(int i = 0; i < MOOD_INDICATORS; ++i)
    {
        isFound = input.find(m_angryStrings[i]);

        if(isFound != std::string::npos){
            return ANGRY;
        }
    }
    
    for(int i = 0; i < MOOD_INDICATORS; ++i)
    {
        isFound = input.find(m_happyStrings[i]);

        if(isFound != std::string::npos){
            return HAPPY;
        }
    }

    for(int i = 0; i < MOOD_INDICATORS; ++i)
    {
        isFound = input.find(m_sadStrings[i]);

        if(isFound != std::string::npos){
            return SAD;
        }
    }

    for(int i = 0; i < MOOD_INDICATORS; ++i)
    {
        isFound = input.find(m_finishedStrings[i]);

        if(isFound != std::string::npos){
            return DONE;
        }
    }
}

void _ChatBot::setNextState(UserMood mood, int numTimesInState, ChatBotState directState)
{
    if(numTimesInState > 3){
        m_nextState = QUESTIONING;
        return;
    }

    if(mood == ANGRY || mood == SAD || mood == HAPPY){
        m_nextState = LISTENING;
    }

    else if(mood == DONE){
        m_nextState = FINISHED;
        std::cout << m_doneString;
        m_sessionOver = true;
    }

    else
        m_nextState = CONFUSED;
}

void _ChatBot::changeState()
{
    m_currentState = m_nextState;
}

_ChatBot::~_ChatBot(void)
{
}
