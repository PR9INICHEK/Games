//! Modded SCR_BaseGameMode — adds configurable random spawn point selection
modded class SCR_BaseGameMode
{
	[Attribute("0", UIWidgets.CheckBox, "Enable weighted random spawn point selection (show 5 of 16 locations per player, re-randomized on death)")]
	protected bool m_bWL_RandomSpawnPoints;

	//------------------------------------------------------------------------------------------------
	void SCR_BaseGameMode(IEntitySource src, IEntity parent)
	{
		WL_SpawnPointSelector.SetEnabled(m_bWL_RandomSpawnPoints);
	}

	//------------------------------------------------------------------------------------------------
	override void OnPlayerKilled(int playerId, IEntity playerEntity, IEntity killerEntity, notnull Instigator killer)
	{
		super.OnPlayerKilled(playerId, playerEntity, killerEntity, killer);
		WL_SpawnPointSelector.InvalidatePlayer(playerId);
	}
}
