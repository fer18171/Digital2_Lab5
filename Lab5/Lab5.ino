


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

  

}

void loop() {
  //Se imprimen las instrucciones del menú 
  Serial.println("De los archivos a continuacion selecciona el que desees abrir ");
  Serial.println("Coloca unicamente el numero correspondiente al orden en el que se encuentran los archivos");
  //Se imprimen los archivos existentes adentro de la SD card
  myFile = SD.open("/");
  printDirectory(myFile, 0);
  while(Serial.available()<1); //Espero a que el usuario me envie el dato por el puerto serial del archivo que desea desplegar de la SD
  Serial.readBytes(eleccion,sizeof eleccion); //Luego de recibir el dato del usuario, lo leo hasta completarlo
  // A continuacion realizo el menu que que se basa en la eleccion del usuario para desplegar cada archivo
  if (eleccion[0] == '1'){
      ReadFile("HEART.txt"); //Se despliega opcion 1 que corresponde al archivo de HEART
  } else if (eleccion[0] == '2'){
      ReadFile("MARIO.txt"); //Se despliega opcion 2 que corresponde al archivo de MARIO
    }else if (eleccion[0] == '3'){
      ReadFile("KIRBY.txt"); //Se despliega opcion 3 que corresponde al archivo de KIRBY
    }
    else{ // Si el usuario no coloca alguna de las opciones disponibles, se despliega este mensaje
      Serial.println("No escribiste un comando valido, escribe unicamente un numeri entre 1 y 3");
    }
  //ReadFile("MARIO.txt");
}

//Funcion utilizada para desplegar los archivos dentro de la SD
void printDirectory(File dir, int numTabs) {
   dir.rewindDirectory(); //Esto es para colocar el puntero que leera los archivos de la SD al principio
   while(true) {
     
     File entry =  dir.openNextFile();  //Se abre el siguiente archivo del puntero
     if (! entry) {
       // no more files
       break;
     }
     for (uint8_t i=0; i<numTabs; i++) {
       Serial.print('\t');
     }
     if (entry.isDirectory()) {  //Esto se utiliza cuando lo que se esta leyendo no es un archivo (usualemente es una carpeta)
       /*Serial.println("/");  //Entonces se lee lo que esta dentro de la carpeta, en este caso lo comente por cuestiones del lab
       printDirectory(entry, numTabs+1);*/
     } else {
       // files have sizes, directories do not
       Serial.print(entry.name());  //Se imprime el nombre del archivo
       Serial.print("\t\t");  //Se realizan 2 tabulaciones, es decir, un espacio largo
       Serial.println(entry.size(), DEC); //Se coloca el tamaño del archivo en decimal
     }
    // entry.close();
   }
}

void ReadFile(char name[]){
  myFile = SD.open(name); //Se abre el arhivo dado en el argumento
  if (myFile) { //Si se logro abrir de manera correcta
    Serial.println(name); //se imprime el nombre del archivo

    // read from the file until there's nothing else in it:
    while (myFile.available()) { //Se va leyendo cada caracter del archivo hasta que ya se hayan leido todos
      Serial.write(myFile.read());
    }
    // close the file:
    myFile.close(); //Se cierra el archivo
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening Hola.txt");
  }
  }
