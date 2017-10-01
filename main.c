// PIC16F18857 Configuration Bit Settings
 
// 'C' source line config statements
 
// CONFIG1
#pragma config FEXTOSC = ECH    // External Oscillator mode selection bits (EC above 8MHz; PFM set to high power)
#pragma config RSTOSC = EXT1X   // Power-up default value for COSC bits (EXTOSC operating per FEXTOSC bits)
#pragma config CLKOUTEN = OFF   // Clock Out Enable bit (CLKOUT function is disabled; i/o or oscillator function on OSC2)
#pragma config CSWEN = ON       // Clock Switch Enable bit (Writing to NOSC and NDIV is allowed)
#pragma config FCMEN = ON       // Fail-Safe Clock Monitor Enable bit (FSCM timer enabled)
 
// CONFIG2
#pragma config MCLRE = ON       // Master Clear Enable bit (MCLR pin is Master Clear function)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config LPBOREN = OFF    // Low-Power BOR enable bit (ULPBOR disabled)
#pragma config BOREN = ON       // Brown-out reset enable bits (Brown-out Reset Enabled, SBOREN bit is ignored)
#pragma config BORV = LO        // Brown-out Reset Voltage Selection (Brown-out Reset Voltage (VBOR) set to 1.9V on LF, and 2.45V on F Devices)
#pragma config ZCD = OFF        // Zero-cross detect disable (Zero-cross detect circuit is disabled at POR.)
#pragma config PPS1WAY = ON     // Peripheral Pin Select one-way control (The PPSLOCK bit can be cleared and set only once in software)
#pragma config STVREN = ON      // Stack Overflow/Underflow Reset Enable bit (Stack Overflow or Underflow will cause a reset)
 
// CONFIG3
#pragma config WDTCPS = WDTCPS_31// WDT Period Select bits (Divider ratio 1:65536; software control of WDTPS)
#pragma config WDTE = ON        // WDT operating mode (WDT enabled regardless of sleep; SWDTEN ignored)
#pragma config WDTCWS = WDTCWS_7// WDT Window Select bits (window always open (100%); software control; keyed access not required)
#pragma config WDTCCS = SC      // WDT input clock selector (Software Control)
 
// CONFIG4
#pragma config WRT = OFF        // UserNVM self-write protection bits (Write protection off)
#pragma config SCANE = available// Scanner Enable bit (Scanner module is available for use)
#pragma config LVP = ON         // Low Voltage Programming Enable bit (Low Voltage programming enabled. MCLR/Vpp pin function is MCLR.)
 
// CONFIG5
#pragma config CP = OFF         // UserNVM Program memory code protection bit (Program Memory code protection disabled)
#pragma config CPD = OFF        // DataNVM code protection bit (Data EEPROM code protection disabled)
 
// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.
#define _XTAL_FREQ 32000000
#include <xc.h>
 
int analog_reading;
 
void ledcheck(void){
ADCON0bits.GO_nDONE=1; //do A/D measurement
while(ADCON0bits.GO_nDONE==1);
 
analog_reading= ADRESL + (ADRESH *256);
 if (analog_reading < 1000){
    PORTBbits.RB4= 0;
    }
 else{
    PORTBbits.RB4=1;
    }  
}
 
 
void main(void)
{
//SET UP
//OSCCON defaults to 31KH.
ADCON1= 0b01111110; //AN0 is analogue
TRISA= 0b11111111; //sets PORTA as all inputs, bit0 is AN0
TRISB= 0b00000000; //sets PORTB as all outputs
TRISC= 0b00000000;
PORTB= 0b00000000; //sets all outputs of PORTB off to begin with
PORTC= 0b00000000;
ADCON0bits.ADON=1; //turns on A/D
ADCON2= 0b10000000; //right justified, acquisition times are at 0 with 31KHz
 
while(1){
    for(int i=0; i<100; i++){
    ledcheck();
    PORTCbits.RC5 = 1;
    __delay_us(200);
    PORTCbits.RC5 = 0;
    __delay_us(1800);
    }
    for(int i=0; i<100; i++){
    ledcheck();
    PORTCbits.RC5 = 1;
    __delay_us(100);
    PORTCbits.RC5 = 0;
    __delay_us(1900);
   }
   
}
 
}