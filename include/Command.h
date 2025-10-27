#pragma once
#include "EditorContext.h"

class Command {

public:
    explicit Command(EditorContext&( ctx)) : m_ctx(ctx) {};
    virtual ~Command() = default ;
    virtual void Execute() const = 0  ;
    virtual void Undo() const = 0  ;


protected:
    EditorContext& m_ctx ;

};

