#pragma once
#include "SceneNode.h"
#include <vector> // Include for std::vector
#include <memory>


class SceneGraph : public SceneNode
{
public:
    SceneGraph() : SceneNode(L"Root") {};
    SceneGraph(wstring name) : SceneNode(name) {};
    ~SceneGraph(void) {};

    virtual bool Initialise(void);
    virtual void Update(const Matrix& worldTransformation);
    virtual void Render(void);
    virtual void Shutdown(void);

    void Add(SceneNodePointer node);
    void Remove(SceneNodePointer node);
    SceneNodePointer Find(wstring name);


  
private:
    std::vector<SceneNodePointer> _children; // Collection of child nodes
};

typedef std::shared_ptr<SceneGraph> SceneGraphPointer;
