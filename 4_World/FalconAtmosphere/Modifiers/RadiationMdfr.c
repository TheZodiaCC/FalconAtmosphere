class RadiationMdfr extends ModifierBase
{
	static const int AGENT_THRESHOLD_ACTIVATE = 100;
	static const int AGENT_THRESHOLD_DEACTIVATE = 10;

	override void Init()
	{
		m_TrackActivatedTime = false;
		m_ID = AtmosphereConstants.RADIATION_MDFR_ID;
		m_TickIntervalInactive = 6;
		m_TickIntervalActive = 6;
	}

	override protected bool ActivateCondition(PlayerBase player)
	{
		if (player.GetSingleAgentCount(AtmosphereConstants.RADIATION_AGENT_ID) > AGENT_THRESHOLD_ACTIVATE) 
		{
			return true;
		}
		else 
		{
			return false;
		}
	}

	override protected void OnActivate(PlayerBase player)
	{
		player.IncreaseDiseaseCount();
	}

	override protected void OnDeactivate(PlayerBase player)
	{
		player.DecreaseDiseaseCount();
	}

	override protected bool DeactivateCondition(PlayerBase player)
	{
		if(player.GetSingleAgentCount(AtmosphereConstants.RADIATION_AGENT_ID) < AGENT_THRESHOLD_DEACTIVATE) 
		{
			return true;
		}
		else 
		{
			return false;
		}
	}

	override protected void OnTick(PlayerBase player, float deltaT)
	{
		float chance = Math.Lerp((float)1/25, (float)1/10, player.GetSingleAgentCountNormalized(AtmosphereConstants.RADIATION_AGENT_ID));
		
		if (Math.RandomFloat01() < chance)
		{
			SymptomBase symptom = player.GetSymptomManager().QueueUpPrimarySymptom(SymptomIDs.SYMPTOM_VOMIT);
			
			if(symptom)
			{
				symptom.SetDuration(2);
				
				int count = player.GetSingleAgentCount(AtmosphereConstants.RADIATION_AGENT_ID);
				int countMax = PluginTransmissionAgents.GetAgentMaxCount(AtmosphereConstants.RADIATION_AGENT_ID);
				float newBlood = 150;

				player.AddHealth("", "Blood", newBlood * -1);
				player.GetStatStamina().Set(0);
				
				float newWater = player.GetStatWater().Get() - 300.0;
				float newEnergy = player.GetStatEnergy().Get() - 300.0;
				
				player.GetStatEnergy().Set(newEnergy);
				player.GetStatWater().Set(newWater);
			}
		}
	}
}