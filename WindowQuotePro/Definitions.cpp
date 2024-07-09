#include "Definitions.h"

#include <msclr/lock.h>


namespace WindowQuotePro
{
	Definitions::Definitions()
		: materialNames(gcnew Dictionary<Materials, String^>()),
		  sizeNames(gcnew Dictionary<Sizes, String^>()),
		  culture(gcnew CultureInfo("en-US"))
	{
		materialNames->Add(Materials::Wood, "Wood");
		materialNames->Add(Materials::Metal, "Metal");

		sizeNames->Add(Sizes::Small, "S");
		sizeNames->Add(Sizes::Medium, "M");
		sizeNames->Add(Sizes::Large, "L");
	}

	String^ Definitions::SizeToString(Sizes size)
	{
		return sizeNames[size];
	}

	String^ Definitions::MaterialToString(Materials material)
	{
		return materialNames[material];
	}

	Materials Definitions::MaterialFromString(String^ material)
	{
		for each (KeyValuePair<Materials, String^> pair in materialNames)
		{
			if (pair.Value == material)
			{
				return pair.Key;
			}
		}
		throw gcnew ArgumentException("Invalid material");
	}

	Sizes Definitions::SizeFromString(String^ size)
	{
		for each (KeyValuePair<Sizes, String^> pair in sizeNames)
		{
			if (pair.Value == size)
			{
				return pair.Key;
			}
		}
		throw gcnew ArgumentException("Invalid size");
	}

	double Definitions::ParsePrice(String^ price)
	{
		return Double::Parse(price, NumberStyles::Currency, culture);
	}

	String^ Definitions::PriceToString(double price)
	{
		return price.ToString("C", culture);
	}

	Dictionary<Materials, String^>^ Definitions::MaterialNames::get()
	{
		return materialNames;
	}

	Dictionary<Sizes, String^>^ Definitions::SizeNames::get()
	{
		return sizeNames;
	}

	CultureInfo^ Definitions::Culture::get()
	{
		return culture;
	}

	Definitions^ Definitions::Instance::get()
	{
		if (instance == nullptr)
		{
			msclr::lock lock(lockObject);
			if (instance == nullptr)
			{
				instance = gcnew Definitions();
			}
		}
		return instance;
	}
}
