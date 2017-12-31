#pragma once

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;

namespace BicRF {

	/// <summary>
	/// Сводка для TunesForm
	///
	/// Внимание! При изменении имени этого класса необходимо также изменить
	///          свойство имени файла ресурсов ("Resource File Name") для средства компиляции управляемого ресурса,
	///          связанного со всеми файлами с расширением .resx, от которых зависит данный класс. В противном случае,
	///          конструкторы не смогут правильно работать с локализованными
	///          ресурсами, сопоставленными данной форме.
	/// </summary>
	public ref class TunesForm : public System::Windows::Forms::Form
	{
		Point FormLocation;

	public:
		TunesForm( String ^_DBServerName, Point location )
		{
			InitializeComponent();
			//
			//TODO: добавьте код конструктора
			//

			DBServerName = _DBServerName;
			FormLocation = location;
		}

		property String^ DBServerName;

	protected:
		/// <summary>
		/// Освободить все используемые ресурсы.
		/// </summary>
		~TunesForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::TextBox^  DBServerName_TextBox;
	protected: 

	private: System::Windows::Forms::Button^  button1;
	private: System::Windows::Forms::Button^  button2;

	private:
		/// <summary>
		/// Требуется переменная конструктора.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Обязательный метод для поддержки конструктора - не изменяйте
		/// содержимое данного метода при помощи редактора кода.
		/// </summary>
		void InitializeComponent(void)
		{
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->DBServerName_TextBox = (gcnew System::Windows::Forms::TextBox());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(13, 13);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(246, 13);
			this->label1->TabIndex = 0;
			this->label1->Text = L"Сервер БД (например, localhost\\SQLEXPRESS)";
			// 
			// DBServerName_TextBox
			// 
			this->DBServerName_TextBox->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->DBServerName_TextBox->Location = System::Drawing::Point(39, 30);
			this->DBServerName_TextBox->Name = L"DBServerName_TextBox";
			this->DBServerName_TextBox->Size = System::Drawing::Size(403, 20);
			this->DBServerName_TextBox->TabIndex = 1;
			this->DBServerName_TextBox->TextChanged += gcnew System::EventHandler(this, &TunesForm::textBox1_TextChanged);
			// 
			// button1
			// 
			this->button1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
			this->button1->DialogResult = System::Windows::Forms::DialogResult::OK;
			this->button1->Location = System::Drawing::Point(286, 57);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(75, 23);
			this->button1->TabIndex = 2;
			this->button1->Text = L"Сохранить";
			this->button1->UseVisualStyleBackColor = true;
			// 
			// button2
			// 
			this->button2->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
			this->button2->DialogResult = System::Windows::Forms::DialogResult::Cancel;
			this->button2->Location = System::Drawing::Point(367, 57);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(75, 23);
			this->button2->TabIndex = 3;
			this->button2->Text = L"Отмена";
			this->button2->UseVisualStyleBackColor = true;
			// 
			// TunesForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(454, 92);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->DBServerName_TextBox);
			this->Controls->Add(this->label1);
			this->MinimumSize = System::Drawing::Size(470, 130);
			this->Name = L"TunesForm";
			this->Text = L"Настройки";
			this->FormClosing += gcnew System::Windows::Forms::FormClosingEventHandler(this, &TunesForm::TunesForm_FormClosing);
			this->Load += gcnew System::EventHandler(this, &TunesForm::TunesForm_Load);
			this->Shown += gcnew System::EventHandler(this, &TunesForm::TunesForm_Shown);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void textBox1_TextChanged(System::Object^  sender, System::EventArgs^  e) {
			 }
	private: System::Void TunesForm_Load(System::Object^  sender, System::EventArgs^  e) {
				DBServerName_TextBox->Text = DBServerName;
			 }

	private: System::Void TunesForm_FormClosing(System::Object^  sender, System::Windows::Forms::FormClosingEventArgs^  e) {

				 DBServerName = DBServerName_TextBox->Text;
			 }

private: System::Void TunesForm_Shown(System::Object^  sender, System::EventArgs^  e) {

			 Location = FormLocation;
		 }
};
}
