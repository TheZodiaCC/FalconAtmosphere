class ActionScrapPartCB : ActionContinuousBaseCB
{
	private const float TIME_BETWEEN_MATERIAL_DROPS = AtmosphereConstants.TIME_TO_SCRAP_PART;

	override void CreateActionComponent()
	{
		m_ActionData.m_ActionComponent = new CAContinuousScrapPart(AtmosphereConstants.TIME_TO_SCRAP_PART);
	}
};

class ActionScrapPart: ActionContinuousBase
{
	void ActionScrapPart()
	{
		m_CallbackClass = ActionScrapPartCB;
		m_CommandUID = DayZPlayerConstants.CMD_ACTIONFB_MINEROCK;
		m_FullBody = true;
		m_StanceMask = DayZPlayerConstants.STANCEMASK_ERECT;
		m_SpecialtyWeight = UASoftSkillsWeight.ROUGH_HIGH;
	}
	
	override void CreateConditionComponents()  
	{		
		m_ConditionTarget = new CCTCursor(UAMaxDistances.DEFAULT);
		m_ConditionItem = new CCINonRuined;
	}

	override bool ActionCondition( PlayerBase player, ActionTarget target, ItemBase item )
	{	
		if (player.m_BrokenLegState == eBrokenLegs.BROKEN_LEGS)
		{
			return false;
		}
		
		CarDoor carDoor = CarDoor.Cast(target.GetObject());
		
		if (carDoor)
		{
			return true;
		}
		
		return false;
	}

	override string GetText()
	{
		return "Scrap";
	}
	
	override void OnFinishProgressServer( ActionData action_data )
	{	
		if (action_data)
		{
			CarDoor carDoor = CarDoor.Cast(action_data.m_Target.GetObject());
			
			if (carDoor)
			{
				array<int> chances = {0, 1};
				int chance = chances.GetRandomIndex();
				
				if (chance == 1)
				{
					MetalPlate metal = MetalPlate.Cast(GetGame().CreateObject("MetalPlate", action_data.m_Player.GetPosition(), false, false, false));
					metal.SetQuantity(1);
				}
				
				carDoor.Delete();	
			}
		}
	}
};