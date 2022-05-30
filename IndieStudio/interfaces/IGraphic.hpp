/*
** EPITECH PROJECT, 2021
** IGraphic
** File description:
** IGraphic
*/

#ifndef B_YEP_400_NCE_4_1_INDIESTUDIO_ANTHONY_GOTI_IGRAPHIC_HPP
#define B_YEP_400_NCE_4_1_INDIESTUDIO_ANTHONY_GOTI_IGRAPHIC_HPP

#include "Info.hpp"
#include "IEntities.hpp"

class IGraphic {
public:
    virtual Info *getInfo() = 0;

    virtual void drawEntities(std::vector<IEntities *> i_entities) = 0;
    virtual std::map<std::string, std::vector<Model> *> *getModels() = 0; // only viable for raylib
    virtual void toggleFullscreen() = 0;

    virtual ~IGraphic() = default;;
};

#endif //B_YEP_400_NCE_4_1_INDIESTUDIO_ANTHONY_GOTI_IGRAPHIC_HPP
