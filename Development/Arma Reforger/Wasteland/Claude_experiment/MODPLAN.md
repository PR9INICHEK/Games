# MODPLAN — WastelandReforger

## Концепция
PvPvE режим выживания для Arma Reforger. Игроки начинают с $500, добывают деньги (убивая AI и игроков), тратят в магазинах. Три фракции: BLUFOR, OPFOR, INDEPENDENT.

## Статус фаз

### ✅ Фаза 1 — Game Mode и команды
- [x] WL_GameMode.c — основной игровой режим (наследник SCR_BaseGameMode)
- [x] WL_TeamManagerComponent.c — авто-балансировка команд при коннекте
- [x] WL_ETeam.c — enum: NONE / BLUFOR / OPFOR / INDEPENDENT
- [x] Prefabs/Systems/WL_GameMode.et — prefab игрового режима
- [x] Configs/Factions/ — конфиги трёх фракций (Blufor, Opfor, Independent)

### ✅ Фаза 2 — Экономика и HUD
- [x] WL_EconomyManagerComponent.c — кошельки игроков, начисление/списание
- [x] WL_HUDComponent.c — отображение денег и фракции (наследник SCR_InfoDisplayExtended)
- [x] UI/layouts/WL_HUD.layout — layout HUD (MoneyText + TeamText)

### ✅ Фаза 3 — Магазин
- [x] WL_ShopComponent.c — покупка предметов (AK-74 $300, Pistol $150, Medkit $100)
- [x] UI/layouts/WL_ShopMenu.layout — UI меню магазина

### ✅ Фаза 4 — AI враги
- [x] WL_AIManagerComponent.c — спавн AI патрулей, награда за убийство AI ($100)

### ⏳ Фаза 5 — Интеграция и тест (следующий сеанс)
- [ ] Установить Arma Reforger (игра) для asset_search реальных GUID оружия
- [ ] Заменить placeholder GUID в WL_ShopComponent и WL_AIManagerComponent
- [ ] Создать тестовый мир (.ent) с WL_GameMode entity, спавн-точками и магазином
- [ ] Подключить WL_ShopComponent к UserAction (открытие меню по UseAction)
- [ ] Запустить Workbench (wb_launch), загрузить аддон, проверить компиляцию
- [ ] Тест: коннект → авто-фракция → HUD → магазин → AI спавн

## Известные TODO / ограничения
- Prefab GUID оружия и AI — placeholder (00000000). Нужна установленная игра
- WL_ShopComponent нужен UserAction-скрипт для открытия меню (WL_OpenShopAction.c)
- Respawn игроков — настроить SCR_RespawnSystemComponent в prefab WL_GameMode.et
- WL_HUDComponent.GetForPlayer работает только локально — для server-side уведомлений
  нужна RPC-нотификация через Rpl

## Структура файлов
```
WastelandReforger/
  MODPLAN.md
  WastelandReforger.gproj
  Scripts/Game/
    WL_ETeam.c
    WL_GameMode.c
    WL_TeamManagerComponent.c
    WL_EconomyManagerComponent.c
    WL_HUDComponent.c
    WL_ShopComponent.c
    WL_AIManagerComponent.c
  Prefabs/
    Systems/WL_GameMode.et
  Configs/
    Factions/WL_Blufor.conf
    Factions/WL_Opfor.conf
    Factions/WL_Independent.conf
  UI/layouts/
    WL_HUD.layout
    WL_ShopMenu.layout
```

## Запуск нового сеанса
Открой этот файл и напиши `/modify-mod` — я продолжу с Фазы 5.
