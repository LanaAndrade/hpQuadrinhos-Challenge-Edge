
#include <PubSubClient.h>
#include <WiFi.h>
#include <ArduinoJson.h>

//***************************************************************

int currentMillis = 0;
int previousMillis = 0;


const int redPin = 13;
const int greenPin = 12;
const int bluePin = 14;
int analogValue = 0;
const int PWM_FREQUENCY = 1000;
const int PWM_RESOLUTION = 8;
int PWM_CHANNEL = 0;
int PWM_CHANNEL1 = 1;
int PWM_CHANNEL2 = 2;

int currentColor = 0;  // 0: Red, 1: Green, 2: Blue
int redIntensity = 0;
int greenIntensity = 0;
int blueIntensity = 0;
int primeiraHistoria = 1;
int historiaEscolhida = 0;



int previousAnalogValue = 0;


int tempoCorridoCiano = 0;
int tempoLeituraCiano = 0;
String NomeHistoriaEscolhida = "";
int tempoLeituraTotal = 0;
int tempoLeituraHistoria = 0; 
int tempoCorridoHistoria = 0;
int escolhaHistoria = 0;

int tempoCorridoCianoAv = 0;
int tempoLeituraCianoAv = 0;

int tempoCorridoVermelhoAv = 0;
int tempoLeituraVermelhoAv = 0;

int tempoCorridoVerdeAv = 0;
int tempoLeituraVerdeAv = 0;

int tempoCorridoAzulEscuroAv = 0;
int tempoLeituraAzulEscuroAv = 0;

int tempoCorridoMagentaAv = 0;
int tempoLeituraMagentaAv = 0;

int tempoCorridoAmareloAv = 0;
int tempoLeituraAmareloAv = 0;

int tempoCorridoVermelho = 0;
int tempoLeituraVermelho = 0;

int tempoCorridoVerde = 0;
int tempoLeituraVerde = 0;

int tempoCorridoAmarelo = 0;
int tempoLeituraAmarelo = 0;

int tempoCorridoMagenta = 0;
int tempoLeituraMagenta = 0;

int tempoCorridoAzulEscuro = 0;
int tempoLeituraAzulEscuro = 0;


int avaliacao = 0;


//***************************************************************

#define POTPIN 34

#define debug  //uncomment to debug
//#define DeepSleepEnable  //uncomment to enable deep sleep function on real devices

// MQTT WiFi details
const char* ssid = "Wokwi-GUEST";
const char* password = "";

// MQTT broker details
const char* mqttServer = "broker.hivemq.com";
const int mqttPort = 1883;

// MQTT client details
#define MQTT_TOPIC "hum/10674299"
#define CLIENT_ID "client1"
#define CLIENT_CODE 1

// Wi-Fi client and MQTT client
WiFiClient espClient;
PubSubClient client(espClient);
int notConnectedCounter = 0;

//json file
StaticJsonDocument<200> doc;
StaticJsonDocument<100> message;

unsigned long startTime=0;  // Store the BE time
unsigned long OldTime=0;    // Store the old startTime and compare when 2 beacons are recived

//info from the PanC and sensors
int BE, CAP, CFP, ts, myTurn;
int ActivePart;

// variable we need if we want to use deep sleep mode
int uS_TO_mS_FACTOR = 1000; // Conversion factor for micro seconds to milli seconds

//status
bool IRecivedABeacon = false;

//arrays to store the data readed from the sensor
char strHumidity[10]; //string where i store the data to publish on screen

// Potentiometer input and related variables
int pot_in; 
int mappedvalue;
float humvalue;


//--------------------------------------------------------------------------------------------//

