/***************************************************************
 * Name:      ufesMain.cpp
 * Purpose:   Code for Application Frame
 * Author:    Fernando Menandro (menandro@ct.ufes.br)
 * Created:   2015-03-12
 * Copyright: Fernando Menandro ()
 * License:
 **************************************************************/
#include <wx/wxprec.h>
#ifdef WX_PRECOMP
//#include "wx_pch.h"
#endif

#ifdef __BORLANDC__
#pragma hdrstop
#endif //__BORLANDC__

#include "ufesMain.h"
//#include "base.h"
//helper functions
extern class analise job;
extern class analise_incremental jobi;
extern class analise_termica jobt;
extern int tipo;

enum wxbuildinfoformat {
    short_f, long_f };


wxString wxbuildinfo(wxbuildinfoformat format)
{
    wxString wxbuild(wxVERSION_STRING);

    if (format == long_f )
    {
#if defined(__WXMSW__)
        wxbuild << _T("-Windows");
#elif defined(__WXMAC__)
        wxbuild << _T("-Mac");
#elif defined(__UNIX__)
        wxbuild << _T("-Linux");
#endif

#if wxUSE_UNICODE
        wxbuild << _T("-Unicode build");
#else
        wxbuild << _T("-ANSI build");
#endif // wxUSE_UNICODE
    }

    return wxbuild;
}

BEGIN_EVENT_TABLE(ufesFrame, wxFrame)
    EVT_CLOSE(ufesFrame::OnClose)
    EVT_MENU(idMenuOpen, ufesFrame::OnOpen)
    EVT_MENU(idMenuStan, ufesFrame::OnStan)
    EVT_MENU(idMenuFile, ufesFrame::OnFile)
    EVT_MENU(idMenuQuit, ufesFrame::OnQuit)
    EVT_MENU(idMenuNo, ufesFrame::OnNo)
    EVT_MENU(idMenuNNo, ufesFrame::OnNNo)
    EVT_MENU(idMenuEl, ufesFrame::OnEl)
    EVT_MENU(idMenuNEl, ufesFrame::OnNEl)
    EVT_MENU(idMenuCC, ufesFrame::OnCC)
    EVT_MENU(idMenuNCC, ufesFrame::OnNCC)
    EVT_MENU(idMenuNM, ufesFrame::OnNM)
    EVT_MENU(idMenuRo, ufesFrame::OnRo)
    EVT_MENU(idMenuView, ufesFrame::OnView)
    EVT_MENU(idMenuChro, ufesFrame::OnChro)
    EVT_MENU(idMenuChrm, ufesFrame::OnChrm)
    EVT_MENU(idMenuChcl, ufesFrame::OnChcl)
	EVT_MENU(idMenuChte, ufesFrame::OnChte)
    EVT_MENU(idMenuRun, ufesFrame::OnRun)
    EVT_MENU(idMenuOpt, ufesFrame::OnOpt)
    EVT_MENU(idMenuAbout, ufesFrame::OnAbout)

END_EVENT_TABLE()

BEGIN_EVENT_TABLE(viewComboBox, wxComboBox)
    EVT_COMBOBOX(idView,viewComboBox::OnSelectionChange)
END_EVENT_TABLE()

