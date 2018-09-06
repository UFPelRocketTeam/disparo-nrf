#include<SPI.h>
#include<nRF24L01.h>
#include<RF24.h>

//PINAGEM NANO:
//CE - D10
//CSN - D9
//V+ - 3.3V
//GND - GND
//MISO - D12
//MOSI - D11
//SCK - D13
//LED/TRANSISTOR - D4



const uint64_t pipe[1]= {0xF0F0F0F0E1LL};
RF24 radio(10,9);
int rec[1] = {0};
int LED = 4;
boolean estadoled = false;
void setup()
{
  //POSSÍVEIS MELHORAS: (depende da fonte de alimentação)
//  radio.setPALevel(RF24_PA_MAX);
//  radio.setDataRate(RF24_250KBPS);
//  radio.setChannel(108);
  Serial.begin(57600);
  radio.begin();
  delay(100);
  radio.setAutoAck(true);
  radio.enableAckPayload();
  radio.enableDynamicPayloads();
  radio.openReadingPipe(1,pipe[0]);
  radio.startListening();
  radio.setRetries(15,15);
  pinMode(LED, OUTPUT);
  digitalWrite(LED, LOW);
}
void loop()
{

  if(radio.available())
  {
   
    if(radio.read(rec,sizeof(rec)))
    {
      radio.writeAckPayload(1,rec,sizeof(rec));
      Serial.print("Recebido: ");
      Serial.println(rec[0]);
      if(rec[0] == 2)
            {
              
            estadoled = !estadoled;
            digitalWrite(LED, estadoled);
            while(rec[0] != 1)
                  {
                  float atual = millis()+100;
                  while(millis() <= atual)
                          {
                          radio.read(rec,sizeof(rec));
                          radio.writeAckPayload(1,rec,sizeof(rec));
                          Serial.print("Recebido: ");
                          Serial.println(2);
                          }
                  }
              
            }

            
     
    }

    else
    {Serial.println("Mensagem não recebida");}
  }
}

