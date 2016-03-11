//========================================================================================
//Set this value to the number of keys/piezos you are using
const int NUM_OF_KEYS = 3;
//Adjust this value to change the sensitivity of the piezos
const int THRESHOLD = 5;
//Change these values to set which analog input pins you are using
//Also make sure that the total number of values here matches the value of NUM_OF_KEYS
const int analogInputPins[NUM_OF_KEYS] = {A0, A1, A2};
//=======================================================================================

//Variables for storing certain values
int piezoVal[NUM_OF_KEYS] = {0};
int bufferlength = 0;
char stringBuffer [50];

void setup()
{
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
}

void loop()
{
    //repeat the below code for each anaolog input/piezo sensor
    for (int count; count < NUM_OF_KEYS; count++)
    {
        //read the piezo value
        piezoVal[count] = analogRead(analogInputPins[count]);
    }

    for(int l= 0; l<=bufferlength; l++) 
    {
      Serial.print("A0: ");
      Serial.print(piezoVal[0]);
      Serial.print("\t");
      Serial.print("A1: ");
      Serial.print(piezoVal[1]);
      Serial.print("\t");
      Serial.print("A2: ");
      Serial.print(piezoVal[2]);
      Serial.println();
    }

    //pause the loop
    delay(1);
}
