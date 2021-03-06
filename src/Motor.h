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

#ifndef MBED_MOTOR_H
#define MBED_MOTOR_H
#include "mbed.h"

/** Interface to control a standard DC motor 
 *
 * with an H-bridge using a PwmOut and 2 DigitalOuts
 */
class Motor {
public:
    /** Create a motor control interface    
     *
     * @param pwm A PwmOut pin, driving the H-bridge enable line to control the speed
     * @param fwd A DigitalOut, set high when the motor should go forward
     * @param rev A DigitalOut, set high when the motor should go backwards
     * @param EncA
     * @param EncB
     */
    Motor(PinName pwm, PinName fwd, PinName rev, PinName EncA, PinName EncB);
    
    /** Set the speed of the motor
     * @param speed The speed of the motor as a normalised value between -1.0 and 1.0
     */
    void speed(float speed);

    /** Set the parameters of the motor
     * @param dirrection direction of rotation of the encoder relative to the direction of rotation of the motor shaft
     * @param ration gear ration
     * @param cpr counts per revolution (using just a single edge of one channel)
     */
    void MotorSetup(double direction, float ratio, double cpr);

    float getSpeed(){ return _vitesse; };

protected:
    void UpdateSpeed();
    void risingA();
    void fallingA();
    void risingB();
    void fallingB();

    double _Tq;
    Ticker * _t;

    PwmOut _pwm;
    DigitalOut _fwd;
    DigitalOut _rev;
    InterruptIn _EncA;
    InterruptIn _EncB;

    double _count;
    float _vitesse;
    double _enco;
    double _dir;
    float _ratio;
};
#endif