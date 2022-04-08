/*
 * File:   PreLab7.c
 * Author: Jorge Cerón
 *
 * Created on 4 de abril de 2022, 10:15 PM
 */
// PIC16F887 Configuration Bit Settings
// 'C' source line config statements
// CONFIG1
#pragma config FOSC = INTRC_NOCLKOUT// Oscillator Selection bits (INTOSCIO oscillator: I/O function on RA6/OSC2/CLKOUT pin, I/O function on RA7/OSC1/CLKIN)
#pragma config WDTE = OFF           // Watchdog Timer Enable bit (WDT disabled and can be enabled by SWDTEN bit of the WDTCON register)
#pragma config PWRTE = OFF          // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = OFF          // RE3/MCLR pin function select bit (RE3/MCLR pin function is digital input, MCLR internally tied to VDD)
#pragma config CP = OFF             // Code Protection bit (Program memory code protection is disabled)
#pragma config CPD = OFF            // Data Code Protection bit (Data memory code protection is disabled)
#pragma config BOREN = OFF          // Brown Out Reset Selection bits (BOR disabled)
#pragma config IESO = OFF           // Internal External Switchover bit (Internal/External Switchover mode is disabled)
#pragma config FCMEN = OFF          // Fail-Safe Clock Monitor Enabled bit (Fail-Safe Clock Monitor is disabled)
#pragma config LVP = OFF            // Low Voltage Programming Enable bit (RB3 pin has digital I/O, HV on MCLR must be used for programming)
// CONFIG2
#pragma config BOR4V = BOR40V       // Brown-out Reset Selection bit (Brown-out Reset set to 4.0V)
#pragma config WRT = OFF            // Flash Program Memory Self Write Enable bits (Write protection off)
// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include <xc.h>
#include <stdint.h>                 // int8_t, unit8_t
#define _XTAL_FREQ 4000000          

void __interrupt() isr (void){
    if(INTCONbits.RBIF){            // Verificar si se activa la bandera de interrupcion de PORTB
        if(!PORTBbits.RB0){         // Verificar si fue actividad por presionar RB0
            while(!RB0);            // Antirebotes (Si se mantiene presionado se queda en el while)
            PORTA++;                // Incrementar en 1 PORTA 
            INTCONbits.RBIF = 0;    // Limpiar la bandera de interrupcion de PORTB
        }
        else{
            if(!PORTBbits.RB1){     // Verificar si fue actividad por presionar RB1
            while(!RB1);            // Antirebotes (Si se mantiene presionado se queda en el while)
            PORTA--;                // Decrementar en 1 PORTA
            INTCONbits.RBIF = 0;    // Limpiar la bandera de interrupcion de PORTB
        }
    }
    }
    return;
}

void setup(void){
    ANSEL = 0;
    ANSELH = 0;                 // I/O digitales
        
    TRISA = 0x00;               // PORTA como salida
    TRISC = 0x00;               // PORTC como salida
    PORTA = 0x00;               // Se limpia PORTA
    PORTC = 0x00;               // Se limpia PORTC
    
    TRISBbits.TRISB0 = 1;       // RBO como entrada
    TRISBbits.TRISB1 = 1;       // RB1 como entrada
    
    OPTION_REGbits.nRBPU = 0;   // Habilitar Pull-ups
    WPUBbits.WPUB0 = 1;         // Pull-up en RB0
    WPUBbits.WPUB1 = 1;         // Pull-up en RB0
    INTCONbits.GIE = 1;         // Habilitar interrupciones globales
    INTCONbits.RBIE = 1;        // Habilitar interrupciones de PORTB
    IOCBbits.IOCB0 = 1;         // Habilitar interrupciones de cambio de estado en RB0
    IOCBbits.IOCB1 = 1;         // Habilitar interrupciones de cambio de estado en RB1
    INTCONbits.RBIF = 0;        // Limpiar la bandera de interrupcion de PORTB
    
    // Configuración del oscilador
    OSCCONbits.IRCF = 0b0110;   // 4MHz
    OSCCONbits.SCS = 1;         // Oscilador interno
    return;
}

void main(void){
    setup();
    while(1){
    }
    return;
}
