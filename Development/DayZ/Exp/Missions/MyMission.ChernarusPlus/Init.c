Mission CreateCustomMission(string path)
{
	return new MissionGameplay();
}

void main()
{
	//INIT ECONOMY--------------------------------------
	Hive ce = CreateHive();
	if ( ce )
		ce.InitOffline();
	
	PlayerBase player;
	ItemBase item;

	// Создаем игрока, указываем позицию возрождения
	player = PlayerBase.Cast( GetGame().CreatePlayer(NULL, "SurvivorF_Linda", "2200 10 2200", 0, "NONE") );

	// Спавним игроку рубашку TShirt_Black
	//item = player.GetInventory().CreateInInventory("TShirt_Black");

	// Спавним игроку штаны ShortJeans_Green
	//item = player.GetInventory().CreateInInventory("ShortJeans_Green");

	// Спавним игроку обувь WorkingBoots_Brown
	//item = player.GetInventory().CreateInInventory("WorkingBoots_Brown");

	// Создаем предмет в инвентаре
	//item.GetInventory().CreateInInventory("Apple");

	// Выбираем игрока которым будет управлять клиент
	GetGame().SelectPlayer(NULL, player);
}