class SleepMdfr extends ModifierBase
{
	override void Init()
	{
		m_TrackActivatedTime = false;
		m_ID = AtmosphereConstants.SLEEP_MDFR_ID;
		m_TickIntervalInactive = 6;
		m_TickIntervalActive = 6;
	}

	override protected bool ActivateCondition(PlayerBase player)
	{
		return true;
	}

	override protected void OnActivate(PlayerBase player)
	{
		;
	}

	override protected void OnDeactivate(PlayerBase player)
	{
		;
	}

	override protected bool DeactivateCondition(PlayerBase player)
	{
		return false;
	}

	override protected void OnTick(PlayerBase player, float deltaT)
	{
		int tiredness = player.GetSingleAgentCount(AtmosphereConstants.SLEEP_AGENT_ID);
		
		if (!player.isSleeping() && !player.IsUnconscious())
		{
			if (tiredness > 9000)
			{
				if (Math.RandomFloat(0, 4) >= 3)
				{
					player.SetHealth("", "Shock", 0);
				}
			}
		}
	}
}