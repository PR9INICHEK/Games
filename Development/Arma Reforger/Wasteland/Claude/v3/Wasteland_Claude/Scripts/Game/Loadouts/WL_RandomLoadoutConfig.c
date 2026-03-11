//! Data classes for per-slot loadout randomization config (.conf).
//! Hierarchy: WL_RandomLoadoutConfig → WL_FactionLoadoutConfig → WL_SlotPool → WL_WeightedItem

//! Which equipment area a slot pool targets.
enum EWL_LoadoutArea
{
	Weapon,
	Handgun,
	Vest,
	Helmet,
	Backpack
}

//------------------------------------------------------------------------------------------------
//! A single item entry with a weight for weighted random selection.
//! Can optionally contain attachments (e.g. magazines for weapons).
[BaseContainerProps(description: "Single item with weight")]
class WL_WeightedItem
{
	[Attribute("", UIWidgets.ResourcePickerThumbnail, "Item prefab (.et)", "et")]
	ResourceName m_sPrefab;

	[Attribute("1", UIWidgets.Auto, "Selection weight (higher = more likely)")]
	float m_fWeight;

	[Attribute("", UIWidgets.Auto, "Attachments to spawn with this item (magazines, optics)")]
	ref array<ref WL_WeightedItem> m_aAttachments;
}

//------------------------------------------------------------------------------------------------
//! Pool of items for one equipment slot.
[BaseContainerProps(description: "Item pool for one equipment slot")]
class WL_SlotPool
{
	[Attribute("", UIWidgets.Auto, "Slot display name (for debugging)")]
	string m_sSlotName;

	[Attribute("0", UIWidgets.ComboBox, "Target equipment area", enums: ParamEnumArray.FromEnum(EWL_LoadoutArea))]
	EWL_LoadoutArea m_eAreaType;

	[Attribute("1", UIWidgets.CheckBox, "Enable this slot for randomization")]
	bool m_bEnabled;

	[Attribute("", UIWidgets.Auto, "Items in this slot's pool")]
	ref array<ref WL_WeightedItem> m_aItems;
}

//------------------------------------------------------------------------------------------------
//! Loadout configuration for one faction.
[BaseContainerProps(description: "Per-faction loadout randomization config")]
class WL_FactionLoadoutConfig
{
	[Attribute("", UIWidgets.Auto, "Faction key (US, USSR, FIA)")]
	string m_sFactionKey;

	[Attribute("", UIWidgets.Auto, "Equipment slots to randomize")]
	ref array<ref WL_SlotPool> m_aSlots;
}

//------------------------------------------------------------------------------------------------
//! Root config for all faction loadout randomization data.
[BaseContainerProps(configRoot: true, description: "Wasteland per-slot loadout randomization config")]
class WL_RandomLoadoutConfig
{
	[Attribute("", UIWidgets.Auto, "Faction loadout configs")]
	ref array<ref WL_FactionLoadoutConfig> m_aFactions;
}
