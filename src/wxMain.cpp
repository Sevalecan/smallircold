#include <wx.h>

class MyApp : public wxApp
{
    public:
        virtual bool OnInit();
        void Error();
};

IMPLEMENT_APP(MyApp)


class MainFrame : public wxFrame
{
    public:
        MainFrame();
        ~MainFrame();
        void OnQuit(wxCommandEvent &event);
        wxNotebook *switcher; // switch between outputs
        wxWindow *tfrmt;      // tab for formatted output, includes output thingy
        wxFlexGridSizer *ftab;// formatted server shit tab
        wxTextCtrl *server;   // server output
        wxTextCtrl *err;      // error stuff
        wxTextCtrl *frmt;     // formatted server output
        wxTextCtrl *out;      // you type in here and send you stuff to the server
    DECLARE_EVENT_TABLE()
};

BEGIN_EVENT_TABLE(MainFrame, wxFrame)
    EVT_BUTTON(wxID_EXIT, MainFrame::OnQuit)
END_EVENT_TABLE()

MainFrame::MainFrame() : public wxFrame(NULL, -1, wxString("SmallIRC Test"), wxPoint(50,50), wxSize(500,400))
{
    switcher = new wxNotebook(this, -1, wxPoint(-1,-1), wxSize(-1,-1), 0);
    tfrmt = new wxWindow(NULL, -1);
    server = new wxTextCtrl(NULL, -1, wxString(""), wxPoint(-1,-1), wxDefaultSize, wxTE_MULTILINE | wxTE_RICH | wxTE_WORDWRAP);
    ftab = new wxFlexGridSizer(2, 1, 0, 0);
    
    return;
}    


bool MyApp::OnInit() {
    MainFrame *mf;
    mf = new MainFrame();
    mf->Show(true);
    return 1;
}    
