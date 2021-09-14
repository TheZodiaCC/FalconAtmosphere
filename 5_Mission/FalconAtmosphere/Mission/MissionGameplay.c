modded class MissionGameplay {	
	
	private int atmosphereUpdateTick = 1;
	private int atmosphereCurrentTime;
	private int atmosphereNTime = 0;
	private PlayerBase atmospherePlayer;
	
	
	void MissionGameplay() 
	{
		GetRPCManager().AddRPC( "FalconAtmosphere", "switchDarkC", this, SingeplayerExecutionType.Server );
		GetRPCManager().AddRPC( "FalconAtmosphere", "switchRadiationC", this, SingeplayerExecutionType.Server );
	}
	
	private void switchDarkC( CallType type, ref ParamsReadContext ctx, ref PlayerIdentity sender, ref Object target )
    {
        Param1<float> data;
        if ( !ctx.Read( data ) ) return;
        
        if( type == CallType.Client ) 
		{
			GetGame().GetWorld().SetEyeAccom(data.param1);
       	}
    }
	
	private void switchRadiationC( CallType type, ref ParamsReadContext ctx, ref PlayerIdentity sender, ref Object target )
    {
        Param1<bool> data;
        if ( !ctx.Read( data ) ) return;
        
        if( type == CallType.Client ) 
		{
			PlayerBase player = PlayerBase.Cast(GetGame().GetPlayer());

			if (data.param1)
			{
				player.startRadiationSoundEffect();
			}
			else
			{
				player.stopRadiationSoundEffect();
			}
		}
    }
	
	override void OnInit()
	{
		super.OnInit();
		
		if (m_HudRootWidget)
		{
			m_HudRootWidget.Unlink();
			m_HudRootWidget = NULL;
		}
			
		PPEffects.Init();
		MapMarkerTypes.Init();
		
		m_UIManager = GetGame().GetUIManager();
			
		m_Initialized = true;

		// init hud ui
		if ( !m_HudRootWidget )
		{
			m_HudRootWidget	= GetGame().GetWorkspace().CreateWidgets("FalconAtmosphere/GUI/Layouts/mod_day_z_hud.layout");
			
			m_HudRootWidget.Show(false);
			
			m_Chat.Init(m_HudRootWidget.FindAnyWidget("ChatFrameWidget"));
			
			m_ActionMenu.Init( m_HudRootWidget.FindAnyWidget("ActionsPanel"), TextWidget.Cast( m_HudRootWidget.FindAnyWidget("DefaultActionWidget") ) );
			
			m_Hud.Init( m_HudRootWidget.FindAnyWidget("HudPanel") );
			
			// von enabled icon
			m_MicrophoneIcon = ImageWidget.Cast( m_HudRootWidget.FindAnyWidget("mic") );
			m_MicrophoneIcon.Show(false);
			
			// von voice level
			m_VoiceLevels = m_HudRootWidget.FindAnyWidget("VoiceLevelsPanel");
			m_VoiceLevelsWidgets = new map<int, ImageWidget>; // [key] voice level
			m_VoiceLevelTimers = new map<int,ref WidgetFadeTimer>; // [key] voice level
		
			if( m_VoiceLevels )
			{
				m_VoiceLevelsWidgets.Set(VoiceLevelWhisper, ImageWidget.Cast( m_VoiceLevels.FindAnyWidget("Whisper") ));
				m_VoiceLevelsWidgets.Set(VoiceLevelTalk, ImageWidget.Cast( m_VoiceLevels.FindAnyWidget("Talk") ));
				m_VoiceLevelsWidgets.Set(VoiceLevelShout, ImageWidget.Cast( m_VoiceLevels.FindAnyWidget("Shout") ));
				
				m_VoiceLevelTimers.Set(VoiceLevelWhisper, new WidgetFadeTimer);
				m_VoiceLevelTimers.Set(VoiceLevelTalk, new WidgetFadeTimer);
				m_VoiceLevelTimers.Set(VoiceLevelShout, new WidgetFadeTimer);
			}
			
			HideVoiceLevelWidgets();
			
			// chat channel
			m_ChatChannelArea = m_HudRootWidget.FindAnyWidget("ChatChannelPanel");
			m_ChatChannelText = TextWidget.Cast( m_HudRootWidget.FindAnyWidget("ChatChannelText") );
		}
		
		// init hud ui
		if ( GetGame().IsDebug() )
		{
			m_HudDebug = new HudDebug;
			
			if ( !m_HudDebug.IsInitialized() )
			{
				m_HudDebug.Init( GetGame().GetWorkspace().CreateWidgets("gui/layouts/debug/day_z_hud_debug.layout") );
				
				PluginConfigDebugProfile.GetInstance().SetLogsEnabled(LogManager.IsLogsEnable());
			}
		}
		
		if( GetGame().IsMultiplayer() )
		{
			OnlineServices.m_MuteUpdateAsyncInvoker.Insert( SendMuteListToServer );
		}
	}
	
	override void TickScheduler(float timeslice)
	{	
		super.TickScheduler(timeslice);
		
		atmosphereCurrentTime = GetGame().GetTime() * 0.001;
		
		if (atmosphereCurrentTime >= atmosphereNTime + atmosphereUpdateTick)
		{
			atmospherePlayer = GetGame().GetPlayer();
			
			if (atmospherePlayer)
			{
				AtmosphereUtils.checkTiredness(atmospherePlayer);
			}
			
			atmosphereNTime = atmosphereCurrentTime;
		}
	}
}