void historia(String NomeHistoriaEscolhida)
{

  tempoCorridoHistoria = millis();
  
  previousAnalogValue = analogValue;

  if (historiaEscolhida == 1)
  {
    if (NomeHistoriaEscolhida == "Amelie") 
    {
      printf("Amelie, uma menina curiosa, descobre o mundo microscópico dentro de uma gota de sangue com a ajuda de seu microscópio mágico. Ela aprende com Glóbulo, um glóbulo branco, sobre a importância dos exames de sangue, que revelam a saúde do corpo ao analisar glóbulos brancos, vermelhos e plaquetas, além de níveis de açúcar e vitaminas.");
      printf("\n");
      printf("Inspirada por sua aventura, Amelie se torna uma defensora dos exames de sangue, compartilhando com amigos e familiares como eles são essenciais para manter a saúde. Ela ensina que, embora invisíveis a olho nu, há um universo incrível trabalhando incansavelmente dentro de nós para nos manter saudáveis.");
      printf("\n");
      printf("Mude de cor quando terminar a história");
      printf("\n");
    }
    else if (NomeHistoriaEscolhida == "Leo") 
    {
        printf("Léo, o Leãozinho, estava se divertindo muito em sua casa quando de repente começou a sentir-se um pouco quente. Sua mãe, percebendo sua preocupação, trouxe o Termômetro Valente e explicou que ele era como um amigo que iria ajudar a descobrir se ele estava bem. Léo olhou para o termômetro com curiosidade, mas logo percebeu que não doía e que era uma maneira gentil de verificar sua temperatura.");
        printf("\n");
        printf("Com a ajuda da mãe e do Termômetro Valente, Léo aprendeu que era importante monitorar sua temperatura para se manter saudável. Ele viu que o Termômetro Valente não era assustador, mas sim um aliado que o ajudava a cuidar de si mesmo. No final, Léo ficou aliviado ao ver que estava tudo bem e aprendeu que o exame com o termômetro não era motivo para preocupação, mas sim uma forma de cuidar de sua saúde.");
        printf("\n");
        printf("Mude de cor quando terminar a história");
        printf("\n");
    }
    else if (NomeHistoriaEscolhida == "Carolina") 
    {
        printf("Carolina, uma garotinha curiosa e corajosa, estava se preparando para uma consulta médica quando se deparou com o Estetoscópio Falante. Sua mãe explicou que o estetoscópio era um amigo que iria ajudar o médico a escutar os sons do seu corpo e garantir que ela estivesse saudável. Intrigada, Carolina ouviu atentamente enquanto o Estetoscópio Falante sussurrava suavemente em seu ouvido, explicando que iria apenas ouvir seu coração e pulmões, sem causar dor ou desconforto.");
        printf("\n");
        printf("Com a ajuda do Estetoscópio Falante, Carolina aprendeu que o exame médico não era assustador, mas sim uma forma de garantir que ela estava saudável e forte. Ela descobriu que o estetoscópio era seu amigo e que o médico estava ali para cuidar dela. No final da consulta, Carolina sorriu aliviada, sabendo que o Estetoscópio Falante estava lá para ajudá-la a se sentir melhor e a continuar sua jornada de crescimento saudável.");
        printf("\n");
        printf("Mude de cor quando terminar a história");
        printf("\n");
    }
    else if (NomeHistoriaEscolhida == "Rafael") 
    {
        printf("Rafael, um garotinho curioso e destemido, se deparou com o Raio-X Mágico enquanto se preparava para uma consulta médica. Fascinado, ele descobriu que o Raio-X Mágico podia 'ver através' de seu corpo para ajudar o médico a encontrar o que estava causando seu desconforto. Com a explicação gentil do médico, Rafael aprendeu que o Raio-X Mágico não doía e era apenas uma maneira de ajudar a descobrir o que estava acontecendo dentro dele.");
        printf("\n");
        printf("Empolgado com essa nova descoberta, Rafael deixou de temer o exame de Raio-X, entendendo que era uma ferramenta importante para os médicos cuidarem de sua saúde. Ele viu o Raio-X Mágico como um aliado que o ajudaria a se sentir melhor. No final da consulta, Rafael sorriu aliviado, sabendo que o Raio-X Mágico estava lá para ajudá-lo em sua jornada para uma vida saudável e feliz.");
        printf("\n");
        printf("Mude de cor quando terminar a história");
        printf("\n");
    }
    else if (NomeHistoriaEscolhida == "Vitoria") 
    {
        printf("Em uma aventura médica emocionante, Vitória embarcou em suas incríveis viagens na 'Veia', acompanhada pela equipe médica. Com coragem e curiosidade, ela descobriu que a 'Veia' era como uma estrada dentro de seu corpo, por onde viajavam pequenos heróis chamados glóbulos vermelhos. Com a ajuda do médico, Vitória aprendeu que os exames de sangue eram como mapas mágicos que mostravam o caminho dos glóbulos vermelhos e outras células importantes, ajudando os médicos a entenderem como ela estava se sentindo.");
        printf("\n");
        printf("Encantada com essa jornada dentro de si mesma, Vitória percebeu que os exames de sangue eram uma maneira especial de cuidar de sua saúde. Ela viu os médicos como guias habilidosos em suas aventuras médicas e aprendeu que os exames não eram assustadores, mas sim uma ferramenta mágica que os ajudava a manter seu corpo saudável e forte. No final da jornada, Vitória sorriu confiante, sabendo que estava pronta para novas viagens na 'Veia' com sua equipe médica ao seu lado.");
        printf("\n");
        printf("Mude de cor quando terminar a história");
        printf("\n");
    }
    else if (NomeHistoriaEscolhida == "Enzo") 
    {
        printf("Em um dia ensolarado, Enzo embarcou em uma aventura pelo mundo dos germes, liderado por sua equipe médica. Com sua lupa mágica em mãos, Enzo descobriu que os germes eram pequenos vilões invisíveis que gostavam de se esconder em lugares inesperados. Com a orientação cuidadosa de seus médicos, Enzo aprendeu que os exames microscópicos eram como investigações secretas que ajudavam a encontrar esses vilões e proteger sua saúde.");
        printf("\n");
        printf("Empolgado com essa descoberta, Enzo deixou de temer os exames microscópicos, entendendo que eram uma maneira importante de manter sua saúde em dia. Ele viu seus médicos como verdadeiros heróis que o ajudavam a derrotar os germes invisíveis e garantir que ele pudesse continuar suas aventuras com segurança. No final do dia, Enzo sorriu confiante, sabendo que estava pronto para enfrentar qualquer desafio, com seus médicos ao seu lado.");
        printf("\n");
        printf("Mude de cor quando terminar a história");
        printf("\n");
    }

    while(previousAnalogValue == analogValue)
    {
      analogValue = analogRead(POTPIN);
    }

    CalcularTempo(NomeHistoriaEscolhida);
  }
}

