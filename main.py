from aiogram import Bot, Dispatcher, types, executor
from aiogram import *
from aiogram.types import *

#Токен бота
TOKEN = "6014465871:AAHMedcI028U8P-on9mm1RaWh584ZxcTe2A"
#ID человека, которому бот будет пересылать сообщения (администратор) (узнать ID можно в боте @getmyid_bot)
admin_id = 1563658077

boty = Bot(token=TOKEN)
dp = Dispatcher(boty)

#Начальная команда
@dp.message_handler(commands=['start'])
async def process_start_command(message: types.Message):
    #Если сообщение от администратора
    if message['from'].id == admin_id:
        await message.answer(f"Привет, член ученического совета!")
    #Пишет всем пользователям, кто не является администратором
    else:
        await message.answer(f"Привет, {message['from'].first_name}! Если у тебя есть идея или вопрос, то напиши мне!")

#Для передачи сообщений администратору
@dp.message_handler()
async def process_start_command(message: types.Message):
    if message.reply_to_message == None:
        if '/start' not in message.text:
            await boty.forward_message(admin_id, message.from_user.id, message.message_id)
            await message.answer('Спасибо за сообщение! Я уже передал его члену ученического совета!')
    else:
        #Если на сообщение отвечает администратор
        if message['from'].id == admin_id:
            if message.reply_to_message.forward_from.id:
                #Отправляет сообщение администратора пользователю, которому администратор ответил
                await boty.send_message(message.reply_to_message.forward_from.id, message.text)
        else:
            #Пишет пользователю, если он отвечает на сообщения
            await message.answer('На сообщения нельзя отвечать!')

#Для передачи фото администратору
@dp.message_handler(content_types=['photo'])
async def handle_docs_photo(message):
    await boty.forward_message(admin_id, message.from_user.id, message.message_id)
    await message.answer('Спасибо за фотографию! Я передал ваше сообщение члену ученического совета!')

#Для передачи файлов администратору
@dp.message_handler(content_types=['document'])
async def handle_docs_photo(message):
    await boty.forward_message(admin_id, message.from_user.id, message.message_id)
    await message.answer('Файлик? Спасибо, я передал его члену ученического совета)')


if __name__ == '__main__':
    print("starting")
    executor.start_polling(dp)