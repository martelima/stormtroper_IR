// INCLUSÃO DE BIBLIOTECA
#include <IRremote.h>
#include <PushButton.h>

// DIRETIVAS DE COMPILAÇÃO
#define tempoTecla 350
#define frequencia 38 // kHz

// DEFINIÇÃO DOS PINOS
#define pinReceptor 11
#define pinBot1 8
#define pinLed 12

// INSTANCIANDO OBJETOS
IRrecv receptorIR(pinReceptor);
IRsend emissorIR;
PushButton botaoLeitura(pinBot1);

// DECLARAÇÃO VARIÁVEIS GLOBAIS
bool lerComando = false;

// DECLARAÇÃO DAS FUNÇÕES DE LEITURA

void ircode   (decode_results *results);
void encoding (decode_results *results);
void dumpInfo (decode_results *results);
void dumpRaw  (decode_results *results);
void dumpCode (decode_results *results);

//  DECLARAÇÃO DAS TECLAS CLONADAS

unsigned int teclaA[] = {8800,4500, 550,550, 600,500, 600,550, 550,550, 600,500, 650,500, 550,550, 550,550, 600,1650, 600,1650, 550,1700, 600,1650, 600,500, 600,1650, 600,1650, 550,1650, 650,1600, 600,1650, 550,600, 550,550, 600,500, 550,550, 600,500, 650,500, 550,550, 650,450, 600,1650, 600,1650, 550,1700, 600,1650, 600,1650, 550,1650, 600};
unsigned int teclaB[] = {8800,4500, 550,550, 600,500, 650,500, 550,550, 650,450, 600,550, 600,500, 600,500, 600,1650, 600,1650, 550,1700, 550,1700, 600,500, 600,1650, 600,1600, 600,1650, 600,550, 600,1600, 600,550, 550,550, 600,500, 600,550, 550,550, 600,500, 600,1650, 600,500, 650,1600, 600,1650, 550,1700, 550,1700, 600,1600, 550,1700, 600};
unsigned int teclaC[] = {8900,4500, 500,600, 500,650, 450,650, 450,650, 450,650, 450,650, 500,600, 500,600, 500,1700, 500,600, 500,1750, 500,1700, 500,1700, 500,1700, 500,650, 450,1750, 500,600, 500,600, 500,600, 500,1700, 500,650, 450,650, 500,600, 500,600, 500,1700, 500,1750, 450,1750, 500,600, 500,1750, 450,1750, 450,1750, 500,1700, 500};
unsigned int teclaD[] = {/*COPIE_OS_DADOS_DENTRO_DAS_CHAVES_DO_MONITOR_SERIAL_E_COLE_AQUI*/};

void setup() {
  Serial.begin(9600);
  pinMode(pinLed, OUTPUT);

  // INICIANDO RECEPTOR IR
  receptorIR.enableIRIn();
  Serial.print("Setup Concluído");

}

void loop() {
  // MÉTODO PARA LEITURA E ATUALIZAÇÃO DAS PROPRIEDADES DO BOTÃO
  botaoLeitura.button_loop();

  // BLOCO CONDIÇÕES PARA INICIAR LEITURA
  if (botaoLeitura.pressed() && !lerComando) {
    lerComando = true;
    digitalWrite(pinLed, HIGH);
  } else if (botaoLeitura.pressed() && lerComando) {
    lerComando = false;
    digitalWrite(pinLed, LOW);
  }

  // LAÇO PARA LEITURA DO RECEPTOR IR QUANDO FOR PRESSIONADO O BOTÃO
  while (lerComando) {

    decode_results  results;

    if (receptorIR.decode(&results)) {
      ircode   (&results);
      encoding (&results);
      dumpInfo (&results);
      dumpRaw  (&results);
      dumpCode (&results);
      receptorIR.resume();
      lerComando = false;
      digitalWrite(pinLed, LOW);
    }
  }

  // BLOCO PARA RECEBER DADOS DA SERIAL E INICIAR EMISSOR IR
  if (Serial.available()) {
    char tecla = Serial.read();

    switch (tecla) {
      case 'a':
        emissorIR.sendRaw(teclaA, sizeof(teclaA) / sizeof(teclaA[0]), frequencia);
        Serial.println("Enviando Tecla A clonada");
        delay(tempoTecla);
        break;

      case 'b':
        emissorIR.sendRaw(teclaB, sizeof(teclaB) / sizeof(teclaB[0]), frequencia);
        Serial.println("Enviando Tecla B clonada");
        delay(tempoTecla);
        break;

      case 'c':
        emissorIR.sendRaw(teclaC, sizeof(teclaC) / sizeof(teclaC[0]), frequencia);
        Serial.println("Enviando Tecla C clonada");
        delay(tempoTecla);
        break;

      case 'd':
        emissorIR.sendRaw(teclaD, sizeof(teclaD) / sizeof(teclaD[0]), frequencia);
        Serial.println("Enviando Tecla D clonada");
        delay(tempoTecla);
        break;
    }
  }
}