void CalcularTempo(String NomeHistoriaEscolhida)
{
  tempoLeituraHistoria = millis();

  tempoLeituraTotal = (tempoLeituraHistoria - tempoCorridoHistoria) / 100;

  //printf("%d", tempoLeituraTotal);
  //printf("\n");

  std::string tempoLeituraTotalStr = std::to_string(tempoLeituraTotal);
  client.publish("hpQuadrinhos/tempoLeituraTotal", tempoLeituraTotalStr.c_str());

  AvaliacaoHistoria(NomeHistoriaEscolhida);
}

void AvaliacaoHistoria(String NomeHistoriaEscolhida)
{
    printf("\n");
    printf("***************************************************");
    printf("\n");
    printf("Avalie a história: ");
    printf("\n");
    printf("***************************************************");
    printf("\n");
    printf("Vermelho para: 1 estrela");
    printf("\n");
    printf("Azul escuro para: 2 estrelas");
    printf("\n");
    printf("Ciano para: 3 estrelas");
    printf("\n");
    printf("Magenta para: 4 estrelas");
    printf("\n");
    printf("Amarelo para: 5 estrelas");
    printf("\n");
    printf("Verde para: Pular avaliação");
    printf("\n");
    printf("***************************************************");
    printf("\n");

    currentMillis = millis();

    while (currentMillis - previousMillis <= 2000) {
      
        analogValue = analogRead(POTPIN);

        int interval = map(analogValue, 0, 4095, 0, 5);

        switch (interval) 
        {
          case 0:  // Intervalo 0
            // Define intensidades para a cor ciano
            redIntensity = 255;
            greenIntensity = 0;
            blueIntensity = 0;

            tempoCorridoCianoAv = millis();

            if (tempoCorridoCianoAv - tempoLeituraCianoAv >= 10000) 
            { 
              
                printf("★★★☆☆");
                printf("\n");
                printf("***************************************************");
                printf("\n");

                avaliacao = 3;

              tempoLeituraCianoAv = millis();
            }
          break;
          case 1:  // Intervalo 1
            // Define intensidades para a cor magenta
            redIntensity = 0;
            greenIntensity = 255;
            blueIntensity = 0;

            tempoCorridoMagentaAv = millis();

            if (tempoCorridoMagentaAv - tempoLeituraMagentaAv >= 10000) 
            { 
                printf("★★★★☆");
                printf("\n");
                printf("***************************************************");
                printf("\n");

                avaliacao = 4;

                tempoLeituraMagentaAv = millis();
            }

            break;
          case 2:  // Intervalo 2
            // Define intensidades para a cor amarelo
            redIntensity = 0;
            greenIntensity = 0;
            blueIntensity = 255;

            tempoCorridoAmareloAv = millis();

            if (tempoCorridoAmareloAv - tempoLeituraAmareloAv >= 10000) 
            { 
                printf("★★★★★");
                printf("\n");
                printf("***************************************************");
                printf("\n");

                avaliacao = 5;

                tempoLeituraAmareloAv = millis();
            }

            break;
          case 3:  // Intervalo 3
            // Define intensidades para a cor verde 
            redIntensity = 255;
            greenIntensity = 0;
            blueIntensity = 255;

            tempoCorridoVerdeAv = millis();

            if (tempoCorridoVerdeAv - tempoLeituraVerdeAv >= 10000) 
            { 
                printf("Obrigada pela leitura!");
                printf("\n");
                printf("***************************************************");
                printf("\n");

                tempoLeituraVerdeAv = millis();

                avaliacao = 6;
            }

            break;
          case 4:  // Intervalo 4
            // Define intensidades para a cor vermelha sangue
            redIntensity = 0;
            greenIntensity = 255;
            blueIntensity = 255;

            tempoCorridoVermelhoAv = millis();

            if (tempoCorridoVermelhoAv - tempoLeituraVermelhoAv >= 10000) 
            { 
                printf("★☆☆☆☆");
                printf("\n");
                printf("***************************************************");
                printf("\n");

                avaliacao = 1;

                tempoLeituraVermelhoAv = millis();
            }

            break;
          case 5:  // Intervalo 4
            // Define intensidades para a cor azul escuro
            redIntensity = 255;
            greenIntensity = 255;
            blueIntensity = 0;

            tempoCorridoAzulEscuroAv = millis();

            if (tempoCorridoAzulEscuroAv - tempoLeituraAzulEscuroAv >= 10000) 
            { 
                printf("★★☆☆☆");
                printf("\n");
                printf("***************************************************");
                printf("\n");

                avaliacao = 2;
                
                tempoLeituraAzulEscuroAv = millis();
            }

            break;





      // atualiza o valor de previousMillis
      previousMillis = currentMillis;
    }












  
  
  }

  String AvaliacaoStr = String(avaliacao);

  String topico = "hpQuadrinhos/" + NomeHistoriaEscolhida + "/Avaliacao";

  const char* topico_cstr = topico.c_str();
  const char* avaliacao_cstr = AvaliacaoStr.c_str();

  client.publish(topico_cstr, avaliacao_cstr);


  //*****************************************

  delay(5000);


primeiraHistoria = 1;
historiaEscolhida = 0;

previousAnalogValue = 0;

tempoCorridoCiano = 0;
tempoLeituraCiano = 0;
NomeHistoriaEscolhida = "";
tempoLeituraTotal = 0;
tempoLeituraHistoria = 0; 
tempoCorridoHistoria = 0;
escolhaHistoria = 0;

tempoCorridoCianoAv = 0;
tempoLeituraCianoAv = 0;

tempoCorridoVermelhoAv = 0;
tempoLeituraVermelhoAv = 0;

tempoCorridoVerdeAv = 0;
tempoLeituraVerdeAv = 0;

tempoCorridoAzulEscuroAv = 0;
tempoLeituraAzulEscuroAv = 0;

tempoCorridoMagentaAv = 0;
tempoLeituraMagentaAv = 0;

tempoCorridoAmareloAv = 0;
tempoLeituraAmareloAv = 0;

tempoCorridoVermelho = 0;
tempoLeituraVermelho = 0;

tempoCorridoVerde = 0;
tempoLeituraVerde = 0;

tempoCorridoAmarelo = 0;
tempoLeituraAmarelo = 0;

tempoCorridoMagenta = 0;
tempoLeituraMagenta = 0;

tempoCorridoAzulEscuro = 0;
tempoLeituraAzulEscuro = 0;

avaliacao = 0;

}


