#!/bin/bash
pkill -f Dialog && make --directory=build && ./bot_check.sh && echo "Bot restarted"