ufesFrame::ufesFrame(wxFrame *frame, const wxString& title)
    : wxFrame(frame, -1, title)
{
#if wxUSE_MENUS
    // create a menu bar
    wxMenuBar* mbar = new wxMenuBar();
    wxMenu* fileMenu = new wxMenu(_T(""));
    fileMenu->Append(idMenuOpen, _("&Entrada"), _("Abrir arquivo de entrada"));
    fileMenu->Append(idMenuStan, _("&Padrao"), _("Criar arquivo padrao para otimização"));
    fileMenu->Append(idMenuFile, _("&Saida"), _("Abrir e escrever arquivo de saida"));
    fileMenu->Append(idMenuQuit, _("&Sair\tAlt-F4"), _("Sair do programa"));
    mbar->Append(fileMenu, _("&Arquivo"));

    wxMenu* drawMenu = new wxMenu(_T(""));
    drawMenu->Append(idMenuNo, _("&Nos"), _("Mostrar posicoes"));
    drawMenu->Append(idMenuNNo, _("&Numeros dos nos"), _("Mostrar numeros"));
    drawMenu->Append(idMenuEl, _("&Elementos"), _("Mostrar faces"));
    drawMenu->Append(idMenuNEl, _("&Numeros dos elementos"), _("Mostrar numeros"));
    drawMenu->Append(idMenuCC, _("&Condicoes de contorno"), _("Mostrar posicoes"));
    drawMenu->Append(idMenuNCC, _("&Numeros das condicoes"), _("Mostrar numeros"));
    drawMenu->Append(idMenuNM, _("&Materiais"), _("Mostrar materiais"));
    drawMenu->Append(idMenuRo, _("&Densidades"), _("Mostrar pseudo-densidades"));
    drawMenu->Append(idMenuView, _("&Visao"), _("Angulos de visao"));
     mbar->Append(drawMenu, _("&Mostrar"));

    wxMenu* changeMenu = new wxMenu(_T(""));
    changeMenu->Append(idMenuChro, _("&Densidades\tF5"), _("Alterar densidades"));
    changeMenu->Append(idMenuChrm, _("&Raio minimo\tF6"), _("Alterar raio minimo"));
    changeMenu->Append(idMenuChcl, _("&Limite de otimizacao\tF7"), _("Alterar limite"));
	changeMenu->Append(idMenuChte, _("&Valor da(s) forca(s)\tF10"), _("Alterar valor"));
     mbar->Append(changeMenu, _("&Alterar"));

    wxMenu* runMenu = new wxMenu(_T(""));
    runMenu->Append(idMenuRun, _("&Rodar\tF8"), _("Executar a analise"));
    runMenu->Append(idMenuOpt, _("&Otimizar\tF9"), _("Executar a otimizacao"));
    mbar->Append(runMenu, _("&Executar"));

    wxMenu* helpMenu = new wxMenu(_T(""));
    helpMenu->Append(idMenuAbout, _("&Sobre\tF1"), _("Exibir informacoes sobre o programa"));
    mbar->Append(helpMenu, _("&Ajuda"));

    SetMenuBar(mbar);
#endif // wxUSE_MENUS
#if wxUSE_STATUSBAR
    // create a status bar with some information about the used wxWidgets version
    CreateStatusBar(2);
    SetStatusText(_("Unified Finite Element Solver!"),0);
    SetStatusText(wxbuildinfo(short_f), 1);
#endif // wxUSE_STATUSBAR
}


ufesFrame::~ufesFrame()
{
}

void ufesFrame::OnClose(wxCloseEvent &event)
{
    Destroy();
}

void ufesFrame::OnOpen(wxCommandEvent& WXUNUSED(event))
{
/*if (...current content has not been saved...)
{
if (wxMessageBox(_("Current content has not been saved! Proceed?"), _("Please confirm"),
wxICON_QUESTION | wxYES_NO, this) == wxNO )
return;
//else: proceed asking to the user the new file to open
}*/
wxFileDialog
openFileDialog(this, _("Abrir arquivo de entrada"), "", "",
"Arquivos ENT(*.ent)|*.*", wxFD_OPEN|wxFD_FILE_MUST_EXIST);
if (openFileDialog.ShowModal() == wxID_CANCEL)
return; // the user changed idea...
// proceed loading the file chosen by the user;
// this can be done with e.g. wxWidgets input streams:
wxFileInputStream input_stream(openFileDialog.GetPath());
if (!input_stream.IsOk())
{
wxLogError("Nao e possivel abrir arquivo '%s'.", openFileDialog.GetPath());
return;
}
wxTextInputStream ent( input_stream );
ent>>tipo;
switch(tipo)
{
    case 0:
    case 3:
        ent>>job;
        break;
    case 1:
        ent>>jobi;
        break;
    case 2:
        ent>>jobt;
        break;
}
Refresh();
}

