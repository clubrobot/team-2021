#include "BornibusActions.h"

Elevator::Elevator(uint8_t position, AX12 frontAX, AX12 backAX)
{
    _position = position;
    _frontAX = frontAX;
    _backAX = backAX;
}

void Elevator::begin(uint8_t id_front, uint8_t id_back)
{
    _backAX.attach(id_back);
    _frontAX.attach(id_front);
    _backAX.setEndlessMode(true);
    _frontAX.setEndlessMode(true);
}

void Elevator::setPosition(uint8_t position)
{
    _position = position;
}

int Elevator::getPosition()
{
    int p = _position;
    return p;
}

void Elevator::goTo(uint8_t height)
{
    if (height==HIGH_POSITION && (this->_position != HIGH_POSITION))
    {
        this->_frontAX.turn(700);
        this->_backAX.turn(700);
        this->_position = OTHER;   
    }
    else if (height==LOW_POSITION && (this->_position != LOW_POSITION))
    {
        this->_frontAX.turn(-700);
        this->_backAX.turn(-700); 
        this->_position = OTHER;    
    }
}

void Elevator::stop()
{
    this->_frontAX.turn(0);
    this->_backAX.turn(0);
}

void Elevator::checkPosition(uint8_t pinHigh, uint8_t pinLow)
{
    if(!digitalRead(pinHigh))
    {
        this->stop();
        _position = HIGH_POSITION;
    }
    if(!digitalRead(pinLow))
    {
        this->stop();
        _position = LOW_POSITION;
    }
}

Clamp::Clamp(Servo servo, uint8_t state)
{
    _servo = servo;
    _state = state;
}

void Clamp::attach(uint8_t pin)
{
    _servo.attach(pin);
}

void Clamp::close()
{
    _servo.write(closed_clamp_position);
}

void Clamp::open()
{
    _servo.write(open_clamp_position);
}

void Clamp::move(int position)
{
    _servo.write(position);
}

WindsockArm::WindsockArm(Servo armServo, uint8_t armState)
{   
    _armServo = armServo;
    _armState = armState;
}

void WindsockArm::attach(uint8_t pin)
{
    _armServo.attach(pin);
}

void WindsockArm::fold()
{
    _armServo.write(folded_windsock_arm);
}

void WindsockArm::unfold()
{
    _armServo.write(unfolded_windsock_arm);
}

void WindsockArm::moveArm(int position)
{
    _armServo.write(position);
}