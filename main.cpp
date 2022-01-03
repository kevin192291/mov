#include <tmxlite/Map.hpp>
#include <tmxlite/ObjectGroup.hpp>
#include <tmxlite/LayerGroup.hpp>
#include <tmxlite/TileLayer.hpp>

#include <iostream>

int main()
{
    tmx::Map map;
    std::map<std::pair<int, int>, tmx::Tileset::Tile> m;

    if (map.load("assets/overworld.tmx"))
    {
        std::cout << "Loaded Map version: " << map.getVersion().upper << ", " << map.getVersion().lower << std::endl;
        if (map.isInfinite())
        {
            std::cout << "Map is infinite.\n";
        }

        const auto &mapProperties = map.getProperties();
        std::cout << "Map has " << mapProperties.size() << " properties" << std::endl;
        for (const auto &prop : mapProperties)
        {
            std::cout << "Found property: " << prop.getName() << std::endl;
            std::cout << "Type: " << int(prop.getType()) << std::endl;
        }

        std::cout << std::endl;

        const auto &layers = map.getLayers();
        std::cout << "Map has " << layers.size() << " layers" << std::endl;
        for (const auto &layer : layers)
        {
            std::cout << "Found Layer: " << layer->getName() << std::endl;
            std::cout << "Layer Type: " << int(layer->getType()) << std::endl;

            if (layer->getType() == tmx::Layer::Type::Group)
            {
                std::cout << "Checking sublayers" << std::endl;
                const auto &sublayers = layer->getLayerAs<tmx::LayerGroup>().getLayers();
                std::cout << "LayerGroup has " << sublayers.size() << " layers" << std::endl;
                for (const auto &sublayer : sublayers)
                {
                    std::cout << "Found Layer: " << sublayer->getName() << std::endl;
                    std::cout << "Layer Type: " << int(sublayer->getType()) << std::endl;

                    if (sublayer->getType() == tmx::Layer::Type::Object)
                    {
                        std::cout << sublayer->getName() << " has " << sublayer->getLayerAs<tmx::ObjectGroup>().getObjects().size() << " objects" << std::endl;
                    }
                    else if (sublayer->getType() == tmx::Layer::Type::Tile)
                    {
                        std::cout << sublayer->getName() << " has " << sublayer->getLayerAs<tmx::TileLayer>().getTiles().size() << " tiles" << std::endl;
                    }
                }
            }

            if (layer->getType() == tmx::Layer::Type::Object)
            {
                const auto &objects = layer->getLayerAs<tmx::ObjectGroup>().getObjects();
                std::cout << "Found " << objects.size() << " objects in layer" << std::endl;
                for (const auto &object : objects)
                {
                    std::cout << "Object " << object.getUID() << ", " << object.getName() << std::endl;
                    const auto &properties = object.getProperties();
                    std::cout << "Object has " << properties.size() << " properties" << std::endl;
                    for (const auto &prop : properties)
                    {
                        std::cout << "Found property: " << prop.getName() << std::endl;
                        std::cout << "Type: " << int(prop.getType()) << std::endl;
                    }

                    if (!object.getTilesetName().empty())
                    {
                        std::cout << "Object uses template tile set " << object.getTilesetName() << "\n";
                        tmx::FloatRect rect = object.getAABB();
                    }
                }
            }

            if (layer->getType() == tmx::Layer::Type::Tile)
            {
                const auto &tiles = layer->getLayerAs<tmx::TileLayer>().getTiles();
                if (tiles.empty())
                {
                    const auto &chunks = layer->getLayerAs<tmx::TileLayer>().getChunks();
                    if (chunks.empty())
                    {
                        std::cout << "Layer has missing tile data\n";
                    }
                    else
                    {
                        std::cout << "Layer has " << chunks.size() << " tile chunks.\n";
                    }
                }
                else
                {
                    std::cout << "Layer has " << tiles.size() << " tiles.\n";
                    for (auto &set : map.getTilesets())
                    {
                        int x_cnt = 0;
                        int y_cnt = 0;
                        for (auto &tile : set.getTiles())
                        {
                            
                            x_cnt++;
                            if (x_cnt%layer->getSize().x == 0)
                            {
                                y_cnt++;
                                x_cnt = 0;
                            }
                            m[std::make_pair(x_cnt,y_cnt)] = tile;
                            for (auto &object : tile.objectGroup.getObjects())
                            {
                                for(auto& point : object.getPoints())
                                {
                                    std::cout << "X: " << x_cnt << ", Y: " << y_cnt << std::endl;
                                }
                            }
                        }
                    }
                }
            }

            const auto &properties = layer->getProperties();
            std::cout << properties.size() << " Layer Properties:" << std::endl;
            for (const auto &prop : properties)
            {
                std::cout << "Found property: " << prop.getName() << std::endl;
                std::cout << "Type: " << int(prop.getType()) << std::endl;
            }
        }
    }
    else
    {
        std::cout << "Failed loading map" << std::endl;
    }
            // std::cout << "X: " << m.at(std::make_pair(10,10))) << std::endl;

#if defined(PAUSE_AT_END)
    std::cout << std::endl
              << "Press return to quit..." << std::endl;
    std::cin.get();
#endif

    return 0;
}