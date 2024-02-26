#include <SPI.h>
#include <MFRC522.h>
#include <WiFi.h>
#include <HTTPClient.h>

String URL = "http://192.168.132.158/rfid/test.php";

const char* ssid = "LOGIN WIR"; 
const char* password = "12345678"; 

#define RST_PIN   22
#define SS_PIN    5 

String Data, id;
int idcard;
String akses;

MFRC522 mfrc522(SS_PIN, RST_PIN);

void setup() {
  Serial.begin(115200);

  connectWiFi();
  SPI.begin();
  mfrc522.PCD_Init();
  delay(4);

  Serial.println("Tempel kartu anda");
  Serial.println();
}

void loop() {
  if(WiFi.status() != WL_CONNECTED) {
    connectWiFi();
  }
  if(!mfrc522.PICC_IsNewCardPresent()){
    return;
  }
  if(!mfrc522.PICC_ReadCardSerial()){
    return;
  }
  Serial.print("UID tag : ");
  id = String(mfrc522.uid.uidByte[0]) + String(mfrc522.uid.uidByte[1]) + String(mfrc522.uid.uidByte[2]) + String(mfrc522.uid.uidByte[3]);
  Serial.println(id);
  
  if (id == "414140242")
  { 
    akses = "Succes";
    idcard = id.toInt(); // Mengubah string ke integer
    Data = "idcard="+String(idcard)+"&akses="+akses;
    Serial.println("Hello World!");
  } else{
    akses = "Denied";
    idcard = id.toInt(); // Mengubah string ke integer
    Data = "idcard="+String(idcard)+"&akses="+akses;
    Serial.println("Denied");
  }

  HTTPClient http;
  http.begin(URL);
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");
  int httpCode = http.POST(Data);

  Serial.print("URL : "); Serial.println(URL); 
  Serial.print("Data: "); Serial.println(Data);
  Serial.print("httpCode: "); Serial.println(httpCode);

  if (httpCode == HTTP_CODE_OK) {
    String payload = http.getString();
    Serial.print("Payload: ");
    Serial.println(payload);
  } else {
    Serial.println("Error in HTTP request");
  }
  
  Serial.println("--------------------------------------------------");
  delay(2000);
}

void connectWiFi() {
  WiFi.mode(WIFI_OFF);
  delay(1000);
  //This line hides the viewing of ESP as wifi hotspot
  WiFi.mode(WIFI_STA);
  
  WiFi.begin(ssid, password);
  Serial.println("Connecting to WiFi");
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
    
  Serial.print("connected to : "); Serial.println(ssid);
  Serial.print("IP address: "); Serial.println(WiFi.localIP());
}