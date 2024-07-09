#include "MainWindowForm.h"
#include "CreateQuoteForm.h"
#include "DBService.h"
#include "Definitions.h"


namespace WindowQuotePro {

	MainWindowForm::MainWindowForm(void)
	{
		InitializeComponent();
		
		quotesGridView->DataSource = DBService::Instance->LoadData();
		quotesGridView->Columns[0]->Visible = false; // ID

		quotesGridView->Columns[4]->Visible = false; // Material ID
		quotesGridView->Columns[6]->Visible = false; // Size ID

		quotesGridView->Columns[3]->ReadOnly = true; // Material
		quotesGridView->Columns[5]->ReadOnly = true; // Size
		quotesGridView->Columns[7]->ReadOnly = true; // Price
	}

	MainWindowForm::~MainWindowForm()
	{
		if (components)
		{
			delete components;
		}
	}

	Void MainWindowForm::newQuoteBtn_Click(Object^ sender, EventArgs^ e)
	{
		CreateQuoteForm^ form = gcnew CreateQuoteForm("Create new quote", CreateQuoteForm::Mode::Create);
		form->FormClosed += gcnew FormClosedEventHandler(this, &MainWindowForm::addQuoteWindow_FormClosed);
		form->Show();
	}

	Void MainWindowForm::addQuoteWindow_FormClosed(Object^ sender, FormClosedEventArgs^ e)
	{
		CreateQuoteForm^ form = dynamic_cast<CreateQuoteForm^>(sender);
		if (form == nullptr)
		{
			return;
		}
		if (form->Accepted)
		{
			int id = DBService::Instance->AddRecord(
				form->QuoteName, form->CustomerName, form->Material,
				form->Size, form->Price
			);
			DataTable^ data = dynamic_cast<DataTable^>(quotesGridView->DataSource);
			data->Rows->Add(id,
				form->QuoteName,
				form->CustomerName,
				Definitions::Instance->MaterialToString(static_cast<Materials>(form->Material)),
				form->Material, 
				Definitions::Instance->SizeToString(static_cast<Sizes>(form->Size)),
				form->Size,
				form->Price);
		}
	}

	MainWindowForm::UpdateRowHandler::UpdateRowHandler(DataGridView^ view, DataGridViewRow^ row)
		: view(view), row(row)
	{}

	Void MainWindowForm::UpdateRowHandler::updateQuoteWindow_FormClosed(System::Object^ sender, System::Windows::Forms::FormClosedEventArgs^ e)
	{
		CreateQuoteForm^ form = dynamic_cast<CreateQuoteForm^>(sender);
		if (form == nullptr)
		{
			return;
		}
		if (form->Accepted)
		{
			row->Cells[1]->Value = form->QuoteName;
			row->Cells[2]->Value = form->CustomerName;
			row->Cells[3]->Value = Definitions::Instance->MaterialToString(static_cast<Materials>(form->Material));
			row->Cells[4]->Value = form->Material;
			row->Cells[5]->Value = Definitions::Instance->SizeToString(static_cast<Sizes>(form->Size));
			row->Cells[6]->Value = form->Size;
			row->Cells[7]->Value = form->Price;

			// These calls are required for data not to be reverted in Escape key press
			dynamic_cast<DataTable^>(view->DataSource)->AcceptChanges();
			view->EndEdit();
	
			auto id = Convert::ToInt32(row->Cells[0]->Value);

			DBService::Instance->UpdateRecord(id, form->QuoteName, form->CustomerName, form->Material, form->Size, form->Price);
		}
	}

	Void MainWindowForm::updateQuoteBtn_Click(System::Object^ sender, System::EventArgs^ e)
	{
		for each (DataGridViewRow ^ row in quotesGridView->SelectedRows)
		{
			CreateQuoteForm^ form = gcnew CreateQuoteForm("Update quote",
				CreateQuoteForm::Mode::Update,
				row->Cells[1]->Value->ToString(), // Name
				row->Cells[2]->Value->ToString(), // Customer
				Convert::ToInt32(row->Cells[4]->Value), // Material ID
				Convert::ToInt32(row->Cells[6]->Value), // Size ID
				Convert::ToDouble(row->Cells[7]->Value) // Price
			);
			UpdateRowHandler^ handler = gcnew UpdateRowHandler(quotesGridView, row);
			form->FormClosed += gcnew FormClosedEventHandler(handler, &UpdateRowHandler::updateQuoteWindow_FormClosed);
			form->Show();
		}
	}

	Void MainWindowForm::quotesGridView_DataError(System::Object^ sender, System::Windows::Forms::DataGridViewDataErrorEventArgs^ e)
	{
		// If the data source is a DataTable, handle the exception.
		auto dataTable = dynamic_cast<System::Data::DataTable^>(quotesGridView->DataSource);
		if (dataTable != nullptr) {
		
			// Display an error message.
			MessageBox::Show(e->Exception->Message);
		}
	}

	Void MainWindowForm::quotesGridView_CellValueChanged(System::Object^ sender, System::Windows::Forms::DataGridViewCellEventArgs^ e)
	{
		auto row = quotesGridView->Rows[e->RowIndex];
		auto id = row->Cells[0]->Value;
		auto name = row->Cells[1]->Value;
		auto customer = row->Cells[2]->Value;
		auto materialId = row->Cells[4]->Value;
		auto sizeId = row->Cells[6]->Value;
		auto price = row->Cells[7]->Value;

		DBService::Instance->UpdateRecord(Convert::ToInt32(id), name->ToString(), customer->ToString(), Convert::ToInt32(materialId), Convert::ToInt32(sizeId), Convert::ToDouble(price));
	}

	Void MainWindowForm::deleteQuoteBtn_Click(System::Object^ sender, System::EventArgs^ e)
	{
		for each (DataGridViewRow ^ row in quotesGridView->SelectedRows)
		{
			auto id = Convert::ToInt32(row->Cells[0]->Value);
			DBService::Instance->DeleteRecord(id);
			quotesGridView->Rows->Remove(row);
		}
	}

	Void MainWindowForm::quotesGridView_SelectionChanged(System::Object^ sender, System::EventArgs^ e) {
		if (quotesGridView->SelectedRows->Count > 0) {
			deleteQuoteBtn->Enabled = true;
			updateQuoteBtn->Enabled = true;
		}
		else {
			deleteQuoteBtn->Enabled = false;
			updateQuoteBtn->Enabled = false;
		}
	}
}
