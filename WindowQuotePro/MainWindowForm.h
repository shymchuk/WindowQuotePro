#pragma once

namespace WindowQuotePro {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Data;
	using namespace System::Data::SQLite;
	using namespace System::IO;

	/// <summary>
	/// Main window form of the application
	/// </summary>
	public ref class MainWindowForm : public System::Windows::Forms::Form
	{
	public:
		MainWindowForm(void);

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MainWindowForm();

	private: System::Windows::Forms::Button^ newQuoteBtn;
	private: System::Windows::Forms::DataGridView^ quotesGridView;
	private: System::Windows::Forms::Button^ deleteQuoteBtn;
	private: System::Windows::Forms::Button^ updateQuoteBtn;

	protected:

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
		void InitializeComponent(void)
		{
			this->newQuoteBtn = (gcnew System::Windows::Forms::Button());
			this->quotesGridView = (gcnew System::Windows::Forms::DataGridView());
			this->deleteQuoteBtn = (gcnew System::Windows::Forms::Button());
			this->updateQuoteBtn = (gcnew System::Windows::Forms::Button());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->quotesGridView))->BeginInit();
			this->SuspendLayout();
			// 
			// newQuoteBtn
			// 
			this->newQuoteBtn->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->newQuoteBtn->Location = System::Drawing::Point(449, 12);
			this->newQuoteBtn->Name = L"newQuoteBtn";
			this->newQuoteBtn->Size = System::Drawing::Size(75, 23);
			this->newQuoteBtn->TabIndex = 0;
			this->newQuoteBtn->Text = L"New quote";
			this->newQuoteBtn->UseVisualStyleBackColor = true;
			this->newQuoteBtn->Click += gcnew System::EventHandler(this, &MainWindowForm::newQuoteBtn_Click);
			// 
			// quotesGridView
			// 
			this->quotesGridView->AllowUserToAddRows = false;
			this->quotesGridView->AllowUserToDeleteRows = false;
			this->quotesGridView->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->quotesGridView->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->quotesGridView->Location = System::Drawing::Point(12, 12);
			this->quotesGridView->Name = L"quotesGridView";
			this->quotesGridView->Size = System::Drawing::Size(431, 312);
			this->quotesGridView->TabIndex = 1;
			this->quotesGridView->CellValueChanged += gcnew System::Windows::Forms::DataGridViewCellEventHandler(this, &MainWindowForm::quotesGridView_CellValueChanged);
			this->quotesGridView->DataError += gcnew System::Windows::Forms::DataGridViewDataErrorEventHandler(this, &MainWindowForm::quotesGridView_DataError);
			this->quotesGridView->SelectionChanged += gcnew System::EventHandler(this, &MainWindowForm::quotesGridView_SelectionChanged);
			// 
			// deleteQuoteBtn
			// 
			this->deleteQuoteBtn->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->deleteQuoteBtn->Enabled = false;
			this->deleteQuoteBtn->Location = System::Drawing::Point(449, 70);
			this->deleteQuoteBtn->Name = L"deleteQuoteBtn";
			this->deleteQuoteBtn->Size = System::Drawing::Size(75, 23);
			this->deleteQuoteBtn->TabIndex = 2;
			this->deleteQuoteBtn->Text = L"Delete";
			this->deleteQuoteBtn->UseVisualStyleBackColor = true;
			this->deleteQuoteBtn->Click += gcnew System::EventHandler(this, &MainWindowForm::deleteQuoteBtn_Click);
			// 
			// updateQuoteBtn
			// 
			this->updateQuoteBtn->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->updateQuoteBtn->Enabled = false;
			this->updateQuoteBtn->Location = System::Drawing::Point(449, 41);
			this->updateQuoteBtn->Name = L"updateQuoteBtn";
			this->updateQuoteBtn->Size = System::Drawing::Size(75, 23);
			this->updateQuoteBtn->TabIndex = 0;
			this->updateQuoteBtn->Text = L"Update";
			this->updateQuoteBtn->UseVisualStyleBackColor = true;
			this->updateQuoteBtn->Click += gcnew System::EventHandler(this, &MainWindowForm::updateQuoteBtn_Click);
			// 
			// MainWindowForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(532, 336);
			this->Controls->Add(this->deleteQuoteBtn);
			this->Controls->Add(this->quotesGridView);
			this->Controls->Add(this->updateQuoteBtn);
			this->Controls->Add(this->newQuoteBtn);
			this->Name = L"MainWindowForm";
			this->Text = L"MainWindowForm";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->quotesGridView))->EndInit();
			this->ResumeLayout(false);

		}
#pragma endregion
	private: 
		ref class UpdateRowHandler
		{
		private:
			DataGridView^ view;
			DataGridViewRow^ row;
		public:
			UpdateRowHandler(DataGridView^ view, DataGridViewRow^ row);
			Void updateQuoteWindow_FormClosed(System::Object^ sender, System::Windows::Forms::FormClosedEventArgs^ e);
		};

		Void newQuoteBtn_Click(System::Object^ sender, System::EventArgs^ e);
		Void addQuoteWindow_FormClosed(System::Object^ sender, System::Windows::Forms::FormClosedEventArgs^ e);
		Void updateQuoteBtn_Click(System::Object^ sender, System::EventArgs^ e);
		Void quotesGridView_CellValueChanged(System::Object^ sender, System::Windows::Forms::DataGridViewCellEventArgs^ e);
		Void quotesGridView_DataError(System::Object^ sender, System::Windows::Forms::DataGridViewDataErrorEventArgs^ e);
		Void deleteQuoteBtn_Click(System::Object^ sender, System::EventArgs^ e);
		Void quotesGridView_SelectionChanged(System::Object^ sender, System::EventArgs^ e);
	};
}
