/***************************************************************
 * Name:      ufesMain.h
 * Purpose:   Defines Application Frame
 * Author:    Fernando Menandro (menandro@ct.ufes.br)
 * Created:   2015-03-12
 * Copyright: Fernando Menandro ()
 * License:
 **************************************************************/

#ifndef UFESMAIN_H
#define UFESMAIN_H

#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif
#include <wx/filedlg.h>
#include <wx/textctrl.h>
#include <wx/textentry.h>
#include <wx/combobox.h>
#include "ufesApp.h"
#include <wx/numdlg.h>
#include <wx/textdlg.h>

class ufesFrame: public wxFrame
{
    public:
        ufesFrame(wxFrame *frame, const wxString& title);
        ~ufesFrame();
//         int mef(int, wxFileStream*, wxFileStream*);


       private:
//         char entrada[100],saida[100];

        enum
        {
            idMenuOpen = 1000,
            idMenuStan,
            idMenuFile,
            idMenuQuit,
            idMenuNo,
            idMenuNNo,
            idMenuEl,
            idMenuNEl,
            idMenuCC,
            idMenuNCC,
            idMenuNM,
            idMenuRo,
            idMenuView,
            idMenuChro,
            idMenuChrm,
            idMenuChcl,
			idMenuChte,
            idMenuRun,
            idMenuOpt,
            idMenuAbout
        };
        void OnClose(wxCloseEvent& event);
        void OnOpen(wxCommandEvent& event);
        void OnStan(wxCommandEvent& event);
        void OnFile(wxCommandEvent& event);
        void OnQuit(wxCommandEvent& event);
        void OnNo(wxCommandEvent& event);
        void OnNNo(wxCommandEvent& event);
        void OnEl(wxCommandEvent& event);
        void OnNEl(wxCommandEvent& event);
        void OnCC(wxCommandEvent& event);
        void OnNCC(wxCommandEvent& event);
        void OnNM(wxCommandEvent& event);
        void OnRo(wxCommandEvent& event);
        void OnView(wxCommandEvent& event);
        void OnChro(wxCommandEvent& event);
        void OnChrm(wxCommandEvent& event);
        void OnChcl(wxCommandEvent& event);
		void OnChte(wxCommandEvent& event);
        void OnRun(wxCommandEvent& event);
        void OnOpt(wxCommandEvent& event);
        void OnAbout(wxCommandEvent& event);
        void OnSelectionChange(wxCommandEvent& event);
        DECLARE_EVENT_TABLE()
};
class viewComboBox : public wxComboBox
{
public:

    viewComboBox(    
		  wxWindow * 	parent,
		  wxWindowID 	id,
		  const wxString & 	value = wxEmptyString,
		  const wxPoint & 	pos = wxDefaultPosition,
		  const wxSize & 	size = wxDefaultSize,
		  int 	n = 0,
		  const wxString 	choices[] = NULL,
		  long 	style = 0,
		  const wxValidator & 	validator = wxDefaultValidator,
		  const wxString & 	name = wxComboBoxNameStr       
    );
    ~viewComboBox();
    void OnSelectionChange(wxCommandEvent& event);
private:
    enum
    {
                idView=100
    };
    DECLARE_EVENT_TABLE()	
};


#endif // UFESMAIN_H
