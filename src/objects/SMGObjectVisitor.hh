#pragma once

#include "objects/SMGObject.hh"
#include "objects/SMGRegion.hh"

namespace smg {

class SMGObjectVisitor {
 private:
  void VisitDefault(const SMGObject& object);

 public:
  void Visit(const SMGObject& object);
  void Visit(const SMGRegion& object);
  // void Visit(const SMGSingleLinkedList& object);
  // void Visit(const SimpleBinaryTree& object);
};

}  // namespace smg
