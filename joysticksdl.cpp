#include "joysticksdl.h"

joysticksdl::joysticksdl(unsigned int joystickNumber, QObject *parent) : QObject(parent),
    t(new QTimer(this)),
    joystickNumber(joystickNumber),
    isConnected(false),
    checkAutoRepeat(new QTimer(this)),
    autoRepeat(new QTimer(this)),
    currentButton(0)
{
    SDL_Init( SDL_INIT_VIDEO | SDL_INIT_JOYSTICK );
    SDL_JoystickEventState(SDL_ENABLE);

    if(SDL_NumJoysticks()>0) {
        joy = SDL_JoystickOpen(joystickNumber);
        qDebug()<<"Joystick opened";
    }else {  qDebug()<<"Couldn't open Joystick";}


    t->start(30);

    connect(t,SIGNAL(timeout()),this,SLOT(checkConnectivity()));
    connect(t, SIGNAL(timeout()), this, SLOT(readJoystickState()));
    connect(checkAutoRepeat, SIGNAL(timeout()), this, SLOT(sCheckAutoRepeat()));
    connect(autoRepeat, SIGNAL(timeout()), this, SLOT(sAutoRepeat()));


    for (int i = 0; i < SDL_JoystickNumButtons(joy); i++)
        buttonStates[i] = false;

    for (int i = 0; i < SDL_JoystickNumButtons(joy); i++)
        buttonKinds[i] = 0;


}


joysticksdl::~joysticksdl()
{}

void joysticksdl::readJoystickState()
{
    SDL_Event event;
    while(SDL_PollEvent(&event)){
        switch(event.type)
        {

        /*/////////////////// Button Pressed ////////////////////////////////////*/
        case SDL_JOYBUTTONDOWN:
            for(int i=0;i<SDL_JoystickNumButtons(joy);i++)
            {
                if ( event.jbutton.button == i )
                {
                    if (checkAutoRepeat->isActive())
                        checkAutoRepeat->stop();

                    if (autoRepeat->isActive())
                        autoRepeat->stop();

                    if (getKind(i) == AUTO_REPEAT) {
                        checkAutoRepeat->start(100);

                        currentButton = i;
                    }

                    qDebug()<<"Button pressed" <<i;
                }
            }
            break;
            /*////////////////// Button Released ///////////////////////////////////*/
        case SDL_JOYBUTTONUP:
            for(int i=0;i<SDL_JoystickNumButtons(joy);i++)
            {
                if ( event.jbutton.button == i )
                {
                    if (checkAutoRepeat->isActive())
                        checkAutoRepeat->stop();

                    if (autoRepeat->isActive())
                        autoRepeat->stop();

                    qDebug()<<"released" <<i;
                }
            }
            break;

            /*////////////////// Axis changed ///////////////////////////////////*/
        case SDL_JOYAXISMOTION:
            if ( ( event.jaxis.value < -3200 ) || (event.jaxis.value > 3200 ) )
            {
                if( event.jaxis.axis == 0) /*0 for Left or Right*/
                {
                    if(event.jaxis.value < 0)
                        qDebug()<<"left" << event.jaxis.value;
                    else if(event.jaxis.value > 0)
                        qDebug()<<"Right" << event.jaxis.value;
                }

                if( event.jaxis.axis == 1) /*1 for Up and Down*/
                {
                    if(event.jaxis.value < 0)
                        qDebug()<<"Up" << event.jaxis.value;
                    else if(event.jaxis.value > 0)
                        qDebug()<<"Down" << event.jaxis.value;
                }
            }
            break;
            /*////////////////// Joyball motion ///////////////////////////////////*/
        case SDL_JOYBALLMOTION:
            if( event.jball.ball == 0 )
            {
                qDebug()<<"Ball x"<<event.jball.xrel <<"Ball y"<<event.jball.yrel;
            }
            break;
            /*////////////////// Hat motion ///////////////////////////////////*/
        case SDL_JOYHATMOTION:  /* Handle Hat Motion */
            if ( event.jhat.value & SDL_HAT_UP )
            {
                qDebug()<<"Hat Up" << event.jhat.value;
            }

            if ( event.jhat.value & SDL_HAT_DOWN )
            {
                qDebug()<<"Hat Down" << event.jhat.value;
            }
            if ( event.jhat.value & SDL_HAT_LEFT )
            {
                qDebug()<<"Hat Left" << event.jhat.value;
            }
            if ( event.jhat.value & SDL_HAT_RIGHT )
            {
                qDebug()<<"Hat Right" << event.jhat.value;
            }
            if ( event.jhat.value & SDL_HAT_CENTERED )
            {
                qDebug()<<"Hat Centered" << event.jhat.value;
            }
            if ( event.jhat.value & SDL_HAT_LEFTDOWN )
            {
                qDebug()<<"Hat LeftDown" << event.jhat.value;
            }
            if ( event.jhat.value & SDL_HAT_LEFTUP )
            {
                qDebug()<<"Hat LeftUp" << event.jhat.value;
            }
            if ( event.jhat.value & SDL_HAT_RIGHTDOWN )
            {
                qDebug()<<"Hat RightDown" << event.jhat.value;
            }
            if ( event.jhat.value & SDL_HAT_RIGHTUP )
            {
                qDebug()<<"Hat RightUp" << event.jhat.value;
            }
            break;
        }

    }
}


void joysticksdl::checkConnectivity()
{
    SDL_JoystickUpdate();

    if(SDL_JoystickOpened(joystickNumber) && !isConnected){
        isConnected = true;
        //emit connected();
        qDebug()<<"connected";
    }
    if(!SDL_JoystickOpened(joystickNumber) && isConnected){
        isConnected = false;
        //emit disconnected();
        qDebug()<<"disconnect";
    }
}


void joysticksdl::sCheckAutoRepeat() {
    checkAutoRepeat->stop();
    autoRepeat->start(50);
}

void joysticksdl::sAutoRepeat() {
    qDebug()<<currentButton;
}


void joysticksdl::GetNumberOFButtons()
{    qDebug()<< "Number of buttons is " << SDL_JoystickNumButtons(joy);}

void joysticksdl::GetNumberOFAxes()
{    qDebug()<< "Number of Axes is " << SDL_JoystickNumAxes(joy);}

void joysticksdl::GetNumberOFHats()
{    qDebug()<< "Number of Hats is " << SDL_JoystickNumHats(joy);}

void joysticksdl::GetNumberOFBalls()
{    qDebug()<< "Number of Balls is " << SDL_JoystickNumBalls(joy);}

void joysticksdl::GetIndex()
{    qDebug()<< "Index is " << SDL_JoystickIndex(joy);}

void joysticksdl::NumberOfAvailableJS()
{    qDebug()<<"Number of available joysticks"<<SDL_NumJoysticks();}

void joysticksdl::setKind(int id, int kind)
{buttonKinds[id]=kind;}

int joysticksdl::getKind(int id)
{return buttonKinds[id];}
