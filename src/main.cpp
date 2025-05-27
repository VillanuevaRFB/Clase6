#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

/*
//ejercicio 1: mostrar en monitor
void config_USART(void){
  UCSR0C|=(1<<UCSZ01)|(1<<UCSZ00);
  UCSR0B|=(1<<RXEN0)|(1<<TXEN0);
  UBRR0=103;//9600
}
void send_char(char valor){
  UDR0=valor;
  while(!(UCSR0A&(1<<TXC0)));
  UCSR0A|=(1<<TXC0);
}
int main(void){
  DDRD|=0x02;
  config_USART();
  while(1){
    send_char(105);
    _delay_ms(1000);
  }
}
*/
/*
//ejercicio 2: mostrar voltaje con potenciometro de 0.0 a 5.0
char entero=0;
char decima=0;
int valoradc=0;
int voltaje=0;

void config_USART(void){
  UCSR0C|=(1<<UCSZ01)|(1<<UCSZ00);//transmision sin interrupciones
  UCSR0B|=(1<<RXEN0)|(1<<TXEN0);
  UBRR0=103;//9600 Palabra por segundo palabra=bit
}

ISR(ADC_vect) {
  valoradc=ADC;
  voltaje=((long)valoradc*50)/1023;
  entero=voltaje/10;
  decima=voltaje%10;
  ADCSRA|=(1<<ADSC);
}

void send_char(char valor){//guardar en registro -ubr
  UDR0=valor;
  while(!(UCSR0A&(1<<TXC0)));
  UCSR0A|=(1<<TXC0);
}

int main(void){
  DDRD|=0X02;
  ADMUX|=(1<<REFS0);
  ADCSRA|=(1<<ADEN)|(1<<ADPS2)|(1<<ADIE);
  ADCSRA|=(1<<ADSC);
  sei();
  config_USART();
  while(1){
    send_char(entero+48);
    send_char(46);
    send_char(decima+48);
    send_char(13);
    send_char(10);
    _delay_ms(10);
  }
}
*/
/*
//ejercicio 3: mostrar voltaje potenciometro con interrupciones de 0 a 5
unsigned char value=0;
void config_ADC(void){
  ADCSRA|=(1<<ADEN)|(1<<ADIE)|(1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0);
  ADMUX|=(1<<REFS0);
}
ISR(ADC_vect){
  unsigned char low=ADCL;
  unsigned char high=ADCH;
  value=(high*256+low)*(5.0/1023.0);
  UCSR0B|=(1<<UDRIE0);
}
void config_USART(void){
  UCSR0C|=(1<<UCSZ00)|(1<<UCSZ01);
  UCSR0B|=(1<<TXEN0)|(1<<RXEN0);
  UBRR0=103; 
}
char flag=0;
ISR(USART_UDRE_vect){
  UDR0=value+48;
  UCSR0B&=~(1<<UDRIE0);
  ADCSRA|=(1<<ADSC);
}

int main(void){
  DDRD|=0x02;
  config_ADC();
  config_USART();
  sei();
  ADCSRA|=(1<<ADSC);
  while(1){
  }
}
*/
/*
//ejercicio 4: mostrar voltaje potenciometro con interrupciones de 0.0 a 5.0
float value=0;
int flag=0;
void config_ADC(void){
  ADCSRA|=(1<<ADEN)|(1<<ADIE)|(1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0);
  ADMUX|=(1<<REFS0);
}

ISR(ADC_vect){
  unsigned char low=ADCL;
  unsigned char high=ADCH;
  value=(high*256+low)*(5.0/1023.0);
  UCSR0B|=(1<<UDRIE0);
}

void config_USART(void){
  UCSR0C|=(1<<UCSZ00)|(1<<UCSZ01);
  UCSR0B|=(1<<TXEN0)|(1<<RXEN0);
  UBRR0=103; 
}

ISR(USART_UDRE_vect){
  switch(flag){
    case 0:
    UDR0=(unsigned char)(value)+'0';
    flag=1;
    break;
    case 1:
    UDR0=(unsigned char)(46);
    flag=2;
    break;
    case 2:
    UDR0=((unsigned char)(value*10))%10+'0';
    flag=3;
    break;
    case 3:
    UDR0=((unsigned char)(value*100))%10+'0';
    flag=4;
    break;
    case 4:
    UDR0=(unsigned char)(13);
    flag=5;
    break;
    case 5:
    UDR0=(unsigned char)(10);
    flag=0;
    UCSR0B&=~(1<<UDRIE0);
    ADCSRA|=(1<<ADSC);_delay_ms(100);
    break;
  }
}

int main(void){
  DDRD|=0x02;
  config_ADC();
  config_USART();
  sei();
  ADCSRA|=(1<<ADSC);
  while(1){
  }
}
*/
/*
//ejercicio 5: recivir caracter
char receive_char(void){
  while(!(UCSR0A&(1<<RXC0)));
  return UDR0;
}

void config_USART(void){
  UCSR0B|=(1<<RXEN0)|(1<<TXEN0);
  UCSR0C|=(1<<UCSZ00)|(1<<UCSZ01);
  UBRR0=103;//9600 baudrate
}

unsigned char dato=0;
ISR(USART_UDRE_vect){
  UDR0=dato;
  UCSR0B&=~(1<<UDRIE0);
}

int main(void){
  config_USART();
  sei();
  while(1){
   dato=receive_char();
   UCSR0B|=(1<<UDRIE0);
  }
}
*/
/*
//ejercicio 6: mostrar voltaje al presionar a
float value=0;
int flag=0;
void config_ADC(void){
  ADCSRA|=(1<<ADEN)|(1<<ADIE)|(1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0);
  ADMUX|=(1<<REFS0);
}

ISR(ADC_vect){
  unsigned char low=ADCL;
  unsigned char high=ADCH;
  value=(high*256+low)*(5.0/1023.0);
  UCSR0B|=(1<<UDRIE0);
}

char receive_char(void){
  while(!(UCSR0A&(1<<RXC0)));
  return UDR0;
}

void config_USART(void){
  UCSR0B|=(1<<RXEN0)|(1<<TXEN0);
  UCSR0C|=(1<<UCSZ00)|(1<<UCSZ01);
  UBRR0=103;//9600 baudrate
}

unsigned char dato=0;
ISR(USART_UDRE_vect){
  switch(flag){
    case 0:
    UDR0=(unsigned char)(value)+'0';
    flag=1;
    break;
    case 1:
    UDR0=(unsigned char)(46);
    flag=2;
    break;
    case 2:
    UDR0=((unsigned char)(value*10))%10+'0';
    flag=3;
    break;
    case 3:
    UDR0=((unsigned char)(value*100))%10+'0';
    flag=4;
    break;
    case 4:
    UDR0=(unsigned char)(13);
    flag=5;
    break;
    case 5:
    UDR0=(unsigned char)(10);
    flag=0;
    UCSR0B&=~(1<<UDRIE0);
   _delay_ms(100);
    break;
  }
}

int main(void){
  config_USART();
  config_ADC();
  sei();
  while(1){
   dato=receive_char();
   if(dato=='a'){
    dato=0;
    ADCSRA|=(1<<ADSC);
   }
  }
}
*/
/*
//ejercicio 7: mostrar voltaje al presionar a con interrupciones
float value=0;
int flag=0;
void config_ADC(void){
  ADCSRA|=(1<<ADEN)|(1<<ADIE)|(1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0);
  ADMUX|=(1<<REFS0);
}

ISR(ADC_vect){
  unsigned char low=ADCL;
  unsigned char high=ADCH;
  value=(high*256+low)*(5.0/1023.0);
  UCSR0B|=(1<<UDRIE0);
}

void config_USART(void){
  UCSR0B|=(1<<RXEN0)|(1<<TXEN0)|(1<<RXCIE0);
  UCSR0C|=(1<<UCSZ00)|(1<<UCSZ01);
  UBRR0=103;//9600 baudrate
}

unsigned char dato=0;
ISR(USART_UDRE_vect){
  switch(flag){
    case 0:
    UDR0=(unsigned char)(value)+'0';
    flag=1;
    break;
    case 1:
    UDR0=(unsigned char)(46);
    flag=2;
    break;
    case 2:
    UDR0=((unsigned char)(value*10))%10+'0';
    flag=3;
    break;
    case 3:
    UDR0=((unsigned char)(value*100))%10+'0';
    flag=4;
    break;
    case 4:
    UDR0=(unsigned char)(13);
    flag=5;
    break;
    case 5:
    UDR0=(unsigned char)(10);
    flag=0;
    UCSR0B&=~(1<<UDRIE0);
   _delay_ms(100);
    break;
  }
}

ISR(USART_RX_vect){
  dato=UDR0;
  if(dato=='a'){
    dato=0;
    ADCSRA|=(1<<ADSC);
  }
}
int main(void){
  config_USART();
  config_ADC();
  sei();
  while(1){
  }
}
*/

