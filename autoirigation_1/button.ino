const int buttonPin[] = {14,27,13,12};     // the number of the pushbutton pins
int but[4];
int butcount[4];
int lastbutcount[4]={1,1,1,1};

void but_pres(){
 for(int x=0;x<4;x++) but[x] = digitalRead(buttonPin[x]);
 if (but[0]==0 && butcount[0]== 0){
  Serial.print("buton 1 pressed ");
  Serial.print(butcount[0]);
  butcount[0]++;
 }
}

int button_counter(int x, int y){
  butcount[0]++;
  //return count_val;
}



// Serial.print(but[0]);
// Serial.print(", ");
// Serial.print(but[1]);
// Serial.print(", ");
// Serial.print(but[2]);
// Serial.print(", ");
// Serial.println(but[3]);
