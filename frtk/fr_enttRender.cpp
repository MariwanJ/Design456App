#include<fr_enttScene.h>
#include<fr_primativeShader.h>
#include<fr_item.h>

namespace FR {
    void Fr_enttScene::Render(FR::Node::RenderInfo& info, const glm::mat4& modelview) {
    }

    void Fr_enttScene::RenderPrimativeShapes(FR::Node::RenderInfo& info, const glm::mat4& modelview)
    {
        auto PrimativeShaderView = m_Registry.view<Fr_PrimaitiveShader>();
        //We should have ONLY one grid object. 
        for (auto view: PrimativeShaderView) {
            Fr_Item primative = { view,this };
            auto grd = primative.GetItem<ItemName>();
            if (grd.m_Name.compare("Grid") != std::string::npos){
                auto pShad= primative.GetItem<Fr_PrimaitiveShader>();
                pShad.Render(info, modelview);
                break;//out from the for loop
            }
            if ((grd.m_Name.compare("Axis3D_Red") != std::string::npos)   ||            
                (grd.m_Name.compare("Axis3D_Green") != std::string::npos) ||
                (grd.m_Name.compare("Axis3D_Blue") != std::string::npos)  ||
                (grd.m_Name.compare("Axis3D_ZBlue") != std::string::npos) )
            {
                auto pShad = primative.GetItem<Fr_PrimaitiveShader>();
                pShad.Render(info, modelview);
            }
        }
    }

    void Fr_enttScene::RenderWidgetToolkit(FR::Node::RenderInfo& info, const glm::mat4& modelview)
    {
    }

    void Fr_enttScene::RenderSilhouette(const glm::mat4& mvp) {
    }
    void Fr_enttScene::RenderIMGui(FR::Node::RenderInfo& info, const glm::mat4& modelview)
    {
    }
}