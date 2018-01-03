#pragma once

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;
using namespace System::Threading;


namespace BicRF {

	/// <summary>
	/// Сводка для ProgressBarForm
	///
	/// Внимание! При изменении имени этого класса необходимо также изменить
	///          свойство имени файла ресурсов ("Resource File Name") для средства компиляции управляемого ресурса,
	///          связанного со всеми файлами с расширением .resx, от которых зависит данный класс. В противном случае,
	///          конструкторы не смогут правильно работать с локализованными
	///          ресурсами, сопоставленными данной форме.
	/// </summary>
	public ref class ProgressBarForm : public System::Windows::Forms::Form
	{
		Point FormLocation;

		// Мьютекс, регулирующий доступ к свойству Progress
		Mutex ^rProgressMutex; 

		// Значение прогресса, от 0 до 100
		int ProgressValue;

		String ^OperationValue;

	public:
		ProgressBarForm( Point location, String^ _Title )
		{
			InitializeComponent();
			//
			//TODO: добавьте код конструктора
			//

			ProgressValue = 0;
//			Title = _Title;
			Text = _Title;

			// Создаем мьютекс
			rProgressMutex = gcnew Mutex;
			
			FormLocation = location;
		}
	private: System::Windows::Forms::Timer^  timer1;
	public: 

		property int Progress {

			int get() {
				int value = 0;
				rProgressMutex->WaitOne();
				value = ProgressValue;
				rProgressMutex->ReleaseMutex();
				return value;
			  }

			void set( int value ) {
				rProgressMutex->WaitOne();
				ProgressValue = value;
				rProgressMutex->ReleaseMutex();
			}
		} 		

		property String^ Operation {

			String^ get () { 
				String^ operation;
				rProgressMutex->WaitOne();
				operation = OperationValue; 
				rProgressMutex->ReleaseMutex();
				return operation;
			}

			void set (String^ _operation) { 
				rProgressMutex->WaitOne();
				OperationValue = _operation; 
				rProgressMutex->ReleaseMutex();
			}
		}

	protected:
		/// <summary>
		/// Освободить все используемые ресурсы.
		/// </summary>
		~ProgressBarForm()
		{
			if (components)
			{
				delete components;
			}

			delete rProgressMutex;
		}
	private: System::Windows::Forms::ProgressBar^  progressBar1;
	protected: 
	private: System::Windows::Forms::Label^  label1;
	private: System::ComponentModel::IContainer^  components;

	private:
		/// <summary>
		/// Требуется переменная конструктора.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Обязательный метод для поддержки конструктора - не изменяйте
		/// содержимое данного метода при помощи редактора кода.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			this->progressBar1 = (gcnew System::Windows::Forms::ProgressBar());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
			this->SuspendLayout();
			// 
			// progressBar1
			// 
			this->progressBar1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->progressBar1->Location = System::Drawing::Point(12, 39);
			this->progressBar1->Name = L"progressBar1";
			this->progressBar1->Size = System::Drawing::Size(555, 20);
			this->progressBar1->TabIndex = 0;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(13, 13);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(139, 13);
			this->label1->TabIndex = 1;
			this->label1->Text = L"Информация об операции";
			// 
			// timer1
			// 
			this->timer1->Interval = 500;
			this->timer1->Tick += gcnew System::EventHandler(this, &ProgressBarForm::timer1_Tick);
			// 
			// ProgressBarForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(579, 71);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->progressBar1);
			this->Name = L"ProgressBarForm";
			this->Text = L"Кратко о процессе";
			this->Shown += gcnew System::EventHandler(this, &ProgressBarForm::ProgressBarForm_Shown);
			this->FormClosing += gcnew System::Windows::Forms::FormClosingEventHandler(this, &ProgressBarForm::ProgressBarForm_FormClosing);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void ProgressBarForm_FormClosing(System::Object^  sender, System::Windows::Forms::FormClosingEventArgs^  e) {
			 }
	private: System::Void timer1_Tick(System::Object^  sender, System::EventArgs^  e) {
				 if (Progress == 100)
				 {
					 timer1->Enabled = false;
					 Threading::Thread::Sleep( 500 );
					 Close();
				 }
				 progressBar1->Value = Progress;
				 label1->Text = Operation;
			 }

	private: System::Void ProgressBarForm_Shown(System::Object^  sender, System::EventArgs^  e) {
	 			 Location = FormLocation;
//				 Text = Title;
				 timer1->Enabled = true;
			 }
	};
}
