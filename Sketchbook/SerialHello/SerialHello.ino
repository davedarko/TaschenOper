
uint8_t keys_out [5] = {6,7,8,9,10};
uint8_t keys_in [5] = {1,2,3,4,5};

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  for (uint8_t j=0; j<5; j++) {
      pinMode(keys_out[j], INPUT_PULLUP);
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  
  delay(100);

  for (uint8_t i=0; i<5; i++) {
    for (uint8_t j=0; j<5; j++) {
      
      pinMode(keys_out[j], OUTPUT);
      digitalWrite(keys_out[j], HIGH);
    
      uint8_t x = digitalRead(keys_in[i]);
      if (x==HIGH) {
        Serial.println(j+i*5);
      }
      
      digitalWrite(keys_out[j], LOW);
      pinMode(keys_out[j], INPUT_PULLUP);
    }
  }
}
