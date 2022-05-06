#include "OnScreenKeyboard.h"

using namespace System;
using namespace System::Windows::Forms;

[STAThreadAttribute]

OnScreenKeyboard::OnScreenKeyboard::OnScreenKeyboard(void)
{
	InitializeComponent();
	//
	//TODO: Add the constructor code here
	//

}

OnScreenKeyboard::OnScreenKeyboard::~OnScreenKeyboard()
{
	if (components)
	{
		delete components;
	}
}

void OnScreenKeyboard::OnScreenKeyboard::InitializeComponent(void)
{
	System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(OnScreenKeyboard::typeid));
	this->button_q = (gcnew System::Windows::Forms::Button());
	this->button_w = (gcnew System::Windows::Forms::Button());
	this->button_e = (gcnew System::Windows::Forms::Button());
	this->button_r = (gcnew System::Windows::Forms::Button());
	this->button_t = (gcnew System::Windows::Forms::Button());
	this->button_y = (gcnew System::Windows::Forms::Button());
	this->button_u = (gcnew System::Windows::Forms::Button());
	this->button_i = (gcnew System::Windows::Forms::Button());
	this->button_o = (gcnew System::Windows::Forms::Button());
	this->button_p = (gcnew System::Windows::Forms::Button());
	this->button_a = (gcnew System::Windows::Forms::Button());
	this->button_s = (gcnew System::Windows::Forms::Button());
	this->button_d = (gcnew System::Windows::Forms::Button());
	this->button_f = (gcnew System::Windows::Forms::Button());
	this->button_g = (gcnew System::Windows::Forms::Button());
	this->button_h = (gcnew System::Windows::Forms::Button());
	this->button_j = (gcnew System::Windows::Forms::Button());
	this->button_k = (gcnew System::Windows::Forms::Button());
	this->button_l = (gcnew System::Windows::Forms::Button());
	this->button_z = (gcnew System::Windows::Forms::Button());
	this->button_x = (gcnew System::Windows::Forms::Button());
	this->button_c = (gcnew System::Windows::Forms::Button());
	this->button_v = (gcnew System::Windows::Forms::Button());
	this->button_b = (gcnew System::Windows::Forms::Button());
	this->button_n = (gcnew System::Windows::Forms::Button());
	this->button_m = (gcnew System::Windows::Forms::Button());
	this->button_1 = (gcnew System::Windows::Forms::Button());
	this->button_2 = (gcnew System::Windows::Forms::Button());
	this->button_3 = (gcnew System::Windows::Forms::Button());
	this->button_4 = (gcnew System::Windows::Forms::Button());
	this->button_5 = (gcnew System::Windows::Forms::Button());
	this->button_6 = (gcnew System::Windows::Forms::Button());
	this->button_7 = (gcnew System::Windows::Forms::Button());
	this->button_8 = (gcnew System::Windows::Forms::Button());
	this->button_9 = (gcnew System::Windows::Forms::Button());
	this->button_0 = (gcnew System::Windows::Forms::Button());
	this->button_backspace = (gcnew System::Windows::Forms::Button());
	this->button_space = (gcnew System::Windows::Forms::Button());
	this->button_enter = (gcnew System::Windows::Forms::Button());
	this->button_period = (gcnew System::Windows::Forms::Button());
	this->SuspendLayout();
	// 
	// button_q
	// 
	this->button_q->BackColor = System::Drawing::SystemColors::Control;
	this->button_q->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
		static_cast<System::Byte>(0)));
	this->button_q->Location = System::Drawing::Point(0, 75);
	this->button_q->Name = L"button_q";
	this->button_q->Size = System::Drawing::Size(75, 55);
	this->button_q->TabIndex = 0;
	this->button_q->Text = L"Q";
	this->button_q->UseVisualStyleBackColor = false;
	this->button_q->Click += gcnew System::EventHandler(this, &OnScreenKeyboard::Alphabet);
	// 
	// button_w
	// 
	this->button_w->BackColor = System::Drawing::SystemColors::Control;
	this->button_w->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
		static_cast<System::Byte>(0)));
	this->button_w->Location = System::Drawing::Point(100, 75);
	this->button_w->Name = L"button_w";
	this->button_w->Size = System::Drawing::Size(75, 55);
	this->button_w->TabIndex = 1;
	this->button_w->Text = L"W";
	this->button_w->UseVisualStyleBackColor = false;
	this->button_w->Click += gcnew System::EventHandler(this, &OnScreenKeyboard::Alphabet);
	// 
	// button_e
	// 
	this->button_e->BackColor = System::Drawing::SystemColors::Control;
	this->button_e->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
		static_cast<System::Byte>(0)));
	this->button_e->Location = System::Drawing::Point(200, 75);
	this->button_e->Name = L"button_e";
	this->button_e->Size = System::Drawing::Size(75, 55);
	this->button_e->TabIndex = 2;
	this->button_e->Text = L"E";
	this->button_e->UseVisualStyleBackColor = false;
	this->button_e->Click += gcnew System::EventHandler(this, &OnScreenKeyboard::Alphabet);
	// 
	// button_r
	// 
	this->button_r->BackColor = System::Drawing::SystemColors::Control;
	this->button_r->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
		static_cast<System::Byte>(0)));
	this->button_r->Location = System::Drawing::Point(300, 75);
	this->button_r->Name = L"button_r";
	this->button_r->Size = System::Drawing::Size(75, 55);
	this->button_r->TabIndex = 3;
	this->button_r->Text = L"R";
	this->button_r->UseVisualStyleBackColor = false;
	this->button_r->Click += gcnew System::EventHandler(this, &OnScreenKeyboard::Alphabet);
	// 
	// button_t
	// 
	this->button_t->BackColor = System::Drawing::SystemColors::Control;
	this->button_t->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
		static_cast<System::Byte>(0)));
	this->button_t->Location = System::Drawing::Point(400, 75);
	this->button_t->Name = L"button_t";
	this->button_t->Size = System::Drawing::Size(75, 55);
	this->button_t->TabIndex = 4;
	this->button_t->Text = L"T";
	this->button_t->UseVisualStyleBackColor = false;
	this->button_t->Click += gcnew System::EventHandler(this, &OnScreenKeyboard::Alphabet);
	// 
	// button_y
	// 
	this->button_y->BackColor = System::Drawing::SystemColors::Control;
	this->button_y->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
		static_cast<System::Byte>(0)));
	this->button_y->Location = System::Drawing::Point(500, 75);
	this->button_y->Name = L"button_y";
	this->button_y->Size = System::Drawing::Size(75, 55);
	this->button_y->TabIndex = 5;
	this->button_y->Text = L"Y";
	this->button_y->UseVisualStyleBackColor = false;
	this->button_y->Click += gcnew System::EventHandler(this, &OnScreenKeyboard::Alphabet);
	// 
	// button_u
	// 
	this->button_u->BackColor = System::Drawing::SystemColors::Control;
	this->button_u->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
		static_cast<System::Byte>(0)));
	this->button_u->Location = System::Drawing::Point(600, 75);
	this->button_u->Name = L"button_u";
	this->button_u->Size = System::Drawing::Size(75, 55);
	this->button_u->TabIndex = 6;
	this->button_u->Text = L"U";
	this->button_u->UseVisualStyleBackColor = false;
	this->button_u->Click += gcnew System::EventHandler(this, &OnScreenKeyboard::Alphabet);
	// 
	// button_i
	// 
	this->button_i->BackColor = System::Drawing::SystemColors::Control;
	this->button_i->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
		static_cast<System::Byte>(0)));
	this->button_i->Location = System::Drawing::Point(700, 75);
	this->button_i->Name = L"button_i";
	this->button_i->Size = System::Drawing::Size(75, 55);
	this->button_i->TabIndex = 7;
	this->button_i->Text = L"I";
	this->button_i->UseVisualStyleBackColor = false;
	this->button_i->Click += gcnew System::EventHandler(this, &OnScreenKeyboard::Alphabet);
	// 
	// button_o
	// 
	this->button_o->BackColor = System::Drawing::SystemColors::Control;
	this->button_o->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
		static_cast<System::Byte>(0)));
	this->button_o->Location = System::Drawing::Point(800, 75);
	this->button_o->Name = L"button_o";
	this->button_o->Size = System::Drawing::Size(75, 55);
	this->button_o->TabIndex = 8;
	this->button_o->Text = L"O";
	this->button_o->UseVisualStyleBackColor = false;
	this->button_o->Click += gcnew System::EventHandler(this, &OnScreenKeyboard::Alphabet);
	// 
	// button_p
	// 
	this->button_p->BackColor = System::Drawing::SystemColors::Control;
	this->button_p->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
		static_cast<System::Byte>(0)));
	this->button_p->Location = System::Drawing::Point(900, 75);
	this->button_p->Name = L"button_p";
	this->button_p->Size = System::Drawing::Size(75, 55);
	this->button_p->TabIndex = 9;
	this->button_p->Text = L"P";
	this->button_p->UseVisualStyleBackColor = false;
	this->button_p->Click += gcnew System::EventHandler(this, &OnScreenKeyboard::Alphabet);
	// 
	// button_a
	// 
	this->button_a->BackColor = System::Drawing::SystemColors::Control;
	this->button_a->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
		static_cast<System::Byte>(0)));
	this->button_a->Location = System::Drawing::Point(49, 135);
	this->button_a->Name = L"button_a";
	this->button_a->Size = System::Drawing::Size(75, 55);
	this->button_a->TabIndex = 10;
	this->button_a->Text = L"A";
	this->button_a->UseVisualStyleBackColor = false;
	this->button_a->Click += gcnew System::EventHandler(this, &OnScreenKeyboard::Alphabet);
	// 
	// button_s
	// 
	this->button_s->BackColor = System::Drawing::SystemColors::Control;
	this->button_s->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
		static_cast<System::Byte>(0)));
	this->button_s->Location = System::Drawing::Point(130, 135);
	this->button_s->Name = L"button_s";
	this->button_s->Size = System::Drawing::Size(75, 55);
	this->button_s->TabIndex = 11;
	this->button_s->Text = L"S";
	this->button_s->UseVisualStyleBackColor = false;
	this->button_s->Click += gcnew System::EventHandler(this, &OnScreenKeyboard::Alphabet);
	// 
	// button_d
	// 
	this->button_d->BackColor = System::Drawing::SystemColors::Control;
	this->button_d->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
		static_cast<System::Byte>(0)));
	this->button_d->Location = System::Drawing::Point(211, 135);
	this->button_d->Name = L"button_d";
	this->button_d->Size = System::Drawing::Size(75, 55);
	this->button_d->TabIndex = 12;
	this->button_d->Text = L"D";
	this->button_d->UseVisualStyleBackColor = false;
	this->button_d->Click += gcnew System::EventHandler(this, &OnScreenKeyboard::Alphabet);
	// 
	// button_f
	// 
	this->button_f->BackColor = System::Drawing::SystemColors::Control;
	this->button_f->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
		static_cast<System::Byte>(0)));
	this->button_f->Location = System::Drawing::Point(292, 135);
	this->button_f->Name = L"button_f";
	this->button_f->Size = System::Drawing::Size(75, 55);
	this->button_f->TabIndex = 13;
	this->button_f->Text = L"F";
	this->button_f->UseVisualStyleBackColor = false;
	this->button_f->Click += gcnew System::EventHandler(this, &OnScreenKeyboard::Alphabet);
	// 
	// button_g
	// 
	this->button_g->BackColor = System::Drawing::SystemColors::Control;
	this->button_g->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
		static_cast<System::Byte>(0)));
	this->button_g->Location = System::Drawing::Point(373, 135);
	this->button_g->Name = L"button_g";
	this->button_g->Size = System::Drawing::Size(75, 55);
	this->button_g->TabIndex = 14;
	this->button_g->Text = L"G";
	this->button_g->UseVisualStyleBackColor = false;
	this->button_g->Click += gcnew System::EventHandler(this, &OnScreenKeyboard::Alphabet);
	// 
	// button_h
	// 
	this->button_h->BackColor = System::Drawing::SystemColors::Control;
	this->button_h->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
		static_cast<System::Byte>(0)));
	this->button_h->Location = System::Drawing::Point(454, 135);
	this->button_h->Name = L"button_h";
	this->button_h->Size = System::Drawing::Size(75, 55);
	this->button_h->TabIndex = 15;
	this->button_h->Text = L"H";
	this->button_h->UseVisualStyleBackColor = false;
	this->button_h->Click += gcnew System::EventHandler(this, &OnScreenKeyboard::Alphabet);
	// 
	// button_j
	// 
	this->button_j->BackColor = System::Drawing::SystemColors::Control;
	this->button_j->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
		static_cast<System::Byte>(0)));
	this->button_j->Location = System::Drawing::Point(535, 135);
	this->button_j->Name = L"button_j";
	this->button_j->Size = System::Drawing::Size(75, 55);
	this->button_j->TabIndex = 16;
	this->button_j->Text = L"J";
	this->button_j->UseVisualStyleBackColor = false;
	this->button_j->Click += gcnew System::EventHandler(this, &OnScreenKeyboard::Alphabet);
	// 
	// button_k
	// 
	this->button_k->BackColor = System::Drawing::SystemColors::Control;
	this->button_k->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
		static_cast<System::Byte>(0)));
	this->button_k->Location = System::Drawing::Point(616, 135);
	this->button_k->Name = L"button_k";
	this->button_k->Size = System::Drawing::Size(75, 55);
	this->button_k->TabIndex = 17;
	this->button_k->Text = L"K";
	this->button_k->UseVisualStyleBackColor = false;
	this->button_k->Click += gcnew System::EventHandler(this, &OnScreenKeyboard::Alphabet);
	// 
	// button_l
	// 
	this->button_l->BackColor = System::Drawing::SystemColors::Control;
	this->button_l->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
		static_cast<System::Byte>(0)));
	this->button_l->Location = System::Drawing::Point(697, 135);
	this->button_l->Name = L"button_l";
	this->button_l->Size = System::Drawing::Size(75, 55);
	this->button_l->TabIndex = 18;
	this->button_l->Text = L"L";
	this->button_l->UseVisualStyleBackColor = false;
	this->button_l->Click += gcnew System::EventHandler(this, &OnScreenKeyboard::Alphabet);
	// 
	// button_z
	// 
	this->button_z->BackColor = System::Drawing::SystemColors::Control;
	this->button_z->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
		static_cast<System::Byte>(0)));
	this->button_z->Location = System::Drawing::Point(130, 196);
	this->button_z->Name = L"button_z";
	this->button_z->Size = System::Drawing::Size(75, 55);
	this->button_z->TabIndex = 19;
	this->button_z->Text = L"Z";
	this->button_z->UseVisualStyleBackColor = false;
	this->button_z->Click += gcnew System::EventHandler(this, &OnScreenKeyboard::Alphabet);
	// 
	// button_x
	// 
	this->button_x->BackColor = System::Drawing::SystemColors::Control;
	this->button_x->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
		static_cast<System::Byte>(0)));
	this->button_x->Location = System::Drawing::Point(211, 196);
	this->button_x->Name = L"button_x";
	this->button_x->Size = System::Drawing::Size(75, 55);
	this->button_x->TabIndex = 20;
	this->button_x->Text = L"X";
	this->button_x->UseVisualStyleBackColor = false;
	this->button_x->Click += gcnew System::EventHandler(this, &OnScreenKeyboard::Alphabet);
	// 
	// button_c
	// 
	this->button_c->BackColor = System::Drawing::SystemColors::Control;
	this->button_c->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
		static_cast<System::Byte>(0)));
	this->button_c->Location = System::Drawing::Point(292, 196);
	this->button_c->Name = L"button_c";
	this->button_c->Size = System::Drawing::Size(75, 55);
	this->button_c->TabIndex = 21;
	this->button_c->Text = L"C";
	this->button_c->UseVisualStyleBackColor = false;
	this->button_c->Click += gcnew System::EventHandler(this, &OnScreenKeyboard::Alphabet);
	// 
	// button_v
	// 
	this->button_v->BackColor = System::Drawing::SystemColors::Control;
	this->button_v->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
		static_cast<System::Byte>(0)));
	this->button_v->Location = System::Drawing::Point(373, 196);
	this->button_v->Name = L"button_v";
	this->button_v->Size = System::Drawing::Size(75, 55);
	this->button_v->TabIndex = 22;
	this->button_v->Text = L"V";
	this->button_v->UseVisualStyleBackColor = false;
	this->button_v->Click += gcnew System::EventHandler(this, &OnScreenKeyboard::Alphabet);
	// 
	// button_b
	// 
	this->button_b->BackColor = System::Drawing::SystemColors::Control;
	this->button_b->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
		static_cast<System::Byte>(0)));
	this->button_b->Location = System::Drawing::Point(454, 196);
	this->button_b->Name = L"button_b";
	this->button_b->Size = System::Drawing::Size(75, 55);
	this->button_b->TabIndex = 23;
	this->button_b->Text = L"B";
	this->button_b->UseVisualStyleBackColor = false;
	this->button_b->Click += gcnew System::EventHandler(this, &OnScreenKeyboard::Alphabet);
	// 
	// button_n
	// 
	this->button_n->BackColor = System::Drawing::SystemColors::Control;
	this->button_n->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
		static_cast<System::Byte>(0)));
	this->button_n->Location = System::Drawing::Point(535, 196);
	this->button_n->Name = L"button_n";
	this->button_n->Size = System::Drawing::Size(75, 55);
	this->button_n->TabIndex = 24;
	this->button_n->Text = L"N";
	this->button_n->UseVisualStyleBackColor = false;
	this->button_n->Click += gcnew System::EventHandler(this, &OnScreenKeyboard::Alphabet);
	// 
	// button_m
	// 
	this->button_m->BackColor = System::Drawing::SystemColors::Control;
	this->button_m->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
		static_cast<System::Byte>(0)));
	this->button_m->Location = System::Drawing::Point(616, 196);
	this->button_m->Name = L"button_m";
	this->button_m->Size = System::Drawing::Size(75, 55);
	this->button_m->TabIndex = 25;
	this->button_m->Text = L"M";
	this->button_m->UseVisualStyleBackColor = false;
	this->button_m->Click += gcnew System::EventHandler(this, &OnScreenKeyboard::Alphabet);
	// 
	// button_1
	// 
	this->button_1->BackColor = System::Drawing::SystemColors::Control;
	this->button_1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
		static_cast<System::Byte>(0)));
	this->button_1->Location = System::Drawing::Point(0, 0);
	this->button_1->Name = L"button_1";
	this->button_1->Size = System::Drawing::Size(75, 55);
	this->button_1->TabIndex = 26;
	this->button_1->Text = L"1";
	this->button_1->UseVisualStyleBackColor = false;
	this->button_1->Click += gcnew System::EventHandler(this, &OnScreenKeyboard::Number);
	// 
	// button_2
	// 
	this->button_2->BackColor = System::Drawing::SystemColors::Control;
	this->button_2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
		static_cast<System::Byte>(0)));
	this->button_2->Location = System::Drawing::Point(100, 0);
	this->button_2->Name = L"button_2";
	this->button_2->Size = System::Drawing::Size(75, 55);
	this->button_2->TabIndex = 27;
	this->button_2->Text = L"2";
	this->button_2->UseVisualStyleBackColor = false;
	this->button_2->Click += gcnew System::EventHandler(this, &OnScreenKeyboard::Number);
	// 
	// button_3
	// 
	this->button_3->BackColor = System::Drawing::SystemColors::Control;
	this->button_3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
		static_cast<System::Byte>(0)));
	this->button_3->Location = System::Drawing::Point(200, 0);
	this->button_3->Name = L"button_3";
	this->button_3->Size = System::Drawing::Size(75, 55);
	this->button_3->TabIndex = 28;
	this->button_3->Text = L"3";
	this->button_3->UseVisualStyleBackColor = false;
	this->button_3->Click += gcnew System::EventHandler(this, &OnScreenKeyboard::Number);
	// 
	// button_4
	// 
	this->button_4->BackColor = System::Drawing::SystemColors::Control;
	this->button_4->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
		static_cast<System::Byte>(0)));
	this->button_4->Location = System::Drawing::Point(300, 0);
	this->button_4->Name = L"button_4";
	this->button_4->Size = System::Drawing::Size(75, 55);
	this->button_4->TabIndex = 29;
	this->button_4->Text = L"4";
	this->button_4->UseVisualStyleBackColor = false;
	this->button_4->Click += gcnew System::EventHandler(this, &OnScreenKeyboard::Number);
	// 
	// button_5
	// 
	this->button_5->BackColor = System::Drawing::SystemColors::Control;
	this->button_5->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
		static_cast<System::Byte>(0)));
	this->button_5->Location = System::Drawing::Point(400, 0);
	this->button_5->Name = L"button_5";
	this->button_5->Size = System::Drawing::Size(75, 55);
	this->button_5->TabIndex = 30;
	this->button_5->Text = L"5";
	this->button_5->UseVisualStyleBackColor = false;
	this->button_5->Click += gcnew System::EventHandler(this, &OnScreenKeyboard::Number);
	// 
	// button_6
	// 
	this->button_6->BackColor = System::Drawing::SystemColors::Control;
	this->button_6->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
		static_cast<System::Byte>(0)));
	this->button_6->Location = System::Drawing::Point(500, 0);
	this->button_6->Name = L"button_6";
	this->button_6->Size = System::Drawing::Size(75, 55);
	this->button_6->TabIndex = 31;
	this->button_6->Text = L"6";
	this->button_6->UseVisualStyleBackColor = false;
	this->button_6->Click += gcnew System::EventHandler(this, &OnScreenKeyboard::Number);
	// 
	// button_7
	// 
	this->button_7->BackColor = System::Drawing::SystemColors::Control;
	this->button_7->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
		static_cast<System::Byte>(0)));
	this->button_7->Location = System::Drawing::Point(600, 0);
	this->button_7->Name = L"button_7";
	this->button_7->Size = System::Drawing::Size(75, 55);
	this->button_7->TabIndex = 32;
	this->button_7->Text = L"7";
	this->button_7->UseVisualStyleBackColor = false;
	this->button_7->Click += gcnew System::EventHandler(this, &OnScreenKeyboard::Number);
	// 
	// button_8
	// 
	this->button_8->BackColor = System::Drawing::SystemColors::Control;
	this->button_8->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
		static_cast<System::Byte>(0)));
	this->button_8->Location = System::Drawing::Point(700, 0);
	this->button_8->Name = L"button_8";
	this->button_8->Size = System::Drawing::Size(75, 55);
	this->button_8->TabIndex = 33;
	this->button_8->Text = L"8";
	this->button_8->UseVisualStyleBackColor = false;
	this->button_8->Click += gcnew System::EventHandler(this, &OnScreenKeyboard::Number);
	// 
	// button_9
	// 
	this->button_9->BackColor = System::Drawing::SystemColors::Control;
	this->button_9->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
		static_cast<System::Byte>(0)));
	this->button_9->Location = System::Drawing::Point(800, 0);
	this->button_9->Name = L"button_9";
	this->button_9->Size = System::Drawing::Size(75, 55);
	this->button_9->TabIndex = 34;
	this->button_9->Text = L"9";
	this->button_9->UseVisualStyleBackColor = false;
	this->button_9->Click += gcnew System::EventHandler(this, &OnScreenKeyboard::Number);
	// 
	// button_0
	// 
	this->button_0->BackColor = System::Drawing::SystemColors::Control;
	this->button_0->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
		static_cast<System::Byte>(0)));
	this->button_0->Location = System::Drawing::Point(900, 0);
	this->button_0->Name = L"button_0";
	this->button_0->Size = System::Drawing::Size(75, 55);
	this->button_0->TabIndex = 35;
	this->button_0->Text = L"0";
	this->button_0->UseVisualStyleBackColor = false;
	this->button_0->Click += gcnew System::EventHandler(this, &OnScreenKeyboard::Number);
	// 
	// button_backspace
	// 
	this->button_backspace->BackColor = System::Drawing::SystemColors::Control;
	this->button_backspace->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
		static_cast<System::Byte>(0)));
	this->button_backspace->Location = System::Drawing::Point(697, 196);
	this->button_backspace->Name = L"button_backspace";
	this->button_backspace->Size = System::Drawing::Size(150, 55);
	this->button_backspace->TabIndex = 36;
	this->button_backspace->Text = L"Backspace";
	this->button_backspace->UseVisualStyleBackColor = false;
	this->button_backspace->Click += gcnew System::EventHandler(this, &OnScreenKeyboard::button_backspace_Click);
	// 
	// button_space
	// 
	this->button_space->BackColor = System::Drawing::SystemColors::Control;
	this->button_space->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
		static_cast<System::Byte>(0)));
	this->button_space->Location = System::Drawing::Point(211, 276);
	this->button_space->Name = L"button_space";
	this->button_space->Size = System::Drawing::Size(150, 55);
	this->button_space->TabIndex = 37;
	this->button_space->Text = L"Space";
	this->button_space->UseVisualStyleBackColor = false;
	this->button_space->Click += gcnew System::EventHandler(this, &OnScreenKeyboard::button_space_Click);
	// 
	// button_enter
	// 
	this->button_enter->BackColor = System::Drawing::SystemColors::Control;
	this->button_enter->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
		static_cast<System::Byte>(0)));
	this->button_enter->Location = System::Drawing::Point(659, 276);
	this->button_enter->Name = L"button_enter";
	this->button_enter->Size = System::Drawing::Size(150, 55);
	this->button_enter->TabIndex = 38;
	this->button_enter->Text = L"Enter";
	this->button_enter->UseVisualStyleBackColor = false;
	this->button_enter->Click += gcnew System::EventHandler(this, &OnScreenKeyboard::button_enter_Click);
	// 
	// button_period
	// 
	this->button_period->BackColor = System::Drawing::SystemColors::Control;
	this->button_period->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
		static_cast<System::Byte>(0)));
	this->button_period->Location = System::Drawing::Point(49, 197);
	this->button_period->Name = L"button_period";
	this->button_period->Size = System::Drawing::Size(75, 55);
	this->button_period->TabIndex = 39;
	this->button_period->Text = L".";
	this->button_period->UseVisualStyleBackColor = false;
	this->button_period->Click += gcnew System::EventHandler(this, &OnScreenKeyboard::Symbol);
	// 
	// OnScreenKeyboard
	// 
	this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
	this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
	this->BackColor = System::Drawing::Color::Black;
	this->ClientSize = System::Drawing::Size(1015, 372);
	this->Controls->Add(this->button_period);
	this->Controls->Add(this->button_enter);
	this->Controls->Add(this->button_space);
	this->Controls->Add(this->button_backspace);
	this->Controls->Add(this->button_0);
	this->Controls->Add(this->button_9);
	this->Controls->Add(this->button_8);
	this->Controls->Add(this->button_7);
	this->Controls->Add(this->button_6);
	this->Controls->Add(this->button_5);
	this->Controls->Add(this->button_4);
	this->Controls->Add(this->button_3);
	this->Controls->Add(this->button_2);
	this->Controls->Add(this->button_1);
	this->Controls->Add(this->button_m);
	this->Controls->Add(this->button_n);
	this->Controls->Add(this->button_b);
	this->Controls->Add(this->button_v);
	this->Controls->Add(this->button_c);
	this->Controls->Add(this->button_x);
	this->Controls->Add(this->button_z);
	this->Controls->Add(this->button_l);
	this->Controls->Add(this->button_k);
	this->Controls->Add(this->button_j);
	this->Controls->Add(this->button_h);
	this->Controls->Add(this->button_g);
	this->Controls->Add(this->button_f);
	this->Controls->Add(this->button_d);
	this->Controls->Add(this->button_s);
	this->Controls->Add(this->button_a);
	this->Controls->Add(this->button_p);
	this->Controls->Add(this->button_o);
	this->Controls->Add(this->button_i);
	this->Controls->Add(this->button_u);
	this->Controls->Add(this->button_y);
	this->Controls->Add(this->button_t);
	this->Controls->Add(this->button_r);
	this->Controls->Add(this->button_e);
	this->Controls->Add(this->button_w);
	this->Controls->Add(this->button_q);
	this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
	this->Name = L"OnScreenKeyboard";
	this->Text = L"OnScreenKeyboard";
	this->TopMost = true;
	this->TransparencyKey = System::Drawing::Color::DarkViolet;
	this->Load += gcnew System::EventHandler(this, &OnScreenKeyboard::OnScreenKeyboard_Load);
	this->ResumeLayout(false);
}

