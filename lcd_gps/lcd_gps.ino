/*
Programme qui est utiliser pour simuler le module GPS avec une carte Arduino sur le logiciel Proteus ISIS.

Ecrit par Areour mohamed Cherif
Date : 12/03/2016
E-mail : openhardwaredz@gmail.com

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.
This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.*/

#include <TinyGPS.h>
#include <LiquidCrystal.h>
 
// initialize the LiquidCrystal library with the numbers of the interface pins
// initialiser la bibliothèque LiquidCrystal avec les numéros des pin de l'Arduino
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
 
// Create an instance of the TinyGPS object
// Création d'une instance pour l'objet TinyGPS
TinyGPS gps;
 
// This is where you declare prototypes for the functions that will be 
// using the TinyGPS library.
// Ceci est l'endroit où nous déclarons le prototypes pour la fonction 
// qui utilisera la bibliothéque TinyGPS et controlera l'affichage 
void getgps(TinyGPS &gps);
 
void setup()
{
  Serial.begin(9600);
  lcd.begin(20, 4);
  lcd.clear();
  lcd.setCursor(2,1);
  lcd.print("* OPEN HARDWARE *");
  lcd.setCursor(4,2);
  lcd.print("** ALGERIE **");
  delay(5000);
  lcd.clear();
  lcd.setCursor(2,1);
  lcd.print("En attente ...");
}
 
// The getgps function will get and print the values we want
// La fonction get gps va obtenir et imprimer les valeurs que nous voulons
void getgps(TinyGPS &gps)
{
  // Define the variables that will be used
  // Définir les variables qui seront utilisées
  float latitude, longitude;

  // call the function that retrieves the latitude and longitude
  // appelle de la fonction qui récupère la latitude et la longitude
  gps.f_get_position(&latitude, &longitude);
  
  // clear LCD
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Lat: "); 
  lcd.print(latitude,5); 
  lcd.setCursor(0,1); 
  lcd.print("Long: "); 
  lcd.print(longitude,5);
  
  // the same operation for the date and time
  // la même opération pour la date et le temps
  int annee;
  byte mois, jour, heure, minute, seconde, millieme;
  gps.crack_datetime(&annee,&mois,&jour,&heure,&minute,&seconde,&millieme);
  
  lcd.setCursor(1,2);
  lcd.print(heure,DEC);
  lcd.print(":");
  if (minute<10)
  {
    lcd.print("0");
    lcd.print(minute, DEC);
  } 
  else if (minute>=10)
  {
    lcd.print(minute, DEC);
  }
  lcd.print(":");
  if (seconde<10)
  {
    lcd.print("0");
    lcd.print(seconde,DEC);
  } 
  else if (seconde>=10)
  {
    lcd.print(seconde,DEC);
  }
  lcd.print(" ");
  lcd.print(jour);
  lcd.print("/");
  lcd.print(mois,DEC);
  lcd.print("/");
  lcd.print(annee,DEC);
  lcd.setCursor(0,3);
  lcd.print(gps.f_altitude()); // reading and altitude display
  lcd.print("m ");             // lecture et affichage de l'altitude
  
  lcd.print(gps.f_speed_kmph()); // reading and speed display
  lcd.print("km/h");             // lecture et affichage de la vitesse 
 
}
 
void loop()
{
  byte a;
  if ( Serial.available() > 0 ) 
  {
    a = Serial.read(); 
    if(gps.encode(a)) 
    {
      getgps(gps); // grab the data and display it on the LCD
                   // saisir les données et les afficher sur l'écran LCD
    }
  }
}
