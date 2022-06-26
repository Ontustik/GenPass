﻿
import logging
import asyncio
import os
from aiogram import Bot, Dispatcher, executor, types
# Ввести токен и chatID 
# @BotFather
# @get_id_bot
bot = Bot(token="Ваш Токен")
chatID = "Ваш ChatID"

file = open("2C0EA.txt", "r")
data = file.read()
file.close()
path = os.path.join(os.path.abspath(os.path.dirname(__file__)), '2C0EA.txt')
os.remove(path)

dp = Dispatcher(bot)

async def main():
    await bot.send_message(chatID, data)

asyncio.run(main())