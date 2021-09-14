modded class IngameHud extends Hud
{
	override void Init( Widget hud_panel_widget )
	{
		super.Init(hud_panel_widget);
		
		m_StatesWidgetNames.Set( AtmosphereConstants.SLEEP_ICON_ID, "Sleep" );
		//ImageWidget w;
		
		//ImageWidget w = m_Notifiers.FindAnyWidget("IconSleep");
		
		// clear all arrows
		//for ( int x = 1; x < 4; x++ )
		//{
		//	Class.CastTo(w,  m_Notifiers.FindAnyWidget( String( "SleepArrowUp" + x.ToString() ) ) );
		//	w.Show( false );
		//	Class.CastTo(w,  m_Notifiers.FindAnyWidget( String( "SleepArrowDown" + x.ToString() ) ) );
		//	w.Show( false );
		//}
		
		//DisplayTendencyNormal(17, 0, 3);
	}
}
