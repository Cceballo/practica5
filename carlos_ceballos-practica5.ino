/*
   Fundacion KinaL
   Centro educativo tecnico LaboraL KinaL
   Quinto perito
   Quinto eLectronica
   Codigo Tecnico: EB5AM / EB5AV
   Curso: TaLLer de eLectronica digitaL y reparacion de computadoras I
   Proyecto: Prender, apagar un led por el celular
   aLumno:carlos ceballos
   Fecha: 14/07/2023
*/
#include <Ticker.h>
#include <LedControl.h>   //libreria que me permite usar el controlador led max7219
#define dataPin0   12   //pin 12 conectado al pin de datos del max7219.
#define dataClock0 11   //pin 11 conectado al pin de clock del max7219.
#define dataLoad0  10   //pin 10 conectado al pin de carga del max7219.
#define tiempo 1000
LedControl matrixcc = LedControl(dataPin0, dataClock0, dataLoad0, 1);
byte FUEGO_0[8] = { //animacion de fuego
  B0000000,
  B00011100,
  B00110110,
  B00110110,
  B00110110,
  B00100010,
  B00010100,
  B00001000
};

byte  FUEGO_1[8] = { // animacion de fuego
   B0000000,
  B00011100,
  B00111110,
  B00111110,
  B00111110,
  B00111110,
  B00011100,
  B00001000
};

byte  HIELO_0[8] = { // estas animando el hielo 
  B00011000,
  B00111100,
  B01111110,
  B11100111,
  B01100110,
  B00111100,
  B00011000,
  B00000000
};
byte  HIELO_cc[8] = {
  B10011001,
  B01011010,
  B00111100,
  B11100111,
  B11100111,
  B00111100,
  B01011010,
  B10011001
};



int i;
int MQ, conver;
unsigned long update_delay = 850;

void medicion(void);
Ticker medicionT(medicion, 2000);
void setup() {
  Serial.begin(9600);
  matrizcc.shutdown(0, false); //Activo el max7219 para poder mostrar los digitos.
  matrizcc.setIntensity(0, 18); //Brillo a la mitad del luz
  matrizcc.clearDisplay(0);    //limpiar display
  Serial.println("Medidor de fuego y matriz led");
  medicionT.start();
}

void loop() {
  medicionT.update();
  if (conver < 40) { //conversion

    Serial.println("Sin presencia de fuego"); // declara precensia de fuego
    //nieve
    for (int i = 0; i < 8; i++)
    {
      matrizcc.setRow(0, i, HIELO_cc[i]);

    }
    delay(500);
    matrizcc.clearDisplay(0);
  }
  if (conver > 40 ) {
    Serial.println("Fuego detectado");
    //fuego
    for (int i = 0; i < 8; i++) // mayor 8
    {
      matrizcc.setRow(0, i, FUEGO_0[i]); // sobre animacion fuego prinera
    }
    delay(1000);
    for (int i = 0; i < 8; i++)
    {
      matrizcc.setRow(0, i, FUEGO_1[i]); // sobre animacion fuego 1
    }

    delay(1000);
    for (int i = 0; i < 8; i++)
    {
      matrizcc.setRow(0, i, FUEGO_0[i]); // sobre animacion guego 3
    }


    delay(1000);
  }

}

void medicion(void) {

  MQ = analogRead(A0);
  conver = map(MQ, 0, 1023, 0, 100);
  Serial.println(conver);
}
