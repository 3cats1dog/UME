using namespace System;
using namespace System::Collections::Generic;
using namespace System::Drawing;
using namespace System::Text;
using namespace System::Threading::Tasks;
using namespace System::Windows::Forms;
using namespace System::Runtime::CompilerServices;

namespace MeasLab {


	//static  class ControlExtensions
	//{
	//	public static void UIThread(this Control @this, Action code)
	//	{
	//		if (@this.InvokeRequired)
	//		{
	//			@this.BeginInvoke(code);
	//		}
	//		else
	//		{
	//			code.Invoke();
	//		}
	//	}
	//	
	//};

	[System::Runtime::CompilerServices::ExtensionAttribute]
	public ref  class ControlExtensions abstract sealed
	{
	public:
		[System::Runtime::CompilerServices::ExtensionAttribute]
		static void UIThread(System::Windows::Forms::Control^ instance, Action^ code)
		{
			if (instance->InvokeRequired)
			{
				instance->BeginInvoke(code);
			}
			else
			{
				code->Invoke();
			}
		}

		[System::Runtime::CompilerServices::ExtensionAttribute]
		static void MyStrings(String^ instance)
		{
			instance = gcnew String("Hello");
		}

	};

}


