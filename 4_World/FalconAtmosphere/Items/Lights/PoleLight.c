class PoleLight extends Inventory_Base
{
	private bool isOn = false;
	
	override void EEInit()
	{
		SetIsHologram(true);
	}
	
	bool getIsOn()
	{
		return isOn;
	}
	
	void switchLight()
	{
		isOn = !isOn;
		
		SetPilotLight(isOn);
	}
	
	override bool OnStoreLoad(ParamsReadContext ctx, int version)
	{
		Delete();
		
		return true;
	}
}