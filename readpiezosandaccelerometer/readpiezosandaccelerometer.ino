#include <Wire.h>
#include <ADXL345.h>  // ADXL345 Accelerometer Library

ADXL345 acc;

const int NUM_OF_KEYS = 7;
const int THRESHOLD = 50;
const int analogInputPins[NUM_OF_KEYS] = {A0, A1, A2, A3, A4, A5, A6};

int ax,ay,az;  
int rawX, rawY, rawZ;
float X, Y, Z;
float rolldeg, pitchdeg;
float aoffsetX, aoffsetY, aoffsetZ;

byte arrPiezoVal[2*NUM_OF_KEYS+1];
byte arrAccel[1];
int piezoVal[NUM_OF_KEYS] = {0};
int bufferlength = 0;
char stringBuffer [50];
unsigned long time;

void setup() {
  Serial.print("setup");
  Serial.println();
  Serial.begin(38400);
  acc.powerOn();
  for (int i = 0; i <= 200; i++) {
    acc.readAccel(&ax, &ay, &az);
    if (i == 0) {
      aoffsetX = ax;
      aoffsetY = ay;
      aoffsetZ = az;
    }
    if (i > 1) {
      aoffsetX = (ax + aoffsetX) / 2;
      aoffsetY = (ay + aoffsetY) / 2;
      aoffsetZ = (az + aoffsetZ) / 2;
    }
    Serial.print(i);
    Serial.println();
    delay(10);
  }

} 

void loop() {
arrPiezoVal[0]= 0xc0;
int index = 1;
  /* Piezos values */
 for (int count; count < NUM_OF_KEYS; count++)
    {
        piezoVal[count] = analogRead(analogInputPins[count]);
        arrPiezoVal[index++] = piezoVal[count] & 0x007f;
        arrPiezoVal[index++] = piezoVal[count] >> 7;          
    }

    Serial.write(arrPiezoVal, sizeof(arrPiezoVal));

    // Accelerometer information
    time = millis();
    acc.readAccel(&ax, &ay, &az); //read the accelerometer values and store them in variables  x,y,z
    rawX = ax - aoffsetX;
    rawY = ay - aoffsetY;
    rawZ = az  - (255 - aoffsetZ);
    X = rawX/258.00; // used for angle calculations
    Y = rawY/258.00; // used for angle calculations
    Z = rawZ/258.00; // used for angle calculations
    rolldeg = 180*(atan(Y/sqrt(X*X+Z*Z)))/PI; // calculated angle in degrees
    pitchdeg = 180*(atan(X/sqrt(Y*Y+Z*Z)))/PI; // calculated angle in degrees


    //static char retnum[21];       // Enough for 20 digits plus NUL from a 64-bit uint.
    //sprintf( retnum, "%ul", pitchdeg);
    
    //Serial.write((byte)pitchdeg);
    //Serial.write((byte)rolldeg);
    Serial.write((byte)(X*100));
    Serial.write((byte)(Y*100));

    //Serial.write(arrAccel,sizeof(arrPiezoVal));

    //Serial.print(Y);
    //Serial.print("\t");
    //Serial.print((byte)(Y*100));

    
    // get access to the float as a byte-array:
    //byte * data = (byte *) &X; 

    // write the data to the serial
    //Serial.write (data, sizeof (X));

    //Serial.print(X);
    //Serial.print("\t");
    //Serial.print((byte)(X*100));
    
    /*Serial.print("A0: ");
    Serial.print(piezoVal[0]);
    Serial.print("\t");
    Serial.print("A1: ");
    Serial.print(piezoVal[1]);
    Serial.print("\t");
    Serial.print("A2: ");
    Serial.print(piezoVal[2]);
    Serial.print("\t");
    Serial.print("ax: ");
    Serial.print(ax);
    Serial.print("\t");
    Serial.print("X: ");
    Serial.print(X);
    Serial.print("\t");
    Serial.print(Y);
    Serial.print("\t");
    //Serial.print("rolldeg: ");
    Serial.print(rolldeg);
    Serial.print("\t");
    Serial.print(pitchdeg);
    //Serial.print("\t");
    //Serial.print("az: ");
    //Serial.print(az);
    //Serial.print("\t");
    //Serial.print(pitchdeg);
    //Serial.print("\t");
    //Serial.print(rolldeg);*/

    Serial.println();
    
    



    delay(1);
}
