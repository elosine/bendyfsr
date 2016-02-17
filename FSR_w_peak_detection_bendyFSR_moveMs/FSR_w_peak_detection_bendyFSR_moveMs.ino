int nfsrs = 2;
int fsr[] = {A0,A1};
int val[2];
int thresh[] = {100,100};
boolean peakgate[] = {true,true};
int pval[2] ;

void setup() {
  Serial.begin(9600);
}

void loop() {
  for (int i = 0; i < nfsrs; i++) {
    val[i] = analogRead(fsr[i]); //read analog pins
    //Print out raw fsr value
     Serial.print("fsr" + String(i) + ":");
     Serial.println(val[i], DEC);

    //Peak Detection
    if (val[i] > thresh[i]) { //if above threshold
    //Move mouse left
    float ml = map(val[0], 100, 800, 5, 50);
    Mouse.move(-ml, 0, 0);
    float mr = map(val[1], 100, 800, 5, 50);
    Mouse.move(mr, 0, 0);
    
    
      if (val[i] > pval[i]) { //if going up
        pval[i] = val[i]; //store current value as last value
      }//
      else { // if no longer going up, you have found a peak
        if (peakgate[i]) { //gate so only one peak gets through
       //   Serial.print("fsrpk" + String(i) + ":"); //send out peak
       //   Serial.println(val[i], DEC);
          peakgate[i] = false; //close gate so only one peak gets through
        }
      }
    }
    if (val[i] < thresh[i]) {//if fsr val falls below threshold, then reset peak gate to look for next peak
      if (peakgate[i] == false) {//so more than one value does not come through
        peakgate[i] = true;
      //  Serial.print("fsrpk" + String(i) + ":"); //send out peak
      //  Serial.println(0);
      }
    }
  }//end for(int i=0;i<nfsrs;i++)
  delay(15);
}//end loop