//***************************************************************


void setup(){

  //Set POTPIN as INPUT
  pinMode(POTPIN, INPUT);

  Serial.begin(115200);
  wificonnect();    //connect to wifi

  //Connect to MQTT broker and set callback
  client.setServer(mqttServer, mqttPort);
  client.setCallback(callback);

  //client.setServer(mqttServer, mqttPort);
  client.setCallback(callback);

  //First connection to the MQTT broker
  while (!client.connected()) {
    if (client.connect(CLIENT_ID)) {
      Serial.println("Connected to MQTT broker");
      client.subscribe(MQTT_TOPIC);
    } else {
      Serial.print("Failed to connect to MQTT broker, rc=");
      Serial.print(client.state());
      Serial.println("Retrying in 2 sec...");
      delay(2000);
    }
  }

  //*****************************************************
    pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  
  // Initialize LED PWM channels
  ledcSetup(PWM_CHANNEL, PWM_FREQUENCY, PWM_RESOLUTION);  // PWM channel for red LED
  ledcSetup(PWM_CHANNEL1, PWM_FREQUENCY, PWM_RESOLUTION);  // PWM channel for green LED
  ledcSetup(PWM_CHANNEL2, PWM_FREQUENCY, PWM_RESOLUTION);  // PWM channel for blue LED
  
  // Attach PWM channels to the respective LED pins
      ledcAttachPin(redPin, PWM_CHANNEL);
      ledcAttachPin(greenPin, PWM_CHANNEL1);
      ledcAttachPin(bluePin, PWM_CHANNEL2);

      ledcWrite(PWM_CHANNEL, 255);
      ledcWrite(PWM_CHANNEL1, 255);
      ledcWrite(PWM_CHANNEL2, 255);

  //*****************************************************
  
}


