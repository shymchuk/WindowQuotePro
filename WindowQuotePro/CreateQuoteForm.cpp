#include "CreateQuoteForm.h"

#include "Definitions.h"
#include "PricerService.h"

namespace WindowQuotePro {

	CreateQuoteForm::CreateQuoteForm(String^ title, Mode mode)
	{
		InitializeComponent();

		this->ActiveControl = quoteNameTextBox;

		this->Text = title;
		
		// Add variants to the material combo box
		for each (KeyValuePair<Materials, String^> material in Definitions::Instance->MaterialNames)
		{
			materialComboBox->Items->Add(material.Value);
		}
		materialComboBox->SelectedIndex = 0;

		// Add variants to the size combo box
		for each (KeyValuePair<Sizes, String^> size in Definitions::Instance->SizeNames)
		{
			sizeComboBox->Items->Add(size.Value);
		}
		sizeComboBox->SelectedIndex = 0;

		// Subscribe to the SelectedIndexChanged event of the combo boxes after initialization
		auto indexeChangedHandler = gcnew System::EventHandler(this, &CreateQuoteForm::comboBoxes_SelectedIndexChanged);
		this->materialComboBox->SelectedIndexChanged += indexeChangedHandler;
		this->sizeComboBox->SelectedIndexChanged += indexeChangedHandler;

		createBtn->Text = mode == Mode::Create ? "Create" : "Update";
	}

	CreateQuoteForm::CreateQuoteForm(String^ title, Mode mode, String^ quoteName, String^ customerName, Int32 material, Int32 size, double price)
		: CreateQuoteForm(title, mode)
	{
		quoteNameTextBox->Text = quoteName;
		customerNameTextBox->Text = customerName;
		materialComboBox->SelectedIndex = material;
		sizeComboBox->SelectedIndex = size;
		priceTextBox->Text = Definitions::Instance->PriceToString(price);
	}

	void CreateQuoteForm::OnHandleCreated(EventArgs^ e)
	{
		Form::OnHandleCreated(e);
		CalculateAndSetPrice();
	}

	CreateQuoteForm::~CreateQuoteForm()
	{
		if (components)
		{
			delete components;
		}
	}

	double CreateQuoteForm::Price::get()
	{
		return Definitions::Instance->ParsePrice(priceTextBox->Text);
	}

	CreateQuoteForm::CalculatePriceWrapper::CalculatePriceWrapper(String^ material, String^ size)
		: material(material), size(size)
	{
	}

	double CreateQuoteForm::CalculatePriceWrapper::CalculatePrice()
	{
		return Pricer::PricerService::Instance->CalculatePrice(material, size);
	}

	void CreateQuoteForm::CalculateAndSetPrice()
	{
		using namespace System::Threading::Tasks;

		priceTextBox->Text = "Calculating...";
		createBtn->Enabled = false;

		auto size = sizeComboBox->SelectedItem->ToString();
		auto material = materialComboBox->SelectedItem->ToString();

		Pricer::PricerService^ pricer = Pricer::PricerService::Instance;

		auto calculateWrapper = gcnew CalculatePriceWrapper(material, size);
		Func<double>^ calculatePrice = gcnew Func<double>(calculateWrapper, &CalculatePriceWrapper::CalculatePrice);

		auto task = Task<double>::Factory->StartNew(calculatePrice);

		task->ContinueWith(gcnew Action<Task<double>^>(this, &CreateQuoteForm::PriceTaskCompleted));
	}

	void CreateQuoteForm::PriceTaskCompleted(Task<double>^ t)
	{
		String^ price = nullptr;

		if (t->Exception != nullptr) {
			price = "Error while retrieving price";
		}
		else {
			// Show price in currency format
			price = Definitions::Instance->PriceToString(t->Result);
		}

		if (this->InvokeRequired) {
			this->Invoke(gcnew Action<String^>(this, &CreateQuoteForm::UpdatePrice), price);
		}
		else {
			UpdatePrice(price);
		}
	}

	void CreateQuoteForm::UpdatePrice(String^ text)
	{
		priceTextBox->Text = text;
		createBtn->Enabled = true;
	}

	Void CreateQuoteForm::comboBoxes_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e)
	{
		CalculateAndSetPrice();
	}

	Void CreateQuoteForm::createBtn_Click(System::Object^ sender, System::EventArgs^ e)
	{
		accepted = true;
		this->Close();
	}

	Void CreateQuoteForm::cancelBtn_Click(System::Object^ sender, System::EventArgs^ e)
	{
		accepted = false;
		this->Close();
	}
}
