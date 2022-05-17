#include "mbed.h"
#include "Motor.h"
#include <cstdio>

Serial pc(USBTX, USBRX, 115200);
Motor motor(D10, D9, D6, D5, D4);       //pwm, fwd, rev, EncA, EncB

double dir = -1;
float ratio = 34.014;
double enco = 12;
float vReelMotor ;                      //vitesse de ma roue

int main() {
    while (true){
        motor.MotorSetup(dir, ratio, enco);

        for (float i = 0; i <= 1; i+=0.01){
            motor.speed(i);
            wait_ms(200);
            vReelMotor = motor.getSpeed();
            printf("Vitesse de mon moteur %f \r\n", vReelMotor);
        }
        for (float i = 1; i >= -1; i-=0.01){
            motor.speed(i);
            wait_ms(200);
            vReelMotor = motor.getSpeed();
            printf("Vitesse de mon moteur %f \r\n", vReelMotor);
        }
        for (float i = -1; i <= 0; i+=0.01){
            motor.speed(i);
            wait_ms(200);
            vReelMotor = motor.getSpeed();
            printf("Vitesse de mon moteur %f \r\n", vReelMotor);
        }
    }
}