void wificonnect() {
  delay(400);     // a bit of dealy before to start

  // Setup WiFi properties
  WiFi.mode(WIFI_STA);        //setting the wifi in station mode
  WiFi.begin(ssid, password); //speciyng the SSID and password for the wifi

  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(200);        //we keep waiting 0.2 seconds more for a connection until we get it
    notConnectedCounter++;
    if (notConnectedCounter > 10) { // Reset, if not connected after 10 tries
      Serial.println("Resetting due to Wifi not connecting...");
      ESP.restart();
    }
  }
  Serial.println("Connected to WiFi");
}


// Connect-reconnecting to the broker when a disconnection happen
void reconnect() {
  while (!client.connected()) {
    Serial.println("Attempting MQTT connection...");
    if (client.connect(CLIENT_ID)) {
      Serial.println("Connected to MQTT broker");
      Serial.println("------------------------------");
      client.subscribe(MQTT_TOPIC);
    } else {
      Serial.print("Failed to connect to MQTT broker, rc=");
      Serial.print(client.state());
      Serial.println(" Retrying in 0.5 seconds...");
      delay(500);
    }
  }
}


//maintaininig the MQTT connection while waiting for the beacon
void loop() {
  //reconnect if not connected to the MQTT broker
  if (!client.connected()) {
    reconnect();
  }
  delay(200);
  pot_in = analogRead(POTPIN);             // Input pin is 
  mappedvalue = map(pot_in, 0, 4095, 0, 100);
  humvalue = (float)mappedvalue*1.00;
  client.loop();

  //************************************************

    if(historiaEscolhida == 1){
          
    historia(NomeHistoriaEscolhida);  
    historiaEscolhida = 0; 
        
  }

  if (primeiraHistoria == 1)
  {

    printf("\n");
    printf("***************************************************");
    printf("\n");
    printf("Escolha 1 história deixando 3 segundos em uma cor: ");
    printf("\n");
    printf("***************************************************");
    printf("\n");
    printf("Ciano para: A Aventura de Amelie no Mundo dos Microscópios");
    printf("\n");
    printf("Magenta para: O Raio-X Mágico de Rafael");
    printf("\n");
    printf("Amarelo para: Carolina e o Estetoscópio Falante");
    printf("\n");
    printf("Verde para: As Incríveis Viagens de Vitória na Veia");
    printf("\n");
    printf("Vermelho para: O Dia em que Enzo Encontrou os Germes");
    printf("\n");
    printf("Azul escuro para: Léo, o Leãozinho, e o Termômetro Valente");
    printf("\n");
    printf("***************************************************");
    printf("\n");

    primeiraHistoria = 0;
    escolhaHistoria = 1;
  }

  analogValue = analogRead(POTPIN);

  int interval = map(analogValue, 0, 4095, 0, 5);

  switch (interval) 
  {
    case 0:  // Intervalo 0
      // Define intensidades para a cor ciano
      redIntensity = 255;
      greenIntensity = 0;
      blueIntensity = 0;

      tempoCorridoCiano = millis();

      if (tempoCorridoCiano - tempoLeituraCiano >= 10000) 
      { 
        
        if(primeiraHistoria == 0 && historiaEscolhida == 0 && escolhaHistoria == 1)
        {

          printf("Você escolheu: A Aventura de Amelie no Mundo dos Microscópios");
          printf("\n");
          printf("***************************************************");
          printf("\n");

          primeiraHistoria = 0;
          historiaEscolhida = 1;
          escolhaHistoria = 0;

          NomeHistoriaEscolhida = "Amelie";
          client.publish("hpQuadrinhos/historia", NomeHistoriaEscolhida.c_str());       

        tempoLeituraCiano = millis();
      }
    }
    break;
    case 1:  // Intervalo 1
      // Define intensidades para a cor magenta
      redIntensity = 0;
      greenIntensity = 255;
      blueIntensity = 0;

      tempoCorridoMagenta = millis();

      if (tempoCorridoMagenta - tempoLeituraMagenta >= 10000) 
      { 
          if(primeiraHistoria == 0 && historiaEscolhida == 0 && escolhaHistoria == 1)
          {
              printf("Você escolheu: O Raio-X Mágico de Rafael");
              printf("\n");
              printf("***************************************************");
              printf("\n");

              primeiraHistoria = 0;
              historiaEscolhida = 1;
              escolhaHistoria = 0;

              NomeHistoriaEscolhida = "Rafael";
              client.publish("hpQuadrinhos/historia", NomeHistoriaEscolhida.c_str());       

              tempoLeituraMagenta = millis();
          }
      }
      break;
    case 2:  // Intervalo 2
      // Define intensidades para a cor amarelo
      redIntensity = 0;
      greenIntensity = 0;
      blueIntensity = 255;

      tempoCorridoAmarelo = millis();

      if (tempoCorridoAmarelo - tempoLeituraAmarelo >= 10000) 
      { 
          if(primeiraHistoria == 0 && historiaEscolhida == 0 && escolhaHistoria == 1)
          {
              printf("Você escolheu: Carolina e o Estetoscópio Falante");
              printf("\n");
              printf("***************************************************");
              printf("\n");

              primeiraHistoria = 0;
              historiaEscolhida = 1;
              escolhaHistoria = 0;

              NomeHistoriaEscolhida = "Carolina";
              client.publish("hpQuadrinhos/historia", NomeHistoriaEscolhida.c_str());       

              tempoLeituraAmarelo = millis();
          }
      }
      break;
    case 3:  // Intervalo 3
      // Define intensidades para a cor verde 
      redIntensity = 255;
      greenIntensity = 0;
      blueIntensity = 255;

      tempoCorridoVerde = millis();

      if (tempoCorridoVerde - tempoLeituraVerde >= 10000) 
      { 
          if(primeiraHistoria == 0 && historiaEscolhida == 0 && escolhaHistoria == 1)
          {
              printf("Você escolheu: As Incríveis Viagens de Vitória na Veia");
              printf("\n");
              printf("***************************************************");
              printf("\n");

              primeiraHistoria = 0;
              historiaEscolhida = 1;
              escolhaHistoria = 0;

              NomeHistoriaEscolhida = "Vitoria";
              client.publish("hpQuadrinhos/historia", NomeHistoriaEscolhida.c_str());       

              tempoLeituraVerde = millis();
          }
      }

      break;
    case 4:  // Intervalo 4
      // Define intensidades para a cor vermelha sangue
      redIntensity = 0;
      greenIntensity = 255;
      blueIntensity = 255;

      tempoCorridoVermelho = millis();

      if (tempoCorridoVermelho - tempoLeituraVermelho >= 10000) 
      { 
          if(primeiraHistoria == 0 && historiaEscolhida == 0 && escolhaHistoria == 1)
          {
              printf("Você escolheu: O Dia em que Enzo Encontrou os Germes");
              printf("\n");
              printf("***************************************************");
              printf("\n");

              primeiraHistoria = 0;
              historiaEscolhida = 1;
              escolhaHistoria = 0;

              NomeHistoriaEscolhida = "Enzo";
              client.publish("hpQuadrinhos/historia", NomeHistoriaEscolhida.c_str());       

              tempoLeituraVermelho = millis();
          }
      }
      break;
    case 5:  // Intervalo 4
      // Define intensidades para a cor azul escuro
      redIntensity = 255;
      greenIntensity = 255;
      blueIntensity = 0;

      tempoCorridoAzulEscuro = millis();

      if (tempoCorridoAzulEscuro - tempoLeituraAzulEscuro >= 10000) 
      { 
          if(primeiraHistoria == 0 && historiaEscolhida == 0 && escolhaHistoria == 1)
          {
              printf("Você escolheu: Léo, o Leãozinho, e o Termômetro Valente");
              printf("\n");
              printf("***************************************************");
              printf("\n");

              primeiraHistoria = 0;
              historiaEscolhida = 1;
              escolhaHistoria = 0;

              NomeHistoriaEscolhida = "Leo";
              client.publish("hpQuadrinhos/historia", NomeHistoriaEscolhida.c_str());       

              tempoLeituraAzulEscuro = millis();
          }
      }

      break;

  }

  // Atualizar os LEDs com as novas intensidades
  ledcWrite(PWM_CHANNEL, redIntensity);
  ledcWrite(PWM_CHANNEL1, greenIntensity);
  ledcWrite(PWM_CHANNEL2, blueIntensity);



  //*******************************************************
}


