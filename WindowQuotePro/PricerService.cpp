#include "PricerService.h"

#include <msclr/lock.h>
#include <ctime>

namespace Pricer {
	PricerService::PricerService()
	{
	}

	double PricerService::CalculatePrice(String^ material, String^ size)
	{
		return static_cast<int>((gcnew Random(time(nullptr)))->NextDouble() * 100);
	}

	PricerService^ PricerService::Instance::get()
	{
		if (instance == nullptr)
		{
			msclr::lock lock(lockObject);
			if (instance == nullptr)
			{
				instance = gcnew PricerService();
			}
		}
		return instance;
	}
}
