from aiogram import Bot, types
from aiogram.dispatcher import Dispatcher
from aiogram.utils import executor

# Токен бота
TOKEN = ""
# ID человека (числовой формат), которому бот будет пересылать сообщения (администратор) (узнать ID можно в боте @getmyid_bot)
admin_id = 

boty = Bot(token=TOKEN)
dp = Dispatcher(boty)

ban_list = []


# Начальная команда
@dp.message_handler(commands=['start'])
async def process_start_command(message: types.Message):
    # Если сообщение от администратора
    if message['from'].id == admin_id:
        await message.reply(f"Привет, член ученического совета!")
    # Пишет всем пользователям, кто не является администратором
    else:
        await message.reply(f"Привет, {message['from'].first_name}! Если у тебя есть какая-либо идея, то напиши мне!")


@dp.message_handler(commands=['ban'])
async def process_start_command(message: types.Message):
    if message['from'].id == admin_id:
        if message.reply_to_message.forward_from.id:
            abuser_id = str(message.reply_to_message.forward_from.id)
            ban_list.append(abuser_id)
            await message.reply(f"Пользователь {abuser_id} заблокирован.")


@dp.message_handler(commands=['unban'])
async def handle_unban_command(message: types.Message):
    if message['from'].id == admin_id:
        if message.reply_to_message.forward_from.id:
            abuser_id = str(message.reply_to_message.forward_from.id)
            ban_list.remove(abuser_id)
            await message.reply(f"Пользователь {abuser_id} разблокирован.")


# Для передачи сообщений администратору
@dp.message_handler()
async def process_start_command(message: types.Message):
    if str(message['from'].id) in ban_list:
        await message.reply(f"Прошу прощения, но вы заблокированы.)")
    elif message.reply_to_message is None:
        if '/start' not in message.text:
            await boty.forward_message(admin_id, message.from_user.id, message.message_id)
            await message.reply('Спасибо за сообщение! Я уже передал его члену ученического совета!')
    else:
        # Если на сообщение отвечает администратор
        if message['from'].id == admin_id:
            if message.reply_to_message.forward_from.id:
                # Отправляет сообщение администратора пользователю, которому администратор ответил
                await boty.send_message(message.reply_to_message.forward_from.id, message.text)
        else:
            # Пишет пользователю, если он отвечает на сообщения
            await message.reply('На сообщения нельзя отвечать!')


# Для передачи фото администратору
@dp.message_handler(content_types=['photo'])
async def handle_docs_photo(message):
    await boty.forward_message(admin_id, message.from_user.id, message.message_id)
    await message.answer('Спасибо за фотографию! Я передал ваше сообщение члену ученического совета!')


# Для передачи файлов администратору

@dp.message_handler(content_types=['document'])
async def handle_docs_photo(message):
    await boty.forward_message(admin_id, message.from_user.id, message.message_id)
    await message.answer('Файлик? Спасибо, я передал его члену ученического совета)')


if __name__ == '__main__':
    print("starting")
    executor.start_polling(dp)
