modded class ModifiersManager
{
	override void Init()
	{
		super.Init();

		AddModifier(new RadiationMdfr);
		AddModifier(new SleepMdfr);
	}
}