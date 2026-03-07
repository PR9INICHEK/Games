//! Modded SCR_BaseGameMode to re-randomize spawn points on player death
modded class SCR_BaseGameMode
{
	override void OnPlayerKilled(int playerId, IEntity playerEntity, IEntity killerEntity, notnull Instigator killer)
	{
		super.OnPlayerKilled(playerId, playerEntity, killerEntity, killer);

		// Invalidate spawn point cache so the player gets a fresh random selection
		WL_SpawnPointSelector.InvalidatePlayer(playerId);
	}
}
