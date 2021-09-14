modded class ActionConstructor
{
	override void RegisterActions(TTypenameArray actions)
	{
		super.RegisterActions(actions);
		
		actions.Insert(ActionInjectAntiRadTarget);
		actions.Insert(ActionInjectAntiRadSelf);
		actions.Insert(ActionLightLamps);
		actions.Insert(ActionScrapPart);
		actions.Insert(ActionSearchFruit);
	}
}