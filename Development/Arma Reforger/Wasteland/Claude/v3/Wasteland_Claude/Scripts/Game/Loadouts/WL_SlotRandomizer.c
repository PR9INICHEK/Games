//! Static utility class that randomizes character equipment slots after spawn.
//! Reads WL_RandomLoadoutConfig from a .conf file, picks weighted-random items
//! per slot, and replaces them on the spawned character.
class WL_SlotRandomizer
{
	protected static bool s_bEnabled;
	protected static ref WL_RandomLoadoutConfig s_Config;
	protected static ref map<string, ref WL_FactionLoadoutConfig> s_mFactionConfigs;

	//------------------------------------------------------------------------------------------------
	static void Init(ResourceName configPath)
	{
		s_mFactionConfigs = new map<string, ref WL_FactionLoadoutConfig>();
		s_Config = null;

		if (configPath.IsEmpty())
		{
			PrintFormat("[WL_SlotRandomizer] No config path specified, slot randomization disabled");
			return;
		}

		Resource res = BaseContainerTools.LoadContainer(configPath);
		if (!res || !res.IsValid())
		{
			PrintFormat("[WL_SlotRandomizer] Failed to load config: %1", configPath);
			return;
		}

		BaseContainer container = res.GetResource().ToBaseContainer();
		if (!container)
		{
			PrintFormat("[WL_SlotRandomizer] Failed to get container from: %1", configPath);
			return;
		}

		s_Config = WL_RandomLoadoutConfig.Cast(BaseContainerTools.CreateInstanceFromContainer(container));
		if (!s_Config)
		{
			PrintFormat("[WL_SlotRandomizer] Failed to create config instance from: %1", configPath);
			return;
		}

		// Build faction lookup
		if (s_Config.m_aFactions)
		{
			foreach (WL_FactionLoadoutConfig factionCfg : s_Config.m_aFactions)
			{
				if (factionCfg && !factionCfg.m_sFactionKey.IsEmpty())
					s_mFactionConfigs.Set(factionCfg.m_sFactionKey, factionCfg);
			}
		}

		PrintFormat("[WL_SlotRandomizer] Loaded config with %1 factions", s_mFactionConfigs.Count());
	}

	//------------------------------------------------------------------------------------------------
	static void SetEnabled(bool enabled)
	{
		s_bEnabled = enabled;
		PrintFormat("[WL_SlotRandomizer] %1", enabled ? "Enabled" : "Disabled");
	}

	//------------------------------------------------------------------------------------------------
	static bool IsEnabled()
	{
		return s_bEnabled && s_Config;
	}

	//------------------------------------------------------------------------------------------------
	//! Main entry point: randomize all configured slots on a spawned character.
	//! Must be called server-side only.
	static void RandomizeLoadout(IEntity entity, string factionKey)
	{
		if (!entity || factionKey.IsEmpty())
			return;

		WL_FactionLoadoutConfig factionCfg;
		if (!s_mFactionConfigs.Find(factionKey, factionCfg))
		{
			PrintFormat("[WL_SlotRandomizer] No config for faction: %1", factionKey);
			return;
		}

		if (!factionCfg.m_aSlots || factionCfg.m_aSlots.IsEmpty())
			return;

		InventoryStorageManagerComponent invMgr = InventoryStorageManagerComponent.Cast(
			entity.FindComponent(InventoryStorageManagerComponent)
		);
		if (!invMgr)
		{
			PrintFormat("[WL_SlotRandomizer] No InventoryStorageManagerComponent on entity");
			return;
		}

		EquipedLoadoutStorageComponent loadoutStorage = EquipedLoadoutStorageComponent.Cast(
			entity.FindComponent(EquipedLoadoutStorageComponent)
		);

		foreach (WL_SlotPool slotPool : factionCfg.m_aSlots)
		{
			if (!slotPool || !slotPool.m_bEnabled || !slotPool.m_aItems || slotPool.m_aItems.IsEmpty())
				continue;

			switch (slotPool.m_eAreaType)
			{
				case EWL_LoadoutArea.Weapon:
					RandomizeWeaponSlot(entity, invMgr, slotPool, 0);
					break;
				case EWL_LoadoutArea.Handgun:
					RandomizeWeaponSlot(entity, invMgr, slotPool, 1);
					break;
				case EWL_LoadoutArea.Vest:
					RandomizeClothSlot(invMgr, loadoutStorage, slotPool, LoadoutArmoredVestSlotArea);
					break;
				case EWL_LoadoutArea.Helmet:
					RandomizeClothSlot(invMgr, loadoutStorage, slotPool, LoadoutHeadCoverArea);
					break;
				case EWL_LoadoutArea.Backpack:
					RandomizeClothSlot(invMgr, loadoutStorage, slotPool, LoadoutBackpackArea);
					break;
			}
		}
	}

	//------------------------------------------------------------------------------------------------
	//! Randomize a clothing/armor slot (vest, helmet, backpack).
	protected static void RandomizeClothSlot(InventoryStorageManagerComponent invMgr,
		EquipedLoadoutStorageComponent loadoutStorage, WL_SlotPool slotPool, typename areaType)
	{
		if (!loadoutStorage)
			return;

		// Remove current item in this slot
		IEntity currentItem = loadoutStorage.GetClothFromArea(areaType);
		if (currentItem)
			invMgr.TryDeleteItem(currentItem);

		// Pick new item
		ResourceName pickedPrefab = PickWeightedPrefab(slotPool);
		if (pickedPrefab.IsEmpty())
			return; // Empty prefab = no item in this slot (intentional)

		// Spawn directly into inventory — engine finds the correct loadout slot
		invMgr.TrySpawnPrefabToStorage(pickedPrefab);
	}

