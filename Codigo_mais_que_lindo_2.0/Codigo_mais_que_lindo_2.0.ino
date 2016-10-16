//////////////////////////////////////////////////
//// Agradecimento ao criador da biblioteca   ////
//// do neuro que utilizei George Profenza    ////
//////////////////////////////////////////////////
#include <Servo.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <SPI.h>
#include <RFID.h>
#include <Mindwave.h>

/////////////////////////////////////
//                               ////
//Variaveis de dificuldade Luscas////
//                               ////
/////////////////////////////////////

int min = 70;
int max = 85;

//Declarações RF-ID
#define SS_PIN 10
#define RST_PIN 9

RFID rfid(SS_PIN, RST_PIN);
String conteudo;
int cont;
int card;

//Declarações do Servo
Servo myservo;
int aberto = 30;
int fechado = 110;

//Declarações do LCD
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);

// neuro novo
Mindwave mindwave;

//LED's
int l1 = 2;
int l2 = 3;

//Buzzer
int buz = 4;
int buze = 0;
int trava_buz;



void onMindwaveData() {

//modo hospital para trancar portas em caso de emergencia//

  if (conteudo == "aa 6c 5e a5")
  {
    if (myservo.read() == fechado) {
      digitalWrite(l1, LOW);
      digitalWrite(l2, LOW);
      noTone(buz);
      myservo.write(aberto);
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Porta Liberada");
      cont = 0;
      delay(3000);
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Enfermeiro: Lucas");
      lcd.setCursor(0, 1);
      lcd.print("Liberado");
      conteudo = "";
    } else {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Paciente: Joao");
      lcd.setCursor(0, 1);
      lcd.print("Situacao: OK");
      if (mindwave.attention() > 70) {
        cont = cont + 1;
      } else {
        cont = 0;
      }
      if (cont == 5) {
        digitalWrite(l1, HIGH);
        tone(buz, 1500);
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Paciente: Joao");
        lcd.setCursor(0, 1);
        lcd.print("Sit.: Agitado");
        myservo.write(fechado);
        conteudo = "";
      }
    }

  } else
    if (conteudo == "76 11 ca 32")
  {
    if (myservo.read() == fechado) {
      digitalWrite(l1, LOW);
      digitalWrite(l2, LOW);
      noTone(buz);
      myservo.write(aberto);
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Porta Liberada");
      cont = 0;
      delay(3000);
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Enf. Batista");
      lcd.setCursor(0, 1);
      lcd.print("Liberado");
      conteudo = "";
    } else {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Paciente: Tobi");
      lcd.setCursor(0, 1);
      lcd.print("Situacao: OK");
      if (mindwave.attention() > 40) {
        cont = cont + 1;
      } else {
        cont = 0;
      }
      if (cont == 5) {
        digitalWrite(l2, HIGH);
        tone(buz, 2000);
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Paciente: Tobi");
        lcd.setCursor(0, 1);
        lcd.print("Sit.: Agitado");
        myservo.write(fechado);
        conteudo = "";
      }
    }

  } else





  //Aqui verificamos qual vai ser a dificuldade da abertura e também verifica
  // se a trava vai abrir ou fechar
  //Modo Dificil
  if (conteudo == "c4 81 29 b9")
  {
    if (myservo.read() == 30) {
     // digitalWrite(l1, LOW);
     // digitalWrite(l2, LOW);
     // noTone(buz);
      myservo.write(fechado);
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Trava Fechada");
      cont = 0;
      delay(3000);
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Aproxime o card");
      lcd.setCursor(0, 1);
      lcd.print("de identificacao");
      conteudo = "";
    } else {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Bem Vindo: ");
      lcd.setCursor(0, 1);
      lcd.print("Luscas");
      //myservo.write(aberto);
      if (mindwave.meditation() > min && mindwave.meditation() < max) {
        cont = cont + 1;
      } else {
        cont = 0;
      }
      if (cont == 5) {
        //digitalWrite(l1, HIGH);
        //tone(buz, 1500);
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Trava Aberta");
        myservo.write(aberto);
        conteudo = "";
      }
    }

  } else
    //Aqui verificamos qual vai ser a dificuldade da abertura e também verifica
    // se a trava vai abrir ou fechar
    //Modo Facil
    if (conteudo == "73 49 72 9a")
    {
      if (myservo.read() == 30) {
       // digitalWrite(l1, LOW);
       // digitalWrite(l2, LOW);
       // noTone(buz);
        myservo.write(fechado);
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Trava Fechada");
        cont = 0;
        delay(3000);
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Aproxime o card");
        lcd.setCursor(0, 1);
        lcd.print("de identificacao");
        conteudo = "";

      } else {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Bem Vindo: ");
        lcd.setCursor(0, 1);
        lcd.print("EasyMode");
        if (mindwave.meditation() > 40) {
          cont = cont + 1;
        } else {
          cont = 0;
        }
        if (cont == 5) {
          //digitalWrite(l2, HIGH);
         // tone(buz, 100);
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("Trava Aberta");
          myservo.write(aberto);
          conteudo = "";
        }
      }
    } else
      // aqui valido se o cartão que o leitor pegou é um dos nossos ou não
      if (conteudo != "" && conteudo != "c4 81 29 b9" && conteudo != "73 49 72 9a" && conteudo != "aa 6c 5e a5" && conteudo != "76 11 ca 32") {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Cartao nao");
        lcd.setCursor(0, 1);
        lcd.print("cadastrado");
        delay(3000);
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Aproxime o card");
        lcd.setCursor(0, 1);
        lcd.print("de identificacao");
      }


  //Envio da leitura para a Serial
  //todos os dados do neuro são passados para a Serial e o nosso contador
  // para verificar se a trava vai abrir ou nao
  Serial.print("{\"Buze\":");
  Serial.print(buze);
  Serial.print(",\"Cont\":");
  Serial.print(cont);
  Serial.print(",\"quality\":");
  Serial.print(mindwave.quality());
  Serial.print(",\"tattention\":");
  Serial.print(mindwave.attention());
  Serial.print(",\"meditation\":");
  Serial.print(mindwave.meditation());
  Serial.print(",\"last update\":");
  Serial.print(mindwave.lastUpdate());
  Serial.print("}");
  Serial.println();


//Verifica se o NeuroSky foi desconectado
//caso sim, apita e traca o paciente até um enfermeiro ir verificar
  if (mindwave.attention() == 0 && mindwave.meditation() == 0) {
    buze = buze + 1;
    trava_buz = 1;
  } else if(trava_buz == 1){
    buze = 0;
    noTone(buz);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Aproxime o card");
    lcd.setCursor(0, 1);
    lcd.print("de identificacao");
    trava_buz = 0;
  }
  if (buze == 15) {
    tone(buz, 50);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("NeuroSky");
    lcd.setCursor(0, 1);
    lcd.print("Desconectado");
    myservo.write(fechado);

  }

  //rf-id
  //onde o leitor lê o cartão encostado e pega sua UID e guarda na variável conteudo
  if (rfid.isCard()) {
    Serial.println("IS CARD");
    if (rfid.readCardSerial()) {
      conteudo = "";
      conteudo.concat(String(rfid.serNum[0], HEX));
      conteudo.concat(" ");
      conteudo.concat(String(rfid.serNum[1], HEX));
      conteudo.concat(" ");
      conteudo.concat(String(rfid.serNum[2], HEX));
      conteudo.concat(" ");
      conteudo.concat(String(rfid.serNum[3], HEX));
      Serial.print(conteudo);
      Serial.println("");
    }
  }
}


//////////////////////////
// Microprocessor Setup //
//////////////////////////
void setup() {
  //neuro novo
  //Inicia a Serial com velocidade de 57600
  //essa variavel MINDWAVE_BAUDRATE está na biblioteca que encontrei
  Serial.begin(MINDWAVE_BAUDRATE);

  //Servo
  //informa o pin do servo e inicia ele fechado ou = 30
  myservo.attach(7);
  myservo.write(fechado);

  //LCD
  //Inicia o LCD e informa a frase incial
  lcd.begin (16, 2);
  lcd.setBacklight(HIGH);
  lcd.setCursor(0, 0);
  lcd.print("Aproxime o card");
  lcd.setCursor(0, 1);
  lcd.print("de identificacao");
  //RF-ID
  //inicia o rfid
  SPI.begin();
  rfid.init();
  conteudo = "";
  //LED's
  pinMode(l1, OUTPUT);
  pinMode(l2, OUTPUT);
  //Buzzer
  pinMode(buz, OUTPUT);
}
/////////////
//MAIN LOOP//
/////////////
void loop() {
  //Executa a function criada anteriormente
  mindwave.update(Serial, onMindwaveData);
}
