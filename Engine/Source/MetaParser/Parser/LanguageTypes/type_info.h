#pragma once
#include "../Common/namespace.h"
#include "../Cursor/cursor.h"

#include "../Meta/meta_info.h"
#include "../../Parser/parser.h"

class TypeInfo
{
public:
    TypeInfo(const Cursor& cursor, const Namespace& current_namespace);
    virtual ~TypeInfo(void) {}

    const MetaInfo& getMetaData(void) const;

    std::string getSourceFile(void) const;

    Namespace getCurrentNamespace() const;

    Cursor& getCurosr();

protected:
    MetaInfo meta_data_;

    bool enabled_;

    std::string alias_cn_;

    Namespace namespace_;

private:
    // cursor that represents the root of this language type
    Cursor root_cursor_;
};