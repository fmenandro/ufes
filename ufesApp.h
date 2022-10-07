/***************************************************************
 * Name:      ufesApp.h
 * Purpose:   Defines Application Class
 * Author:    Fernando Menandro (menandro@ct.ufes.br)
 * Created:   2015-03-12
 * Copyright: Fernando Menandro ()
 * License:
 **************************************************************/

#ifndef UFESAPP_H
#define UFESAPP_H

#include <wx/app.h>
#include "wx/wx.h"
#include "wx/sizer.h"
#include <wx/wfstream.h>
#include <cstdlib>
#include <cstdio>
#include <wx/string.h>
#include <wx/textfile.h>
#include <wx/txtstrm.h>
#include "analise.h"
#include "analise_incremental.h"
#include "analise_termica.h"


class BasicDrawPane : public wxPanel
{

public:
    BasicDrawPane(wxFrame* parent);

    void paintEvent(wxPaintEvent & evt);
    void paintNow();

    void render(wxDC& dc);

    // some useful events
    /*
     void mouseMoved(wxMouseEvent& event);
     void mouseDown(wxMouseEvent& event);
     void mouseWheelMoved(wxMouseEvent& event);
     void mouseReleased(wxMouseEvent& event);
     void rightClick(wxMouseEvent& event);
     void mouseLeftWindow(wxMouseEvent& event);
     void keyPressed(wxKeyEvent& event);
     void keyReleased(wxKeyEvent& event);
     */

    DECLARE_EVENT_TABLE()
};



class ufesApp : public wxApp
{
    public:
        virtual bool OnInit();
    wxFrame *frame;
    BasicDrawPane * drawPane;
//    class analise job;

//         wxTextInputStream *ent;
//         wxTextOutputStream *sai;
//         int mef(int);

};

#endif // UFESAPP_H
