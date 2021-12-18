/*modded class Land_Power_Pole_Conc1_Amp extends PASReceiver
{
	 Object lamp;

    void EEInit()
    {
	 	super.EEInit();
		
		if (GetGame().IsServer())
		{
			lamp = GetGame().CreateObject( "PoleLight", GetPosition() );
	        lamp.SetPosition( "-0.80 4.32 1.24" );
	        
	        AddChild( lamp, -1, false );
	        Update();
	        lamp.Update();
		}
    }
}*/

modded class Land_Lamp_City1_amp extends PASReceiver
{
	Object lamp;

    override void EEInit()
    {
	 	super.EEInit();
		
		if (GetGame().IsServer())
		{
			lamp = GetGame().CreateObject( "PoleLight", GetPosition() );
	        lamp.SetPosition( "-0.8 5.075 0.2" );
	        
	        AddChild( lamp, -1, false );
	        Update();
	        lamp.Update();
		}
    }
}

modded class Land_Power_Pole_Conc4_Lamp_Amp extends PASReceiver
{
	 Object lamp;

   	override void EEInit()
    {
	 	super.EEInit();
		
		if (GetGame().IsServer())
		{
			lamp = GetGame().CreateObject( "PoleLight", GetPosition() );
	        lamp.SetPosition( "-0.8 5.075 0.2" );
	        
	        AddChild( lamp, -1, false );
	        Update();
	        lamp.Update();
		}
    }
}

modded class Land_Power_Pole_Wood1_Lamp_Amp extends PASReceiver
{
	 Object lamp;

    override void EEInit()
    {
	 	super.EEInit();
		
		if (GetGame().IsServer())
		{
			lamp = GetGame().CreateObject( "PoleLight", GetPosition() );
	        lamp.SetPosition( "-0.2 3.65 0.4" );
	        
	        AddChild( lamp, -1, false );
	        Update();
	        lamp.Update();
		}
    }
}