	//------------------------------------------------------------------------------------------------
	//! Randomize a weapon slot (primary weapon at index 0, handgun at index 1).
	protected static void RandomizeWeaponSlot(IEntity entity, InventoryStorageManagerComponent invMgr,
		WL_SlotPool slotPool, int weaponSlotIndex)
	{
		// Get weapon storage
		EquipedWeaponStorageComponent weaponStorage = EquipedWeaponStorageComponent.Cast(
			entity.FindComponent(EquipedWeaponStorageComponent)
		);
		if (!weaponStorage)
			return;

		// Remove current weapon at this slot index
		int slotCount = weaponStorage.GetSlotsCount();
		if (weaponSlotIndex < slotCount)
		{
			IEntity currentWeapon = weaponStorage.Get(weaponSlotIndex);
			if (currentWeapon)
				invMgr.TryDeleteItem(currentWeapon);
		}

		// Pick new weapon (with attachment data)
		WL_WeightedItem pickedItem = PickWeightedItemFull(slotPool);
		if (!pickedItem || pickedItem.m_sPrefab.IsEmpty())
			return; // Empty = no weapon in this slot

		// Spawn weapon directly into weapon storage
		if (!invMgr.TrySpawnPrefabToStorage(pickedItem.m_sPrefab, weaponStorage))
		{
			PrintFormat("[WL_SlotRandomizer] Failed to spawn weapon %1 into storage", pickedItem.m_sPrefab);
			return;
		}

		// Spawn attachments (magazines) into the newly created weapon
		if (!pickedItem.m_aAttachments || pickedItem.m_aAttachments.IsEmpty())
			return;

		// Find the weapon entity we just inserted
		IEntity newWeapon = weaponStorage.Get(weaponSlotIndex);
		if (!newWeapon)
			return;

		SpawnAttachments(invMgr, newWeapon, pickedItem.m_aAttachments);
	}

	//------------------------------------------------------------------------------------------------
	//! Spawn attachments (magazines, optics) into a weapon's sub-storages.
	protected static void SpawnAttachments(InventoryStorageManagerComponent invMgr, IEntity parentItem,
		array<ref WL_WeightedItem> attachments)
	{
		foreach (WL_WeightedItem attachDef : attachments)
		{
			if (!attachDef || attachDef.m_sPrefab.IsEmpty())
				continue;

			// TrySpawnPrefabToStorage with null storage auto-finds a suitable slot
			// We need to find the weapon's own storage manager or use the parent inv manager
			// Since the weapon is already in the character inventory, spawning into weapon sub-storage:
			InventoryStorageManagerComponent weaponInvMgr = InventoryStorageManagerComponent.Cast(
				parentItem.FindComponent(InventoryStorageManagerComponent)
			);

			if (weaponInvMgr)
			{
				// Weapon has its own storage manager — spawn into it
				weaponInvMgr.TrySpawnPrefabToStorage(attachDef.m_sPrefab);
			}
			else
			{
				// Fallback: try to find a storage component on the weapon and use the character's inv manager
				BaseInventoryStorageComponent weaponSubStorage = BaseInventoryStorageComponent.Cast(
					parentItem.FindComponent(BaseInventoryStorageComponent)
				);

				if (weaponSubStorage)
					invMgr.TrySpawnPrefabToStorage(attachDef.m_sPrefab, weaponSubStorage);
				else
					invMgr.TrySpawnPrefabToStorage(attachDef.m_sPrefab);
			}
		}
	}

	//------------------------------------------------------------------------------------------------
	//! Pick a random ResourceName from a slot pool using weights.
	static ResourceName PickWeightedPrefab(WL_SlotPool slotPool)
	{
		WL_WeightedItem item = PickWeightedItemFull(slotPool);
		if (!item)
			return ResourceName.Empty;

		return item.m_sPrefab;
	}

	//------------------------------------------------------------------------------------------------
	//! Pick a random WL_WeightedItem from a slot pool (includes attachment data).
	protected static WL_WeightedItem PickWeightedItemFull(WL_SlotPool slotPool)
	{
		if (!slotPool || !slotPool.m_aItems || slotPool.m_aItems.IsEmpty())
			return null;

		// Calculate total weight
		float totalWeight = 0;
		foreach (WL_WeightedItem item : slotPool.m_aItems)
		{
			if (item)
				totalWeight += item.m_fWeight;
		}

		if (totalWeight <= 0)
			return null;

		// Weighted random selection
		float roll = Math.RandomFloat(0, totalWeight);
		float cumulative = 0;
		foreach (WL_WeightedItem item : slotPool.m_aItems)
		{
			if (!item)
				continue;

			cumulative += item.m_fWeight;
			if (roll < cumulative)
				return item;
		}

		// Fallback to last item (floating point edge case)
		return slotPool.m_aItems[slotPool.m_aItems.Count() - 1];
	}
}
