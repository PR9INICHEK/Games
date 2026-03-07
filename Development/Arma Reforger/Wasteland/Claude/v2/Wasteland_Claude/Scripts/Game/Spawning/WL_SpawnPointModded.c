//! Modded SCR_SpawnPoint to limit the deploy menu to 5 weighted random locations.
//! The base class faction filter runs first, then our location filter.
//! Location index is cached per spawn point (computed once, never changes).
modded class SCR_SpawnPoint
{
	protected int m_iWL_LocationIdx = -2; // -2 = not yet computed

	//------------------------------------------------------------------------------------------------
	//! Get the cached location index for this spawn point (computed once on first call)
	int WL_GetLocationIdx()
	{
		if (m_iWL_LocationIdx == -2)
			m_iWL_LocationIdx = WL_SpawnPointSelector.FindNearestLocation(GetOrigin());

		return m_iWL_LocationIdx;
	}

	//------------------------------------------------------------------------------------------------
	override bool IsSpawnPointVisibleForPlayer(int pid)
	{
		// Base class handles faction filtering — reject wrong-faction points
		if (!super.IsSpawnPointVisibleForPlayer(pid))
			return false;

		// Additionally filter by weighted random location selection
		return WL_SpawnPointSelector.IsPointVisibleForPlayer(this, pid);
	}
}
