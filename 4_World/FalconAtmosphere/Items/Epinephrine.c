modded class Epinephrine: Inventory_Base
{
	override void OnApply(PlayerBase player)
	{
		if( player.GetModifiersManager().IsModifierActive(eModifiers.MDF_EPINEPHRINE ) )
		{
			player.GetModifiersManager().DeactivateModifier( eModifiers.MDF_EPINEPHRINE );
			player.RemoveAgent(AtmosphereConstants.SLEEP_AGENT_ID);
		}
		player.GetModifiersManager().ActivateModifier( eModifiers.MDF_EPINEPHRINE );
	}
};