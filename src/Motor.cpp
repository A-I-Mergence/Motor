/* mbed simple H-bridge motor controller
 * Copyright (c) 2007-2010, sford, http://mbed.org
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#include "Motor.h"
#include "mbed.h"

Motor::Motor(PinName pwm, PinName fwd, PinName rev, PinName EncA, PinName EncB):
        _pwm(pwm), _fwd(fwd), _rev(rev), _EncA(EncA), _EncB(EncB){

    _Tq = 0.01; // default
    _t = new Ticker;

    // Set initial condition of PWM
    _pwm.period(0.001);
    _pwm = 0;

    // Initial condition of output enables
    _fwd = 0;
    _rev = 0;
    _count = 0;

    _EncA.rise(callback(this, &Motor::risingA));
    _EncA.fall(callback(this, &Motor::fallingA));
    _EncB.rise(callback(this, &Motor::risingB));
    _EncB.fall(callback(this, &Motor::fallingB));

    _t->attach(callback(this, &Motor::UpdateSpeed), _Tq);
}

void Motor::MotorSetup(double dir, float ratio, double enco){
    _enco = enco;
    _dir = dir;
    _ratio = ratio;
}

void Motor::speed(float speed) {
    _fwd = (speed > 0.0);
    _rev = (speed < 0.0);
    _pwm = abs(speed);
}

void Motor::risingA(){
    if(_EncB.read())       _count++;
    else                   _count--;
}   
void Motor::fallingA(){
    if(not(_EncB.read()))  _count++;
    else                   _count--;
}
void Motor::risingB(){
    if(not(_EncA.read()))  _count++;          
    else                   _count--;
}
void Motor::fallingB(){
    if(_EncA.read())       _count++;
    else                   _count--;
}

void Motor::UpdateSpeed(){
    // vitesse des roues=direction*nombre de tick de l'encodeur * 60 secondes / 
    // (nb tick encodeur*4 car 2 encodeur en change*fréquence echantillonnage)/rapport de réduction
    _vitesse = _dir * _count *  60.0f/(_enco*4*_Tq)/_ratio;
    _count = 0;
}