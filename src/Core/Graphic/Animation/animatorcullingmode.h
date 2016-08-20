#ifndef ANIMATORCULLINGMODE
#define ANIMATORCULLINGMODE

enum class AnimatorCullingMode{
    AlwaysAnimate,	//Always animate the entire character. Object is animated even when offscreen.
    CullUpdateTransforms,	//Retarget, IK and write of Transforms are disabled when renderers are not visible.
    CullCompletely	//Animation is completely disabled when renderers are not visible.
};

#endif // ANIMATORCULLINGMODE

