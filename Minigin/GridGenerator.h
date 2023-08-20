#pragma once
#pragma once
#include <string>
#include <vector>
#include <glm/vec2.hpp>
#include <memory>
#include <map>

#include "Singleton.h"
#include "Texture2D.h"
#include "GameObject.h"

namespace dae
{
	enum class TileType
	{
		WALL,
		PATH,
	};


	struct Tile
	{
		Tile() = default;

		glm::vec2 LeftTop{};
		int Width{};
		int Height{};
		bool walkable = true;
		bool hasDot{};
		bool hasBigDot{};
		bool isSpawnPointPlayer{};
		bool isSpawnPointEnemy{};
		bool isTeleporter{};
		TileType tileType{};
	};

	struct Block
	{
		glm::vec2 LeftTop;
		int Width;
		int Height;
	};

	class GridGenerator final : public Singleton<GridGenerator>
	{
	public:
		GridGenerator() = default;
		~GridGenerator() = default;

		GridGenerator(const GridGenerator& other) = delete;
		GridGenerator& operator=(const GridGenerator& other) = delete;
		GridGenerator(GridGenerator&& other) = delete;
		GridGenerator& operator=(GridGenerator&& other) = delete;

		using Grid = std::map<std::string, std::vector<Tile>>;

		Grid CreateGrid(const std::string& levelPathName, glm::vec2 tileDimensions, std::string levelName);
		void SetTileDimensions(glm::vec2 tileDimensions);
		void LinkTextureToTile(TileType tileType, std::shared_ptr<Texture2D> pTexture);

		std::vector<std::shared_ptr<GameObject>> CreateGameObjects(std::string levelName);

		Grid GetGrid() const;
		int GetIdxFromPos(glm::vec2 pos);

		int GetGridWidth() const;
		int GetGridHeight() const;

	private:
		int m_GridWidth{}, m_GridHeight{};
		Grid m_Grid{};
		glm::vec2 m_TileDimensions{};
		using textureMap = std::map<TileType, std::shared_ptr<Texture2D>>;
		textureMap m_TextureMaps{};
	};
}
