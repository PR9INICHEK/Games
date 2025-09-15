1. При вводе `r` или любого другого символа в консоли и нажатии **Tab** показываются возможные команды
    - **TODO** Добавить скрин
    - Если ещё ввести полную и нажать **Tab**, то покажут какие данные и каких типов принимают на вход
    - **TODO** Добавить скрин
2. С помощью Tab или(ВЫЯСНИТЬ) Shift + Tab можно увидеть список возможных команд
    - **TODO** Добавить скрин





Ребята, всем привет :)

Случайно узнал, что у игры выставлено ограничение в 100 фпс
Можете проверить у себя, какое оно в данный момент, открыв консоль, нажав кнопку ~(ниже кнопки Esc) и вбив команду
Код: [Выделить]
Game.LockFps

Скорее всего у вас выдаст, что 100

Чтобы изменить его, нужно вбить эту команду и указать в конце, после пробела, цифру 0
То есть должно получиться:
Код: [Выделить]
Game.LockFps 0

НО я настоятельно рекомендую вам выставить не 0, а частоту разрешения вашего монитора, например 144, если у вас 144 Гц

Чтобы при каждом запуске игры не вводить эту команду вручную, просто добавьте эту команду в файл GameLogicInit.con
Код: [Выделить]
Он находится в "ПАПКА, ГДЕ У ВАС УСТАНОВЛЕНА ИГРА\mods\bf2\GameLogicInit.con"

Примечание:
Это нужно будет сделать для каждого мода, например для brw и xpack

Так же рекомендую добавить помимо этой строчки ещё и
Код: [Выделить]
renderer.drawfps 1
renderer.vsync 1

Первая позволит вам видеть ФПС и применённые изменения
А вторая синхронизирует частоту кадров с вашим монитором

Инфу о том, в какой файл добавлять изменения почерпнул на https://www.pcgamingwiki.com/wiki/Battlefield_2 и https://www.pcgamingwiki.com/wiki/Battlefield_2#High_frame_rate

https://2f4y.com/forum/viewthread.php?forum_id=5&thread_id=3837
> Battlefield2->mods->bf2->Settings
> 
> USERSETTINGS
> 
> Btw Usersettings.con ->1. Uncheck ReadOnly, 2. do whatever U want, 3. Check ReadOnly


А тут про Controls в папке с профилем

https://www.lost-soldiers.org/v2.php?site=forum_topic&topic=81#16314
> Documents \ Battlefield 2 \ Profiles \ 0001 folder (repeat for every other profile), open the Controls.con file with the editor and at the end the line,



3. Включение синхронизации через монитор - https://steamcommunity.com/app/24860/discussions/0/133256959380901741/
4. https://hardforum.com/threads/forcing-vsync-in-bf-2-2142-on-ati.1485390/
   - Тут пишут, что эту настройку надо сохранять в video.con в профиле


https://www.lost-soldiers.org/v2.php?site=forum_topic&topic=81#16314
Про то, что надо убирать лок фпс совсем

Stutter or input lag?
Locking your frames can create quite a lot of input lag, depending on what kind of frame limiter is used. Many ingame frame limiters do a bad job and I feel like the one in BF2 is not particularly good. Newer Nvidia drivers offer an inbuilt frame limiter, which is not too bad, but the best frame limiter by far is RTSS.

The thing with RTSS is, that is adds exactly one frame of input lag. In turn it creates very stable frametimes which gives you a pretty smooth experience ingame. Frametimes are defined like this:

 Frametime (ms) = 1000/fps

So if you run the game at 100 fps, you get a new frame every 10 ms. These 10ms are ADDED to the chain of input lag you experience. Since FPS are an average value, this could mean that one frame takes 15ms to render and then other one 5 ms, giving you an average of 10ms. This will cause perceived stutter.
 Where to put your money on
So what you want is STABLE frametimes; but BF2 makes this hard. Due to the hardware limitations at release of the game, only things in front of you will be rendered properly. You can check this by observing FPS and looking at the "action" and then looking away from the action. So if you are turning fast in battle, frametimes will become unstable for a split second which can cause mouse skipping and rubber banding.

So you can basically choose whether you want smoothness or input delay/lag. The statement that locking fps at the value your monitor supports is enough is wrong though, since higher FPS shorten frametimes and the frames will get to your PC faster. So what you see will be a bit less "in the past".

People seem to have the assumption that everything is instant, but in reality you will see everything that happens in your RAM/CPU around 10-200ms later, with 10 being on top notch Intel Hardware with a perfectly optimized system.

To get you in the ballpark, 35ms is around a head's length of a running soldier. In general BF2 is a rather CPU heavy game, so on modern hardware the bottleneck will always be the CPU. GPUs have evolved much faster than CPUs since 2005.
 So what do I do now?
I personally unlock my FPS with game.lockfps 0, because I crave that input lag reduction. You have to note, though, that doing so will tax your CPU more and you will need to optimize your windows environment so that not only the game, but also the OTHER components run well.

These other components are the windows infrastructure needed to run the game, including things such as USB drivers, mouse/kb drivers, Network protocols and drivers, graphics drivers, etc.

5. Как изменить язык - https://web.archive.org/web/20171117214115mp_/https://battlelog.co/post.php?id=13636
6. Описание карт с расположением различных мест - https://www.realtimerendering.com/erich/battlefield2/maps/maps.html
7. Различные показания для оружия и техники - https://www.realtimerendering.com/erich/battlefield2/grid.html
8. 
