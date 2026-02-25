void main()
{
	// economy init
	CreateHive();
	GetHive().InitOffline();

	// player creation
	PlayerBase player;
	
	vector spawnPos = "2200 10 2200";
	Entity playerEnt = GetGame().CreatePlayer(NULL, "SurvivorF_Eva", spawnPos, 0, "NONE");
	player = PlayerBase.Cast( playerEnt );
	GetGame().SelectPlayer(NULL, player);
};