
//Incluimos librerias necesarias
#include <SPI.h>
#include <SD.h>

File myFile;
char eleccion[20];
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);  //iniciamos comunicacion serial
  SPI.setModule(0);  //iniciamos comunicacion SPI en el modulo 0
  Serial.print("Initializing SD card...");
  // On the Ethernet Shield, CS is pin 4. It's set as an output by default.
  // Note that even if it's not used as the CS pin, the hardware SS pin
  // (10 on most Arduino boards, 53 on the Mega) must be left as an output
  // or the SD library functions will not work.
  pinMode(12, OUTPUT);  //Colocamos el CS del modulo SPI-0 como Output

//Se verifica que se haya iniciado correctamente la SD
  if (!SD.begin(12)) {
    Serial.println("initialization failed!");
    return;
  }
  Serial.println("initialization done.");

  //Se imprimen los nombres de los archivos dentro de la SD
 /* myFile = SD.open("/");
  printDirectory(myFile, 0);*/

}

void loop() {
  // put your main code here, to run repeatedly: 
  Serial.println("De los archivos a continuacion selecciona el que desees abrir ");
  Serial.println("Coloca unicamente el numero correspondiente al orden en el que se encuentran los archivos");
  myFile = SD.open("/");
  printDirectory(myFile, 0);
  while(Serial.available()<1);
  Serial.readBytes(eleccion,sizeof eleccion);
  
  //ReadFile("MARIO.txt");
}

void printDirectory(File dir, int numTabs) {
   while(true) {
     
     File entry =  dir.openNextFile();
     if (! entry) {
       // no more files
       break;
     }
     for (uint8_t i=0; i<numTabs; i++) {
       Serial.print('\t');
     }
     Serial.print(entry.name());
     if (entry.isDirectory()) {
       Serial.println("/");
       printDirectory(entry, numTabs+1);
     } else {
       // files have sizes, directories do not
       Serial.print("\t\t");
       Serial.println(entry.size(), DEC);
     }
     entry.close();
   }
}

void ReadFile(char name[]){
  myFile = SD.open(name);
  if (myFile) {
    Serial.println(name);

    // read from the file until there's nothing else in it:
    while (myFile.available()) {
      Serial.write(myFile.read());
    }
    // close the file:
    myFile.close();
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening Hola.txt");
  }
  }
