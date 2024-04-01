#define WIFI_SSID "hehehe" // Название WiFi или точки доступа
#define WIFI_PASS "14761476" // Пароль от WiFi или точки доступа
#define BOT_TOKEN "6014465871:AAHMedcI028U8P-on9mm1RaWh584ZxcTe2A" // Токен бота
#define MY_ID "1563658077" // ID администратора
#define ANOTHER_ID "1097741110"


#include <FastBot.h>
#include <string>
FastBot bot(BOT_TOKEN);
String ban_list[50]; // Список забаненых
int len_of_ban_list_now = 0; // Количество забаненых пользователей
bool res = 0;

void setup() {
  connectWiFi();
  bot.attach(newMsg);
}

void newMsg(FB_msg& msg) {
  // Действия над сообщениями пользователей
  int flag = 0;
  for (int i=0; i<50; i++) {
    if (msg.userID == ban_list[i]) {
      flag = 1;
      break;
    }
  }
  if (msg.text == "/start") {
    bot.sendMessage("Привет! Если у тебя есть какая-либо идея, то напиши мне!", msg.chatID); // Начало работы пользователя с ботом
  }
  else if (msg.userID == MY_ID or msg.userID == ANOTHER_ID) {
    if (msg.text == "/restart") {
        bot.sendMessage("Бот перезапущен.", msg.userID); // Перезапуск бота
        res = 1;
    }
    else if (!msg.replyText.isEmpty()) {
      if (msg.text == "/ban") {
        ban_list[len_of_ban_list_now] = msg.replyText;
        len_of_ban_list_now++;
        bot.sendMessage("Пользователь "+msg.replyText+" заблокирован.", MY_ID); // Блокировка пользователя с помощью команды /ban
        bot.sendMessage("Пользователь "+msg.replyText+" заблокирован.", ANOTHER_ID);
      }
      else if (msg.text == "/unban") {
        for (int i=0; i < 50; i++) {
          if (ban_list[i] == msg.userID) {                        
            ban_list[i] = "0";
            len_of_ban_list_now--;
          }
        }
        bot.sendMessage("Пользователь "+msg.replyText+" разблокирован.", MY_ID);  // Разблокировка пользователя с помощью команды /unban
        bot.sendMessage("Пользователь "+msg.replyText+" разблокирован.", ANOTHER_ID);
      }
      else {
        if (msg.userID == MY_ID) {
          bot.sendMessage("Ответ от администратора Инна: "+msg.text, msg.replyText);
          bot.sendMessage("Ответ отправлен.", msg.userID);
          if (msg.replyText != ANOTHER_ID){
            bot.sendMessage("Ответ от администратора Инна: "+msg.text, ANOTHER_ID);
          }
        }
        else {
          bot.sendMessage("Ответ от администратора Артём: "+msg.text, msg.replyText);
          bot.sendMessage("Ответ отправлен.", msg.userID);
          if (msg.replyText != MY_ID){
          bot.sendMessage("Ответ от администратора Артём: "+msg.text, MY_ID);
          }
        }
      }
    }
    else {
      if (msg.userID == MY_ID) {
        bot.sendMessage(msg.userID, MY_ID); 
        bot.sendMessage("Инна: "+msg.text, MY_ID);
        bot.sendMessage(msg.userID, ANOTHER_ID); 
        bot.sendMessage("Инна: "+msg.text, ANOTHER_ID);
      }
      else {
        bot.sendMessage(msg.userID, MY_ID); 
        bot.sendMessage("Артём: "+msg.text, MY_ID);
        bot.sendMessage(msg.userID, ANOTHER_ID); 
        bot.sendMessage("Артём: "+msg.text, ANOTHER_ID);
      }
    }
  } 
  else if (flag == 1) {
    bot.sendMessage("Прошу прощения, но вы заблокированы.", msg.chatID); // Когда пользователь забанен, то программа уведомляет его об этом и не пересылает сообщение администратору
  }
  else if (flag == 0){
    bot.replyMessage("Спасибо за сообщение! Я уже передал его члену ученического совета!", msg.messageID, msg.chatID); // Пересылка сообщения администратору
    bot.sendMessage(msg.userID, MY_ID); 
    bot.sendMessage(msg.text, MY_ID);  
    bot.sendMessage(msg.userID, ANOTHER_ID); 
    bot.sendMessage(msg.text, ANOTHER_ID);
  }
}
// Цикл, обновляющий информацию о сообщениях в чате
void loop() {
  if (res) {
    bot.tickManual(); // Чтобы отметить сообщение прочитанным
    ESP.restart();
  }
  bot.tick();
}
// Подключение к сети
void connectWiFi() {
  delay(2000);
  Serial.begin(9600);
  Serial.println();

  WiFi.begin(WIFI_SSID, WIFI_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    if (millis() > 15000) ESP.restart();
  }
  Serial.println("Connected");
}
