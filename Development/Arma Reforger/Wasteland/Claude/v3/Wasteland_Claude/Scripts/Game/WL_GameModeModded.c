//! Modded SCR_BaseGameMode — adds configurable random spawn point selection
//! and random per-faction loadout assignment.
modded class SCR_BaseGameMode
{
	[Attribute("0", UIWidgets.CheckBox, "Enable weighted random spawn point selection (show 5 of 16 locations per player, re-randomized on death)")]
	protected bool m_bWL_RandomSpawnPoints;

	[Attribute("1", UIWidgets.CheckBox, "Enable random loadout per faction (player spawns with a random combat role each life)")]
	protected bool m_bWL_RandomLoadouts;

	[Attribute("1", UIWidgets.CheckBox, "Enable per-slot loadout randomization (replaces individual equipment slots after spawn)")]
	protected bool m_bWL_SlotRandomization;

	[Attribute("", UIWidgets.ResourcePickerThumbnail, "Per-slot loadout randomization config (.conf)", "conf")]
	protected ResourceName m_sWL_LoadoutConfigPath;

	//------------------------------------------------------------------------------------------------
	void SCR_BaseGameMode(IEntitySource src, IEntity parent)
	{
		WL_SpawnPointSelector.SetEnabled(m_bWL_RandomSpawnPoints);
		WL_RandomLoadoutPool.SetEnabled(m_bWL_RandomLoadouts);

		// Per-slot randomization
		WL_SlotRandomizer.Init(m_sWL_LoadoutConfigPath);
		WL_SlotRandomizer.SetEnabled(m_bWL_SlotRandomization);
	}

	//------------------------------------------------------------------------------------------------
	override void OnPlayerKilled(int playerId, IEntity playerEntity, IEntity killerEntity, notnull Instigator killer)
	{
		super.OnPlayerKilled(playerId, playerEntity, killerEntity, killer);
		WL_SpawnPointSelector.InvalidatePlayer(playerId);
	}
}
