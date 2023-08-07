#pragma once
#pragma once
#include <string>
#include <vector>
#include <glm/vec2.hpp>
#include <memory>

#include "Singleton.h"

namespace dae
{
	struct Tile
	{
		Tile() = default;
		glm::vec2 LeftTop;
		int Width;
		int Height;
		bool walkable;
	};

	struct Block
	{
		glm::vec2 LeftTop;
		int Width;
		int Height;
	};

	struct LevelData
	{
		std::vector<Block> pathWays;
		std::vector<Block> Void;
		std::vector<Block> walls;
	};

	class GridGenerator final : public Singleton<GridGenerator>
	{
	public:
		GridGenerator() = default;
		//GridGenerator(glm::vec2 tileDimensions);
		~GridGenerator() = default;

		GridGenerator(const GridGenerator& other) = delete;
		GridGenerator& operator=(const GridGenerator& other) = delete;
		GridGenerator(GridGenerator&& other) = delete;
		GridGenerator& operator=(GridGenerator&& other) = delete;

		std::vector<Tile> CreateGrid(const std::string& levelPathName, glm::vec2 tileDimensions);
		void SetTileDimensions(glm::vec2 tileDimensions);

	private:
		glm::vec2 m_TileDimensions{};
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

		std::unique_ptr<LevelData> LoadLevel(const std::string& filePath);
		void SetBlockDimension(int dimensions); //Needs to be a square
	private:
		std::vector<Block> m_PathWays{};
		std::vector<Block> m_Void{};
		std::vector<Block> m_Walls{};

		int m_TextureDimensions{ 8 }; //Standard 8, but can be changed
	};
}

