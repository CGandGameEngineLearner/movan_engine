#pragma once

#include "runtime/core/math/vector2.h"

#include <memory>

namespace Movan
{
    class EditorUI;
    class MovanEngine;

    class MovanEditor 
    {
        friend class EditorUI;

    public:
        MovanEditor();
        virtual ~MovanEditor();

        void initialize(MovanEngine* engine_runtime);
        void clear();

        void run();

    protected:
        std::shared_ptr<EditorUI> m_editor_ui;
        MovanEngine* m_engine_runtime{ nullptr };
    };
} // namespace Movan
