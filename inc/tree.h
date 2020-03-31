#pragma once

#include "./list.h"

namespace bpp
{
namespace ulib
{


template <typename T>
class TreeNode
{
public:
    TreeNode(T Value, TreeNode<T>* pParrent = nullptr)
    {
        mpParrent = pParrent;
        if (pParrent != nullptr)
        {
            pParrent->addChild(this);
        }
    }

    void addChild(const TreeNode<T>& child)
    {
        mChildren.add(child);
    }

    bool removeChild(const TreeNode<T>& child)
    {
        typename bpp::ulib::List<TreeNode<T>>::iterator it = mChildren.find(child);
        if (it.hasValidValue())
        {
            mChildren.erase(it);
            return true;
        }
        return false;
    }


private:
    TreeNode<T>*                 mpParrent;
    bpp::ulib::List<TreeNode<T>> mChildren;
    T                            mValue;
};

}}//namespace
