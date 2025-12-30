#include "MyForm.h"

using namespace MDS;
using namespace System;
using namespace System::Windows::Forms;

[STAThreadAttribute]
int main(array<System::String^>^ args)
{
    // Enable Windows visual styles
    Application::EnableVisualStyles();

    // Set text rendering
    Application::SetCompatibleTextRenderingDefault(false);

    // Run main form
    Application::Run(gcnew MDS::MyForm());

    return 0;
}
