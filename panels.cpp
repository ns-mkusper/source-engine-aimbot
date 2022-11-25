#include "panels.h"
#include "stdafx.h"

//------------------------------
ScreenSize_t sScreenSize;	// struct to store the screen-size
//------------------------------
//----------------------------------------------------------------------------------------------------------
CDrawLayer::CDrawLayer ( void )
{
	pDrawPanel = NULL;
}

CDrawLayer::~CDrawLayer ( void )
{
	Destroy();
}

void CDrawLayer::Create( vgui::VPANEL parent )
{
	pDrawPanel = new CDrawPanel ( parent );
}

void CDrawLayer::Destroy( void )
{
	if ( pDrawPanel )
	{
		ExitProcess( 0 );
		pDrawPanel->SetParent( (vgui::Panel *)NULL );
		delete pDrawPanel;
		pDrawPanel = NULL;
	}
}

//------------------------------------------------------------------------------------------------------------------
CDrawPanel::CDrawPanel( vgui::VPANEL parent ) : BaseClass( NULL,"DrawPanel" )
{
	SetParent( parent );	// set the parent
	SetPos( 0, 0 );			// start at the left top corner
	SetVisible( true );		// yup ... :)
	SetCursor( null );		// not needed
	HalFLife2.m_pEngineClient->GetScreenSize( sScreenSize.m_iWidth, sScreenSize.m_iHeight );
	add_log("GetScreenSize");
	SetSize( sScreenSize.m_iWidth, sScreenSize.m_iHeight );
}

void CDrawPanel::Paint( void ) 
{
	if (   !HalFLife2.m_pEngineClient->IsConnected()
		|| !HalFLife2.m_pEngineClient->IsInGame()
		|| !HalFLife2.m_pMyPlayer->BaseEnt() 
		|| HalFLife2.m_pEngineClient->Con_IsVisible() 
		|| HalFLife2.m_pEngineClient->IsLevelMainMenuBackground())
		return;

	//Now Draw The Stuff
	HalFLife2.m_pEsp->CrossHairByLix();
	HalFLife2.m_pEsp->DrawEsp();
}