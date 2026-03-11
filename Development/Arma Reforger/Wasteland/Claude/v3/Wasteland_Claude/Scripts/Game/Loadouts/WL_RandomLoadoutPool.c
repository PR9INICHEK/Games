//! Manages per-faction pools of character prefabs for random loadout assignment.
//! Each faction has a curated list of infantry combat roles.
//! On spawn, a random prefab is picked from the player's faction pool.
class WL_RandomLoadoutPool
{
	protected static bool s_bEnabled;
	protected static ref map<string, ref array<ResourceName>> s_mPools;

	//------------------------------------------------------------------------------------------------
	static void SetEnabled(bool enabled)
	{
		s_bEnabled = enabled;
		PrintFormat("[WL_RandomLoadoutPool] %1", enabled ? "Enabled" : "Disabled");
	}

	//------------------------------------------------------------------------------------------------
	static bool IsEnabled()
	{
		return s_bEnabled;
	}

	//------------------------------------------------------------------------------------------------
	//! Returns a random character prefab ResourceName for the given faction.
	//! Returns empty if faction has no pool defined.
	static ResourceName GetRandomResource(string factionKey)
	{
		InitPools();

		array<ResourceName> pool;
		if (!s_mPools.Find(factionKey, pool) || pool.IsEmpty())
			return ResourceName.Empty;

		int idx = Math.RandomInt(0, pool.Count());
		return pool[idx];
	}

	//------------------------------------------------------------------------------------------------
	protected static void InitPools()
	{
		if (s_mPools)
			return;

		s_mPools = new map<string, ref array<ResourceName>>();

		// --- US (BLUFOR) ---
		array<ResourceName> us = new array<ResourceName>();
		us.Insert("{C5574DAD3956486C}Prefabs/Characters/Campaign/Final/BLUFOR/US_army/Regular/Campaign_US_Player_Rifleman.et");
		us.Insert("{33CDB2B7C3F1EB63}Prefabs/Characters/Campaign/Final/BLUFOR/US_army/Regular/Campaign_US_Player_AR.et");
		us.Insert("{3E18CC9634468249}Prefabs/Characters/Campaign/Final/BLUFOR/US_army/Regular/Campaign_US_Player_GL.et");
		us.Insert("{61DA6CADADBEFF80}Prefabs/Characters/Campaign/Final/BLUFOR/US_army/Regular/Campaign_US_Player_MG.et");
		us.Insert("{9F4976C06FD1C839}Prefabs/Characters/Campaign/Final/BLUFOR/US_army/Regular/Campaign_US_Player_LAT.et");
		us.Insert("{4357ABF9CA279803}Prefabs/Characters/Campaign/Final/BLUFOR/US_army/Regular/Campaign_US_Player_Medic.et");
		us.Insert("{E27CC9493BFAF668}Prefabs/Characters/Campaign/Final/BLUFOR/US_army/Regular/Campaign_US_Player_Sniper.et");
		s_mPools.Set("US", us);

		// --- USSR (OPFOR) ---
		array<ResourceName> ussr = new array<ResourceName>();
		ussr.Insert("{9BDC3AC0BDB50019}Prefabs/Characters/Campaign/Final/OPFOR/USSR_Army/Regular/Campaign_USSR_Player_Rifleman.et");
		ussr.Insert("{FE117C2D5326CFCB}Prefabs/Characters/Campaign/Final/OPFOR/USSR_Army/Regular/Campaign_USSR_Player_AR.et");
		ussr.Insert("{F3C4020CA491A6E1}Prefabs/Characters/Campaign/Final/OPFOR/USSR_Army/Regular/Campaign_USSR_Player_GL.et");
		ussr.Insert("{AC06A2373D69DB28}Prefabs/Characters/Campaign/Final/OPFOR/USSR_Army/Regular/Campaign_USSR_Player_MG.et");
		ussr.Insert("{26B915EC2AAFD197}Prefabs/Characters/Campaign/Final/OPFOR/USSR_Army/Regular/Campaign_USSR_Player_AT.et");
		ussr.Insert("{7A1B2C9ECC6AD565}Prefabs/Characters/Campaign/Final/OPFOR/USSR_Army/Regular/Campaign_USSR_Player_Medic.et");
		ussr.Insert("{9118454F47ED90E2}Prefabs/Characters/Campaign/Final/OPFOR/USSR_Army/Regular/Campaign_USSR_Player_Sharpshooter.et");
		s_mPools.Set("USSR", ussr);

		// --- FIA (INDFOR) ---
		array<ResourceName> fia = new array<ResourceName>();
		fia.Insert("{84B40583F4D1B7A3}Prefabs/Characters/Factions/INDFOR/FIA/Character_FIA_Rifleman.et");
		fia.Insert("{58E47E5A4D599432}Prefabs/Characters/Factions/INDFOR/FIA/Character_FIA_MG.et");
		fia.Insert("{D25BC9815A9F9E8D}Prefabs/Characters/Factions/INDFOR/FIA/Character_FIA_AT.et");
		fia.Insert("{45A02CA25CBA9443}Prefabs/Characters/Factions/INDFOR/FIA/Character_FIA_Medic.et");
		fia.Insert("{CE33AB22F61F3365}Prefabs/Characters/Factions/INDFOR/FIA/Character_FIA_Sharpshooter.et");
		s_mPools.Set("FIA", fia);
	}
}