void ufesFrame::OnStan(wxCommandEvent& WXUNUSED(event))
{
/*if (...current content has not been saved...)
{
if (wxMessageBox(_("Current content has not been saved! Proceed?"), _("Please confirm"),
wxICON_QUESTION | wxYES_NO, this) == wxNO )
return;
//else: proceed asking to the user the new file to open
}*/
//wxFileDialog
//openFileDialog(this, _("Abrir arquivo de entrada"), "", "",
//"Arquivos ENT(*.ent)|*.*", wxFD_OPEN|wxFD_FILE_MUST_EXIST);
//if (openFileDialog.ShowModal() == wxID_CANCEL)
//return; // the user changed idea...
// proceed loading the file chosen by the user;
// this can be done with e.g. wxWidgets input streams:
wxFileInputStream input_stream("O2d496n.txt");
if (!input_stream.IsOk())
{
wxLogError("Nao e possivel abrir arquivo '%s'.", "O2d496n.txt");
return;
}
wxTextInputStream ent( input_stream );
ent>>tipo;
switch(tipo)
{
    case 0:
    case 3:
        ent>>job;
        break;
    case 1:
        ent>>jobi;
        break;
    case 2:
        ent>>jobt;
        break;
}
Refresh();
}

void ufesFrame::OnFile(wxCommandEvent &event)
{
wxFileDialog
openOutputDialog(this, _("Abrir arquivo de saida"), "", "",
"Arquivos sai(*.sai)|*.sai", wxFD_OPEN);
if (openOutputDialog.ShowModal() == wxID_CANCEL)
return; // the user changed idea...
// proceed loading the file chosen by the user;
// this can be done with e.g. wxWidgets input streams:
wxFileOutputStream output_stream(openOutputDialog.GetPath());
if (!output_stream.IsOk())
{
wxLogError("Nao e possivel abrir arquivo '%s'.", openOutputDialog.GetPath());
return;
}
wxTextOutputStream sai( output_stream );
switch(tipo)
{
    case 0:
    case 3:
        sai<<job;
        break;
    case 1:
        sai<<jobi;
        break;
    case 2:
        sai<<jobt;
        break;
}
//saida=printf("'%s'",wxString::wc_str(openOutputDialog.GetPath()));
}
void ufesFrame::OnQuit(wxCommandEvent &event)
{
    Destroy();
}

