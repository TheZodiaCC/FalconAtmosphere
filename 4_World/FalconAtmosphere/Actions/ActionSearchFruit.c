class ActionSearchFruitCB : ActionContinuousBaseCB
{
	override void CreateActionComponent()
	{
		m_ActionData.m_ActionComponent = new CAContinuousTime(AtmosphereConstants.TIME_TO_SEARCH_FRUIT);
	}
};

class ActionSearchFruit: ActionContinuousBase
{
	void ActionSearchFruit()
	{
		m_CallbackClass = ActionSearchFruitCB;
		m_CommandUID = DayZPlayerConstants.CMD_ACTIONFB_INTERACT;
		m_FullBody = true;
		m_StanceMask = DayZPlayerConstants.STANCEMASK_ERECT;
		
		m_SpecialtyWeight = UASoftSkillsWeight.ROUGH_HIGH;
	}
	
	override void CreateConditionComponents()  
	{
		m_ConditionItem = new CCINone;
		m_ConditionTarget = new CCTNonRuined(UAMaxDistances.BASEBUILDING);
	}
		
	override string GetText()
	{
		return "Search tree";
	}

	override bool ActionCondition( PlayerBase player, ActionTarget target, ItemBase item )
	{	
		Object targetObject = target.GetObject();
		
		if (targetObject && targetObject.ClassName().Contains("TreeSoft_t_malusDomestica_"))
		{
			return true;
		}
		
		return false;
	}
		
	override void OnFinishProgressServer(ActionData action_data)
	{	
		array<int> chances = {0, 1, 2};
		int chance = chances.GetRandomIndex();
				
		if (chance == 1)
		{
			GetGame().CreateObject("Apple", action_data.m_Player.GetPosition(), false, false, false);
		}
	}
}