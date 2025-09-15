# Создание и настройка сервера
## Дано
- Ubuntu 24.04

## Подготовка
1. `sudo useradd -m bf2server`
2. `sudo passwd bf2server` далее вводим пароль
3. `sudo adduser bf2server sudo` - даём возможность новому пользователю выполнять команды из под _sudo_
4. `sudo -u bf2server -s`
5. `cd /home/bf2server`
    - потому что по умолчанию попадаешь в _bf2server@noname:/root$_
6. `mkdir server-files`
7. `cd server-files`
## Скачивание
1. `wget http://ftp2.sly.hu/letolt//battlefield2/bf2-linuxded-1.5.3153.0-installer.rar`
    - Тут должны быть запасные urls
10. Если файл с расширением .rar, то устанавлием _unrar_ - `sudo apt-get install unrar`
11. Разархивируем архив -`unrar x -r bf2-linuxded-1.5.3153.0-installer.rar`
12. Для _.sh_ этого не требуется делать
## Установка
1. `sudo chmod +x bf2-linuxded-1.5.3153.0-installer.sh` - без этой команды при выполнении `sudo ./bf2-linuxded-1.5.3153.0-installer.sh` получите ошибку _command not found_
15. `sudo ./bf2-linuxded-1.5.3153.0-installer.sh`
16. Видим сообщение "You will now be shown the EULA for the BF2 dedicated Linux server. Press return to continue."
17. Нажимаем _Enter_
12. Открывается лицензия и показывается процент пройдённого
13. Либо пролистываем по чуть-чуть с помощью нажатия _Enter_
14. Либо переходим к концу с помощью _Page Down_
15. Пишем _accept_
    - не ясно, _decline_ влияет ли на работоспособность сервера
        - > If you decline, you may not use the Tools & Materials.
16. Далее открывается лицензия на использование PunkBuster'a - "You will now be shown the EULA for PunkBuster. Press return to continue."
17. Нажимаем _Enter_
18. Нажимаем _Page Down_
19. Пишем _yes_
    - Не ясно, нужен ли он нам в текущих реалиях и можно ли написать _no_
20. > The target installation directory is where the bf2 directory will be created and must be an existing directory. Enter your target installation directory:
21. Указываем текущую директорию `/home/bf2server/server-files`
22. Дожидаемся сообщений
    - > Installing BF2 to /home/bf2server/server-files/bf2...
    - > Installing PunkBuster...
    - 
    - > Installation complete.



Вот такие файлы и папки у вас должны появиться в созданной папке **bf2**:
1. admin
2. lowercaseDir.py
3. pb_ia-32
4. readmes
5. adminutils
6. mods
7. pylib-2.3.4.zip
8. rotate_demo.cfg
9. bin
10. pb_amd-64
11. python
12. start.sh

# Статистика
1. https://github.com/wilson212/bf2stats
2. https://code.google.com/archive/p/bf2stats/downloads

# Полезные ссылки
1. https://habr.com/ru/articles/149947/
2. https://github.com/nihlen/bf2-docker
4. https://bf2-nns.clan.su/forum/4-77-1
5. https://opticatelecom.ru/forum/topic/4773-%D0%BA%D0%B0%D0%BA-%D1%81%D0%B4%D0%B5%D0%BB%D0%B0%D1%82%D1%8C-%D1%81%D0%B2%D0%BE%D0%B9-%D1%80%D0%B0%D0%BD%D0%B3%D0%BE%D0%B2%D1%8B%D0%B9-%D1%81%D0%B5%D1%80%D0%B2%D0%B5%D1%80-battlefield-2/
6. 
9. Какая-то инфа, может быть полезна - https://serversupportforum.de/threads/battlefield-2-server-installation.60229/
    - https://www.lissyara.su/articles/freebsd/games/ea_battlefield_2_game_server/
        - В комментариях есть полезная инфа
    - https://forum.lissyara.su/igry-f33/battlefield-2-server-t8015.html#p66968
    - https://www.forum-volgograd.ru/threads/75914/page-3#post-1539801
        - > В принципе, у меня есть и bf2-linuxded-1.1.2965-797.0-installer.sh, т.е. сервер под linux версии 1.41, а к нему еще какие-то скрипты для статистики и еще что-то... Накачал, а времени разбираться нет.
    - 1.5 - bf2-linuxded-1.5.3153.0-installer.sh
        - https://www.bf-games.net/downloads/954/bf2-dedicated-server-150-linux-build-153153-8020.html
        - https://en.ds-servers.com/gf/bf2-linuxded-1-5-3153-0-installer-sh.html
10. Возможно, что для 1.41 подходит патч от 1.40 - https://www.patches-scrolls.com/battlefield2.php
     - А изменения чисто клиентские, НО ЭТО НЕ ТОЧНО
11. https://www.bf-games.net/forum/topic/44144-bf2-15-image-howto-install-linux/
12. https://web.archive.org/web/20140816010034/http://live.cnews.ru/games/index.php?showtopic=27998
13. 

# Если нужно подключить сервер к BF2HUB
- https://www.bf2hub.com/home/serversetup.php

# Старые версии
- 1.0 - https://www.moddb.com/games/battlefield-2/downloads/linux-dedicated-server-1-0
- 1.41 - https://forums.bf2s.com/viewtopic.php?id=81206
    - http://wftp2.sly.hu/ftpstart/?dl=letolt//battlefield2/bf2-linuxded-1.1.2965-797.0-installer.sh.gz
