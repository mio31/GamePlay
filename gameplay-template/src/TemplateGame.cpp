#include "TemplateGame.h"

// Declare our game instance
TemplateGame game;

TemplateGame::TemplateGame()
    : _scene(NULL)
{
}

void TemplateGame::initialize()
{
    // Load game scene from file
    Package* pkg = Package::create("res/box.gpb");
    _scene = pkg->loadScene();
    SAFE_RELEASE(pkg);

    // Get light node
    Node* lightNode = _scene->findNode("directionalLight");
    Light* light = lightNode->getLight();

    // Initialize box model
    Node* boxNode = _scene->findNode("box");
    Model* boxModel = boxNode->getModel();
    Material* boxMaterial = boxModel->setMaterial("res/box.material");
    boxMaterial->getParameter("u_lightColor")->setValue(light->getColor());
    boxMaterial->getParameter("u_lightDirection")->setValue(lightNode->getForwardVectorView());
}

void TemplateGame::finalize()
{
    SAFE_RELEASE(_scene);
}

void TemplateGame::update(long elapsedTime)
{
    // Rotate model
    _scene->findNode("box")->rotateY(MATH_DEG_TO_RAD((float)elapsedTime / 1000.0f * 180.0f));
}

void TemplateGame::render(long elapsedTime)
{
    // Clear the color and depth buffers
    clear(CLEAR_COLOR_DEPTH, Vector4::zero(), 1.0f, 0);

    // Visit all the nodes in the scene for drawing
    _scene->visit(this, &TemplateGame::drawScene);
}

void TemplateGame::drawScene(Node* node, long cookie)
{
    // If the node visited contains a model, draw it
    Model* model = node->getModel(); 
    if (model)
    {
        model->draw();
    }
}

void TemplateGame::touch(int x, int y, int touchEvent)
{
    switch (touchEvent)
    {
    case Input::TOUCHEVENT_PRESS:
        break;
    case Input::TOUCHEVENT_RELEASE:
        break;
    case Input::TOUCHEVENT_MOVE:
        break;
    };
}
