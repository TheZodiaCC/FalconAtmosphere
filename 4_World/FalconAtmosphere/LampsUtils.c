class LampsUtils
{
	static private void setupLamp(Object obj)
	{
		Object lamp;
		
		lamp = GetGame().CreateObject( "PoleLight", obj.GetPosition() );
	    lamp.SetPosition( "-0.8 5.075 0.2" );
	        
	    obj.AddChild( lamp, -1, false );
	    obj.Update();
	    lamp.Update();
	}
	
	static void initLamps()
	{
		vector center = "8600 465 9225";
		array<Object> allWorldObjects = new array<Object>();
		
		
		GetGame().GetObjectsAtPosition3D(center, 40000, allWorldObjects, null);
		
		for (int i = 0; i < allWorldObjects.Count(); i++)
		{
			if (allWorldObjects[i].ClassName().Contains("Static_Lamp"))
			{
				setupLamp(allWorldObjects[i]);
			}
		}
		
		allWorldObjects.Clear();
	}
	
	static void lightLampsInRange(vector position, float range)
	{
		array<Object> allWorldObjects = new array<Object>();
		PoleLight light;
		
		GetGame().GetObjectsAtPosition3D(position, range, allWorldObjects, null);
		
		for (int i = 0; i < allWorldObjects.Count(); i++)
		{
			if (allWorldObjects[i].ClassName() == "PoleLight")
			{
				light = PoleLight.Cast(allWorldObjects[i]);
				
				light.switchLight();
			}
		}
	}
}