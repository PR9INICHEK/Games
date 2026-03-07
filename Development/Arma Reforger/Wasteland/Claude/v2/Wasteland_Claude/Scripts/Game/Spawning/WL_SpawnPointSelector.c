//! Defines a known map location with a spawn weight for weighted random selection
class WL_LocationDef
{
	string m_sName;
	float m_fX;
	float m_fZ;
	float m_fWeight;

	void WL_LocationDef(string name, float x, float z, float weight)
	{
		m_sName = name;
		m_fX = x;
		m_fZ = z;
		m_fWeight = weight;
	}
}

//! Manages weighted random spawn point selection per player.
//! Shows only 5 of 16 locations in the deploy menu, weighted by importance.
//! Re-randomizes on each death.
class WL_SpawnPointSelector
{
	static const int VISIBLE_COUNT = 5;

	protected static ref array<ref WL_LocationDef> s_aLocations;
	protected static ref map<int, ref array<int>> s_mPlayerLocations; // pid -> allowed location indices
	protected static ref map<int, bool> s_mPlayerWasAlive;           // pid -> seen alive since cache built

	//------------------------------------------------------------------------------------------------
	//! Initialize the 16 location definitions with weights
	protected static void InitLocations()
	{
		if (s_aLocations)
			return;

		s_aLocations = new array<ref WL_LocationDef>();

		// Weight 3: Major towns and strategic points
		s_aLocations.Insert(new WL_LocationDef("Arleville",        2777, 1623, 3));
		s_aLocations.Insert(new WL_LocationDef("Beauregard",       3165, 2787, 3));
		s_aLocations.Insert(new WL_LocationDef("Airbase",          1366, 2939, 3));

		// Weight 2: Military / industrial areas
		s_aLocations.Insert(new WL_LocationDef("MilitaryBase",     1389, 2376, 2));
		s_aLocations.Insert(new WL_LocationDef("Harbor",           1166, 3311, 2));
		s_aLocations.Insert(new WL_LocationDef("TrainingArea",     1414, 1836, 2));
		s_aLocations.Insert(new WL_LocationDef("SignalHill",       2509, 2260, 2));

		// Weight 1: Remote POIs
		s_aLocations.Insert(new WL_LocationDef("MossHill",         2384, 1298, 1));
		s_aLocations.Insert(new WL_LocationDef("BaldRidge",        1979, 1135, 1));
		s_aLocations.Insert(new WL_LocationDef("TimberRidge",      2646, 2634, 1));
		s_aLocations.Insert(new WL_LocationDef("NorthHead",        2044, 3396, 1));
		s_aLocations.Insert(new WL_LocationDef("AnglerBluff",      1337, 1934, 1));
		s_aLocations.Insert(new WL_LocationDef("Highfield",        2602, 1833, 1));
		s_aLocations.Insert(new WL_LocationDef("Newfield",         2008, 2888, 1));
		s_aLocations.Insert(new WL_LocationDef("WickPoint",        3665, 2720, 1));
		s_aLocations.Insert(new WL_LocationDef("ArlevilleHeights", 3360, 1540, 1));
	}

	//------------------------------------------------------------------------------------------------
	//! Find the nearest known location index for a world position (2D distance)
	protected static int FindNearestLocation(vector pos)
	{
		InitLocations();

		float bestDistSq = 999999999;
		int bestIdx = -1;

		for (int i = 0; i < s_aLocations.Count(); i++)
		{
			WL_LocationDef loc = s_aLocations[i];
			float dx = pos[0] - loc.m_fX;
			float dz = pos[2] - loc.m_fZ;
			float distSq = dx * dx + dz * dz;

			if (distSq < bestDistSq)
			{
				bestDistSq = distSq;
				bestIdx = i;
			}
		}

		return bestIdx;
	}

