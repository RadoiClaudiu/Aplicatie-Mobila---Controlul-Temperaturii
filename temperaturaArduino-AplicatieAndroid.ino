#include <dht.h>
#include <SoftwareSerial.h>
#define DHT11_PIN A0

#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);
int thresholds[16]={2,77,144,202,244,290,331,368,394,424,452,477,496,518,538,556};
char keypad[16] = {'1','2','3','A','4','5','6','B','7','8','9','C','*','0','#','D'};

dht DHT;
SoftwareSerial blue(2,3); // bluetooth module connected here 
long int data=0; 
int vent= 13;
long int password1 = 92;
long int password2 = 79; 
long int password20 = 20; 
long int password21 = 21; 
long int password22 = 22;  
long int password23 = 23;
long int password24 = 24; 

void setup(){
  lcd.begin(16,2);//Defining 16 columns and 2 rows of lcd display
  lcd.backlight();//To Power ON the back light
  pinMode(13, OUTPUT);
  pinMode(vent, OUTPUT); 
  Serial.begin(9600); 
  delay(500);
  blue.begin(9600); 
} 

void loop(){
  //Lumina:
  int lightPin = A1 ;  //Photoresistor Pin
  int val = analogRead(lightPin); //Read Pin
  val = map(val, 0, 1023, 0, 100);  //Convert Value From Pin To Percent
  Serial.print("Light Intencity" ) ;  // Display Percent
  Serial.print(val ) ;
  lcd.setCursor(0,1);
  lcd.print("VLum:");
  lcd.print(val);
  lcd.print("%");
  if(val>25 && val <=40){
    lcd.print(" Led 33%");
    lcd.setCursor(15,1);
    lcd.print(" ");
    analogWrite(9,50);
  }else if(val>40 && val <=65){
          lcd.print(" Led 66%");
          lcd.setCursor(15,1);
          lcd.print(" ");
          analogWrite(9,100);
        }else if(val>65 && val <=100){
                 lcd.print(" Led100%");
                 lcd.setCursor(15,1);
                 lcd.print(" ");
                 analogWrite(9,250);
              }else{analogWrite(9,LOW);lcd.print(" Led OFF");}
  Serial.println("%" ) ;
  
  
  
  //Temperatura:
   DHT.read11(DHT11_PIN);
   int temp = DHT.temperature;
   blue.print("Umiditatea = ");
   blue.print(DHT.humidity);
   blue.print("%  ");
   blue.print("Temperatura = ");
   blue.print(DHT.temperature); 
   blue.println("C  ");

   lcd.setCursor(0,0);
   lcd.print("T:");
   lcd.print(temp);
   lcd.print("C");

   Serial.print("Current humidity = ");
   Serial.print(DHT.humidity);
   Serial.print("%  ");
   Serial.print("temperature = ");
   Serial.print(DHT.temperature); 
   Serial.println("C  ");
   delay(2000);
   Serial.println(temp);

   if(blue.available()>0) 
   {
      data = blue.parseInt();
   } 
   delay(400);
   if(data==password20){
      if(temp > 20){
         digitalWrite(vent,LOW);
         Serial.println("VENT OFF20");
      }else digitalWrite(vent,HIGH);
   }else if(data==password21){
            if(temp > 30){
               digitalWrite(vent,LOW);
               Serial.println("VENT OFF21");
            }else digitalWrite(vent,HIGH);
         }else if(data==password22){
                  if(temp > 22){
                     digitalWrite(vent,LOW);
                     Serial.println("VENT OFF22");
                  }else {digitalWrite(vent,HIGH);}
               }else if(data==password23){
                        if(temp > 23){
                           digitalWrite(vent,LOW);
                           Serial.println("VENT OFF23");
                        }else digitalWrite(vent,HIGH);
                     }else if(data==password24){
                              if(temp > 24){
                                 digitalWrite(vent,LOW);
                                 Serial.println("VENT OFF24");
                              }else digitalWrite(vent,HIGH);
                           }else if(temp <=26){
                                    digitalWrite(vent,HIGH);
                                    Serial.println("VENT ONNNNNNNNNNNNNNNNNNNNNNNNNNN");
                                    
                                }else if(temp >= 28){
                                       digitalWrite(vent,LOW);
                                       Serial.println("VENT OFFFFFFFFFFFFFFFFFFFFFFFFF");
                                    }
   if (data == password1)
   {
      digitalWrite(vent,HIGH);
      Serial.println("VENT ON");
      delay(10000);
      digitalWrite(vent,LOW);
      Serial.println("VENT OFF ");
      data=0;
   }
   if( data == password2)
   {
      digitalWrite(vent,LOW);
      Serial.println("VENT OFF");
   }
   
   Serial.print("data este:");
   Serial.print(data);

   //lcd.clear();

    //lcd.setCursor(0,0);
//    lcd.print("  ");
//    lcd.print(num);
    



  int value = analogRead(A2);
   Serial.println(value);
  for(int i=0;i<16;i++){
    if(abs(value - thresholds[i]) < 5){
      Serial.println(keypad[i]);
      lcd.print("  ");
      lcd.print(keypad[i]);
   // while(analogRead(A2)<1000){delay(1000);
    }
    //
    }
    delay(100);
  

delay(2000);
}
