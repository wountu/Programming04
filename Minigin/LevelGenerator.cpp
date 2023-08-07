#include "LevelGenerator.h"
#include "ResourceManager.h"
#include <fstream>
#include <sstream>
#include <iostream>

namespace dae
{
    std::vector<Block> LevelGenerator::GetPathWay() const
    {
        return m_PathWays;
    }

    std::vector<Block> LevelGenerator::GetVoid() const
    {
        return m_Void;
    }

    std::vector<Block> LevelGenerator::GetWalls() const
    {
        return m_Walls;
    }

    std::unique_ptr<LevelData> LevelGenerator::LoadLevel(const std::string& pathName)
    {
        std::unique_ptr<LevelData> pLevelData = std::make_unique<LevelData>();
        m_PathWays.clear();
        m_Void.clear();
        m_Walls.clear();

        const std::string fullPath{ ResourceManager::GetInstance().GetDataPath() + pathName };

        std::ifstream file(fullPath);
        assert(file.is_open() && "Failed to open the file given in the loadlevel!");

        int row{ 0 };
        int column{ 0 };
        std::string line{};
        while (std::getline(file, line)) //Get line
        {
            std::stringstream ss(line);
            std::string number{};
            while (std::getline(ss, number, ',')) //Get number
            {
                int blockType = std::stoi(number);
                
                if (blockType > 2)
                {
                    blockType = 2; //No teleporters
                }

                Block block; //Make block
                block.LeftTop.x = static_cast<float>(column * m_TextureDimensions);
                block.LeftTop.y = static_cast<float>(row * m_TextureDimensions);
                block.Width = m_TextureDimensions;
                block.Height = m_TextureDimensions;



                switch (blockType) //Get right block
                {
                case 0:
                    pLevelData->walls.push_back(block);
                    m_Walls.push_back(block);
                    break;
                case 1:
                    m_Void.push_back(block);
                    pLevelData->Void.push_back(block);
                    break;
                case 2:
                    m_PathWays.push_back(block);
                    pLevelData->pathWays.push_back(block);
                    break;
                default:
                    break;
                }

                ++column;
            }
            ++row;
            column = 0;
        }

        return pLevelData;
    }

    void LevelGenerator::SetBlockDimension(int dimensions)
    {
        m_TextureDimensions = dimensions;
    }

    std::vector<Tile> GridGenerator::CreateGrid(const std::string& levelPathName, glm::vec2 tileDimensions)
    {
        std::vector<Tile> grid{};
        std::vector<int> intGrid{};
        const std::string fullPath{ ResourceManager::GetInstance().GetDataPath() + levelPathName };

        std::ifstream file(fullPath);
        assert(file.is_open() && "Failed to open the file given in the loadlevel!");

        int width{};
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

                    width = std::stoi(number);
                    std::cout << "Found width: " << number << "\n";
                }
                if (text == "height")
                {
                    std::string number{};
                    std::getline(ss, number, ',');

                    std::cout << "Found height: " << number <<  "\n";
                }
                if (text == "grid")
                {
                    std::string gridLine{};
                    while (std::getline(file, gridLine))
                    {
                        std::stringstream ssGridLine{ gridLine };

                        //ssGridLine.get(catchSs);

                        std::string number{};
                        while (std::getline(ssGridLine, number, ','))
                        {
                            for (int idx{ 0 }; idx < number.size(); ++idx)
                            {
                                if (number[idx] != '[' && number[idx] != ']' && number[idx] != ' ' && number[idx] != '\t')
                                {
                                    Tile tile{};
                                    tile.Width = static_cast<int>(tileDimensions.x);
                                    tile.Height = static_cast<int>(tileDimensions.y);
                                    tile.LeftTop.x = ((grid.size()) % width) * tileDimensions.x;
                                    tile.LeftTop.y = static_cast<float>((grid.size() / (width)) * tileDimensions.y);

                                    int parsedNmbr{ static_cast<int>(number[idx] - '0') };
                                    
                                    switch (parsedNmbr)
                                    {
                                    case 1: 
                                        tile.walkable = false;
                                        break;
                                    case 2:
                                        tile.walkable = true;
                                        break;
                                    default:
                                        tile.walkable = true;
                                        break;
                                    }
                                  
                                    grid.push_back(tile);
                                    //std::cout << number[idx] << "\n";
                                    //intGrid.push_back(parsedNmbr);
                                    break;
                                }
                            }
                        }
                    }
                }
            }
        }

        return grid;
    }

    void GridGenerator::SetTileDimensions(glm::vec2 tileDimensions)
    {
        m_TileDimensions = tileDimensions;
    }
}