System::Void OnScreenKeyboard::OnScreenKeyboard::OnScreenKeyboard_Load(System::Object^ sender, System::EventArgs^ e) {

	XmlTextReader^ reader = gcnew XmlTextReader("Keyboard_Config.xml");

	while (reader->Read())
	{
		switch (reader->NodeType)
		{
		case XmlNodeType::Element:
			if (msclr::interop::marshal_as<std::string>(reader->Name) == "ALPHABET")
			{
				while (reader->Read())
				{
					if (msclr::interop::marshal_as<std::string>(reader->Name) == "WIDTH")
					{
						ALPHABET_W = reader->ReadElementContentAsInt();
						NUMBER_W = ALPHABET_W;
						SYMBOL_W = ALPHABET_W;

					}
					else if (msclr::interop::marshal_as<std::string>(reader->Name) == "HEIGHT")
					{
						ALPHABET_H = reader->ReadElementContentAsInt();
						NUMBER_H = ALPHABET_H;
						SYMBOL_H = ALPHABET_H;
					}
					else if (msclr::interop::marshal_as<std::string>(reader->Name) == "ALPHABET") {
						break;
					}
				}
			}
			else if (msclr::interop::marshal_as<std::string>(reader->Name) == "SPACING")
			{
				while (reader->Read())
				{
					if (msclr::interop::marshal_as<std::string>(reader->Name) == "WIDTH")
					{
						SPACING_W = reader->ReadElementContentAsInt();

					}
					else if (msclr::interop::marshal_as<std::string>(reader->Name) == "HEIGHT")
					{
						SPACING_H = reader->ReadElementContentAsInt();
					}
					else if (msclr::interop::marshal_as<std::string>(reader->Name) == "SPACING") {
						break;
					}
				}
			}
			else if (msclr::interop::marshal_as<std::string>(reader->Name) == "TEXT")
			{
				while (reader->Read())
				{
					if (msclr::interop::marshal_as<std::string>(reader->Name) == "R")
					{
						TEXT_RED = reader->ReadElementContentAsInt();
					}
					else if (msclr::interop::marshal_as<std::string>(reader->Name) == "G")
					{
						TEXT_GREEN = reader->ReadElementContentAsInt();
					}
					else if (msclr::interop::marshal_as<std::string>(reader->Name) == "B")
					{
						TEXT_BLUE = reader->ReadElementContentAsInt();
					}
					else if (msclr::interop::marshal_as<std::string>(reader->Name) == "FONT_SIZE")
					{
						TEXT_SIZE = reader->ReadElementContentAsFloat();
					}
					else if (msclr::interop::marshal_as<std::string>(reader->Name) == "TEXT") {
						break;
					}
				}
			}
			else if (msclr::interop::marshal_as<std::string>(reader->Name) == "BUTTON_COLOUR")
			{
				while (reader->Read())
				{
					if (msclr::interop::marshal_as<std::string>(reader->Name) == "R")
					{
						FG_RED = reader->ReadElementContentAsInt();
					}
					else if (msclr::interop::marshal_as<std::string>(reader->Name) == "G")
					{
						FG_GREEN = reader->ReadElementContentAsInt();
					}
					else if (msclr::interop::marshal_as<std::string>(reader->Name) == "B") {
						FG_BLUE = reader->ReadElementContentAsInt();
					}
					else if (msclr::interop::marshal_as<std::string>(reader->Name) == "BUTTON_COLOUR") {
						break;
					}
				}
			}
			else if (msclr::interop::marshal_as<std::string>(reader->Name) == "BACKGROUND_COLOUR")
			{
				while (reader->Read())
				{
					if (msclr::interop::marshal_as<std::string>(reader->Name) == "R")
					{
						BG_RED = reader->ReadElementContentAsInt();
					}
					else if (msclr::interop::marshal_as<std::string>(reader->Name) == "G")
					{
						BG_GREEN = reader->ReadElementContentAsInt();
					}
					else if (msclr::interop::marshal_as<std::string>(reader->Name) == "B") {
						BG_BLUE = reader->ReadElementContentAsInt();
					}
					else if (msclr::interop::marshal_as<std::string>(reader->Name) == "BACKGROUND_COLOUR") {
						break;
					}
				}
			}
			break;
		}
		//switch (reader->NodeType)
		//{
		//case XmlNodeType::Element: // The node is an element.
		//	Console::Write("<{0}", reader->Name);

		//	while (reader->MoveToNextAttribute()) // Read the attributes.
		//		Console::Write(" {0}='{1}'", reader->Name, reader->Value);
		//	Console::WriteLine(">");
		//	break;
		//case XmlNodeType::Text: //Display the text in each element.
		//	Console::WriteLine(reader->Value);
		//	break;
		//case XmlNodeType::EndElement: //Display the end of the element.
		//	Console::Write("</{0}", reader->Name);
		//	Console::WriteLine(">");
		//	break;
		//}
	}
	reader->Close();	//Close XmlTextReader after use.

	int pos_x = SPACING_W, pos_y = SPACING_H;

	/*	Resize buttons using xml config values	*/
	button_q->Size = System::Drawing::Size(ALPHABET_W, ALPHABET_H);
	button_w->Size = System::Drawing::Size(ALPHABET_W, ALPHABET_H);
	button_e->Size = System::Drawing::Size(ALPHABET_W, ALPHABET_H);
	button_r->Size = System::Drawing::Size(ALPHABET_W, ALPHABET_H);
	button_t->Size = System::Drawing::Size(ALPHABET_W, ALPHABET_H);
	button_y->Size = System::Drawing::Size(ALPHABET_W, ALPHABET_H);
	button_u->Size = System::Drawing::Size(ALPHABET_W, ALPHABET_H);
	button_i->Size = System::Drawing::Size(ALPHABET_W, ALPHABET_H);
	button_o->Size = System::Drawing::Size(ALPHABET_W, ALPHABET_H);
	button_p->Size = System::Drawing::Size(ALPHABET_W, ALPHABET_H);
	button_a->Size = System::Drawing::Size(ALPHABET_W, ALPHABET_H);
	button_s->Size = System::Drawing::Size(ALPHABET_W, ALPHABET_H);
	button_d->Size = System::Drawing::Size(ALPHABET_W, ALPHABET_H);
	button_f->Size = System::Drawing::Size(ALPHABET_W, ALPHABET_H);
	button_g->Size = System::Drawing::Size(ALPHABET_W, ALPHABET_H);
	button_h->Size = System::Drawing::Size(ALPHABET_W, ALPHABET_H);
	button_j->Size = System::Drawing::Size(ALPHABET_W, ALPHABET_H);
	button_k->Size = System::Drawing::Size(ALPHABET_W, ALPHABET_H);
	button_l->Size = System::Drawing::Size(ALPHABET_W, ALPHABET_H);
	button_z->Size = System::Drawing::Size(ALPHABET_W, ALPHABET_H);
	button_x->Size = System::Drawing::Size(ALPHABET_W, ALPHABET_H);
	button_c->Size = System::Drawing::Size(ALPHABET_W, ALPHABET_H);
	button_v->Size = System::Drawing::Size(ALPHABET_W, ALPHABET_H);
	button_b->Size = System::Drawing::Size(ALPHABET_W, ALPHABET_H);
	button_n->Size = System::Drawing::Size(ALPHABET_W, ALPHABET_H);
	button_m->Size = System::Drawing::Size(ALPHABET_W, ALPHABET_H);
	button_1->Size = System::Drawing::Size(NUMBER_W, NUMBER_H);
	button_2->Size = System::Drawing::Size(NUMBER_W, NUMBER_H);
	button_3->Size = System::Drawing::Size(NUMBER_W, NUMBER_H);
	button_4->Size = System::Drawing::Size(NUMBER_W, NUMBER_H);
	button_5->Size = System::Drawing::Size(NUMBER_W, NUMBER_H);
	button_6->Size = System::Drawing::Size(NUMBER_W, NUMBER_H);
	button_7->Size = System::Drawing::Size(NUMBER_W, NUMBER_H);
	button_8->Size = System::Drawing::Size(NUMBER_W, NUMBER_H);
	button_9->Size = System::Drawing::Size(NUMBER_W, NUMBER_H);
	button_0->Size = System::Drawing::Size(NUMBER_W, NUMBER_H);
	button_period->Size = System::Drawing::Size(SYMBOL_W, SYMBOL_H);
	button_backspace->Size = System::Drawing::Size(1.5 * SYMBOL_W + SPACING_W, ALPHABET_H);
	button_space->Size = System::Drawing::Size(7 * SYMBOL_W + 6 * SPACING_W, ALPHABET_H);
	button_enter->Size = System::Drawing::Size(1.5 * SYMBOL_W + SPACING_W, ALPHABET_H);

	/*	Resize spacings using xml config values	*/
	//1st row
	button_1->Location = System::Drawing::Point(pos_x + 0 * (NUMBER_W + SPACING_W), pos_y);
	button_2->Location = System::Drawing::Point(pos_x + 1 * (NUMBER_W + SPACING_W), pos_y);
	button_3->Location = System::Drawing::Point(pos_x + 2 * (NUMBER_W + SPACING_W), pos_y);
	button_4->Location = System::Drawing::Point(pos_x + 3 * (NUMBER_W + SPACING_W), pos_y);
	button_5->Location = System::Drawing::Point(pos_x + 4 * (NUMBER_W + SPACING_W), pos_y);
	button_6->Location = System::Drawing::Point(pos_x + 5 * (NUMBER_W + SPACING_W), pos_y);
	button_7->Location = System::Drawing::Point(pos_x + 6 * (NUMBER_W + SPACING_W), pos_y);
	button_8->Location = System::Drawing::Point(pos_x + 7 * (NUMBER_W + SPACING_W), pos_y);
	button_9->Location = System::Drawing::Point(pos_x + 8 * (NUMBER_W + SPACING_W), pos_y);
	button_0->Location = System::Drawing::Point(pos_x + 9 * (NUMBER_W + SPACING_W), pos_y);

	//2nd row
	button_q->Location = System::Drawing::Point(pos_x + 0 * (ALPHABET_W + SPACING_W), pos_y + 1 * (NUMBER_H + SPACING_H));
	button_w->Location = System::Drawing::Point(pos_x + 1 * (ALPHABET_W + SPACING_W), pos_y + 1 * (NUMBER_H + SPACING_H));
	button_e->Location = System::Drawing::Point(pos_x + 2 * (ALPHABET_W + SPACING_W), pos_y + 1 * (NUMBER_H + SPACING_H));
	button_r->Location = System::Drawing::Point(pos_x + 3 * (ALPHABET_W + SPACING_W), pos_y + 1 * (NUMBER_H + SPACING_H));
	button_t->Location = System::Drawing::Point(pos_x + 4 * (ALPHABET_W + SPACING_W), pos_y + 1 * (NUMBER_H + SPACING_H));
	button_y->Location = System::Drawing::Point(pos_x + 5 * (ALPHABET_W + SPACING_W), pos_y + 1 * (NUMBER_H + SPACING_H));
	button_u->Location = System::Drawing::Point(pos_x + 6 * (ALPHABET_W + SPACING_W), pos_y + 1 * (NUMBER_H + SPACING_H));
	button_i->Location = System::Drawing::Point(pos_x + 7 * (ALPHABET_W + SPACING_W), pos_y + 1 * (NUMBER_H + SPACING_H));
	button_o->Location = System::Drawing::Point(pos_x + 8 * (ALPHABET_W + SPACING_W), pos_y + 1 * (NUMBER_H + SPACING_H));
	button_p->Location = System::Drawing::Point(pos_x + 9 * (ALPHABET_W + SPACING_W), pos_y + 1 * (NUMBER_H + SPACING_H));

	//3rd row
	button_a->Location = System::Drawing::Point(pos_x + 0 * (ALPHABET_W + SPACING_W) + (NUMBER_W / 2), pos_y + 1 * NUMBER_H + 1 * ALPHABET_H + 2 * SPACING_H);
	button_s->Location = System::Drawing::Point(pos_x + 1 * (ALPHABET_W + SPACING_W) + (NUMBER_W / 2), pos_y + 1 * NUMBER_H + 1 * ALPHABET_H + 2 * SPACING_H);
	button_d->Location = System::Drawing::Point(pos_x + 2 * (ALPHABET_W + SPACING_W) + (NUMBER_W / 2), pos_y + 1 * NUMBER_H + 1 * ALPHABET_H + 2 * SPACING_H);
	button_f->Location = System::Drawing::Point(pos_x + 3 * (ALPHABET_W + SPACING_W) + (NUMBER_W / 2), pos_y + 1 * NUMBER_H + 1 * ALPHABET_H + 2 * SPACING_H);
	button_g->Location = System::Drawing::Point(pos_x + 4 * (ALPHABET_W + SPACING_W) + (NUMBER_W / 2), pos_y + 1 * NUMBER_H + 1 * ALPHABET_H + 2 * SPACING_H);
	button_h->Location = System::Drawing::Point(pos_x + 5 * (ALPHABET_W + SPACING_W) + (NUMBER_W / 2), pos_y + 1 * NUMBER_H + 1 * ALPHABET_H + 2 * SPACING_H);
	button_j->Location = System::Drawing::Point(pos_x + 6 * (ALPHABET_W + SPACING_W) + (NUMBER_W / 2), pos_y + 1 * NUMBER_H + 1 * ALPHABET_H + 2 * SPACING_H);
	button_k->Location = System::Drawing::Point(pos_x + 7 * (ALPHABET_W + SPACING_W) + (NUMBER_W / 2), pos_y + 1 * NUMBER_H + 1 * ALPHABET_H + 2 * SPACING_H);
	button_l->Location = System::Drawing::Point(pos_x + 8 * (ALPHABET_W + SPACING_W) + (NUMBER_W / 2), pos_y + 1 * NUMBER_H + 1 * ALPHABET_H + 2 * SPACING_H);

	//4th row
	button_period->Location = System::Drawing::Point(pos_x + 0 * (NUMBER_W + SPACING_W) + (NUMBER_W / 2), pos_y + 1 * NUMBER_H + 2 * ALPHABET_H + 3 * SPACING_H);
	button_z->Location = System::Drawing::Point(pos_x + 0 * ALPHABET_W + 1 * SPACING_W + (NUMBER_W / 2) + SYMBOL_W, pos_y + 1 * NUMBER_H + 2 * ALPHABET_H + 3 * SPACING_H);
	button_x->Location = System::Drawing::Point(pos_x + 1 * ALPHABET_W + 2 * SPACING_W + (NUMBER_W / 2) + SYMBOL_W, pos_y + 1 * NUMBER_H + 2 * ALPHABET_H + 3 * SPACING_H);
	button_c->Location = System::Drawing::Point(pos_x + 2 * ALPHABET_W + 3 * SPACING_W + (NUMBER_W / 2) + SYMBOL_W, pos_y + 1 * NUMBER_H + 2 * ALPHABET_H + 3 * SPACING_H);
	button_v->Location = System::Drawing::Point(pos_x + 3 * ALPHABET_W + 4 * SPACING_W + (NUMBER_W / 2) + SYMBOL_W, pos_y + 1 * NUMBER_H + 2 * ALPHABET_H + 3 * SPACING_H);
	button_b->Location = System::Drawing::Point(pos_x + 4 * ALPHABET_W + 5 * SPACING_W + (NUMBER_W / 2) + SYMBOL_W, pos_y + 1 * NUMBER_H + 2 * ALPHABET_H + 3 * SPACING_H);
	button_n->Location = System::Drawing::Point(pos_x + 5 * ALPHABET_W + 6 * SPACING_W + (NUMBER_W / 2) + SYMBOL_W, pos_y + 1 * NUMBER_H + 2 * ALPHABET_H + 3 * SPACING_H);
	button_m->Location = System::Drawing::Point(pos_x + 6 * ALPHABET_W + 7 * SPACING_W + (NUMBER_W / 2) + SYMBOL_W, pos_y + 1 * NUMBER_H + 2 * ALPHABET_H + 3 * SPACING_H);
	button_backspace->Location = System::Drawing::Point(pos_x + 7 * ALPHABET_W + 8 * SPACING_W + (NUMBER_W / 2) + SYMBOL_W, pos_y + 1 * NUMBER_H + 2 * ALPHABET_H + 3 * SPACING_H);

	//5th row
	button_space->Location = System::Drawing::Point(pos_x + 0 * ALPHABET_W + 1 * SPACING_W + (NUMBER_W / 2) + SYMBOL_W, pos_y + 1 * NUMBER_H + 3 * ALPHABET_H + 4 * SPACING_H);
	button_enter->Location = System::Drawing::Point(pos_x + 7 * ALPHABET_W + 8 * SPACING_W + (NUMBER_W / 2) + SYMBOL_W, pos_y + 1 * NUMBER_H + 3 * ALPHABET_H + 4 * SPACING_H);

	/*	Resize keyboard window	*/
	ClientSize = System::Drawing::Size(10 * ALPHABET_W + 11 * SPACING_W, 5 * ALPHABET_H + 6 * SPACING_H);

	/* Change button color */
	//1st row
	button_1->BackColor = Color::FromArgb(FG_RED, FG_GREEN, FG_BLUE);
	button_2->BackColor = Color::FromArgb(FG_RED, FG_GREEN, FG_BLUE);
	button_3->BackColor = Color::FromArgb(FG_RED, FG_GREEN, FG_BLUE);
	button_4->BackColor = Color::FromArgb(FG_RED, FG_GREEN, FG_BLUE);
	button_5->BackColor = Color::FromArgb(FG_RED, FG_GREEN, FG_BLUE);
	button_6->BackColor = Color::FromArgb(FG_RED, FG_GREEN, FG_BLUE);
	button_7->BackColor = Color::FromArgb(FG_RED, FG_GREEN, FG_BLUE);
	button_8->BackColor = Color::FromArgb(FG_RED, FG_GREEN, FG_BLUE);
	button_9->BackColor = Color::FromArgb(FG_RED, FG_GREEN, FG_BLUE);
	button_0->BackColor = Color::FromArgb(FG_RED, FG_GREEN, FG_BLUE);

	//2nd row
	button_q->BackColor = Color::FromArgb(FG_RED, FG_GREEN, FG_BLUE);
	button_w->BackColor = Color::FromArgb(FG_RED, FG_GREEN, FG_BLUE);
	button_e->BackColor = Color::FromArgb(FG_RED, FG_GREEN, FG_BLUE);
	button_r->BackColor = Color::FromArgb(FG_RED, FG_GREEN, FG_BLUE);
	button_t->BackColor = Color::FromArgb(FG_RED, FG_GREEN, FG_BLUE);
	button_y->BackColor = Color::FromArgb(FG_RED, FG_GREEN, FG_BLUE);
	button_u->BackColor = Color::FromArgb(FG_RED, FG_GREEN, FG_BLUE);
	button_i->BackColor = Color::FromArgb(FG_RED, FG_GREEN, FG_BLUE);
	button_o->BackColor = Color::FromArgb(FG_RED, FG_GREEN, FG_BLUE);
	button_p->BackColor = Color::FromArgb(FG_RED, FG_GREEN, FG_BLUE);

	//3rd row
	button_a->BackColor = Color::FromArgb(FG_RED, FG_GREEN, FG_BLUE);
	button_s->BackColor = Color::FromArgb(FG_RED, FG_GREEN, FG_BLUE);
	button_d->BackColor = Color::FromArgb(FG_RED, FG_GREEN, FG_BLUE);
	button_f->BackColor = Color::FromArgb(FG_RED, FG_GREEN, FG_BLUE);
	button_g->BackColor = Color::FromArgb(FG_RED, FG_GREEN, FG_BLUE);
	button_h->BackColor = Color::FromArgb(FG_RED, FG_GREEN, FG_BLUE);
	button_j->BackColor = Color::FromArgb(FG_RED, FG_GREEN, FG_BLUE);
	button_k->BackColor = Color::FromArgb(FG_RED, FG_GREEN, FG_BLUE);
	button_l->BackColor = Color::FromArgb(FG_RED, FG_GREEN, FG_BLUE);

	//4th row
	button_z->BackColor = Color::FromArgb(FG_RED, FG_GREEN, FG_BLUE);
	button_x->BackColor = Color::FromArgb(FG_RED, FG_GREEN, FG_BLUE);
	button_c->BackColor = Color::FromArgb(FG_RED, FG_GREEN, FG_BLUE);
	button_v->BackColor = Color::FromArgb(FG_RED, FG_GREEN, FG_BLUE);
	button_b->BackColor = Color::FromArgb(FG_RED, FG_GREEN, FG_BLUE);
	button_n->BackColor = Color::FromArgb(FG_RED, FG_GREEN, FG_BLUE);
	button_m->BackColor = Color::FromArgb(FG_RED, FG_GREEN, FG_BLUE);
	button_backspace->BackColor = Color::FromArgb(FG_RED, FG_GREEN, FG_BLUE);
	button_period->BackColor = Color::FromArgb(FG_RED, FG_GREEN, FG_BLUE);

	//5th row
	button_space->BackColor = Color::FromArgb(FG_RED, FG_GREEN, FG_BLUE);
	button_enter->BackColor = Color::FromArgb(FG_RED, FG_GREEN, FG_BLUE);

	/* Change background colour */
	BackColor = Color::FromArgb(BG_RED, BG_GREEN, BG_BLUE);

	/* Change Text color and font size */
	//1st row
	button_1->ForeColor = Color::FromArgb(TEXT_RED, TEXT_GREEN, TEXT_BLUE);
	button_2->ForeColor = Color::FromArgb(TEXT_RED, TEXT_GREEN, TEXT_BLUE);
	button_3->ForeColor = Color::FromArgb(TEXT_RED, TEXT_GREEN, TEXT_BLUE);
	button_4->ForeColor = Color::FromArgb(TEXT_RED, TEXT_GREEN, TEXT_BLUE);
	button_5->ForeColor = Color::FromArgb(TEXT_RED, TEXT_GREEN, TEXT_BLUE);
	button_6->ForeColor = Color::FromArgb(TEXT_RED, TEXT_GREEN, TEXT_BLUE);
	button_7->ForeColor = Color::FromArgb(TEXT_RED, TEXT_GREEN, TEXT_BLUE);
	button_8->ForeColor = Color::FromArgb(TEXT_RED, TEXT_GREEN, TEXT_BLUE);
	button_9->ForeColor = Color::FromArgb(TEXT_RED, TEXT_GREEN, TEXT_BLUE);
	button_0->ForeColor = Color::FromArgb(TEXT_RED, TEXT_GREEN, TEXT_BLUE);

	//2nd row
	button_q->ForeColor = Color::FromArgb(TEXT_RED, TEXT_GREEN, TEXT_BLUE);
	button_w->ForeColor = Color::FromArgb(TEXT_RED, TEXT_GREEN, TEXT_BLUE);
	button_e->ForeColor = Color::FromArgb(TEXT_RED, TEXT_GREEN, TEXT_BLUE);
	button_r->ForeColor = Color::FromArgb(TEXT_RED, TEXT_GREEN, TEXT_BLUE);
	button_t->ForeColor = Color::FromArgb(TEXT_RED, TEXT_GREEN, TEXT_BLUE);
	button_y->ForeColor = Color::FromArgb(TEXT_RED, TEXT_GREEN, TEXT_BLUE);
	button_u->ForeColor = Color::FromArgb(TEXT_RED, TEXT_GREEN, TEXT_BLUE);
	button_i->ForeColor = Color::FromArgb(TEXT_RED, TEXT_GREEN, TEXT_BLUE);
	button_o->ForeColor = Color::FromArgb(TEXT_RED, TEXT_GREEN, TEXT_BLUE);
	button_p->ForeColor = Color::FromArgb(TEXT_RED, TEXT_GREEN, TEXT_BLUE);

	//3rd row
	button_a->ForeColor = Color::FromArgb(TEXT_RED, TEXT_GREEN, TEXT_BLUE);
	button_s->ForeColor = Color::FromArgb(TEXT_RED, TEXT_GREEN, TEXT_BLUE);
	button_d->ForeColor = Color::FromArgb(TEXT_RED, TEXT_GREEN, TEXT_BLUE);
	button_f->ForeColor = Color::FromArgb(TEXT_RED, TEXT_GREEN, TEXT_BLUE);
	button_g->ForeColor = Color::FromArgb(TEXT_RED, TEXT_GREEN, TEXT_BLUE);
	button_h->ForeColor = Color::FromArgb(TEXT_RED, TEXT_GREEN, TEXT_BLUE);
	button_j->ForeColor = Color::FromArgb(TEXT_RED, TEXT_GREEN, TEXT_BLUE);
	button_k->ForeColor = Color::FromArgb(TEXT_RED, TEXT_GREEN, TEXT_BLUE);
	button_l->ForeColor = Color::FromArgb(TEXT_RED, TEXT_GREEN, TEXT_BLUE);

	//4th row
	button_z->ForeColor = Color::FromArgb(TEXT_RED, TEXT_GREEN, TEXT_BLUE);
	button_x->ForeColor = Color::FromArgb(TEXT_RED, TEXT_GREEN, TEXT_BLUE);
	button_c->ForeColor = Color::FromArgb(TEXT_RED, TEXT_GREEN, TEXT_BLUE);
	button_v->ForeColor = Color::FromArgb(TEXT_RED, TEXT_GREEN, TEXT_BLUE);
	button_b->ForeColor = Color::FromArgb(TEXT_RED, TEXT_GREEN, TEXT_BLUE);
	button_n->ForeColor = Color::FromArgb(TEXT_RED, TEXT_GREEN, TEXT_BLUE);
	button_m->ForeColor = Color::FromArgb(TEXT_RED, TEXT_GREEN, TEXT_BLUE);
	button_period->ForeColor = Color::FromArgb(TEXT_RED, TEXT_GREEN, TEXT_BLUE);
	button_backspace->ForeColor = Color::FromArgb(TEXT_RED, TEXT_GREEN, TEXT_BLUE);

	//5th row
	button_space->ForeColor = Color::FromArgb(TEXT_RED, TEXT_GREEN, TEXT_BLUE);
	button_enter->ForeColor = Color::FromArgb(TEXT_RED, TEXT_GREEN, TEXT_BLUE);

	/* Change font size	*/
	//1st row
	button_1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", TEXT_SIZE, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
		static_cast<System::Byte>(0)));
	button_2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", TEXT_SIZE, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
		static_cast<System::Byte>(0)));
	button_3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", TEXT_SIZE, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
		static_cast<System::Byte>(0)));
	button_4->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", TEXT_SIZE, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
		static_cast<System::Byte>(0)));
	button_5->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", TEXT_SIZE, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
		static_cast<System::Byte>(0)));
	button_6->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", TEXT_SIZE, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
		static_cast<System::Byte>(0)));
	button_7->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", TEXT_SIZE, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
		static_cast<System::Byte>(0)));
	button_8->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", TEXT_SIZE, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
		static_cast<System::Byte>(0)));
	button_9->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", TEXT_SIZE, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
		static_cast<System::Byte>(0)));
	button_0->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", TEXT_SIZE, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
		static_cast<System::Byte>(0)));

	//2nd row
	button_q->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", TEXT_SIZE, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
		static_cast<System::Byte>(0)));
	button_w->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", TEXT_SIZE, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
		static_cast<System::Byte>(0)));
	button_e->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", TEXT_SIZE, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
		static_cast<System::Byte>(0)));
	button_r->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", TEXT_SIZE, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
		static_cast<System::Byte>(0)));
	button_t->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", TEXT_SIZE, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
		static_cast<System::Byte>(0)));
	button_y->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", TEXT_SIZE, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
		static_cast<System::Byte>(0)));
	button_u->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", TEXT_SIZE, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
		static_cast<System::Byte>(0)));
	button_i->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", TEXT_SIZE, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
		static_cast<System::Byte>(0)));
	button_o->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", TEXT_SIZE, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
		static_cast<System::Byte>(0)));
	button_p->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", TEXT_SIZE, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
		static_cast<System::Byte>(0)));

	//3rd row
	button_a->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", TEXT_SIZE, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
		static_cast<System::Byte>(0)));
	button_s->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", TEXT_SIZE, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
		static_cast<System::Byte>(0)));
	button_d->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", TEXT_SIZE, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
		static_cast<System::Byte>(0)));
	button_f->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", TEXT_SIZE, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
		static_cast<System::Byte>(0)));
	button_g->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", TEXT_SIZE, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
		static_cast<System::Byte>(0)));
	button_h->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", TEXT_SIZE, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
		static_cast<System::Byte>(0)));
	button_j->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", TEXT_SIZE, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
		static_cast<System::Byte>(0)));
	button_k->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", TEXT_SIZE, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
		static_cast<System::Byte>(0)));
	button_l->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", TEXT_SIZE, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
		static_cast<System::Byte>(0)));

	//4th row
	button_z->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", TEXT_SIZE, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
		static_cast<System::Byte>(0)));
	button_x->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", TEXT_SIZE, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
		static_cast<System::Byte>(0)));
	button_c->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", TEXT_SIZE, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
		static_cast<System::Byte>(0)));
	button_v->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", TEXT_SIZE, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
		static_cast<System::Byte>(0)));
	button_b->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", TEXT_SIZE, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
		static_cast<System::Byte>(0)));
	button_n->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", TEXT_SIZE, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
		static_cast<System::Byte>(0)));
	button_m->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", TEXT_SIZE, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
		static_cast<System::Byte>(0)));
	button_period->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", TEXT_SIZE, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
		static_cast<System::Byte>(0)));
	button_backspace->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", TEXT_SIZE, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
		static_cast<System::Byte>(0)));

	//5th row
	button_space->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", TEXT_SIZE, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
		static_cast<System::Byte>(0)));
	button_enter->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", TEXT_SIZE, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
		static_cast<System::Byte>(0)));
}

