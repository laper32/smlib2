#if defined _entity_included
    #endinput
#endif

#define _entity_included

inline bool EntitySetParent(int parent, int child)
{
    SetVariantString("!activator");
    return AcceptEntityInput(child, "SetParent", parent, child, 0);
}