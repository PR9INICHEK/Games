//! Modded SCR_SpawnPoint to limit the deploy menu to 5 weighted random locations.
//! The base class faction filter runs first, then our location filter.
modded class SCR_SpawnPoint
{
	override bool IsSpawnPointVisibleForPlayer(int pid)
	{
		// Base class handles faction filtering — reject wrong-faction points
		if (!super.IsSpawnPointVisibleForPlayer(pid))
			return false;

		// Additionally filter by weighted random location selection
		return WL_SpawnPointSelector.IsPointVisibleForPlayer(this, pid);
	}
}
