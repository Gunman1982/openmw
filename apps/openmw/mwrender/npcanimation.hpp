#ifndef _GAME_RENDER_NPCANIMATION_H
#define _GAME_RENDER_NPCANIMATION_H

#include "animation.hpp"

#include "../mwworld/inventorystore.hpp"

namespace ESM
{
    struct NPC;
}

namespace MWRender
{

class NpcAnimation : public Animation, public MWWorld::InventoryStoreListener
{
public:
    virtual void equipmentChanged() { updateParts(); }
    virtual void permanentEffectAdded(const ESM::MagicEffect *magicEffect, bool isNew, bool playSound);

public:
    typedef std::map<ESM::PartReferenceType,std::string> PartBoneMap;

    enum ViewMode {
        VM_Normal,
        VM_FirstPerson,
        VM_HeadOnly
    };

private:
    static const PartBoneMap sPartList;

    bool mListenerDisabled;

    // Bounded Parts
    NifOgre::ObjectList mObjectParts[ESM::PRT_Count];

    const ESM::NPC *mNpc;
    std::string    mHeadModel;
    std::string    mHairModel;
    ViewMode       mViewMode;
    bool mShowWeapons;

    int mVisibilityFlags;

    int mPartslots[ESM::PRT_Count];  //Each part slot is taken by clothing, armor, or is empty
    int mPartPriorities[ESM::PRT_Count];

    Ogre::Vector3 mFirstPersonOffset;

    void updateNpcBase();

    NifOgre::ObjectList insertBoundedPart(const std::string &model, int group, const std::string &bonename);

    void removeIndividualPart(ESM::PartReferenceType type);
    void reserveIndividualPart(ESM::PartReferenceType type, int group, int priority);

    bool addOrReplaceIndividualPart(ESM::PartReferenceType type, int group, int priority, const std::string &mesh);
    void removePartGroup(int group);
    void addPartGroup(int group, int priority, const std::vector<ESM::PartReference> &parts);

public:
    /**
     * @param ptr
     * @param node
     * @param visibilityFlags
     * @param disableListener  Don't listen for equipment changes and magic effects. InventoryStore only supports
     *                         one listener at a time, so you shouldn't do this if creating several NpcAnimations
     *                         for the same Ptr, eg preview dolls for the player.
     *                         Those need to be manually rendered anyway.
     * @param viewMode
     */
    NpcAnimation(const MWWorld::Ptr& ptr, Ogre::SceneNode* node, int visibilityFlags, bool disableListener = false,
                 ViewMode viewMode=VM_Normal);
    virtual ~NpcAnimation();

    virtual Ogre::Vector3 runAnimation(float timepassed);

    virtual void showWeapons(bool showWeapon);

    void setViewMode(ViewMode viewMode);

    void updateParts();

    /// \brief Applies a translation to the arms and hands.
    /// This may be called multiple times before the animation
    /// is updated to add additional offsets.
    void addFirstPersonOffset(const Ogre::Vector3 &offset);

    /// Rebuilds the NPC, updating their root model, animation sources, and equipment.
    void rebuild();
};

}

#endif
