#include <xc.h>    //Use this to include the device header for your PIC.

#define _XTAL_FREQ 4000000  //4MHz, which is default
#define PK1 PORTDbits.RD4
#define PK2 PORTDbits.RD5
#define PK3 PORTDbits.RD6
#define PK4 PORTDbits.RD7
#define PK5 PORTBbits.RB0
#define PK6 PORTBbits.RB1
#define PK7 PORTBbits.RB2
#define PK8 PORTBbits.RB3
#define PK9 PORTBbits.RB4
#define PK10 PORTBbits.RB5

//set the configuration bits: internal OSC, everything off except MCLR
#pragma config FOSC=INTOSC, WDTE=OFF, PWRTE=OFF, MCLRE=ON, CP=OFF, \
                , BOREN=OFF, IESO=OFF, FCMEN=OFF

#define TIMER_RESET_VALUE 25 // http://picguides.com/beginner/timers.php                        

int delayTime = 0;          //A global variable to store the time that has
                            //elapsed. This must be global!
    int i;
    int k;   
    int a;
    int b;
    int a1;
    int c;
    int p=0;
    
    void seven_segm(int cyfra){
        switch(cyfra){
            case 0:
                PORTC = 0b00111111;
                break;
            case 1:
                PORTC = 0b00000110;
                break;
            case 2:
                PORTC = 0b01011011;
                break;
            case 3:
                PORTC = 0b01001111;
                break;
            case 4:
                PORTC = 0b01100110;
                break;
            case 5:
                PORTC = 0b01101101;
                break;
            case 6:
                PORTC = 0b01111101;
                break;
            case 7:
                PORTC = 0b00000111;
                break;
            case 8:
                PORTC = 0b01111111;
                break;
            case 9:
                PORTC = 0b01101111;
                break;
        }
  }
    void seven_segm_kropka(int kropka){
        switch(kropka){
            case 0:
                PORTC = 0b10111111;
                break;
            case 1:
                PORTC = 0b10000110;
                break;
            case 2:
                PORTC = 0b11011011;
                break;
            case 3:
                PORTC = 0b11001111;
                break;
            case 4:
                PORTC = 0b11100110;
                break;
            case 5:
                PORTC = 0b11101101;
                break;
            case 6:
                PORTC = 0b11111101;
                break;
            case 7:
                PORTC = 0b10000111;
                break;
            case 8:
                PORTC = 0b11111111;
                break;
            case 9:
                PORTC = 0b11101111;
                break;
        }
  }
    
void interrupt isr(){
    
    INTCONbits.T0IF = 0;        //Clear the Timer 0 interrupt flag
    TMR0 = TIMER_RESET_VALUE;   //Load the starting value back into the timer
   
       PORTDbits.RD0 = 1; 
       PORTDbits.RD1 = 1;
       PORTDbits.RD2 = 1; 
       PORTDbits.RD3 = 1;
       k++;
       delayTime++;
                      
    if(delayTime >= 17800){      // CZAS "MARTWY" PRZEKAZNIKOW
        PK1=PK2=PK3=PK4=PK5=PK6=PK7=PK8=PK9=PK10=0;
        p=0;
        }
       
    if(delayTime >= 18000) {     // CZAS PRZELACZENIA KOLEJNYCH PRZEKAZNIKOW
        delayTime = 0;
        i++;
        p=1;
        }
       
       
    if(k==1){                  // PIERWSZY WYSWIETACZ
       seven_segm(a1);
       PORTDbits.RD0 = 0; 
       PORTDbits.RD1 = 1;
       PORTDbits.RD2 = 1; 
       PORTDbits.RD3 = 1;  
    }
    
    if(k==2){                   // DRUGI WYSWIETACZ
       seven_segm_kropka(a);
       PORTDbits.RD0 = 1; 
       PORTDbits.RD1 = 0;
       PORTDbits.RD2 = 1; 
       PORTDbits.RD3 = 1;   
    }
    
    if(k==3){                   // TRZECI WYSWIETACZ
       seven_segm(b);
       PORTDbits.RD0 = 1; 
       PORTDbits.RD1 = 1;
       PORTDbits.RD2 = 0; 
       PORTDbits.RD3 = 1;   
    }
    
    if(k==4){                   // CZWARTY WYSWIETACZ
       seven_segm(c);
       PORTDbits.RD0 = 1; 
       PORTDbits.RD1 = 1;
       PORTDbits.RD2 = 1; 
       PORTDbits.RD3 = 0;   
    }
            
    if(k>4) k=0;
}
// FUNKCJA WYLACZAJACA WSZYSTKIE PRZEKAZNIKI//
void zerowanie(){
    PK1=PK2=PK3=PK4=PK5=PK6=PK7=PK8=PK9=PK10=0;
   
}

