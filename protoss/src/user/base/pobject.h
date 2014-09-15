// pobject.h
// The base class of all protoss objects which needs the parentship.
//
// Copyright 2013 by Cooee. All rights reserved.
//
// Hongwei Li lihw81@gmail.com
//
// 

#ifndef POBJECT_H
#define POBJECT_H

#include <PUser/pdata.h>

// REVIEW(lihw): overall, I think we can combine PNode and PObject so that the 
// latter has the parentship and update callback, otherwise PObject is a little
// skinny.
// FEEDBACK: thanks.

class P_DLLEXPORT PObject : public PData
{
public:
    // in PObject's constructor, we generate a global unique id as identification.
    pUint32         m_id;
public:
    PObject();
    virtual ~PObject();

    // REVIEW(lihw): it is a good idea to add reference count to PObject, but
    // we need to be careful about the design of the destructor of PObject so
    // that others can't call it to release the PObject directly.
    // FEEDBACK: I think we should allow others to call PObject::release().
    // in parent's destructor, would call each child's release() function.
    // I don't quite get your meaning.
    void release();
    void retain();
    // REVIEW(lihw): I'd like to hear more about why we need isSingleReference()
    // and retainCount(). ;-)
    // FEEDBACK: thanks.
    // these two functions are used for scripting language - js and lua in cocos2d.
    // yes, we can remove it.

    // REVIEW(lihw): In addition to reference count, one thing I am looking for
    // in PObject is the parentship and children of a PObject. My original thought
    // is each PObject contains a list of PObject as its children and a parent.
    // In the runtime, we have a PObject forest (trees) given some PObjects have no parents.
    // Do we have an alternative design different from PObject tree? Or we put it
    // somewhere else?
    // FEEDBACK: I put it in pnode originally.
    // after discussion, we will combine pobject and pnode.

    virtual void addChild(PObject *child);
    // REVIEW(lihw): I think we can drop zOrder. In 3D rendering, z order
    // becomes useless as we have z dimension and hardware depth testing.
    // FEEDBACK: thanks.
    virtual void addChild(PObject *child, const pChar *name);
    
    // REVIEW(lihw): how do we generate a globally unique tag? Do we put
    // the burden of this tag generation task on API users? It needs further
    // discussion.
    // FEEDBACK: replace tag to name.
    virtual PObject *getChild(const pChar *name) const;

    PArray<PObject *> &getChildren();
    pUint32 getChildrenCount() const;
    
    // REVIEW(lihw): when we call removeAllChildren(), are we going to 
    // delete the memory of these children?
    // FEEDBACK: just call children's PObject::release(),
    // do nothing about memory directly.
    virtual void removeAllChildren();
    // REVIEW(lihw): is there any function that can remove single child?
    // FEEDBACK: thanks. I forgot to fill it.
    virtual void removeChild(PObject *child);
    virtual void removeChild(const pChar *name);

    // REVIEW(lihw): could you give me a little hint about what this function
    // does?
    // REVIEW(lihw): what is paremeter dt about? Could you give a little
    // more explanation? Is this function called once every frame?
    // FEEDBACK: it's update stuff.
    // I designed a callback function for animation at first, 
    // when scheduleUpdate() is called, update() will be called every frame
    // (dt means 'delta time').
    // but we shouldn't involve animation here, so remove it to keep PObject concise.
    
    // REVIEW(lihw): is there any function that can check the tag/name
    // of a PNode?
    // FEEDBACK: thanks.
    // name getter
    virtual PString getName();
    // name setter
    virtual void setName(const pChar *name);
    
protected:
    // REVIEW(lihw): hmm, I remember we don't need to add the type identifier
    // into the variable name by our coding style.
    // FEEDBACK: thanks.
    // fix coding style.
    // count of references
    pUint32             m_reference;
    // each pobject has a unique name, init with m_id.
    PString             m_name;
    // reference to parent pobject
    PObject             *m_parent;
    // array of children pobjects
    PArray<PObject *>   m_children;
};


#endif // !POBJECT_H
