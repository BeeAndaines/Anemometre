
/*
 * Si temps < 10s 
 * alors temps augmente de l'interval
 * si tension < 100
 * alors compteur ++
 * else 
 * enregistrer compteur et la date 
 * compteur =0
 * temps = 0
 * reset millis() ?
 * fin du else 
 * 
 */
// définition des constantes entières
int tension ; //pour afficher la valeur du reed
int compteur ; //pour compter les activations du reed
int comptetour ; //pour calculer la vitesse en tour/heure
float frequence ;
// définition des parametre pour compter le temps
unsigned long previousMillis = 0;        
const long interval = 10000;  //pour afficher la vitesse toutes les 10s
//définition d'un compteur à incrémenter tant que le reed est déclenché
int countreedferme =0;   

/**
 * nous utilisons Tiny RTC module horloge
  * DS1307 pour bus I2C
 * avec batterie au lithium CR1225
 * Le port I2C de l'Arduino est situé
 * sur les pin A4 et A5
 *
 * Analog pin A5 <-> SCL
 * Analog pin A4 <-> SDA
 */
// nous utilisons la librairie RTClib
//pour lire les données de l'horloge
//cf: https://github.com/adafruit/RTClib
 #include <Wire.h>
#include "RTClib.h"

RTC_DS1307 RTC;

/**
 * Écriture sur une carte SD
 *
 * SD card reliée au bus SPI :
 * MOSI       - pin 11
 * MISO       - pin 12
 * CLK ou SCK - pin 13
 * CS         - pin 4
 *
 * SPI pour Serial Peripheral Interface
 *
 * created  24 Nov 2010
 * modified 9 Apr 2012
 * by Tom Igoe
 * cf: https://www.arduino.cc/en/Tutorial/Datalogger
 */
#include <SPI.h>
#include <SD.h>

// Arduino Uno pin 4
// cf: https://www.arduino.cc/en/Reference/SPI
const int chipSelect = 4;



// boucle de démarrage
void setup() {
// définition de la liaison serie USB avec le PC
  Serial.begin(9600);

// vérification de l'affichage par ecriture d'un texte
  Serial.println("Hello world !");
Serial.print("test reed branche avec resistance en A0 valeur:");
Serial.println(tension);

 Wire.begin();
      RTC.begin();
      if (! RTC.isrunning())
      {
        Serial.println("RTC is NOT running!");
      }
      // Décommenter cette ligne pour mettre à jour l'heure dans RTC
       RTC.adjust(DateTime(__DATE__, __TIME__));


//zone SD
  while (!Serial)
    {
    ; // wait for serial port to connect. Needed for native USB port only
 
    }
  
  Serial.println("Initialisation de la carte SD ...");
 
  // on verifie que la carte est présente et peut être initialisée
  if (!SD.begin(chipSelect))
    {
    Serial.println("Carte Sd inaccesible ou absente");
    
    // ne fait rien d'autre
    return;
}
}

// lancement de la boucle qui se repetera 9600 fois par seconde
void loop() 
{

  
// définition d'un temps  pour lire la valeur durant 10s
unsigned long currentMillis = millis();

   tension= analogRead (A0) ;
   //quand le reed n'est pas activé, il est en valeur haute 1023
   //quand le reeed detecte l aimant, la tension diminue sous le seuil
   
  if (currentMillis - previousMillis <= interval)
  {
//Serial.print("premier if  ");
 //Serial.println(tension);
        if ( tension <500 ) 
        {
          countreedferme ++;
          //Serial.println(tension);        
         // Serial.print("countreedferme vaut : ");
          //    Serial.println (countreedferme );
          }
         if (tension >500)
         {
          if (countreedferme>0)
          { 
          compteur ++ ; 
          Serial.print("compteur vaut : ");
          Serial.println (compteur );
          countreedferme=0;
          }
        }
 }
        else 
        {
          // ecrire compteur dans datastring avec l'heure date ...
            DateTime now = RTC.now(); 
            Serial.println (compteur );
            comptetour=compteur *360;
            Serial.print("vitesse en tour/h : ");
              Serial.println (comptetour);
           // on enregistre sur SD année; mois; jour; heure; minute; seconde; T1; T2
//Zone SD
  // nous créons une chaîne de caractères pour
  // concaténer les données à écrire :
  String dataString = "";

  // nous convertissons la valeur 
  // avec l'objet String() afin de pouvoir 
  // l'écrire sur la carte
  dataString += String(now.year(), DEC);
  dataString += ";";
  dataString += String(now.month(), DEC);
  dataString += ";";
  dataString += String(now.day(), DEC);
  dataString += ";";
  dataString += String(now.hour(), DEC);
  dataString += ";";
  dataString += String(now.minute(), DEC);
  dataString += ";";
  dataString += String(now.second(), DEC);
  dataString += ";";
  dataString += String(compteur);
  dataString +=  ";";
  dataString += String(comptetour);
  dataString += ";";
  
  /**
   * nous ouvrons le fichier
   * Nb: un seul fichier peut être ouvert à la fois
   * le fichier se nomme : journal.csv
   */
  File dataFile = SD.open("journal.csv", FILE_WRITE);

  // si le fichier est disponible, nous écrivons dedans :
  if (dataFile) {
    Serial.print("journal ouvert");
    dataFile.println(dataString);
    dataFile.close();

    // nous affichons aussi notre chaîne sur le port série :
    Serial.println(dataString);
  }
 
  // Si le fichier n'est pas ouvert nous affichons
  // un message d'erreur
  else {
    Serial.println("nous ne pouvons ouvrir journal.csv");
            }
  
            compteur=0 ; 
          previousMillis = currentMillis;

         }
  
  
}
 
  
  
                                                  
 
