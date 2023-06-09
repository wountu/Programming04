#pragma once
#pragma once
#include <string>
#include <vector>
#include <glm/vec2.hpp>
#include "Singleton.h"

namespace dae
{
	struct Block
	{
		glm::vec2 LeftTop;
		int Width;
		int Height;
	};

	class LevelGenerator final : public Singleton<LevelGenerator>
	{
	public:
		LevelGenerator() = default;
		~LevelGenerator() = default;

		LevelGenerator(const LevelGenerator& other) = delete;
		LevelGenerator& operator=(const LevelGenerator& other) = delete;
		LevelGenerator(LevelGenerator&& other) = delete;
		LevelGenerator& operator =(LevelGenerator&& other) = delete;

		std::vector<Block> GetPathWay() const;
		std::vector<Block> GetVoid() const;
		std::vector<Block> GetWalls() const;

		void LoadLevel(const std::string& filePath);
		void SetBlockDimension(int dimensions); //Needs to be a square
	private:
		std::vector<Block> m_PathWays{};
		std::vector<Block> m_Void{};
		std::vector<Block> m_Walls{};

		int m_TextureDimensions{ 8 }; //Standard 8, but can be changed
	};
}

