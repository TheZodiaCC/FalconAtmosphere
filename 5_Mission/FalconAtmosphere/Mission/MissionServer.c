modded class MissionServer
{
	private ref array<Man> players = new array<Man>;
	private int atmosphereUpdateTick = 3;
	private int atmosphereCurrentTime;
	private int atmosphereNTime = 0;
	
	private ref array<ref AtmosphereDarkPlace> darkPlaces = new ref array<ref AtmosphereDarkPlace>();
	private ref array<ref AtmosphereRadiationPlace> radiationPlaces = new ref array<ref AtmosphereRadiationPlace>();
	
	
	void MissionServer()
	{
		darkPlaces = AtmosphereUtils.getDarkPlaces();
		radiationPlaces = AtmosphereUtils.getRadiationPlaces();
	}
	
	override void TickScheduler(float timeslice)
	{	
		super.TickScheduler(timeslice);
		
		atmosphereCurrentTime = GetGame().GetTime() * 0.001;
		
		if(atmosphereCurrentTime >= atmosphereNTime + atmosphereUpdateTick)
		{
			GetGame().GetPlayers(players);
			
			AtmosphereUtils.checkPlayersInDarkPlaces(players, darkPlaces);
			AtmosphereUtils.checkPlayersInRadiationPlaces(players, radiationPlaces);
			
			atmosphereNTime = atmosphereCurrentTime;
		}
	}
	
	override void OnMissionStart()
	{
		super.OnMissionStart();
		LampsUtils.initLamps();
	}

	//override void OnMissionLoaded()
	//{
	//	super.OnMissionLoaded();
	//	//LampsUtils.initLamps();
	//}
}