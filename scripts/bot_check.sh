#!/bin/bash
ps -A | grep Dialog || /home/gleb/CXX/BotDialog/scripts/bot_start.sh >> /home/gleb/CXX/BotDialog/error_log.txt 2>&1 &