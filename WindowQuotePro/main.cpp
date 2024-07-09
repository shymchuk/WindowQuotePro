#include "MainWindowForm.h"

using namespace System;
using namespace System::Windows::Forms;

[STAThreadAttribute]
int main(array<String^>^ args)
{
	Application::SetCompatibleTextRenderingDefault(false);
	Application::EnableVisualStyles();
	//WindowQuotePro::InputForm inputForm{L"Hello world application"};
	WindowQuotePro::MainWindowForm mainWindow;
	Application::Run(% mainWindow);
	return 0;
}
