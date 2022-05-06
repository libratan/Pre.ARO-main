#pragma once
#include <msclr\marshal_cppstd.h>
namespace OnScreenKeyboard {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Xml;

	/// <summary>
	/// Summary for OnScreenKeyboard
	/// </summary>
	public ref class OnScreenKeyboard : public System::Windows::Forms::Form
	{
	public:
		OnScreenKeyboard(void);

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~OnScreenKeyboard();
	private: System::Windows::Forms::Button^ button_q;
	protected:
	private: System::Windows::Forms::Button^ button_w;
	private: System::Windows::Forms::Button^ button_e;
	private: System::Windows::Forms::Button^ button_r;
	private: System::Windows::Forms::Button^ button_t;
	private: System::Windows::Forms::Button^ button_y;
	private: System::Windows::Forms::Button^ button_u;
	private: System::Windows::Forms::Button^ button_i;
	private: System::Windows::Forms::Button^ button_o;
	private: System::Windows::Forms::Button^ button_p;
	private: System::Windows::Forms::Button^ button_a;
	private: System::Windows::Forms::Button^ button_s;
	private: System::Windows::Forms::Button^ button_d;
	private: System::Windows::Forms::Button^ button_f;
	private: System::Windows::Forms::Button^ button_g;
	private: System::Windows::Forms::Button^ button_h;
	private: System::Windows::Forms::Button^ button_j;
	private: System::Windows::Forms::Button^ button_k;
	private: System::Windows::Forms::Button^ button_l;
	private: System::Windows::Forms::Button^ button_z;
	private: System::Windows::Forms::Button^ button_x;
	private: System::Windows::Forms::Button^ button_c;
	private: System::Windows::Forms::Button^ button_v;
	private: System::Windows::Forms::Button^ button_b;
	private: System::Windows::Forms::Button^ button_n;
	private: System::Windows::Forms::Button^ button_m;
	private: System::Windows::Forms::Button^ button_1;
	private: System::Windows::Forms::Button^ button_2;
	private: System::Windows::Forms::Button^ button_3;
	private: System::Windows::Forms::Button^ button_4;
	private: System::Windows::Forms::Button^ button_5;
	private: System::Windows::Forms::Button^ button_6;
	private: System::Windows::Forms::Button^ button_7;
	private: System::Windows::Forms::Button^ button_8;
	private: System::Windows::Forms::Button^ button_9;
	private: System::Windows::Forms::Button^ button_0;
	private: System::Windows::Forms::Button^ button_backspace;
	private: System::Windows::Forms::Button^ button_space;
	private: System::Windows::Forms::Button^ button_period;
	private: System::Windows::Forms::Button^ button_enter;

	private: 
		int ALPHABET_W;	//_W represents Width
		int ALPHABET_H;	//_H represents Height
		int NUMBER_W;
		int NUMBER_H;
		int SYMBOL_W;
		int SYMBOL_H;
		int SPACING_W;
		int SPACING_H;
		int TEXT_RED;
		int TEXT_GREEN;
		int TEXT_BLUE;
		float TEXT_SIZE;
		int FG_RED;
		int FG_GREEN;
		int FG_BLUE;
		int BG_RED;
		int BG_GREEN;
		int BG_BLUE;

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void);
#pragma endregion
		protected:
			virtual property System::Windows::Forms::CreateParams^ CreateParams
			{
				System::Windows::Forms::CreateParams^ get() override
				{
					System::Windows::Forms::CreateParams^ param = __super::CreateParams;
					param->ExStyle |= 0x08000000;
					return param;
				}
			}
		private: System::Void OnScreenKeyboard_Load(System::Object^ sender, System::EventArgs^ e);
		private: System::Void Alphabet(System::Object^ sender, System::EventArgs^ e);
		private: System::Void button_enter_Click(System::Object^ sender, System::EventArgs^ e);
		private: System::Void button_backspace_Click(System::Object^ sender, System::EventArgs^ e);
		private: System::Void button_space_Click(System::Object^ sender, System::EventArgs^ e);
		private: System::Void Number(System::Object^ sender, System::EventArgs^ e);
		private: System::Void Symbol(System::Object^ sender, System::EventArgs^ e);
	};
}
