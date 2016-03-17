const int NUM_OF_KEYS = 3;
const int THRESHOLD = 5;
const int analogInputPins[NUM_OF_KEYS] = {A0, A1, A2};

byte arrPiezoVal[2*NUM_OF_KEYS+1];
int piezoVal[NUM_OF_KEYS] = {0};
int bufferlength = 0;
char stringBuffer [50];

void setup() {
 Serial.begin(9600);
}

void loop() {
arrPiezoVal[0]= 0xc0;
int index = 1;
 for (int count; count < NUM_OF_KEYS; count++)
    {
        piezoVal[count] = analogRead(analogInputPins[count]);
        arrPiezoVal[index++] = piezoVal[count] & 0x007f;
        arrPiezoVal[index++] = piezoVal[count] >> 7;
    }
    Serial.write(arrPiezoVal, sizeof(arrPiezoVal));
    delay(100);
}