void ufesFrame::OnNo(wxCommandEvent &event)
{
switch(tipo)
{
    case 0:
    case 3:
        job.fn=!job.fn;
        break;
    case 1:
        jobi.fn=!jobi.fn;
        break;
    case 2:
        jobt.fn=!jobt.fn;
        break;
}
Refresh();
}
void ufesFrame::OnNNo(wxCommandEvent &event)
{
switch(tipo)
{
    case 0:
    case 3:
        job.fnn=!job.fnn;
        if (job.fnn==1) job.fn=1;
        break;
    case 1:
        jobi.fnn=!jobi.fnn;
        if (jobi.fnn==1) jobi.fn=1;
        break;
    case 2:
        jobt.fnn=!jobt.fnn;
        if (jobt.fnn==1) jobt.fn=1;
        break;
}
Refresh();
}
void ufesFrame::OnEl(wxCommandEvent &event)
{
switch(tipo)
{
    case 0:
    case 3:
        job.fe=!job.fe;
        break;
    case 1:
        jobi.fe=!jobi.fe;
        break;
    case 2:
        jobt.fe=!jobt.fe;
        break;
}
Refresh();
}
void ufesFrame::OnNEl(wxCommandEvent &event)
{
switch(tipo)
{
    case 0:
    case 3:
        job.fne=!job.fne;
        if (job.fne==1) job.fe=1;
        break;
    case 1:
        jobi.fne=!jobi.fne;
        if (jobi.fne==1) jobi.fe=1;
        break;
    case 2:
        jobt.fne=!jobt.fne;
        if (jobt.fne==1) jobt.fe=1;
        break;
}
Refresh();
}
void ufesFrame::OnCC(wxCommandEvent &event)
{
switch(tipo)
{
    case 0:
    case 3:
        job.fcc=!job.fcc;
        break;
    case 1:
        jobi.fcc=!jobi.fcc;
        break;
    case 2:
        jobt.fcc=!jobt.fcc;
        break;
}
Refresh();
}
void ufesFrame::OnNCC(wxCommandEvent &event)
{
switch(tipo)
{
    case 0:
    case 3:
        job.fnc=!job.fnc;
        if (job.fnc==1) job.fcc=1;
        break;
    case 1:
        jobi.fnc=!jobi.fnc;
        if (jobi.fnc==1) jobi.fcc=1;
        break;
    case 2:
        jobt.fnc=!jobt.fnc;
        if (jobt.fnc==1) jobt.fcc=1;
        break;
}
Refresh();
}
void ufesFrame::OnNM(wxCommandEvent &event)
{
switch(tipo)
{
    case 0:
    case 3:
        job.fnm=!job.fnm;
        if (job.fnm==1) job.fe=1;
        break;
    case 1:
        jobi.fnm=!jobi.fnm;
        if (jobi.fnm==1) jobi.fe=1;
        break;
    case 2:
        jobt.fnm=!jobt.fnm;
        if (jobt.fnm==1) jobt.fe=1;
        break;
}
Refresh();
}
void ufesFrame::OnRo(wxCommandEvent &event)
{
switch(tipo)
{
    case 0:
    case 3:
        job.fro=!job.fro;
        if (job.fro==1) job.fe=1;
        break;
    case 1:
        jobi.fro=!jobi.fro;
        if (jobi.fro==1) jobi.fe=1;
        break;
    case 2:
        jobt.fro=!jobt.fro;
        if (jobt.fro==1) jobt.fe=1;
        break;
}
Refresh();
}
void ufesFrame::OnView(wxCommandEvent &event)
{
    wxCoord w,h;
    int d;
    this->GetSize(&w,&h);
wxTextEntryDialog dialog(this,
wxT("Entre um vetor de direcao do observador, em graus\n")
wxT("separado por espacos  (visao inicial 0 0 0)"), 
wxT("Visao"), 
wxT("0 0 0"), wxOK|wxCANCEL);
if (dialog.ShowModal() == wxID_OK)
	job.visao(dialog.GetValue());
//wxMessageBox(dialog.GetValue(),wxT("Pegamos"));
/*
    wxString choices[3]={"Um","Dois","Tres"};
    viewComboBox *view=new viewComboBox(this,idMenuView,"Escolha um item...",wxPoint(0.2*w,0.2*h),
                             wxSize(0.5*w,0.1*h),3,choices,0,wxDefaultValidator,"mytext");
    view->Show(true);*/
//        *mytext<<"Testando";
Refresh();
}

void ufesFrame::OnChro(wxCommandEvent &event)
{
    wxCoord w,h;
    int d;
    this->GetSize(&w,&h);
wxNumberEntryDialog dialog(this,
wxT("Novo valor desejado para a densidade,\nem porcentagem"),
wxT("Entre um numero:"), wxT("Nova Densidade"), 
50, 0, 100);
if (dialog.ShowModal() == wxID_OK)
{
long value = dialog.GetValue();
for(int el=0;el<job.ne;el++)
	job.elementos[el]->upro(value/100.);
job.ro=value/100.0;
}
/*
    wxString choices[3]={"Um","Dois","Tres"};
    viewComboBox *view=new viewComboBox(this,idMenuView,"Escolha um item...",wxPoint(0.2*w,0.2*h),
                             wxSize(0.5*w,0.1*h),3,choices,0,wxDefaultValidator,"mytext");
    view->Show(true);*/
//        *mytext<<"Testando";
Refresh();
}
void ufesFrame::OnChrm(wxCommandEvent &event)
{
    wxCoord w,h;
    int d;
    this->GetSize(&w,&h);
    wxString RM;
    RM<<job.rm;
wxTextEntryDialog dialog(this,
wxT("Novo valor desejado para o raio minimo\n"),
wxT("Entre um numero:"), RM, 
wxOK | wxCANCEL);
if (dialog.ShowModal() == wxID_OK)
{
    double value;
//    sscanf(dialog.GetValue(),"%lf",&value);
    if(!dialog.GetValue().ToDouble(&value))
    {
        wxMessageBox(dialog.GetValue(),wxT("Raio minimo inalterado"));
    }
    else
    {
        wxString NRM;
        job.rm=value;
        NRM<<job.rm;
        wxMessageBox(NRM,wxT("Novo raio minimo"));        
    }
//   double value = dialog.GetValue();
//job.rm=value;
}
Refresh();
}

