#include <LiquidCrystal.h>

#define LEITURA_VOUT A0

#define ZERO 500

//pinout leds de indicação para zerar a ponte
#define LED1 7
#define LED2 8
#define LED3 9

#define BOTAO 13

//-------------------------------------------------------------

bool papel = true; //true para sulfite e false para almaço
int pin_leitura = LEITURA_VOUT;
unsigned long tempo;
int vout_amp = 0;
int numero_folhas = 0;
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void zerar_numero_folhas()
{
  numero_folhas = 0;
}

void setup_leds()
{
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
}

void loop_leds(int comp)
{
  if(comp < (ZERO + 10) & comp > (ZERO - 10))
  {
    digitalWrite(LED2, HIGH);
  } else{digitalWrite(LED2, LOW);}
  if(comp <= (ZERO - 10) & comp > (ZERO - 200))
  {
    digitalWrite(LED1, HIGH);
  }else{digitalWrite(LED1, LOW);}
  if(comp < (ZERO + 200) & comp >= (ZERO + 10))
  {
    digitalWrite(LED3, HIGH);
  }else{digitalWrite(LED3, LOW);}
}

void loop_lcd(bool p)
{
  if((millis() - tempo) < 300)
  {
    //Limpa a tela
    //lcd.clear();
    //Posiciona o cursor na coluna 3, linha 0;
    lcd.setCursor(1, 0);
    //Envia o texto entre aspas para o LCD
    if(!p)
    {
      lcd.print("Sulfite"); 
    }
    else
    {
      lcd.print("Almaco ");
    }
    lcd.setCursor(1, 1);
    lcd.print(" Qtd: ");
    lcd.setCursor(7, 1);
    lcd.print(numero_folhas);
  }
  if((millis() - tempo) > 800){
    tempo = millis();
  }
}

void setup()
{
  Serial.begin(9600);
  lcd.begin(16, 2);
  pinMode(BOTAO, INPUT_PULLUP);
}

void loop()
{
  vout_amp = analogRead(pin_leitura);
  loop_leds(vout_amp);
  //Serial.println(vout_amp);
  if (digitalRead(BOTAO) == LOW)
  {
    papel = !papel;
  }
  loop_lcd(papel);
  Serial.println(papel);
}
