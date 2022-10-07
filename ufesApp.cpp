/***************************************************************
 * Name:      ufesApp.cpp
 * Purpose:   Code for Application Class
 * Author:    Fernando Menandro (menandro@ct.ufes.br)
 * Created:   2015-03-12
 * Copyright: Fernando Menandro ()
 * License:
 **************************************************************/

#ifdef WX_PRECOMP
#include "wx_pch.h"
#endif

#ifdef __BORLANDC__
#pragma hdrstop
#endif //__BORLANDC__

#include "ufesApp.h"
#include "ufesMain.h"

class analise job;
class analise_incremental jobi;
class analise_termica jobt;
int tipo;
IMPLEMENT_APP(ufesApp);



bool ufesApp::OnInit()
{
     wxBoxSizer* sizer = new wxBoxSizer(wxHORIZONTAL);
     ufesFrame* frame = new ufesFrame(0L, _("U. F. E. S."));
//     wxTextInputStream ent= new wxTextInputStream(sai);
//     wxTextOutputStream sai= new wxTextOutputStream(ent);

    drawPane = new BasicDrawPane( (wxFrame*) frame );
    sizer->Add(drawPane, 1, wxEXPAND);

    frame->SetSizer(sizer);
    frame->SetAutoLayout(true);

    frame->Show();
//    class analise *job;
//    job.Show(true);
    SetTopWindow(frame);
    return true;
}

BEGIN_EVENT_TABLE(BasicDrawPane, wxPanel)
// some useful events
/*
 EVT_MOTION(BasicDrawPane::mouseMoved)
 EVT_LEFT_DOWN(BasicDrawPane::mouseDown)
 EVT_LEFT_UP(BasicDrawPane::mouseReleased)
 EVT_RIGHT_DOWN(BasicDrawPane::rightClick)
 EVT_LEAVE_WINDOW(BasicDrawPane::mouseLeftWindow)
 EVT_KEY_DOWN(BasicDrawPane::keyPressed)
 EVT_KEY_UP(BasicDrawPane::keyReleased)
 EVT_MOUSEWHEEL(BasicDrawPane::mouseWheelMoved)
 */

// catch paint events
EVT_PAINT(BasicDrawPane::paintEvent)

END_EVENT_TABLE()


// some useful events
/*
 void BasicDrawPane::mouseMoved(wxMouseEvent& event) {}
 void BasicDrawPane::mouseDown(wxMouseEvent& event) {}
 void BasicDrawPane::mouseWheelMoved(wxMouseEvent& event) {}
 void BasicDrawPane::mouseReleased(wxMouseEvent& event) {}
 void BasicDrawPane::rightClick(wxMouseEvent& event) {}
 void BasicDrawPane::mouseLeftWindow(wxMouseEvent& event) {}
 void BasicDrawPane::keyPressed(wxKeyEvent& event) {}
 void BasicDrawPane::keyReleased(wxKeyEvent& event) {}
 */

BasicDrawPane::BasicDrawPane(wxFrame* parent) :
wxPanel(parent)
{
}

/*
 * Called by the system of by wxWidgets when the panel needs
 * to be redrawn. You can also trigger this call by
 * calling Refresh()/Update().
 */

void BasicDrawPane::paintEvent(wxPaintEvent & evt)
{
    wxPaintDC dc(this);
    render(dc);
}

/*
 * Alternatively, you can use a clientDC to paint on the panel
 * at any time. Using this generally does not free you from
 * catching paint events, since it is possible that e.g. the window
 * manager throws away your drawing when the window comes to the
 * background, and expects you will redraw it when the window comes
 * back (by sending a paint event).
 *
 * In most cases, this will not be needed at all; simply handling
 * paint events and calling Refresh() when a refresh is needed
 * will do the job.
 */
void BasicDrawPane::paintNow()
{
    wxClientDC dc(this);
    render(dc);
}

/*
 * Here we do the actual rendering. I put it in a separate
 * method so that it can work no matter what type of DC
 * (e.g. wxPaintDC or wxClientDC) is used.
 */
void BasicDrawPane::render(wxDC&  dc)
{
// Meu texto
wxCoord w,h;
dc.GetSize(&w,&h);

//    dc.DrawText(wxT("Testing"), 0.4*(w), 0.6*(h));

    // draw some text
//    dc.DrawText(wxT("Testing"), 40, 60);

    // draw a circle

//    dc.SetBrush(*wxGREEN_BRUSH); // green filling
//    dc.SetPen( wxPen( wxColor(255,0,0), 5 ) ); // 5-pixels-thick red outline
//    dc.DrawCircle( wxPoint(200,100), 25 /* radius */ );

    // draw a rectangle

//    dc.SetBrush(*wxBLUE_BRUSH); // blue filling
//    dc.SetPen( wxPen( wxColor(255,175,175), 10 ) ); // 10-pixels-thick pink outline
//    dc.DrawRectangle( 300, 100, 400, 200 );

    // draw a line

    dc.SetPen( wxPen( wxColor(0,0,0), 3 ) ); // black line, 3 pixels thick
//    dc.DrawLine( 0.2*(w), 0.3*(h), 0.2*(w), 0.8*(h) ); // draw line across the rectangle
//   dc.DrawLine( 0.2*(w), 0.8*(h), 0.6*(w), 0.8*(h) ); // draw line across the rectangle
//   dc.DrawLine( 0.6*(w), 0.8*(h), 0.6*(w), 0.3*(h) ); // draw line across the rectangle
//   dc.DrawLine( 0.6*(w), 0.3*(h), 0.2*(w), 0.3*(h) ); // draw line across the rectangle

    // Look at the wxDC docs to learn how to draw other stuff

    // desenhar uma malha da elementos finitos
    switch(tipo)
    {
        case 0:
            if(job.nn!=0)
            {
               dc.DrawText(wxT("Analise Estrutural Linear"),5,5);
               job.draw(dc);
            }
            break;
        case 1:
            if(jobi.nn!=0)
            {
                dc.DrawText(wxT("Analise Incremental"),5,5);
                jobi.draw(dc);
            }
            break;
        case 2:
            if(jobt.nn!=0)
            {
               dc.DrawText(wxT("Propagacao de Calor"),5,5);
               jobt.draw(dc);
            }
            break;
        case 3:
            if(job.nn!=0)
            {
               dc.DrawText(wxT("Otimizacao Topologica"),5,5);
               job.draw(dc);
            }
    }
    

}
