#include "mbed.h"
#include "Motor.h"
#include <cstdio>

Serial pc(USBTX, USBRX, 115200);
Motor motor(D10, D9, D6, D5, D4);       //pwm, fwd, rev, EncA, EncB

int _count;                             //declaration du compteur pour l'encodeur
int rev = 12;                           // nombre de tick sur l'encodeur
int dir = -1;                           //sens de direction du moteur par rapport a l'encodeur
float ratio = 34.014;                   //rapport de réduction
int freq_echnatillonnage = 50;          //frequence d'execution de l'asservissement
float vReelMotor ;                      //vitesse de ma roue
float _Tq = 0.01;                       //fréquence d'échantillonnage pour update et afficher la vitesse
Ticker t;
Timer tm;

int main() {
    motor.speed(0); 
     
    float cmd = 0.5;                    //commande du moteur
    int stop = 1;                       //variable pour faire démarer la boucle while
    int compt_chang = 0;                //compteur pour changer la vitesse voulue du moteur
    
    tm.start();
    int t0 = tm.read_ms();
    while (stop) {    
        int dt = tm.read_ms() - t0;
        if (dt >= _Tq*1000) {
            
            motor.speed(cmd);                                        //donner la commande au moteur
            vReelMotor = motor.getSpeed();
            printf("Vitesse de mon moteur %f \r\n", vReelMotor);

            tm.reset();
            compt_chang++;                                           //incrementation pour changement de vitsse
            t0 = tm.read_ms();
            if (compt_chang == 500) {                                //changement de la vitesse
                cmd = -0.5;
            }
        }       
    }
}