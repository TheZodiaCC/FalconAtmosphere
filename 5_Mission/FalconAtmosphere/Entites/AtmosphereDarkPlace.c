class AtmosphereDarkPlace
{
	private ref array<string> placePos = new array<string>;
	private float placeHeight;
	private float darkness;
	
	
	array<string> getPlacePos() {
		return placePos;
	}
	
	float getPlaceHeight()
	{
		return placeHeight;
	}
	
	float getDarkness()
	{
		return darkness;
	}
}