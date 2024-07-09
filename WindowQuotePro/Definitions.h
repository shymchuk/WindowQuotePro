#pragma once


public enum class Materials
{
	Wood,
	Metal
};

namespace WindowQuotePro
{
	using namespace System::Collections::Generic;
	using namespace System;
	using namespace System::Globalization;

	public enum class Materials
	{
		Wood,
		Metal
	};

	public enum class Sizes
	{
		Small,
		Medium,
		Large
	};
	
	/// <summary>
	/// Singleton class that provides definitions for constants used in the application
	/// </summary>
	public ref class Definitions
	{
	private:
		static Definitions^ instance = nullptr;
		static Object^ lockObject = gcnew Object();

		Dictionary<Materials, String^>^ materialNames;
		Dictionary<Sizes, String^>^ sizeNames;
		CultureInfo^ culture;

		Definitions();
	public:

		String^ SizeToString(Sizes size);
		String^ MaterialToString(Materials material);

		Materials MaterialFromString(String^ material);
		Sizes SizeFromString(String^ size);

		double ParsePrice(String^ price);
		String^ PriceToString(double price);

		property Dictionary<Materials, String^>^ MaterialNames
		{
			Dictionary<Materials, String^>^ get();
		}

		property Dictionary<Sizes, String^>^ SizeNames
		{
			Dictionary<Sizes, String^>^ get();
		}

		property CultureInfo^ Culture
		{
			CultureInfo^ get();
		}

		static property Definitions^ Instance
		{
			Definitions^ get();
		}
	};
}
