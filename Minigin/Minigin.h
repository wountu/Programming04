#pragma once
#include <string>
#include <functional>
#include <memory>

#include "TimeClass.h"

namespace dae
{
	class Minigin
	{
	public:
		explicit Minigin(const std::string& dataPath);
		~Minigin();
		void Run(const std::function<void()>& load);

		Minigin(const Minigin& other) = delete;
		Minigin(Minigin&& other) = delete;
		Minigin& operator=(const Minigin& other) = delete;
		Minigin& operator=(Minigin&& other) = delete;
	private:
		std::shared_ptr<TimeClass> m_pTimeClass = std::make_shared<TimeClass>();
	};
}