class AtmosphereHelpers
{
	
	private static array<string> getClothingParts()
	{
		array<string> bodyParts = new array<string>();
		
		bodyParts.Insert("Body");
		bodyParts.Insert("Legs");
		bodyParts.Insert("Mask");
		bodyParts.Insert("Gloves");
		bodyParts.Insert("Feet");
		
		return bodyParts;
	}
	
	static Clothing getRadiationSuitPart(PlayerBase player, string bodyPart)
	{
		array<string> bodyParts = new array<string>();
		bodyParts = getClothingParts();
		
		if (player.GetInventory().FindAttachmentByName(bodyPart))
		{
			Clothing clothing = player.GetInventory().FindAttachmentByName(bodyPart);
			
			if (clothing.IsInherited(Clothing))
			{
				return clothing;
			}
		
		}
		
		return null;
	}
	
	static bool checkIfCloseToFirePlace(vector playerPosition)
	{
		array<Object> objects = new array<Object>();
		Fireplace fireplace;
		
		GetGame().GetObjectsAtPosition(playerPosition, AtmosphereConstants.FIREPLACE_DISTANCE_THRESHOLD, objects, null);
		
		for (int i = 0; i < objects.Count(); i++)
		{
			if (objects[i].IsInherited(Fireplace))
			{
				fireplace = Fireplace.Cast(objects[i]);
				
				if (fireplace.IsBurning())
				{
					return true;
				}
			}
		}
		
		return false;
	}
}