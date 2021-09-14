class AntiRad extends Inventory_Base
{
	override void SetActions()
	{
		super.SetActions();
		
		AddAction(ActionInjectAntiRadTarget);
		AddAction(ActionInjectAntiRadSelf);
	}
	
	override void OnApply(PlayerBase player)
	{
		player.RemoveAgent(AtmosphereConstants.RADIATION_AGENT_ID);
	}
}