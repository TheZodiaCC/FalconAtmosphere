class GeigerCounter extends Inventory_Base
{
	ref EffectSound	radiationSoundEffect;
	
	override void EEInit()
	{
		super.EEInit();
		
		PlaySoundSetLoop(radiationSoundEffect, "Flies_SoundSet", 1.0, 1.0);
	}
}