//--------------------------------------------------------------------------------------------//

// Handle incoming MQTT messages
void callback(char * topic, byte * message, unsigned int length){
  DeserializationError e = deserializeJson(doc, message);
 if (((int)doc["BE"]) != 0) { // recieved the beacon enable
    #ifdef debug 
      Serial.print("Beacon number: "); Serial.println((int)doc["count"]);
      Serial.print("Delta time between beacons: "); Serial.println((millis() - startTime));
    #endif
    OldTime = startTime;      // save the old startTime;
    startTime = millis();     // update the startTime
    
    IRecivedABeacon = true;
    BE = (int)doc["BE"];        // reading the BeaconEnable (== time_slot)
    ts = (int)doc["ts"];        // reading the time slot
    CAP = (int)doc["CAP"];      // reading the CAP
    CFP = (int)doc["CFP"];      // reading the CFP

    String s="c" + String(CLIENT_CODE);   // creating the string to identify my turn 
    myTurn = (int)doc[s];       // reading my slot index to trasmitt
    
    ActivePart=(ts+CAP+CFP);    // ActivePart = BE+CAP+CFP

    #ifdef debug
      if (!myTurn) {            //Check if we are registered
        Serial.println("Not registered, No CFP slot ");
      } else {
        Serial.print("CFP assigned slot is: "); Serial.println(myTurn);     //check if my index is right
      }
    #endif

    workTime(); // Lets do the work 
  }
  
}


