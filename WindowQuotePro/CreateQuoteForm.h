#pragma once

namespace WindowQuotePro {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Threading::Tasks;

	/// <summary>
	/// Form for creating a new quote
	/// </summary>
	public ref class CreateQuoteForm : public System::Windows::Forms::Form
	{
	private:

		bool accepted = false;

	public:

		enum class Mode
		{
			Create,
			Update
		};

		CreateQuoteForm(String^ title, Mode mode);

		CreateQuoteForm(String^ title, Mode mode, String^ quoteName, String^ customerName, Int32 material, Int32 size, double price);

		property String^ QuoteName
		{
			String^ get() { return quoteNameTextBox->Text; }
		}

		property String^ CustomerName
		{
			String^ get() { return customerNameTextBox->Text; }
		}

		property Int32 Material
		{
			Int32 get() { return materialComboBox->SelectedIndex; }
		}

		property Int32 Size
		{
			Int32 get() { return sizeComboBox->SelectedIndex; }
		}

		property bool Accepted
		{
			bool get() { return accepted; }
		}

		property double Price
		{
			double get();
		}

	protected:

		void OnHandleCreated(EventArgs^ e) override;

		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~CreateQuoteForm();
	private:
		/// <summary>
		/// Update the price text box with the calculated price
		/// </summary>
		void CalculateAndSetPrice();

		// Callbacks for the price 
		void PriceTaskCompleted(Task<double>^ t);
		void UpdatePrice(String^ text);

		ref class CalculatePriceWrapper
		{
		private:
			String^ material;
			String^ size;
		public:

			CalculatePriceWrapper(String^ material, String^ size);
			double CalculatePrice();
		};

	private: System::Windows::Forms::TextBox^ quoteNameTextBox;
	private: System::Windows::Forms::TextBox^ customerNameTextBox;
	private: System::Windows::Forms::Label^ quoteNameLbl;
	private: System::Windows::Forms::Label^ customerNameLbl;
	private: System::Windows::Forms::ComboBox^ materialComboBox;
	private: System::Windows::Forms::ComboBox^ sizeComboBox;
	private: System::Windows::Forms::Label^ materialLbl;
	private: System::Windows::Forms::Label^ sizeLbl;
	private: System::Windows::Forms::TextBox^ priceTextBox;
	private: System::Windows::Forms::Label^ priceLbl;
	private: System::Windows::Forms::Button^ cancelBtn;
	private: System::Windows::Forms::Button^ createBtn;

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
			this->quoteNameTextBox = (gcnew System::Windows::Forms::TextBox());
			this->customerNameTextBox = (gcnew System::Windows::Forms::TextBox());
			this->quoteNameLbl = (gcnew System::Windows::Forms::Label());
			this->customerNameLbl = (gcnew System::Windows::Forms::Label());
			this->materialComboBox = (gcnew System::Windows::Forms::ComboBox());
			this->sizeComboBox = (gcnew System::Windows::Forms::ComboBox());
			this->materialLbl = (gcnew System::Windows::Forms::Label());
			this->sizeLbl = (gcnew System::Windows::Forms::Label());
			this->priceTextBox = (gcnew System::Windows::Forms::TextBox());
			this->priceLbl = (gcnew System::Windows::Forms::Label());
			this->cancelBtn = (gcnew System::Windows::Forms::Button());
			this->createBtn = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// quoteNameTextBox
			// 
			this->quoteNameTextBox->Location = System::Drawing::Point(64, 15);
			this->quoteNameTextBox->Name = L"quoteNameTextBox";
			this->quoteNameTextBox->Size = System::Drawing::Size(216, 20);
			this->quoteNameTextBox->TabIndex = 0;
			// 
			// customerNameTextBox
			// 
			this->customerNameTextBox->Location = System::Drawing::Point(64, 41);
			this->customerNameTextBox->Name = L"customerNameTextBox";
			this->customerNameTextBox->Size = System::Drawing::Size(216, 20);
			this->customerNameTextBox->TabIndex = 0;
			// 
			// quoteNameLbl
			// 
			this->quoteNameLbl->AutoSize = true;
			this->quoteNameLbl->Location = System::Drawing::Point(12, 18);
			this->quoteNameLbl->Name = L"quoteNameLbl";
			this->quoteNameLbl->Size = System::Drawing::Size(35, 13);
			this->quoteNameLbl->TabIndex = 1;
			this->quoteNameLbl->Text = L"Name";
			// 
			// customerNameLbl
			// 
			this->customerNameLbl->AutoSize = true;
			this->customerNameLbl->Location = System::Drawing::Point(12, 44);
			this->customerNameLbl->Name = L"customerNameLbl";
			this->customerNameLbl->Size = System::Drawing::Size(51, 13);
			this->customerNameLbl->TabIndex = 1;
			this->customerNameLbl->Text = L"Customer";
			// 
			// materialComboBox
			// 
			this->materialComboBox->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->materialComboBox->FormattingEnabled = true;
			this->materialComboBox->Location = System::Drawing::Point(64, 67);
			this->materialComboBox->Name = L"materialComboBox";
			this->materialComboBox->Size = System::Drawing::Size(119, 21);
			this->materialComboBox->TabIndex = 2;
			// 
			// sizeComboBox
			// 
			this->sizeComboBox->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->sizeComboBox->FormattingEnabled = true;
			this->sizeComboBox->Location = System::Drawing::Point(222, 67);
			this->sizeComboBox->Name = L"sizeComboBox";
			this->sizeComboBox->Size = System::Drawing::Size(58, 21);
			this->sizeComboBox->TabIndex = 2;
			// 
			// materialLbl
			// 
			this->materialLbl->AutoSize = true;
			this->materialLbl->Location = System::Drawing::Point(13, 71);
			this->materialLbl->Name = L"materialLbl";
			this->materialLbl->Size = System::Drawing::Size(44, 13);
			this->materialLbl->TabIndex = 1;
			this->materialLbl->Text = L"Material";
			// 
			// sizeLbl
			// 
			this->sizeLbl->AutoSize = true;
			this->sizeLbl->Location = System::Drawing::Point(189, 71);
			this->sizeLbl->Name = L"sizeLbl";
			this->sizeLbl->Size = System::Drawing::Size(27, 13);
			this->sizeLbl->TabIndex = 1;
			this->sizeLbl->Text = L"Size";
			// 
			// priceTextBox
			// 
			this->priceTextBox->Location = System::Drawing::Point(64, 94);
			this->priceTextBox->Name = L"priceTextBox";
			this->priceTextBox->ReadOnly = true;
			this->priceTextBox->Size = System::Drawing::Size(216, 20);
			this->priceTextBox->TabIndex = 3;
			this->priceTextBox->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			// 
			// priceLbl
			// 
			this->priceLbl->AutoSize = true;
			this->priceLbl->Location = System::Drawing::Point(13, 97);
			this->priceLbl->Name = L"priceLbl";
			this->priceLbl->Size = System::Drawing::Size(31, 13);
			this->priceLbl->TabIndex = 1;
			this->priceLbl->Text = L"Price";
			// 
			// cancelBtn
			// 
			this->cancelBtn->Location = System::Drawing::Point(205, 135);
			this->cancelBtn->Name = L"cancelBtn";
			this->cancelBtn->Size = System::Drawing::Size(75, 23);
			this->cancelBtn->TabIndex = 4;
			this->cancelBtn->Text = L"Cancel";
			this->cancelBtn->UseVisualStyleBackColor = true;
			this->cancelBtn->Click += gcnew System::EventHandler(this, &CreateQuoteForm::cancelBtn_Click);
			// 
			// createBtn
			// 
			this->createBtn->Location = System::Drawing::Point(124, 135);
			this->createBtn->Name = L"createBtn";
			this->createBtn->Size = System::Drawing::Size(75, 23);
			this->createBtn->TabIndex = 4;
			this->createBtn->TabStop = false;
			this->createBtn->Text = L"Create";
			this->createBtn->UseVisualStyleBackColor = true;
			this->createBtn->Click += gcnew System::EventHandler(this, &CreateQuoteForm::createBtn_Click);
			// 
			// CreateQuoteForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(293, 170);
			this->Controls->Add(this->cancelBtn);
			this->Controls->Add(this->createBtn);
			this->Controls->Add(this->priceTextBox);
			this->Controls->Add(this->sizeComboBox);
			this->Controls->Add(this->materialComboBox);
			this->Controls->Add(this->sizeLbl);
			this->Controls->Add(this->priceLbl);
			this->Controls->Add(this->materialLbl);
			this->Controls->Add(this->customerNameLbl);
			this->Controls->Add(this->quoteNameLbl);
			this->Controls->Add(this->customerNameTextBox);
			this->Controls->Add(this->quoteNameTextBox);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
			this->MaximizeBox = false;
			this->Name = L"CreateQuoteForm";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private:
		/// <summary>
		/// Event handler for when the selected index of a combo box changes
		/// Is used to calculate the price when the material or size changes
		/// </summary>
		Void comboBoxes_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e);

		Void createBtn_Click(System::Object^ sender, System::EventArgs^ e);
		Void cancelBtn_Click(System::Object^ sender, System::EventArgs^ e);
	};
}
