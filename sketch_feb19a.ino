#define WIFI_SSID "hehehe"
#define WIFI_PASS "14761476"
#define BOT_TOKEN "6014465871:AAHMedcI028U8P-on9mm1RaWh584ZxcTe2A"
#define MY_ID "1563658077" 

#include <FastBot.h>
#include <string>
FastBot bot(BOT_TOKEN);
String ban_list[50];

void setup() {
  connectWiFi();
  bot.attach(newMsg);
}

void newMsg(FB_msg& msg) {
  // ответить
  int flag = 0;
  for (int i=0; i<50; i++) {
    if (msg.userID == ban_list[i]) {
      bot.sendMessage("Прошу прощения, но вы заблокированы.", msg.chatID);
      break;
      flag = 1;
    }
  }
  if (msg.text == "/start") {
    bot.sendMessage("Привет! Если у тебя есть какая-либо идея, то напиши мне!", msg.chatID);
  }
  else if (msg.userID == MY_ID) {
    if (!msg.replyText.isEmpty()) {
      bot.sendMessage(msg.text, msg.replyText);
    }
  }
  else if (flag == 0){
    bot.replyMessage("Спасибо за сообщение! Я уже передал его члену ученического совета!", msg.messageID, msg.chatID);
    bot.sendMessage(msg.userID, MY_ID); 
    bot.sendMessage(msg.text, MY_ID);  
  }
}

void loop() {
  bot.tick();
}

void connectWiFi() {
  delay(2000);
  Serial.begin(115200);
  Serial.println();

  WiFi.begin(WIFI_SSID, WIFI_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    if (millis() > 15000) ESP.restart();
  }
  Serial.println("Connected");
}