//OBLICZENIE ILOSCI PRZEKAZNIKOW ZA POMOCA ZWOREK//
int zworki(){
        int Z0, Z1, Z2, Z3;
                
        if(PORTAbits.RA0==1) Z0=1;
        else Z0=0;
        if(PORTAbits.RA1==1) Z1=2;
        else Z1=0;
        if(PORTAbits.RA2==1) Z2=4;
        else Z2=0;
        if(PORTAbits.RA3==1) Z3=8;
        else Z3=0;
                      
        return (Z0 + Z1 + Z2 +Z3);
    }

//PRZELACZENIE PRZEKAZNIKOW//
przekazniki(int i){
        
    switch(i){      
            
            case 1:
                zerowanie();
                PK1 = 1;
                break;
            case 2:
                zerowanie();
                PK2 = 1;
                break;
             case 3:
                zerowanie();
                PK3 = 1;
                break;
            case 4:
                zerowanie();
                PK4 = 1;
                break;
            case 5:
                zerowanie();
                PK5 = 1;
                break;
            case 6:
                zerowanie();
                PK6 = 1;
                break;
            case 7:
                zerowanie();
                PK7 = 1;
                break;
            case 8:
                zerowanie();
                PK8 = 1;
                break;
            case 9:
                zerowanie();
                PK9 = 1;
                break;
            case 10:
                zerowanie();
                PK10 = 1;
                break;          
        }
}


int main(){
    
    double result;          // musi byc double
    int pomiar;
    int pomiar1;
    int pomiar2;
    int pomiar3;
    int pomiar4;
    int pomiar5;
    int pomiar6;
        
    
    TRISA = 0xFF;             
    ANSELAbits.ANSA5 = 1;     //set RA5/AN4 to analog mode
    TRISB = 0x00;
    TRISC = 0x00;             
    TRISD = 0x00;
       
    ANSELD = 0x00;            //disable analog port D !WAZNE!
    ANSELAbits.ANSA0 = 0;     //disable analog pin
    ANSELAbits.ANSA1 = 0;       
    ANSELAbits.ANSA2 = 0; 
    ANSELAbits.ANSA3 = 0; 
    
    ///////////////
    // ADC Setup //
    ///////////////
    ADCON1bits.ADFM = 1;        //ADC result is right justified
    ADCON1bits.ADPREF = 0;      //Vdd is the +ve reference
    ADCON1bits.ADCS = 0b001;    //Fosc/8 is the conversion clock
                                //This is selected because the conversion
                                //clock period (Tad) must be greater than 1.5us.
                                //With a Fosc of 4MHz, Fosc/8 results in a Tad
                                //of 2us.
    ADCON0bits.CHS = 4;         //select analog input, AN4
    ADCON0bits.ADON = 1;        //Turn on the ADC
    
    
    ///////////////////
    // Timer 0 Setup //
    ///////////////////
    OPTION_REGbits.PSA = 0;     //Prescaler assigned to Timer 0 (other option is to
                                //the Watchdog timer (WDT))

    OPTION_REGbits.PS = 0b000;  //Set the prescaler to 1:4
    OPTION_REGbits.T0CS = 0;    //Use the instruction clock (Fcy/4) as the timer
                                //clock. Other option is an external oscillator
                                //or clock on the T0CKI pin.

    INTCONbits.T0IF = 0;        //Clear the Timer 0 interrupt flag
    TMR0 = TIMER_RESET_VALUE;   //Load the starting value into the timer
    INTCONbits.T0IE = 1;        //Enable the Timer 0 interrupt   
    INTCONbits.GIE = 1;         //set the Global Interrupt Enable
        

    ///////////////////////
    // Main Program Loop //
    ///////////////////////
    while(1){          
             
       //OBLICZANIE CYFR WYSWIETLACZA 7SEG// 
       a1 = pomiar/1000;             // PIERWSZY WYSWIETLACZ
       
       if(pomiar<1000) a = pomiar/100;    // DRUGI WYSWIETLACZ
       else a = (pomiar%1000)/100;   
       
       b = (pomiar%100)/10;          // TRZECI WYSWIETLACZ
       c = pomiar%10;                // CZWARTY WYSWIETLACZ
          
              
        //ADC//           
            __delay_us(5);              //Wait the acquisition time (about 5us).
        ADCON0bits.GO = 1;              //start the conversion
        while(ADCON0bits.GO==1){};      //wait for the conversion to end
        result = (ADRESH<<8)+ADRESL;	//combine the 10 bits of the conversion
        
        //SZESC POMIAROW W CELU USREDNIENIA //
        pomiar1 = ((result*3300)/1023); 
        pomiar2 = ((result*3300)/1023);
        pomiar3 = ((result*3300)/1023);
        pomiar4 = ((result*3300)/1023);
        pomiar5 = ((result*3300)/1023);
        pomiar6 = ((result*3300)/1023);
                      
        pomiar=(pomiar1+pomiar2+pomiar3+pomiar4+pomiar5+pomiar6)/6;
                  
        if(i>zworki() || i>10) i=1;
        if(p==1) przekazniki(i);                         
              
    }
    return 0;
    
}