void ufesFrame::OnChcl(wxCommandEvent &event)
{
    wxCoord w,h;
    int d;
    this->GetSize(&w,&h);
    wxString CL;
    CL<<job.ch_lim;
wxTextEntryDialog dialog(this,
wxT("Novo valor desejado para o limite de parada da otimizacao,\n"),
wxT("Entre um numero:"), CL, 
wxOK | wxCANCEL);
if (dialog.ShowModal() == wxID_OK)
{
    double value;
//    sscanf(dialog.GetValue(),"%lf",&value);
    if(!dialog.GetValue().ToDouble(&value))
    {
        wxMessageBox(dialog.GetValue(),wxT("Parada da otimizacao inalterada"));
    }
    else
    {
        wxString NCL;
        job.ch_lim=value;
        NCL<<job.ch_lim;
        wxMessageBox(NCL,wxT("Novo valor de parada da otimizacao"));        
    }
//   double value = dialog.GetValue();
//job.rm=value;
}
Refresh();
}

void ufesFrame::OnChte(wxCommandEvent &event)
{
	wxCoord w, h;
	int d;
	this->GetSize(&w, &h);
	wxString TE1;
	TE1 << job.ch_lim;
	wxTextEntryDialog dialog(this,
		wxT("Novo valor desejado para a forca\n"),
		wxT("Entre um numero:"), TE1,
		wxOK | wxCANCEL);
	if (dialog.ShowModal() == wxID_OK)
		job.chcc(dialog.GetValue());
	Refresh();
}

void ufesFrame::OnRun(wxCommandEvent &event)
{
   switch(tipo)
   {
   case 0:
   case 3:
      job.montaK();
      job.impoeCC();
      job.resolve();
      job.posprocessa();
      break;
   case 2:
	   jobt.roda();
       break;
   }
}

void ufesFrame::OnOpt(wxCommandEvent &event)
{
   switch(tipo)
   {
   case 0:
      double change=1;
	  double c;
          int a=1;
      while(change>job.ch_lim)
      {
	 job.zerar();
         job.montaroK();
         job.impoeCC();
         job.resolve();
         c=job.ofsa();
         double rmin=job.rm;
         job.fs(rmin);
         change=job.oc();
         cout<<"change["<<a++<<"] = "<<change<<"\n";
         job.posprocessa();  
      }
   }
   Refresh();
}

void ufesFrame::OnAbout(wxCommandEvent &event)
{
//    wxFileInputStream ajuda_stream("ajuda.txt");
//    wxTextInputStream ajuda(ajuda_stream);
//    wxString msg;
//    ajuda>>msg;
    wxString msg = wxbuildinfo(long_f);
    wxMessageBox(msg, _("Ajuda"));
}

viewComboBox::viewComboBox(		  wxWindow * 	parent,
		  wxWindowID 	id,
		  const wxString & 	value,
		  const wxPoint & 	pos,
		  const wxSize & 	size ,
		  int 	n,
		  const wxString 	choices[]  ,
		  long 	style,
		  const wxValidator & 	validator ,
		  const wxString & 	name    )
       : wxComboBox(parent,id,value,pos,size,n,choices,style,validator,name)
{}

viewComboBox::~viewComboBox()
{}

void viewComboBox::OnSelectionChange(wxCommandEvent &event)
{
    wxMessageBox(	"You Selected: "+GetStringSelection(),
		"wxComboBox Selection Changed",
		 wxOK);
}