System::Void OnScreenKeyboard::OnScreenKeyboard::Alphabet(System::Object^ sender, System::EventArgs^ e) {
	Button^ character = safe_cast<Button^>(sender);
	SendKeys::Send(character->Text);
}

System::Void OnScreenKeyboard::OnScreenKeyboard::button_enter_Click(System::Object^ sender, System::EventArgs^ e) {
	SendKeys::Send("{ENTER}");
}

System::Void OnScreenKeyboard::OnScreenKeyboard::button_backspace_Click(System::Object^ sender, System::EventArgs^ e) {
	SendKeys::Send("{BACKSPACE}");
}

System::Void OnScreenKeyboard::OnScreenKeyboard::button_space_Click(System::Object^ sender, System::EventArgs^ e) {
	SendKeys::Send(" ");
}

System::Void OnScreenKeyboard::OnScreenKeyboard::Number(System::Object^ sender, System::EventArgs^ e) {
	Button^ character = safe_cast<Button^>(sender);
	SendKeys::Send(character->Text);
}

System::Void OnScreenKeyboard::OnScreenKeyboard::Symbol(System::Object^ sender, System::EventArgs^ e) {
	Button^ character = safe_cast<Button^>(sender);
	SendKeys::Send(character->Text);
}

void main(array<String^>^ args) {
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	OnScreenKeyboard::OnScreenKeyboard OSK;
	Application::Run(% OSK);
}