#ifndef COMMANDS_H
#define COMMANDS_H

#include "Scene.h"


class ScreenCommand {
public:
    virtual ~ScreenCommand() {}
    virtual void execute(Scene& scene) = 0;
};

class RenderCommand : public ScreenCommand {
public:
    virtual ~RenderCommand() {}
    RenderCommand(int width, int height, const RenderMode& rd_mode, const ColorGC& bgColor, const ColorGC& normColor,
        const ColorGC& wireColor) : screenWidth(width), screenHeigth(height), rd_mode(rd_mode), bg(bgColor),
        normals(normColor), wireframe(wireColor){}
    virtual void execute(Scene& scene) override {
        scene.render(screenWidth, screenHeigth, rd_mode, bg, normals, wireframe);
    }
protected:
    int screenWidth;
    int screenHeigth;
    RenderMode rd_mode;
    ColorGC bg;
    ColorGC normals;
    ColorGC wireframe;
};

class TransformationCommand : public RenderCommand {
public:
    TransformationCommand(int width, int height, const RenderMode& rd_mode, const ColorGC& bgColor,
        const ColorGC& normColor, const ColorGC& wireColor,
        const Vector3& ref_point, const Vector3& movement,
        float aspectRatio,int action, int axis,int tSpace, 
        float sensitivity)
        : RenderCommand(width,height,rd_mode,bgColor, normColor, wireColor)
        , ref_point(ref_point), movement(movement), aspectRatio(aspectRatio),
        action(action), axis(axis), tSpace(tSpace), sensitivity(sensitivity) {}

    TransformationCommand(const RenderCommand& rc, const Vector3& ref_point, const Vector3& movement,
        float aspectRatio, int action, int axis, int tSpace, float sensitivity)
        : RenderCommand(rc), ref_point(ref_point), movement(movement), aspectRatio(aspectRatio),
        action(action), axis(axis), tSpace(tSpace), sensitivity(sensitivity) {}

    void execute(Scene& scene) override {
        scene.handleTransformationAction(ref_point, movement, aspectRatio,action, axis, sensitivity,tSpace, screenWidth, screenHeigth);
        RenderCommand::execute(scene);
    }

private:
    Vector3 ref_point;
    Vector3 movement;
    float aspectRatio;
    int action;
    int axis;
    int tSpace;
    float sensitivity;
};
#endif //COMMANDS_H

//
//class ViewCommand : public ICommand {
//public:
//    ViewCommand(float aspectRatio, int axis, float sensitivity)
//        : ref_point(ref_point), movement(movement), aspectRatio(aspectRatio), axis(axis), sensitivity(sensitivity) {}
//
//    void execute(Scene& scene) override {
//        scene.handleViewAction(ref_point, movement, aspectRatio, /*action=*/1, axis, /*perspective=*/false, sensitivity, /*space=*/0);
//    }
//
//private:
//    int flag;
//    int axis;
//    float sensitivity;
//};
//
//class ViewableObjectsCommand : public ICommand {
//public:
//    ViewableObjectsCommand(float aspectRatio, int axis, float sensitivity)
//        : ref_point(ref_point), movement(movement), aspectRatio(aspectRatio), axis(axis), sensitivity(sensitivity) {}
//
//    void execute(Scene& scene) override {
//        scene.handleViewObjectsAction(ref_point, movement, aspectRatio, /*action=*/1, axis, /*perspective=*/false, sensitivity, /*space=*/0);
//    }
//
//private:
//    int flag;
//    int axis;
//    float sensitivity;
//};
//class SetColorsCommand : public ICommand {
//public:
//    SetColorsCommand(const Vector3& ref_point, const Vector3& movement, float aspectRatio, int axis, float sensitivity)
//        : ref_point(ref_point), movement(movement), aspectRatio(aspectRatio), axis(axis), sensitivity(sensitivity) {}
//
//    void execute(Scene& scene) override {
//        scene.handleColorAction(ref_point, movement, aspectRatio, /*action=*/1, axis, /*perspective=*/false, sensitivity, /*space=*/0);
//    }
//
//private:
//    Vector3 ref_point;
//    Vector3 movement;
//    float aspectRatio;
//    int axis;
//    float sensitivity;
//};

