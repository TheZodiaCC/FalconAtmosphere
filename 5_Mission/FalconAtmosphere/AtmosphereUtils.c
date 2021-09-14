class AtmosphereUtils
{	
	const static string darkPlacesDataPath = "$profile:/FValues/FAtmosphereDarkPlaces.json";	
	const static string radiationPlacesDataPath = "$profile:/FValues/FAtmosphereRadiationPlaces.json";
	
	static ref array<ref AtmosphereDarkPlace> getDarkPlaces() 
	{
		ref array<ref AtmosphereDarkPlace> darkPlaces = new ref array<ref AtmosphereDarkPlace>();
		
		JsonFileLoader<ref array<ref AtmosphereDarkPlace>>.JsonLoadFile(darkPlacesDataPath, darkPlaces);
		
		return darkPlaces;
	}
	
	static ref array<ref AtmosphereRadiationPlace> getRadiationPlaces() 
	{
		ref array<ref AtmosphereRadiationPlace> radiationPlaces = new ref array<ref AtmosphereRadiationPlace>();
		
		JsonFileLoader<ref array<ref AtmosphereRadiationPlace>>.JsonLoadFile(radiationPlacesDataPath, radiationPlaces);
		
		return radiationPlaces;
	}
	
	static bool isInBbox(AtmosphereDarkPlace darkPlace, vector objectPos)
	{
		array<string> placePos = new array<string>();
		placePos = darkPlace.getPlacePos();
		
		vector tl = placePos[0].ToVector();
		vector br = placePos[1].ToVector();
		float height = darkPlace.getPlaceHeight();
		
		//Place cords
		float tlx = tl[0];
		float tly = tl[2];
		float tlz = tl[1];
		
		float brx = br[0];
		float bry = br[2];
		
		//Object cords
		float x = objectPos[0];
		float y = objectPos[2];
		float z = objectPos[1];
		
		if ((z > tlz) && (z < height))
		{
			if ((x < tlx) && (y > tly))
			{
				if ((x > brx) && (y < bry))
				{
					return true;
				}
			}
		}
		
		return false;
	}
	
	static void checkPlayersInDarkPlaces(array<Man> players, array<ref AtmosphereDarkPlace> darkPlaces) 
	{
		PlayerBase player;
		AtmosphereDarkPlace darkPlace;
		int placesCount = 0;
		
		for (int i = 0; i < players.Count(); i++)
		{
			player = PlayerBase.Cast(players.Get(i));
			
			for (int j = 0; j< darkPlaces.Count(); j++)
			{
				darkPlace = darkPlaces.Get(j);

				if (isInBbox(darkPlace, player.GetPosition())) 
				{
					player.setIsInDarkPlace(true);
					placesCount++;
					
					GetRPCManager().SendRPC( "FalconAtmosphere", "switchDarkC", new Param1<float>(darkPlace.getDarkness()), true, player.GetIdentity());
					
					break;
				}
			}
			
			if (player.getIsInDarkPlace() && (placesCount == 0)) 
			{
				player.setIsInDarkPlace(false);			
	
				GetRPCManager().SendRPC( "FalconAtmosphere", "switchDarkC", new Param1<float>(1), true, player.GetIdentity());
			}
		}
	}

	static void checkPlayersInRadiationPlaces(array<Man> players, array<ref AtmosphereRadiationPlace> radiationPlaces) 
	{
		float playerRadiationPlaceDistance;
		
		PlayerBase player;
		AtmosphereRadiationPlace radiationPlace;
		
		for (int i = 0; i < players.Count(); i++)
		{
			player = PlayerBase.Cast(players.Get(i));
			
			for (int j = 0; j < radiationPlaces.Count(); j++)
			{
				radiationPlace = radiationPlaces.Get(j);
				
				//Need some tweaks but it works
				
				//High
				if (vector.Distance(radiationPlace.getPlacePos().ToVector(), player.GetPosition()) <= radiationPlace.getPlaceRadiusHigh()) 
				{
					player.setIsInRadiationPlace(true);
					player.setRadiationZoneLevel(2);
					
					GetRPCManager().SendRPC( "FalconAtmosphere", "switchRadiationC", new Param1<bool>(true), true, player.GetIdentity());
				}
				
				//Medium
				else if (vector.Distance(radiationPlace.getPlacePos().ToVector(), player.GetPosition()) <= radiationPlace.getPlaceRadiusMedium()) 
				{
					player.setIsInRadiationPlace(true);
					player.setRadiationZoneLevel(1);
					
					GetRPCManager().SendRPC( "FalconAtmosphere", "switchRadiationC", new Param1<bool>(true), true, player.GetIdentity());
				}
				
				//Low
				else if (vector.Distance(radiationPlace.getPlacePos().ToVector(), player.GetPosition()) <= radiationPlace.getPlaceRadiusLow()) 
				{
					player.setIsInRadiationPlace(true);
					player.setRadiationZoneLevel(0);
					
					GetRPCManager().SendRPC( "FalconAtmosphere", "switchRadiationC", new Param1<bool>(true), true, player.GetIdentity());
				}
				
				else
				{
					if (player.getIsInRadiationPlace()) 
					{
						player.setIsInRadiationPlace(false);
						player.setRadiationZoneLevel(-1);
						
						GetRPCManager().SendRPC( "FalconAtmosphere", "switchRadiationC", new Param1<bool>(false), true, player.GetIdentity());
					}
				}
			}
		}
	}
	
	private static int getPerc(int perc, int full)
	{
		int percValue = full / 100 * perc;
		
		return percValue;
	}
	
	static void checkTiredness(PlayerBase player)
	{
		int tiredness = player.getTirednes();
		
		IngameHud hud = IngameHud.Cast(GetGame().GetMission().GetHud());
				
		if (tiredness.InRange(getPerc(0, AtmosphereConstants.TIREDNESS_MAX_COUNT), getPerc(50, AtmosphereConstants.TIREDNESS_MAX_COUNT)))
		{
			hud.DisplayTendencyNormal(AtmosphereConstants.SLEEP_ICON_ID, 0, 1);
		}
		
		else if (tiredness.InRange(getPerc(50, AtmosphereConstants.TIREDNESS_MAX_COUNT) + 1, getPerc(75, AtmosphereConstants.TIREDNESS_MAX_COUNT)))
		{
			hud.DisplayTendencyNormal(AtmosphereConstants.SLEEP_ICON_ID, 0, 3);
		}
		
		else if (tiredness.InRange(getPerc(75, AtmosphereConstants.TIREDNESS_MAX_COUNT) + 1, getPerc(90, AtmosphereConstants.TIREDNESS_MAX_COUNT)))
		{
			hud.DisplayTendencyNormal(AtmosphereConstants.SLEEP_ICON_ID, 0, 4);
		}
		
		else
		{
			hud.DisplayTendencyNormal(AtmosphereConstants.SLEEP_ICON_ID, 0, 5);
		}
	}
}