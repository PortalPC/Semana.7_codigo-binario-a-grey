#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#define F_CPU 16000000UL


char cuenta_binario = 0;
char cuenta_gray = 0;
 char a =0;
  void config_IE (void){
    EIMSK |= (1<<INT0); // Habilitar interrupción externa INT0
    EICRA |= (1<<ISC01); // Configurar INT0 para disparar en flanco de bajada
    DDRD &= ~(0X04);
    PORTD |= 0x04;

  }

  ISR(INT0_vect) {
    a++;
    if(a>1){
      a = 0;
    }
    
  }
  int main(void){
DDRD |= 0x0F;
DDRB |= 0x0F;
while(1){
  cuenta_binario++;

  if(cuenta_binario >15){
    cuenta_binario = 0;
  }
  
cuenta_gray = cuenta_binario ^ (cuenta_binario << 1); // Convertir a Gray
if(a ==1){
  PORTD |=((cuenta_binario | 0x00) << 4);
  PORTD &= ((cuenta_binario | 0x00) << 4);
  PORTB |=(cuenta_gray |0x00);
  PORTB &= (cuenta_gray |0xF0);



}else{
  PORTD &= ~(0xF0);
  PORTB = ~(0x0F);
}
_delay_ms(1000);
}
  }
  