//things to do during the beacon interval
void workTime(){

  //Beacon Enable
  if (((millis() - startTime) < ts)) {  // wait for the end of the BE slot
    delay(ts - (millis() - startTime)); // go after the BE
  }

  //CAP slot, perform registration
  if (myTurn == 0 && ((millis() - startTime) < ts+CAP) ) {    //if we are not registered, we register
    registration();
  }

  //CFP part, if we have an assigned slot, do work
  else {    
    //Exit from the CAP slot
    if ((millis() - startTime) < (ts + CAP + (myTurn-1)*ts)) {  // BE+CAP+ my turn *time slot
      delay((ts + CAP + (myTurn-1)*ts) - (millis() - startTime));  //we delay to get in our slot
    } 
      
    //Check to be in our assigned slot
    if( (millis() - startTime) < ((ts + CAP + (myTurn-1)*ts) + ts)){  // BE+CAP+ my turn *time slot+ 1 next slot, before which i must trasmit all my data
      sensor_read();
    }
  }

  //if not in CFP (CAP), then jump after the ActivePart
  if((millis()-startTime)<(ActivePart)){
    delay((ActivePart)-(millis()-startTime));   // go straight to the end of the active part
  }
}


// Perform registration during the CAP part, we assume that the server is performing by itself the CSMA/CA, so we omitt it
void registration () {
  message["tipo"] = 0;    // Registration code
  message["val"] = CLIENT_CODE;  // Client id value

  char msgout[100];
  serializeJson(message, msgout);      // Create the message
  client.publish(MQTT_TOPIC, msgout);  // Publish on the topic that i want to register and my code
  #ifdef debug
    Serial.println("(CAP) Sent registration message");
    Serial.println("------------------------------");
  #endif
}


// Reading and publishing the Data and the destination actuator
void sensor_read() {
  // inputs are taken before, in loop()
  Serial.print("Potentiomet value: ");Serial.println(pot_in);
  Serial.print("Humvalue is: "); Serial.println(humvalue); 

  message["tipo"] = 1;              // "tipo" and not "type" otherwise there are errors ("pippo" can be a good choice too)
  message["val"] = humvalue;
  message["sender"] = CLIENT_CODE;
  //random actuator as destination
  int rand_act=random(1,3);
  message["actuator"]=rand_act;
  Serial.print("This message is for actuator: ");Serial.println(rand_act);


  char msgout[100];
  sprintf(strHumidity, "%.2f", humvalue);  //float value with 2 digits after the comma
  #ifdef debug
    Serial.println("Humidity: " + String(strHumidity, 2) + "%");
  #endif

  #ifdef debug
    Serial.print("Sent humidity message at:"); Serial.print(millis()-startTime); Serial.println(" millis since BE");
    Serial.println("------------------------------");
  #endif
  serializeJson(message, msgout);     // create the message
  client.publish(MQTT_TOPIC, msgout); // publish the humidity message on the topic
}
