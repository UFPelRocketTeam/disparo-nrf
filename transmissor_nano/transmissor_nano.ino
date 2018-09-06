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
//BOTAO - D5

int msg[1] = {1};
int rec[1] = {5};
RF24 radio(10, 9);
const uint64_t pipe[1] = {0xF0F0F0F0E1LL};
int BOTAO = 5;

void setup()
{
  Serial.begin(57600);
  radio.begin();
  delay(1000);
  //POSSÍVEIS MELHORAS:
  //radio.setPALevel(RF24_PA_MAX);
  //radio.setDataRate(RF24_250KBPS);
  //radio.setChannel(108);
  radio.setAutoAck(true);
  radio.enableAckPayload();
  radio.enableDynamicPayloads();
  radio.openWritingPipe(pipe[0]);
  radio.setRetries(15, 15);
  pinMode(BOTAO, INPUT_PULLUP);
}
void loop()
{
  Serial.println("Começou");
  Serial.print("Botão = ");
  if (digitalRead(BOTAO) == 1)
  {
    msg[0] = 1;
    Serial.println(msg[0]);
  }
  else
  {
    msg[0] = 2;
    Serial.println(msg[0]);
  }
  radio.stopListening();
  if (radio.write(msg, sizeof(msg)))
  {
    Serial.println(msg[0]);
    Serial.println("Enviado com sucesso!");
    if (radio.isAckPayloadAvailable())
    {
      radio.read(rec, sizeof(rec));
      Serial.println("Confirmado: ");
      Serial.println(rec[0]);
    }
    else
    {
      Serial.println("Não confirmado");
    }
  }
  else
  {
    Serial.println("Não enviado");
  }
}
