#include "LevelGenerator.h"
#include "ResourceManager.h"
#include <fstream>
#include <sstream>

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
    void LevelGenerator::LoadLevel(const std::string& pathName)
    {
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
                    m_Walls.push_back(block);
                    break;
                case 1:
                    m_Void.push_back(block);
                    break;
                case 2:
                    m_PathWays.push_back(block);
                    break;
                default:
                    break;
                }

                ++column;
            }
            ++row;
            column = 0;
        }
    }

    void LevelGenerator::SetBlockDimension(int dimensions)
    {
        m_TextureDimensions = dimensions;
    }
}


