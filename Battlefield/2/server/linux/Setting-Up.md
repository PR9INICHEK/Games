# Настройка
1. `sudo nano bf2/mods/bf2/settings/serversettings.con`
    - через `sudo`, в ином случае увидите - "[ File 'serversettings.con' is unwritable ]"
    - Не меняем значение _sv.internet_ с 0 на 1 или получите ошибку при запуске
    > Build date:implement unix date here
        Module: GameServer
        File: Game/GameServer/GameServer.cpp
        Line: 647
        Text: 0xbfed6a28
        Current confile:
    > https://www.realitymod.com/forum/showthread.php?p=2101064#post2101064
    > _sv.punkBuster_ тоже 0 должен быть, так как не имеет смысла
    > https://www.realitymod.com/forum/showthread.php?p=2101308#post2101308 
2. **TODO** Тут нужна ссылка на то как настраивать _serversettings.con_, что за что отвечает и для _maplist.con_
    - `cd readmes`
    - `nano readme-linux.txt`
        - Тут инфа по параметрам для _serversettings.con_
    - `nano readmeserver.txt`
        - Тут ещё доп инфа, в том числе и про _maplist.con_
     
Какие-то из команд ниже помогли с проблемой

4. `sudo apt-get install ia32-libs`
        Reading package lists... Done
        Building dependency tree... Done
        Reading state information... Done
        Package ia32-libs is not available, but is referred to by another package.
        This may mean that the package is missing, has been obsoleted, or
        is only available from another source
        However the following packages replace it:
          lib32z1
        
        E: Package 'ia32-libs' has no installation candidate

`find /usr/lib/ -name *ncurses*`

/usr/lib/x86_64-linux-gnu/libncursesw.so.6
/usr/lib/x86_64-linux-gnu/libncurses.so.6
/usr/lib/x86_64-linux-gnu/libncursesw.so.6.4
/usr/lib/x86_64-linux-gnu/libncurses.so.6.4


https://stackoverflow.com/questions/17005654/error-while-loading-shared-libraries-libncurses-so-5

`sudo ln -s /usr/lib/x86_64-linux-gnu/libncursesw.so.6.0 /usr/lib/libncurses.so.5`
`sudo ln -s /usr/lib/x86_64-linux-gnu/libncursesw.so.6.0 libncursesw.so.5`


find /usr/lib/ -name *libtinfo*
/usr/lib/x86_64-linux-gnu/libtinfo.so.6.4
/usr/lib/x86_64-linux-gnu/libtinfo.so.6

`sudo ln -s /usr/lib/x86_64-linux-gnu/libncursesw.so.6.0 /usr/lib/libtinfo.so.5`


https://stackoverflow.com/a/79141988

`sudo nano /etc/apt/sources.list.d/ubuntu.sources`
    Types: deb
    URIs: http://security.ubuntu.com/ubuntu/
    Suites: focal-security
    Components: main universe
    Signed-By: /usr/share/keyrings/ubuntu-archive-keyring.gpg


`sudo apt update`
`sudo apt-get install libncurses5:i386`

https://stackoverflow.com/a/78649883

`sudo add-apt-repository universe`
`sudo apt-get install libncurses5 libncurses5:i386`
https://askubuntu.com/questions/1252062/how-to-install-libncurses-so-5-in-ubuntu-20-04


`cd /home/bf2server/server-files/bf2`


## Запуск
1. `sudo ./start.sh +help` - Для проверки, что всё хорошо
    - Если без `sudo`, то будет ошибка "./start.sh: 24: ulimit: error setting limit (Operation not permitted)". Хотя информация о параметрах выведется
2. `screen ./start.sh +dedicated`
Now press Ctrl-A followed by Ctrl-D to detach the screen session, leaving it
running in the background. You can now log out without affecting the server.

# Мониторинг
`screen -r`

# Подключение к серверу
Создаём ярлык для BF2.exe и в свойствах объекта прописываем путь до сервера _+joinServer айпи.сервера +port 16567_

# Открытые вопросы
1. Куда логируются ошибки

# Полезные ссылки
1. Инфа про PunkBuster - https://habr.com/ru/articles/149947/#comment_5076552
2. В файлах есть инфа про
    > Have fun with your Linux server!
    > Andreas Andersson andreas.andersson@dice.se
    > Возможно, что это он - https://dev.to/derwiath - https://www.neoboid.com/
