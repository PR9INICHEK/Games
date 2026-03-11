//! Modded SCR_FactionPlayerLoadout — replaces the fixed loadout prefab with a
//! random pick from the faction's pool when the random loadout system is enabled.
//! Also hooks OnLoadoutSpawned to apply per-slot randomization.
modded class SCR_FactionPlayerLoadout
{
	//------------------------------------------------------------------------------------------------
	//! Factory: create a loadout instance at runtime (bypasses config serialization)
	static SCR_FactionPlayerLoadout Create(string name, ResourceName resource, string faction)
	{
		SCR_FactionPlayerLoadout loadout = new SCR_FactionPlayerLoadout();
		loadout.m_sLoadoutName = name;
		loadout.m_sLoadoutResource = resource;
		loadout.m_sAffiliatedFaction = faction;
		return loadout;
	}

	//------------------------------------------------------------------------------------------------
	override ResourceName GetLoadoutResource()
	{
		if (!WL_RandomLoadoutPool.IsEnabled())
			return super.GetLoadoutResource();

		ResourceName randomResource = WL_RandomLoadoutPool.GetRandomResource(GetFactionKey());
		if (randomResource.IsEmpty())
			return super.GetLoadoutResource();

		return randomResource;
	}

	//------------------------------------------------------------------------------------------------
	override void OnLoadoutSpawned(GenericEntity pOwner, int playerId)
	{
		super.OnLoadoutSpawned(pOwner, playerId);

		// Per-slot randomization runs server-side only
		if (WL_SlotRandomizer.IsEnabled())
			WL_SlotRandomizer.RandomizeLoadout(pOwner, GetFactionKey());
	}
}