	//------------------------------------------------------------------------------------------------
	//! Check if a spawn point should be visible for a player in the deploy menu.
	//! Called from modded SCR_SpawnPoint after the base faction filter passes.
	static bool IsPointVisibleForPlayer(SCR_SpawnPoint point, int pid)
	{
		// Only filter for the local player (client-side UI filtering only)
		PlayerController pc = GetGame().GetPlayerController();
		if (!pc || pc.GetPlayerId() != pid)
			return true;

		// Detect death to invalidate stale cache
		DetectPlayerDeath(pid);

		// Build cache on first access
		if (!s_mPlayerLocations || !s_mPlayerLocations.Contains(pid))
			BuildCacheForPlayer(pid);

		// Find which location this spawn point belongs to
		int locIdx = FindNearestLocation(point.GetOrigin());
		if (locIdx < 0)
			return true;

		// Check if this location is in the player's randomly selected set
		array<int> allowed;
		if (!s_mPlayerLocations || !s_mPlayerLocations.Find(pid, allowed))
			return true;

		return allowed.Find(locIdx) != -1;
	}

	//------------------------------------------------------------------------------------------------
	//! Detect if the player died since the cache was built.
	//! When a player had an alive entity but now has none, they died — invalidate cache.
	protected static void DetectPlayerDeath(int pid)
	{
		if (!s_mPlayerLocations || !s_mPlayerLocations.Contains(pid))
			return;

		IEntity controlled = GetGame().GetPlayerManager().GetPlayerControlledEntity(pid);

		if (controlled)
		{
			// Player is alive — track this so we can detect subsequent death
			if (!s_mPlayerWasAlive)
				s_mPlayerWasAlive = new map<int, bool>();

			s_mPlayerWasAlive.Set(pid, true);
			return;
		}

		// Player has no controlled entity — if they were alive before, they died
		bool wasAlive;
		if (s_mPlayerWasAlive && s_mPlayerWasAlive.Find(pid, wasAlive) && wasAlive)
			InvalidatePlayer(pid);
	}

	//------------------------------------------------------------------------------------------------
	//! Invalidate the spawn point cache for a player (called on death)
	static void InvalidatePlayer(int pid)
	{
		if (s_mPlayerLocations)
			s_mPlayerLocations.Remove(pid);

		if (s_mPlayerWasAlive)
			s_mPlayerWasAlive.Set(pid, false);
	}

	//------------------------------------------------------------------------------------------------
	//! Build a fresh weighted random selection of locations for a player
	protected static void BuildCacheForPlayer(int pid)
	{
		InitLocations();

		if (!s_mPlayerLocations)
			s_mPlayerLocations = new map<int, ref array<int>>();
		if (!s_mPlayerWasAlive)
			s_mPlayerWasAlive = new map<int, bool>();

		// All 16 locations are candidates (every location has all 3 faction spawn points)
		array<int> candidates = new array<int>();
		array<float> weights = new array<float>();
		float totalWeight = 0;

		int locCount = s_aLocations.Count();
		for (int i = 0; i < locCount; i++)
		{
			candidates.Insert(i);
			float w = s_aLocations[i].m_fWeight;
			weights.Insert(w);
			totalWeight += w;
		}

		// Weighted random pick of VISIBLE_COUNT locations without replacement
		int pickCount = VISIBLE_COUNT;
		if (locCount < pickCount)
			pickCount = locCount;

		array<int> picked = new array<int>();

		for (int p = 0; p < pickCount; p++)
		{
			if (totalWeight <= 0)
				break;

			float roll = Math.RandomFloat(0, totalWeight);
			float cumulative = 0;

			for (int j = 0; j < candidates.Count(); j++)
			{
				cumulative += weights[j];
				if (cumulative >= roll || j == candidates.Count() - 1)
				{
					picked.Insert(candidates[j]);
					totalWeight -= weights[j];
					candidates.Remove(j);
					weights.Remove(j);
					break;
				}
			}
		}

		s_mPlayerLocations.Set(pid, picked);
		s_mPlayerWasAlive.Set(pid, false);

		// Debug log
		string names = "";
		for (int k = 0; k < picked.Count(); k++)
		{
			if (k > 0)
				names += ", ";
			names += s_aLocations[picked[k]].m_sName;
		}
		PrintFormat("[WL_SpawnPointSelector] Player %1: %2", pid, names);
	}
}
