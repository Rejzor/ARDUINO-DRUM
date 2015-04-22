
int noteON = 144;//MIDI NOTE ON 
int threshold[6] = {750, 120, 700, 200, 200, 200}; //piezzos threshold
int port[6] = {A0, A1, A2, A3, A4, A5}; //piezzos ports
int readport[6];
int i;
void setup() {
  Serial.begin(31250); //MIDI baund rate
}

void loop() 
{
  for (i = 0; i < 6; i++)
  {
    readport[i] = analogRead(port[i]);//Read data from piezzo 
      if ( readport[i] > threshold[i] ) //Comparison read volts with threshold
        {
          int velocity = map(readport[i], 0, 1023, 0, 127); //Scale the piezzo data to fit between 0 and 127 (this is the range of MIDI notes)
          int note = 60 + i; //MIDI map note

          MIDImessage(noteON, note, velocity);//turn note on
          MIDImessage(noteON, note, 0);//turn note off (note on with velocity 0)
         }     
   }
 }


void MIDImessage(int command, int data1, int data2) //Send MIDI message
{
  Serial.write(command);
  Serial.write(data1);
  Serial.write(data2);
}
