class RadiationSounds
{
	static const ref array<string> radiationSounds = {"rad1_SoundSet", "rad2_SoundSet", "rad3_SoundSet"};
}


modded class PlayerBase
{
	private bool isInDarkPlace;
	private bool isInRadiationPlace;
	private int radiationZoneLevel;
	ref EffectSound	radiationSoundEffect;
	
	private int atmosphereUpdateTick = 1;
	private int atmosphereCurrentTime;
	private int atmosphereNTime = 0;
	
	private int tiredness;
	
	
	void PlayerBase()
	{
		RegisterNetSyncVariableInt("radiationZoneLevel");
		RegisterNetSyncVariableInt("tiredness");
	}
	
	bool getIsInDarkPlace()
	{
		return isInDarkPlace;
	}
	
	void setIsInDarkPlace(bool value)
	{
		isInDarkPlace = value;
	}
	
	bool getIsInRadiationPlace()
	{
		return isInRadiationPlace;
	}
	
	void setRadiationZoneLevel(int level)
	{
		radiationZoneLevel = level;
	}
	
	bool getRadiationZoneLevel()
	{
		return radiationZoneLevel;
	}
	
	void setIsInRadiationPlace(bool value)
	{
		isInRadiationPlace = value;
	}
	
	void startRadiationSoundEffect()
	{
		stopRadiationSoundEffect();
		
		if (radiationZoneLevel >= 0)
		{
			PlaySoundSetLoop(radiationSoundEffect, RadiationSounds.radiationSounds[radiationZoneLevel], 0.1, 0.8);
		}
	}
	
	void stopRadiationSoundEffect()
	{
		if (radiationSoundEffect)
		{
			if (radiationSoundEffect.IsSoundPlaying())
			{
				StopSoundSet(radiationSoundEffect);
			}
		}
	}
	
	int getTirednes()
	{
		return tiredness;
	}
	
	private void checkRadiation()
	{
		if (GetGame().IsServer())
		{	
			if (isInRadiationPlace)
			{
				if (!GetModifiersManager().GetModifier(AtmosphereConstants.RADIATION_MDFR_ID).IsActive())
				{
					GetModifiersManager().ActivateModifier(AtmosphereConstants.RADIATION_MDFR_ID);
				}
				
				int radiationMultiplier = Math.Pow(AtmosphereConstants.BASE_RADIATION_GAIN, radiationZoneLevel);
				int radiationGain = (AtmosphereConstants.BASE_RADIATION_GAIN * radiationMultiplier) - getRadiationResistance();
				
				if (radiationGain < 0)
				{
					radiationGain = 0;
				}

				InsertAgent(AtmosphereConstants.RADIATION_AGENT_ID, radiationGain);
			}
			//else
			//{
			//	if (GetModifiersManager().GetModifier(AtmosphereConstants.RADIATION_MDFR_ID).IsActive())
			//	{
			//		GetModifiersManager().DeactivateModifier(AtmosphereConstants.RADIATION_MDFR_ID);
			//	}
			//}
		}
	}
	
	int getRadiationResistance()
	{
		int res = 0;
		
		Clothing mask = AtmosphereHelpers.getRadiationSuitPart(this, "Mask");
		Clothing body = AtmosphereHelpers.getRadiationSuitPart(this, "Body");
		Clothing legs = AtmosphereHelpers.getRadiationSuitPart(this, "Legs");
		Clothing gloves = AtmosphereHelpers.getRadiationSuitPart(this, "Gloves");
		Clothing feet = AtmosphereHelpers.getRadiationSuitPart(this, "Feet");
		
		if (mask)
		{
			res += mask.getRadiationResistance();
		}
		
		if (body)
		{
			res += body.getRadiationResistance();
		}
	
		if (legs)
		{
			res += legs.getRadiationResistance();
		}
		
		if (gloves)
		{
			res += gloves.getRadiationResistance();
		}
		
		if (feet)
		{
			res += feet.getRadiationResistance();
		}
		
		return res;
	}
	
	bool isSleeping()
	{
		if (m_EmoteManager)
		{
			if (m_EmoteManager.m_bEmoteIsPlaying || m_EmoteManager.m_Callback)
			{
				if (m_EmoteManager.m_Callback.m_callbackID == DayZPlayerConstants.CMD_GESTUREFB_LYINGDOWN)
				{
					return true;
				}
			}
		}

		return false;
	}
	
	private void checkSleep()
	{
		if (GetGame().IsClient())
		{
			if (isSleeping())
			{
				PPEffects.EnableBurlapSackBlindness();
			}
			else
			{
				PPEffects.DisableBurlapSackBlindness();
			}
		}
	}
	
	private void insertTiredness()
	{
		if (GetGame().IsServer())
		{	
			if (!isSleeping() && !IsUnconscious())
			{
				InsertAgent(AtmosphereConstants.SLEEP_AGENT_ID, AtmosphereConstants.BASE_TIREDNESS_GAIN);
			}
			else
			{
				int reductionValue = AtmosphereConstants.SLEEP_TIREDNESS_REDUCTION;
				
				if (AtmosphereHelpers.checkIfCloseToFirePlace(GetPosition()))
				{
					reductionValue = reductionValue * AtmosphereConstants.FIREPLACE_TIREDNESS_REDUCTION_MULTIPLIER;
				}

				InsertAgent(AtmosphereConstants.SLEEP_AGENT_ID, -1 * reductionValue);
			}
		}
	}
	
	private void updateTiredness()
	{
		if (GetGame().IsServer())
		{
			tiredness = GetSingleAgentCount(AtmosphereConstants.SLEEP_AGENT_ID);
		}	
	}
	
	override void OnScheduledTick(float deltaTime)
	{
		super.OnScheduledTick(deltaTime);

		atmosphereCurrentTime = GetGame().GetTime() * 0.001;
		
		if(atmosphereCurrentTime >= atmosphereNTime + atmosphereUpdateTick)
		{
			checkRadiation();
			checkSleep();
			insertTiredness();
			updateTiredness();
			
			atmosphereNTime = atmosphereCurrentTime;
		}
	}
	
	override void SetActions(out TInputActionMap InputActionMap)
	{
		super.SetActions(InputActionMap);
		
		AddAction(ActionSearchFruit, InputActionMap);
	}
}