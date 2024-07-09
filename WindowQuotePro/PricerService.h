#pragma once

namespace Pricer {
	using namespace System;

	ref class PricerService
	{
	private:
		static PricerService^ instance = nullptr;
		static Object^ lockObject = gcnew Object();

	protected:
		PricerService();

	public:
		double CalculatePrice(String^ material, String^ size);

		static property PricerService^ Instance
		{
			PricerService^ get();
		}
	};
}
