#ifndef JOYSTICKSDL_H
#define JOYSTICKSDL_H

#include <QObject>
#include <SDL.h>
#include <QTimer>
#include <QDebug>

class joysticksdl : public QObject {
    Q_OBJECT
public:
    explicit joysticksdl(unsigned int joystickNumber, QObject *parent = 0);
    ~joysticksdl();

    static enum KIND {
        NORMAL      = 0,
        TOGGLE      = 1,
        CAPTURE     = 2,
        MODE        = 3,
        AUTO_REPEAT = 4
    } KIND;

    void GetNumberOFButtons();
    void GetNumberOFAxes();
    void GetNumberOFHats();
    void GetNumberOFBalls();
    void GetIndex();
    void NumberOfAvailableJS();
    void ShowJoystickData();
    void ShowAvailableJoysticks();

    void setKind(int id, int kind);
    int getKind(int id);

private:
    SDL_Joystick *joy;
    int joystickNumber;
    bool isConnected;
    bool buttonStates[100];
    short buttonKinds[100];
    QTimer *t, *checkAutoRepeat, *autoRepeat;
    float x, y, z, r;
    float povX, povY;
    int currentButton;

    void ButtonDown(SDL_Event event);
    void ButtonUp(SDL_Event event);
    void AxisMotion(SDL_Event event);
    void BallMotion(SDL_Event event);
    void HatMotion(SDL_Event event);

    //    bool isButtonPressed(int id);
    //signals:
    //    void connected();

    //    void disconnected();

    //    void buttonPressed(int id);

    //    void buttonReleased(int id);

private slots:
    void checkConnectivity();

    void readJoystickState();

    void sCheckAutoRepeat();

    void sAutoRepeat();
};

#endif // JOYSTICKSDL_H