//ejercicio 8: conectar 2 arduinos, mandar y recibir señal(tarea)
float value=0;
int flag=0;
void config_ADC(void){
  ADCSRA|=(1<<ADEN)|(1<<ADIE)|(1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0);
  ADMUX|=(1<<REFS0);
}

ISR(ADC_vect){
  unsigned char low=ADCL;
  unsigned char high=ADCH;
  value=(high*256+low)*(50.0/1023.0);
  UCSR0B|=(1<<UDRIE0);
}

void config_USART(void){
  UCSR0B|=(1<<RXEN0)|(1<<TXEN0)|(1<<RXCIE0);
  UCSR0C|=(1<<UCSZ00)|(1<<UCSZ01);
  UBRR0=103;//9600 baudrate
}

unsigned char dato=0;
ISR(USART_UDRE_vect){
  switch(flag){
    case 0:
    UDR0=(unsigned char)(value/10)%10+'0';
    flag=1;
    break;
    case 1:
    UDR0=(unsigned char)(46);
    flag=2;
    break;
    case 2:
    UDR0=((unsigned char)(value))%10+'0';
    flag=3;
    break;
    case 3:
    UDR0=(unsigned char)(13);
    flag=4;
    break;
    case 4:
    UDR0=(unsigned char)(10);
    flag=0;
    UCSR0B&=~(1<<UDRIE0);
   _delay_ms(100);
    break;
  }
}

ISR(USART_RX_vect){
  dato=UDR0;
  if(dato=='a'){
    dato=0;
    ADCSRA|=(1<<ADSC);
  }
}
int main(void){
  config_USART();
  config_ADC();
  sei();
  while(1){
  }
}