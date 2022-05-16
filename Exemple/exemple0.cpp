#include "mbed.h"
#include "Motor.h"
#include <cstdio>

Serial pc(USBTX, USBRX, 115200);
Motor motor(D10, D9, D6, D5, D4);       //pwm, fwd, rev, EncA, EncB

float vReelMotor ;                      //vitesse de ma roue

int main() {
    motor.speed(0); 
    float cmd = 0;                      //commande du moteur
   
    for (int i = 0; i <= 1; i++){
        motor.speed(i);
        vReelMotor = motor.getSpeed();
        printf("Vitesse de mon moteur %f \r\n", vReelMotor);
    }
    for (int j = 1; j >= -1; j--){
        motor.speed(j);
        vReelMotor = motor.getSpeed();
        printf("Vitesse de mon moteur %f \r\n", vReelMotor);
    }
    for (int k = -1; k <= 0; k++){
        motor.speed(k);
        vReelMotor = motor.getSpeed();
        printf("Vitesse de mon moteur %f \r\n", vReelMotor);
    }
}