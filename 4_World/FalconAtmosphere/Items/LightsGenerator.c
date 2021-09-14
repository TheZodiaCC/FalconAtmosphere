class LightsGenerator extends PowerGenerator
{
	override bool CanPutInCargo( EntityAI parent )
	{
		return false;
	}

	override bool CanPutIntoHands ( EntityAI player ) 
	{
		return false;
	}
	
	override void OnWorkStart()
	{
		super.OnWorkStart();
		
		if (GetGame().IsServer())
		{
			LampsUtils.lightLampsInRange(GetPosition(), 1000);
		}
	}
	
	override void OnWorkStop()
	{
		super.OnWorkStop();
		
		if (GetGame().IsServer())
		{
			LampsUtils.lightLampsInRange(GetPosition(), 1000);
		}
	}
	
	override void EOnInit( IEntity other, int extra)
	{
		super.EOnInit(other, extra);
		
		if (GetGame().IsServer())
		{
			if (m_Smoke)
			{
				LampsUtils.lightLampsInRange(GetPosition(), 1000);
			}
		}
	}
	
	override void SetActions()
	{
		AddAction(ActionTurnOnPowerGenerator);
		AddAction(ActionTurnOffPowerGenerator);
	}
}