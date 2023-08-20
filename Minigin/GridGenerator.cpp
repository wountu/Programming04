#include "GridGenerator.h"
#include "ResourceManager.h"
#include "TransformComponent.h"
#include "RenderComponent.h"
#include "CollisionBoxComponent.h"

#include <fstream>
#include <sstream>
#include <iostream>

namespace dae
{
    GridGenerator::Grid GridGenerator::CreateGrid(const std::string& levelPathName, glm::vec2 tileDimensions, std::string levelName)
    {
        std::vector<Tile> grid{};
        std::vector<int> intGrid{};
        const std::string fullPath{ ResourceManager::GetInstance().GetDataPath() + levelPathName };

        std::ifstream file(fullPath);
        assert(file.is_open() && "Failed to open the file given in the loadlevel!");

        std::string line{};
        while (std::getline(file, line))
        {
            std::stringstream ss{ line };
            std::string text{};
            while (std::getline(ss, text, ':'))
            {
                if (text == "width")
                {
                    std::string number{};
                    std::getline(ss, number, ',');

                    m_GridWidth = std::stoi(number);
                }
                if (text == "height")
                {
                    std::string number{};
                    std::getline(ss, number, ',');

                    m_GridHeight = std::stoi(number);
                }
                if (text == "grid")
                {
                    std::string gridLine{};
                    while (std::getline(file, gridLine))
                    {
                        std::stringstream ssGridLine{ gridLine };

                        std::string number{};
                        while (std::getline(ssGridLine, number, ','))
                        {
                            for (size_t idx{ 0 }; idx < number.size(); ++idx)
                            {
                                if (number[idx] != '[' && number[idx] != ']' && number[idx] != ' ' && number[idx] != '\t')
                                {
                                    Tile tile{};
                                    tile.Width = static_cast<int>(tileDimensions.x);
                                    tile.Height = static_cast<int>(tileDimensions.y);
                                    tile.LeftTop.x = ((m_Grid[levelName].size()) % m_GridWidth) * tileDimensions.x;
                                    tile.LeftTop.y = static_cast<float>((m_Grid[levelName].size() / (m_GridWidth)) * tileDimensions.y);

                                    int parsedNmbr{ static_cast<int>(number[idx] - '0') };
                                    
                                    switch (parsedNmbr)
                                    {
                                    case 1: 
                                        tile.tileType = TileType::WALL;
                                        tile.walkable = false;
                                        break;


                                    case 2:
                                        tile.tileType = TileType::PATH;
                                        tile.hasDot = true;
                                        break;

                                    case 3:
                                        tile.tileType = TileType::PATH;
                                        tile.hasBigDot = true;
                                        break;

                                    case 4:
                                        tile.tileType = TileType::PATH;
                                        break;

                                    case 5:
                                        tile.tileType = TileType::PATH;
                                        break;

                                    case 6:
                                        tile.tileType = TileType::PATH;
                                        tile.isSpawnPointEnemy = true;
                                        break;

                                    case 7:
                                        tile.tileType = TileType::PATH;
                                        tile.isSpawnPointPlayer = true;
                                        break;

                                    case 8:
                                        tile.tileType = TileType::PATH;
                                        tile.isTeleporter = true;
                                        break;
                                    }
                                  
                                    m_Grid[levelName].push_back(tile);
                                    break;
                                }
                            }
                        }
                    }
                }
            }
        }

        return m_Grid;
    }

    void GridGenerator::SetTileDimensions(glm::vec2 tileDimensions)
    {
        m_TileDimensions = tileDimensions;
    }

    void GridGenerator::LinkTextureToTile(TileType tileType, std::shared_ptr<Texture2D> pTexture)
    {
        m_TextureMaps.emplace(tileType, pTexture);
    }

    std::vector<std::shared_ptr<GameObject>> GridGenerator::CreateGameObjects(std::string levelName)
    {
        std::vector<std::shared_ptr<GameObject>> gridGO{};

        assert(!m_Grid.empty() && "First the grid needs to be created before turning in it into GO's");

        for (const auto& tile : m_Grid[levelName])
        {
            auto tileGO = std::make_shared<GameObject>();
            tileGO->Initialize();
            tileGO->SetTag(Static);

            auto transform = tileGO->AddComponent<TransformComponent>();
            transform->Initialize(tile.LeftTop, 0.f, tileGO);

            auto texture = m_TextureMaps.at(tile.tileType);
            auto render = tileGO->AddComponent<RenderComponent>();
            render->Initialize(texture, tileGO);

            if (tile.tileType == TileType::WALL)
            {
                auto collision = tileGO->AddComponent<CollisionBoxComponent>();
                auto collBox = CollisionBox(tile.LeftTop, static_cast<float>(tile.Width), static_cast<float>(tile.Height));
                collision->Initialize(tileGO, collBox, 0);
                collision->SetActive(true);
            }

            gridGO.push_back(tileGO);
        }

        return gridGO;
    }

    GridGenerator::Grid GridGenerator::GetGrid() const
    {
        return m_Grid;
    }

    int GridGenerator::GetIdxFromPos(glm::vec2 pos)
    {
        int x = static_cast<int>(pos.x / m_TileDimensions.x);
        int y = static_cast<int>(pos.y / m_TileDimensions.y);

        return x + (y * m_GridWidth);
    }

    int GridGenerator::GetGridWidth() const
    {
        return m_GridWidth;
    }

    int GridGenerator::GetGridHeight() const
    {
        return m_GridHeight;
    }
}


