//! Modded SCR_LoadoutManager — injects per-faction loadouts at runtime.
//! The layer file cannot inline SCR_FactionPlayerLoadout data (script class,
//! not known to the binary entity deserializer), so we create them here.
modded class SCR_LoadoutManager
{
	//------------------------------------------------------------------------------------------------
	override void OnPostInit(IEntity owner)
	{
		super.OnPostInit(owner);

		// Only inject if the prefab has no loadouts defined
		if (m_aPlayerLoadouts && !m_aPlayerLoadouts.IsEmpty())
			return;

		if (!m_aPlayerLoadouts)
			m_aPlayerLoadouts = {};

		m_aPlayerLoadouts.Insert(
			SCR_FactionPlayerLoadout.Create("US Soldier",
				"{C5574DAD3956486C}Prefabs/Characters/Campaign/Final/BLUFOR/US_army/Regular/Campaign_US_Player_Rifleman.et",
				"US"));

		m_aPlayerLoadouts.Insert(
			SCR_FactionPlayerLoadout.Create("USSR Soldier",
				"{9BDC3AC0BDB50019}Prefabs/Characters/Campaign/Final/OPFOR/USSR_Army/Regular/Campaign_USSR_Player_Rifleman.et",
				"USSR"));

		m_aPlayerLoadouts.Insert(
			SCR_FactionPlayerLoadout.Create("FIA Fighter",
				"{84B40583F4D1B7A3}Prefabs/Characters/Factions/INDFOR/FIA/Character_FIA_Rifleman.et",
				"FIA"));

		PrintFormat("[WL_LoadoutManager] Injected %1 faction loadouts", m_aPlayerLoadouts.Count());
	}
}
